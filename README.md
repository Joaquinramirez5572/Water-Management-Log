# Water Management Log

A C++ console application for tracking household water consumption, identifying usage trends, and encouraging sustainable water habits. The project is designed to help users log daily water usage, monitor consumption over time, and maintain conservation goals through persistent storage and simple data analysis.

## Overview

Water Management Log is a desktop application built in C++ that allows users to:
- record water usage entries
- track daily and cumulative consumption
- review usage patterns and statistics
- set conservation goals
- validate input to reduce data errors
- sort entries chronologically for better reporting

This project demonstrates object-oriented programming, file-based persistence, and practical software design for a utility application.

## Why This Project Matters

Household water usage often goes untracked, which makes it difficult to identify wasteful habits or compare consumption over time. This application gives users a structured way to log water data and understand usage patterns, helping support more efficient resource management and conservation.

## Features

- Persistent data storage using file I/O
- Water consumption statistics and summaries
- Conservation goal tracking
- Input validation for safer data entry
- Chronological sorting of log entries
- Entry management for adding, viewing, and organizing records
- Practical water-saving recommendations based on usage patterns

## Technical Stack

- Language: C++
- Programming Paradigm: Object-oriented programming
- Core Concepts: std::vector, std::sort, lambda expressions, file handling
- Design Approach: modular classes with separated responsibilities

## Application Design

The application is organized around a small set of core components:

- WaterLog: manages the overall log and user operations
- WaterEntry: represents an individual water usage record
- Data persistence layer: saves and reads log data from a local file
- Validation logic: ensures inputs are accurate and consistent
- Sorting and reporting logic: organizes entries and computes statistics

This structure keeps the program maintainable and demonstrates clean separation of responsibilities, which is important in object-oriented software design.

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
5. Enter and track water usage entries through the console interface.

## Example Workflow

- Add a new water usage entry
- Include the date, amount, and relevant notes
- View total consumption statistics
- Review trends over time
- Adjust habits to meet conservation goals

## Testing and Validation

The program includes validation checks to improve reliability and reduce user input errors. It also supports data persistence so records remain available across runs.

## Software Design Document

The full design document for this project is available in the repository:

[Ramirez, Joaquin - Software Design Document Water Log](./Ramirez%20Joaquin%20-%20Software%20Design%20Document%20Water%20Log.pdf)
