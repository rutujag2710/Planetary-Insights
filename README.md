# Planetary Insights

## Overview
This project is a graphical simulation of the Solar System created using **C++ and the graphics.h library**. It features planets, moons, a comet, an asteroid belt, and an educational mode that provides interesting facts about celestial bodies. The simulation allows for real-time updates, animations, and user interactions.

## Features
- Simulated Orbits: Planets orbit the Sun along elliptical paths.
- Planetary Details: Each planet has its own size, orbit radius, speed, and unique color.
- Moons: Some planets have moons, which also orbit their respective planets.
- Asteroid Belt: A dense cluster of asteroids between Mars and Jupiter.
- Comet: Randomly generated comet traversing the screen.
- Educational Mode: Provides facts and information about selected celestial objects.
- Adjustable Time Scale: Speed up or slow down the simulation.
- Pause and Resume: Ability to pause or resume the simulation.
- Graphical Features: Stars in the background, elliptical orbits, and comet tail effects.

## Controls
- Left Click: Click on a planet to display information.
- P: Pause/Resume the simulation.
- E: Toggle Educational Mode.
- +: Increase the time scale (up to 5x speed).
- -: Decrease the time scale (down to 0.1x speed).
- R: Reset the time scale to normal.
- ESC: Exit the simulation.

## How to Run
1. Prerequisites: 
   - Install a C++ compiler such as Dev-C++.
   - Ensure the `graphics.h` library is set up properly.
2. Compiling:
   - Open the project in Dev-C++.
   - Compile and run the `main.cpp` file.
3. Note: Ensure to have the necessary graphics files for Windows.

## Implementation Details
- Language: C++
- Libraries: `graphics.h`, `math.h`, `ctime`, `windows.h`
- Class Structure:
  - `Planet`: Manages the properties and behavior of each planet.
  - `Comet`: Simulates a comet with a tail effect.
  - `AsteroidBelt`: Contains and animates a collection of asteroids.
- Graphics: Uses the `graphics.h` library for all graphical elements, including drawing orbits, planets, and animations.

## Project Structure
- `main.cpp`: The main source file containing the simulation logic.
- Graphics Setup: Instructions for setting up `graphics.h` on your system.

## Future Enhancements
- More Celestial Bodies: Adding dwarf planets or additional moons.
- Improved Interactions: Click-and-drag to view different perspectives.
- 3D Simulation: Expanding the project to a 3D environment.


