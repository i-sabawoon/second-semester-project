#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//================ PERSON CLASS ================

class Person
{
protected:
    string name;

public:
// default cons
    Person()
    {
        name = "";
    }

    //parameterized const

    Person(string n )
    {
        name = n;
    }

    //run-time polymorphism or func overriding

   virtual void display()
    {
        cout << "Name: " << name << endl;
    }

    string getName()
    {
        return name;
    }

    //virtual destructor

    virtual ~Person(){}
};

//================ ATTENDANCE CLASS ================

class Attendance
{
private:
    int presents;
    int absents;
    int bunks;

public:

// default cont
    Attendance()
    {
        presents = 0;
        absents = 0;
        bunks = 0;
    }

    // member function ---> counters
    
    void markPresent() { presents++; }
    void markAbsent()  { absents++; }
    void markBunk()    { bunks++; }

    void displayAttendance()
    {
        cout << "Presents: " << presents << endl;
        cout << "Absents : " << absents << endl;
        cout << "Bunks   : " << bunks << endl;
    }

        //      file handling

        // FILE SAVING
        void save(ofstream &fout)
        {
        cout<<"--------------------"<<endl;
        fout << presents << " "
        << absents << " "
        << bunks << endl;
        
    }

    // FILE LOADING
    void load(ifstream &fin)
    {
        fin >> presents >> absents >> bunks;
    }
};


//================ STUDENT CLASS ================

class Student : public Person
{
private:
    string department;
    static int totalStudents;

    //composition
    Attendance attendance;


public:

    Student(string n = "unknown", string d = "") : Person(n)
    {
        department = d;
        totalStudents++;
    }
  

    void markAttendance(char choice)
    {
        if(choice == 'P' || choice == 'p')
            attendance.markPresent();
        else if(choice == 'A' || choice == 'a')
            attendance.markAbsent();
        else if(choice == 'B' || choice == 'b')
            attendance.markBunk();
        else
            cout << "Invalid Choice!" << endl;
    }

    void display() override
    {
        cout << "------------------------" << endl;
        Person::display();
        cout << "Department: " << department << endl;
        attendance.displayAttendance();
    }

    string getName()
    {
        return name;
    }

    static void showTotalStudents(){

        cout<<"Total students: "<<totalStudents<<endl;
    }

     //  FILE SAVE
    void saveToFile(ofstream &fout)
    {
        fout << name << endl;
        fout << department << endl;
        attendance.save(fout);
    }

    // FILE LOAD
    void loadFromFile(ifstream &fin)
    {
        
        getline(fin >> ws,  name);
        getline(fin, department);
        attendance.load(fin);
    }
};

int Student :: totalStudents = 0;
//================ MAIN FUNCTION ================

int main()
{
    
    Student s1("Sabawoon", "SE");
    Student s2("Dawar", "SE");
    Student s3("Rehab", "SE");

    int choice;
    int studentChoice;
    
    cout<<endl;
    do
    {
        cout << "===== MENU ====="<<endl;;
        cout << "1. Mark Attendance"<<endl;
        cout << "2. Display Students"<<endl;
        cout << "3. Save data"<<endl;
        cout << "4. Load data"<<endl;
        cout << "5. Show total students"<<endl;
        cout << "6. Exit"<<endl;
        
        cout << "Enter Choice: ";
        cin >> choice;
        
        switch(choice)
        {
        case 1:{

        
            cout << "Select Student:"<<endl;
            cout << "1. Sabawoon \n2. Dawar\n3. Rehab\n";
            cin >> studentChoice;

            cout << "Present (P/p)   Absent (A/a)   Bunk (B/b)"<<endl;
            char attChoice;
            cin >> attChoice;

            if(studentChoice == 1)
                s1.markAttendance(attChoice);
            else if(studentChoice == 2)
                s2.markAttendance(attChoice);
            else if(studentChoice == 3)
                s3.markAttendance(attChoice);
            else
                cout << "Invalid Student!\n";

            break;
        }
        case 2:{

        
            Person* p1 = &s1;
            Person* p2 = &s2;
            Person* p3 = &s3;

            p1->display();
            p2->display();
            p3->display();
            break;
        }
       case 3:
        {
            ofstream fout("students.txt");

            s1.saveToFile(fout);
            s2.saveToFile(fout);
            s3.saveToFile(fout);

            fout.close();

            cout << "Data Saved Successfully!" << endl;
            break;
        }

        case 4:
        {
            ifstream fin("students.txt");

            if(!fin)
            {
                cout << "File not found!" << endl;
                break;
            }

            s1.loadFromFile(fin);
            s2.loadFromFile(fin);
            s3.loadFromFile(fin);

            fin.close();

            cout << "Data Loaded Successfully!" << endl;
            break;
        }

        case 5:{

        
            Student::showTotalStudents();
            break;
        }
        case 6:{

        
            cout << "Exiting..." << endl;
            break;
        }
        default:{

        
            cout << "Invalid Choice!" << endl;
        }
    }

    } while(choice != 6);

    return 0;
}