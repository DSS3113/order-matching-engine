#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>

#include <Order.hpp>
#include <Trade.hpp>

class OrderBook {
    private:
        std::map< double, std::unique_ptr<std::deque<std::shared_ptr<Order>>> > asks;
        std::map< double, std::unique_ptr<std::deque<std::shared_ptr<Order>>>, std::greater<double> > bids;
        std::unordered_map<uint64_t, std::shared_ptr<Order>> orderIdMap;
    public:
        void add_order(std::shared_ptr<Order> order);
        void cancel_order(std::shared_ptr<Order> order);
        std::shared_ptr<Order> get_order(uint64_t orderId);
        bool no_asks_exist();
        bool no_bids_exist();
        double peek_best_ask_price();
        double peek_best_bid_price();
        bool consume_best_ask(std::shared_ptr<Order> order, std::vector<std::unique_ptr<Trade>>&);
        bool consume_best_bid(std::shared_ptr<Order> order, std::vector<std::unique_ptr<Trade>>&);
};