#include "stdafx.h"
#include "IO.h"
//#include "spatialDistance.h"
//#include "point.h"
#include "spatialFeatures.h"
#include <chrono>

#ifdef BASELINE
    #include "baselineWindow.h"
#elif defined ITL
    #include "incTrajLengthWindow.h"
#elif defined IDA
    #include "incDistArrayWindow.h"
#endif

#include <iostream>
#include <cmath>
#include <list>
#include <tuple>
#include <sstream>


int main()
{
    IO io;
    //std::list<std::tuple<int, Point> > objList;

    //std::list<std::tuple<std::string, Point > > allGasStations;
    //allGasStations = io.readGasStationCSVFile("/mnt/DataDrive/Data/NYC_Data/NewYork-gas-station-locations.csv");


    /*
    for (auto& gasStation : allGasStations)
    {
        // Create a point using latitude and longitude
        Point p(std::get<3>(gasStation), std::get<4>(gasStation));
        objList.push_back( make_tuple (i, p) );
        i++;
    }
    */

    std::stringstream outputText;
    std::list<Point> candidPoints;

    Point p1(40.883908, -73.856133);
    Point p2(40.809537, -73.880674);
    Point p3(40.834730, -73.917698);
    Point p4(40.793056, -73.967525);
    Point p5(40.758583, -73.973072);
    Point p6(40.769927, -73.927136);
    Point p7(40.749569, -73.869212);
    Point p8(40.723074, -73.913955);
    Point p9(40.668553, -73.932088);
    Point p10(40.659875, -73.870134);

    candidPoints.push_back(p1);
    candidPoints.push_back(p2);
    candidPoints.push_back(p3);
    candidPoints.push_back(p4);
    candidPoints.push_back(p5);
    candidPoints.push_back(p6);
    candidPoints.push_back(p7);
    candidPoints.push_back(p8);
    candidPoints.push_back(p9);
    candidPoints.push_back(p10);


    /*
    std::list<Point> allGasStations;
    allGasStations = io.readCSVFileWIndex("/mnt/DataDrive/Data/NYC_Data/NewYork-gas-station-locations.csv", 3, 4);

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 1000 * i; // in meters

        std::cout <<  "radius : " << radius << std::endl;
        outputText << "Gas stations within radius : " << radius << "\n";
        outputText << "\n****************************\n";
        std::cout <<  "**************" << std::endl;

        // Counting # objects
        std::list<std::tuple<Point, int> > numObjWithinR = sf.numObjectsWithinR(candidPoints, allGasStations, radius);
        for(auto& numObjWithinRTuple : numObjWithinR)
        {
            Point p = std::get<0>(numObjWithinRTuple);
            int counter = std::get<1>(numObjWithinRTuple);

            p.print(std::cout);
            std::cout <<  ": " << counter << std::endl;

            outputText << p.GetX() << ", " << p.GetY() << "\t" << counter <<"\n";
        }

        outputText << "\n***\n\n";
    }

    io.writeTextToFile("output/NYC_GasStation.txt", outputText.str() );
    */



    /*
    // Counting # of car parking slots
    std::list<std::tuple<Point, double> > carParksWArea;
    carParksWArea = io.readCSVFileWIndex("/mnt/DataDrive/Data/NYC_Data/NYC_ParkingLotsCentroidsFinal.csv", 7, 6, 5); // latitude, longitude, area

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 1000 * i; // in meters

        std::cout <<  "radius : " << radius << std::endl;
        outputText << "Num cars parking within radius : " << radius << "\n";
        outputText << "\n****************************\n";
        std::cout <<  "**************" << std::endl;

        std::list<std::tuple<Point, double> > nCarParkingsWithinR = sf.numCarParkingsWithinR(candidPoints, carParksWArea, radius);
        for(auto& pCarParkings : nCarParkingsWithinR)
        {
            Point p = std::get<0>(pCarParkings);
            int counter = std::get<1>(pCarParkings);

            p.print(std::cout);
            std::cout <<  ": " << counter << std::endl;

            outputText << p.GetX() << ", " << p.GetY() << "\t" << counter <<"\n";
        }

        outputText << "\n***\n\n";
    }

    io.writeTextToFile("output/NYC_GasStation.txt", outputText.str() );
    */


    /*
    // Counting # of checkins for individual point
    std::unordered_map<std::string, int> nCheckInsWRTAttribute = sf.numCheckInsWRTAttribute(p1, fourSquareCheckinsWDay, radius);
    std::unordered_map<std::string, int>::iterator nCheckInsWRTAttributeIt;
    for(nCheckInsWRTAttributeIt = nCheckInsWRTAttribute.begin(); nCheckInsWRTAttributeIt != nCheckInsWRTAttribute.end(); nCheckInsWRTAttributeIt++)
    {
        std::cout <<  nCheckInsWRTAttributeIt->first <<" : " << nCheckInsWRTAttributeIt->second << std::endl;
    }
    */


    // total number of check ins
    std::list<std::tuple<std::string, Point> > fourSquareCheckinsWDay;
    fourSquareCheckinsWDay = io.readCSVFileWGroupingAttrib("/mnt/DataDrive/Data/NYC_Data/FourSquareCheckIns/dataset_TSMC2014_NYC.csv", 4, 5, 7); // latitude, longitude, area

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 1000 * i; // in meters

        std::cout <<  "radius : " << radius << std::endl;
        outputText << "Four square check-ins within radius : " << radius << "\n";
        outputText << "\n****************************\n";
        std::cout <<  "**************" << std::endl;

        std::unordered_map< Point, std::map<std::string, int> > nCheckInsWRTAttribute = sf.numCheckInsWRTAttribute(candidPoints, fourSquareCheckinsWDay, radius);
        std::unordered_map< Point, std::map<std::string, int> >::iterator nCheckInsWRTAttributeIt;

        //for(unsigned int i = 0; i < candidPoints.size(); i++)
        //for(nCheckInsWRTAttributeIt = nCheckInsWRTAttribute.begin(); nCheckInsWRTAttributeIt != nCheckInsWRTAttribute.end(); nCheckInsWRTAttributeIt++)
        for (auto& objPoint : candidPoints)
        {
            nCheckInsWRTAttributeIt = nCheckInsWRTAttribute.find(objPoint);

            Point p = nCheckInsWRTAttributeIt -> first;
            std::map<std::string, int> nCheckIns = nCheckInsWRTAttributeIt -> second;
            std::map<std::string, int>::iterator nCheckInsIt;

            p.print(std::cout);
            outputText << p.GetX() << ", " << p.GetY() << "\n*******************\n";
            std::cout << std::endl << "*******************" << std::endl;

            int totalCheckIns = 0;
            for(nCheckInsIt = nCheckIns.begin(); nCheckInsIt != nCheckIns.end(); nCheckInsIt++)
            {
                std::cout <<  nCheckInsIt->first <<" : " << nCheckInsIt->second << std::endl;
                outputText << nCheckInsIt->first << "\t" << nCheckInsIt->second <<"\n";

                totalCheckIns+= nCheckInsIt->second;
            }
            std::cout << "totalCheckIns: " << totalCheckIns << std::endl << std::endl;

            outputText << "totalCheckIns\t" << totalCheckIns <<"\n\n";
        }

        outputText << "\n***\n\n";
    }

    io.writeTextToFile("output/NYC_GasStation.txt", outputText.str() );

    /*
    // Traffic Estimate
    std::list<std::tuple<Point, double> > trafficEstimate;
    trafficEstimate = io.readCSVFileWIndex("/mnt/DataDrive/Data/NYC_Data/NYC_Traffic_Estimate/travel_times_2013_joined/2013_December/DecLastWeekTravelEstimates.csv", 4, 3, 2); // latitude, longitude, area

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 1000 * i; // in meters

        std::cout <<  "radius : " << radius << std::endl;
        outputText << "Traffic Estimate within radius : " << radius << "\n";
        outputText << "\n****************************\n";
        std::cout <<  "**************" << std::endl;

        std::list<std::tuple<Point, double> > trafficEstimateWithinR = sf.trafficEstimateWithinR(candidPoints, trafficEstimate, radius);
        for(auto& trafficEstimateObj : trafficEstimateWithinR)
        {
            Point p = std::get<0>(trafficEstimateObj);
            double avgTraffic = std::get<1>(trafficEstimateObj);

            p.print(std::cout);
            std::cout <<  ": " << avgTraffic << std::endl;
            outputText << p.GetX() << ", " << p.GetY() << "\t" << avgTraffic <<"\n";
        }

        outputText << "\n***\n\n";
    }

    io.writeTextToFile("output/NYC_GasStation.txt", outputText.str() );
    */


    // Distance Window Related
    /*
    int windowSize = 1000; // 1000,2000,3000,4000,5000
    IO io;
    spatialDistance sd;

    #ifdef BASELINE
        std::cout << "Baseline" << std::endl;
        baselineWindow bw;
        bw.setWindowSize(windowSize);
    #elif defined ITL
        std::cout << "ITL" << std::endl;
        incTrajLengthWindow itlw;
        itlw.setWindowSize(windowSize);
    #elif defined IDA
        std::cout << "IDA" << std::endl;
        incDistArrayWindow idaw;
        idaw.setWindowSize(windowSize);
    #endif

    // reading data
    std::list<std::tuple<int, std::string, double, double> > allTrajectories;
    allTrajectories = io.readCSVFile("/mnt/DataDrive/Data/MicrosoftGeolifeTrajectories/TrajLengthDivision/combinedTrajectories_all/MediumLength.csv");

    auto start = std::chrono::steady_clock::now();
    for (auto& trajTuple : allTrajectories)
    {
        //std::cout << std::get<0>(trajTuple) << ", " << std::get<1>(trajTuple) << ", " << std::get<2>(trajTuple) << ", " << std::get<3>(trajTuple) << std::endl;
        #ifdef BASELINE
            bw.insertElement(std::get<0>(trajTuple), std::get<1>(trajTuple), std::get<2>(trajTuple), std::get<3>(trajTuple));
        #elif defined ITL
            itlw.insertElement(std::get<0>(trajTuple), std::get<1>(trajTuple), std::get<2>(trajTuple), std::get<3>(trajTuple));
        #elif defined IDA
            idaw.insertElement(std::get<0>(trajTuple), std::get<1>(trajTuple), std::get<2>(trajTuple), std::get<3>(trajTuple));
        #endif
    }
    auto end = std::chrono::steady_clock::now();
    // Store the time difference between start and end
    auto diff = end - start;

    //std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    //std::cout << std::chrono::duration <double, std::nano> (diff).count() << " ns" << std::endl;

    std::stringstream outputText;
    int numOfTrajectories;

    outputText << "\n***\n";

    #ifdef BASELINE
        outputText << "Approach\tBaseline\n";
        numOfTrajectories = bw.getNumOfTrajectories();
    #elif defined ITL
        outputText << "Approach\tITL\n";
        numOfTrajectories = itlw.getNumOfTrajectories();
    #elif defined IDA
        outputText << "Approach\tIDA\n";
        numOfTrajectories = idaw.getNumOfTrajectories();
    #endif

    #ifdef HAVERSINE
        outputText << "Dist.Function\tHAVERSINE\n";
    #elif defined EQUIRECTANGULAR
        outputText << "Dist.Function\tEQUIRECTANGULAR\n";
    #elif defined SPHERICALLAWOFCOSINES
        outputText << "Dist.Function\tSPHERICALLAWOFCOSINES\n";
    #endif

    outputText << "Window size\t" << windowSize;
    outputText << "\nNumOfTrajectories\t" << numOfTrajectories;
    outputText << "\nNumDistanceComputations\t" << sd.getNumDistanceComputations();
    outputText << "\nExecution time (ms)\t" << std::chrono::duration <double, std::milli> (diff).count();

    io.writeTextToFile("output/output.txt", outputText.str() );
    */


    /*
    for(allTrajectoriesIt = allTrajectories.begin(); allTrajectoriesIt != allTrajectories.end(); allTrajectoriesIt++)
    {
        std::cout << "(" << std::get<0>(allTrajectoriesIt*) << ", " << std::get<1>(allTrajectoriesIt*) << ", " << std::get<2>(allTrajectoriesIt*) << ")" << endl;
    }
    */

	return 0;
}
