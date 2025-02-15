#include <iostream>
#include "line.cpp"
#include "plateform.cpp"

using  namespace std;

template <typename T>


class Station {
private:
    T stationID;
     vector<Line> lines;
     vector<Platform> platforms;

public:
    Station(T id) : stationID(id) {}

    void addLine(const Line& line) {
        lines.push_back(line);
    }

    void addPlatform(const Platform& platform) {
        platforms.push_back(platform);
    }

    T getStationID() const {
        return stationID;
    }

    bool scheduleTrain(int trainTime, bool isThroughTrain, int platformIndex) {
        if (platformIndex < 0 || platformIndex >= platforms.size()) {
            throw  out_of_range("Invalid platform index.");
        }
        return platforms[platformIndex].canAccommodate(trainTime, isThroughTrain);
    }

    void printStationDetails() const {
         cout << "Station ID: " << stationID <<  endl;
        for (size_t i = 0; i < lines.size(); ++i) {
             cout << "Line " << i + 1 << ": " << lines[i].getLineName() <<  endl;
        }
        for (size_t i = 0; i < platforms.size(); ++i) {
             cout << "Platform " << i + 1 << ": ";
            platforms[i].printScheduledStops();
        }
    }
};
