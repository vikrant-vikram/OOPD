#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>




//Class is Used to store Data abput property
//Such as Inflation , Growth Rate

class Property{
    private :
        double** data;
    public:

        Property(){
            //This Constuctor Reads the CSV file  price-inflation.csv and stores in data
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

                string input = ss.str();
                size_t pos1 = input.find(',');
                size_t pos2 = input.find(',', pos1 + 1);
                string value1 = input.substr(0, pos1);
                double grouth = stod(input.substr(pos1 + 1, pos2 - pos1 - 1));
                double inflation = stod(input.substr(pos2 + 1));
                pos1 = value1.find("-");
                year = stoi(value1.substr(0,pos1));

                // In 2D array at index[][0]  growth rate
                // and at index[1] Inflation is being stored
                data[year - baseYear][0] = (grouth);
                data[year - baseYear][1] = (inflation);

                // cout<<year << " Grouth Price :"<<grouth<<" Inflation :" <<inflation<<endl;
                // year++;
            }
        }
        double getInflationRate(int sellingYear){
            //This function takes selling year and return corresponging years InflationRate
            return data[sellingYear - baseYear][1];
        }
        double getGrowthPrice( int sellingYear){
            //This function takes selling year and return corrresponding growth rate
            return data[sellingYear - baseYear][0];
        }
};


//This class have been is used to inplement effect of Inflation and Growth on property
class Inflation{
    private:
        double purchasedAT;
        int tillYear;
        int yearOfPurchase;
    public:
        Inflation(double purchasedAt, int year, int purchasingYear){
            purchasedAT = purchasedAt;
            tillYear = year;
            yearOfPurchase = purchasingYear;
        }

        double calculateSellingPrice(  Property p) {
            //This function takes hostorical data of Propery to calculate selling Price

            double sellAt = purchasedAT;
            // cout<<purchasedAT;
            int year = tillYear;
            int current = yearOfPurchase;
            double temp = 0;
            while (  current < year) {
                // cout<<sellAt<< "Year "<< current << " Grouth "<<p.getGrowthPrice(current) << " Inflation "<<p.getInflationRate(current) <<endl;
                sellAt*=(1+((p.getGrowthPrice(current) - p.getInflationRate(current))/100));
                current+=1;
            }
            return sellAt;
        }


};





int main() {
    Property property;
    int yearOfSelling, yearOfPurchase;
    double PurchasingPrice;
    cout<<"CSV file containe data from 2001 to 2029 so choose year of sellign and purchase within the range"<<endl;
    cout<<"Enter year of Purchase : ";
    cin >> yearOfPurchase;
    cout<<"Enter year of Sellig : ";
    cin >> yearOfSelling;
    if( yearOfPurchase< 2001 || yearOfPurchase > yearOfSelling){
        throw out_of_range("Year of Purchase Out of Range");

    }

    if( yearOfSelling< yearOfPurchase || yearOfSelling> 2029){
        // cout<<" Year of Sellling have invalid range\n";
        throw out_of_range("Year of Selling Out of Range");
    }
    cout<< "Enter Purchasing Price : ";
    cin>>PurchasingPrice;
    cout<<endl;
    Inflation inf(PurchasingPrice, yearOfSelling, yearOfPurchase);
    cout<<"Selling Price for the Propery in Year "<< yearOfSelling<< " be " <<inf.calculateSellingPrice(property)<< "Rs. Only\n";
    return 0;
}
