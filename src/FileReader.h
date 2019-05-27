#include <string>
#include <fstream>
#include "Graph.h"
#include "Location.h"

bool readFile(std::string selectedLocation, Graph<Location> * graph);

class tempEdge{
    Location origin, dest;
    double w;

public:


    tempEdge(Location &o, Location &d);

    Location getOrigin();
    Location getDest();
    double getW();
};
