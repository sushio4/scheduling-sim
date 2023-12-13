#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Util.hpp"
#include "RoundRobin.hpp"
#include "TextSched.hpp"

#include <unistd.h>

void display_help();

int main(int argc, char* argv[]) {

    if(argc < 2 || argc > 3) {
        display_help();
        return 1;
    }

    auto arg1 = std::string(argv[1]);
    
    if(argc == 2 && arg1 == "-h") {
        display_help();
        return 0;
    }

    if(argc < 3) {
        display_help();
        return 1;
    }

    auto arg2 = std::string(argv[2]);

    if(argc == 3 && (arg1 != "-r" && arg1 != "-f" && arg1 != "-rf" && arg1 != "-fr")) {
        display_help();
        return 1;
    }

    //parse input file
    std::ifstream file(argv[2]);
    if(!file) {
        std::cout << "Could not open file: " << argv[2] << '\n';
        return 1;
    }

    std::vector<int> arrivals;
    std::vector<int> durations;

    std::string tempstr;

    std::getline(file, tempstr);
    split_stoi(tempstr, ' ', arrivals);
    
    std::getline(file, tempstr);
    split_stoi(tempstr, ' ', durations);

    std::getline(file, tempstr);
    std::getline(file, tempstr);
    std::getline(file, tempstr);
    int quant = std::stoi(tempstr);

    auto sim = TextScheduler(
        std::unique_ptr<Scheduler>(
            new RoundRobin(arrivals, durations, quant)
        )
    );

    while(sim.is_running()) {
        sim.draw_frame();
        sleep(1);
    }

    return 0;
}

void display_help() {
    std::cout << "Usages:\n"
        "1. schedule -h\n\n"
        "Shows this message.\n\n"
        "2. schedule [-r | -f] [input file]\n\n"
        "-r corresponds to Round-robin algorithm\n"
        "-f corresponds to FCFS algorithm\n\n"
        "Made by Maciej Suski\n";
}