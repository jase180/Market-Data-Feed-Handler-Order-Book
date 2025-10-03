#include "OrderBook.h"
#include <iostream>

// NOTETOSELF : symbol(sym) is an initializer list, faster in C++ lower level machine code (2-3x faster)
OrderBook::OrderBook(const std::string& sym) : symbol(sym) { 

};

void OrderBook::addBid(double price, uint32_t volume) {
    bids[price] += volume;
};

void OrderBook::addAsk(double price, uint32_t volume) {
    asks[price] += volume;
};

double OrderBook::getBestBid() const {
    if (bids.empty()) {
        std::cout << "No bids exist" << std::endl;
        return 0.0;
    }
    return bids.begin() -> first;
};

double OrderBook::getBestAsk() const {
    if (asks.empty()) {
        std::cout << "No asks exist" << std::endl;
        return 0.0;
    };
    return asks.begin() -> first;
};

double OrderBook::getSpread() const {
    if (bids.empty() || (asks.empty())) {
        std::cout << "Bids or asks empty" << std::endl;
        return 0.0;
    };
    return getBestAsk() - getBestBid();
};

void OrderBook::print() const {
    std::cout << "========== " << symbol << " Order Book ==========" << std::endl;
    
    std::cout << "ASKS (Sellers):" << std::endl;
    for (const auto& [price, volume] : asks) {
        std::cout << "  $" << price << " → " << volume << " shares" << std::endl;
    }
    
    std::cout << "-------" << std::endl;
    
    std::cout << "BIDS (Buyers):" << std::endl;
    for (const auto& [price, volume] : bids) {
        std::cout << "  $" << price << " → " << volume << " shares" << std::endl;
    }
    
    std::cout << "Best Bid: $" << getBestBid() 
              << " | Best Ask: $" << getBestAsk() 
              << " | Spread: $" << getSpread() << std::endl;
};