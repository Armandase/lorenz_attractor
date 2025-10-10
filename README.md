# Lorenz attractor


## Usage steps:

#### install vtk:

```bash
sudo apt-get install libvtk9-dev  # On Debian/Ubuntu
```

#### build with cmake:
```bash
mkdir -p build
cd build
cmake ..
make
```

#### launch it:
```bash
./lorenz [nb_iterations] [timer_interval_ms] [time_step_ms]
```

## Then:

![Lorenz attractor](./assets/lorenz_multicolor.png)
