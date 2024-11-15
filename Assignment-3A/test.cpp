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
        while (1) {

            string lineName;
            cout << "Enter line name (or 'q' to quit): ";
            cin >> lineName;
            if (lineName == "q") {
                break;
            }
            Line line(lineName);
            station1.addLine(line);
        }
        // Line line1("Delhi to Mumbai");
        // Line line2("Mumbai to Bangalore");
        Platform platform1;
        Platform platform2;

        // Add lines and platforms to the station
        // station1.addLine(line1);
        // station1.addLine(line2);
        cout<<"Enter number of plateforms\n";
        int noOffPlatforms;
        cin>>noOffPlatforms;
        for(int i=0;i<noOffPlatforms;i++){
            station1.addPlatform(platform1);
        }


        // Create a train and try scheduling it
        // Train train1(1001, false);  // Not a through train
  // A through train

        // Try scheduling the train at different times
        while(1){

            try {
                int trainNumber;
                int trainTime;
                int platformNumber;
                bool isThrough;
                cout<<"Enter train number, train time, platform number and isThrough\n";
                cin>>trainNumber;
                cin>>trainTime;
                cin>>platformNumber;
                cin>>isThrough;
                Train train1(trainNumber, isThrough);

                if (station1.scheduleTrain(trainTime, isThrough, platformNumber)) {
                    cout << "Train " << train1.getTrainID() << " scheduled successfully on platform 1.\n";
                } else {
                    cout << "Train " << train1.getTrainID() << " could not be scheduled.\n";
                }
            } catch (exception& e) {
                cerr << "Error: " << e.what() << endl;

            }

        }
        // int trainTime;
        // int platformNumber;
        // bool isThrough;
        // cout<<"Enter train time, platform number and isThrough\n";
        // cin>>trainTime;
        // cin>>platformNumber;
        // cin>>isThrough;
        // if (station1.scheduleTrain(540, train1.isThrough(), 0)) {
        //     cout << "Train " << train1.getTrainID() << " scheduled successfully on platform 1.\n";
        // } else {
        //     cout << "Train " << train1.getTrainID() << " could not be scheduled.\n";
        // }

        // if (station1.scheduleTrain(50, train2.isThrough(), 0)) {
        //     cout << "Train " << train2.getTrainID() << " scheduled successfully on platform 1.\n";
        // } else {
        //     cout << "Train " << train2.getTrainID() << " could not be scheduled.\n";
        // }

        // Display station details
        station1.printStationDetails();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
