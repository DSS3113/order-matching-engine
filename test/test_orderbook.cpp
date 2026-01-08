#include <gtest/gtest.h>
#include <memory>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "Side.hpp"

TEST(OrderBookTest, AddOrder) {
    OrderBook ob;
    auto buyOrder = std::make_shared<Order>("AAPL", Side::BUY, 100, 150.0);
    auto sellOrder = std::make_shared<Order>("AAPL", Side::SELL, 100, 151.0);

    ob.add_order(buyOrder);
    ob.add_order(sellOrder);

    EXPECT_EQ(ob.get_order(buyOrder->get_order_id()), buyOrder);
    EXPECT_EQ(ob.get_order(sellOrder->get_order_id()), sellOrder);
}

TEST(OrderBookTest, CancelOrder) {
    OrderBook ob;
    auto buyOrder = std::make_shared<Order>("AAPL", Side::BUY, 100, 150.0);

    ob.add_order(buyOrder);
    ob.cancel_order(buyOrder);

    EXPECT_EQ(buyOrder->get_status(), OrderStatus::CANCELLED);
}
