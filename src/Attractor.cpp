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
    // std::ofstream log_file("attractor_log.txt");
    // for (const auto& point : points_vec) {
    //     log_file << point.getX() << ";" << point.getY() << ";" << point.getZ() << ";" << point.getT() << std::endl;
    // }
    // log_file.close();

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

// dx/dt = σ(y - x)
double Attractor::delta_x() const{
    return SIGMA * (this->_y - this->_x);
}

// dy/dt = x(ρ - z) - y
double Attractor::delta_y() const{
    return this->_x * (RHO - this->_z) - this->_y;
}

// dz/dt = xy - βz
double Attractor::delta_z() const{
    return this->_x * this->_y - BETA * this->_z;
}

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