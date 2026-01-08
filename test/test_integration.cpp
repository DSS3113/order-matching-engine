#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "MatchingEngine.hpp"
#include "Order.hpp"
#include "OrderBook.hpp"
#include "Trade.hpp"
#include "Side.hpp"

TEST(IntegrationTest, FullOrderLifecycle) {
    MatchingEngine engine;

    // Place buy and sell orders
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    auto sellOrder = engine.add_order("AAPL", 150.0, 100, Side::SELL);

    // Both should be filled
    EXPECT_EQ(buyOrder->get_status(), OrderStatus::FILLED);
    EXPECT_EQ(sellOrder->get_status(), OrderStatus::FILLED);

    // Cancel a filled order (should not change status)
    auto cancelled = engine.cancel_order(buyOrder->get_order_id(), "AAPL");
    EXPECT_TRUE(cancelled == nullptr || cancelled->get_status() == OrderStatus::FILLED);
}

TEST(IntegrationTest, PartialFillAndAmend) {
    MatchingEngine engine;

    // Place a buy order
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);

    // Place a sell order with less quantity
    auto sellOrder = engine.add_order("AAPL", 150.0, 50, Side::SELL);

    EXPECT_EQ(buyOrder->get_status(), OrderStatus::PARTIAL_FILLED);
    EXPECT_EQ(sellOrder->get_status(), OrderStatus::FILLED);

    // Amend remaining buy order
    auto amended = engine.amend_order(buyOrder->get_order_id(), "AAPL", 151.0, 50);

    ASSERT_NE(amended, nullptr);
    EXPECT_DOUBLE_EQ(amended->get_price(), 151.0);
    EXPECT_EQ(amended->get_quantity(), 50);
}

TEST(IntegrationTest, MultipleInstruments) {
    MatchingEngine engine;

    auto buyAAPL = engine.add_order("AAPL", 150.0, 100, Side::BUY);
    auto sellGOOG = engine.add_order("GOOG", 2800.0, 100, Side::SELL);

    // Orders for different instruments should not match
    EXPECT_TRUE(buyAAPL->get_status() == OrderStatus::PARTIAL_FILLED ||
                buyAAPL->get_status() == OrderStatus::NEW);
    EXPECT_TRUE(sellGOOG->get_status() == OrderStatus::PARTIAL_FILLED ||
                sellGOOG->get_status() == OrderStatus::NEW);
}
