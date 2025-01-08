Multithreaded Space System Simulation

This project is a multithreaded simulation of a space system, where different subsystems operate concurrently, sharing and managing critical resources such as fuel and oxygen.
A central manager oversees the entire operation, ensuring smooth resource allocation and system synchronization. 
The simulation demonstrates concepts like multithreading, resource management, event handling, and dynamic data structures.

I) Overview

The simulation consists of various subsystems such as propulsion, life support, and energy generation. 
These subsystems consume and produce resources, with their operations managed by a central event-driven mechanism. 
The simulation is designed to run until a defined goal (e.g., reaching a destination) or critical failure (e.g., resource depletion) occurs.

II) Features

 - Concurrent Subsystems: Each system runs on its own thread, simulating real-world multitasking.

 - Shared Resource Management: Resources such as fuel and oxygen are shared among subsystems, with semaphores ensuring safe access.

 - Priority-Based Event Queue: Critical events are handled based on their priority to ensure the stability of the system.

 - Dynamic Resource Allocation: Arrays dynamically resize to accommodate additional systems or resources as needed.

 - Live Simulation Display: Real-time updates on system statuses and resource levels are displayed to the console.

III) How It Works

- Initialization:
   The manager initializes all resources, systems, and the event queue. Subsystems are configured with their resource consumption and production rates.

- Subsystem Operations:
   Each system runs in its own thread, consuming input resources and producing output resources. If resources are insufficient, the system generates an event, notifying the manager.

- Event Handling:
   Events are added to a priority queue, ensuring critical issues are addressed first. The manager processes these events and adjusts subsystem behaviors (e.g., speeding up, slowing down, or stopping).

- Simulation End:
   The simulation ends when critical conditions are met, such as oxygen depletion or reaching the destination.

IV) File Structure

project-directory
 - defs.h: Global definitions and data structures
 - main.c: Entry point of the simulation
 - manager.c: Handles overall simulation management
 - system.c: Implements subsystem behaviors
 - resource.c: Manages resources and their allocation
 - event.c: Handles event creation and the event queue
 - Makefile: Automates the build process

V) Technologies Used

 - C Programming Language: Core implementation of the simulation.

 - POSIX Threads: Enables multithreading for concurrent subsystem operations.

 - Semaphores: Ensures thread-safe access to shared resources.

 - GCC Compiler: Used to build the project.

VI) Acknowledgments

Developed by Daryll Giovanny Bikak Mbal as part of the COMP2401 coursework.

Special thanks to the teaching team and resources provided during the course.
