#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "myHeaderForAssignment.h"

using namespace std;



class NewLTCG{
    private:
        double LTCG;
        double purchasedAT;
        int tillYear;
        int yearOfPurchase;
    public:
        NewLTCG(double purchasedAt, int year, int purchasingYear){
            LTCG = 12.5;
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
                sellAt*=(1+p.getGrowthPrice(current));
                current+=1;
            }
            return sellAt;
        }

        double calculateLTCG(Property p){
            double sellingPrice = calculateSellingPrice(p);
            if( purchasedAT){
                double profit = sellingPrice - purchasedAT;
                profit = profit>0?profit:0;
                return profit*(LTCG/100);
            }
            else {
                throw "Error";
            }
        }
};



int main (){

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

    LTCG infOld(PurchasingPrice, yearOfSelling, yearOfPurchase);
    cout<< "Enter Purchasing Price : ";
    cin>>PurchasingPrice;
    cout<<endl;
    NewLTCG infNew(PurchasingPrice, yearOfSelling, yearOfPurchase);
    cout<<fixed<<"Selling Price for the Propery in Year "<< yearOfSelling<< " be " <<infNew.calculateSellingPrice(property)<< "Rs. Only\n";
    cout<<fixed<< "New Long-term Capital Gains Tax :"<< infNew.calculateLTCG(property)<<endl;
    cout<<fixed<< "Old Long-term Capital Gains Tax :"<< infOld.calculateLTCG(property)<<endl;
    cout<<fixed<< "Defference beteen New and Old  Long-term Capital Gains Tax :"<< infNew.calculateLTCG(property)- infOld.calculateLTCG(property)<<endl;

    return 0;

}
