#include <vector>
#include <queue>
#include <numeric>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size();
        
        // 1. Initialize our state
        
        // Use a boolean array to track which boxes have been opened and processed.
        // Once a box is opened, its candies are collected, its keys are added,
        // and its contained boxes are added to our inventory.
        vector<bool> opened(n, false); 
        
        // Use a set to keep track of the labels of the *keys* we currently possess.
        // A key allows us to open a *closed* box.
        unordered_set<int> possessedKeys;
        
        // Use a set to keep track of the labels of the *boxes* we currently have in our inventory.
        // A box needs to be in this set AND be either initially open or have its key 
        // in 'possessedKeys' to be opened.
        unordered_set<int> possessedBoxes;

        // 2. Initialize with initialBoxes
        for (int box : initialBoxes) {
            possessedBoxes.insert(box);
        }

        // We use a queue for the BFS-like process of opening boxes.
        // Start by checking all initially available boxes.
        queue<int> q; 

        // Initial sweep to find boxes that are immediately openable
        for (int box : initialBoxes) {
            if (status[box] == 1) {
                q.push(box);
            }
        }
        
        // Variable to store the total candies collected
        long long totalCandies = 0;

        // 3. Main loop (BFS-like)
        // The process continues as long as we can open new boxes.
        while (true) {
            bool boxOpenedInThisIteration = false;
            
            // Temporary storage for boxes we couldn't open but now have the key for
            // or for boxes we found but couldn't open yet.
            unordered_set<int> nextBoxesToProcess; 
            
            // First, process all boxes in the current queue (i.e., openable boxes)
            while (!q.empty()) {
                int currentBox = q.front();
                q.pop();

                // Check if this box has already been processed/opened.
                if (opened[currentBox]) {
                    continue; 
                }

                // A box can only be pushed into the queue if it's openable and not yet opened,
                // so we can now process it.
                opened[currentBox] = true;
                boxOpenedInThisIteration = true; // Mark that we opened a box
                
                // a) Collect candies
                totalCandies += candies[currentBox];

                // b) Collect keys
                for (int key : keys[currentBox]) {
                    possessedKeys.insert(key);
                }

                // c) Collect contained boxes
                for (int containedBox : containedBoxes[currentBox]) {
                    possessedBoxes.insert(containedBox);
                }
            }

            // If we didn't open any box in the last sweep, the process is finished.
            if (!boxOpenedInThisIteration) {
                break;
            }

            // 4. Re-evaluate which boxes we can now open
            // After collecting new keys and boxes, check the inventory again.
            // We iterate over all boxes we possess that haven't been opened yet.
            for (int box : possessedBoxes) {
                if (opened[box]) {
                    continue; // Skip boxes already opened
                }
                
                // A closed box is openable if we have its key.
                bool hasKey = possessedKeys.count(box);
                
                // A box is openable if it's initially open (status[box] == 1) OR 
                // we now have the key for it.
                if (status[box] == 1 || hasKey) {
                    q.push(box); // Add it to the queue for the next processing round
                }
            }
        }

        return totalCandies;
    }
};