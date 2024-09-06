#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

#include "myHeaderForAssignment.h"

using namespace std;


//Class is Used to store Data abput property
//Such as LTCG , Growth Rate



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
    LTCG inf(PurchasingPrice, yearOfSelling, yearOfPurchase);
    cout<<fixed<<"Selling Price for the Propery in Year "<< yearOfSelling<< " be " <<inf.calculateSellingPrice(property)<< " Rs. Only\n";
    return 0;
}
