#include <string>
#include <vector>

class Location{
    double x, y;
    int id, expectedDeliveries;
    std::vector<std::string> tags;

public:

    Location(int id, double x, double y);
    double getX() const;
    double getY() const;
    int getID() const;
    void addTag(std::string tag);
    bool checkIfHasTag(std::string tag) const;

};

bool operator==(const Location& lhs, const Location& rhs){
    if(lhs.getID() == rhs.getID())
        return true;
    else
        return false;
}