#include "../inc/main.hpp"
#include "../inc/Attractor.hpp"

// x = 10, y = 10, z = 10
// beta = 8/3
// sigma = 10
// rho = 28
t_deltas getLorenzAttractorFormula() {
    t_deltas deltas;

    // dx/dt = σ(y - x)
    deltas.delta_x = [](double x, double y, double z) { return 10.0 * (y - x); };
    // dy/dt = x(ρ - z) - y
    deltas.delta_y = [](double x, double y, double z) { return x * (28.0 - z) - y; };
    // dz/dt = xy - βz
    deltas.delta_z = [](double x, double y, double z) { return x * y - (8.0 / 3.0) * z; };
    return deltas;
}

// x = 0.1, y = 0, z = 0
// a = 1.4
t_deltas getHalvorsenAttractorFormula() {
    t_deltas deltas;
    
    // dx/dt = -a*x - 4*y - 4*z - y^2
    deltas.delta_x = [](double x, double y, double z) { return -1.4 * x - 4 * y - 4 * z - y * y; };
    // dy/dt = -a*y - 4*z - 4*x - z^2
    deltas.delta_y = [](double x, double y, double z) { return -1.4 * y - 4 * z - 4 * x - z * z; };
    // dz/dt = -a*z - 4*x - 4*y - x^2
    deltas.delta_z = [](double x, double y, double z) { return -1.4 * z - 4 * x - 4 * y - x * x; };
    return deltas;
}

// x = 0.1, y = 0, z = 0
t_deltas getAizawaAttractorFormula() {
    t_deltas deltas;

    // dx/dt = (z - b)*x - d*y
    deltas.delta_x = [](double x, double y, double z) { return (z - 0.7) * x - 3.5 * y; };
    // dy/dt = d*x + (z - b)*y
    deltas.delta_y = [](double x, double y, double z) { return 3.5 * x + (z - 0.7) * y; };
    // dz/dt = c + a*z - z^3/3 - (x^2 + y^2)*(1 + e*z) + f*z*x^3
    deltas.delta_z = [](double x, double y, double z) { return 0.6 + 0.95 * z - ((z * z * z) / 3) - (x * x + y * y) * (1 + 0.25 * z) + 0.1 * z * x * x * x; };
    return deltas;
}

// x = 0.1, y = 0, z = 0
t_deltas getSprottBAttractorFormula() {
    t_deltas deltas;

    // dx/dt = a*y*z
    deltas.delta_x = [](double x, double y, double z) { return 0.4 * y * z; };
    // dy/dt = x - b * y
    deltas.delta_y = [](double x, double y, double z) { return x - 1.2 * y; };
    // dz/dt = c - x * y
    deltas.delta_z = [](double x, double y, double z) { return 1.0 - x * y; };
    return deltas;
}

// x = 1, y = 1, z = 0
// p = 0.3
// o = 2.7
// r = 1.7
// c = 2.0
// e = 9.0
t_deltas getDadrasAttractorFormula(){
    t_deltas deltas;

    // dx/dt = y - p * x + o * y * z
    deltas.delta_x = [](double x, double y, double z) { return y - 0.3 * x + 2.7 * y * z; };
    // dy/dt = r * y - x * z + z
    deltas.delta_y = [](double x, double y, double z) { return 1.7 * y - x * z + z; };
    // dz/dt = c * x * y - e * z
    deltas.delta_z = [](double x, double y, double z) { return 2.0 * x * y - 9.0 * z; };
    return deltas;
}

// a = b = 0.2
// c = 5.7
t_deltas getRosselAttractorFormula(){
    t_deltas deltas;

    // dx/dt = -y - z
    deltas.delta_x = [](double x, double y, double z) { return -y - z; };
    // dy/dt = x + a*y
    deltas.delta_y = [](double x, double y, double z) { return x + 0.2 * y; };
    // dz/dt = b + z * (x - c)
    deltas.delta_z = [](double x, double y, double z) { return 0.2 + z * (x - 5.7); };
    return deltas;
}