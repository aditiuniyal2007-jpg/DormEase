
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class student
{
    string name,father_name,phone_number,mother_name,state,uni_roll_no,course,branch;
    int age,room_no,year;
    public:
    void get_student_data();
    void display_details();
    int get_room();
    int get_roll();
    string getname();
    string getcourse();
    void change_room(int newroom);
    void change_course(string course);
    void change_branch(string branch);
    bool search_by_uni_roll(string uniroll);
    bool search_by_name(string name);
};
class room
{
    int room_no,floor,capacity,occupied_beds;
    public:
    void get_data();
    void display_details();
};
void student::get_student_data()
{
    string name,father_name,phone_number,mother_name,state,uni_roll_no,course,branch;
    cout<<"enter the name of student: ";
    cin>>this->name;
    cout<<"Enter the father's name of student: ";
    cin>>this->father_name;
    cout<<"Enter the phone number of student: ";
    cin>>this->phone_number;
    cout<<"enter the mother's name of the student: ";
    cin>>mother_name;
    cout<<"enter the state of student: ";
    cin>>this->state;
    cout<<"enter the university roll number of the student: ";
    cin>>this->uni_roll_no;
    cout<<"enter the course and branch of student: ";
    cin>>this->course>>this->branch;
    cout<<"enter the age of student: ";
    cin>>this->age;
    cout<<"enter the room number of student: ";
    cin>>this->room_no;
    cout<<"enter the current year of student: ";
    cin>>this->year;
}
int student::get_room()
{
    return this->room_no;
}
void student::display_details()
{
    cout<<"name: "<<this->name<<endl;
    cout<<"father's name: "<<this->father_name<<endl;
    cout<<"phone number: "<<this->phone_number<<endl;
    cout<<"mother's name: "<<this->mother_name<<endl;
    cout<<"state: "<<this->state<<endl;
    cout<<"univeristy roll number: "<<this->uni_roll_no<<endl;
    cout<<"course: "<<this->course<<" branch: "<<this->branch<<endl;
    cout<<"age: "<<this->age;
    cout<<"room number: "<<this->room_no<<endl;
    cout<<"current year: "<<this->year<<endl;
}
void room::get_data()
{
    cout<<"Enter the details of room:\n";
    cout<<"room number: ";
    cin>>this->room_no;
    cout<<"floor: ";
    cin>>this->floor;
    cout<<"capacity: ";
    cin>>this->capacity;
    cout<<"occupied beds: ";
    cin>>occupied_beds;
}
void room::display_details()
{
    cout<<"detail of room:\n";
    cout<<"room number: "<<this->room_no<<endl;
    cout<<"floor: "<<this->floor<<endl;
    cout<<"capaity: "<<this->capacity<<endl;
    cout<<"occupied beds: "<<this->occupied_beds<<endl;
    cout<<"available beds: "<<this->capacity-this->occupied_beds<<endl;
}
int main()
{
    int n;
    cout<<"enter the number of students: ";
    cin>>n;
    vector<student>students(n);
    for(int i=0;i<n;i++)
    {
        cout<<"\n\nEnter the details of student "<<i+1<<" "<<endl<<endl<<endl;
        students[i].get_student_data();
    }
    for(int i=0;i<students.size();i++)
    {
        cout<<"Details of student "<<i+1<<":\n";
        students[i].display_details();
    }
    sort(students.begin(),students.end(),[](student &a,student &b) {return a.get_room()<b.get_room();});
    for(int i=0;i<n;i++)
    {
        cout<<"Details of student after sorting:\n\n\n";
        students[i].display_details();
    }
}
