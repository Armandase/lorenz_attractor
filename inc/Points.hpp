#ifndef POINTS_HPP
# define POINTS_HPP

#include <ostream>

class Points
{
    public:
        Points();
        Points(double x, double y, double z, double t);
        Points(double x, double y, double z);
        ~Points();

        Points(const Points& copy);
		Points& operator=(const Points &cpy);

        double getX() const { return (this->_x); };
        double getY() const { return (this->_y); };
        double getZ() const { return (this->_z); };
        double getT() const { return (this->_t); };

    private:
        double _x, _y, _z;
        double _t;
};

std::ostream& operator<<(std::ostream& os, const Points& point);

#endif