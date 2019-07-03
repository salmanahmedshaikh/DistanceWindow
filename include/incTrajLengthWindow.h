#include <distanceWindow.h>
#include<unordered_map>
#include "stdafx.h"


class incTrajLengthWindow : public distanceWindow
{
    public:
        incTrajLengthWindow();
        virtual ~incTrajLengthWindow();

        void insertElement(int trajectoryID, std::string timestamp, double longitude, double latitude);

    protected:


    private:

        //double mLongitude1;
        //double mLatitude1;
        std::unordered_map<int, double> trajectoryLengthMap;
        std::unordered_map<int, double>::iterator trajectoryLengthMapIt;

        void updateWindow(int trajectoryID);
};


