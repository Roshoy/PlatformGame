# PlatformGame
Simple mechanics for 2D platform game
## Functionalities
### Mechanics
1. Collisions based on rectangle hitbox (AABB collision detection), between player and enemies, any character and solid fields
2. Moving with player (left, right, jump), with basic phisics (falling)
3. Killing enemy when jumping on top of him
4. Enemies move as far as they can to one side, and when they meet obstacle, they turn the other way
5. Camera follows player
6. Animations: in cycle (idle animation) or one series of frames (jump animation)
### Map
Map is implemented as tile map and consists of:
1. Textures for every tile held in mapfile.txt
2. Spawn points of characters
3. *IN PROGRESS* Scripts for fields with strategy design pattern
### Menu
1. Buttons, that can be highlighted
2. Main menu: start game and exit
3. Menu after lose/win: try again, main menu, exit
### TO DO
1. More possible moves
2. Attack
3. Projectiles
4. Actual playable map
5. More enemies
## Prerequisites
Visual Studio 2017



