#include <iostream>
#include "KnapsackProfitCalc.h"

using namespace std;

int main()
{
    vector<KnapsackItem> knapsackItems = {
        KnapsackItem(2, 40),
        KnapsackItem((float)3.14, 50),
        KnapsackItem((float)1.98, 100),
        KnapsackItem(5, 95),
        KnapsackItem(3, 30),
    };

    KnapsackProfitCalc calc(
        knapsackItems,
        10
    );

    cout << "Max profit: " << calc.getMaxProfit();

    return 0;
}
