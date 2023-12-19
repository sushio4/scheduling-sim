#include "FCFS.hpp"

FCFS::FCFS(const std::vector<int>& arrivals, const std::vector<int>& durations) :
    Scheduler(arrivals, durations) {
    name = "FCFS";
}

SchedulerEvent FCFS::next_frame() {
    auto tup = to_arrive();
    int arrive_time = std::get<0>(tup);

    if(queue.empty() && time == 0) {
        queue.push_back(*std::get<1>(tup));
        time += arrive_time;
        return {EventType::add_process, (*std::get<1>(tup)).id, 0};
    }

    auto& current = queue.front();
    int finish_time = current.duration_time - current.time_spent;

    auto result = SchedulerEvent{EventType::none, 0, 0};

    if(arrive_time <= finish_time) {
        time += arrive_time;
        queue.push_back(*std::get<1>(tup));
        result = {EventType::add_process, (*std::get<1>(tup)).id, 0};
    }
    else {
        result = {EventType::finish_process, current.id, 0};
        time += finish_time;
        queue.pop_front();
    }

    if(queue.empty())
        done = true;
    
    return result;
}