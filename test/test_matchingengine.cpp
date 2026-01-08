#include <gtest/gtest.h>
#include <memory>
#include "MatchingEngine.hpp"
#include "Order.hpp"
#include "Side.hpp"

TEST(MatchingEngineTest, CancelOrder) {
    MatchingEngine engine;
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);

    ASSERT_NE(buyOrder, nullptr);

    auto cancelled = engine.cancel_order(buyOrder->get_order_id(), "AAPL");
    EXPECT_TRUE(cancelled == nullptr || cancelled->get_status() == OrderStatus::CANCELLED);
}

TEST(MatchingEngineTest, AmendOrder) {
    MatchingEngine engine;
    auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);

    ASSERT_NE(buyOrder, nullptr);

    auto amended = engine.amend_order(buyOrder->get_order_id(), "AAPL", 151.0, 50);

    ASSERT_NE(amended, nullptr);
    EXPECT_DOUBLE_EQ(amended->get_price(), 151.0);
    EXPECT_EQ(amended->get_quantity(), 50);
}
