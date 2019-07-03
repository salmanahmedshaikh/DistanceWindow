#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<tuple>

#include "stdafx.h"



class IO
{
    public:
        IO();
        virtual ~IO();

        // Each tuple consists of a trajectory id, timestamp, longitude, latitude
        std::list<std::tuple<int, std::string, double, double> > readCSVFile(std::string fileName);
        bool writeTextToFile(std::string fileName, std::string text);

    protected:

    private:
        std::vector<std::string> parseCSVLine(std::string line);
};
