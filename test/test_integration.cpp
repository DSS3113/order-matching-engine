#include "../src/MatchingEngine.hpp"
#include "../src/Order.hpp"
#include "../src/OrderBook.hpp"
#include "../src/Trade.hpp"
#include "../src/Side.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <memory>

void test_full_order_lifecycle() {
    MatchingEngine engine;
    // Place buy and sell orders
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    auto sellOrder = engine.add_order("AAPL", 150.0, 100, Side::SELL);
    // Both should be filled
    buyOrder->print_order();
    sellOrder->print_order();
    assert(buyOrder->get_status() == OrderStatus::FILLED);
    assert(sellOrder->get_status() == OrderStatus::FILLED);
    // Cancel a filled order (should not change status)
    auto cancelled = engine.cancel_order(buyOrder->get_order_id(), "AAPL");
    assert(cancelled == nullptr || cancelled->get_status() == OrderStatus::FILLED);
    std::cout << "test_full_order_lifecycle passed\n";
}

void test_partial_fill_and_amend() {
    MatchingEngine engine;
    // Place a buy order
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    // Place a sell order with less quantity
    auto sellOrder = engine.add_order("AAPL", 150.0, 50, Side::SELL);
    assert(buyOrder->get_status() == OrderStatus::PARTIAL_FILLED);
    assert(sellOrder->get_status() == OrderStatus::FILLED);
    // Amend remaining buy order
    auto amended = engine.amend_order(buyOrder->get_order_id(), "AAPL", 151.0, 50);
    assert(amended != nullptr);
    assert(amended->get_price() == 151.0);
    assert(amended->get_quantity() == 50);
    std::cout << "test_partial_fill_and_amend passed\n";
}

void test_multiple_instruments() {
    MatchingEngine engine;
    auto buyAAPL = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    auto sellGOOG = engine.add_order("GOOG", 2800.0, 100, Side::SELL);
    assert(buyAAPL->get_status() == OrderStatus::PARTIAL_FILLED || buyAAPL->get_status() == OrderStatus::NEW);
    assert(sellGOOG->get_status() == OrderStatus::PARTIAL_FILLED || sellGOOG->get_status() == OrderStatus::NEW);
    std::cout << "test_multiple_instruments passed\n";
}

int main() {
    test_full_order_lifecycle();
    test_partial_fill_and_amend();
    test_multiple_instruments();
    std::cout << "All integration tests passed!\n";
    return 0;
}
