# SatelliteOrbits
Satellite Orbit Simulation in C++

This was my first attempt at a GUI based project in C++. It was also my first try at a new IDE, Visual Studio. I set out wanting to make a full real-physics simulation of orbits around the earth in 2D. I utilized the SFML graphics library for all of the 2 dimensional displays for the Earth, and each satellite. 

I wanted to test out usage of classes mostly with this project, as well as making my own header files to define them. I had already experienced usage of structs in my C projects, so this was a good opportunity. I utilized the Class structure for the SpaceObjects being tracked on screen, as well as for the overall simulation running. 

Future Features:
  - Addition of a dropdown menu feature where you can add in your own custom satellite orbits
  - Simulations of orbits with varying eccentricity (right now the simulation only will do circular orbits)
    -Also adding in the real physics calculations, right now the algorithm for movement on screen is just a basic check of how far the satellite should've moved in degrees       based on the period of the orbit/altitude
  - "Main Menu" with start and settings
  - Actual sprites for satellites instead of circles
  




