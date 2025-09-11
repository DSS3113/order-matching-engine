#include <iostream>
#include <algorithm>

#include <OrderBook.hpp>

void OrderBook::add_order(std::shared_ptr<Order> order)  {
    
    double price = order->get_price();
    if (order->is_sell()) {
        if (asks.find(price) == asks.end())
            asks.insert({ price, std::make_unique<std::deque<std::shared_ptr<Order>>>() });
        asks.at(price)->push_back(order);
    } else {
         if (bids.find(price) == bids.end())
            bids.insert({ price, std::make_unique<std::deque<std::shared_ptr<Order>>>() });
            
        bids.at(price)->push_back(order);
    }

    auto orderId = order->get_order_id();
    if (orderIdMap.find(orderId) == orderIdMap.end())
        orderIdMap.insert({ orderId, order });
    else    
        orderIdMap[orderId] = order;
    
        
}

void OrderBook::cancel_order(std::shared_ptr<Order> order) {
    
    order->cancel();

    double orderPrice = order->get_price();
    uint64_t orderId = order->get_order_id();
    std::deque<std::shared_ptr<Order>>* priceLevel = nullptr;

    if (order->is_buy() && bids.find(orderPrice) != bids.end() && !bids.at(orderPrice)->empty()) {
        priceLevel = bids.at(orderPrice).get();
    } else if (order->is_sell() && asks.find(orderPrice) != asks.end() && !asks.at(orderPrice)->empty()) {
        priceLevel = asks.at(orderPrice).get();
    }
    
    if (priceLevel) {
        
        auto it = std::find(priceLevel->begin(), priceLevel->end(), order);
        if (it != priceLevel->end()) {
                
            orderIdMap.erase(orderId);
            priceLevel->erase(it);
            if (priceLevel->empty()) {
                    
                if (order->is_buy())
                    bids.erase(orderPrice);
                else
                    asks.erase(orderPrice);
            }
        }
    }
}

std::shared_ptr<Order> OrderBook::get_order(uint64_t orderId) {
    try { 
        return orderIdMap.at(orderId);
    } catch (const std::out_of_range& e) {
        return nullptr;
    }
}

bool OrderBook::no_asks_exist() {
    return asks.empty();
}

bool OrderBook::no_bids_exist() {
    return bids.empty();
}

double OrderBook::peek_best_ask_price() {
    if (asks.empty()) {
        throw std::runtime_error("No ask prices available");
    }
    return asks.begin()->first;
}

double OrderBook::peek_best_bid_price() {
    if (bids.empty()) {
        throw std::runtime_error("No bid prices available");
    }
    return bids.begin()->first;
}

bool OrderBook::consume_best_ask(std::shared_ptr<Order> order, std::vector<std::unique_ptr<Trade>>& trades) {
    if (asks.empty())
        return false;
    double bestAskPrice = peek_best_ask_price();
    if (asks.find(bestAskPrice) == asks.end() || asks.at(bestAskPrice)->empty())
        return false;

    auto bestAsk = asks.at(bestAskPrice)->front();

    if (order->get_price() < bestAsk->get_price()) {
        return false;
    }
    uint32_t fillableQuantity = std::min(order->get_remaining_quantity(), bestAsk->get_remaining_quantity());

    bool fillSuccess = order->fill(fillableQuantity, bestAsk->get_price());
    if (!fillSuccess) {
        return false;
    }
    trades.push_back(std::make_unique<Trade>(order->get_order_id(), order->get_instrument(), bestAskPrice, fillableQuantity, Side::BUY));
    trades.push_back(std::make_unique<Trade>(bestAsk->get_order_id(), bestAsk->get_instrument(), bestAskPrice, fillableQuantity, Side::SELL));
    bestAsk->fill(fillableQuantity, bestAsk->get_price());
    if (bestAsk->is_fully_filled()) {
        asks.at(bestAskPrice)->pop_front();
        orderIdMap.erase(bestAsk->get_order_id());
        if (asks.at(bestAskPrice)->empty())
            asks.erase(bestAskPrice);
    }
    if (order->is_fully_filled() && orderIdMap.find(order->get_order_id()) != orderIdMap.end()) {
        orderIdMap.erase(order->get_order_id());
    }

    return true;
}

bool OrderBook::consume_best_bid(std::shared_ptr<Order> order, std::vector<std::unique_ptr<Trade>>& trades) {
    if (bids.empty())
        return false;
    double bestBidPrice = peek_best_bid_price();
    if (bids.find(bestBidPrice) == bids.end() || bids.at(bestBidPrice)->empty())
        return false;

    auto bestBid = bids.at(bestBidPrice)->front();

    if (order->get_price() > bestBid->get_price()) {
        return false;
    }
    uint32_t fillableQuantity = std::min(order->get_remaining_quantity(), bestBid->get_remaining_quantity());

    bool fillSuccess = order->fill(fillableQuantity, bestBid->get_price());
    if (!fillSuccess) {
        return false;
    }
    trades.push_back(std::make_unique<Trade>(order->get_order_id(), order->get_instrument(), bestBidPrice, fillableQuantity, Side::SELL));
    trades.push_back(std::make_unique<Trade>(bestBid->get_order_id(), bestBid->get_instrument(), bestBidPrice, fillableQuantity, Side::BUY));
    bestBid->fill(fillableQuantity, bestBid->get_price());

    if (bestBid->is_fully_filled()) {
        bids.at(bestBidPrice)->pop_front();
        orderIdMap.erase(bestBid->get_order_id());
        if (bids.at(bestBidPrice)->empty())
            bids.erase(bestBidPrice);
    }
    if (order->is_fully_filled() && orderIdMap.find(order->get_order_id()) != orderIdMap.end()) {
        orderIdMap.erase(order->get_order_id());
    }
    
    return true;
}