#include "IO.h"
#include<boost/tokenizer.hpp>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>

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
