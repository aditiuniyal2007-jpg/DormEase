
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    int studentID;
    string name;
};

class WaitingQueue
{
    struct QueueNode
    {
        Student data;
        QueueNode* next;
    };

    QueueNode* front;
    QueueNode* rear;

public:
    WaitingQueue()
    {
        front = rear = nullptr;
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void enqueue(Student s)
    {
        QueueNode* newNode = new QueueNode;
        newNode->data = s;
        newNode->next = nullptr;

        if (isEmpty())
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

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

    ~WaitingQueue()
    {
        Student s;
        while (dequeue(s));
    }
};

int main()
{
    WaitingQueue q;
    Student s1 = {2, "Abhinav"};
    Student s2;

    q.enqueue(s1);

    if (q.dequeue(s2))
        cout << s2.studentID << " " << s2.name;

    return 0;
}
