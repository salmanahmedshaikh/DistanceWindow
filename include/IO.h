#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<tuple>
#include <unordered_map>
#include "point.h"

#include "stdafx.h"



class IO
{
    public:
        IO();
        virtual ~IO();

        // Each tuple consists of a trajectory id, timestamp, longitude, latitude
        std::list<std::tuple<int, std::string, double, double> > readCSVFile(std::string fileName);
        std::list<std::tuple<std::string, Point> > readGasStationCSVFile(std::string fileName);
        std::list<Point> readCSVFileWIndex(std::string fileName, int latitudeIndex, int longitudeIndex);
        std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>> buildTrajectoryFromFourSquareCSV(std::string fileName);
        std::list<std::tuple<Point, double> > readCSVFileWIndex(std::string fileName, int latitudeIndex, int longitudeIndex, int attribIndex);
        std::list<std::tuple<std::string, Point> > readCSVFileWGroupingAttrib(std::string fileName, int latitudeIndex, int longitudeIndex, int attribIndex);
        void filterFileViaSpecificAttribute(std::string sourceFileName, std::string destFileName, int latitudeIndex, int longitudeIndex, int attribIndex, std::string attribValue);

        bool writeTextToFile(std::string fileName, std::string text);

    protected:

    private:
        std::vector<std::string> parseCSVLine(std::string line);
};
