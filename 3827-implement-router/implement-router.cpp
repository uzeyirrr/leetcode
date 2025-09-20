#include <vector>
#include <unordered_set>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

class Router {
private:
    int memoryLimit;
    deque<vector<int>> packetQueue;  // For FIFO forwarding (using deque for efficiency)
    unordered_set<string> packetSet; // For duplicate detection
    
    // For efficient range queries: destination -> vector of timestamps (kept sorted)
    unordered_map<int, vector<int>> destinationTimestamps;
    
    // Helper function to create a unique key for packet identification
    string createPacketKey(int source, int destination, int timestamp) {
        return to_string(source) + "," + to_string(destination) + "," + to_string(timestamp);
    }
    
    void addToDestinationMap(int destination, int timestamp) {
        auto& timestamps = destinationTimestamps[destination];
        // Since timestamps come in increasing order, we can just push_back
        timestamps.push_back(timestamp);
    }
    
    void removeFromDestinationMap(int destination, int timestamp) {
        auto& timestamps = destinationTimestamps[destination];
        // Find and remove the timestamp
        auto it = find(timestamps.begin(), timestamps.end(), timestamp);
        if (it != timestamps.end()) {
            timestamps.erase(it);
            if (timestamps.empty()) {
                destinationTimestamps.erase(destination);
            }
        }
    }
    
public:
    Router(int memoryLimit) : memoryLimit(memoryLimit) {}
    
    bool addPacket(int source, int destination, int timestamp) {
        string key = createPacketKey(source, destination, timestamp);
        
        // Check for duplicate
        if (packetSet.count(key)) {
            return false;
        }
        
        // If we're at capacity, remove oldest packet
        if (packetQueue.size() >= memoryLimit) {
            vector<int> oldestPacket = packetQueue.front();
            packetQueue.pop_front();
            
            // Remove from set
            string oldestKey = createPacketKey(oldestPacket[0], oldestPacket[1], oldestPacket[2]);
            packetSet.erase(oldestKey);
            
            // Remove from destination map
            removeFromDestinationMap(oldestPacket[1], oldestPacket[2]);
        }
        
        // Add new packet
        vector<int> newPacket = {source, destination, timestamp};
        packetQueue.push_back(newPacket);
        packetSet.insert(key);
        addToDestinationMap(destination, timestamp);
        
        return true;
    }
    
    vector<int> forwardPacket() {
        if (packetQueue.empty()) {
            return {};
        }
        
        vector<int> packet = packetQueue.front();
        packetQueue.pop_front();
        
        // Remove from set
        string key = createPacketKey(packet[0], packet[1], packet[2]);
        packetSet.erase(key);
        
        // Remove from destination map
        removeFromDestinationMap(packet[1], packet[2]);
        
        return packet;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        if (destinationTimestamps.find(destination) == destinationTimestamps.end()) {
            return 0;
        }
        
        const auto& timestamps = destinationTimestamps[destination];
        
        // Use binary search to find the range
        auto start = lower_bound(timestamps.begin(), timestamps.end(), startTime);
        auto end = upper_bound(timestamps.begin(), timestamps.end(), endTime);
        
        return end - start;
    }
};