#pragma once
#include <distanceWindow.h>
#include "stdafx.h"


class incDistArrayWindow : public distanceWindow
{
    public:
        incDistArrayWindow();
        virtual ~incDistArrayWindow();

        void insertElement(int trajectoryID, std::string timestamp, double longitude, double latitude);

    protected:

    private:
        void updateWindow(int trajectoryID);

        std::unordered_map<int, std::list<double> > trajectoryDistanceArrayMap;
        std::unordered_map<int, std::list<double> >::iterator trajectoryDistanceArrayMapIt;
};
