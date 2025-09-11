#include "../src/OrderBook.hpp"
#include "../src/Order.hpp"
#include "../src/Side.hpp"
#include <cassert>
#include <iostream>
#include <memory>

void test_add_order() {
    OrderBook ob;
    auto buyOrder = std::make_shared<Order>("AAPL", Side::BUY, 100, 150.0);
    auto sellOrder = std::make_shared<Order>("AAPL", Side::SELL, 100, 151.0);
    ob.add_order(buyOrder);
    ob.add_order(sellOrder);
    assert(ob.get_order(buyOrder->get_order_id()) == buyOrder);
    assert(ob.get_order(sellOrder->get_order_id()) == sellOrder);
    std::cout << "test_add_order passed\n";
}

void test_cancel_order() {
    OrderBook ob;
    auto buyOrder = std::make_shared<Order>("AAPL", Side::BUY, 100, 150.0);
    ob.add_order(buyOrder);
    ob.cancel_order(buyOrder);
    assert(buyOrder->get_status() == OrderStatus::CANCELLED);
    std::cout << "test_cancel_order passed\n";
}

int main() {
    test_add_order();
    test_cancel_order();
    std::cout << "All OrderBook tests passed!\n";
    return 0;
}
