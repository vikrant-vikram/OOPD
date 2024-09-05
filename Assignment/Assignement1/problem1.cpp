#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

const int numYears = 40;

const int baseYear = 2000;

using namespace std;

class Property{
    private :
        double** data;
    public:

        Property(){
            data = new double*[numYears];
            for (int i = 0; i < numYears; i++) {
                data[i] = new double[2];  // Pair of inflation rate and property rate for each year
            }
            ifstream file("price-inflation.csv");
            if (!file.is_open()) {
                throw out_of_range("Error opening file.");
            }
            string line;
            int year = baseYear;
            stringstream ss;
            getline(file,line);
            while (std::getline(file, line) ) {
                stringstream ss(line);
                // cout<<ss.str();
                string input = ss.str();
                size_t pos1 = input.find(',');
                size_t pos2 = input.find(',', pos1 + 1);

                string value1 = input.substr(0, pos1);


                double grouth = stod(input.substr(pos1 + 1, pos2 - pos1 - 1));
                double inflation = stod(input.substr(pos2 + 1));
                pos1 = value1.find("-");
                year = stoi(value1.substr(0,pos1));

                // cout << value1 << std::endl;
                // cout << value2 << std::endl;
                // cout << value3 << std::endl;


                data[year - baseYear][0] = grouth;
                data[year - baseYear][1] = inflation;
                cout<<year << " Grouth Price :"<<grouth<<" Inflation :" <<inflation<<endl;
                // year++;
            }
        }
        double getInflationRateTill(int sellingYear){

            return data[sellingYear - baseYear][1];
        }
        double getGrouthPrice( int sellingYear){
            return data[sellingYear - baseYear][0];
        }
};

class Inflation{
    private:
        double purchasedAT;
    public:
        Inflation(double purchasedAt){
            purchasedAt = purchasedAt;
        }

        double calculateSellingPrice( int year , Property p) {
            double sellAt = purchasedAT;
            int current = 2010;
            double temp = 0;
            while (  current <= year) {
                cout<<temp<< "Year "<< current << " Grouth "<<p.getGrouthPrice(current) << " Inflation "<<p.getInflationRateTill(current) <<endl;
                sellAt= sellAt *(1+((p.getGrouthPrice(current) - p.getInflationRateTill(current))/100));
                current+=1;
            }
            return sellAt;
        }


};





int main() {
    Property property;
    int year;
    double at;
    cin >> year;
    cin>>at;
    Inflation inf(at);
    cout<<inf.calculateSellingPrice(year,property)<<endl;
    return 0;
}
