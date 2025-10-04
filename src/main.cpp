#include <iostream>
#include "OrderBook.h"

#include <fstream> // file stream (reading)
#include <sstream> // parsing stream (parsing)
#include <string>
#include <chrono>  // high-resolution timing

// Test OrderBook works
int main() {
    // Create an order book for Apple stock
    OrderBook appleBook("AAPL");
    
    //open file with error catch 
    //NOTETOSELF return style handle error is common for I/O for C++
    std::ifstream file ("sample_market_data.csv");
    if (!file.is_open()) {
        std::cout<< "error: could not open file" << std::endl;
        return 1;
    }

    std::string line;

    //Skip header line
    std::getline(file,line);

    // Performance tracking
    int tickCount = 0;
    long long totalLatencyNs = 0;

    // Loop through each line
    while (std::getline(file,line)) {
        // Start timing for this tick
        auto startTime = std::chrono::high_resolution_clock::now();
        std::stringstream ss(line);
        std::string timestamp, symbol, side, priceStr, volumeStr;

        std::getline(ss, timestamp, ',');
        std::getline(ss, symbol, ',');
        std::getline(ss, side, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, volumeStr, ',');

        double price = std::stod(priceStr);
        uint32_t volume = std::stoul(volumeStr);

        // Check if BID or ASK and add to order book
        if (side == "BID") {
            appleBook.addBid(price, volume);
        } else if (side == "ASK") {
            appleBook.addAsk(price, volume);
        }

        // End timing for this tick
        auto endTime = std::chrono::high_resolution_clock::now();
        auto latencyNs = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

        totalLatencyNs += latencyNs;
        tickCount++;
    }

    file.close();

    // Print the final order book
    appleBook.print();

    // Print performance statistics
    std::cout << "\n========== Performance Statistics ==========" << std::endl;
    std::cout << "Total ticks processed: " << tickCount << std::endl;
    std::cout << "Total latency: " << totalLatencyNs << " ns" << std::endl;

    if (tickCount > 0) {
        double avgLatencyNs = static_cast<double>(totalLatencyNs) / tickCount;
        double avgLatencyUs = avgLatencyNs / 1000.0;

        std::cout << "Average latency per tick: " << avgLatencyNs << " ns ("
                  << avgLatencyUs << " μs)" << std::endl;

        // Check against HFT target of 50 microseconds
        if (avgLatencyUs < 50.0) {
            std::cout << "✓ UNDER 50μs TARGET! Ready for HFT!" << std::endl;
        } else {
            std::cout << "✗ Over 50μs target (needs optimization)" << std::endl;
        }
    }

    return 0;
}