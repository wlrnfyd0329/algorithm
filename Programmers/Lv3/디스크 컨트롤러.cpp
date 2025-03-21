// 필요한 부분을 차례대로 적으면서 풀자

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Work {
    int work_time;
    int request_time;
    int id;
    
    bool operator<(const Work &other) const {
        if (work_time == other.work_time) {
            if (request_time == other.request_time) {
                return id > other.id;
            }
            return request_time > other.request_time;
        }
        return work_time > other.work_time;
    }
};

priority_queue<Work> pq;

int solution(vector<vector<int>> jobs) {
    int n = jobs.size();
    int answer = 0;
    int time = 0;
    int idx = 0;
    sort(jobs.begin(), jobs.end());
    
    while(!pq.empty() || idx < n) {
        
        if (idx < n && jobs[idx][0] <= time) {
            pq.push({jobs[idx][1], jobs[idx][0], idx });
            idx++;
            continue;
        }
        
        if (!pq.empty()) {
            auto work = pq.top();
            time += work.work_time;
            answer += time - work.request_time;
            pq.pop();
        }
        else {
            time = jobs[idx][0];
        }
    }
    
    return answer / n;
}