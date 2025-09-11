#include <iostream>

#include <Order.hpp>
#include <chrono>

uint64_t Order::lastOrderId = 0;

Order::Order(std::string instrument, Side side, uint32_t quantity,
            double price) {
    this->orderId = ++Order::lastOrderId;
    this->instrument = instrument;
    this->side = side;
    this->quantity = quantity;
    this->remainingQuantity = quantity;
    this->price = price;
    this->timestamp = std::chrono::system_clock::now();
    this->status = OrderStatus::NEW;
}

bool Order::fill(uint32_t quantity, double price) {
    if (quantity <= this->remainingQuantity) {
        if ((is_buy() && price <= this->price) || (is_sell() && price >= this->price)) {
            this->remainingQuantity -= quantity;
        }
        this->status = OrderStatus::PARTIAL_FILLED;

        if (this->remainingQuantity == 0) {
            this->status = OrderStatus::FILLED;
        }

        return true;
    } 

    return false;
}

bool Order::cancel() {
    status = OrderStatus::CANCELLED;
    remainingQuantity = 0;
    return true;
}
bool Order::is_fully_filled() {
    return status == OrderStatus::FILLED;
}

uint32_t Order::get_remaining_quantity() {
    return remainingQuantity;
}

uint64_t Order::get_order_id() {
    return orderId;
}

const std::string& Order::get_instrument() {
    return instrument;
}

double Order::get_price() {
    return price;
}

OrderStatus Order::get_status() {
    return status;
}

bool Order::is_buy() {
    return side == Side::BUY;
}

bool Order::is_sell() {
    return side == Side::SELL;
}

uint32_t Order::get_quantity() {
    return quantity;
}

void Order::set_quantity(uint32_t newQuantity) {
    quantity = newQuantity;
}

void Order::set_remaining_quantity(uint32_t newRemainingQuantity) {
    remainingQuantity = newRemainingQuantity;
}

void Order::print_order() {
    std::cout << "Order ID: " << orderId 
              << ", Instrument: " << instrument 
              << ", Side: " << (side == Side::BUY ? "BUY" : "SELL") 
              << ", Quantity: " << quantity 
              << ", Remaining Quantity: " << remainingQuantity 
              << ", Price: " << price 
              << ", Status: ";
    switch (status) {
        case OrderStatus::NEW:
            // Removed std::cout statement
            break;
        case OrderStatus::PARTIAL_FILLED:
            // Removed std::cout statement
            break;
        case OrderStatus::FILLED:
            // Removed std::cout statement
            break;
        case OrderStatus::CANCELLED:
            // Removed std::cout statement
            break;
        case OrderStatus::REJECTED:
            // Removed std::cout statement
            break;
    }
        // Removed std::cout statement
}