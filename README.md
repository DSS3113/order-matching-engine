# Order Matching Engine

A C++20 implementation of a financial order matching engine designed for low-latency trading systems. Built with modern C++ features, RAII principles, and comprehensive testing.

## 🚀 Features

- **Multi-Instrument Support**: Handle orders across different trading instruments simultaneously
- **Complete Order Lifecycle**: Create, amend, cancel, and fill orders with proper state management
- **Price-Time Priority**: Industry-standard FIFO matching algorithm within price levels
- **Memory Safe**: Modern C++ with smart pointers and RAII for automatic memory management
- **High Performance**: O(log n) order book operations using balanced trees
- **Comprehensive Testing**: Unit and integration tests with 100% core functionality coverage

## 🏗️ Architecture

### Core Components

```
MatchingEngine
├── OrderBook (per instrument)
│   ├── Bid Levels (std::map<price, orders>, descending)
│   ├── Ask Levels (std::map<price, orders>, ascending)
│   └── Order Index (O(1) order lookup)
├── Trade Generation
└── Order Management
```

### Key Design Decisions

- **Smart Pointers**: `std::shared_ptr<Order>` for shared ownership, `std::unique_ptr` for exclusive ownership
- **Ordered Maps**: `std::map` for natural price ordering (eliminates need for separate priority queues)
- **RAII**: Automatic resource management, exception-safe
- **Header-only Dependencies**: No external libraries required

## 🔧 Technical Implementation

### Order Matching Algorithm
```cpp
// Price-time priority matching
while (!order->is_fully_filled() && opposite_side_has_orders()) {
    if (can_match_with_best_opposite()) {
        execute_trade();
        update_quantities();
        remove_filled_orders();
    } else break;
}
```

### Performance Characteristics
- **Order Insertion**: O(log n) per price level
- **Best Price Lookup**: O(1) with ordered maps
- **Order Cancellation**: O(log n) + O(k) where k = orders at price level
- **Memory Usage**: Linear with number of active orders

## 📊 Supported Order Types

- **Market Orders**: Execute immediately at best available price
- **Limit Orders**: Execute only at specified price or better
- **Order Amendments**: Price and quantity modifications
- **Order Cancellations**: Remove orders from book

## 🚦 Getting Started

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 12+)
- Make build system

### Build & Test
```bash
# Build all components
make

# Run comprehensive test suite
make test

# Clean build artifacts
make clean
```

### Example Usage
```cpp
#include "MatchingEngine.hpp"

MatchingEngine engine;

// Add orders
auto buyOrder = engine.add_order("AAPL", 150.0, 100, Side::BUY);
auto sellOrder = engine.add_order("AAPL", 150.0, 100, Side::SELL);

// Orders automatically match at $150.00 for 100 shares
assert(buyOrder->get_status() == OrderStatus::FILLED);
assert(sellOrder->get_status() == OrderStatus::FILLED);

// Amend existing order
auto amended = engine.amend_order(buyOrder->get_order_id(), "AAPL", 151.0, 50);

// Cancel order
auto cancelled = engine.cancel_order(sellOrder->get_order_id(), "AAPL");
```

## 🧪 Testing Strategy

### Test Coverage
- **Unit Tests**: Individual component validation
- **Integration Tests**: End-to-end order lifecycle scenarios
- **Edge Cases**: Partial fills, amendments, multiple instruments

### Key Test Scenarios
```cpp
✅ Order creation and validation
✅ Price-time priority matching
✅ Partial fill handling
✅ Order amendments and cancellations
✅ Multi-instrument isolation
✅ Memory management verification
```

## 📈 Performance Optimizations

1. **Data Structure Choice**: Maps for O(log n) price-ordered access
2. **Memory Management**: Smart pointers eliminate allocation overhead
3. **Algorithmic Efficiency**: Minimal price level iterations
4. **Cache Locality**: Contiguous storage for orders at same price

## 🔮 Future Enhancements

### Production Readiness
- [ ] Thread safety with lock-free data structures
- [ ] Market data publishing (Level 1/Level 2)
- [ ] Order book snapshots and recovery
- [ ] Network protocol integration (FIX/Binary)

### Advanced Features
- [ ] IOC/FOK order type implementation
- [ ] Stop and stop-limit orders
- [ ] Cross-trading prevention
- [ ] Position risk management

### Performance
- [ ] Memory pool allocation
- [ ] SIMD optimizations for matching logic
- [ ] Zero-copy message handling
- [ ] Latency monitoring and metrics

## 📋 Project Structure

```
.
├── src/
│   ├── MatchingEngine.{hpp,cpp}    # Main engine logic
│   ├── OrderBook.{hpp,cpp}         # Order book implementation
│   ├── Order.{hpp,cpp}             # Order representation
│   ├── Trade.hpp                   # Trade execution records
│   └── Side.hpp                    # Buy/Sell enumeration
├── test/
│   ├── test_order.cpp              # Order unit tests
│   ├── test_orderbook.cpp          # OrderBook unit tests
│   ├── test_matchingengine.cpp     # Engine unit tests
│   └── test_integration.cpp        # End-to-end tests
├── Makefile                        # Build configuration
└── README.md                       # This file
```

## 🎯 Key Learnings & Challenges

### Technical Challenges Solved
1. **Memory Management**: Transitioned from raw pointers to smart pointers for safety
2. **Algorithm Optimization**: Replaced priority queues with ordered maps for better performance
3. **Order Amendment Logic**: Implemented cancel-and-replace pattern for consistency

### Design Patterns Applied
- **RAII**: Resource management through smart pointers
- **Factory Pattern**: Centralized order creation
- **Observer Pattern**: Trade generation on matches

## 💼 Skills Demonstrated

**C++ Expertise**: Modern C++20, STL containers, smart pointers, RAII <br>
**Data Structures**: Maps, deques, hash maps for optimal performance <br>
**Algorithm Design**: Price-time priority matching, O(log n) operations <br>
**Memory Management**: Leak-free code with automatic cleanup <br>
**Testing**: Comprehensive unit and integration test coverage <br>
**Build Systems**: Make-based compilation and testing workflow <br>

---

*Developed as a demonstration of low-latency financial systems programming capabilities for quantitative development roles.*
