#include <iostream>

#include <MatchingEngine.hpp>

std::shared_ptr<Order> MatchingEngine::add_order(const std::string& instrument, double price, uint32_t quantity, Side side) {    
    
    OrderBook* orderBook;
    auto orderBookFindIter = this->orderBooks.find(instrument);

    if (orderBookFindIter == this->orderBooks.end()) {
        orderBooks.insert({ instrument, std::make_unique<OrderBook>() });
    }

    orderBook = orderBooks.at(instrument).get();
    if (!orderBook) {
        return nullptr;
    }

    auto order = std::make_shared<Order>(instrument, side, quantity, price);
    

    if (side == Side::BUY) {
        while (!order->is_fully_filled() && !orderBook->no_asks_exist()) {   
            if(!orderBook->consume_best_ask(order, trades)) {
                
                break;
            }
        }
        if (!order->is_fully_filled()) {
            
            orderBook->add_order(order);
        }
    } else {
        while (!order->is_fully_filled() && !orderBook->no_bids_exist()) {
            
            if(!orderBook->consume_best_bid(order, trades)) {
                
                break;
            }
        }
        if (!order->is_fully_filled()) {
            
            orderBook->add_order(order);
        }
    }

    
    return order;
}

std::shared_ptr<Order> MatchingEngine::cancel_order(uint64_t orderId, const std::string& instrument) {    
    OrderBook* orderBook;
    auto orderBookFindIter = this->orderBooks.find(instrument);

    if (orderBookFindIter == this->orderBooks.end()) {
        return nullptr;
    }

    orderBook = orderBookFindIter->second.get();

    auto order = orderBook->get_order(orderId);

    if (order) {
        orderBook->cancel_order(order);
        return order;
    } else {
        return nullptr;
    }

}

std::shared_ptr<Order> MatchingEngine::amend_order(uint64_t orderId, const std::string& instrument, double newPrice, uint32_t newQuantity) {    
    OrderBook* orderBook;
    auto orderBookFindIter = this->orderBooks.find(instrument);

    if (orderBookFindIter == this->orderBooks.end()) {
        return nullptr;
    }

    orderBook = orderBookFindIter->second.get();

    auto order = orderBook->get_order(orderId);

    if (!order) {
        return nullptr;
    }

    Side side = order->is_buy() ? Side::BUY : Side::SELL;

    this->cancel_order(orderId, instrument);
    order = std::make_shared<Order>(instrument, side, newQuantity, newPrice);

    orderBook->add_order(order);

    return order;
}

