#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Util.hpp"
#include "RoundRobin.hpp"
#include "FCFS.hpp"
#include "TextSched.hpp"

void display_help();

int main(int argc, char* argv[]) {

    char* fname = nullptr;
    struct {
        bool roundrobin = false;
        bool fcfs = false;
        bool help = false;
    } flags;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] != '-') {
            if(fname) {
                std::cout << "Warning: specified filename multiple times! Taking only the 2nd.\n";
            }

            fname = argv[i];
            continue;
        }

        for(auto p = &argv[i][1]; *p != '\0'; p++) {
            switch(*p) {
            case 'r':
                flags.roundrobin = true;
                break;
            case 'f':
                flags.fcfs = true;
                break;
            case 'h':
                flags.help = true;
                break;
            default:
                std::cout << "Warning: unrecognized option: " << *p << '\n';
            }
        }
    }   

    if(flags.help) {
        display_help();
        return 0;
    }

    if(!fname) {
        std::cout << "Error: input file not specified!\n";
        display_help();
        return 1;
    }

    if(!flags.roundrobin && !flags.fcfs) {
        std::cout << "Error: algorithm not specified!\n";
        display_help();
        return 1;
    }

    //parse input file
    std::ifstream file(fname);
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
    
    if(flags.fcfs)
        TextScheduler::run<FCFS>(arrivals, durations);
    if(flags.roundrobin)
        TextScheduler::run<RoundRobin>(arrivals, durations, quant);

    return 0;
}

void display_help() {
    std::cout << "Usage:\n"
        "schedule [options] [input file]\n\n"
        "Available options:\n"
        "-h shows this message\n"
        "-r corresponds to Round-robin algorithm\n"
        "-f corresponds to FCFS algorithm\n\n"
        "Made by Maciej Suski\n";
}