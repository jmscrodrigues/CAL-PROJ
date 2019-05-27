#pragma once

#include <string>
#include <vector>
#include <cmath>

class Location{
	int id;
    double x, y;
    int expectedDeliveries;
    std::vector<std::string> tags;

public:
    Location(int id, double x, double y);
    double getX() const;
    double getY() const;
    int getID() const;
    void addTag(std::string tag);
    bool checkIfHasTag(std::string tag) const;

};

bool operator==(const Location& lhs, const Location& rhs);

double getDistBetweenLocations(const Location origin, const Location dest);

//int findClosestLocation(Location origin, vector<Location> destinations);
