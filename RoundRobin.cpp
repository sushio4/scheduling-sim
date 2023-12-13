#include "RoundRobin.hpp"

RoundRobin::RoundRobin(const std::vector<int>& arrivals, const std::vector<int>& durations, int time_quant) :
    Scheduler(arrivals, durations),
    time_quant(time_quant) {

    time_to_change = time_quant;
}

void RoundRobin::next_frame() {
    auto tup = to_arrive();
    int arrive_time = std::get<0>(tup);
    
    if(queue.empty()) {
        if(time != 0) {
            done = true;
            return;
        }
        queue.push_back(*std::get<1>(tup));
        time += arrive_time;
        time_to_change += arrive_time;
        return;
    }

    auto& current = queue.front();
    int finish_time = current.duration_time - current.time_spent;

    //look for the smallest time 

    if(arrive_time < finish_time &&
       arrive_time < time_to_change) {
        //process arrives
        queue.push_back(*std::get<1>(tup));
        time += arrive_time;
        time_to_change -= arrive_time;
        current.time_spent += arrive_time;
    }
    else if(finish_time < arrive_time &&
            finish_time < time_to_change) {
        //process finishes
        queue.pop_front();
        time += finish_time;
        time_to_change = time_quant;
        current.time_spent = current.duration_time;
    }
    else {
        //we switch processes
        current.time_spent += time_to_change;
        queue.push_back(queue.front());
        queue.pop_front();
        time += time_to_change;
        time_to_change = time_quant;
    }
}