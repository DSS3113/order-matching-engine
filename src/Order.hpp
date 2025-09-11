#pragma once

#include <string>

#include <Side.hpp>

enum class OrderStatus {
    NEW,
    PARTIAL_FILLED,
    FILLED,
    CANCELLED
};

class Order {
    private:
        static uint64_t lastOrderId;
        uint64_t orderId;                                       // Unique identifier
        std::string instrument;                                 // Trading instrument (e.g., "AAPL")
        Side side;                                              // BUY or SELL (enum)
        uint32_t quantity;                                      // Number of shares/units
        uint32_t remainingQuantity;                             // Unfilled portion
        double price;                                           // Limit price (0 for market orders)
        std::chrono::system_clock::time_point timestamp;        // When order was placed
        OrderStatus status;                                     // NEW, PARTIAL_FILLED, FILLED, CANCELLED

    public:
        Order(std::string instrument, Side side, uint32_t quantity,
              double price);
        bool fill(uint32_t quantity, double price);
        bool cancel();
        bool is_fully_filled();
        uint32_t get_quantity();
        void set_quantity(uint32_t newQuantity);
        uint32_t get_remaining_quantity();
        void set_remaining_quantity(uint32_t newRemainingQuantity);
        uint64_t get_order_id();
        const std::string& get_instrument();
        double get_price();
        OrderStatus get_status();
        bool is_buy();
        bool is_sell();
        void print_order();
};