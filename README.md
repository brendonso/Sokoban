# Sokoban Simulator - Brendon So

# Intro
Hello! Welcome to my Sokoban project developed on Linux using the SFML library. The objective of the game is to push crates into their designated positions on the map. The game includes various gameplay mechanics such as tracking progress, backtracking steps, dragging back crates, and resetting the game.

**Initial map layout with some crates in position.**
<img src="resources/SS1.png" alt="Initial map layout with some crates in position." width="444"/>

**Completed game**
<img src="resources/SS3.png" alt="Completed game" width="444"/>

**A new generated object locations**
<img src="resources/SS2.png" alt="A new generated object locations" width="444"/>



# Features
- **Gameplay Tracking**: Saves every movement in the game and allows the player to backtrack each step with the 'R' key, and drag boxes with the 'E' key.
- **Map Generation**: Generates new layouts for objects locations and ability to reset the map. 

# Installation
**Clone or download**
```bash
git clone https://github.com/brendonso/Sokoban.git
```
**To run this game, it requires you to install the SFML library.** 
```bash
sudo apt-get install libsfml-dev
```
**Compile in the projects folder**
```bash
make
```
**Run**
```bash
./Sokoban
```