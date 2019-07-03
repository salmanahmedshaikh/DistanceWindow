#include "stdafx.h"
#include "IO.h"
#include "spatialDistance.h"
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
    int windowSize = 5000; // 1000,2000,3000,4000,5000
    IO io;
    spatialDistance sd;

    #ifdef BASELINE
        baselineWindow bw;
        bw.setWindowSize(windowSize);
    #elif defined ITL
        incTrajLengthWindow itlw;
        itlw.setWindowSize(windowSize);
    #elif defined IDA
        incDistArrayWindow idaw;
        idaw.setWindowSize(windowSize);
    #endif

    // reading data
    std::list<std::tuple<int, std::string, double, double> > allTrajectories;
    allTrajectories = io.readCSVFile("data/combinedTrajectories.csv");

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

    /*
    for(allTrajectoriesIt = allTrajectories.begin(); allTrajectoriesIt != allTrajectories.end(); allTrajectoriesIt++)
    {
        std::cout << "(" << std::get<0>(allTrajectoriesIt*) << ", " << std::get<1>(allTrajectoriesIt*) << ", " << std::get<2>(allTrajectoriesIt*) << ")" << endl;
    }
    */


    /*
    // Testing with sample trajectories
    for(int i=0; i<2; i++)
        for(int j=0; j<3; j++)
        {
            double val1 = (double)rand();
            double val2 = (double)rand();

            cout << "inserting " << i << "," << to_string(j) << "," << val1 << "," << val2 << endl;
            dw.insertTuple(i, to_string(j), val1, val2);
        }

    dw.listAllTrajectories();
    dw.deleteOldestTrajectoryTuple(0);
    cout << "Updated list " << endl;
    dw.listAllTrajectories();
    */

    /*
    double lat1 = 51.5007;
	double lon1 = 0.1246;
	double lat2 = 40.6892;
	double lon2 = 74.0445;


	cout << "haversine " << sd.haversine(lat1, lon1, lat2, lon2) << " meters" << endl;
	cout << "equirectangular " << sd.equirectangular(lat1, lon1, lat2, lon2) << " meters" << endl;
	cout << "sphericalLawOfCosines " << sd.sphericalLawOfCosines(lat1, lon1, lat2, lon2) << " meters" << endl;
	*/

	return 0;
}
