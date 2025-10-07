#include "../inc/Points.hpp"
#include <cmath>

Points::Points(){
    this->_x = 10;
    this->_y = 10;
    this->_z = 10;
    this->_t = 10;
}

Points::Points(double x, double y, double z, double t){
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_t = t;
}

Points::~Points(){}

Points::Points(const Points& copy){
    Points::operator=(copy);
}

Points& Points::operator=(const Points &cpy){
    if (this != &cpy){
        this->_x = cpy.getX();
        this->_y = cpy.getY();
        this->_z = cpy.getZ();
        this->_t = cpy.getT();
    }
    return (*this);
}

// double Points::getX() const {
//     return this->_x;
// }

// double Points::getY() const {
//     return this->_y;
// }

// double Points::getZ() const {
//     return this->_z;
// }

// double Points::getT() const {
//     return this->_t;
// }