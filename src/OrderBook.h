// NOTETOSELF: .h files are like interfaces
#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <string>
#include <cstdint> // For cross language we have to define the int sizes

struct Order {
    double price;
    uint32_t volume;
    uint64_t timestamp;
};

class OrderBook {
    private:
        std::string symbol;
        std::map<double, uint32_t, std::greater<double>> bids;
        std::map<double, uint32_t> asks; // map is sorted by lowest by default, neat
    public:
        // Constructor
        OrderBook(const std::string& sym);

        // Add orders
        void addBid(double price, uint32_t volume);
        void addAsk(double price, uint32_t volume);

        // Get best prices
        // NOTETOSELF: const at end is often used for getters so won't change anything
        double getBestBid() const;
        double getBestAsk() const;
        double getSpread() const;

        // debugger method
        void print() const;

};

#endif