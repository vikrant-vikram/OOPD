
// Dean
// Associate Dean
// Administrative Officer
// Assistant Administrative Officer
// Junior Administrative Officer



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_PERSONS = 110; // Define a maximum number of personnel

class Person {
protected:
    string name;
    string email;
    string room;
    string phone;
    string position;
    string department;

public:
    Person(const string& name, const string& email, const string& room, const string& phone,const string&  Position,const string& department)
        : name(name), email(email), room(room), phone(phone),  position(Position), department(department){}

    virtual void displayInfo() const {
        // cout<< "Department: "<<department<<endl;


        cout << "Name: " << name << "\nEmail: " << email
             << "\nRoom: " << room << "\nPhone: " << phone << endl;
    }

    string getPosition() const {
        return position;
    }
};

class AdminData {
private:
    Person* persons[MAX_PERSONS];
    int count;

public:
    AdminData() : count(0) {}

    ~AdminData() {
        for (int i = 0; i < count; ++i) {
            delete persons[i];
        }
    }

    void addPerson(Person* person) {
        if (count < MAX_PERSONS) {
            persons[count++] = person;
        } else {
            cout << "Max capacity reached. Cannot add more persons." << endl;
        }
    }

    Person* findPerson(const string& Position) {
        for (int i = 0; i < count; ++i) {
            // cout<<persons[i]->getPosition()<<endl;
            if (persons[i]->getPosition() == Position) {
                return persons[i];
            }
        }
        return nullptr;
    }
};

void loadAdminData(const string& filename, AdminData& adminData) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error opening file.");
    }

    string line;
    getline(file, line); // Skip the header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, room, phone, position, department;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, room, ',');
        getline(ss, phone, ',');
        getline(ss, position, ',');
        getline(ss, department, ','); // Read position

        // cout<<department<<endl;

        Person* person = nullptr;

        person = new Person(name, email, room, phone, position, department);



        adminData.addPerson(person);
    }
}

int main() {
    const string filename = "iiit_admin_data.csv";
    AdminData adminData;

    try {
        loadAdminData(filename, adminData);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    string name;
    // cout << "Enter the name of the Deapratment: ";
    // getline(cin, name);
    // }
    int days;
    try{
        cout << "Enter no of days ";

        cin>>days;
    }
    catch (...){
        cout<<"give proper input"<<endl;
    }
    Person* person;
    if(days<=0)
    cout<<"Invailid no of days\n";
    else if(days<=3){
        cout <<"Yout complaint have been  esca-lated to Junior Administrative Officer\n";
        person = adminData.findPerson("Junior Administrative Officer");
    }

    else if(days<=6){
        cout <<"Yout complaint have been  esca-lated to Assistant Administrative Officer\n";

        person = adminData.findPerson("Assistant Administrative Officer");

    }
    else if(days<=9){
        cout <<"Yout complaint have been  esca-lated to Administrative Officer\n";

        person = adminData.findPerson("Administrative Officer");

    }
    else if(days<=12){
        cout <<"Yout complaint have been  esca-lated to Associate Dean\n";
        person = adminData.findPerson("Associate Dean");

    }
    else if(days>12){
        cout <<"Yout complaint have been  esca-lated to Dean\n";
        person = adminData.findPerson("Dean");
    }


    if (person) {
        person->displayInfo();
    } else {
        cout << "Wrong input Given." << endl;
    }


    return 0;
}
