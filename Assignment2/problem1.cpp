#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
// changeing just to push
const int MAX_PERSONS = 100; // Define a maximum number of personnel

class Person {
protected:
    string name;
    string email;
    string room;
    string phone;

public:
    Person(const string& name, const string& email, const string& room, const string& phone)
        : name(name), email(email), room(room), phone(phone) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << "\nEmail: " << email
             << "\nRoom: " << room << "\nPhone: " << phone << endl;
    }

    string getName() const {
        return name;
    }
};

class Dean : public Person {
public:
    Dean(const string& name, const string& email, const string& room, const string& phone)
        : Person(name, email, room, phone) {}

    void displayInfo() const override {
        cout << "Dean Information:\n";
        Person::displayInfo();
    }
};

class AssociateDean : public Person {
public:
    AssociateDean(const string& name, const string& email, const string& room, const string& phone)
        : Person(name, email, room, phone) {}

    void displayInfo() const override {
        cout << "Associate Dean Information:\n";
        Person::displayInfo();
    }
};

class Registrar : public Person {
public:
    Registrar(const string& name, const string& email, const string& room, const string& phone)
        : Person(name, email, room, phone) {}

    void displayInfo() const override {
        cout << "Registrar Information:\n";
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
        string name, email, room, phone, position;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, room, ',');
        getline(ss, phone, ',');
        getline(ss, position, ','); // Read position

        Person* person = nullptr;
        if (position == "Dean") {
            person = new Dean(name, email, room, phone);
        } else if (position == "Associate Dean") {
            person = new AssociateDean(name, email, room, phone);
        } else if (position == "Registrar") {
            person = new Registrar(name, email, room, phone);
        } else {
            person = new Person(name, email, room, phone); // Generic person
        }

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
