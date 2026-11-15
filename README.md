# 🏠 DormEase – Student Accommodation System

DormEase is a C++-based application developed to simplify and organise student accommodation-related operations. It provides a structured platform for handling student records, room allocation, attendance, complaints, leave requests, and waiting lists.

## 📌 Project Overview

Managing student accommodation activities manually can be time-consuming and may lead to errors, duplication of records, and difficulties in tracking student information.

DormEase aims to address these challenges through an integrated application that applies Object-Oriented Programming principles and Data Structures in C++.

## 🎯 Problem Statement

Traditional methods of maintaining accommodation records often involve separate manual processes for student details, room assignments, attendance, complaints, and leave requests. These processes can make information difficult to organise and retrieve.

DormEase provides a centralised application to organise these operations, maintain student records, and make accommodation-related activities easier to handle.

## ✨ Key Features

- Student registration and record management
- Room creation and allocation
- Waiting list management
- Student attendance tracking
- Complaint registration and tracking
- Leave request management
- Student record deletion and undo functionality
- Administrator login and dashboard
- Student login and portal

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Programming Standard:** C++11 or later, depending on compiler compatibility
- **Core Concepts:** Object-Oriented Programming
- **Data Structures:** Arrays, Stack, Queue, and Linked List
- **Development Environment:** Visual Studio Code / Any C++ compatible IDE
- **Compiler:** GCC (g++)

## 📚 Object-Oriented Programming Concepts

DormEase uses Object-Oriented Programming to structure its components and organise application functionality.

- **Classes and Objects:** Represent application entities such as students, administrators, rooms, and attendance records.
- **Encapsulation:** Groups related data and operations within classes. Some data members are public in the current implementation.
- **Modularity:** Separates different operations into individual classes and source files for better organisation.
- **Abstraction:** Provides methods to perform specific operations without requiring the user to handle their internal implementation.

## 🔗 Data Structures Implemented

| Data Structure | Application |
|---|---|
| Array | Student records and room-related operations |
| Stack | Maintaining deleted student records for undo functionality |
| Queue | Managing students waiting for room availability |
| Linked List | Managing complaints, leave requests, and other records |

## 📂 Project Structure

```text
DormEase/
│
├── Dormease.cpp
├── ArrayDhruv.cpp
├── StackAditi.cpp
├── QueueAbhinav.cpp
├── LinkedListAman.cpp
├── PBL2.cpp
└── README.md
```

### File Descriptions

- `Dormease.cpp` – Main integrated application containing the core functionality.
- `ArrayDhruv.cpp` – Array-based implementation.
- `StackAditi.cpp` – Stack implementation for undo operations.
- `QueueAbhinav.cpp` – Queue implementation for waiting list operations.
- `LinkedListAman.cpp` – Linked list implementation for complaint and leave-related operations.
- `PBL2.cpp` – Additional project source file.

## ▶️ How to Compile and Run

A C++ compiler such as GCC is required.

If `Dormease.cpp` contains the complete integrated application, compile it using:

```bash
g++ -std=c++11 Dormease.cpp -o DormEase
```

Run on Linux:

```bash
./DormEase
```

Run on Windows:

```bash
DormEase.exe
```

**Note:** The separate module files are included as individual implementations. The integrated application should be compiled using the appropriate source file and build instructions.

## 🔐 Administrator Login

The application provides an administrator login facility to access administrative operations.

Demonstration login credentials can be added here after verifying them in the current source code.

## 👥 Team Members and Contributions

| Team Member | Contribution |
|---|---|
| Dhruv | Array-based implementation and room-related operations |
| Aditi | Stack implementation and undo functionality |
| Abhinav | Queue implementation and waiting list operations |
| Aman | Linked list implementation for complaint and leave operations |

The team collaborated on integrating the individual modules, connecting application functionalities, testing, and debugging the overall system.

## 🚀 Future Scope

- Improved input validation and error handling.
- Enhanced authentication and access control.
- Permanent storage of student and accommodation records.
- Improved user interface and navigation.
- More efficient room allocation and waiting list operations.
- Report generation and notification features.

## 📌 Project Status

DormEase is an academic C++ project demonstrating the practical implementation of Object-Oriented Programming and Data Structures through a student accommodation application.

---

**Developed as a team project using C++.**
