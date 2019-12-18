#pragma once
#include<tuple>
#include<list>
#include<unordered_map>
#include <queue>
#include <iostream>



#include "stdafx.h"


class distanceWindow
{
    public:
        distanceWindow();

        virtual ~distanceWindow();

        void listAllTrajectories();
        int getNumOfTrajectories();
        int getFilteredTrajectoriesCount(int trajLowerBound, int trajUpperBound);
        std::vector<int> getFilteredTrajectoryIDs(int trajLowerBound, int trajUpperBound);

        void setWindowSize(int);
        int getWindowSize(void);

        void setStalledTrajThreshold(uint64_t);
        uint64_t getStalledTrajThreshold(void);

    protected:
        int mWindowSize;
        uint64_t stalledTrajThresholdMicroSeconds;

        virtual void updateWindow(int trajectoryID) = 0;
        void insertTuple(int trajectoryID, std::string timestamp, double longitude, double latitude);
        void deleteOldestTrajectoryTuple(int trajectoryID);
        double distBetweenTwoOldestPoints(int trajectoryID);
        double distBetweenTwoNewestPoints(int trajectoryID);
        void deleteExpiredTrajectories();
        void deleteTrajectory(int trajectoryID);

        std::unordered_map<int, std::list<std::tuple<std::string,double,double> > > trajectoryMap;
        std::unordered_map<int, std::list<std::tuple<std::string,double,double> > >::iterator trajectoryMapIt;

        typedef std::pair<uint64_t, int> PQPair; // <updateTime, TrajID>

        // Priority queue is ordered w.r.t. first element of the pair, by default larger element at top, however if "greater" is used, the smaller at top
        std::priority_queue<PQPair, std::vector<PQPair>, std::greater<PQPair> > trajectoryUpdateTimePQ;
        std::unordered_map<int, uint64_t> trajectoryUpdateTimeMap;
        std::unordered_map<int, uint64_t>::iterator trajectoryUpdateTimeMapIt;

    private:

        //list<tuple<string,double,double> > trajectory;
        //list<tuple<string,double,double> >::iterator trajectoryIt;

};
