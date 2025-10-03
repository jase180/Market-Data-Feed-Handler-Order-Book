#include <iostream>
#include "OrderBook.h"

// Test OrderBook works
int main() {
    // Create an order book for Apple stock
    OrderBook appleBook("AAPL");
    
    // Add some buy orders (bids)
    appleBook.addBid(150.25, 100);
    appleBook.addBid(150.24, 200);
    appleBook.addBid(150.20, 150);
    
    // Add some sell orders (asks)
    appleBook.addAsk(150.27, 100);
    appleBook.addAsk(150.28, 150);
    appleBook.addAsk(150.30, 200);

    // Print the order book
    appleBook.print();
    
    return 0;
}