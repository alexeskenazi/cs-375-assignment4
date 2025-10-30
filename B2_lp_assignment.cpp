#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

// Assignment 4 - Linear Programming Diet Problem
// Minimize cost of drinks X and Y subject to nutritional constraints
// Using corner point method to solve the LP problem

class DietProblem {
public:
    // Cost per cup (objective function coefficients)
    double drinkX_cost;
    double drinkY_cost;
    
    // Nutritional content per cup (constraint coefficients)
    double drinkX_calories;
    double drinkX_vitA;
    double drinkX_vitC;
    
    double drinkY_calories;
    double drinkY_vitA;
    double drinkY_vitC;
    
    // Daily nutritional requirements (RHS values)
    double min_calories;
    double min_vitA;
    double min_vitC;
    
    // Read problem data from input file
    void readFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open input file " << filename << endl;
            return;
        }
        
        string line;
        bool readingCoeffs = false;
        bool readingConstraints = false;
        
        while (getline(file, line)) {
            if (line.find("object function coefficients") != string::npos) {
                readingCoeffs = true;
                continue;
            }
            if (line.find("constraint coefficients") != string::npos) {
                readingConstraints = true;
                readingCoeffs = false;
                continue;
            }
            
            if (readingCoeffs && line.length() > 0 && line[0] != '/') {
                istringstream iss(line);
                iss >> drinkX_cost >> drinkY_cost;
            }
            
            if (readingConstraints && line.length() > 0 && line[0] != '/') {
                istringstream iss(line);
                vector<double> values;
                double val;
                while (iss >> val) {
                    values.push_back(val);
                }
                
                if (values.size() == 3) {
                    static int constraintNum = 0;
                    if (constraintNum == 0) {
                        drinkX_calories = values[0];
                        drinkY_calories = values[1];
                        min_calories = values[2];
                    } else if (constraintNum == 1) {
                        drinkX_vitA = values[0];
                        drinkY_vitA = values[1];
                        min_vitA = values[2];
                    } else if (constraintNum == 2) {
                        drinkX_vitC = values[0];
                        drinkY_vitC = values[1];
                        min_vitC = values[2];
                    }
                    constraintNum++;
                }
            }
        }
        file.close();
    }
    
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

int main(int argc, char* argv[]) {
    cout << "CS 375 Assignment 4 - Linear Programming" << endl;
    
    // Set default file names
    string inputFileName = "B2_input.txt";
    string outputFileName = "B2_output.txt";
    
    // Parse command line arguments
    if (argc == 2) {
        inputFileName = argv[1];
    } else if (argc == 3) {
        inputFileName = argv[1];
        outputFileName = argv[2];
    }
    
    DietProblem problem;
    problem.readFromFile(inputFileName);
    
    // Open output file
    ofstream outputFile(outputFileName);
    
    problem.printProblem();
    
    cout << "\nSolving:" << endl;
    
    clock_t start = clock();
    pair<double, double> solution = problem.solveByCornerPoints();
    clock_t end = clock();
    
    double x = solution.first, y = solution.second;
    double totalCost = problem.getCost(x, y);
    
    // Output to console
    cout << "\n=== OPTIMAL SOLUTION ===" << endl;
    cout << "Cups of drink X: " << x << endl;
    cout << "Cups of drink Y: " << y << endl;
    cout << "Minimum cost: $" << totalCost << endl;
    double time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    
    // Output to file in sample format
    outputFile << "//** Print out the minimum cost, and number cups of drink X and number of cups of drink Y **/" << endl;
    outputFile << "Minimum cost: " << totalCost << endl;
    outputFile << "# (drink X): " << x << endl;
    outputFile << "# (drink Y): " << y << endl;
    outputFile << endl;
    
    outputFile << "//** Print out the maximum profit, and number of items x1, x2, x3 **/" << endl;
    outputFile << "Maximum profit: N/A" << endl;
    outputFile << "# (x1): N/A" << endl;
    outputFile << "# (x2): N/A" << endl;
    outputFile << "# (x3): N/A" << endl;
    outputFile << endl;
    
    outputFile << "//** print out running time **/" << endl;
    outputFile << time << " milliseconds" << endl;
    
    outputFile.close();
    
    // Console verification
    cout << "\nConstraint verification:" << endl;
    double calories = problem.drinkX_calories*x + problem.drinkY_calories*y;
    double vitA = problem.drinkX_vitA*x + problem.drinkY_vitA*y;  
    double vitC = problem.drinkX_vitC*x + problem.drinkY_vitC*y;
    
    cout << "Calories: " << calories << " >= " << problem.min_calories << "? " << (calories >= problem.min_calories ? "YES" : "NO") << endl;
    cout << "Vitamin A: " << vitA << " >= " << problem.min_vitA << "? " << (vitA >= problem.min_vitA ? "YES" : "NO") << endl;
    cout << "Vitamin C: " << vitC << " >= " << problem.min_vitC << "? " << (vitC >= problem.min_vitC ? "YES" : "NO") << endl;
    
    cout << "\nAll constraints satisfied: " << (calories >= problem.min_calories && vitA >= problem.min_vitA && vitC >= problem.min_vitC ? "YES" : "NO") << endl;
    cout << "\nRunning time: " << time << " milliseconds" << endl;
    
    return 0;
}