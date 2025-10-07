#include "../inc/Attractor.hpp"
#include "../inc/Points.hpp"
#include <cmath>
#include <fstream>

Attractor::Attractor(){
    this->_x = 10;
    this->_y = 10;
    this->_z = 10;
    this->_dt = 0.01;
    this->_t = 10;
}

Attractor::Attractor(double x, double y, double z, double dt, double t){
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_dt = dt;
    this->_t = t;
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
        this->_t = cpy.getT();
    }
    return (*this);
}

void    Attractor::renderItself(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, RED, GREEN , BLUE, 255);

    // drawCircle(this->_x, this->_y, this->_radius, renderer);
    // SDL_Point();
}


std::vector<Points> Attractor::updateForDuration(double duration){
    std::vector<Points> points_vec;

    double x = this->_x;
    double y = this->_y;
    double z = this->_z;
    this->_t = duration;
    for (double  iter_t = 0; iter_t < this->_t; iter_t += this->_dt){
        this->updateAttractor(iter_t);       
        points_vec.push_back({this->_x, this->_y, this->_z, iter_t});
    }
    // save the vector into a log file
    std::ofstream log_file("attractor_log.txt");
    for (const auto& point : points_vec) {
        log_file << point.getX() << ";" << point.getY() << ";" << point.getZ() << ";" << point.getT() << std::endl;
    }
    log_file.close();

    return points_vec;
}

void Attractor::updateAttractor(double t){
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
double Attractor::delta_x(double x, double y, double z) const{
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
/*
Entrées :
  - Paramètres : σ, ρ, β
  - Conditions initiales : x0, y0, z0
  - Intervalle de temps : t0, T
  - Pas de temps : h

Définitions :
  f1(x, y, z) = σ (y - x)
  f2(x, y, z) = ρ x - y - x z
  f3(x, y, z) = x y - β z

Algorithme :
  t ← t0
  x ← x0
  y ← y0
  z ← z0

  Tant que t ≤ T faire :
    k1x = h * f1(x, y, z)
    k1y = h * f2(x, y, z)
    k1z = h * f3(x, y, z)

    k2x = h * f1(x + k1x/2, y + k1y/2, z + k1z/2)
    k2y = h * f2(x + k1x/2, y + k1y/2, z + k1z/2)
    k2z = h * f3(x + k1x/2, y + k1y/2, z + k1z/2)

    k3x = h * f1(x + k2x/2, y + k2y/2, z + k2z/2)
    k3y = h * f2(x + k2x/2, y + k2y/2, z + k2z/2)
    k3z = h * f3(x + k2x/2, y + k2y/2, z + k2z/2)

    k4x = h * f1(x + k3x, y + k3y, z + k3z)
    k4y = h * f2(x + k3x, y + k3y, z + k3z)
    k4z = h * f3(x + k3x, y + k3y, z + k3z)

    x ← x + (k1x + 2*k2x + 2*k3x + k4x) / 6
    y ← y + (k1y + 2*k2y + 2*k3y + k4y) / 6
    z ← z + (k1z + 2*k2z + 2*k3z + k4z) / 6

    t ← t + h

    Sauvegarder (t, x, y, z)

Sortie : Liste des Attractor (t, x(t), y(t), z(t))
*/
// std::vector<Points> Attractor::runge_kutta(){
//     std::vector<Points> points_vec;

//     // double x = 0, y = 0, z = 0, t = 0;
//     double x = this->_x;
//     double y = this->_y;
//     double z = this->_z;
//     for (double  iter_t = 0; iter_t < this->_t; iter_t += this->_dt){
//         double k1x = this->_dt * this->delta_x(x, y, z);
//         double k1y = this->_dt * this->delta_y(x, y, z);
//         double k1z = this->_dt * this->delta_z(x, y, z);

//         double k2x = this->_dt * this->delta_x(x + k1x / 2, y + k1y / 2, z + k1z / 2);
//         double k2y = this->_dt * this->delta_y(x + k1x / 2, y + k1y / 2, z + k1z / 2);
//         double k2z = this->_dt * this->delta_z(x + k1x / 2, y + k1y / 2, z + k1z / 2);

//         double k3x = this->_dt * this->delta_x(x + k2x / 2, y + k2y / 2, z + k2z / 2);
//         double k3y = this->_dt * this->delta_y(x + k2x / 2, y + k2y / 2, z + k2z / 2);
//         double k3z = this->_dt * this->delta_z(x + k2x / 2, y + k2y / 2, z + k2z / 2);

//         double k4x = this->_dt * this->delta_z(x + k3x, y + k3y, z + k3z);
//         double k4y = this->_dt * this->delta_x(x + k3x, y + k3y, z + k3z);
//         double k4z = this->_dt * this->delta_y(x + k3x, y + k3y, z + k3z);

//         x = x + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
//         y = y + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;
//         z = z + (k1z + 2 * k2z + 2 * k3z + k4z) / 6;

//         points_vec.push_back({x, y, z, iter_t});
//     }
//     for (auto &point : points_vec){
//         std::cout << point.getX() << ";" << point.getY() << ";" << point.getZ() << ";" << point.getT() << std::endl;
//     }
//     return points_vec;
// }