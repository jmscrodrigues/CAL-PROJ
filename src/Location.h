#include <string>
#include <vector>

class Location{
    double x, y;
    int id, expectedDeliveries;
    std::vector<std::string> tags;

public:

    Location(int id, double x, double y);
    double getX();
    double getY();
    int getID();
    void addTag(std::string tag);
    bool checkIfHasTag(std::string tag);

};

Location::Location(int id, double x, double y) {
    this->id  = id;
    this->x = x;
    this->y = y;
    this->expectedDeliveries = 0;
}

double Location::getX(){
    return this->x;
}

double Location::getY(){
    return this->y;
}

int Location::getID(){
    return this->id;
}

bool Location::checkIfHasTag(std::string tag){
    for(int i = 0; i < (this->tags).size(); i++){
        if((this->tags).at(i) == tag)
            return true;
    }
    return false;
}

void Location::addTag(std::string tag){
    (this->tags).push_back(tag);
}

bool operator==(const Location& lhs, const Location& rhs){
    if(lhs.getID == rhs.getID)
        return true;
    else
        return false;
}