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
    char* outfname = nullptr;
    struct {
        bool roundrobin = false;
        bool fcfs = false;
        bool help = false;
        bool all = false;
    } flags;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] != '-') {
            if(fname) {
                std::cout << "Warning: specified filename multiple times! Taking only the 2nd.\n";
            }

            fname = argv[i];
            continue;
        }

        if(std::string("-a") == argv[i]) {
            i++;
            flags.all = true;
            outfname = argv[i];
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
                std::cout << "Warning: unrecognized option: " << argv[i] << '\n';
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

    if(!flags.roundrobin && !flags.fcfs &&
        !flags.all) {
        std::cout << "Error: algorithm not specified!\n";
        display_help();
        return 1;
    }

    //parse input file
    std::ifstream file(fname);
    if(!file) {
        std::cout << "Could not open file: " << fname << '\n';
        return 1;
    }

    //open output file
    std::ofstream ofile(outfname);
    if(!ofile && flags.all) {
        std::cout << "Could not open file: " << outfname << '\n';
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

    if(flags.all) {
        TextScheduler(tag<FCFS>{}, arrivals, durations).run(TextMode::summary, ofile);
        TextScheduler(tag<RoundRobin>{}, arrivals, durations, quant).run(TextMode::summary, ofile);
        return 0;
    }
    
    if(flags.fcfs)
        TextScheduler(tag<FCFS>{}, arrivals, durations).run();
    if(flags.roundrobin)
        TextScheduler(tag<RoundRobin>{}, arrivals, durations, quant).run();

    return 0;
}

void display_help() {
    std::cout << "Usage:\n"
        "schedule [options] [input file]\n\n"
        "Available options:\n"
        "-h shows this message\n"
        "-a [FILE] uses all algorithms and compares them in a FILE"
        "-r corresponds to Round-robin algorithm\n"
        "-f corresponds to FCFS algorithm\n\n"
        "Made by Maciej Suski\n";
}