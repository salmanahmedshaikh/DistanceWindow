#include "stdafx.h"
#include "IO.h"
//#include "spatialDistance.h"
//#include "point.h"
#include "spatialFeatures.h"
#include "helperClass.h"
#include "queries.h"
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
#include <unistd.h>

#include <routingkit/osm_simple.h>
#include <routingkit/inverse_vector.h>
#include <routingkit/timer.h>
#include <routingkit/geo_position_to_node.h>
#include <routingkit/contraction_hierarchy.h>

using namespace RoutingKit;


int main()
{

    // Optimal Site Selection Related

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
    /*
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
    */



    /*
    // Gas Stations
    std::list<Point> allGasStations;
    allGasStations = io.readCSVFileWIndex("/mnt/DataDrive/Data/NYC_Data/NYCGasStations_Google_Filtered.csv", 1, 2);

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 500 * i; // in meters

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

    io.writeTextToFile("output/NYC_GasStations_Milos.txt", outputText.str() );
    */

    /*
    // # of car parking slots
    std::list<std::tuple<Point, double> > carParksWArea;
    carParksWArea = io.readCSVFileWIndex("/mnt/DataDrive/Data/NYC_Data/NYC_ParkingLotsCentroidsFinal.csv", 7, 6, 5); // latitude, longitude, area

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 500 * i; // in meters

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
    io.writeTextToFile("output/NYC_GasStations_Milos.txt", outputText.str() );
    */


    // Counting # of checkins for individual point
    //std::unordered_map<std::string, int> nCheckInsWRTAttribute = sf.numCheckInsWRTAttribute(p1, fourSquareCheckinsWDay, radius);
    //std::unordered_map<std::string, int>::iterator nCheckInsWRTAttributeIt;
    //for(nCheckInsWRTAttributeIt = nCheckInsWRTAttribute.begin(); nCheckInsWRTAttributeIt != nCheckInsWRTAttribute.end(); nCheckInsWRTAttributeIt++)
    //{
    //    std::cout <<  nCheckInsWRTAttributeIt->first <<" : " << nCheckInsWRTAttributeIt->second << std::endl;
    //}


    //Separating Gas Station / Garage data from four square check ins
    //std::list<std::tuple<std::string, Point> > fourSquareCheckinsAtGasStation;
    //std::string sourceFile = "/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/FourSquareCheckIns/dataset_TSMC2014_NYC.csv";
    //std::string destFile = "/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/FourSquareCheckIns/gasStation.csv";
    //io.filterFileViaSpecificAttribute(sourceFile, destFile, 4, 5, 3, "Gas Station / Garage"); // latitude, longitude, area


    /*
    // four square check ins
    std::list<std::tuple<std::string, Point> > fourSquareCheckinsWDay;
    //fourSquareCheckinsWDay = io.readCSVFileWGroupingAttrib("/mnt/DataDrive/Data/NYC_Data/FourSquareCheckIns/dataset_TSMC2014_NYC.csv", 4, 5, 7); // latitude, longitude, area
    fourSquareCheckinsWDay = io.readCSVFileWGroupingAttrib("/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/FourSquareCheckIns/dataset_TSMC2014_NYC.csv", 4, 5, 7); // latitude, longitude, area

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 50 * i; // in meters

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
            //outputText << p.GetX() << ", " << p.GetY() << "\n*******************\n";
            std::cout << std::endl << "*******************" << std::endl;

            int totalCheckIns = 0;
            for(nCheckInsIt = nCheckIns.begin(); nCheckInsIt != nCheckIns.end(); nCheckInsIt++)
            {
                // Day wise check-in output
                //std::cout <<  nCheckInsIt->first <<" : " << nCheckInsIt->second << std::endl;
                //outputText << nCheckInsIt->first << "\t" << nCheckInsIt->second <<"\n";

                totalCheckIns+= nCheckInsIt->second;
            }
            std::cout << "totalCheckIns: " << totalCheckIns << std::endl << std::endl;

            outputText << p.GetX() << ", " << p.GetY() << "\t" << totalCheckIns <<"\n";
            //outputText << "totalCheckIns\t" << totalCheckIns <<"\n\n";
        }

        outputText << "\n***\n\n";
    }

    io.writeTextToFile("output/NYC_GasStations_Milos.txt", outputText.str() );
    */

    // Traffic Estimate
    /*
    std::list<std::tuple<Point, double> > trafficEstimate;
    trafficEstimate = io.readCSVFileWIndex("/mnt/DataDrive/Data/NYC_Data/NYC_Traffic_Estimate/travel_times_2013_joined/2013_December/DecLastWeekTravelEstimates.csv", 4, 3, 2); // latitude, longitude, area

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 500 * i; // in meters

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
    io.writeTextToFile("output/NYC_GasStations_Milos.txt", outputText.str() );
    */




    // Preparing Road Distance Environment (Index)
    // Load a car routing graph from OpenStreetMap-based data
	auto graph = simple_load_osm_car_routing_graph_from_pbf("data/NYC.osm.pbf");
	auto tail = invert_inverse_vector(graph.first_out);

	// Build the shortest path index
	// Use "graph.travel_time" for indexing w.r.t. travel time and "graph.geo_distance" for indexing w.r.t. road distance
	/*
	auto ch = ContractionHierarchy::build(
		graph.node_count(),
		tail, graph.head,
		graph.travel_time
	);
	*/

	auto ch = ContractionHierarchy::build(
		graph.node_count(),
		tail, graph.head,
		graph.geo_distance
	);

	// Build the index to quickly map latitudes and longitudes
	GeoPositionToNode map_geo_position(graph.latitude, graph.longitude);

	// Besides the CH itself we need a query object.
	ContractionHierarchyQuery ch_query(ch);

    //std::cout << roadDist.getDistance(map_geo_position, ch_query, 40.87105, -73.86361, 40.87332, -73.88967) << std::endl;

    std::list<Point> allGasStations;
    allGasStations = io.readCSVFileWIndex("/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/NYCGasStations_Google_Filtered.csv", 1, 2);

    // Gas Stations evaluation using road distance
    /*
    std::cout << "allGasStations.size: " << allGasStations.size() << std::endl;

    for(int i = 1; i <= 5; i++)
    {
        spatialFeatures sf;
        int radius = 500 * i; // in meters

        std::cout <<  "radius : " << radius << std::endl;
        outputText << "Gas stations within radius : " << radius << "\n";
        outputText << "\n****************************\n";
        std::cout <<  "**************" << std::endl;

        // Counting # objects
        std::list<std::tuple<Point, int> > numObjWithinR = sf.numObjectsWithinR(map_geo_position, ch_query, allGasStations, allGasStations, radius);
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

    io.writeTextToFile("output/NYC_GasStations_Google_RoadDistance.txt", outputText.str() );
    */

    // # of car parking slots using road distance

    std::list<std::tuple<Point, double> > carParksWArea;
    carParksWArea = io.readCSVFileWIndex("/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/NYC_ParkingLotsCentroidsFinal.csv", 7, 6, 5); // latitude, longitude, area

    spatialFeatures sf;
    int radius = 1500; // in meters

    std::cout <<  "radius : " << radius << std::endl;
    outputText << "Num cars parking within radius : " << radius << "\n";
    outputText << "\n****************************\n";
    std::cout <<  "**************" << std::endl;

    std::list<std::tuple<Point, double> > nCarParkingsWithinR = sf.numCarParkingsWithinR(map_geo_position, ch_query, allGasStations, carParksWArea, radius);
    for(auto& pCarParkings : nCarParkingsWithinR)
    {
        Point p = std::get<0>(pCarParkings);
        int counter = std::get<1>(pCarParkings);

        p.print(std::cout);
        std::cout <<  ": " << counter << std::endl;

        outputText << p.GetX() << ", " << p.GetY() << "\t" << counter <<"\n";
    }

    outputText << "\n***\n\n";
    io.writeTextToFile("output/NYC_GasStations_Google_RoadDistance.txt", outputText.str() );



    // Traffic Estimate using road distance
    std::list<std::tuple<Point, double> > trafficEstimate;
    //trafficEstimate = io.readCSVFileWIndex("/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/NYC_Traffic_Estimate/travel_times_2013_joined/2013_December/NYCTrafficEstimate20131218.csv", 4, 3, 2); // latitude, longitude, area
    trafficEstimate = io.readCSVFileWIndex("/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/NYC_Traffic_Estimate/travel_times_2013_joined/2013_December/NYCTrafficEstimate20131218_Aggregated.csv", 1, 0, 2); // latitude, longitude, area

    //spatialFeatures sf;
    radius = 1000; // in meters

    std::cout <<  "radius : " << radius << std::endl;
    outputText << "Traffic Estimate within radius : " << radius << "\n";
    outputText << "\n****************************\n";
    std::cout <<  "**************" << std::endl;

    std::list<std::tuple<Point, double> > trafficEstimateWithinR = sf.trafficEstimateWithinR(map_geo_position, ch_query, allGasStations, trafficEstimate, radius);
    for(auto& trafficEstimateObj : trafficEstimateWithinR)
    {
        Point p = std::get<0>(trafficEstimateObj);
        double avgTraffic = std::get<1>(trafficEstimateObj);

        p.print(std::cout);
        std::cout <<  ": " << avgTraffic << std::endl;
        outputText << p.GetX() << ", " << p.GetY() << "\t" << avgTraffic <<"\n";
    }

    outputText << "\n***\n\n";

    io.writeTextToFile("output/NYC_GasStations_Google_RoadDistance.txt", outputText.str() );


    /*
    // four square check ins using road distance
    std::list<std::tuple<std::string, Point> > fourSquareCheckinsWDay;
    fourSquareCheckinsWDay = io.readCSVFileWGroupingAttrib("/media/salman/DATA/Datasets/2D_Spatial/NYC_Data/FourSquareCheckIns/dataset_TSMC2014_NYC.csv", 4, 5, 7); // latitude, longitude

    spatialFeatures sf;
    int radius = 500; // in meters

    std::cout <<  "radius : " << radius << std::endl;
    outputText << "Four square check-ins within radius : " << radius << "\n";
    outputText << "\n****************************\n";
    std::cout <<  "**************" << std::endl;

    std::unordered_map< Point, std::map<std::string, int> > nCheckInsWRTAttribute = sf.numCheckInsWRTAttribute(map_geo_position, ch_query, allGasStations, fourSquareCheckinsWDay, radius);
    std::unordered_map< Point, std::map<std::string, int> >::iterator nCheckInsWRTAttributeIt;

    //for(unsigned int i = 0; i < candidPoints.size(); i++)
    //for(nCheckInsWRTAttributeIt = nCheckInsWRTAttribute.begin(); nCheckInsWRTAttributeIt != nCheckInsWRTAttribute.end(); nCheckInsWRTAttributeIt++)
    for (auto& objPoint : allGasStations)
    {
        nCheckInsWRTAttributeIt = nCheckInsWRTAttribute.find(objPoint);

        Point p = nCheckInsWRTAttributeIt -> first;
        std::map<std::string, int> nCheckIns = nCheckInsWRTAttributeIt -> second;
        std::map<std::string, int>::iterator nCheckInsIt;

        //p.print(std::cout);
        //outputText << p.GetX() << ", " << p.GetY() << "\n*******************\n";
        //std::cout << std::endl << "*******************" << std::endl;

        int totalCheckIns = 0;
        for(nCheckInsIt = nCheckIns.begin(); nCheckInsIt != nCheckIns.end(); nCheckInsIt++)
        {
            // Day wise check-in output
            //std::cout <<  nCheckInsIt->first <<" : " << nCheckInsIt->second << std::endl;
            //outputText << nCheckInsIt->first << "\t" << nCheckInsIt->second <<"\n";

            totalCheckIns+= nCheckInsIt->second;
        }
        //std::cout << "totalCheckIns: " << totalCheckIns << std::endl << std::endl;

        outputText << p.GetX() << ", " << p.GetY() << "\t" << totalCheckIns <<"\n";
        //outputText << "totalCheckIns\t" << totalCheckIns <<"\n\n";
    }

    outputText << "\n***\n\n";
    io.writeTextToFile("output/NYC_GasStations_Google_RoadDistance.txt", outputText.str() );
    */





















    // Distance Window Related (BigMM and Journal)
    /*
    uint64_t stalledTrajThreshold = 1000000; // stalledTrajThreshold duration in microseconds: 1 second = 1000000 microsecond
    uint64_t slidingStep = 1000000; // slidingStep in microseconds: 1 second = 1000000 microsecond
    // reading data
    std::list<std::tuple<int, std::string, double, double> > allTrajectories;
    IO io;

    std::vector<std::string> fileNameVector;

    fileNameVector.push_back("ShortestLength.csv");
    fileNameVector.push_back("ShortLength.csv");
    fileNameVector.push_back("MediumLength.csv");
    fileNameVector.push_back("LongLength.csv");
    fileNameVector.push_back("LongestLength.csv");

    fileNameVector.push_back("3556Traj.csv");
    fileNameVector.push_back("7113Traj.csv");
    fileNameVector.push_back("10670Traj.csv");
    fileNameVector.push_back("14227Traj.csv");
    fileNameVector.push_back("17784Traj.csv");

    for (std::string fileName : fileNameVector)
    {
        allTrajectories = io.readCSVFile("/media/salman/DATA/Datasets/2D_Spatial/MicrosoftGeolifeTrajectories/TrajLengthDivision/combinedTrajectories_all/" + fileName);
        std::cout << "Finished reading file" << std::endl;

        std::vector<std::string> queryStrVector;

        queryStrVector.push_back("trajectoriesCount");
        queryStrVector.push_back("filteredTrajectoriesCount");
        queryStrVector.push_back("filteredTrajectoriesLength");

        for (std::string queryStr : queryStrVector)
        {
            for(int i = 1; i <= 5; i++)
            {
                int windowSize = 500 * i; // 1000,2000,3000,4000,5000 - in meters
                spatialDistance sd;

                #ifdef BASELINE
                    std::cout << "Baseline" << std::endl;
                    baselineWindow bw;
                    bw.setWindowSize(windowSize);
                    bw.setStalledTrajThreshold(stalledTrajThreshold);
                #elif defined ITL
                    std::cout << "ITL" << std::endl;
                    incTrajLengthWindow itlw;
                    itlw.setWindowSize(windowSize);
                    itlw.setStalledTrajThreshold(stalledTrajThreshold);
                #elif defined IDA
                    std::cout << "IDA" << std::endl;
                    incDistArrayWindow idaw;
                    idaw.setWindowSize(windowSize);
                    idaw.setStalledTrajThreshold(stalledTrajThreshold);
                #endif


                //queries q;
                int filterLowerBound = 500;
                int filterUpperBound = 5000;
                uint64_t slideStepStartTime = helperClass::timeSinceEpochMicrosec();
                auto start = std::chrono::steady_clock::now();
                for (auto& trajTuple : allTrajectories)
                {
                    uint64_t currentTime = helperClass::timeSinceEpochMicrosec();
                    // Query is called based on window slide time
                    if( (currentTime - slideStepStartTime) > slidingStep)
                    {
                        if(queryStr == "trajectoriesCount")
                        {
                            #ifdef BASELINE
                                bw.getNumOfTrajectories();
                            #elif defined ITL
                                itlw.getNumOfTrajectories();
                            #elif defined IDA
                                idaw.getNumOfTrajectories();
                            #endif
                        }
                        else if(queryStr == "filteredTrajectoriesCount")
                        {
                            #ifdef BASELINE
                                bw.getFilteredTrajectoriesCount(filterLowerBound, filterUpperBound);
                            #elif defined ITL
                                itlw.getFilteredTrajectoriesCount(filterLowerBound, filterUpperBound);
                            #elif defined IDA
                                idaw.getFilteredTrajectoriesCount(filterLowerBound, filterUpperBound);
                            #endif
                        }
                        else if(queryStr == "filteredTrajectoriesLength")
                        {
                            std::vector<int> filteredTrajectoryIDs;

                            #ifdef BASELINE
                                filteredTrajectoryIDs = bw.getFilteredTrajectoryIDs(filterLowerBound, filterUpperBound);
                                for (int trajID : filteredTrajectoryIDs)
                                    bw.getTrajectoryLength(trajID);
                            #elif defined ITL
                                filteredTrajectoryIDs = itlw.getFilteredTrajectoryIDs(filterLowerBound, filterUpperBound);
                                for (int trajID : filteredTrajectoryIDs)
                                    itlw.getTrajectoryLength(trajID);
                            #elif defined IDA
                                filteredTrajectoryIDs = idaw.getFilteredTrajectoryIDs(filterLowerBound, filterUpperBound);
                                for (int trajID : filteredTrajectoryIDs)
                                    idaw.getTrajectoryLength(trajID);
                            #endif
                        }
                        else
                        {
                            std::cout << "Invalid Query" << std::endl;
                            exit(0);
                        }

                        slideStepStartTime = currentTime;

                        //q.trajectoriesCount();
                        //q.filteredTrajectoriesCount(trajLowerBound, trajUpperBound);
                        //q.filteredTrajectoriesLength(trajLowerBound, trajUpperBound);
                    }
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

                //outputText << "\n***\n";

                //outputText << "\n";

                #ifdef BASELINE
                    //outputText << "Approach\tBaseline\n";
                    outputText << "Approach,Baseline,";
                    numOfTrajectories = bw.getNumOfTrajectories();
                #elif defined ITL
                    //outputText << "Approach\tITL\n";
                    outputText << "Approach,ITL,";
                    numOfTrajectories = itlw.getNumOfTrajectories();
                #elif defined IDA
                    //outputText << "Approach\tIDA\n";
                    outputText << "Approach,IDA,";
                    numOfTrajectories = idaw.getNumOfTrajectories();
                #endif

                #ifdef HAVERSINE
                    //outputText << "Dist.Function\tHAVERSINE\n";
                    outputText << "Dist.Function,HAVERSINE,";
                #elif defined EQUIRECTANGULAR
                    //outputText << "Dist.Function\tEQUIRECTANGULAR\n";
                    outputText << "Dist.Function,EQUIRECTANGULAR,";
                #elif defined SPHERICALLAWOFCOSINES
                    //outputText << "Dist.Function\tSPHERICALLAWOFCOSINES\n";
                    outputText << "Dist.Function,SPHERICALLAWOFCOSINES,";
                #endif


                outputText << "\nTraj File\t" << fileName;
                outputText << "\nQuery\t" << queryStr;
                outputText << "\nFilterLowerBound\t" << filterLowerBound;
                outputText << "\nFilterUpperBound\t" << filterUpperBound;
                outputText << "\nWindow size\t" << windowSize;
                outputText << "\nSlidingStep(micro seconds)\t" << slidingStep;
                outputText << "\nStalledTrajThreshold\t" << stalledTrajThreshold;
                outputText << "\nNumOfTrajectories\t" << numOfTrajectories;
                outputText << "\nNumDistanceComputations\t" << sd.getNumDistanceComputations();
                outputText << "\nExecution time (ms)\t" << std::chrono::duration <double, std::milli> (diff).count();


                outputText << "Traj File," << fileName;
                outputText << ",Query," << queryStr;
                outputText << ",FilterLowerBound," << filterLowerBound;
                outputText << ",FilterUpperBound," << filterUpperBound;
                outputText << ",Window size," << windowSize;
                outputText << ",SlidingStep(micro seconds)," << slidingStep;
                outputText << ",StalledTrajThreshold," << stalledTrajThreshold;
                outputText << ",NumOfTrajectories," << numOfTrajectories;
                outputText << ",NumDistanceComputations," << sd.getNumDistanceComputations();
                outputText << ",Execution time (ms)," << std::chrono::duration <double, std::milli> (diff).count();

                io.writeTextToFile("output/output_Baseline.csv", outputText.str() );

            }
        }
    }
    */

    /*
    for(allTrajectoriesIt = allTrajectories.begin(); allTrajectoriesIt != allTrajectories.end(); allTrajectoriesIt++)
    {
        std::cout << "(" << std::get<0>(allTrajectoriesIt*) << ", " << std::get<1>(allTrajectoriesIt*) << ", " << std::get<2>(allTrajectoriesIt*) << ")" << endl;
    }
    */

	return 0;
}
