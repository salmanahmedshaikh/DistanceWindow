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


std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>> IO::buildTrajectoryFromFourSquareCSV(std::string fileName)
{
    // sample data NYC Foursquare check ins
    //470,49bbd6c0f964a520f4531fe3,4bf58dd8d48988d127951735,Arts & Crafts Store,40.7198103755,-74.0025810321,-240,Tue,Apr,3,06:00:09 PM,06:00:09 PM,0,2012

    // sample data Tokyo Foursquare check ins
    //1541,4f0fd5a8e4b03856eeb6c8cb,4bf58dd8d48988d10c951735,Cosmetics Shop,35.7051010886,139.619590044,540,Tue,Apr,3,06:17:18 PM,0,2012

    std::string line;
    std::ifstream dataFile(fileName);
    std::list<std::tuple<Point, double> > allData;
    // <UserID <Month <Date, <Time, tuple<Point, venueCategory>>>>>
    std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>> trajectoryMap;
    std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>>::iterator trajectoryMapIt;
    //std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::tuple<Point, std::string, std::string>>>>::iterator trajectoryMapIt;

    if (dataFile)
    {
        while (getline(dataFile, line))
        {
            std::vector<std::string> vec = parseCSVLine(line); // Get parsed vector string via parseCSVLine
            Point p( std::atof(vec[4].c_str()), std::atof(vec[5].c_str()) );
            int userID = std::atoi(vec[0].c_str());
            int date = std::atoi(vec[9].c_str());
            std::string venueCategory = vec[3];
            std::string month = vec[8];
            std::string time = vec[10].c_str();

            //std::cout << userID << ", " << month << ", " << date << ", " << time << ", " << venueCategory << ", " << p.GetX() << ", " << p.GetY() << std::endl;

            if( (trajectoryMapIt = trajectoryMap.find(userID)) != trajectoryMap.end() ) // If a userID found
            {
                std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>::iterator  trajectoryMapMonthIt;
                std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>> trajectoryMapMonth = trajectoryMapIt->second;

                if( (trajectoryMapMonthIt = trajectoryMapMonth.find(month)) != trajectoryMapMonth.end() ) // If a month found
                {
                    std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>::iterator  trajectoryMapDateIt;
                    std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>> trajectoryMapDate = trajectoryMapMonthIt->second;

                    if( (trajectoryMapDateIt = trajectoryMapDate.find(date)) != trajectoryMapDate.end() ) // If a date found
                    {
                        std::unordered_map< std::string, std::tuple<Point, std::string>>::iterator  trajectoryMapTimeIt;
                        std::unordered_map< std::string, std::tuple<Point, std::string>> trajectoryMapTime = trajectoryMapDateIt->second;

                        auto innerTuple = std::make_tuple (p, venueCategory);
                        trajectoryMapTime[time] = innerTuple;
                        trajectoryMap[userID][month][date] = trajectoryMapTime;
                    }
                    else
                    {
                        auto innerTuple = std::make_tuple (p, venueCategory);
                        trajectoryMapDate[date][time] = innerTuple;
                        trajectoryMap[userID][month] = trajectoryMapDate;
                    }

                }
                else
                {
                    auto innerTuple = std::make_tuple (p, venueCategory);
                    trajectoryMapMonth[month][date][time] = innerTuple;
                    trajectoryMap[userID] = trajectoryMapMonth;
                }

            }
            else // If not found then insert
            {
                auto innerTuple = std::make_tuple (p, venueCategory);
                trajectoryMap[userID][month][date][time] = innerTuple;
            }


        }
    }
    dataFile.close();

  return trajectoryMap;
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
