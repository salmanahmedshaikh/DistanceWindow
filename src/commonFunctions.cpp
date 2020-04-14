#include <iostream>


#include "commonFunctions.h"

commonFunctions::commonFunctions()
{
    //ctor
}

commonFunctions::~commonFunctions()
{
    //dtor
}

void commonFunctions::checkTrajectoryForVenue(std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>> trajectoryMap, std::string venueName, std::string outputFile)
{
    IO io;
    std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>>::iterator trajectoryMapIt;

    for (trajectoryMapIt = trajectoryMap.begin(); trajectoryMapIt != trajectoryMap.end(); trajectoryMapIt++)
    {
        //std::cout << trajectoryMapIt->first << std::endl;
        std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>>::iterator  trajectoryMapMonthIt;
        std::unordered_map<std::string,  std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>> trajectoryMapMonth = trajectoryMapIt->second;

        for (trajectoryMapMonthIt = trajectoryMapMonth.begin(); trajectoryMapMonthIt != trajectoryMapMonth.end(); trajectoryMapMonthIt++)
        {
            //std::cout << trajectoryMapMonthIt->first << std::endl;
            std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>>::iterator  trajectoryMapDateIt;
            std::unordered_map < int, std::unordered_map< std::string, std::tuple<Point, std::string>>> trajectoryMapDate = trajectoryMapMonthIt->second;

            for(trajectoryMapDateIt = trajectoryMapDate.begin(); trajectoryMapDateIt != trajectoryMapDate.end(); trajectoryMapDateIt++)
            {
                //std::cout << trajectoryMapDateIt->first << std::endl;
                std::unordered_map< std::string, std::tuple<Point, std::string>>::iterator  trajectoryMapTimeIt;
                std::unordered_map< std::string, std::tuple<Point, std::string>> trajectoryMapTime = trajectoryMapDateIt->second;

                //Find trajectories with size > 1
                if(trajectoryMapTime.size() > 1)
                {
                    //Find trajectories with venueName
                    for(trajectoryMapTimeIt = trajectoryMapTime.begin(); trajectoryMapTimeIt != trajectoryMapTime.end(); trajectoryMapTimeIt++)
                    {
                        auto trajTuple = trajectoryMapTimeIt->second;
                        if(std::get<1>(trajTuple).compare(venueName) == 0) // If venueName found in trajectory
                        {
                            std::stringstream outputText;
                            //outputText << "User ID: " << trajectoryMapIt->first << ", Month: " << trajectoryMapMonthIt->first << ", Date: " << trajectoryMapDateIt->first << "\n";
                            //std::cout << "User ID: " << trajectoryMapIt->first << ", Month: " << trajectoryMapMonthIt->first << ", Date: " << trajectoryMapDateIt->first << std::endl;

                            std::unordered_map< std::string, std::tuple<Point, std::string>>::iterator trajectoryMapTimeIt2;
                            for(trajectoryMapTimeIt2 = trajectoryMapTime.begin(); trajectoryMapTimeIt2 != trajectoryMapTime.end(); trajectoryMapTimeIt2++)
                            {
                                auto trajTuple2 = trajectoryMapTimeIt2->second;
                                //std::cout << trajectoryMapTimeIt2->first << ": " << std::get<1>(trajTuple2) << std::endl;
                                outputText << trajectoryMapTimeIt2->first << ", " << std::get<1>(trajTuple2) << "\n";
                            }
                            //std::cout << std::endl;
                            outputText << "\n";
                            //io.writeTextToFile("output/trajectoryVenueName_TKY.txt", outputText.str());
                            io.writeTextToFile(outputFile, outputText.str());
                            continue;
                        }
                    }
                }
            }

        }
    }
}



