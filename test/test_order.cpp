#include <gtest/gtest.h>
#include "Order.hpp"

TEST(OrderTest, Creation) {
    Order order("AAPL", Side::BUY, 100, 150.0);
    EXPECT_EQ(order.get_instrument(), "AAPL");
    EXPECT_TRUE(order.is_buy());
    EXPECT_FALSE(order.is_sell());
    EXPECT_EQ(order.get_quantity(), 100);
    EXPECT_DOUBLE_EQ(order.get_price(), 150.0);
    EXPECT_EQ(order.get_status(), OrderStatus::NEW);
}

TEST(OrderTest, Fill) {
    Order order("AAPL", Side::BUY, 100, 150.0);

    bool filled = order.fill(50, 150.0);
    EXPECT_TRUE(filled);
    EXPECT_EQ(order.get_remaining_quantity(), 50);
    EXPECT_EQ(order.get_status(), OrderStatus::PARTIAL_FILLED);

    filled = order.fill(50, 150.0);
    EXPECT_TRUE(filled);
    EXPECT_EQ(order.get_remaining_quantity(), 0);
    EXPECT_EQ(order.get_status(), OrderStatus::FILLED);
}

TEST(OrderTest, Cancel) {
    Order order("AAPL", Side::BUY, 100, 150.0);

    bool cancelled = order.cancel();
    EXPECT_TRUE(cancelled);
    EXPECT_EQ(order.get_status(), OrderStatus::CANCELLED);
    EXPECT_EQ(order.get_remaining_quantity(), 0);
}
