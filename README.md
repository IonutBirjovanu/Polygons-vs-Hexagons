# Polygons-vs-Hexagons
A OpenGL-powered graphical application inspired by the classic Plants vs. Zombies game. In this game, shooters and zombies are color-coded into four distinct colors: blue, yellow, orange, and red. Only shooters of the same color will attack zombies of the corresponding color, adding a strategic layer to the gameplay.

## Overview
The game uses the mouse cursor as the user input method. The user has a simple interface that consists of four color-coded shooters, each costing a set amount of stars, a 3x3 grid of green squares where he can place the shooters (if he has enough stars for them) and a dashboard displaying the lives left (starts with 3, game is over when all 3 are lost) and the number of stars the user has gathered (he starts with 5 and can gather to a maximum of 9).

### These are the user inputs of the game:

**1) Place Shooter:** Left-Click to select a type of shooter and plant it on a green square, or drag-and-drop it on the square.

**2) Remove Shooter:** Right-Click onto a placed shooter to remove it from the squares grid. Removing a shooter will not give the user its spent stars back.

**3) Collect Star:** To gather stars used for placing shooters, the user has to Left-Click the gold stars that appear on the screen at random places. The uncollected stars will disappear from the screen after 5 seconds.

### Gameplay
The player starts the game with an empty grid, 5 stars and 3 lives. Every 5 seconds, 1-3 stars will appear on the screen, and can be collected if Left-Clicked. There can be a maximum of 9 stars, after which further collected stars will not add up to the total any more.
Every 1-10 seconds, several colored hexagons will appear on one or more of the 3 lines corresponding to the green squares grid and start advancing to the left. The player has to place a color-matched shooter on the correspondent line to defend from the hexagon. The hexagon will faint after 3 attacks of any same-colored shooter. However, if the shooter didn't have enough time to attack the hexagon and it got too close to it, the shooter will get removed by the hexagon. If a hexagon tears through an entire row of shooters, it will activate the final defense: the Mower: Once a mower detects a hexagon, it will start advancing from left to right on the whole row, removing any hexagon in its path. Every row has one mower, with a single use each. The player will lose a heart after a hexagon advances a whole row from left to right without being removed.
The game ends after the player loses all its 3 lives, triggering the ending animation. The game goes on infinitely, it can only end when the player loses.

## How to use
This graphical application uses the UPB-graphics [gfx-framework](https://github.com/UPB-Graphics/gfx-framework) at its core. To use it, follow these steps:

**1)** Clone the [gfx-framework](https://github.com/UPB-Graphics/gfx-framework) repository on your local machine.

**2)** Replace the ```gfx-framework/src/lab_m1``` folder with the one provided in this repository.

**3)** Edit the ```gfx-framework/src/main.cpp``` file: replace the 47th line with: ```World *world = new m1::tema1;``` to select the Polygons-vs-Hexagons graphical application.

**4)** Compile and run the code using your preferred C++ compiler with support for OpenGL.

## Screenshot of the graphical application running:
![polygons_vs_hexagons](https://github.com/IonutBirjovanu/Polygons-vs-Hexagons/assets/44101580/5e10915c-7ceb-46a7-8e34-a4bd0a841dfd)
