## Text Adventure
Text Adventure is a terminal-based dungeon crawler written in C where players explore a series of cave floors, battle monsters, and collect treasure using simple text commands.

### Features:
- Multi-floor dungeon exploration
- Turn-based combat system
- Randomized encounters and treasure
- Command-driven player movement and actions

### Technical Highlights:
- Dungeon floors implemented as 2D arrays of characters stored as double pointers within structs
- Multiple dungon floors managed through an array of struct pointers
- Player state managed by a struct containing combat ability, health, position, and inventory
- Modular architechture with seperate files for movement, maps, events, and combat

### Project Structure:
- textAdventure - main game loop and initialization
- textAMaps - map generation and storage
- textAEvents - encounters and events
- textAMove - handles character movement
- textACombat - combat mechanics

### Build and Run:

This project was built using GCC in the Cygwin terminal.

> gcc textAdventure.c textAMaps.c textAMove.c textACombat.c textAEvents.c -o game

> ./game

### What We Learned: 
- Designing data-driven systems using structs and pointers
- Utilizing dynamic memory in C
- Organizing a C project with seperate files
- Collaborating with a partner using GitHub
