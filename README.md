# Snake Game

A simple terminal-based Snake game written in C++ using `ncurses`.

## Features
- Classic Snake game mechanics
- Keyboard controls for movement
- Dynamic screen resizing support
- Collision detection for walls and self
- Randomly generated food items
- Adjustable game speed

## Requirements
- Linux-based OS (Tested on Arch Linux)
- g++ compiler
- `ncurses` library

## Installation
Ensure you have `ncurses` installed on your system:
```sh
sudo pacman -S ncurses # For Arch Linux
sudo apt-get install libncurses5-dev libncursesw5-dev # For Debian-based systems
```

## Build
To compile the game, run:
```sh
g++ -o snake main.cpp -lncurses
```

## Run
To play the game, execute:
```sh
./snake
```

## Controls
- `Arrow keys` - Move the snake
- `Esc` - Exit the game

## Gameplay
The goal of the game is to eat the food and grow the snake while avoiding collisions with the walls and itself. Each time the snake eats food, it grows longer and the speed increases.

## License
This project is open-source and available under the MIT License.

