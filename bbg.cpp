#include <iostream>
#include <sstream>
#include <iomanip>
#include <variant>
#include <cmath>  // Add this for std::round

void processLine(const std::string &line, int &t1, int &t2, std::variant<int, double, char, std::string> &t3, int dt) {
    std::istringstream ss(line);
    int first;
    ss >> first;  // Read operation code

    t1 = -1;
    t2 = -1;
    t3 = std::string("");  // Default to an empty string

    if (first == 1 || first == 2) {  // Insert or Remove operations
        t1 = first;
        ss >> t2;  // Read set number (1 or 2)

        if (dt == 1) {  // Integer
            int value;
            if (ss >> value) {
                t3 = value;
            }
        } else if (dt == 2) {  // Double
            double value;
            if (ss >> value) {
                value = std::round(value * 100) / 100;  // Round to 2 decimal places
                t3 = value;
            }
        } else if (dt == 3) {  // Char
            char value;
            if (ss >> value) {
                t3 = value;
            }
        } else if (dt == 4 || dt == 5) {  // String
            std::string value;
            ss >> value;
            t3 = value;
        }
    } else if (first >= 3 && first <= 6) {  // Other operations (Subset, Union, Intersection, Difference)
        t1 = first;
    } else {  // If operation doesn't match expected cases
        t1 = first;
        ss >> t2;
    }
}

int main() {
    std::string testCases[] = {
        "1 1 42",      // Insert integer
        "2 2 3.14159", // Remove double
        "1 1 a",      // Insert char
        "2 2 hello",  // Remove string
        "3",          // Subset operation
        "4",          // Union operation
        "5",          // Intersection operation
        "6",          // Difference operation
        "7 9"         // Unknown operation
    };
    
    int t1, t2;
    std::variant<int, double, char, std::string> t3;
    
    int dataTypes[] = {1, 2, 3, 4, 5}; // Integer, Double, Char, String (dt values)
    
    for (const auto &line : testCases) {
        for (int dt : dataTypes) {
            processLine(line, t1, t2, t3, dt);
            std::cout << "Processed: " << line << " (dt = " << dt << ")\n";
            std::cout << "t1: " << t1 << ", t2: " << t2 << ", t3: ";
            
            if (std::holds_alternative<int>(t3)) {
                std::cout << std::get<int>(t3);
            } else if (std::holds_alternative<double>(t3)) {
                std::cout << std::fixed << std::setprecision(2) << std::get<double>(t3);
            } else if (std::holds_alternative<char>(t3)) {
                std::cout << std::get<char>(t3);
            } else if (std::holds_alternative<std::string>(t3)) {
                std::cout << std::get<std::string>(t3);
            }
            std::cout << "\n\n";
        }
    }
    
    return 0;
}
