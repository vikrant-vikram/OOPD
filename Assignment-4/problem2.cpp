#include <iostream>
#include <fstream>
#include <iso646.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>

#include "problem1h.cpp" // Assuming this contains Affiliation, Author, and Publication classes

using namespace std;

// ANSI color codes for terminal output
const string colors[] = {
    "\033[31m", // Red
    "\033[32m", // Green
    "\033[33m", // Yellow
    "\033[34m", // Blue
    "\033[35m", // Magenta
    "\033[36m"  // Cyan
};
const string resetColor = "\033[0m"; // Reset to default color

// Function to trim leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
}

// Function to parse a BibTeX entry and return key-value pairs
void parseBibTeX(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Could not open file!" << endl;
        return;
    }

    string line;
    string currentEntry;
    bool insideEntry = false;
    int colorIndex = 0; // Index to cycle through colors

    while (getline(file, line)) {
        line = trim(line);

        // Skip empty lines and comments
        if (line.empty() || line[0] == '%') {
            continue;
        }

        unordered_map<string, string> keyValueMap;
        unordered_map<string, string> authors;

        // Check for the start of an entry (e.g., @ARTICLE, @INPROCEEDINGS)
        if (line.find("@") == 0) {
            insideEntry = true;
            if (insideEntry) {
                stringstream entryStream(currentEntry);
                string key, value;
                while (getline(entryStream, key, '=') && getline(entryStream, value, '}')) {
                    key = trim(key);
                    value = trim(value);
                    // Remove surrounding braces or quotes if any
                    if (value.front() == '{' || value.front() == '"') value = value.substr(1, value.length() - 1);

                    // Clean key if it starts with a comma
                    if (key.front() == ',') {
                        key = key.substr(1); // Remove the leading comma
                        key = trim(key);
                    }

                    // Special handling for `author` field
                    if (key == "author") {
                        vector<string> authorsList;
                        size_t pos = 0;
                        string delimiter = " and ";
                        while ((pos = value.find(delimiter)) != string::npos) {
                            authorsList.push_back(trim(value.substr(0, pos)));
                            value.erase(0, pos + delimiter.length());
                        }
                        authorsList.push_back(trim(value)); // Add the last author
                        for (const auto& author : authorsList) {
                            authors[author] = "IIITD"; // Assign a default affiliation
                        }
                    } else {
                        keyValueMap[key] = value;
                    }
                }

                // Create Author objects
                vector<Author> authorObjects;
                for (const auto& pair : authors) {
                    Affiliation affiliation(pair.second, true); // Default to institute affiliation
                    Author author(pair.first, affiliation);
                    authorObjects.push_back(author);
                }

                // Create a Publication object
                if (!authorObjects.empty()) {
                    Publication publication(
                        keyValueMap["title"],
                        keyValueMap["venue"],
                        authorObjects,
                        stoi(keyValueMap["year"]),
                        keyValueMap["doi"]
                    );

                    // Print publication details with a unique color
                    cout << colors[colorIndex % 6]; // Cycle through the color array
                    publication.printPublication();
                    cout << "Has Institute Author: "
                         << (publication.hasInstituteAuthor() ? "Yes" : "No") << endl;
                    cout << resetColor; // Reset to default color

                    colorIndex++; // Move to the next color
                }

                currentEntry.clear(); // Reset the current entry
            }

            currentEntry = line;
        } else {
            // Append lines to the current entry if inside an entry
            currentEntry += " " + line;
        }

        // Check for the end of an entry (closing brace)
        if (line.find("\n") && insideEntry) {
            stringstream entryStream(currentEntry);
            string key, value;
            while (getline(entryStream, key, '=') && getline(entryStream, value, '}')) {
                key = trim(key);
                value = trim(value);
                // Remove surrounding braces or quotes if any
                if (value.front() == '{' || value.front() == '"') value = value.substr(1, value.length() - 1);

                // Clean key if it starts with a comma
                if (key.front() == ',') {
                    key = key.substr(1); // Remove the leading comma
                    key = trim(key);
                }

                // Special handling for `author` field
                if (key == "author") {
                    vector<string> authorsList;
                    size_t pos = 0;
                    string delimiter = " and ";
                    while ((pos = value.find(delimiter)) != string::npos) {
                        authorsList.push_back(trim(value.substr(0, pos)));
                        value.erase(0, pos + delimiter.length());
                    }
                    authorsList.push_back(trim(value)); // Add the last author
                    for (const auto& author : authorsList) {
                        authors[author] = "IIITD"; // Assign a default affiliation
                    }
                } else {
                    keyValueMap[key] = value;
                }
            }

            currentEntry.clear(); // Reset the current entry
            insideEntry = false;
        }
    }
}

int main() {
    string filePath = "publist.bib"; // Provide the correct file path
    parseBibTeX(filePath);
    return 0;
}
