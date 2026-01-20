Text Adventure is a dungeon crawler and adventure game written in C. Users can type simply commands to explore a series of cave floors, fight monsters, and search for treasure. 

The maps or dungeon floors of Text Adventure are 2D arrays of chars that are stored as double pointers in a struct. Each char of the dungeon arrays either correspond to a certain event or indicate an empty space. The instances of each struct (each dungeon floor) is then stored in an array of struct pointers. 

The player character is also managed by a struct. Each of the fields in the character struct correspond to their combat ability, health, location in the dungeon, and their gold. 

Code is separated by their purpose into multiple files: textAMove, textAMaps, textAEvents, textACombat, for clarity and better readability. Each file has a header and code files which are included in the main textAdventure file and compiled all together.
To compile, we used the cygwin terminal with the command, "gcc textAdventure.c textAMaps.c textAMove.c textACombat.c textAEvents.c -o game" The game is then run with the command "./game"
