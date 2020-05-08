#include "generate.hpp"
#include "historic.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <cmath>
#include <iomanip>


int main() {


    generate genObject[4];
    std::string tempFile;

    //this loop handles the output and function calling of the first part of the project
    for (int i = 0; i < 4; ++i) {
        std::cout<<"Simulation: "<<i + 1<<std::endl;
        std::cout<<"---------------------------------------------------------------------------"<<std::endl;
        tempFile = "t" + std::to_string(i + 1) + ".txt";
        //respective functions are called

        genObject[i].loadFile(tempFile);
        genObject[i].printUserInfo();
        int temp1 = genObject[i].generateData();
        int temp2 = genObject[i].analyzeData();
        int temp3 = genObject[i].getItemBad();

        //various output calculations are performed
        double base = 1.00000 - (temp3 / 100.00000);
        int exponent = genObject[i].getItemSample();
        std::cout <<std::setprecision(6)<<std::fixed<<"Base = "<< base <<" Exponent = "<< exponent<<std::endl;
        double badBatch = pow(base, exponent);
        std::cout <<std::setprecision(6)<<std::fixed<<"P(failure to detect bad batch) = "<<badBatch<<std::endl;
        float temp4 =  1 - ((float)temp2 / (float)temp1);
        double percent = (1 - temp4) * 100;
        std::cout<<"Percentage of bad batches actually detected = "<<std::fixed<<std::setprecision(2)<< percent
                 <<"%"<<std::endl;
        std::cout<<"---------------------------------------------------------------------------"<<std::endl;
    }



    historic histObject;

    //setting the filename
    std::string newFileName = "readings.txt";

    // historic data analysis function calls
    histObject.loadData(newFileName);
    histObject.parser();
    histObject.splitter();
    histObject.print();
    histObject.findAnalytical();
    histObject.findSim();

    return 0;
}
