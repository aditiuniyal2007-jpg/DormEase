#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// ===================== BASE USER CLASS =====================
class User
{
public:
    virtual void showRole() = 0;
    virtual ~User() {}
};

// ===================== STUDENT CLASS =====================
class Student : public User
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
             << "\nRoom number: ";

        if (roomNo == 0)
            cout << "Waiting for room";
        else
            cout << roomNo;
        cout << "\n";
    }

    void showRole()
    {
        cout << "Student";
    }
};

// ===================== ADMIN CLASS =====================
class Admin : public User
{
public:
    void showRole()
    {
        cout << "Administrator";
    }
};

// ===================== ROOM CLASS =====================
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
             << "\nAvailable beds: " << capacity - occupiedBeds << "\n";
    }
};

// ===================== STACK FOR UNDO =====================
class StudentStack
{
    struct Node
    {
        Student data;
        Node *next;
    };
    Node *top;

public:
    StudentStack() { top = NULL; }

    bool isEmpty() const { return top == NULL; }

    void push(const Student &s)
    {
        Node *newNode = new Node;
        newNode->data = s;
        newNode->next = top;
        top = newNode;
    }

    bool pop(Student &s)
    {
        if (isEmpty())
            return false;

        Node *temp = top;
        s = temp->data;
        top = top->next;
        delete temp;
        return true;
    }

    ~StudentStack()
    {
        Student s;
        while (pop(s)) {}
    }
};

// ===================== QUEUE FOR WAITING LIST =====================
class WaitingQueue
{
    struct QueueNode
    {
        Student data;
        QueueNode *next;
    };
    QueueNode *front;
    QueueNode *rear;

public:
    WaitingQueue() { front = rear = NULL; }

    bool isEmpty() const { return front == NULL; }

    void enqueue(const Student &s)
    {
        QueueNode *newNode = new QueueNode;
        newNode->data = s;
        newNode->next = NULL;

        if (isEmpty())
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool dequeue(Student &s)
    {
        if (isEmpty())
            return false;

        QueueNode *temp = front;
        s = temp->data;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;
        return true;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Waiting list is empty.\n";
            return;
        }

        QueueNode *temp = front;
        cout << "\n--- Waiting Students (FIFO) ---\n";
        while (temp != NULL)
        {
            cout << "ID: " << temp->data.studentID
                 << " | Name: " << temp->data.name
                 << " | Roll: " << temp->data.uniRollNo << "\n";
            temp = temp->next;
        }
    }

    ~WaitingQueue()
    {
        Student s;
        while (dequeue(s)) {}
    }
};

// ===================== COMPLAINT LINKED LIST =====================
class ComplaintManager
{
    struct Node
    {
        int complaintID, studentID, roomNo;
        string description;
        Node *next;
    };
    Node *head;

public:
    ComplaintManager() { head = NULL; }

    bool addComplaint(int id, int student, int room, const string &description)
    {
        if (searchComplaint(id, false))
        {
            cout << "Complaint ID already exists.\n";
            return false;
        }

        Node *newNode = new Node;
        newNode->complaintID = id;
        newNode->studentID = student;
        newNode->roomNo = room;
        newNode->description = description;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
        cout << "Complaint added successfully.\n";
        return true;
    }

    void displayComplaints() const
    {
        if (head == NULL)
        {
            cout << "No complaints found.\n";
            return;
        }

        Node *temp = head;
        while (temp != NULL)
        {
            cout << "\nComplaint ID: " << temp->complaintID
                 << "\nStudent ID: " << temp->studentID
                 << "\nRoom number: " << temp->roomNo
                 << "\nDescription: " << temp->description
                 << "\n-------------------------\n";
            temp = temp->next;
        }
    }

    bool searchComplaint(int id, bool show = true) const
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->complaintID == id)
            {
                if (show)
                    cout << "\nFound: Complaint ID " << temp->complaintID
                         << ", Student ID " << temp->studentID
                         << ", Room " << temp->roomNo
                         << "\nDescription: " << temp->description << "\n";
                return true;
            }
            temp = temp->next;
        }
        if (show)
            cout << "Complaint not found.\n";
        return false;
    }

    bool deleteComplaint(int id)
    {
        Node *temp = head, *previous = NULL;
        while (temp != NULL && temp->complaintID != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Complaint not found.\n";
            return false;
        }

        if (previous == NULL)
            head = head->next;
        else
            previous->next = temp->next;

        delete temp;
        cout << "Complaint deleted.\n";
        return true;
    }

    ~ComplaintManager()
    {
        while (head != NULL)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ===================== LEAVE REQUEST LINKED LIST =====================
class LeaveManager
{
    struct Node
    {
        int requestID, studentID, roomNo;
        string reason, fromDate, toDate;
        Node *next;
    };
    Node *head;

public:
    LeaveManager() { head = NULL; }

    bool addRequest(int id, int student, int room, string reason,
                    string fromDate, string toDate)
    {
        if (searchRequest(id, false))
        {
            cout << "Leave request ID already exists.\n";
            return false;
        }

        Node *newNode = new Node;
        newNode->requestID = id;
        newNode->studentID = student;
        newNode->roomNo = room;
        newNode->reason = reason;
        newNode->fromDate = fromDate;
        newNode->toDate = toDate;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
        cout << "Leave request submitted.\n";
        return true;
    }

    void displayRequests() const
    {
        if (head == NULL)
        {
            cout << "No leave requests found.\n";
            return;
        }

        Node *temp = head;
        while (temp != NULL)
        {
            cout << "\nRequest ID: " << temp->requestID
                 << "\nStudent ID: " << temp->studentID
                 << "\nRoom number: " << temp->roomNo
                 << "\nReason: " << temp->reason
                 << "\nFrom: " << temp->fromDate
                 << "\nTo: " << temp->toDate
                 << "\n-------------------------\n";
            temp = temp->next;
        }
    }

    bool searchRequest(int id, bool show = true) const
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->requestID == id)
            {
                if (show)
                    cout << "\nRequest found. Student ID: " << temp->studentID
                         << ", Room: " << temp->roomNo
                         << "\nReason: " << temp->reason
                         << "\nFrom: " << temp->fromDate
                         << "\nTo: " << temp->toDate << "\n";
                return true;
            }
            temp = temp->next;
        }
        if (show)
            cout << "Leave request not found.\n";
        return false;
    }

    bool deleteRequest(int id)
    {
        Node *temp = head, *previous = NULL;
        while (temp != NULL && temp->requestID != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Leave request not found.\n";
            return false;
        }

        if (previous == NULL)
            head = head->next;
        else
            previous->next = temp->next;

        delete temp;
        cout << "Leave request deleted.\n";
        return true;
    }

    ~LeaveManager()
    {
        while (head != NULL)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ===================== ATTENDANCE =====================
class AttendanceRecord
{
public:
    int studentID;
    string date;
    char status;
};

// ===================== MAIN DORMEASE SYSTEM =====================
class DormEase
{
    vector<Student> students;
    vector<Room> rooms;
    vector<AttendanceRecord> attendance;
    StudentStack deletedStudents;
    WaitingQueue waitingList;
    ComplaintManager complaints;
    LeaveManager leaves;

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
            if (index == -1)
            {
                cout << "Room does not exist.\n";
                return false;
            }
            if (rooms[index].occupiedBeds >= rooms[index].capacity)
            {
                cout << "This room is full.\n";
                return false;
            }
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

    void assignWaitingStudents()
    {
        Student s;
        while (!waitingList.isEmpty())
        {
            int available = -1;
            for (int i = 0; i < (int)rooms.size(); i++)
            {
                if (rooms[i].occupiedBeds < rooms[i].capacity)
                {
                    available = i;
                    break;
                }
            }

            if (available == -1)
                break;

            waitingList.dequeue(s);
            rooms[available].occupiedBeds++;
            s.roomNo = rooms[available].roomNo;
            students.push_back(s);
            cout << "Room " << s.roomNo << " allocated to waiting student "
                 << s.name << ".\n";
        }
    }

    void addStudent()
    {
        Student s;
        s.getStudentData();

        if (findStudentIndex(s.studentID) != -1 || findRollIndex(s.uniRollNo) != -1)
        {
            cout << "Student ID or university roll number already exists.\n";
            return;
        }

        int roomChoice;
        cout << "Enter preferred room number (0 for automatic allocation): ";
        cin >> roomChoice;

        // Students already in the queue must get the next available beds first.
        if (!waitingList.isEmpty())
        {
            s.roomNo = 0;
            waitingList.enqueue(s);
            cout << "A waiting list already exists. Student added at the end of the queue.\n";
            return;
        }

        if (roomChoice == 0)
        {
            if (!allocateRoom(s))
            {
                s.roomNo = 0;
                waitingList.enqueue(s);
                cout << "No rooms available. Student added to waiting list.\n";
            }
        }
        else if (!allocateRoom(s, roomChoice))
        {
            cout << "Student was not registered. Correct the room choice and try again.\n";
            return;
        }

        students.push_back(s);
        cout << "Student registered successfully.\n";
    }

    void displayStudents() const
    {
        if (students.empty())
        {
            cout << "No registered students.\n";
            return;
        }
        for (int i = 0; i < (int)students.size(); i++)
        {
            cout << "\n========== STUDENT " << i + 1 << " ==========";
            students[i].displayDetails();
        }
    }

    void searchStudent() const
    {
        int choice;
        cout << "1. Search by Student ID\n2. Search by University Roll Number\n3. Search by Name\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            cout << "Enter student ID: ";
            cin >> id;
            int index = findStudentIndex(id);
            if (index == -1) cout << "Student not found.\n";
            else students[index].displayDetails();
        }
        else if (choice == 2)
        {
            string roll;
            cout << "Enter university roll number: ";
            cin >> roll;
            int index = findRollIndex(roll);
            if (index == -1) cout << "Student not found.\n";
            else students[index].displayDetails();
        }
        else if (choice == 3)
        {
            string name;
            cout << "Enter name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            bool found = false;
            for (int i = 0; i < (int)students.size(); i++)
            {
                if (students[i].name == name)
                {
                    students[i].displayDetails();
                    found = true;
                }
            }
            if (!found) cout << "Student not found.\n";
        }
        else cout << "Invalid choice.\n";
    }

    void updateStudent()
    {
        int id;
        cout << "Enter student ID to update: ";
        cin >> id;
        int index = findStudentIndex(id);
        if (index == -1)
        {
            cout << "Student not found.\n";
            return;
        }

        int choice;
        cout << "1. Update phone number\n2. Update course and branch\n3. Change room\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "New phone number: ";
            cin >> students[index].phone;
        }
        else if (choice == 2)
        {
            cout << "New course: ";
            cin >> students[index].course;
            cout << "New branch: ";
            cin >> students[index].branch;
        }
        else if (choice == 3)
        {
            int newRoom;
            cout << "Enter new room number: ";
            cin >> newRoom;
            int roomIndex = findRoomIndex(newRoom);
            if (roomIndex == -1)
            {
                cout << "Room not found.\n";
                return;
            }
            if (rooms[roomIndex].occupiedBeds >= rooms[roomIndex].capacity)
            {
                cout << "Room is full.\n";
                return;
            }

            int oldRoomIndex = findRoomIndex(students[index].roomNo);
            if (oldRoomIndex != -1)
                rooms[oldRoomIndex].occupiedBeds--;

            rooms[roomIndex].occupiedBeds++;
            students[index].roomNo = newRoom;
            assignWaitingStudents();
        }
        else cout << "Invalid choice.\n";
    }

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

        Student deleted = students[index];
        deletedStudents.push(deleted);

        int roomIndex = findRoomIndex(deleted.roomNo);
        if (roomIndex != -1)
            rooms[roomIndex].occupiedBeds--;

        students.erase(students.begin() + index);
        cout << "Student deleted. Undo is available.\n";
        assignWaitingStudents();
    }

    void undoDelete()
    {
        Student s;
        if (!deletedStudents.pop(s))
        {
            cout << "No deleted student available to restore.\n";
            return;
        }

        if (findStudentIndex(s.studentID) != -1 || findRollIndex(s.uniRollNo) != -1)
        {
            cout << "Cannot restore: student ID or roll number already exists.\n";
            deletedStudents.push(s);
            return;
        }

        if (s.roomNo != 0 && allocateRoom(s, s.roomNo))
        {
            // Restored to the previous room.
        }
        else if (allocateRoom(s))
        {
            cout << "Previous room unavailable. Student assigned another room.\n";
        }
        else
        {
            s.roomNo = 0;
            waitingList.enqueue(s);
            cout << "No room available. Restored student added to waiting list.\n";
        }

        students.push_back(s);
        cout << "Student record restored.\n";
    }

    void studentMenu()
    {
        int choice;
        do
        {
            cout << "\n===== STUDENT MANAGEMENT =====\n"
                 << "1. Register student\n2. Display all students\n"
                 << "3. Search student\n4. Update student\n"
                 << "5. Delete student\n6. Undo deleted student\n0. Back\nChoice: ";
            cin >> choice;

            switch (choice)
            {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: undoDelete(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void addRoom()
    {
        Room r;
        r.getData();
        if (findRoomIndex(r.roomNo) != -1)
        {
            cout << "Room number already exists.\n";
            return;
        }
        if (r.capacity <= 0 || r.occupiedBeds < 0 ||
            r.occupiedBeds > r.capacity)
        {
            cout << "Invalid room capacity or occupied-bed count.\n";
            return;
        }
        rooms.push_back(r);
        cout << "Room added successfully.\n";
        assignWaitingStudents();
    }

    void roomMenu()
    {
        int choice;
        do
        {
            cout << "\n===== ROOM MANAGEMENT =====\n"
                 << "1. Add room\n2. Display all rooms\n"
                 << "3. Search room\n4. Allocate next waiting student\n0. Back\nChoice: ";
            cin >> choice;

            if (choice == 1)
                addRoom();
            else if (choice == 2)
            {
                if (rooms.empty()) cout << "No rooms added.\n";
                for (int i = 0; i < (int)rooms.size(); i++)
                    rooms[i].displayDetails();
            }
            else if (choice == 3)
            {
                int no;
                cout << "Enter room number: ";
                cin >> no;
                int index = findRoomIndex(no);
                if (index == -1) cout << "Room not found.\n";
                else rooms[index].displayDetails();
            }
            else if (choice == 4)
                assignWaitingStudents();
            else if (choice != 0)
                cout << "Invalid choice.\n";
        } while (choice != 0);
    }

    void attendanceMenu()
    {
        int choice;
        do
        {
            cout << "\n===== ATTENDANCE MANAGEMENT =====\n"
                 << "1. Mark attendance\n2. Display all attendance\n"
                 << "3. Display attendance of a student\n0. Back\nChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                int id;
                string date;
                char status;
                cout << "Student ID: ";
                cin >> id;
                if (findStudentIndex(id) == -1)
                {
                    cout << "Student is not registered.\n";
                    continue;
                }
                cout << "Date (DD-MM-YYYY): ";
                cin >> date;

                bool duplicate = false;
                for (int i = 0; i < (int)attendance.size(); i++)
                    if (attendance[i].studentID == id && attendance[i].date == date)
                        duplicate = true;

                if (duplicate)
                {
                    cout << "Attendance already marked for this student on this date.\n";
                    continue;
                }

                cout << "Enter P for Present or A for Absent: ";
                cin >> status;
                if (status != 'P' && status != 'p' && status != 'A' && status != 'a')
                {
                    cout << "Invalid attendance status.\n";
                    continue;
                }

                AttendanceRecord record;
                record.studentID = id;
                record.date = date;
                record.status = (status == 'p' || status == 'P') ? 'P' : 'A';
                attendance.push_back(record);
                cout << "Attendance recorded.\n";
            }
            else if (choice == 2)
            {
                if (attendance.empty()) cout << "No attendance records.\n";
                for (int i = 0; i < (int)attendance.size(); i++)
                    cout << "Student ID: " << attendance[i].studentID
                         << " | Date: " << attendance[i].date
                         << " | Status: " << attendance[i].status << "\n";
            }
            else if (choice == 3)
            {
                int id;
                cout << "Enter student ID: ";
                cin >> id;
                if (findStudentIndex(id) == -1)
                {
                    cout << "Student not found.\n";
                    continue;
                }
                bool found = false;
                for (int i = 0; i < (int)attendance.size(); i++)
                {
                    if (attendance[i].studentID == id)
                    {
                        cout << "Date: " << attendance[i].date
                             << " | Status: " << attendance[i].status << "\n";
                        found = true;
                    }
                }
                if (!found) cout << "No attendance records for this student.\n";
            }
            else if (choice != 0)
                cout << "Invalid choice.\n";
        } while (choice != 0);
    }

    void waitingMenu()
    {
        int choice;
        do
        {
            cout << "\n===== WAITING LIST =====\n"
                 << "1. Display waiting list\n2. Allocate available rooms\n0. Back\nChoice: ";
            cin >> choice;
            if (choice == 1) waitingList.display();
            else if (choice == 2) assignWaitingStudents();
            else if (choice != 0) cout << "Invalid choice.\n";
        } while (choice != 0);
    }

    void complaintMenu()
    {
        int choice;
        do
        {
            cout << "\n===== COMPLAINT MANAGEMENT =====\n"
                 << "1. Add complaint\n2. Display complaints\n"
                 << "3. Search complaint\n4. Delete complaint\n0. Back\nChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                int id, studentID;
                string description;
                cout << "Complaint ID: ";
                cin >> id;
                cout << "Student ID: ";
                cin >> studentID;
                int index = findStudentIndex(studentID);
                if (index == -1)
                {
                    cout << "Student not found.\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Description: ";
                getline(cin, description);
                complaints.addComplaint(id, studentID, students[index].roomNo, description);
            }
            else if (choice == 2) complaints.displayComplaints();
            else if (choice == 3)
            {
                int id;
                cout << "Complaint ID: ";
                cin >> id;
                complaints.searchComplaint(id);
            }
            else if (choice == 4)
            {
                int id;
                cout << "Complaint ID: ";
                cin >> id;
                complaints.deleteComplaint(id);
            }
            else if (choice != 0) cout << "Invalid choice.\n";
        } while (choice != 0);
    }

    void leaveMenu()
    {
        int choice;
        do
        {
            cout << "\n===== LEAVE REQUEST MANAGEMENT =====\n"
                 << "1. Submit leave request\n2. Display requests\n"
                 << "3. Search request\n4. Delete request\n0. Back\nChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                int id, studentID;
                string reason, fromDate, toDate;
                cout << "Request ID: ";
                cin >> id;
                cout << "Student ID: ";
                cin >> studentID;
                int index = findStudentIndex(studentID);
                if (index == -1)
                {
                    cout << "Student not found.\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Reason: ";
                getline(cin, reason);
                cout << "From date (DD-MM-YYYY): ";
                getline(cin, fromDate);
                cout << "To date (DD-MM-YYYY): ";
                getline(cin, toDate);
                leaves.addRequest(id, studentID, students[index].roomNo,
                                  reason, fromDate, toDate);
            }
            else if (choice == 2) leaves.displayRequests();
            else if (choice == 3)
            {
                int id;
                cout << "Request ID: ";
                cin >> id;
                leaves.searchRequest(id);
            }
            else if (choice == 4)
            {
                int id;
                cout << "Request ID: ";
                cin >> id;
                leaves.deleteRequest(id);
            }
            else if (choice != 0) cout << "Invalid choice.\n";
        } while (choice != 0);
    }

    void adminMenu()
    {
        int choice;
        do
        {
            cout << "\n========== DORMEASE ADMIN ==========\n"
                 << "1. Student management\n2. Room management\n"
                 << "3. Attendance management\n4. Waiting list\n"
                 << "5. Complaint management\n6. Leave request management\n0. Logout\nChoice: ";
            cin >> choice;

            switch (choice)
            {
            case 1: studentMenu(); break;
            case 2: roomMenu(); break;
            case 3: attendanceMenu(); break;
            case 4: waitingMenu(); break;
            case 5: complaintMenu(); break;
            case 6: leaveMenu(); break;
            case 0: cout << "Logged out.\n"; break;
            default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void studentLogin()
    {
        string roll;
        int id;
        cout << "University roll number: ";
        cin >> roll;
        cout << "Student ID: ";
        cin >> id;

        int index = findStudentIndex(id);
        if (index == -1 || students[index].uniRollNo != roll)
        {
            cout << "Invalid student login details.\n";
            return;
        }

        int choice;
        do
        {
            cout << "\n========== STUDENT PORTAL ==========\n"
                 << "1. View my details\n2. View my room\n"
                 << "3. View my attendance\n4. Submit complaint\n"
                 << "5. Submit leave request\n0. Logout\nChoice: ";
            cin >> choice;

            if (choice == 1)
                students[index].displayDetails();
            else if (choice == 2)
            {
                if (students[index].roomNo == 0)
                    cout << "You are currently in the waiting list.\n";
                else
                {
                    int r = findRoomIndex(students[index].roomNo);
                    if (r != -1) rooms[r].displayDetails();
                }
            }
            else if (choice == 3)
            {
                bool found = false;
                for (int i = 0; i < (int)attendance.size(); i++)
                    if (attendance[i].studentID == id)
                    {
                        cout << "Date: " << attendance[i].date
                             << " | Status: " << attendance[i].status << "\n";
                        found = true;
                    }
                if (!found) cout << "No attendance records found.\n";
            }
            else if (choice == 4)
            {
                int complaintID;
                string description;
                cout << "Complaint ID: ";
                cin >> complaintID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Description: ";
                getline(cin, description);
                complaints.addComplaint(complaintID, id, students[index].roomNo, description);
            }
            else if (choice == 5)
            {
                int requestID;
                string reason, fromDate, toDate;
                cout << "Request ID: ";
                cin >> requestID;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Reason: ";
                getline(cin, reason);
                cout << "From date (DD-MM-YYYY): ";
                getline(cin, fromDate);
                cout << "To date (DD-MM-YYYY): ";
                getline(cin, toDate);
                leaves.addRequest(requestID, id, students[index].roomNo,
                                  reason, fromDate, toDate);
            }
            else if (choice != 0)
                cout << "Invalid choice.\n";
        } while (choice != 0);
    }

public:
    void run()
    {
        // A small demonstration of runtime polymorphism.
        Admin admin;
        User *currentUser = &admin;
        cout << "Welcome, ";
        currentUser->showRole();
        cout << "!\n";

        int choice;
        do
        {
            cout << "\n========== DORMEASE ==========\n"
                 << "Student Accommodation System\n"
                 << "1. Admin login\n2. Student login\n0. Exit\nChoice: ";
            cin >> choice;

            if (choice == 1)
            {
                string username, password;
                cout << "Admin username: ";
                cin >> username;
                cout << "Admin password: ";
                cin >> password;

                if (username == "admin" && password == "admin123")
                    adminMenu();
                else
                    cout << "Incorrect admin username or password.\n";
            }
            else if (choice == 2)
                studentLogin();
            else if (choice == 0)
                cout << "Thank you for using DormEase.\n";
            else
                cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};

int main()
{
    DormEase system;
    system.run();
    return 0;
}
