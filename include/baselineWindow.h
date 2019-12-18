#pragma once
#include <distanceWindow.h>
#include "stdafx.h"


class baselineWindow : public distanceWindow
{
    public:
        baselineWindow();
        virtual ~baselineWindow();
        void insertElement(int trajectoryID, std::string timestamp, double longitude, double latitude);
        double getTrajectoryLength(int trajectoryID);


    protected:

    private:
        void updateWindow(int trajectoryID);
};
