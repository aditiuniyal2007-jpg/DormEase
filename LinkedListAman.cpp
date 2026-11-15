#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ================= COMPLAINT MANAGER =================

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

    // Prevent accidental shallow copies of the linked list
    ComplaintManager(const ComplaintManager&) = delete;
    ComplaintManager& operator=(const ComplaintManager&) = delete;

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


// ================= LEAVE REQUEST MANAGER =================

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

    LeaveRequestManager(const LeaveRequestManager&) = delete;
    LeaveRequestManager& operator=(const LeaveRequestManager&) = delete;

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


// ================= TESTING MENU =================

int main()
{
    ComplaintManager complaints;
    LeaveRequestManager leaves;

    int choice;

    do
    {
        cout << "\n===== DORMEASE =====\n"
             << "1. Add Complaint\n"
             << "2. Display Complaints\n"
             << "3. Search Complaint\n"
             << "4. Delete Complaint\n"
             << "5. Add Leave Request\n"
             << "6. Display Leave Requests\n"
             << "7. Search Leave Request\n"
             << "8. Delete Leave Request\n"
             << "0. Exit\n"
             << "Enter choice: ";

        if (!(cin >> choice))
            break;

        int id, student, room;
        string details;

        switch (choice)
        {
            case 1:
                cout << "Complaint ID: ";
                cin >> id;
                cout << "Student ID: ";
                cin >> student;
                cout << "Room Number: ";
                cin >> room;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Complaint description: ";
                getline(cin, details);

                complaints.addComplaint(id, student, room, details);
                break;

            case 2:
                complaints.displayComplaints();
                break;

            case 3:
                cout << "Enter Complaint ID: ";
                cin >> id;
                complaints.searchComplaint(id);
                break;

            case 4:
                cout << "Enter Complaint ID: ";
                cin >> id;
                complaints.deleteComplaint(id);
                break;

            case 5:
                cout << "Request ID: ";
                cin >> id;
                cout << "Student ID: ";
                cin >> student;
                cout << "Room Number: ";
                cin >> room;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Leave reason: ";
                getline(cin, details);

                leaves.addRequest(id, student, room, details);
                break;

            case 6:
                leaves.displayRequests();
                break;

            case 7:
                cout << "Enter Request ID: ";
                cin >> id;
                leaves.searchRequest(id);
                break;

            case 8:
                cout << "Enter Request ID: ";
                cin >> id;
                leaves.deleteRequest(id);
                break;

            case 0:
                cout << "Exiting DormEase.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}