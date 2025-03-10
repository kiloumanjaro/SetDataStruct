/* I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs. */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <variant>
#include <fstream> 

template <typename T>
class Set {
private:
    std::vector<T> elements;

public:
    // Inserts a value into the set if it does not already exist
    void insert(const T& value) {
        if (!contains(value)) {
            elements.push_back(value);
        }
    }

    // Removes a value from the set if it exists
    // Uses std::remove to shift elements before erasing them
    void remove(const T& value) {
        elements.erase(std::remove(elements.begin(), elements.end(), value), elements.end());
    }

    bool contains(const T& value) const {
        return std::find(elements.begin(), elements.end(), value) != elements.end();
    }

    size_t size() const {
        return elements.size();
    }

    // Prints the set elements in a formatted way
    void print() const {
        if (elements.empty()) {
            std::cout << "empty\n";
            return;
        }
        std::cout << "{";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i];
            if (i < elements.size() - 1) {
                std::cout << ","; // Print comma only between elements
            }
        }
        std::cout << "}\n";
    }
    
    void powerPrint() const {
        if (elements.empty()) {
            std::cout << "";
            return;
        }
        std::cout << "{";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i];
            if (i < elements.size() - 1) {
                std::cout << ","; // Print comma only between elements
            }
        }
        std::cout << "}";
    }

    bool isSubset(const Set<T>& other) const {
        for (const auto& elem : elements) {
            if (!other.contains(elem)) {
                return false;
            }
        }
        return true;
    }

    // Merges two sets; does not allow duplicate elements
    Set<T> setUnion(const Set<T>& other) const {
        Set<T> result = *this;
        for (const auto& elem : other.elements) {
            result.insert(elem);
        }
        return result;
    }

    Set<T> intersection(const Set<T>& other) const {
        Set<T> result;
        for (const auto& elem : elements) {
            if (other.contains(elem)) {
                result.insert(elem);
            }
        }
        return result;
    }

    Set<T> difference(const Set<T>& other) const {
        Set<T> result;
        for (const auto& elem : elements) {
            if (!other.contains(elem)) {
                result.insert(elem);
            }
        }
        return result;
    }

    // Generates all subsets of the set, including the empty set and the full set
    std::vector<Set<T>> powerSet() const {
        std::vector<Set<T>> result;
        size_t n = elements.size();
        std::vector<bool> contain(n, false);
        
        // Insert the empty set
        result.push_back(Set<T>());
        
        // Generate subsets of size 1 to n using previous permutation
        for (size_t i = 1; i <= n; ++i) {
            std::fill(contain.begin(), contain.end(), false);
            for (size_t j = 0; j < i; ++j) {
                contain[j] = true;
            }
            
            do {
                Set<T> subset;
                for (size_t j = 0; j < n; ++j) {
                    if (contain[j]) {
                        subset.insert(elements[j]);
                    }
                }
                result.push_back(subset);
            } while (std::prev_permutation(contain.begin(), contain.end()));
        }
        return result;
    }


    void insertFromInput(std::ifstream& inputFile) {
        std::string input;
        std::getline(inputFile, input);
        std::istringstream ss(input);
        T value;  // Use T instead of int
        while (ss >> value) {
            this->insert(value);
        }
    }
};

// Tokenizes input string into words
void tokenize(const std::string &line, std::vector<std::string> &tokens) {
    std::istringstream ss(line);
    std::string token;
    while (ss >> token) {  // Extracts words separated by spaces
        tokens.push_back(token);
    }
}


// Processes input tokens
void processTokens(const std::vector<std::string> &tokens, int &t1, int &t2, std::variant<int, double, char, std::string> &t3, int dt) {
    if (tokens.empty()) return;

    t1 = std::stoi(tokens[0]);  // Convert first token to an int

    if (t1 == 1 || t1 == 2 || t1 == 7) {  // Include t1 == 7 case
        if (tokens.size() > 1) t2 = std::stoi(tokens[1]);  // Read set number for t1 == 1, 2, or 7
        if ((t1 == 1 || t1 == 2) && tokens.size() > 2) {  // Read value for Insert/Remove operations
            if (dt == 1) t3 = std::stoi(tokens[2]);
            else if (dt == 2) t3 = std::stod(tokens[2]);
            else if (dt == 3) t3 = tokens[2][0];  // First char
            else t3 = tokens[2];  // Assume string
        }
    }
}


int main() {
    std::ifstream inputFile("mpa1.in");
    int t1, t2, dt, n, tc;
    std::string input;
    std::variant<int, double, char, std::string> value;
    std::stringstream ss;
    inputFile >> tc;

    for (int j=0; j < tc; j++) {
        inputFile >> dt;
        if (dt == 5) {
            inputFile >> dt;
            dt = 5;
        }
        inputFile.ignore(); 
  
        Set<int> intSet1, intSet2;
        Set<double> doubleSet1, doubleSet2;
        Set<char> charSet1, charSet2;
        Set<std::string> stringSet1, stringSet2;
        
        if (dt == 1) {
            intSet1.insertFromInput(inputFile);
            intSet2.insertFromInput(inputFile);
        } else if (dt == 2) {
            doubleSet1.insertFromInput(inputFile);
            doubleSet2.insertFromInput(inputFile);
        } else if (dt == 3) {
            charSet1.insertFromInput(inputFile);
            charSet2.insertFromInput(inputFile);
        } else if (dt == 4 || dt == 5) {
            stringSet1.insertFromInput(inputFile);
            stringSet2.insertFromInput(inputFile);
        }  else {
            return 1; // Data type invalid
        }
    
        inputFile >> n;
        inputFile.ignore();

        for (int i = 0; i < n; i++) {

            if (!std::getline(inputFile, input) || input.empty()) {
                return 0; // Stop if input is empty
            }
            std::vector<std::string> tokens;
            tokenize(input, tokens);

            processTokens(tokens, t1, t2, value, dt);

                        switch (t1) {
                case 1:
                    if (dt==1) {
                        int valueInt;
                        if (std::holds_alternative<int>(value)) {
                            valueInt = std::get<int>(value);
                        } else {
                            std::cerr << "Error: value is not an int\n";
                        }
                        if (t2 == 1) {
                            intSet1.insert(valueInt);
                            intSet1.print();
                        } else {
                            intSet2.insert(valueInt);
                            intSet2.print();
                        }
                    }
                    if (dt==2) {
                        double valueDouble;
                        if (std::holds_alternative<double>(value)) {
                            valueDouble = std::get<double>(value);
                        } else {
                            std::cerr << "Error: value is not a double\n";
                        }
                        if (t2 == 1) {
                            doubleSet1.insert(valueDouble);
                            doubleSet1.print();
                        } else {
                            doubleSet2.insert(valueDouble);
                            doubleSet2.print();
                        }
                    }
                    if (dt==3) {
                        char valueChar;
                        if (std::holds_alternative<char>(value)) {
                            valueChar = std::get<char>(value);
                        } else {
                            std::cerr << "Error: value is not an int\n";
                        }
                        if (t2 == 1) {
                            charSet1.insert(valueChar);
                            charSet1.print();
                        } else {
                            charSet2.insert(valueChar);
                            charSet2.print();
                        }
                    }
                    if (dt==4 || dt==5) {
                        std::string valueString;
                        if (std::holds_alternative<std::string>(value)) {
                            valueString = std::get<std::string>(value);
                        } else {
                            std::cerr << "Error: value is not an int\n";
                        }
                        if (t2 == 1) {
                            stringSet1.insert(valueString);
                            stringSet1.print();
                        } else {
                            stringSet2.insert(valueString);
                            stringSet2.print();
                        }
                    }
                    break;
            
                case 2:
                    if (dt==1) {
                        int valueInt;
                        if (std::holds_alternative<int>(value)) {
                            valueInt = std::get<int>(value);
                        } else {
                            std::cerr << "Error: value is not an int\n";
                        }
                        if (t2 == 1) {
                            intSet1.remove(valueInt);
                            intSet1.print();
                        } else {
                            intSet2.remove(valueInt);
                            intSet2.print();
                        }
                    }
                    if (dt==2) {
                        double valueDouble;
                        if (std::holds_alternative<double>(value)) {
                            valueDouble = std::get<double>(value);
                        } else {
                            std::cerr << "Error: value is not a double\n";
                        }
                        if (t2 == 1) {
                            doubleSet1.remove(valueDouble);
                            doubleSet1.print();
                        } else {
                            doubleSet2.remove(valueDouble);
                            doubleSet2.print();
                        }
                    }
                    if (dt==3) {
                        char valueChar;
                        if (std::holds_alternative<char>(value)) {
                            valueChar = std::get<char>(value);
                        } else {
                            std::cerr << "Error: value is not an int\n";
                        }
                        if (t2 == 1) {
                            charSet1.remove(valueChar);
                            charSet1.print();
                        } else {
                            charSet2.remove(valueChar);
                            charSet2.print();
                        }
                    }
                    if (dt==4 || dt==5) {
                        std::string valueString;
                        if (std::holds_alternative<std::string>(value)) {
                            valueString = std::get<std::string>(value);
                        } else {
                            std::cerr << "Error: value is not an string\n";
                        }
                        if (t2 == 1) {
                            stringSet1.remove(valueString);
                            stringSet1.print();
                        } else {
                            stringSet2.remove(valueString);
                            stringSet2.print();
                        }
                    }
                    break;
        
                case 3:
                    if (dt==1) {
                        std::cout << (intSet1.isSubset(intSet2) ? "true\n" : "false\n");
                    }
                    if (dt==2) {
                        std::cout << (doubleSet1.isSubset(doubleSet2) ? "true\n" : "false\n");
                    }
                    if (dt==3) {
                        std::cout << (charSet1.isSubset(charSet2) ? "true\n" : "false\n");
                    }
                    if (dt==4 || dt==5) {
                        std::cout << (stringSet1.isSubset(stringSet2) ? "true\n" : "false\n");
                    }
                    break;
        
                case 4:
                    if (dt==1) {
                        intSet1.setUnion(intSet2).print();
                    }
                    if (dt==2) {
                        doubleSet1.setUnion(doubleSet2).print();
                    }
                    if (dt==3) {
                        charSet1.setUnion(charSet2).print();
                    }
                    if (dt==4 || dt==5) {
                        stringSet1.setUnion(stringSet2).print();
                    }
                    break;
        
                case 5:
                    if (dt==1) {
                        intSet1.intersection(intSet2).print();
                    }
                    if (dt==2) {
                        doubleSet1.intersection(doubleSet2).print();
                    }
                    if (dt==3) {
                        charSet1.intersection(charSet2).print();
                    }
                    if (dt==4 || dt==5) {
                        stringSet1.intersection(stringSet2).print();
                    }
                    break;
        
                case 6:
                    if (dt==1) {
                        intSet1.difference(intSet2).print();
                    }
                    if (dt==2) {
                        doubleSet1.difference(doubleSet2).print();
                    }
                    if (dt==3) {
                        charSet1.difference(charSet2).print();
                    }
                    if (dt==4 || dt==5) {
                        stringSet1.difference(stringSet2).print();
                    }
                    break;
        
                case 7: {
                    if (dt==1) {
                        std::vector<Set<int>> powerSet;
                        std::cout << "{empty";
                        
                        powerSet = (t2 == 1) ? intSet1.powerSet() : intSet2.powerSet();
                        
                        for (auto it = powerSet.begin(); it != powerSet.end(); ++it) {
                            std::ostringstream buffer; // Temporary stream to capture output
                            std::streambuf* oldCoutBuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout
                        
                            it->powerPrint(); // Capture powerPrint() output
                        
                            std::cout.rdbuf(oldCoutBuf); // Restore cout
                        
                            std::string output = buffer.str();
                            if (!output.empty()) { // Only print if powerPrint() actually outputs something
                                std::cout << "," << output;
                            }
                        }
                        
                        std::cout << "}\n";
                    }
                    if (dt==2) {
                        std::vector<Set<double>> powerSet;
                        std::cout << "{empty";
                        
                        powerSet = (t2 == 1) ? doubleSet1.powerSet() : doubleSet2.powerSet();
                        
                        for (auto it = powerSet.begin(); it != powerSet.end(); ++it) {
                            std::ostringstream buffer; // Temporary stream to capture output
                            std::streambuf* oldCoutBuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout
                        
                            it->powerPrint(); // Capture powerPrint() output
                        
                            std::cout.rdbuf(oldCoutBuf); // Restore cout
                        
                            std::string output = buffer.str();
                            if (!output.empty()) { // Only print if powerPrint() actually outputs something
                                std::cout << "," << output;
                            }
                        }
                        
                        std::cout << "}\n";                        
                    }
                    if (dt==3) {
                        std::vector<Set<char>> powerSet;
                        std::cout << "{empty";
                        
                        powerSet = (t2 == 1) ? charSet1.powerSet() : charSet2.powerSet();
                        
                        for (auto it = powerSet.begin(); it != powerSet.end(); ++it) {
                            std::ostringstream buffer; // Temporary stream to capture output
                            std::streambuf* oldCoutBuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout
                        
                            it->powerPrint(); // Capture powerPrint() output
                        
                            std::cout.rdbuf(oldCoutBuf); // Restore cout
                        
                            std::string output = buffer.str();
                            if (!output.empty()) { // Only print if powerPrint() actually outputs something
                                std::cout << "," << output;
                            }
                        }
                        
                        std::cout << "}\n";                                               
                    }
                    if (dt==4 || dt==5) {
                        std::vector<Set<std::string>> powerSet;
                        std::cout << "{empty";
                        
                        powerSet = (t2 == 1) ? stringSet1.powerSet() : stringSet2.powerSet();
                        
                        for (auto it = powerSet.begin(); it != powerSet.end(); ++it) {
                            std::ostringstream buffer; // Temporary stream to capture output
                            std::streambuf* oldCoutBuf = std::cout.rdbuf(buffer.rdbuf()); // Redirect cout
                        
                            it->powerPrint(); // Capture powerPrint() output
                        
                            std::cout.rdbuf(oldCoutBuf); // Restore cout
                        
                            std::string output = buffer.str();
                            if (!output.empty()) { // Only print if powerPrint() actually outputs something
                                std::cout << "," << output;
                            }
                        }
                        
                        std::cout << "}\n";                                            
                    }
                    break;
                }
        
                default:
                    std::cout << "Invalid choice. Try again.\n";
                    break;
            }
        }
    }
    inputFile.close();  // Close the file when done
    return 0;
}    