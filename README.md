# Dining Philosophers Project

## Table of Contents
1. [Introduction: The Philosophers' Story](#introduction-the-philosophers-story)
2. [Understanding Threads and Mutexes](#understanding-threads-and-mutexes)
3. [Purpose of the Project](#purpose-of-the-project)
4. [Project Rules](#project-rules)
5. [Implementation Overview](#implementation-overview)

---

## Introduction: The Philosophers' Story

The "Dining Philosophers" problem is a classic synchronization issue used to illustrate the challenges of concurrent resource allocation. Imagine a group of philosophers sitting at a circular table. In front of each philosopher, there is a bowl of spaghetti, and between each pair of philosophers, there is one fork. A philosopher must pick up both forks (one on their left and one on their right) to eat. Philosophers alternate between eating, thinking, and sleeping. They must ensure that they do not starve and avoid deadlocks, where no one can eat.

Key rules in this scenario include:
- Philosophers do not communicate with each other.
- A philosopher can only eat when they have both forks.
- The simulation ends when a philosopher dies due to starvation.

## Understanding Threads and Mutexes

- **Threads**: Threads are the smallest unit of a process that can be scheduled for execution. They allow parallel execution within a program, making it possible for multiple tasks to run simultaneously.
- **Mutexes (Mutual Exclusion)**: A mutex is a synchronization primitive used to protect shared data from being accessed by multiple threads at the same time. It ensures that only one thread can access a critical section of code, which prevents race conditions and maintains data consistency.

In this project, threads represent the philosophers, while mutexes ensure that forks (shared resources) are accessed safely, preventing data races and deadlocks.

## Purpose of the Project

The primary aim of this project is to explore threading, synchronization mechanisms, and resource management in concurrent programming. By simulating the dining philosophers, you will gain practical experience with creating threads, using mutexes, and implementing robust synchronization techniques.

## Project Rules

1. The project must be implemented in C.
2. Global variables are forbidden.
3. The program should be executed with the following parameters:
- `number_of_philosophers`: Number of philosophers and forks.
- `time_to_die`: Maximum time a philosopher can go without eating.
- `time_to_eat`: Time spent eating (requires holding both forks).
- `time_to_sleep`: Time spent sleeping after eating.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops once all philosophers have eaten at least this many times.

4. Key functional rules:
- Each philosopher is represented as a thread.
- Each fork is protected with a mutex to ensure proper access.
- The simulation stops when a philosopher dies.
- State changes (e.g., eating, thinking, taking a fork, etc.) must be printed with timestamps.

5. Logs for each philosopher state change must be formatted as:
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
Replace `X` with the philosopher number and `timestamp_in_ms` with the current timestamp.

## Implementation Overview

### Basic Structure
- Each philosopher is represented by a thread.
- Forks are represented by mutexes, one for each fork.
- Philosophers attempt to pick up their left and right forks (mutexes) before eating.
- After eating, a philosopher releases the forks (unlocks the mutexes) and enters a sleeping state.

### Key Components
1. **Main Program**: Initializes philosophers, forks, and handles simulation logic.
2. **Thread Handling**: Each philosopher is a separate thread that handles their life cycle (eating, sleeping, thinking).
3. **Mutex Locking**: Ensures safe access to forks and prevents race conditions or deadlocks.

### Key Functions and Tools Used
- `pthread_create`, `pthread_mutex_init`, `pthread_mutex_lock`, and `pthread_mutex_unlock` to manage threads and mutexes.
- Timing functions to monitor philosopher actions and detect starvation.

---

