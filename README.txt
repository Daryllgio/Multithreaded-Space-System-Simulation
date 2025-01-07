Student Name: Daryll Giovanny Bikak Mbal
Student Number: 101319027

## Multithreaded Treasure HHunt
This project implements a multi-threaded space system simulation where differebnt systems (like engines and life support)
that share resources like fule and oxygen. Each system runs on its own thread and, there's a manger keeping an eye on 
everything 

## Features
	- Every system runs at the same time (multi-threading)
	- Systems share resources and talk to each other 
	- Priority-based message system for important events
	- Live display of what's happening 
	- Safe resource sharing between threads 
	- Smart storage systems that grow when needed
	 

## Building and Running 
1. Open the terminal and navigate to the comp2401-project2-provided.tar folder containing the files
2. Compile the main.c, event.c, system.c, resource.c, and manager.c programs using GCC with the command: gcc -o ./project2 main.c, event.c,system.c, resource.c and manager.c . 
3. Run the compiled program by typing ./project2 on the terminal. 

## Program Structure
 - Makefile: Helps build the project 
 - defs.h: Allthe important definitions
 - main.c: Where everything starts 
 - manager.c: The brain of the operation
 - resource.c: Handles all the resources
 - system.c: Makes the systems work
 - event.c: Handles communication



## Credits 
Developed individually by Me (101319027)
Used ChatGPT for error handling and clarifications.
