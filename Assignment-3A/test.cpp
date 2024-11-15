#include <iostream>
#include <vector>
#include "station.cpp"
#include "train.cpp"

using namespace std;

int main() {
    try {
        // Create a station with an integer ID
        Station<int> station1(101);

        // Create some lines and platforms
        Line line1("Delhi to Mumbai");
        Line line2("Mumbai to Bangalore");
        Platform platform1;
        Platform platform2;

        // Add lines and platforms to the station
        station1.addLine(line1);
        station1.addLine(line2);
        station1.addPlatform(platform1);
        station1.addPlatform(platform2);

        // Create a train and try scheduling it
        Train train1(1001, false);  // Not a through train
        Train train2(1002, true);   // A through train

        // Try scheduling the train at different times
        if (station1.scheduleTrain(540, train1.isThrough(), 0)) {
            cout << "Train " << train1.getTrainID() << " scheduled successfully on platform 1.\n";
        } else {
            cout << "Train " << train1.getTrainID() << " could not be scheduled.\n";
        }

        if (station1.scheduleTrain(550, train2.isThrough(), 0)) {
            cout << "Train " << train2.getTrainID() << " scheduled successfully on platform 1.\n";
        } else {
            cout << "Train " << train2.getTrainID() << " could not be scheduled.\n";
        }

        // Display station details
        station1.printStationDetails();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
