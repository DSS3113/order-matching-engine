#include <string>

#include <Side.hpp>
#include <Trade.hpp>

uint64_t Trade::lastTradeId = 0;

Trade::Trade(uint64_t orderId, std::string instrument, double price, double quantity, Side side) {
    this->orderId = orderId;
    this->instrument = instrument;
    this->price = price;
    this->quantity = quantity;
    this->side = side;
    this->tradeId = ++Trade::lastTradeId;
}

uint64_t Trade::get_order_id() {
    return orderId;
}

uint64_t Trade::get_trade_id() {
    return tradeId;
}

const std::string& Trade::get_instrument() {
    return instrument;
}

bool Trade::is_buy() {
    return side == Side::BUY;
}

bool Trade::is_sell() {
    return side == Side::SELL;
}
