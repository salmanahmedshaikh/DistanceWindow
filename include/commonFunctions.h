#pragma once

#include <tuple>
#include <unordered_map>
#include <map>
#include <sstream>
#include "point.h"
#include "IO.h"
#include "stdafx.h"


class commonFunctions
{
    public:
        commonFunctions();
        virtual ~commonFunctions();

        void checkTrajectoryForVenue(std::unordered_map<int, std::unordered_map<std::string,  std::unordered_map < int, std::map< std::string, std::tuple<Point, std::string>>>>> trajectoryMap, std::string venueName, std::string outputFile);

    protected:

    private:
};


