#ifndef ATTRACTOR_HPP
# define ATTRACTOR_HPP

# include "Points.hpp"
# include "main.hpp"
# include <vector>
# include <cmath>
# include <fstream>

class Attractor
{
    public:
        Attractor();
        Attractor(double x, double y, double z, double dt);
        Attractor(double x, double y, double z, double dt, t_deltas deltas);
        ~Attractor();

        Attractor(const Attractor& copy);
		Attractor& operator=(const Attractor &particle);

        double getX() const { return (this->_x); };
        double getY() const { return (this->_y); };
        double getZ() const { return (this->_z); };
        double getdT() const { return (this->_dt); };

        void    updateAttractor();

        std::vector<Points>    updateForDuration(double duration);


    private:
        t_deltas deltas; // struct containing the 3 functions for dx/dt, dy/dt and dz/dt

        double _x, _y, _z;
        double _dt;

};

#endif