//
// Created by David Maples on 4/12/20.
//

#ifndef PROJECT4_HISTORIC_HPP
#define PROJECT4_HISTORIC_HPP
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>

class historic {
private:
    std::vector<std::string> readVec;
    std::vector<int> obs;
    std::vector<int> r1;
    std::vector<int> r2;
    int days;
    int categories;
    std::string unit;
public:
    void loadData(std::string tempFile);
    void parser();
    void splitter();
    void print();
    void findAnalytical();
    void findSim();
};


#endif //PROJECT4_HISTORIC_HPP