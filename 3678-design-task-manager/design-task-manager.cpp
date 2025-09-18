#include <bits/stdc++.h>
using namespace std;

class TaskManager {
    struct Task {
        int priority;
        int taskId;
        int userId;
    };
    
    // max-heap: higher priority first; if tie, larger taskId first
    struct Compare {
        bool operator()(const Task& a, const Task& b) const {
            if (a.priority == b.priority)
                return a.taskId < b.taskId; // larger taskId wins
            return a.priority < b.priority; // larger priority wins
        }
    };
    
    // maps taskId -> (userId, priority)
    unordered_map<int, pair<int,int>> taskMap;
    priority_queue<Task, vector<Task>, Compare> pq;

public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto& t : tasks) {
            int userId = t[0], taskId = t[1], priority = t[2];
            add(userId, taskId, priority);
        }
    }

    void add(int userId, int taskId, int priority) {
        taskMap[taskId] = {userId, priority};
        pq.push({priority, taskId, userId});
    }

    void edit(int taskId, int newPriority) {
        auto [userId, _] = taskMap[taskId];
        taskMap[taskId] = {userId, newPriority};
        pq.push({newPriority, taskId, userId}); // push new version
    }

    void rmv(int taskId) {
        taskMap.erase(taskId);
        // old versions remain in heap (lazy deletion)
    }

    int execTop() {
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            auto it = taskMap.find(top.taskId);
            if (it != taskMap.end() && it->second.second == top.priority) {
                // valid task
                int userId = it->second.first;
                taskMap.erase(it);
                return userId;
            }
        }
        return -1; // no tasks
    }
};
