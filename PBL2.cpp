
// =====================================================================
//  DORMEASE - Student Accommodation System (simplified version)
//
//  An academic console project. All data is kept IN MEMORY only, so
//  everything is lost when the program ends (no files, no database).
//
//  Admin login   : username = admin , password = admin123
//  Student login : Student ID + password given at registration
//  (Demo credentials only - not a real security system.)
//
//  Compile : g++ -std=c++11 dormease_simple.cpp -o dormease
//
//  Data structures used
//    Array         -> rooms (RoomManager), students (StudentManager),
//                     attendance (AttendanceManager)
//    Linked list   -> complaints, leave requests (teammate's code)
//    Stack (list)  -> Undo deleted student (StudentStack)
//    Queue (list)  -> waiting list for rooms (WaitingQueue)
//  OOP concepts used
//    Classes/objects, encapsulation, constructors, destructors,
//    inheritance (User -> Student, Admin), pure virtual function,
//    abstract class, virtual destructor, runtime polymorphism,
//    pointers to objects, arrays of objects.
// =====================================================================

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_ROOMS = 10;          // rooms 101 to 110
const int FIRST_ROOM = 101;
const int MAX_STUDENTS = 50;
const int MAX_ATTENDANCE = 100;


// =====================================================================
//  INPUT FUNCTIONS
//  readNumber : reads an integer. If the user types letters, it clears
//               the error, throws the bad input away and asks again.
//  readText   : reads a whole line (spaces allowed), must not be empty.
//  If the input stream ends (Ctrl+Z / end of file) the program exits.
// =====================================================================

int readNumber(string prompt)
{
    int number;
    cout << prompt;

    while (!(cin >> number))
    {
        if (cin.eof())
            exit(0);
        cin.clear();               // remove the error state
        cin.ignore(1000, '\n');    // throw away the bad input
        cout << "Invalid input. Enter a number: ";
    }

    cin.ignore(1000, '\n');        // remove the Enter key left in the buffer
    return number;
}

string readText(string prompt)
{
    string text;

    do
    {
        cout << prompt;
        if (!getline(cin, text))
            exit(0);
    } while (text == "");

    return text;
}


// =====================================================================
//  COMPLAINT MANAGER  (teammate's linked list code)
//  Unchanged except that the two "= delete" copy lines were removed.
//  Only ONE ComplaintManager object is ever created and it is never
//  copied, so those lines are not needed.
// =====================================================================

class ComplaintManager
{
private:
    struct Node
    {
        int complaintID;
        int studentID;
        int roomNo;
        string description;
        Node* next;
    };

    Node* head;

public:
    ComplaintManager()
    {
        head = nullptr;
    }

    ~ComplaintManager()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add complaint
    bool addComplaint(int id, int student, int room,
                      const string& description)
    {
        if (searchComplaint(id, false))
        {
            cout << "Complaint ID already exists.\n";
            return false;
        }

        Node* newNode = new Node{
            id, student, room, description, nullptr
        };

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;

            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newNode;
        }

        cout << "Complaint added successfully.\n";
        return true;
    }

    // Display all complaints
    void displayComplaints() const
    {
        if (head == nullptr)
        {
            cout << "No complaints found.\n";
            return;
        }

        Node* temp = head;

        while (temp != nullptr)
        {
            cout << "\nComplaint ID: " << temp->complaintID
                 << "\nStudent ID: " << temp->studentID
                 << "\nRoom Number: " << temp->roomNo
                 << "\nDescription: " << temp->description
                 << "\n----------------------\n";

            temp = temp->next;
        }
    }

    // Search complaint by unique ID
    bool searchComplaint(int id, bool show = true) const
    {
        Node* temp = head;

        while (temp != nullptr)
        {
            if (temp->complaintID == id)
            {
                if (show)
                {
                    cout << "\nComplaint found!\n"
                         << "Complaint ID: " << temp->complaintID
                         << "\nStudent ID: " << temp->studentID
                         << "\nRoom Number: " << temp->roomNo
                         << "\nDescription: " << temp->description
                         << '\n';
                }

                return true;
            }

            temp = temp->next;
        }

        if (show)
            cout << "Complaint not found.\n";

        return false;
    }

    // Delete complaint by unique ID
    bool deleteComplaint(int id)
    {
        Node* temp = head;
        Node* previous = nullptr;

        while (temp != nullptr &&
               temp->complaintID != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Complaint not found.\n";
            return false;
        }

        if (previous == nullptr)
            head = head->next;
        else
            previous->next = temp->next;

        delete temp;

        cout << "Complaint deleted successfully.\n";
        return true;
    }
};


// =====================================================================
//  LEAVE REQUEST MANAGER  (teammate's linked list code)
// =====================================================================

class LeaveRequestManager
{
private:
    struct Node
    {
        int requestID;
        int studentID;
        int roomNo;
        string reason;
        Node* next;
    };

    Node* head;

public:
    LeaveRequestManager()
    {
        head = nullptr;
    }

    ~LeaveRequestManager()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add leave request
    bool addRequest(int id, int student, int room,
                    const string& reason)
    {
        if (searchRequest(id, false))
        {
            cout << "Request ID already exists.\n";
            return false;
        }

        Node* newNode = new Node{
            id, student, room, reason, nullptr
        };

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;

            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newNode;
        }

        cout << "Leave request added successfully.\n";
        return true;
    }

    // Display all requests
    void displayRequests() const
    {
        if (head == nullptr)
        {
            cout << "No leave requests found.\n";
            return;
        }

        Node* temp = head;

        while (temp != nullptr)
        {
            cout << "\nRequest ID: " << temp->requestID
                 << "\nStudent ID: " << temp->studentID
                 << "\nRoom Number: " << temp->roomNo
                 << "\nReason: " << temp->reason
                 << "\n----------------------\n";

            temp = temp->next;
        }
    }

    // Search request by unique ID
    bool searchRequest(int id, bool show = true) const
    {
        Node* temp = head;

        while (temp != nullptr)
        {
            if (temp->requestID == id)
            {
                if (show)
                {
                    cout << "\nLeave request found!\n"
                         << "Request ID: " << temp->requestID
                         << "\nStudent ID: " << temp->studentID
                         << "\nRoom Number: " << temp->roomNo
                         << "\nReason: " << temp->reason
                         << '\n';
                }

                return true;
            }

            temp = temp->next;
        }

        if (show)
            cout << "Leave request not found.\n";

        return false;
    }

    // Delete request by unique ID
    bool deleteRequest(int id)
    {
        Node* temp = head;
        Node* previous = nullptr;

        while (temp != nullptr &&
               temp->requestID != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Leave request not found.\n";
            return false;
        }

        if (previous == nullptr)
            head = head->next;
        else
            previous->next = temp->next;

        delete temp;

        cout << "Leave request deleted successfully.\n";
        return true;
    }
};


// =====================================================================
//  USER  -  abstract base class (INHERITANCE, ABSTRACTION)
//  Holds what every user has: id, name, password.
//  showDashboard() is a PURE VIRTUAL function, so User is an abstract
//  class: we can never create a plain User object, only Student/Admin.
//  The destructor is virtual so that deleting through a User pointer
//  would call the correct derived destructor.
// =====================================================================

class User
{
private:
    int id;
    string name;
    string password;

public:
    User()
    {
        id = 0;
        name = "";
        password = "";
    }

    User(int userID, string userName, string userPassword)
    {
        id = userID;
        name = userName;
        password = userPassword;
    }

    virtual ~User() {}

    int getID() const { return id; }
    string getName() const { return name; }
    void setName(string newName) { name = newName; }
    void setPassword(string newPassword) { password = newPassword; }

    // The password is never shown, it can only be checked
    bool checkPassword(string attempt) const
    {
        return password == attempt;
    }

    // Pure virtual function: derived classes must write their own version
    virtual void showDashboard() const = 0;
};


// =====================================================================
//  ADMIN  -  derived class (public inheritance from User)
// =====================================================================

class Admin : public User
{
public:
    // Passes the values to the base class constructor
    Admin() : User(1, "Administrator", "admin123") {}

    // Overrides User::showDashboard()
    void showDashboard() const
    {
        cout << "\n========== ADMIN DASHBOARD ==========\n"
             << "1. Student Management\n"
             << "2. Room Management\n"
             << "3. Waiting List\n"
             << "4. Attendance Management\n"
             << "5. Complaint Management\n"
             << "6. Leave Request Management\n"
             << "7. Undo Deleted Student\n"
             << "8. Display Student Records\n"
             << "0. Logout\n";
    }
};


// =====================================================================
//  STUDENT  -  derived class (public inheritance from User)
//  Inherits id, name, password and their functions from User.
//  Adds age, course, contact and room number.
// =====================================================================

class Student : public User
{
private:
    int age;
    string course;
    string contact;
    int roomNo;                 // 0 means no room allocated

public:
    // Default constructor (needed for arrays of Student objects)
    Student() : User()
    {
        age = 0;
        course = "";
        contact = "";
        roomNo = 0;
    }

    // Parameterized constructor
    Student(int id, string name, string password,
            int studentAge, string studentCourse, string studentContact)
        : User(id, name, password)
    {
        age = studentAge;
        course = studentCourse;
        contact = studentContact;
        roomNo = 0;
    }

    int getAge() const { return age; }
    string getCourse() const { return course; }
    string getContact() const { return contact; }
    int getRoomNo() const { return roomNo; }

    void setAge(int newAge) { age = newAge; }
    void setCourse(string newCourse) { course = newCourse; }
    void setContact(string newContact) { contact = newContact; }
    void setRoomNo(int newRoomNo) { roomNo = newRoomNo; }

    // Overrides User::showDashboard()
    void showDashboard() const
    {
        cout << "\n========== STUDENT DASHBOARD ==========\n"
             << "Welcome, " << getName() << "\n"
             << "1. View My Details\n"
             << "2. Submit Complaint\n"
             << "3. Submit Leave Request\n"
             << "4. View Attendance\n"
             << "0. Logout\n";
    }

    void displayDetails() const
    {
        cout << "\nStudent ID : " << getID()
             << "\nName       : " << getName()
             << "\nAge        : " << age
             << "\nCourse     : " << course
             << "\nContact    : " << contact
             << "\nRoom       : ";

        if (roomNo == 0)
            cout << "Not allocated\n";
        else
            cout << roomNo << "\n";
    }
};


// =====================================================================
//  STUDENT MANAGER  -  stores students in an ARRAY OF OBJECTS
// =====================================================================

class StudentManager
{
private:
    Student students[MAX_STUDENTS];
    int count;

public:
    StudentManager()
    {
        count = 0;
    }

    bool isFull() const
    {
        return count == MAX_STUDENTS;
    }

    // Position of the student in the array, or -1 if not found
    int findIndex(int id) const
    {
        for (int i = 0; i < count; i++)
        {
            if (students[i].getID() == id)
                return i;
        }
        return -1;
    }

    // Pointer to the stored student, or nullptr if not found
    Student* getStudent(int id)
    {
        int index = findIndex(id);

        if (index == -1)
            return nullptr;

        return &students[index];
    }

    // Add a student (no duplicate IDs, no overflow)
    bool addStudent(Student s)
    {
        if (findIndex(s.getID()) != -1)
        {
            cout << "Student ID already exists.\n";
            return false;
        }

        if (isFull())
        {
            cout << "Student storage is full.\n";
            return false;
        }

        students[count] = s;
        count++;
        return true;
    }

    // Remove a student by shifting the later students one place left
    bool removeStudent(int id)
    {
        int index = findIndex(id);

        if (index == -1)
            return false;

        for (int i = index; i < count - 1; i++)
            students[i] = students[i + 1];

        count--;
        return true;
    }

    void displayAll() const
    {
        if (count == 0)
        {
            cout << "No student records found.\n";
            return;
        }

        for (int i = 0; i < count; i++)
            students[i].displayDetails();
    }
};


// =====================================================================
//  ROOM MANAGER  -  ARRAY
//  occupant[i] stores the ID of the student living in room (101 + i).
//  0 means the room is vacant. This array IS the room availability.
// =====================================================================

class RoomManager
{
private:
    int occupant[MAX_ROOMS];

public:
    RoomManager()
    {
        for (int i = 0; i < MAX_ROOMS; i++)
            occupant[i] = 0;               // all rooms start vacant
    }

    bool isValidRoom(int roomNo) const
    {
        return roomNo >= FIRST_ROOM && roomNo < FIRST_ROOM + MAX_ROOMS;
    }

    bool isVacant(int roomNo) const
    {
        return isValidRoom(roomNo) && occupant[roomNo - FIRST_ROOM] == 0;
    }

    // First vacant room number, or 0 if every room is occupied
    int findFreeRoom() const
    {
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            if (occupant[i] == 0)
                return FIRST_ROOM + i;
        }
        return 0;
    }

    // Give a vacant room to a student
    bool assignRoom(int roomNo, int studentID)
    {
        if (!isVacant(roomNo))
            return false;

        occupant[roomNo - FIRST_ROOM] = studentID;
        return true;
    }

    // Make a room vacant again
    void releaseRoom(int roomNo)
    {
        if (isValidRoom(roomNo))
            occupant[roomNo - FIRST_ROOM] = 0;
    }

    void showAllRooms() const
    {
        int occupiedCount = 0;

        cout << "\n----- All Rooms -----\n";
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            cout << "Room " << FIRST_ROOM + i << " : ";

            if (occupant[i] == 0)
                cout << "Vacant\n";
            else
            {
                cout << "Occupied by Student ID " << occupant[i] << "\n";
                occupiedCount++;
            }
        }
        cout << "Occupied: " << occupiedCount
             << " | Vacant: " << MAX_ROOMS - occupiedCount << "\n";
    }

    void showVacantRooms() const
    {
        bool found = false;

        cout << "\n----- Vacant Rooms -----\n";
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            if (occupant[i] == 0)
            {
                cout << "Room " << FIRST_ROOM + i << "\n";
                found = true;
            }
        }
        if (!found)
            cout << "No vacant rooms.\n";
    }

    void showOccupiedRooms() const
    {
        bool found = false;

        cout << "\n----- Occupied Rooms -----\n";
        for (int i = 0; i < MAX_ROOMS; i++)
        {
            if (occupant[i] != 0)
            {
                cout << "Room " << FIRST_ROOM + i
                     << " - Student ID " << occupant[i] << "\n";
                found = true;
            }
        }
        if (!found)
            cout << "No occupied rooms.\n";
    }
};


// =====================================================================
//  WAITING QUEUE  -  QUEUE using a linked list (FIFO)
//  enqueue : add a student ID at the REAR.
//  dequeue : remove the student ID from the FRONT.
// =====================================================================

class WaitingQueue
{
private:
    struct QueueNode
    {
        int studentID;
        QueueNode* next;
    };

    QueueNode* front;
    QueueNode* rear;

public:
    WaitingQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~WaitingQueue()
    {
        while (front != nullptr)
        {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    bool contains(int id) const
    {
        QueueNode* temp = front;

        while (temp != nullptr)
        {
            if (temp->studentID == id)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Add at the rear (a student cannot be added twice)
    bool enqueue(int id)
    {
        if (contains(id))
            return false;

        QueueNode* newNode = new QueueNode;
        newNode->studentID = id;
        newNode->next = nullptr;

        if (rear == nullptr)           // queue was empty
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        return true;
    }

    // Remove from the front and give back the student ID
    bool dequeue(int& id)
    {
        if (isEmpty())
            return false;

        QueueNode* temp = front;
        id = temp->studentID;
        front = front->next;

        if (front == nullptr)          // queue became empty
            rear = nullptr;

        delete temp;
        return true;
    }

    // Remove one particular student (used when a waiting student is deleted)
    void removeStudent(int id)
    {
        QueueNode* temp = front;
        QueueNode* previous = nullptr;

        while (temp != nullptr && temp->studentID != id)
        {
            previous = temp;
            temp = temp->next;
        }

        if (temp == nullptr)
            return;

        if (previous == nullptr)
            front = temp->next;
        else
            previous->next = temp->next;

        if (temp == rear)
            rear = previous;

        delete temp;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Waiting list is empty.\n";
            return;
        }

        cout << "\n----- Waiting List (first to last) -----\n";
        QueueNode* temp = front;
        int position = 1;

        while (temp != nullptr)
        {
            cout << position << ". Student ID " << temp->studentID << "\n";
            temp = temp->next;
            position++;
        }
    }
};


// =====================================================================
//  STUDENT STACK  -  STACK using a linked list (LIFO) for Undo
//  Each node stores a complete copy of the deleted Student object, so
//  nothing is lost (name, password, age, course, contact, room).
//  push : new node goes on TOP.   pop : node is removed from TOP.
// =====================================================================

class StudentStack
{
private:
    struct StackNode
    {
        Student data;
        StackNode* next;
    };

    StackNode* top;

public:
    StudentStack()
    {
        top = nullptr;
    }

    ~StudentStack()
    {
        while (top != nullptr)
        {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    void push(Student s)
    {
        StackNode* newNode = new StackNode;
        newNode->data = s;
        newNode->next = top;
        top = newNode;
    }

    bool pop(Student& s)
    {
        if (isEmpty())
            return false;

        StackNode* temp = top;
        s = temp->data;
        top = top->next;
        delete temp;
        return true;
    }
};


// =====================================================================
//  ATTENDANCE MANAGER  -  ARRAY of records
//  An array is enough because we only add records at the end and
//  search through them, and the maximum size is fixed.
// =====================================================================

class AttendanceManager
{
private:
    struct Record
    {
        int studentID;
        string date;
        bool present;
    };

    Record records[MAX_ATTENDANCE];
    int count;

public:
    AttendanceManager()
    {
        count = 0;
    }

    void markAttendance(int studentID, string date, bool present)
    {
        if (count == MAX_ATTENDANCE)
        {
            cout << "Attendance storage is full.\n";
            return;
        }

        records[count].studentID = studentID;
        records[count].date = date;
        records[count].present = present;
        count++;

        cout << "Attendance marked.\n";
    }

    void displayAll() const
    {
        if (count == 0)
        {
            cout << "No attendance records found.\n";
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << "Student ID " << records[i].studentID
                 << " | " << records[i].date << " | ";

            if (records[i].present)
                cout << "Present\n";
            else
                cout << "Absent\n";
        }
    }

    void displayForStudent(int studentID) const
    {
        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (records[i].studentID == studentID)
            {
                cout << records[i].date << " : ";

                if (records[i].present)
                    cout << "Present\n";
                else
                    cout << "Absent\n";

                found = true;
            }
        }

        if (!found)
            cout << "No attendance records found for this student.\n";
    }
};


// =====================================================================
//  DORMEASE APP  -  connects all the modules together
//  Menus call simple functions such as registerStudent(), allocateRoom()
//  and undoDelete(). The stack, queue and array details stay hidden
//  inside their own classes (ABSTRACTION).
// =====================================================================

class DormEaseApp
{
private:
    Admin admin;
    StudentManager students;
    RoomManager rooms;
    WaitingQueue waitingList;
    StudentStack deletedStack;
    AttendanceManager attendance;
    ComplaintManager complaints;
    LeaveRequestManager leaves;

    int nextComplaintID;
    int nextRequestID;

    // ---------------- Waiting list ----------------

    // While a room is vacant and someone is waiting, DEQUEUE the student
    // at the front and give them the room (FIFO).
    void processWaitingList()
    {
        while (rooms.findFreeRoom() != 0 && !waitingList.isEmpty())
        {
            int id;
            waitingList.dequeue(id);                 // DEQUEUE

            Student* s = students.getStudent(id);

            if (s != nullptr && s->getRoomNo() == 0)
            {
                int room = rooms.findFreeRoom();
                rooms.assignRoom(room, id);
                s->setRoomNo(room);
                cout << "Waiting list: Student ID " << id
                     << " got Room " << room << ".\n";
            }
        }
    }

    // ---------------- Student management ----------------

    void registerStudent()
    {
        if (students.isFull())
        {
            cout << "Student storage is full.\n";
            return;
        }

        int id = readNumber("Enter new Student ID: ");

        if (id <= 0)
        {
            cout << "Student ID must be a positive number.\n";
            return;
        }

        if (students.findIndex(id) != -1)
        {
            cout << "Student ID already exists.\n";
            return;
        }

        string name = readText("Name: ");

        int age = readNumber("Age: ");
        while (age < 15 || age > 60)
            age = readNumber("Age must be between 15 and 60. Enter again: ");

        string course = readText("Course: ");
        string contact = readText("Contact: ");
        string password = readText("Password: ");

        Student s(id, name, password, age, course, contact);

        if (students.addStudent(s))
            cout << "Student registered. Allocate a room from Room Management.\n";
    }

    void searchStudent()
    {
        int id = readNumber("Enter Student ID: ");
        Student* s = students.getStudent(id);

        if (s == nullptr)
            cout << "Student record not found.\n";
        else
            s->displayDetails();
    }

    void updateStudent()
    {
        int id = readNumber("Enter Student ID to update: ");
        Student* s = students.getStudent(id);

        if (s == nullptr)
        {
            cout << "Student record not found.\n";
            return;
        }

        s->setName(readText("New name: "));

        int age = readNumber("New age: ");
        while (age < 15 || age > 60)
            age = readNumber("Age must be between 15 and 60. Enter again: ");
        s->setAge(age);

        s->setCourse(readText("New course: "));
        s->setContact(readText("New contact: "));
        s->setPassword(readText("New password: "));

        cout << "Student record updated.\n";
    }

    // Delete: save a copy on the STACK, free the room, remove the record
    void deleteStudent()
    {
        int id = readNumber("Enter Student ID to delete: ");
        Student* s = students.getStudent(id);

        if (s == nullptr)
        {
            cout << "Student record not found.\n";
            return;
        }

        Student copy = *s;                    // complete copy of the record
        deletedStack.push(copy);              // PUSH

        waitingList.removeStudent(id);        // in case the student was waiting

        if (copy.getRoomNo() != 0)
            rooms.releaseRoom(copy.getRoomNo());

        students.removeStudent(id);           // pointer s is invalid now

        cout << "Student deleted. You can undo this from the Admin menu.\n";
        processWaitingList();                 // a room may be free now
    }

    // Undo: POP the latest deleted student and put the record back
    void undoDelete()
    {
        if (deletedStack.isEmpty())
        {
            cout << "Nothing to undo.\n";
            return;
        }

        if (students.isFull())
        {
            cout << "Cannot restore: student storage is full.\n";
            return;
        }

        Student s;
        deletedStack.pop(s);                  // POP

        if (students.findIndex(s.getID()) != -1)
        {
            cout << "Cannot restore: Student ID " << s.getID()
                 << " is already in use. Record discarded.\n";
            return;
        }

        int oldRoom = s.getRoomNo();

        // Give the old room back only if it is still vacant
        if (oldRoom != 0 && rooms.isVacant(oldRoom))
        {
            rooms.assignRoom(oldRoom, s.getID());
            cout << "Student restored with Room " << oldRoom << ".\n";
        }
        else
        {
            s.setRoomNo(0);
            cout << "Student restored without a room. "
                 << "Allocate one from Room Management.\n";
        }

        students.addStudent(s);
    }

    // ---------------- Room management ----------------

    // Give a room to a student, or add the student to the waiting QUEUE
    void allocateRoom()
    {
        int id = readNumber("Enter Student ID: ");
        Student* s = students.getStudent(id);

        if (s == nullptr)
        {
            cout << "Student record not found.\n";
            return;
        }

        if (s->getRoomNo() != 0)
        {
            cout << "This student already has Room " << s->getRoomNo() << ".\n";
            return;
        }

        int room = readNumber("Room number (0 = any vacant room): ");

        if (room == 0)
            room = rooms.findFreeRoom();

        if (room == 0)                        // no vacant room at all
        {
            if (waitingList.enqueue(id))      // ENQUEUE
                cout << "All rooms are full. Student added to the waiting list.\n";
            else
                cout << "Student is already in the waiting list.\n";
            return;
        }

        if (!rooms.isValidRoom(room))
        {
            cout << "Invalid room number. Rooms are 101 to 110.\n";
            return;
        }

        if (!rooms.isVacant(room))
        {
            cout << "Room " << room << " is already occupied.\n";
            return;
        }

        rooms.assignRoom(room, id);
        s->setRoomNo(room);
        waitingList.removeStudent(id);        // leave the queue if waiting
        cout << "Room " << room << " allocated to Student ID " << id << ".\n";
    }

    // Student leaves the hostel: free the room, then serve the waiting list
    void releaseRoom()
    {
        int id = readNumber("Enter Student ID: ");
        Student* s = students.getStudent(id);

        if (s == nullptr)
        {
            cout << "Student record not found.\n";
            return;
        }

        if (s->getRoomNo() == 0)
        {
            cout << "This student has no room.\n";
            return;
        }

        rooms.releaseRoom(s->getRoomNo());
        cout << "Room " << s->getRoomNo() << " released.\n";
        s->setRoomNo(0);
        processWaitingList();
    }

    // ---------------- Attendance ----------------

    void markAttendance(bool present)
    {
        int id = readNumber("Student ID: ");

        if (students.findIndex(id) == -1)
        {
            cout << "Student not found. Attendance not recorded.\n";
            return;
        }

        string date = readText("Date (for example 15-10-2026): ");
        attendance.markAttendance(id, date, present);
    }

    // ---------------- Complaints and leave requests ----------------

    // The student must exist. The room number is taken from the record.
    void addComplaint(int studentID)
    {
        Student* s = students.getStudent(studentID);

        if (s == nullptr)
        {
            cout << "Student not found. Complaint not added.\n";
            return;
        }

        string description = readText("Complaint description: ");

        if (complaints.addComplaint(nextComplaintID, studentID,
                                    s->getRoomNo(), description))
        {
            cout << "Your complaint ID is " << nextComplaintID << ".\n";
            nextComplaintID++;
        }
    }

    void addLeaveRequest(int studentID)
    {
        Student* s = students.getStudent(studentID);

        if (s == nullptr)
        {
            cout << "Student not found. Leave request not added.\n";
            return;
        }

        string reason = readText("Leave reason: ");

        if (leaves.addRequest(nextRequestID, studentID,
                              s->getRoomNo(), reason))
        {
            cout << "Your request ID is " << nextRequestID << ".\n";
            nextRequestID++;
        }
    }

    // ---------------- Admin submenus ----------------

    void studentMenu()
    {
        int choice;

        do
        {
            cout << "\n--- Student Management ---\n"
                 << "1. Register Student\n"
                 << "2. Display All Students\n"
                 << "3. Search Student by ID\n"
                 << "4. Update Student\n"
                 << "5. Delete Student\n"
                 << "0. Back\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1: registerStudent(); break;
                case 2: students.displayAll(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void roomMenu()
    {
        int choice;

        do
        {
            cout << "\n--- Room Management ---\n"
                 << "1. Display All Rooms\n"
                 << "2. Display Vacant Rooms\n"
                 << "3. Display Occupied Rooms\n"
                 << "4. Allocate Room to Student\n"
                 << "5. Release Student's Room\n"
                 << "0. Back\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1: rooms.showAllRooms(); break;
                case 2: rooms.showVacantRooms(); break;
                case 3: rooms.showOccupiedRooms(); break;
                case 4: allocateRoom(); break;
                case 5: releaseRoom(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void waitingMenu()
    {
        int choice;

        do
        {
            cout << "\n--- Waiting List ---\n"
                 << "1. Display Waiting List\n"
                 << "2. Allocate Vacant Rooms to Waiting Students\n"
                 << "0. Back\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1: waitingList.display(); break;
                case 2: processWaitingList(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void attendanceMenu()
    {
        int choice;

        do
        {
            cout << "\n--- Attendance Management ---\n"
                 << "1. Mark Present\n"
                 << "2. Mark Absent\n"
                 << "3. Search Attendance by Student ID\n"
                 << "4. Display All Attendance\n"
                 << "0. Back\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1: markAttendance(true); break;
                case 2: markAttendance(false); break;
                case 3:
                {
                    int id = readNumber("Student ID: ");
                    if (students.findIndex(id) == -1)
                        cout << "Student not found.\n";
                    else
                        attendance.displayForStudent(id);
                    break;
                }
                case 4: attendance.displayAll(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void complaintMenu()
    {
        int choice;

        do
        {
            cout << "\n--- Complaint Management ---\n"
                 << "1. Add Complaint\n"
                 << "2. Display All Complaints\n"
                 << "3. Search Complaint by ID\n"
                 << "4. Delete Complaint\n"
                 << "0. Back\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1:
                    addComplaint(readNumber("Student ID: "));
                    break;
                case 2:
                    complaints.displayComplaints();
                    break;
                case 3:
                    complaints.searchComplaint(readNumber("Complaint ID: "));
                    break;
                case 4:
                    complaints.deleteComplaint(readNumber("Complaint ID: "));
                    break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void leaveMenu()
    {
        int choice;

        do
        {
            cout << "\n--- Leave Request Management ---\n"
                 << "1. Add Leave Request\n"
                 << "2. Display All Requests\n"
                 << "3. Search Request by ID\n"
                 << "4. Delete Request\n"
                 << "0. Back\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1:
                    addLeaveRequest(readNumber("Student ID: "));
                    break;
                case 2:
                    leaves.displayRequests();
                    break;
                case 3:
                    leaves.searchRequest(readNumber("Request ID: "));
                    break;
                case 4:
                    leaves.deleteRequest(readNumber("Request ID: "));
                    break;
                case 0: break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------------- Sessions ----------------

    // RUNTIME POLYMORPHISM: 'user' is a base class (User) pointer that
    // points to an Admin object. user->showDashboard() runs Admin's version.
    void adminSession()
    {
        User* user = &admin;
        int choice;

        do
        {
            user->showDashboard();
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1: studentMenu(); break;
                case 2: roomMenu(); break;
                case 3: waitingMenu(); break;
                case 4: attendanceMenu(); break;
                case 5: complaintMenu(); break;
                case 6: leaveMenu(); break;
                case 7: undoDelete(); break;
                case 8: students.displayAll(); break;
                case 0: cout << "Logged out.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // Here the same kind of User pointer points to a Student object,
    // so the same call user->showDashboard() runs Student's version.
    void studentSession(Student* student)
    {
        User* user = student;
        int choice;

        do
        {
            user->showDashboard();
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1:
                    student->displayDetails();
                    break;
                case 2:
                    addComplaint(student->getID());
                    break;
                case 3:
                    addLeaveRequest(student->getID());
                    break;
                case 4:
                    attendance.displayForStudent(student->getID());
                    break;
                case 0:
                    cout << "Logged out.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void adminLogin()
    {
        string username = readText("Username: ");
        string password = readText("Password: ");

        if (username == "admin" && admin.checkPassword(password))
            adminSession();
        else
            cout << "Wrong username or password.\n";
    }

    void studentLogin()
    {
        int id = readNumber("Student ID: ");
        string password = readText("Password: ");

        Student* s = students.getStudent(id);

        if (s != nullptr && s->checkPassword(password))
            studentSession(s);
        else
            cout << "Wrong Student ID or password.\n";
    }

public:
    DormEaseApp()
    {
        nextComplaintID = 1;
        nextRequestID = 1;
    }

    void run()
    {
        int choice;

        do
        {
            cout << "\n========================================\n"
                 << "             DORMEASE\n"
                 << "  Student Accommodation System\n"
                 << "========================================\n"
                 << "1. Login as Admin\n"
                 << "2. Login as Student\n"
                 << "3. Exit\n";
            choice = readNumber("Enter choice: ");

            switch (choice)
            {
                case 1: adminLogin(); break;
                case 2: studentLogin(); break;
                case 3: cout << "Exiting DormEase.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 3);
    }
};


int main()
{
    DormEaseApp app;
    app.run();
    return 0;
}