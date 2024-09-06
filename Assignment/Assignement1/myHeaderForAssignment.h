#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>



const int numYears = 40;//USed to Create  Array of to Store Date
const int baseYear = 2000;
using namespace std;


//Class is Used to store Data abput property
//Such as LTCG , Growth Rate

class Property{
    private :
        double** data;
    public:

        Property(){
            //This Constuctor Reads the CSV file  price-LTCG.csv and stores in data
            data = new double*[numYears];
            for (int i = 0; i < numYears; i++) {
                data[i] = new double[2];  // Pair of LTCG rate and property rate for each year
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

                string input = ss.str();
                size_t pos1 = input.find(',');
                size_t pos2 = input.find(',', pos1 + 1);
                string value1 = input.substr(0, pos1);
                double grouth = stod(input.substr(pos1 + 1, pos2 - pos1 - 1));
                double LTCG = stod(input.substr(pos2 + 1));
                pos1 = value1.find("-");
                year = stoi(value1.substr(0,pos1));

                // In 2D array at index[][0]  growth rate
                // and at index[1] LTCG is being stored
                data[year - baseYear][0] = (grouth);
                data[year - baseYear][1] = (LTCG);

                // cout<<year << " Grouth Price :"<<grouth<<" LTCG :" <<LTCG<<endl;
                // year++;
            }
        }
        double getInflationRate(int sellingYear){
            //This function takes selling year and return corresponging years LTCGRate
            return data[sellingYear - baseYear][1];
        }
        double getGrowthPrice( int sellingYear){
            //This function takes selling year and return corrresponding growth rate
            return data[sellingYear - baseYear][0];
        }
};



//This class have been is used to inplement effect of LTCG and Growth on property
class LTCG{
    private:
        double purchasedAT;
        int tillYear;
        int yearOfPurchase;
        double ltcg;
    public:
        LTCG(double purchasedAt, int year, int purchasingYear){
            purchasedAT = purchasedAt;
            tillYear = year;
            yearOfPurchase = purchasingYear;
            ltcg = 20;

        }

        double calculateSellingPrice(  Property p) {
            double sellAt = purchasedAT;
            // cout<<purchasedAT;
            int year = tillYear;
            int current = yearOfPurchase;
            double temp = 0;
            while (  current < year) {
                // cout<<sellAt<< "Year "<< current << " Grouth "<<p.getGrowthPrice(current) << " LTCG "<<p.getLTCGRate(current) <<endl;
                sellAt*=(1+((p.getGrowthPrice(current) - p.getInflationRate(current))/100));
                current+=1;
            }
            return sellAt;
        }
        double calculateLTCG(Property p){
            double sellingPrice = calculateSellingPrice(p);
            if( purchasedAT){
                double profit = sellingPrice - purchasedAT;
                profit = profit>0?profit:0;
                return profit*(ltcg/100);
            }
            else {
                throw "Error";
            }
        }


};
