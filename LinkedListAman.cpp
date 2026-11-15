#include <iostream>
#include <string>
#include <limits>
using namespace std;

class ComplaintManager {
private:
    struct Node {
        int complaintID;
        int studentID;
        int roomNo;
        string description;
        Node* next;
    };

    Node* head;

public:
    ComplaintManager() {
        head = nullptr;
    }

    ~ComplaintManager() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool addComplaint(int id, int student, int room, const string& description) {
        if (searchComplaint(id, false)) {
            cout << "Complaint ID already exists.\n";
            return false;
        }

        Node* newNode = new Node{id, student, room, description, nullptr};

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newNode;
        }

        cout << "Complaint added successfully.\n";
        return true;
    }

    void displayComplaints() const {
        if (head == nullptr) {
            cout << "No complaints found.\n";
            return;
        }

        Node* temp = head;

        while (temp != nullptr) {
            cout << "\nComplaint ID: " << temp->complaintID
                 << "\nStudent ID: " << temp->studentID
                 << "\nRoom Number: " << temp->roomNo
                 << "\nDescription: " << temp->description
                 << "\n----------------------\n";
            temp = temp->next;
        }
    }

    bool searchComplaint(int id, bool show = true) const {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->complaintID == id) {
                if (show) {
                    cout << "\nComplaint found!\n"
                         << "Complaint ID: " << temp->complaintID
                         << "\nStudent ID: " << temp->studentID
                         << "\nRoom Number: " << temp->roomNo
                         << "\nDescription: " << temp->description << '\n';
                }
                return true;
            }
            temp = temp->next;
        }

        if (show)
            cout << "Complaint not found.\n";

        return false;
    }

    bool deleteComplaint(int id) {
        Node* temp = head;
        Node* previous = nullptr;

        while (temp != nullptr && temp->complaintID != id) {
            previous = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
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

int main() {
    ComplaintManager complaints;
    int choice;

    do {
        cout << "\n===== DORMEASE COMPLAINT MANAGEMENT =====\n"
             << "1. Add Complaint\n"
             << "2. Display Complaints\n"
             << "3. Search Complaint\n"
             << "4. Delete Complaint\n"
             << "0. Exit\n"
             << "Enter choice: ";

        if (!(cin >> choice))
            break;

        int id, student, room;
        string details;

        switch (choice) {
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

            case 0:
                cout << "Exiting DormEase.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}