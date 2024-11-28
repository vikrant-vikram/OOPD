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


int main() {
    vector<Author> authors;

    cout << "Enter the number of authors: ";
    int numAuthors;
    cin >> numAuthors;
    cin.ignore(); // Ignore newline after the number input.

    for (int i = 0; i < numAuthors; ++i) {
        cout << "Enter name of author " << i + 1 << ": ";
        string authorName;
        getline(cin, authorName);

        cout << "Enter affiliation for " << authorName << ": ";
        string affiliationName;
        getline(cin, affiliationName);

        cout << "Is this an institute affiliation? (1 for Yes, 0 for No): ";
        bool isInstitute;
        cin >> isInstitute;
        cin.ignore(); // Ignore newline after the boolean input.

        Affiliation affiliation(affiliationName, isInstitute);
        Author author(authorName, affiliation);
        authors.push_back(author);
    }

    cout << "Enter the title of the publication: ";
    string title;
    getline(cin, title);

    cout << "Enter the journal name: ";
    string journal;
    getline(cin, journal);

    cout << "Enter the publication year: ";
    int year;
    cin >> year;
    cin.ignore();

    cout << "Enter the DOI (Digital Object Identifier): ";
    string doi;
    getline(cin, doi);

    // Create the publication object
    Publication publication(title, journal, authors, year, doi);

    // Print the publication details
    publication.printPublication();

    // Check if there's at least one institute author
    cout << "Has Institute Author: "
         << (publication.hasInstituteAuthor() ? "Yes" : "No") << "\n";

    return 0;
}
