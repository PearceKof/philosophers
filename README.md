# Philosophers
![42](https://img.shields.io/badge/School-42-black?style=flat-square&logo=42)

Philosophers is a simulation program implemented in C as part of a project at 19 (42 Network). The objective is to create a multithreaded (or multiprocessing) simulation of philosophers sitting at a round table, managing their eating, thinking, and sleeping states while avoiding starvation.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Logs](#logs)
- [Dependencies](#dependencies)

## Project Overview

The Philosophers project aims to deepen our understanding of threading, process synchronization, and inter-process communication in C. The program simulates a scenario where philosophers alternately eat spaghetti and think, while managing access to shared resources (forks) to prevent starvation.

## Features

- Multithreading or multiprocessing simulation of philosophers
- Forks represented as shared resources
- Proper management of philosopher states (eating, thinking, sleeping)
- Avoids deadlocks and ensures no philosopher starves
- Logs state changes with timestamps for monitoring

## Requirements

- All the requirements for this project are outlined in the project description.
- Language: C, following the Norm.
- Memory Management: All allocated memory must be properly freed, and no memory leaks are tolerated.
- Makefile: The project must include a Makefile with at least the following rules: all, clean, fclean, re, and $(NAME).
- Compilation: Use `cc` with the flags `-Wall`, `-Wextra`, and `-Werror`.
- Global variables are forbidden.
- External functions: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock` for the mandatory part, and additional functions for the bonus part.

## Installation

To build and run Philosophers, you need a C compiler and `make`. This program is compatible with Unix-like systems.

1. Clone the repository:

```
git clone https://github.com/yourusername/philosophers.git
```

2. Go in the cloned repository:

```
cd philosophers
```

3. Build the project:

```
make
```

4. The Makefile includes the following targets:
- `all`: Compiles the project
- `clean`: Removes object files
- `fclean`: Removes object files and the executable
- `re`: Rebuilds the project

## Usage

After building the program, you can start it by running:

```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat OPTIONAL]
```
```
./philo 10 1000 200 300 5
```
This will initiate the simulation with the specified parameters.

## Logs

Any state change of a philosopher will be logged in the following format:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

Where `timestamp_in_ms` is the current timestamp in milliseconds and `X` is the philosopher number.

## Dependencies

Philosophers relies solely on the C standard library and system calls. It does not require any external libraries.

