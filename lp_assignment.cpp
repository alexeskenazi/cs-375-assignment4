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
    
   
    pair<double, double> solveByCornerPoints() {
        cout << "Trying corner point method instead..." << endl;
        
        vector<pair<double, double>> corners;
        double bestCost = 1e9;
        pair<double, double> bestSolution = {0, 0};
        
        // Need to find intersections of constraint lines
        // Constraint 1: 60X + 60Y >= 300 → X + Y >= 5
        // Constraint 2: 12X + 6Y >= 36 → 2X + Y >= 6  
        // Constraint 3: 10X + 30Y >= 90 → X + 3Y >= 9
        
        // Try intersection of constraint lines
        // Line 1 and Line 2: X + Y = 5, 2X + Y = 6
        // Solve: X = 1, Y = 4
        corners.push_back({1, 4});
        
        // Line 1 and Line 3: X + Y = 5, X + 3Y = 9  
        // Solve: Y = 2, X = 3
        corners.push_back({3, 2});
        
        // Line 2 and Line 3: 2X + Y = 6, X + 3Y = 9
        // From X + 3Y = 9: X = 9 - 3Y
        // Substitute into 2X + Y = 6: 2(9 - 3Y) + Y = 6
        // 18 - 6Y + Y = 6 → 18 - 5Y = 6 → Y = 2.4, X = 1.8
        corners.push_back({1.8, 2.4}); // Fixed calculation
        
        // Check axis intersections too
        corners.push_back({0, 6});  // Y-axis intersection for worst case
        corners.push_back({9, 0});  // X-axis intersection for worst case
        
        cout << "Checking corner points:" << endl;
        for (auto corner : corners) {
            double x = corner.first, y = corner.second;
            if (isFeasible(x, y)) {
                double cost = getCost(x, y);
                cout << "(" << x << ", " << y << ") - Cost: $" << cost;
                if (cost < bestCost) {
                    bestCost = cost;
                    bestSolution = corner;
                    cout << " <- Best so far!";
                }
                cout << endl;
            } else {
                cout << "(" << x << ", " << y << ") - Not feasible" << endl;
            }
        }
        
        return bestSolution;
    }
};

int main() {
    cout << "CS 375 Assignment 4 - Linear Programming" << endl;
    
    DietProblem problem;
    problem.printProblem();
    
    cout << "\n--- Testing Feasibility ---" << endl;
    
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
    
    cout << "\n--- Attempting to Solve ---" << endl;
    
    clock_t start = clock();
    pair<double, double> solution = problem.solveByCornerPoints();
    clock_t end = clock();
    
    double x = solution.first, y = solution.second;
    double totalCost = problem.getCost(x, y);
    
    cout << "\n=== OPTIMAL SOLUTION ===" << endl;
    cout << "Number of cups of drink X: " << x << endl;
    cout << "Number of cups of drink Y: " << y << endl;
    cout << "Minimum cost: $" << totalCost << endl;
    
    cout << "\nNutrient totals provided:" << endl;
    double calories = 60*x + 60*y;
    double vitA = 12*x + 6*y;  
    double vitC = 10*x + 30*y;
    
    cout << "Calories: " << calories << " (required: >= 300)" << endl;
    cout << "Vitamin A: " << vitA << " (required: >= 36)" << endl;
    cout << "Vitamin C: " << vitC << " (required: >= 90)" << endl;
    
    cout << "\nAll constraints satisfied: " << (calories >= 300 && vitA >= 36 && vitC >= 90 ? "YES" : "NO") << endl;
    
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "\nRunning time: " << time << " milliseconds" << endl;
    
    return 0;
}