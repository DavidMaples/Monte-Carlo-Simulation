//
// Created by David Maples on 4/12/20.
//

#ifndef PROJECT4_GENERATE_HPP
#define PROJECT4_GENERATE_HPP
#include <string>
#include <iostream>

class generate {
    private:
    int batches;
    int batchSize;
    int percBad;
    int itemBad;
    int itemSample;
    std::string fileName;

    public:

    void setUserInfo(int batches, int batchSize, int percBad, int itemBad, int itemSample);  //sets all of the user info fields
    void loadFile(std::string fileName);
    void printUserInfo();
    int generateData();
    int analyzeData();

    int getItemSample();
    void setItemSample(int itemSample);
    int getBatches();
    void setBatches(int batches);
    int getBatchSize();
    void setBatchSize(int batchSize);
    int getPercBad();
    void setPercBad(int percBad);
    int getItemBad();
    void setItemBad(int itemBad);
};


#endif //PROJECT4_GENERATE_HPP
