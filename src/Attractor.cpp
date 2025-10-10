#include "../inc/Attractor.hpp"
#include "../inc/Points.hpp"
#include <cmath>
#include <fstream>

Attractor::Attractor(){
    this->_x = 10;
    this->_y = 10;
    this->_z = 10;
    this->_dt = 0.01;
}

Attractor::Attractor(double x, double y, double z, double dt){
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_dt = dt;
}

Attractor::~Attractor(){}

Attractor::Attractor(const Attractor& copy){
    Attractor::operator=(copy);
}

Attractor& Attractor::operator=(const Attractor &cpy){
    if (this != &cpy){
        this->_x = cpy.getX();
        this->_y = cpy.getY();
        this->_z = cpy.getZ();
        this->_dt = cpy.getdT();
    }
    return (*this);
}

std::vector<Points> Attractor::updateForDuration(double duration){
    std::vector<Points> points_vec;

    for (double  iter_t = 0; iter_t < duration; iter_t += this->_dt){
        this->updateAttractor();
        points_vec.push_back({this->_x, this->_y, this->_z, iter_t});
    }
    return points_vec;
}

//  use Runge-Kutta 4th order
void Attractor::updateAttractor(){
    double x = this->_x;
    double y = this->_y;
    double z = this->_z;

    double k1x = this->_dt * this->delta_x(x, y, z);
    double k1y = this->_dt * this->delta_y(x, y, z);
    double k1z = this->_dt * this->delta_z(x, y, z);

    double k2x = this->_dt * this->delta_x(x + k1x / 2, y + k1y / 2, z + k1z / 2);
    double k2y = this->_dt * this->delta_y(x + k1x / 2, y + k1y / 2, z + k1z / 2);
    double k2z = this->_dt * this->delta_z(x + k1x / 2, y + k1y / 2, z + k1z / 2);

    double k3x = this->_dt * this->delta_x(x + k2x / 2, y + k2y / 2, z + k2z / 2);
    double k3y = this->_dt * this->delta_y(x + k2x / 2, y + k2y / 2, z + k2z / 2);
    double k3z = this->_dt * this->delta_z(x + k2x / 2, y + k2y / 2, z + k2z / 2);

    double k4x = this->_dt * this->delta_z(x + k3x, y + k3y, z + k3z);
    double k4y = this->_dt * this->delta_x(x + k3x, y + k3y, z + k3z);
    double k4z = this->_dt * this->delta_y(x + k3x, y + k3y, z + k3z);

    this->_x = x + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
    this->_y = y + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;
    this->_z = z + (k1z + 2 * k2z + 2 * k3z + k4z) / 6;
}
// /* 
// Lorenz attractor equations
// dx/dt = σ(y - x)
double Attractor::delta_x(double x, double y, __attribute_maybe_unused__ double z) const{
    return SIGMA * (y - x);
}

// dy/dt = x(ρ - z) - y
double Attractor::delta_y(double x, double y, double z) const{
    return x * (RHO - z) - y;
}

// dz/dt = xy - βz
double Attractor::delta_z(double x, double y, double z) const{
    return x * y - BETA * z;
}
// */

//Aizawa attractor equations
/*
double Attractor::delta_x(double x, double y, __attribute_maybe_unused__ double z) const{
    double a = 0.95, b = 0.7, c = 0.6, d = 3.5, e = 0.25, f = 0.1;
    return (z - b) * x - d * y;
}

double Attractor::delta_y(double x, double y, double z) const{
    double a = 0.95, b = 0.7, c = 0.6, d = 3.5, e = 0.25, f = 0.1;
    return d * x + (z - b) * y;
}

double Attractor::delta_z(double x, double y, double z) const{
    double a = 0.95, b = 0.7, c = 0.6, d = 3.5, e = 0.25, f = 0.1;
    return c + a * z - (z * z * z) / 3 - (x * x) + f * z * (x * x * x);
}
*/