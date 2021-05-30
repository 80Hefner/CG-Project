# Project source

Code used for generating .3d files

```bash
./generator torus 2 25 32 128 asteroid_belt.3d
./generator torus 0.6 1.7 32 32 saturn_ring.3d
./generator torus 0.05 1.7 32 32 uranus_ring.3d
./generator sphere 1 32 32 sphere.3d
./generator --bezier teapot.patch 8 teapot.3d

./generator torus 0.01 8.5 8 128 orbits/mercury_orbit.3d
./generator torus 0.01 11.5 8 128 orbits/venus_orbit.3d
./generator torus 0.01 14.5 8 128 orbits/earth_orbit.3d
./generator torus 0.01 17.5 8 128 orbits/mars_orbit.3d
./generator torus 0.01 35 8 128 orbits/jupiter_orbit.3d
./generator torus 0.01 60 8 128 orbits/saturn_orbit.3d
./generator torus 0.01 100 8 128 orbits/uranus_orbit.3d
./generator torus 0.01 140 8 128 orbits/neptune_orbit.3d

```
