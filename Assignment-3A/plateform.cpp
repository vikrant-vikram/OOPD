#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <ctime>


using namespace std;
class Platform {
private:
    vector<int> scheduledStops;  // To store train stoppage times (in minutes past midnight)

public:
    bool canAccommodate(int trainTime, bool isThroughTrain) {
        int interval = isThroughTrain ? 10 : 30;  // 10 min for through trains, 30 min for others
        for (int stopTime : scheduledStops) {
            if (abs(stopTime - trainTime) < interval) {
                return false;  // Cannot accommodate train if there's a train stop within the interval
            }
        }
        scheduledStops.push_back(trainTime);  // Schedule the train
        return true;
    }

    void printScheduledStops() const {
        for (int stopTime : scheduledStops) {
            cout << "Train stop at: " << stopTime << " minutes past midnight." << std::endl;
        }
    }
};
