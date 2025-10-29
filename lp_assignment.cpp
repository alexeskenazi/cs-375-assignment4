#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Assignment 4 - Linear Programming Diet Problem
// Minimize cost of drinks X and Y subject to nutritional constraints
// Using corner point method to solve the LP problem

class DietProblem {
public:
    // Cost per cup (objective function coefficients)
    double drinkX_cost = 0.12;
    double drinkY_cost = 0.15;
    
    // Nutritional content per cup (constraint coefficients)
    double drinkX_calories = 60;
    double drinkX_vitA = 12;
    double drinkX_vitC = 10;
    
    double drinkY_calories = 60;
    double drinkY_vitA = 6;
    double drinkY_vitC = 30;
    
    // Daily nutritional requirements (RHS values)
    double min_calories = 300;
    double min_vitA = 36;
    double min_vitC = 90;
    
    // Display the linear programming problem formulation
    void printProblem() {
        cout << "Diet Optimization Problem:" << endl;
        cout << "Minimize: " << drinkX_cost << "*X + " << drinkY_cost << "*Y" << endl;
        cout << "Subject to:" << endl;
        cout << "  " << drinkX_calories << "*X + " << drinkY_calories << "*Y >= " << min_calories << " (calories)" << endl;
        cout << "  " << drinkX_vitA << "*X + " << drinkY_vitA << "*Y >= " << min_vitA << " (vitamin A)" << endl;
        cout << "  " << drinkX_vitC << "*X + " << drinkY_vitC << "*Y >= " << min_vitC << " (vitamin C)" << endl;
        cout << "  X, Y >= 0 (non-negativity)" << endl;
    }
    
    // Check if a solution point satisfies all constraints
    bool isFeasible(double x, double y) {
        if (x < 0 || y < 0) return false;
        if (drinkX_calories * x + drinkY_calories * y < min_calories) return false;
        if (drinkX_vitA * x + drinkY_vitA * y < min_vitA) return false;
        if (drinkX_vitC * x + drinkY_vitC * y < min_vitC) return false;
        return true;
    }
    
    // Calculate total cost for given amounts of drinks X and Y
    double getCost(double x, double y) {
        return drinkX_cost * x + drinkY_cost * y;
    }
    
   
    // Solve using corner point method (fundamental theorem of LP)
    // Optimal solution occurs at a vertex of the feasible region
    pair<double, double> solveByCornerPoints() {
        cout << "Using corner point method to solve LP..." << endl;
        
        vector<pair<double, double>> corners;
        double bestCost = 1e9;
        pair<double, double> bestSolution = {0, 0};
        
        // Convert constraints to standard form for intersection calculations
        // Constraint 1: 60X + 60Y >= 300 → X + Y >= 5 (simplified by dividing by 60)
        // Constraint 2: 12X + 6Y >= 36 → 2X + Y >= 6 (simplified by dividing by 6)
        // Constraint 3: 10X + 30Y >= 90 → X + 3Y >= 9 (simplified by dividing by 10)
        
        // Find intersection points of constraint boundary lines
        // These form the vertices of the feasible region
        
        // Intersection 1: Lines X + Y = 5 and 2X + Y = 6
        // Subtract: X = 1, substitute back: Y = 4
        corners.push_back({1, 4});
        
        // Intersection 2: Lines X + Y = 5 and X + 3Y = 9
        // Subtract: 2Y = 4, so Y = 2, X = 3
        corners.push_back({3, 2});
        
        // Intersection 3: Lines 2X + Y = 6 and X + 3Y = 9
        // From second equation: X = 9 - 3Y
        // Substitute: 2(9 - 3Y) + Y = 6 → 18 - 6Y + Y = 6 → Y = 2.4, X = 1.8
        corners.push_back({1.8, 2.4});
        
        // Also check boundary intersections with axes
        corners.push_back({0, 6});
        corners.push_back({9, 0});
        
        // Evaluate objective function at each corner point
        cout << "Evaluating corner points:" << endl;
        for (auto corner : corners) {
            double x = corner.first, y = corner.second;
            if (isFeasible(x, y)) {
                double cost = getCost(x, y);
                cout << "(" << x << ", " << y << ") - Cost: $" << cost;
                if (cost < bestCost) {
                    bestCost = cost;
                    bestSolution = corner;
                    cout << " <- New minimum!";
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
    
    // Step 1: Test some sample points for feasibility
    cout << "\n--- Testing Sample Points ---" << endl;
    
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
            cout << "Infeasible (violates constraints)" << endl;
        }
    }
    
    // Step 2: Solve the LP problem using corner point method
    cout << "\n--- Solving LP Problem ---" << endl;
    
    clock_t start = clock();
    pair<double, double> solution = problem.solveByCornerPoints();
    clock_t end = clock();
    
    double x = solution.first, y = solution.second;
    double totalCost = problem.getCost(x, y);
    
    cout << "\n=== OPTIMAL SOLUTION ===" << endl;
    cout << "Cups of drink X: " << x << endl;
    cout << "Cups of drink Y: " << y << endl;
    cout << "Minimum cost: $" << totalCost << endl;
    
    // Step 3: Verify solution satisfies all constraints
    cout << "\nConstraint verification:" << endl;
    double calories = 60*x + 60*y;
    double vitA = 12*x + 6*y;  
    double vitC = 10*x + 30*y;
    
    cout << "Calories: " << calories << " >= 300? " << (calories >= 300 ? "YES" : "NO") << endl;
    cout << "Vitamin A: " << vitA << " >= 36? " << (vitA >= 36 ? "YES" : "NO") << endl;
    cout << "Vitamin C: " << vitC << " >= 90? " << (vitC >= 90 ? "YES" : "NO") << endl;
    
    cout << "\nAll constraints satisfied: " << (calories >= 300 && vitA >= 36 && vitC >= 90 ? "YES" : "NO") << endl;
    
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    cout << "\nRunning time: " << time << " milliseconds" << endl;
    
    return 0;
}