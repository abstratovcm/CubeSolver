# CubeSolver

CubeSolver is an OpenGL-based project that draws a Rubik's Cube and allows it to be manipulated by the user using keyboard inputs. The cube can be rotated and twisted just like a real Rubik's Cube.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites
Before you begin, make sure that you have the following software installed:

- G++ compiler
- GLUT library
- OpenGL library
- GLU library

## Installing
To install the project, simply clone the repository onto your local machine:

```bash
git clone https://github.com/abstratovcm/CubeSolver.git
```
Next, navigate to the project directory and run the following command to compile the code:

```bash
make all
```
## Running the program
To run the program, execute the following command in the terminal:

```bash
./bin/Debug
```
This will launch the CubeSolver program, and you will be able to move the cube by pressing keys on your keyboard.

## Keyboard and Mouse Controls
CubeSolver allows you to manipulate the Rubik's Cube using the following controls:

- `U`: rotate the upper layer clockwise
- `u`: rotate the upper layer counter-clockwise
- `D`: rotate the bottom layer clockwise
- `d`: rotate the bottom layer counter-clockwise
- `L`: rotate the left layer clockwise
- `l`: rotate the left layer counter-clockwise
- `R`: rotate the right layer clockwise
- `r`: rotate the right layer counter-clockwise
- `F`: rotate the front layer clockwise
- `f`: rotate the front layer counter-clockwise
- `B`: rotate the back layer clockwise
- `b`: rotate the back layer counter-clockwise
- `1`: return the cube to its original form
- Up arrow: pitch the camera up
- Down arrow: pitch the camera down
- Left arrow: yaw the camera to the left
- Right arrow: yaw the camera to the right
- Left mouse button: Click and hold to rotate the cube by moving the mouse horizontally and vertically.



## Cleaning up
To clean up any generated files, run the following command:

```bash
make clean
```
## Built With
- GLUT - The OpenGL Utility Toolkit
- OpenGL - A cross-platform graphics API
## Contributing
Please read CONTRIBUTING.md for details on our code of conduct, and the process for submitting pull requests to us.

If you are interested in contributing to CubeSolver, please feel free to fork the repository and make a pull request with your changes. All contributions are welcome and appreciated.

