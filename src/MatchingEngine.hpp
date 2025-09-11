#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include <Order.hpp>
#include <OrderBook.hpp>
#include <Side.hpp>
#include <Trade.hpp>

class MatchingEngine {
    private:
        std::unordered_map<std::string, std::unique_ptr<OrderBook>> orderBooks;
        std::vector<std::unique_ptr<Trade>> trades;

    public:
        std::shared_ptr<Order> add_order(const std::string& instrument, double price, uint32_t quantity, Side side);
        std::shared_ptr<Order> cancel_order(uint64_t orderId, const std::string& instrument);
        std::shared_ptr<Order> amend_order(uint64_t orderId, const std::string& instrument, double newPrice, uint32_t newQuantity);
};