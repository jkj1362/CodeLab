// Rebalancer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>  // for output manipulator std::setprecision()

std::string nameInput()
{
    std::cout << "Name: ";
    std::string name{};
    std::cin >> name;

    return name;
}

double targetInput()
{
    std::cout << "Target proportion in %: ";
    double target{};
    std::cin >> target;

    return target;
}

double calcInitialAmount(double total, double targetPercent)
{
    double initial{ total * (targetPercent / 100) };

    return initial;
}

double currentInput(std::string_view name)
{
    std::cout << name << ": ";
    double amountCurrent{};
    std::cin >> amountCurrent;

    return amountCurrent;
}

double calcCurrentProportion(std::string_view name, double item, double total)
{
    std::cout << name << ": ";
    double percent{ 100 * item / total };

    return percent;
}

void modifyProportion(std::string_view name, double currentPercent, double targetPercent, double currentTotal)
{
    std::cout << name << ": ";
    double disparity{(currentPercent - targetPercent)};
    std::cout << disparity << "%" << "\n";

    if (disparity > 0)
    {
        std::cout << "Overproportion. Sell: " << (disparity * currentTotal) / 100 << "\n";
    }
    else if (disparity < 0)
    {
        std::cout << "Underproportion. Buy: " << -(disparity * currentTotal) / 100 << "\n";
    }
    else
    {
        std::cout << "No change: Maintain this proportion." << "\n";
    }
}

int main()
{
    // Get user input for total asset amount
    std::cout << "Total asset amount: ";
    double initTotal;
    std::cin >> initTotal;
    
    while(true)
    {
        std::cout << "\n";
        // Get user input for investment item information including names and target proportions.
        // Refactor with array in the future.
        std::cout << "Type in items and target proportions." << "\n";
        std::cout << "Item #1" << '\n';
        std::string oneName{ nameInput() };
        double oneTargetPerc{ targetInput() };

        std::cout << "Item #2" << '\n';
        std::string twoName{ nameInput() };
        double twoTargetPerc{ targetInput() };

        std::cout << "Item #3" << '\n';
        std::string threeName{ nameInput() };
        double threeTargetPerc{ targetInput() };

        if (oneTargetPerc + twoTargetPerc + threeTargetPerc != 100)
        {
            std::cout << "Wrong percentage. Sum of all proportions should be 100%. Try again.\n";
        }

        else
        {
            std::cout << "\n";
            // Calculate target amount to invest
            std::cout << "Target amount of initial investment\n";

            // Force fixed notation and show 2 decimal places
            std::cout << std::fixed << std::setprecision(2);

            double oneInitial{ calcInitialAmount(initTotal, oneTargetPerc) };
            std::cout << oneName << ": " << oneInitial << '\n';

            double twoInitial{ calcInitialAmount(initTotal, twoTargetPerc) };
            std::cout << twoName << ": " << twoInitial << '\n';

            double threeInitial{ calcInitialAmount(initTotal, threeTargetPerc) };
            std::cout << threeName << ": " << threeInitial << '\n';

            std::cout << "\n";
            // Get input of current value for each item
            std::cout << "Current amount of each item\n";

            double oneCurrent{ currentInput(oneName) };
            double twoCurrent{ currentInput(twoName) };
            double threeCurrent{ currentInput(threeName) };

            double currentTotal{ oneCurrent + twoCurrent + threeCurrent };
            std::cout << "Current gross value: " << currentTotal << '\n';

            std::cout << "Percentage growth/loss of asset: ";
            std::cout << (currentTotal - initTotal) * 100 / initTotal << "%\n";

            std::cout << "\n";
            std::cout << "Current proportion\n";
            double oneCurrentPerc{ calcCurrentProportion(oneName, oneCurrent, currentTotal) };
            std::cout << oneCurrentPerc << "%\n";

            double twoCurrentPerc{ calcCurrentProportion(twoName, twoCurrent, currentTotal) };
            std::cout << twoCurrentPerc << "%\n";

            double threeCurrentPerc{ calcCurrentProportion(threeName, threeCurrent, currentTotal) };
            std::cout << threeCurrentPerc << "%\n";

            std::cout << "\n";
            std::cout << "Percentage point disparity in proportion \n";
            modifyProportion(oneName, oneCurrentPerc, oneTargetPerc, currentTotal);
            modifyProportion(twoName, twoCurrentPerc, twoTargetPerc, currentTotal);
            modifyProportion(threeName, threeCurrentPerc, threeTargetPerc, currentTotal);
            break;
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
