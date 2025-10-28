#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Assignment 4 - Linear Programming
// Diet problem: minimize cost of drinks X and Y

class DietProblem {
public:
    // Problem data
    double drinkX_cost = 0.12;
    double drinkY_cost = 0.15;
    
    // Nutritional content per cup
    double drinkX_calories = 60;
    double drinkX_vitA = 12;
    double drinkX_vitC = 10;
    
    double drinkY_calories = 60;
    double drinkY_vitA = 6;
    double drinkY_vitC = 30;
    
    // Requirements
    double min_calories = 300;
    double min_vitA = 36;
    double min_vitC = 90;
    
    void printProblem() {
        cout << "Diet Optimization Problem:" << endl;
        cout << "Minimize: " << drinkX_cost << "*X + " << drinkY_cost << "*Y" << endl;
        cout << "Subject to:" << endl;
        cout << "  " << drinkX_calories << "*X + " << drinkY_calories << "*Y >= " << min_calories << " (calories)" << endl;
        cout << "  " << drinkX_vitA << "*X + " << drinkY_vitA << "*Y >= " << min_vitA << " (vitamin A)" << endl;
        cout << "  " << drinkX_vitC << "*X + " << drinkY_vitC << "*Y >= " << min_vitC << " (vitamin C)" << endl;
        cout << "  X, Y >= 0" << endl;
    }
    
    // Check if a solution is feasible
    bool isFeasible(double x, double y) {
        if (x < 0 || y < 0) return false;
        if (drinkX_calories * x + drinkY_calories * y < min_calories) return false;
        if (drinkX_vitA * x + drinkY_vitA * y < min_vitA) return false;
        if (drinkX_vitC * x + drinkY_vitC * y < min_vitC) return false;
        return true;
    }
    
    double getCost(double x, double y) {
        return drinkX_cost * x + drinkY_cost * y;
    }
};

int main() {
    cout << "CS 375 Assignment 4 - Linear Programming" << endl;
    
    DietProblem problem;
    problem.printProblem();
    
    cout << "\n--- Testing Feasibility ---" << endl;
    
    // Try some test points
    vector<pair<double, double>> testPoints = {
        {0, 0}, {5, 5}, {10, 0}, {0, 10}, {3, 2}
    };
    
    for (auto point : testPoints) {
        double x = point.first, y = point.second;
        bool feasible = problem.isFeasible(x, y);
        cout << "Point (" << x << ", " << y << "): ";
        if (feasible) {
            cout << "Feasible, cost = $" << problem.getCost(x, y) << endl;
        } else {
            cout << "Not feasible" << endl;
        }
    }
    
    cout << "\nNext step: Need to implement optimization algorithm..." << endl;
    
    return 0;
}