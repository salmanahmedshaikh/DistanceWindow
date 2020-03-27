#include "spatialFeatures.h"

spatialFeatures::spatialFeatures()
{
    //ctor
}

spatialFeatures::~spatialFeatures()
{
    //dtor
}

bool spatialFeatures::withinDistanceR(Point p1, Point p2, double r)
{
    spatialDistance sd;
    double spatialDist = sd.sphericalLawOfCosines(p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
    //std::cout << spatialDist << std::endl;

    if (spatialDist < r)
        return true;
    else
        return false;
}


bool spatialFeatures::withinRoadDistanceR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p1, Point p2, double r)
{
    spatialDistance sd;
    double spatialDist = sd.roadDistance(map_geo_position, ch_query, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
    //std::cout << "P1: " << p1.GetX() << ", " << p1.GetY() << ", P2: " << p2.GetX() << ", " << p2.GetY() << std::endl;
    //std::cout << spatialDist << std::endl;

    if (spatialDist < r)
        return true;
    else
        return false;
}

int spatialFeatures::numObjectsWithinR(Point p, std::list<std::tuple<std::string, Point> > objSet, double r)
{
    //std::string objName;
    Point objPoint;
    int objCounter = 0;

    if(objSet.size() > 1)
    {
        for (auto& obj : objSet)
        {
            //objName = std::get<0>(obj);
            objPoint = std::get<1>(obj);

            if(withinDistanceR(p,objPoint, r))
                objCounter++;
        }
    }

    return objCounter;
}

int spatialFeatures::numObjectsWithinR(Point p, std::list<Point> objList, double r)
{
    //Point objPoint;
    int objCounter = 0;

    if(objList.size() > 1)
    {
        for (auto& objPoint : objList)
        {

            if(withinDistanceR(p,objPoint, r))
                objCounter++;
        }
    }

    return objCounter;
}

int spatialFeatures::numObjectsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<Point> objList, double r)
{
    //Point objPoint;
    int objCounter = 0;

    if(objList.size() > 1)
    {
        for (auto& objPoint : objList)
        {

            if(withinRoadDistanceR(map_geo_position, ch_query, p,objPoint, r))
                objCounter++;
        }
    }

    return objCounter;
}

std::list<std::tuple<Point, int> > spatialFeatures::numObjectsWithinR(std::list<Point> candidObjList, std::list<Point> objList, double r)
{
    //Point objPoint;
    std::list<std::tuple<Point, int> > withinRObjList;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objList.size() > 1)
            {
                int objCounter = numObjectsWithinR(objPoint, objList, r);
                withinRObjList.push_back( std::make_tuple (objPoint, objCounter) );

            }
        }
    }

    return withinRObjList;
}


std::list<std::tuple<Point, int> > spatialFeatures::numObjectsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<Point> objList, double r)
{
    //Point objPoint;
    std::list<std::tuple<Point, int> > withinRObjList;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objList.size() > 1)
            {
                int objCounter = numObjectsWithinR(map_geo_position, ch_query, objPoint, objList, r);
                withinRObjList.push_back( std::make_tuple (objPoint, objCounter) );

            }
        }
    }

    return withinRObjList;
}

int spatialFeatures::numCarParkingsWithinR(Point p, std::list<std::tuple<Point, double> > objSetWithArea, double r)
{
    //Point objPoint;
    int numCarParkings = 0;

    if(objSetWithArea.size() > 1)
    {
        for (auto& pointObj : objSetWithArea)
        {
            Point objPoint = std::get<0>(pointObj);
            double objArea = std::get<1>(pointObj);

            if(withinDistanceR(p, objPoint, r))
                numCarParkings += (objArea/(288)); // Assuming that one car require 288 sq. feet of space in a parking lot Ref. https://usa.streetsblog.org/2016/07/05/parking-takes-up-more-space-than-you-think/#targetText=A%20standard%20parking%20space%20is,feet%20(16.7%20square%20meters).
        }
    }

    return numCarParkings;
}


//Computes the total number of car parking facility nearby
std::list<std::tuple<Point, double> > spatialFeatures::numCarParkingsWithinR(std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWithArea, double r)
{
    //Point objPoint;
    std::list<std::tuple<Point, double> > withinRCarParkings;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objSetWithArea.size() > 1)
            {
                int numCarParkings = numCarParkingsWithinR(objPoint, objSetWithArea, r);
                withinRCarParkings.push_back( std::make_tuple (objPoint, numCarParkings) );

            }
        }
    }

    return withinRCarParkings;
}


int spatialFeatures::numCarParkingsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<std::tuple<Point, double> > objSetWithArea, double r)
{
    //Point objPoint;
    int numCarParkings = 0;

    if(objSetWithArea.size() > 1)
    {
        for (auto& pointObj : objSetWithArea)
        {
            Point objPoint = std::get<0>(pointObj);
            double objArea = std::get<1>(pointObj);

            if(withinRoadDistanceR(map_geo_position, ch_query, p, objPoint, r))
                numCarParkings += (objArea/(288)); // Assuming that one car require 288 sq. feet of space in a parking lot Ref. https://usa.streetsblog.org/2016/07/05/parking-takes-up-more-space-than-you-think/#targetText=A%20standard%20parking%20space%20is,feet%20(16.7%20square%20meters).
        }
    }

    return numCarParkings;
}


//Computes the total number of car parking facility nearby
std::list<std::tuple<Point, double> > spatialFeatures::numCarParkingsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWithArea, double r)
{
    //Point objPoint;
    std::list<std::tuple<Point, double> > withinRCarParkings;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objSetWithArea.size() > 1)
            {
                int numCarParkings = numCarParkingsWithinR(map_geo_position, ch_query, objPoint, objSetWithArea, r);
                withinRCarParkings.push_back( std::make_tuple (objPoint, numCarParkings) );

            }
        }
    }

    return withinRCarParkings;
}


double spatialFeatures::trafficEstimateWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r)
{
    //Point objPoint;
    double amountTraffic = 0.0;

    if(objSetWTrafficEstimate.size() > 1)
    {
        for (auto& pointObj : objSetWTrafficEstimate)
        {
            Point objPoint = std::get<0>(pointObj);
            double trafficEstimate = std::get<1>(pointObj);
            //std::cout << "outsideR" << trafficEstimate << std::endl;

            if(withinRoadDistanceR(map_geo_position, ch_query, p, objPoint, r))
            {
                amountTraffic += trafficEstimate;
                //std::cout << "withinR " << amountTraffic << std::endl;
            }
        }
    }

    //std::cout << (amountTraffic*1.0)/(7*24) <<std::endl; // Since the traffic estimate is computed for one week, this gives avg. amount of traffic per hour
    return (amountTraffic*1.0)/(24); // Since the traffic estimate is computed for one day, this gives avg. amount of traffic per hour
}


//Computes the total number of car parking facility nearby
std::list<std::tuple<Point, double> > spatialFeatures::trafficEstimateWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r)
{
    //Point objPoint;
    std::list<std::tuple<Point, double> > withinRTrafficEstimate;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objSetWTrafficEstimate.size() > 1)
            {
                double amountTraffic = trafficEstimateWithinR(map_geo_position, ch_query, objPoint, objSetWTrafficEstimate, r);
                withinRTrafficEstimate.push_back( std::make_tuple (objPoint, amountTraffic) );

            }
        }
    }

    return withinRTrafficEstimate;
}


double spatialFeatures::trafficEstimateWithinR(Point p, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r)
{
    //Point objPoint;
    double amountTraffic = 0.0;

    if(objSetWTrafficEstimate.size() > 1)
    {
        for (auto& pointObj : objSetWTrafficEstimate)
        {
            Point objPoint = std::get<0>(pointObj);
            double trafficEstimate = std::get<1>(pointObj);
            //std::cout << "outsideR" << trafficEstimate << std::endl;

            if(withinDistanceR(p, objPoint, r))
            {
                amountTraffic += trafficEstimate;
                //std::cout << "withinR " << amountTraffic << std::endl;
            }
        }
    }

    //std::cout << (amountTraffic*1.0)/(7*24) <<std::endl; // Since the traffic estimate is computed for one week, this gives avg. amount of traffic per hour
    return (amountTraffic*1.0)/(7*24); // Since the traffic estimate is computed for one week, this gives avg. amount of traffic per hour
}


//Computes the total number of car parking facility nearby
std::list<std::tuple<Point, double> > spatialFeatures::trafficEstimateWithinR(std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r)
{
    //Point objPoint;
    std::list<std::tuple<Point, double> > withinRTrafficEstimate;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objSetWTrafficEstimate.size() > 1)
            {
                double amountTraffic = trafficEstimateWithinR(objPoint, objSetWTrafficEstimate, r);
                withinRTrafficEstimate.push_back( std::make_tuple (objPoint, amountTraffic) );

            }
        }
    }

    return withinRTrafficEstimate;
}

//CheckIns w.r.t. Attribute
std::map<std::string, int> spatialFeatures::numCheckInsWRTAttribute(Point p, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r)
{
    std::map<std::string, int> groupedCounterMap;
    std::map<std::string, int>::iterator groupedCounterMapIt;

    if(objSetWithGroupingAttrib.size() > 1)
    {
        for (auto& pointObj : objSetWithGroupingAttrib)
        {
            std::string groupingAttrib = std::get<0>(pointObj);
            Point objPoint = std::get<1>(pointObj);

            if(withinDistanceR(p, objPoint, r))
            {
                groupedCounterMapIt = groupedCounterMap.find(groupingAttrib);

                //If not found, create it
                if ( groupedCounterMapIt == groupedCounterMap.end() )
                {
                    std::pair<std::string, int> groupingAttribInit (groupingAttrib, 1);
                    groupedCounterMap.insert(groupingAttribInit);
                }
                else
                {
                    // updating already existing record
                    int groupingAttribCounter = groupedCounterMapIt->second;
                    groupingAttribCounter++;

                    //Updating groupedCounterMap
                    groupedCounterMap[groupingAttrib] = groupingAttribCounter;
                }
            }
        }
    }

    return groupedCounterMap;
}

std::unordered_map< Point, std::map<std::string, int> > spatialFeatures::numCheckInsWRTAttribute(std::list<Point> candidObjList, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r)
{
    std::unordered_map< Point, std::map<std::string, int> > groupedCounterMap;
    std::unordered_map< Point, std::map<std::string, int> >::iterator groupedCounterMapIt;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objSetWithGroupingAttrib.size() > 1)
            {
                std::map<std::string, int> nCheckIns = numCheckInsWRTAttribute(objPoint, objSetWithGroupingAttrib, r);
                groupedCounterMap[objPoint] = nCheckIns;

                /*
                // TODO - Update the existing point counter
                groupedCounterMapIt = groupedCounterMap.find(objPoint);

                //If not found, create it
                if ( groupedCounterMapIt == groupedCounterMap.end() )
                {
                    std::pair< Point, std::unordered_map<std::string, int> > groupingAttribInit (objPoint, nCheckIns);
                    groupedCounterMap.insert(groupingAttribInit);
                }
                else
                {
                    // updating already existing record
                    std::unordered_map<std::string, int> groupingAttribPair = groupedCounterMapIt->second;
                    for (auto& obj : groupingAttribPair)
                    {
                        //Update the already existing map
                    }
                }
                */
            }
        }
    }

    return groupedCounterMap;
}


//CheckIns w.r.t. Attribute
std::map<std::string, int> spatialFeatures::numCheckInsWRTAttribute(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r)
{
    std::map<std::string, int> groupedCounterMap;
    std::map<std::string, int>::iterator groupedCounterMapIt;

    if(objSetWithGroupingAttrib.size() > 1)
    {
        for (auto& pointObj : objSetWithGroupingAttrib)
        {
            std::string groupingAttrib = std::get<0>(pointObj);
            Point objPoint = std::get<1>(pointObj);

            if(withinRoadDistanceR(map_geo_position, ch_query, p, objPoint, r))
            {
                groupedCounterMapIt = groupedCounterMap.find(groupingAttrib);

                //If not found, create it
                if ( groupedCounterMapIt == groupedCounterMap.end() )
                {
                    std::pair<std::string, int> groupingAttribInit (groupingAttrib, 1);
                    groupedCounterMap.insert(groupingAttribInit);
                }
                else
                {
                    // updating already existing record
                    int groupingAttribCounter = groupedCounterMapIt->second;
                    groupingAttribCounter++;

                    //Updating groupedCounterMap
                    groupedCounterMap[groupingAttrib] = groupingAttribCounter;
                }
            }
        }
    }

    return groupedCounterMap;
}

std::unordered_map< Point, std::map<std::string, int> > spatialFeatures::numCheckInsWRTAttribute(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r)
{
    std::unordered_map< Point, std::map<std::string, int> > groupedCounterMap;
    std::unordered_map< Point, std::map<std::string, int> >::iterator groupedCounterMapIt;

    if(candidObjList.size() > 1)
    {
        for (auto& objPoint : candidObjList)
        {
            if(objSetWithGroupingAttrib.size() > 1)
            {
                std::map<std::string, int> nCheckIns = numCheckInsWRTAttribute(map_geo_position, ch_query, objPoint, objSetWithGroupingAttrib, r);
                groupedCounterMap[objPoint] = nCheckIns;
            }
        }
    }

    return groupedCounterMap;
}
