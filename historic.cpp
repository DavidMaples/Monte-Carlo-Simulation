//
// Created by David Maples on 4/12/20.
//

#include "historic.hpp"
#include <string>



//loads data from readings.txt
void historic::loadData(std::string tempFile) {
    std::ifstream inFile;
    std::string line;

    inFile.open(tempFile);
    if (!inFile){std::cout<<"Cannot open file."<<std::endl;}

    while(std::getline(inFile, line)) {
        this->readVec.push_back(line);
    }
    inFile.close();
}

//parses various pieces of data and sets the class variables
void historic::parser(){
    std::string tempDays = readVec.at(0);
    std::string tempCategories = readVec.at(1);

    this->days = atoi(tempDays.c_str());
    this->categories = atoi(tempCategories.c_str());

    int size = readVec.size() - 1;
    this->unit = readVec.at(size);
    std::cout<<days<<std::endl;
    std::cout<<categories<<std::endl;
    std::cout<<this->unit<<std::endl;
}

//prints out information that was obtained from the readings.txt file
void historic::print(){
    std::cout<<"Simulated Days: "<< this->days<<std::endl;
    std::cout<<"Number of categories: "<< this->categories<<std::endl;
    std::cout<<"Ranges and occurrences in each range:"<<std::endl;
    for (int i = 2; i < readVec.size() - 1; ++i) {
        std::cout<<readVec.at(i)<<std::endl;
    }
    std::cout<<"Units of measure: "<<this->unit<<std::endl;

}

//splits up the information found in the readings.txt file for processing
void historic::splitter(){
    std::vector<std::string> parsed;
    std::vector<int> numsParced;

    for (int i = 2; i < readVec.size() - 1; ++i) {
        std::string temp = readVec.at(i);
        std::string const delimiters{ "- :" };

        size_t begin, pos = 0;
        while ((begin = temp.find_first_not_of(delimiters, pos)) != std::string::npos)
        {
            pos = temp.find_first_of(delimiters, begin + 1);
            parsed.push_back( temp.substr(begin, pos - begin));
        }
    }


    for (int j = 0; j < parsed.size(); ++j) {
        std::string temp = parsed.at(j);
        int tempInt = atoi(temp.c_str());
        numsParced.push_back(tempInt);
    }


    int count = 0;
    for (int k = 0; k < numsParced.size(); ++k) {
        count++;
        int tempParced = numsParced.at(k);
        if(count == 1){
            this->r1.push_back(tempParced);
        }else if(count == 2){
            this->r2.push_back(tempParced);
        }else if(count == 3){
            this->obs.push_back(tempParced);
            count = 0;
        }
    }
}

//finds the analytical values
void historic::findAnalytical(){
    double analytical;
    for (int i = 0; i < r1.size(); ++i) {
        double avg = ((r1.at(i) + r2.at(i)) / 2.00);
        float temp = obs.at(i) / 100.0;
        analytical = analytical + (temp * avg);

    }
    for (int j = 0; j < r1.size(); ++j) {
        if(r1.at(j) < analytical && r2.at(j) > analytical ){
            std::cout<<"Analytical model: "<< analytical<< ". Expected value is in the "<<
                     r1.at(j)<<"-"<<r2.at(j)<<this->unit<<" range."<<std::endl;
        }
    }
}

//finds the simulated values
void historic::findSim(){
    std::vector<int> tobs;
    std::vector<int> tavg;


    for (int i = 0; i < r1.size(); ++i) {

        int min = r1.at(i);
        int max = r2.at(i);
        int simAvg = rand() % (max-min + 1) + min;
        tavg.push_back(simAvg);

        int temObs = obs.at(i);
        int simOBs = rand() % temObs;
        tobs.push_back(simOBs);
    }

    double analytical;
    for (int j = 0; j < r1.size(); ++j) {
        float temp = tobs.at(j) / 100.0;
        analytical = analytical + (temp * tavg.at(j));

    }
    for (int k = 0; k < r1.size(); ++k) {
        if(r1.at(k) < analytical && r2.at(k) > analytical ){
            std::cout<<"Simulated model: "<< analytical<< ". Expected value is in the "<<
                     r1.at(k)<<"-"<<r2.at(k)<<this->unit<<" range."<<std::endl;
        }
    }

}