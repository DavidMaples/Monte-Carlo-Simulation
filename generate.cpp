//
// Created by David Maples on 4/12/20.
//

#include "generate.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

void generate::setUserInfo(int batches, int batchSize, int percBad, int itemBad, int itemSample) {

    //user sets the number of batches
    setBatches(batches);

    //user sets the batch size
    setBatchSize(batchSize);

    //user sets percentage of datasets containing bad chips
    setPercBad(percBad);

    //user sets the percentage of bad chips in a dataset
    setItemBad(itemBad);

    //user sets the number of items samples
    setItemSample(itemSample);

}

//prints out all user info that is set in the above function
void generate::printUserInfo(){
    std::cout << "Number of batches: " << getBatches() << std::endl;
    std::cout << "Batch size: " << getBatchSize() << std::endl;
    std::cout << "Percentage of datasets containing defective items: " << getPercBad() <<"%"<< std::endl;
    std::cout << "Percentage of defective items in a given dataset: " << getItemBad() <<"%"<< std::endl;
    std::cout << "number of items samples: " << getItemSample() << std::endl;
}

//loads in an individual file and sets the class variables using setUserInfo
void generate::loadFile(std::string fileName) {
    int batches, batchSize, percBad, itemBad, itemSample;
    this->fileName = fileName;
    std::ifstream inFile{fileName};
    if (!inFile){std::cout<<"Cannot open file."<<std::endl;}

    while (inFile>>batches>>batchSize>>percBad>>itemBad>>itemSample)
    {
        setUserInfo(batches,batchSize,percBad,itemBad,itemSample);
    }
}

// generates batches of data according to the users parameters
int generate::generateData() {
    int numBatches = getBatches();
    int percBadBatch = getPercBad();
    int percBadChip = getItemBad();
    int numSize = getBatchSize();
    int numSet = 0;
    int numBadSets = 0;

    for (int i = 0; i < numBatches; ++i) {
        std::ofstream fileName;
        std::string tempFile;
        tempFile = "ds" + std::to_string(i + 1) + ".txt";
        fileName.open(tempFile);

        int temp = rand() % 100;

        numSet++;
        if(temp < percBadBatch){
            int numBad = 0;
            numBadSets++;
            for (int j = 0; j < numSize; ++j) {
                int temp1 = rand() % 100;
                if(temp1 < percBadChip){
                    fileName << "b" << std::endl;
                    numBad++;
                }else{
                    fileName << "g" << std::endl;
                }
            }
            std::cout<<"Created bad set batch #"<<numSet
                     <<", total Bad =  "<<numBad<< " total =  "<<numSize<<" bad percent =  "<<percBad<<std::endl;
        }else{
            for (int k = 0; k < numSize; ++k) {
                fileName << "g" << std::endl;
            }
        }
    }
    std::cout<<"Number of bad sets: "<<numBadSets<<std::endl;
    std::cout<<"-----------------------------"<<std::endl;
    return numBadSets;
}

//analyzes the generated batches of data and returns a aprox number of bad batches
int generate::analyzeData() {
    int numBatches = getBatches();
    int numSize = getBatchSize();
    int numSample = getItemSample();
    int random;
    int batchNum = 0;
    int totalBatches = 0;

    std::string line;
    std::vector<std::string> lineVec;

    std::cout<<"Analyzing Data Sets:"<<std::endl;
    for (int i = 0; i < numBatches; ++i) {
        batchNum++;
        std::string tempFile = "ds" + std::to_string(i + 1) + ".txt";
        std::ifstream inFile;
        inFile.open(tempFile);
        if (!inFile){std::cout<<"Cannot open file."<<std::endl;}

        while(std::getline(inFile, line)) {
            lineVec.push_back(line);
        }

        for (int j = 0; j < numSample; ++j) {
            random = rand() % numSize;
            if(lineVec.at(j) == "b"){
                std::cout<<"Batch #"<<batchNum<<" is bad"<<std::endl;
                totalBatches++;
                break;
            }
        }
        lineVec.clear();
        inFile.close();
    }
    return totalBatches;
}

int generate::getBatches(){
    return batches;
}

void generate::setBatches(int batches){
    this->batches = batches;
}

int generate::getBatchSize(){
    return batchSize;
}

void generate::setBatchSize(int batchSize){
    this->batchSize = batchSize;
}

int generate::getPercBad() {
    return percBad;
}

void generate::setPercBad(int percBad) {
    this->percBad = percBad;
}

int generate::getItemBad() {
    return itemBad;
}

void generate::setItemBad(int itemBad) {
    this->itemBad = itemBad;
}

int generate::getItemSample() {
    return itemSample;
}

void generate::setItemSample(int itemSample) {
    this->itemSample = itemSample;
}