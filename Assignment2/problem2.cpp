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
    string department;

public:
    Person(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : name(name), email(email), room(room), phone(phone),  department(department){}

    virtual void displayInfo() const {
        cout<< "Department: "<<department<<endl;
        cout << "Name: " << name << "\nEmail: " << email
             << "\nRoom: " << room << "\nPhone: " << phone << endl;
    }

    string getName() const {
        return name;
    }
};

class Head : public Person {
public:
    Head(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        cout << "Heead Information:\n";
        Person::displayInfo();
    }
};

class CSE : public Person {
public:
    CSE(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        cout << "CSE department  Information:\n";
        Person::displayInfo();
    }
};


class CB : public Person {
public:
    CB(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        cout << "CB Department Information:\n";
        Person::displayInfo();
    }
};
class SSH : public Person {
public:
    SSH(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        cout << "SSH Department Information:\n";
        Person::displayInfo();
    }
};
class Math : public Person {
public:
    Math(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        cout << "Math Department Information:\n";
        Person::displayInfo();
    }
};

class ECE : public Person {
public:
    ECE(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        cout << "ECE Department Information:\n";
        Person::displayInfo();
    }
};

class HCD : public Person {
public:
    HCD(const string& name, const string& email, const string& room, const string& phone,const string&  department)
        : Person(name, email, room, phone, department) {}

    void displayInfo() const override {
        // cout << "ECE Department Information:\n";
        Person::displayInfo();
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

    Person* findPerson(const string& name) {
        for (int i = 0; i < count; ++i) {
            if (persons[i]->getName() == name) {
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
        // Read position
        //
        // cout<<department<<endl;

        Person* person = nullptr;
        if (position == "Head"){
            person = new Head(name, email, room, phone, department);
        }
        else if (department == "CB") {
            person = new CB(name, email, room, phone, department);
        } else if (department == "Math") {
            person = new Math(name, email, room, phone, department);
        } else if (department == "CSE") {
            person = new CSE(name, email, room, phone, department);

        } else if (department == "SSH") {
            person = new SSH(name, email, room, phone, department);

        }
        else if (department == "ECE") {
            person = new ECE(name, email, room, phone, department);

        }
        else{
            person = new HCD(name, email, room, phone, department);

        }

        adminData.addPerson(person);
    }
}

int main() {
    const string filename = "iiitd_faculty_data.csv";
    AdminData adminData;

    try {
        loadAdminData(filename, adminData);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }


    try{


    string name;
    cout << "Enter the name of the person: ";
    getline(cin, name);

    Person* person = adminData.findPerson(name);
    if (person) {
        person->displayInfo();
    } else {
        cout << "Person not found." << endl;
    }

    }
    catch (...){
        cout<<"give proper input"<<endl;
    }

    return 0;
}
