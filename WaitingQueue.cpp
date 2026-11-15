
#include <iostream>
using namespace std;

// Student class
class Student
{
public:
    int studentID;

    void display()
    {
        cout << "Student ID: " << studentID << endl;
    }
};

// Waiting Queue class
class WaitingQueue
{
private:
    // Node structure
    struct QueueNode
    {
        Student data;
        QueueNode* next;
    };

    QueueNode* front;
    QueueNode* rear;

public:

    // Constructor
    WaitingQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Destructor
    ~WaitingQueue()
    {
        while (front != nullptr)
        {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }

    // Check whether queue is empty
    bool isEmpty()
    {
        return front == nullptr;
    }

    // Insert student at rear
    void enqueue(Student s)
    {
        QueueNode* newNode = new QueueNode;
        newNode->data = s;
        newNode->next = nullptr;

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Delete student from front
    bool dequeue(Student& s)
    {
        if (isEmpty())
            return false;

        QueueNode* temp = front;
        s = temp->data;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        return true;
    }

    // Display all students in queue
    void display()
    {
        if (isEmpty())
        {
            cout << "Waiting list is empty." << endl;
            return;
        }

        QueueNode* temp = front;

        while (temp != nullptr)
        {
            temp->data.display();
            temp = temp->next;
        }
    }

    // Search student by ID
    bool contains(int id)
    {
        QueueNode* temp = front;

        while (temp != nullptr)
        {
            if (temp->data.studentID == id)
                return true;

            temp = temp->next;
        }

        return false;
    }

    // Remove a particular student by ID
    bool removeStudent(int id)
    {
        if (isEmpty())
            return false;

        QueueNode* temp = front;
        QueueNode* prev = nullptr;

        while (temp != nullptr)
        {
            if (temp->data.studentID == id)
            {
                if (prev == nullptr)
                    front = temp->next;
                else
                    prev->next = temp->next;

                if (temp == rear)
                    rear = prev;

                delete temp;
                return true;
            }

            prev = temp;
            temp = temp->next;
        }

        return false;
    }
};

// Main function

int main()
{
    WaitingQueue q;
    Student s;
    int choice = 0, id;

    while (choice != 7)
    {
        cout << "\n===== WAITING QUEUE MENU =====" << endl;
        cout << "1. Enqueue Student" << endl;
        cout << "2. Dequeue Student" << endl;
        cout << "3. Display Waiting List" << endl;
        cout << "4. Search Student" << endl;
        cout << "5. Remove Particular Student" << endl;
        cout << "6. Check if Queue is Empty" << endl;
        cout << "7. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter Student ID: ";
                cin >> s.studentID;
                q.enqueue(s);
                cout << "Student added successfully." << endl;
                break;

            case 2:
                if (q.dequeue(s))
                    cout << "Dequeued Student ID: " << s.studentID << endl;
                else
                    cout << "Waiting list is empty." << endl;
                break;

            case 3:
                q.display();
                break;

            case 4:
                cout << "Enter Student ID to search: ";
                cin >> id;

                if (q.contains(id))
                    cout << "Student found." << endl;
                else
                    cout << "Student not found." << endl;
                break;

            case 5:
                cout << "Enter Student ID to remove: ";
                cin >> id;

                if (q.removeStudent(id))
                    cout << "Student removed successfully." << endl;
                else
                    cout << "Student not found." << endl;
                break;

            case 6:
                if (q.isEmpty())
                    cout << "Waiting list is empty." << endl;
                else
                    cout << "Waiting list is not empty." << endl;
                break;

            case 7:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
