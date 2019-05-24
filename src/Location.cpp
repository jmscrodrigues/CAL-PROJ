#include "Location.h"

Location::Location(int id, double x, double y) : id(id) , x(x),y(y) , expectedDeliveries(0) {
}

double Location::getX() const{
    return this->x;
}

double Location::getY() const{
    return this->y;
}

int Location::getID() const{
    return this->id;
}

bool Location::checkIfHasTag(std::string tag) const{
    for(unsigned int i = 0; i < (this->tags).size(); i++){
        if((this->tags).at(i) == tag)
            return true;
    }
    return false;
}

void Location::addTag(std::string tag){
    (this->tags).push_back(tag);
}

bool operator==(const Location& lhs, const Location& rhs){
    if(lhs.getID() == rhs.getID())
        return true;
    else
        return false;
}
