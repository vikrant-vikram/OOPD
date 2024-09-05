#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAX_YEARS = 30;


class InflationRate {
private:
    double rates[MAX_YEARS];

public:
    void loadRates(const string& filename) {
        ifstream file(filename);
        for (int i = 0; i < MAX_YEARS; ++i) {
            if (!(file >> rates[i])) {
                throw runtime_error("Not enough data in file");
            }
        }
    }

    double getRate(int year) const {
        if (year < 2001 || year > 2030) {
            throw out_of_range("Year out of range");
        }
        return rates[year - 2001];
    }
};


class TaxRate {
private:
    double rate;

public:
    TaxRate(double r) : rate(r) {}
    double getRate() const { return rate; }
};

double calculateSellingPrice(double initialPrice, int buyYear, int sellYear, const InflationRate& inflation) {
    double price = initialPrice;
    for (int year = buyYear; year < sellYear; ++year) {
        double propertyIncrease = 0.15; // 15% per annum
        double inflationRate = inflation.getRate(year);
        price *= (1 + (propertyIncrease - inflationRate) / 100);
    }
    return price;
}

double calculateLTCG(double sellingPrice, double costPrice, const TaxRate& taxRate) {
    double profit = sellingPrice - costPrice;
    return profit * taxRate.getRate();
}

int main() {
    InflationRate inflation;
    inflation.loadRates("inflation_rates.csv");

    TaxRate oldTaxRate(0.20);
    TaxRate newTaxRate(0.125);

    double initialPrice = 5000000; // 50 lakhs
    int buyYear = 2010;

    int sellYear;
    cout << "Enter the year of selling (between 2011 and 2030): ";
    cin >> sellYear;

    if (sellYear <= buyYear || sellYear > 2030) {
        cout << "Invalid selling year. It should be between 2011 and 2030." << endl;
        return 1;
    }

    double sellingPrice = calculateSellingPrice(initialPrice, buyYear, sellYear, inflation);
    double oldLTCG = calculateLTCG(sellingPrice, initialPrice, oldTaxRate);

    double newSellingPrice = sellingPrice; // No inflation adjustment in new scheme
    double newLTCG = calculateLTCG(newSellingPrice, initialPrice, newTaxRate);

    cout << fixed << setprecision(2);
    cout << "Estimated selling price: Rs. " << sellingPrice << endl;
    cout << "Old LTCG scheme tax: Rs. " << oldLTCG << endl;
    cout << "New LTCG scheme tax: Rs. " << newLTCG << endl;

    double difference = newLTCG - oldLTCG;
    cout << "Difference in tax (New - Old): Rs. " << difference << endl;
    cout << "The " << (difference > 0 ? "new" : "old") << " scheme leads to higher taxes by Rs. " << abs(difference) << endl;

    return 0;
}
