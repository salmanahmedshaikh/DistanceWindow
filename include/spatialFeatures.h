#pragma once
#ifndef SPATIALFEATURES_H
#define SPATIALFEATURES_H
#include<list>
#include<tuple>
#include<list>
#include <iostream>
#include <unordered_map>
#include <map>
#include "point.h"
#include "spatialDistance.h"
#include "stdafx.h"
#include <routingkit/geo_position_to_node.h>
#include <routingkit/contraction_hierarchy.h>

using namespace RoutingKit;


class spatialFeatures
{
    public:
        spatialFeatures();
        virtual ~spatialFeatures();

        bool withinDistanceR(Point p1, Point p2, double r);
        bool withinRoadDistanceR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p1, Point p2, double r);

        int numObjectsWithinR(Point p, std::list<std::tuple<std::string, Point> > objSet, double r);
        int numObjectsWithinR(Point p, std::list<Point> objSet, double r);
        std::list<std::tuple<Point, int> > numObjectsWithinR(std::list<Point> candidObjList, std::list<Point> objList, double r);
        std::list<std::tuple<Point, int> > numObjectsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<Point> objList, double r);
        int numObjectsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<Point> objList, double r);

        int numCarParkingsWithinR(Point p, std::list<std::tuple<Point, double> > objSetWithArea, double r);
        std::list<std::tuple<Point, double> > numCarParkingsWithinR(std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWithArea, double r);
        int numCarParkingsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<std::tuple<Point, double> > objSetWithArea, double r);
        std::list<std::tuple<Point, double> > numCarParkingsWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWithArea, double r);

        std::map<std::string, int> numCheckInsWRTAttribute(Point p, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r);
        std::unordered_map< Point, std::map<std::string, int> > numCheckInsWRTAttribute(std::list<Point> candidObjList, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r);

        std::list<std::tuple<Point, double> > trafficEstimateWithinR(std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r);
        double trafficEstimateWithinR(Point p, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r);

        double trafficEstimateWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r);
        std::list<std::tuple<Point, double> > trafficEstimateWithinR(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<std::tuple<Point, double> > objSetWTrafficEstimate, double r);

        std::map<std::string, int> numCheckInsWRTAttribute(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, Point p, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r);
        std::unordered_map< Point, std::map<std::string, int> > numCheckInsWRTAttribute(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, std::list<Point> candidObjList, std::list<std::tuple<std::string, Point> > objSetWithGroupingAttrib, double r);


        //std::unordered_map<std::string, int> groupedCounterMap;
        //std::unordered_map<std::string, int>::iterator groupedCounterMapIt;

    protected:

    private:
};

#endif // SPATIALFEATURES_H


