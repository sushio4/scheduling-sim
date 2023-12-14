#include "RoundRobin.hpp"

RoundRobin::RoundRobin(const std::vector<int>& arrivals, const std::vector<int>& durations, int time_quant) :
    Scheduler(arrivals, durations),
    time_quant(time_quant) {

    time_to_change = time_quant;
}

SchedulerEvent RoundRobin::next_frame() {
    auto tup = to_arrive();
    int arrive_time = std::get<0>(tup);
    
    if(queue.empty() && time == 0) {
        queue.push_back(*std::get<1>(tup));
        time += arrive_time;
        time_to_change += arrive_time;
        return {EventType::add_process, (*std::get<1>(tup)).id, 0};
    }

    auto& current = queue.front();
    int finish_time = current.duration_time - current.time_spent;

    //look for the smallest time 
    auto result = SchedulerEvent{EventType::none, 0};

    if(arrive_time < finish_time &&
       arrive_time < time_to_change) {
        //process arrives
        result = {EventType::add_process, (*std::get<1>(tup)).id, 0};

        queue.push_back(*std::get<1>(tup));
        time += arrive_time;
        time_to_change -= arrive_time;
        current.time_spent += arrive_time;
    }
    else if(finish_time < arrive_time &&
            finish_time < time_to_change) {
        //process finishes
        result = {EventType::finish_process, queue.front().id, 0};

        queue.pop_front();
        time += finish_time;
        time_to_change = time_quant;
        current.time_spent = current.duration_time;
    }
    else {
        //we switch processes
        result = {EventType::switch_process, queue.front().id, 0};

        current.time_spent += time_to_change;
        queue.push_back(queue.front());
        queue.pop_front();
        time += time_to_change;
        time_to_change = time_quant;

        result.pid2 = queue.front().id;
    }

    if(queue.empty())
        done = true;

    return result;
}