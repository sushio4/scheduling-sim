#include "BaseScheduler.hpp"
#include <algorithm>

Scheduler::Scheduler(const std::vector<int>& arrivals, const std::vector<int>& durations) {

    if(arrivals.size() != durations.size())
        throw;

    processes.reserve(arrivals.size());

    for(int i = 0; i < arrivals.size(); i++) {
        Process proc;
        proc.arrive_time = arrivals[i];
        proc.duration_time = durations[i];
        proc.id = i;
        proc.time_spent = 0;
        proc.priority = 0;

        processes.push_back(proc);
    } 
}

int Scheduler::enqueue_process(int dt) {
    int upper = dt == 0 ?__INT_MAX__: dt;
    int min = __INT_MAX__;
    auto p = processes.end();

    for(auto i = processes.begin(); i < processes.end(); i++) {
        auto proc = *i;
        if(proc.arrive_time < upper &&
            proc.arrive_time >= time &&
            proc.arrive_time < min &&
            std::find_if(queue.begin(), queue.end(), [&proc](Process p){return p.id == proc.id;}) == queue.end()){
            
            min = proc.arrive_time;
            p = i;
        }
    }
    if(p == processes.end()) return -1;
    queue.push_back(*p);
    return min - time;
}

auto Scheduler::to_arrive() -> decltype(Scheduler::to_arrive()) {
    int min = __INT_MAX__;
    auto p = processes.end();

    for(auto i = processes.begin(); i < processes.end(); i++) {
        int parr = (*i).arrive_time - time;

        if(parr >= 0 && parr < min &&
          std::find_if(queue.begin(), 
                       queue.end(),
                       [&i](Process p){return p.id == (*i).id;}) 
                == queue.end()) {
            
            min = parr;
            p = i;
        }
    }

    if(p == processes.end()) return std::tuple{__INT_MAX__, p};

    return std::tuple{min, p};
}