#include "Util.hpp"

using namespace std;

void split_stoi(const string& str, char delim, vector<int>& parts) {
    size_t start = 0;
    for(size_t i = 0; i < str.length(); i++) {
        if(str[i] != delim) {
            continue;
        }

        auto newstr = str.substr(start, i - start);
        if(!newstr.empty())
            parts.push_back(std::stoi(newstr));
        start = i + 1;
    }
}