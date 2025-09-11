CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./src
SRC_DIR = src
TEST_DIR = test

SRC_FILES = $(SRC_DIR)/Order.cpp \
            $(SRC_DIR)/OrderBook.cpp \
            $(SRC_DIR)/MatchingEngine.cpp \
            $(SRC_DIR)/Trade.cpp

TEST_ORDER = $(TEST_DIR)/test_order
TEST_ORDERBOOK = $(TEST_DIR)/test_orderbook
TEST_MATCHINGENGINE = $(TEST_DIR)/test_matchingengine
TEST_INTEGRATION = $(TEST_DIR)/test_integration

all: $(TEST_ORDER) $(TEST_ORDERBOOK) $(TEST_MATCHINGENGINE) $(TEST_INTEGRATION)

$(TEST_ORDER): $(TEST_DIR)/test_order.cpp $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_ORDERBOOK): $(TEST_DIR)/test_orderbook.cpp $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_MATCHINGENGINE): $(TEST_DIR)/test_matchingengine.cpp $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_INTEGRATION): $(TEST_DIR)/test_integration.cpp $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: all
	$(TEST_ORDER)
	$(TEST_ORDERBOOK)
	$(TEST_MATCHINGENGINE)
	$(TEST_INTEGRATION)

clean:
	rm -f $(TEST_ORDER) $(TEST_ORDERBOOK) $(TEST_MATCHINGENGINE)
	rm -f $(TEST_INTEGRATION)

.PHONY: all clean
