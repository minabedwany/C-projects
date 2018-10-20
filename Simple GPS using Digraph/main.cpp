// main.cpp
//
// ICS 46 Spring 2018
// Project #5: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include <iostream>
#include <algorithm>
#include <iomanip>
#include "InputReader.hpp"
#include "RoadMap.hpp"
#include "RoadMapReader.hpp"
#include "TripReader.hpp"
#include "Trip.hpp"
#include "RoadSegment.hpp"
#include "TripMetric.hpp"
#include "RoadMapWriter.hpp"

int main()
{
    InputReader input(std::cin);
    RoadMapReader reader;
    RoadMap digraph = reader.readRoadMap(input);
    
    if(!digraph.isStronglyConnected())
    {
        std::cout << "Disconnected Map" << std::endl;
        return 0;
    }

    TripReader trip;
    std::vector<Trip> mytrips;
    mytrips = trip.readTrips(input); 

    for(auto x = mytrips.begin(); x != mytrips.end(); ++x)
    { 

                  //------------------------DISTANCE---------------------- 

        if(x->metric == TripMetric::Distance)
        {
            std::cout << "Shortest distance from " << digraph.vertexInfo(x->startVertex) << " to " << digraph.vertexInfo(x->endVertex) << std::endl;
            std:: cout << "  Begin at " << digraph.vertexInfo(x->startVertex) << std::endl;
            std::function<double(const RoadSegment&)> lambda = [](RoadSegment segment){return segment.miles;};
            std::map<int, int> paths = digraph.findShortestPaths(x->startVertex, lambda);
            std::vector<int> temp;
            temp.push_back(x->endVertex);
            int lastVertex = x->endVertex;
            for(auto it = paths.begin(); it != paths.end(); ++it)
            {
                int prevVertex = paths[lastVertex];
                if(temp.back() != prevVertex)
                {   
                    temp.push_back(prevVertex);
                    lastVertex = prevVertex;
                }
            }
        
            std::reverse(temp.begin(), temp.end());

            auto iter1 = temp.begin();
            double total = 0.0;
            iter1++;
            for(auto iter = temp.begin(); iter != temp.end(); ++iter)
            {
                if(iter1 == temp.end())
                    break;

                RoadSegment seg = digraph.edgeInfo(*iter, *iter1);
                std::cout << "  Continue to " << digraph.vertexInfo(*iter1) << " (" << seg.miles << " miles)" << std::endl;
                total += seg.miles;
                if(iter1 != temp.end())
                    iter1++;
            }
            std::cout << "Total distance: " << total << " miles\n" << std::endl;
        }


                 //-------------------------TIME---------------------------

        if(x->metric == TripMetric::Time)
        {
            std::cout << "Shortest driving time from " << digraph.vertexInfo(x->startVertex) << " to " << digraph.vertexInfo(x->endVertex) << std::endl;
            std:: cout << "  Begin at " << digraph.vertexInfo(x->startVertex) << std::endl;
            std::function<double(const RoadSegment&)> lambda = [](RoadSegment segment){return segment.miles/segment.milesPerHour;};
            std::map<int, int> paths = digraph.findShortestPaths(x->startVertex, lambda);
            std::vector<int> temp;
            temp.push_back(x->endVertex);
            int lastVertex = x->endVertex;
            for(auto it = paths.begin(); it != paths.end(); ++it)
            {
                int prevVertex = paths[lastVertex];
                if(temp.back() != prevVertex)
                {
                    temp.push_back(prevVertex);
                    lastVertex = prevVertex;
                }
            }

            std::reverse(temp.begin(), temp.end());
            
            auto iter1 = temp.begin();
            double final_total = 0.0;
            iter1++;
            for(auto iter = temp.begin(); iter != temp.end(); ++iter)
            {
                double total = 0.0;

                if(iter1 == temp.end())
                    break;
        
                RoadSegment seg = digraph.edgeInfo(*iter, *iter1);
                total += (seg.miles/seg.milesPerHour);
                final_total += (seg.miles/seg.milesPerHour);   

                int hours = total;
                double minutes = total*60.0;
                int mins = minutes;
                double secs = (minutes-mins)*60.0;                

                if(total >= 1.0)
                {  
                    std::cout << "  Continue to " << digraph.vertexInfo(*iter1) << " (" << seg.miles << " miles @ " << seg.milesPerHour << "mph = " << hours << " hrs " << mins << " mins " << secs << " secs)" << std::endl;
                }
                if(total < 1.0 && (total*60.0) >= 1.0)
                {
                    std::cout << "  Continue to " << digraph.vertexInfo(*iter1) << " (" << seg.miles << " miles @ " << seg.milesPerHour << "mph = " << mins << " mins " << std::setprecision(3) << secs << " secs)" << std::endl;           
                }

                if(total < 1.0 && (total*60.0) < 1.0)
                {
                    std::cout << "  Continue to " << digraph.vertexInfo(*iter1) << " (" << seg.miles << " miles @ " << seg.milesPerHour << "mph = " << std::setprecision(3) << secs << " secs)" << std::endl;
                }
            
                if(iter1 != temp.end())
                    iter1++;
            }

            int hours = final_total;
            double minutes = final_total*60.0;
            int mins = minutes;
            double secs = (minutes-mins)*60.0;
            
            if(final_total >= 1.0)
            {
                std::cout << "Total time: " << hours << " hrs " << mins << " mins " << secs << " secs\n" << std::endl;
            }
            if(final_total < 1.0 && (final_total*60.0) >= 1.0)
            {
                std::cout << "Total time: " << mins << " mins " << std::setprecision(3) << secs << " secs\n" << std::endl;
            }

            if(final_total < 1.0 && (final_total*60.0) < 1.0)
            {
                std::cout << "Total time: " << std::setprecision(3) << secs << " secs\n" << std::endl;
            }    
        }    
    }

    return 0;
}

