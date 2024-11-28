#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Affiliation {
    private:
        string name;
        bool isInstitute;

    public:
        Affiliation(const string& name, bool isInstitute = false)
            : name(name), isInstitute(isInstitute) {}
        string getName() const { return name; }
        bool isInstituteAffiliation() const { return isInstitute; }
};

class Author {
    private:
        string name;
        Affiliation affiliation;
    public:
        Author(const string& name, const Affiliation& affiliation)
            : name(name), affiliation(affiliation) {}
        string getName() const { return name; }
        Affiliation getAffiliation() const { return affiliation; }

        void printAuthor() const {
            cout << name << " (" << affiliation.getName() << ")";
        }


};

class Publication {
    private:
        string title;
        string venue;
        vector<Author> authors;
        int year;
        string doi;  // Optional DOI
public:
    Publication(const string& title, const string& venue,
                const vector<Author>& authors, int year,
                const string& doi)
        : title(title), venue(venue), authors(authors), year(year), doi(doi) {}
    bool hasInstituteAuthor() const {
        for (auto it = authors.cbegin(); it != authors.cend(); ++it) {
            if (it->getAffiliation().isInstituteAffiliation()) {
                return true;
            }
        }
        return false;
    }

    bool hasAuthor(const string& authorName) const {
        // cout << "Author Name: " << authorName << "\n";
        for (const auto& author : authors) {
            // cout << author.getName()<<authorName << "\n";
            if (author.getName() == authorName) {
                return true;
            }
        }
        return false;
    }
    int noOfAuthor() const {
        int temp = 0;
        // cout << "Author Name: " << authorName << "\n";
        for (const auto& author : authors) {
            // cout << author.getName()<<authorName << "\n";
            temp+=1;
        }
        return temp;
    }

    void printPublication() const {
        cout << "Title: " << title << "\n";
        cout << "Venue: " << venue << "\n";
        cout << "Year: " << year << "\n";
        cout << "Authors: ";
        for (auto it = authors.cbegin(); it != authors.cend(); ++it) {
            it->printAuthor();
            if (it + 1 != authors.cend()) {
                cout << ", ";
            }
        }
        cout << "\n";
        cout << "DOI: " << doi << "\n";
    }

    Publication getPublication() const {
        return *this;
    }
};

// int main() {
//     Affiliation instituteAffiliation("Institute of Research", true);
//     Affiliation universityAffiliation("University of Science");
//     Author author1("Dr. Alice Smith", instituteAffiliation);
//     Author author2("Dr. Bob Johnson", universityAffiliation);
//     vector<Author> authors;
//     authors.push_back(author1);
//     authors.push_back(author2);
//     Publication publication("Groundbreaking Research in AI",
//                             "International Journal of AI Research",
//                             authors, 2024, "10.1000/j.jair.2024.01.001");
//     publication.printPublication();
//     cout << "Has Institute Author: "
//               << (publication.hasInstituteAuthor() ? "Yes" : "No") << "\n";

//     return 0;
// }
