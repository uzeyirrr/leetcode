#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>

class MovieRentingSystem {
public:
    MovieRentingSystem(int n, std::vector<std::vector<int>>& entries) {
        for (const auto& entry : entries) {
            int shop = entry[0];
            int movie = entry[1];
            int price = entry[2];
            
            // Store prices for easy lookup
            prices[{shop, movie}] = price;
            
            // Add to unrented movies, sorted by movie ID, then price
            // using a set to maintain the order (price, shop)
            unrented[movie].insert({price, shop});
        }
    }
    
    std::vector<int> search(int movie) {
        std::vector<int> result;
        if (unrented.find(movie) == unrented.end()) {
            return result;
        }
        
        auto& available_shops = unrented[movie];
        int count = 0;
        for (const auto& p : available_shops) {
            if (count >= 5) {
                break;
            }
            result.push_back(p.second);
            count++;
        }
        return result;
    }
    
    void rent(int shop, int movie) {
        int price = prices[{shop, movie}];
        
        // Remove from unrented
        unrented[movie].erase({price, shop});
        
        // Add to rented, sorted by price, then shop, then movie
        rented.insert({price, shop, movie});
    }
    
    void drop(int shop, int movie) {
        int price = prices[{shop, movie}];
        
        // Remove from rented
        rented.erase({price, shop, movie});
        
        // Add back to unrented
        unrented[movie].insert({price, shop});
    }
    
    std::vector<std::vector<int>> report() {
        std::vector<std::vector<int>> result;
        int count = 0;
        for (const auto& t : rented) {
            if (count >= 5) {
                break;
            }
            result.push_back({std::get<1>(t), std::get<2>(t)});
            count++;
        }
        return result;
    }
    
private:
    std::map<std::pair<int, int>, int> prices;
    std::map<int, std::set<std::pair<int, int>>> unrented;
    std::set<std::tuple<int, int, int>> rented;
};