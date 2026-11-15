
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Student
{
public:
    int studentID;
    string name, fatherName, motherName, phone, state;
    string uniRollNo, course, branch;
    int age, year, roomNo;

    Student()
    {
        studentID = age = year = roomNo = 0;
    }

    void getStudentData()
    {
        cout << "Student ID: ";
        cin >> studentID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Name: ";
        getline(cin, name);
        cout << "Father's name: ";
        getline(cin, fatherName);
        cout << "Mother's name: ";
        getline(cin, motherName);
        cout << "Phone number: ";
        getline(cin, phone);
        cout << "State: ";
        getline(cin, state);
        cout << "University roll number: ";
        getline(cin, uniRollNo);
        cout << "Course: ";
        getline(cin, course);
        cout << "Branch: ";
        getline(cin, branch);
        cout << "Age: ";
        cin >> age;
        cout << "Current year: ";
        cin >> year;
    }

    void displayDetails() const
    {
        cout << "\nStudent ID: " << studentID
             << "\nName: " << name
             << "\nFather's name: " << fatherName
             << "\nMother's name: " << motherName
             << "\nPhone: " << phone
             << "\nState: " << state
             << "\nUniversity roll number: " << uniRollNo
             << "\nCourse: " << course
             << "\nBranch: " << branch
             << "\nAge: " << age
             << "\nCurrent year: " << year
             << "\nRoom number: " << roomNo << "\n";
    }
};

class Room
{
public:
    int roomNo, floor, capacity, occupiedBeds;

    Room()
    {
        roomNo = floor = capacity = occupiedBeds = 0;
    }

    void getData()
    {
        cout << "Room number: ";
        cin >> roomNo;
        cout << "Floor: ";
        cin >> floor;
        cout << "Capacity: ";
        cin >> capacity;
        cout << "Occupied beds: ";
        cin >> occupiedBeds;
    }

    void displayDetails() const
    {
        cout << "\nRoom number: " << roomNo
             << "\nFloor: " << floor
             << "\nCapacity: " << capacity
             << "\nOccupied beds: " << occupiedBeds
             << "\nAvailable beds: "
             << capacity - occupiedBeds << "\n";
    }
};

class DormEase
{
    // Encapsulation: Private data members
    vector<Student> students;
    vector<Room> rooms;

    int findStudentIndex(int id) const
    {
        for (int i = 0; i < (int)students.size(); i++)
            if (students[i].studentID == id)
                return i;
        return -1;
    }

    int findRollIndex(const string &roll) const
    {
        for (int i = 0; i < (int)students.size(); i++)
            if (students[i].uniRollNo == roll)
                return i;
        return -1;
    }

    int findRoomIndex(int roomNo) const
    {
        for (int i = 0; i < (int)rooms.size(); i++)
            if (rooms[i].roomNo == roomNo)
                return i;
        return -1;
    }

    bool allocateRoom(Student &s, int requestedRoom = 0)
    {
        int index = -1;

        if (requestedRoom != 0)
        {
            index = findRoomIndex(requestedRoom);

            if (index == -1 ||
                rooms[index].occupiedBeds >= rooms[index].capacity)
                return false;
        }
        else
        {
            for (int i = 0; i < (int)rooms.size(); i++)
            {
                if (rooms[i].occupiedBeds < rooms[i].capacity)
                {
                    index = i;
                    break;
                }
            }

            if (index == -1)
                return false;
        }

        rooms[index].occupiedBeds++;
        s.roomNo = rooms[index].roomNo;
        return true;
    }

public:
    // Adding student using vector
    void addStudent()
    {
        Student s;
        s.getStudentData();

        if (findStudentIndex(s.studentID) != -1 ||
            findRollIndex(s.uniRollNo) != -1)
        {
            cout << "Student already exists.\n";
            return;
        }

        int roomChoice;
        cout << "Enter preferred room number (0 for automatic allocation): ";
        cin >> roomChoice;

        if (!allocateRoom(s, roomChoice))
        {
            cout << "Room unavailable. Student not registered.\n";
            return;
        }

        students.push_back(s);
        cout << "Student registered successfully.\n";
    }

    // Displaying students using vector
    void displayStudents() const
    {
        if (students.empty())
        {
            cout << "No registered students.\n";
            return;
        }

        for (int i = 0; i < (int)students.size(); i++)
            students[i].displayDetails();
    }

    // Searching student using vector
    void searchStudent() const
    {
        int id;
        cout << "Enter student ID: ";
        cin >> id;

        int index = findStudentIndex(id);

        if (index == -1)
            cout << "Student not found.\n";
        else
            students[index].displayDetails();
    }

    // Updating student records using vector
    void updateStudent()
    {
        int id;
        cout << "Enter student ID: ";
        cin >> id;

        int index = findStudentIndex(id);

        if (index == -1)
        {
            cout << "Student not found.\n";
            return;
        }

        cout << "New phone number: ";
        cin >> students[index].phone;

        cout << "New course: ";
        cin >> students[index].course;

        cout << "New branch: ";
        cin >> students[index].branch;

        cout << "Student updated successfully.\n";
    }

    // Deleting student using vector
    void deleteStudent()
    {
        int id;
        cout << "Enter student ID to delete: ";
        cin >> id;

        int index = findStudentIndex(id);

        if (index == -1)
        {
            cout << "Student not found.\n";
            return;
        }

        int roomIndex = findRoomIndex(students[index].roomNo);

        if (roomIndex != -1)
            rooms[roomIndex].occupiedBeds--;

        students.erase(students.begin() + index);

        cout << "Student deleted successfully.\n";
    }

    // Adding room using vector
    void addRoom()
    {
        Room r;
        r.getData();

        if (findRoomIndex(r.roomNo) != -1)
        {
            cout << "Room already exists.\n";
            return;
        }

        if (r.capacity <= 0 || r.occupiedBeds < 0 ||
            r.occupiedBeds > r.capacity)
        {
            cout << "Invalid room details.\n";
            return;
        }

        rooms.push_back(r);
        cout << "Room added successfully.\n";
    }

    // Displaying rooms using vector
    void displayRooms() const
    {
        if (rooms.empty())
        {
            cout << "No rooms added.\n";
            return;
        }

        for (int i = 0; i < (int)rooms.size(); i++)
            rooms[i].displayDetails();
    }

    // Public interface for accessing private members
    void run()
    {
        int choice;

        do
        {
            cout << "\n===== DORMEASE =====\n"
                 << "1. Add Student\n"
                 << "2. Display Students\n"
                 << "3. Search Student\n"
                 << "4. Update Student\n"
                 << "5. Delete Student\n"
                 << "6. Add Room\n"
                 << "7. Display Rooms\n"
                 << "0. Exit\n"
                 << "Choice: ";

            cin >> choice;

            switch (choice)
            {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: addRoom(); break;
            case 7: displayRooms(); break;
            case 0: cout << "Thank you for using DormEase.\n"; break;
            default: cout << "Invalid choice.\n";
            }

        } while (choice != 0);
    }
};

int main()
{
    DormEase system;
    system.run();
    return 0;
}
