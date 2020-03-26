#include "IO.h"
#include<boost/tokenizer.hpp>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>



IO::IO()
{
    //ctor
}

IO::~IO()
{
    //dtor
}

std::list<std::tuple<int, std::string, double, double> > IO::readCSVFile(std::string fileName)
{
    std::string line;
    std::ifstream dataFile(fileName);
    std::list<std::tuple<int, std::string, double, double> > allTrajectories;

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine
            allTrajectories.push_back( make_tuple (atoi(vec[7].c_str()), vec[4], std::atof(vec[1].c_str()), std::atof(vec[0].c_str()) ) );
        }
    }
    dataFile.close();

  return allTrajectories;
}

std::list<Point> IO::readCSVFileWIndex(std::string fileName, int latitudeIndex, int longitudeIndex)
{
    std::string line;
    std::ifstream dataFile(fileName);
    std::list<Point> allData;

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine
            Point p( std::atof(vec[latitudeIndex].c_str()), std::atof(vec[longitudeIndex].c_str()) );
            allData.push_back(p);
        }
    }
    dataFile.close();

  return allData;
}


std::list<std::tuple<Point, double> > IO::readCSVFileWIndex(std::string fileName, int latitudeIndex, int longitudeIndex, int attribIndex)
{
    std::string line;
    std::ifstream dataFile(fileName);
    std::list<std::tuple<Point, double> > allData;

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine
            Point p( std::atof(vec[latitudeIndex].c_str()), std::atof(vec[longitudeIndex].c_str()) );
            double attrib = std::atof(vec[attribIndex].c_str());
            allData.push_back( std::make_tuple (p, attrib) );
        }
    }
    dataFile.close();

  return allData;
}


void IO::filterFileViaSpecificAttribute(std::string sourceFile, std::string destFile, int latitudeIndex, int longitudeIndex, int attribIndex, std::string attribValue)
{
    std::string line;
    std::ifstream dataFile(sourceFile);

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine

            if(vec[attribIndex].compare(attribValue) == 0 )
            {
                std::stringstream outputData;
                outputData << vec[latitudeIndex] << ", " << vec[longitudeIndex];
                writeTextToFile(destFile, outputData.str());
            }
        }
    }
    dataFile.close();
}


std::list<std::tuple<std::string, Point> > IO::readCSVFileWGroupingAttrib(std::string fileName, int latitudeIndex, int longitudeIndex, int attribIndex)
{
    std::string line;
    std::ifstream dataFile(fileName);
    std::list<std::tuple<std::string, Point> > allData;

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine
            Point p( std::atof(vec[latitudeIndex].c_str()), std::atof(vec[longitudeIndex].c_str()) );
            std::string attrib = vec[attribIndex].c_str();
            allData.push_back( std::make_tuple (attrib, p) );

            //p.print(std::cout);
            //std::cout << attrib << std::endl;

        }
    }
    dataFile.close();

  return allData;
}



std::list<std::tuple<std::string, Point> > IO::readGasStationCSVFile(std::string fileName)
{
    std::string line;
    std::ifstream dataFile(fileName);
    std::list<std::tuple<std::string, Point> > allData;

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine
            Point p(std::atof(vec[3].c_str()), std::atof(vec[4].c_str()));
            allData.push_back( std::make_tuple (vec[0], p) );
        }
    }
    dataFile.close();

  return allData;
}

std::vector<std::string> IO::parseCSVLine(std::string line)
{
   using namespace boost;
   std::vector<std::string> vec;

   // Tokenizes the input string
   tokenizer<escaped_list_separator<char> > tk(line, escaped_list_separator<char>('\\', ',', '\"'));

   for (auto i = tk.begin();  i!=tk.end();  ++i)
   vec.push_back(*i);

   return vec;
}

bool IO::writeTextToFile(std::string fileName, std::string text)
{
    std::ofstream dataFile;
    dataFile.open (fileName, std::ofstream::out | std::ofstream::app);

    //std::ofstream dataFile(fileName);
    if (dataFile)
    {
        dataFile << text;
        dataFile << "\n";

    }
    else
    {
        std::cout << "Can't write to " << fileName << std::endl;
        return false;
    }

    dataFile.close();
    return true;
}
