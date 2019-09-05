#pragma once
#include<tuple>
#include<list>
#include<unordered_map>
#include <iostream>

#include "stdafx.h"


class distanceWindow
{
    public:
        distanceWindow();

        virtual ~distanceWindow();

        void listAllTrajectories();
        int getNumOfTrajectories();
        void setWindowSize(int);
        int getWindowSize(void);



    protected:
        int mWindowSize;
        virtual void updateWindow(int trajectoryID) = 0;
        void insertTuple(int trajectoryID, std::string timestamp, double longitude, double latitude);
        void deleteOldestTrajectoryTuple(int trajectoryID);
        double distBetweenTwoOldestPoints(int trajectoryID);
        double distBetweenTwoNewestPoints(int trajectoryID);

        std::unordered_map<int, std::list<std::tuple<std::string,double,double> > > trajectoryMap;
        std::unordered_map<int, std::list<std::tuple<std::string,double,double> > >::iterator trajectoryMapIt;

    private:

        //list<tuple<string,double,double> > trajectory;
        //list<tuple<string,double,double> >::iterator trajectoryIt;

};
