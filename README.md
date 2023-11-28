# Raylib C++ Platformer Basics

This project is an exploration into the basics of game development using the Raylib library in C++. It features a simple platformer game where the player can move and jump within a 2D environment, enhanced with animated elements like nebulae.

## Features

- Basic game loop structure using Raylib.
- Player movement and jumping mechanics.
- Animated background elements (nebulae) for a dynamic environment.
- Basic collision detection and gravity implementation.

## Requirements

To run this project, you'll need:
- [Raylib](https://www.raylib.com/) installed on your system.
- A C++ compiler (e.g., GCC, Clang).

## Installation

1. Clone the repository:
   ```bash
   git clone [repository-url]
   ```
2. Navigate to the project directory:
```
cd [project-directory]
```

3 .Create a build directory and navigate into it:
  ```
mkdir build && cd build
```
4. Run CMake to configure the project:
```
cmake ..
```
5. Compile the project:
```
cmake --build .
```
6. Run the compiled executable (the executable name is 'cpplatformer'):
```
./cpplatformer
```
Note: Make sure you have Raylib installed and findable by CMake. The CMake configuration is set to use C++17 and link against the Raylib library.


## Usage

- **Movement**: Use the `A` and `D` keys to move the player left and right.
- **Jump**: Press the `SPACE` key to make the player jump.
- **Run**: Hold the `LEFT SHIFT` key to make the player run.

## Contributing

Contributions to this project are welcome, especially from those who are also learning game development and C++. Feel free to fork the repository, make changes, and submit a pull request!

## License

This project is open source and available under the [MIT License](https://opensource.org/licenses/MIT).
