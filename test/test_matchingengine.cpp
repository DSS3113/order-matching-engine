#include "../src/MatchingEngine.hpp"
#include "../src/Order.hpp"
#include "../src/Side.hpp"
#include <cassert>
#include <iostream>
#include <memory>

void test_cancel_order() {
    std::cout << "Starting test_cancel_order" << std::endl;
    MatchingEngine engine;
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    std::cout << "Buy order created: " << (buyOrder ? "OK" : "NULL") << std::endl;
    auto cancelled = engine.cancel_order(buyOrder->get_order_id(), "AAPL");
    std::cout << "Cancel order returned: " << (cancelled ? "OK" : "NULL") << std::endl;
    assert(cancelled == nullptr || cancelled->get_status() == OrderStatus::CANCELLED);
    std::cout << "test_cancel_order passed\n";
}

void test_amend_order() {
    std::cout << "Starting test_amend_order" << std::endl;
    MatchingEngine engine;
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    std::cout << "Buy order created: " << (buyOrder ? "OK" : "NULL") << std::endl;
    auto amended = engine.amend_order(buyOrder->get_order_id(), "AAPL", 151.0, 50);
    std::cout << "Amend order returned: " << (amended ? "OK" : "NULL") << std::endl;
    assert(amended != nullptr);
    assert(amended->get_price() == 151.0);
    assert(amended->get_quantity() == 50);
    std::cout << "test_amend_order passed\n";
}
int main() {
    std::cout << "Starting MatchingEngine tests" << std::endl;
    test_cancel_order();
    test_amend_order();
    std::cout << "All MatchingEngine tests passed!\n";
    return 0;
}
