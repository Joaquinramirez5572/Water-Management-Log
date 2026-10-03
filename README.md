# Water Management Log

A C++ console application for tracking household water usage and identifying patterns over time. The program helps users log daily consumption, review totals, and support water conservation habits.

## Overview

- Record water usage entries
- Track cumulative consumption over time
- View usage summaries and trends
- Set water conservation goals

This project demonstrates object-oriented programming, file persistence, and practical utility application design.

## Why This Project Matters

Water usage often goes untracked, making it hard to notice wasteful habits. This application gives users a structured way to log water use and review patterns so they can reduce unnecessary consumption.

## Features

- Persistent storage using file I/O
- Water usage summaries and totals
- Goal tracking for conservation
- Input validation and chronological sorting

## Technical Stack

- Language: C++
- Programming Paradigm: Object-oriented programming
- Core Concepts: vectors, sorting, file handling, input validation
- Design Approach: modular classes with clear responsibilities

## Application Design

- WaterLog: manages the main log and actions
- WaterEntry: stores one water usage entry
- Persistence Layer: saves and reads data from a file
- Reporting Logic: calculates totals and shows trends

This design keeps the application maintainable and easier to extend with new features.

## Project Structure

```text
Water-Management-Log/
├── main.cpp
├── WaterLog.h
├── WaterLog.cpp
├── WaterEntry.h
├── WaterEntry.cpp
├── data.txt
├── README.md
└── Ramirez Joaquin - Software Design Document Water Log.pdf
```

## How to Run

1. Clone the repository.
2. Open the project in Visual Studio.
3. Build the solution.
4. Run the application.
5. Use the console menu to log and review water data.

## Example Workflow

- Add a new water usage entry
- View total consumption statistics
- Review usage patterns over time
- Adjust habits to meet conservation goals

## Testing and Validation

The program includes validation checks to reduce input errors and confirm that saved records remain available across runs. It also supports accurate summaries and sorting so reported trends are consistent.

## Software Design Document

The full design document for this project is available in the repository:

[Ramirez, Joaquin - Software Design Document Water Log](./Ramirez%20Joaquin%20-%20Software%20Design%20Document%20Water%20Log.pdf)
