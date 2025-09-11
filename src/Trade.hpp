#pragma once

#include <string>

#include <Side.hpp>

class Trade {
    private:
        static uint64_t lastTradeId;
        uint64_t orderId;
        std::string instrument;
        double price;
        double quantity;
        Side side;
        uint64_t tradeId;

    public:
        Trade(uint64_t orderId, std::string instrument, double price, double quantity, Side side);
        uint64_t get_order_id();
        uint64_t get_trade_id();
        const std::string& get_instrument();
        bool is_buy();
        bool is_sell();
};