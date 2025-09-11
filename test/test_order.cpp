#include "../src/Order.hpp"
#include <cassert>
#include <iostream>

void test_order_creation() {
    Order order("AAPL", Side::BUY, 100, 150.0);
    assert(order.get_instrument() == "AAPL");
    assert(order.is_buy());
    assert(!order.is_sell());
    assert(order.get_quantity() == 100);
    assert(order.get_price() == 150.0);
    assert(order.get_status() == OrderStatus::NEW);
    std::cout << "test_order_creation passed\n";
}

void test_order_fill() {
    Order order("AAPL", Side::BUY, 100, 150.0);
    bool filled = order.fill(50, 150.0);
    assert(filled);
    assert(order.get_remaining_quantity() == 50);
    assert(order.get_status() == OrderStatus::PARTIAL_FILLED);
    filled = order.fill(50, 150.0);
    assert(filled);
    assert(order.get_remaining_quantity() == 0);
    assert(order.get_status() == OrderStatus::FILLED);
    std::cout << "test_order_fill passed\n";
}

void test_order_cancel() {
    Order order("AAPL", Side::BUY, 100, 150.0);
    bool cancelled = order.cancel();
    assert(cancelled);
    assert(order.get_status() == OrderStatus::CANCELLED);
    assert(order.get_remaining_quantity() == 0);
    std::cout << "test_order_cancel passed\n";
}

int main() {
    test_order_creation();
    test_order_fill();
    test_order_cancel();
    std::cout << "All Order tests passed!\n";
    return 0;
}
