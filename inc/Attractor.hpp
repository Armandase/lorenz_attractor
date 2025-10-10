#ifndef ATTRACTOR_HPP
# define ATTRACTOR_HPP

# include "Points.hpp"
# include <vector>

# define BETA 8/3
# define SIGMA 10
# define RHO 28

class Attractor
{
    public:
        Attractor();
        Attractor(double x, double y, double z, double dt);
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
        double delta_x(double x, double y, __attribute_maybe_unused__ double z) const;
        double delta_y(double x, double y, double z) const;
        double delta_z(double x, double y, double z) const;

        double _x, _y, _z;
        double _dt;

};

#endif