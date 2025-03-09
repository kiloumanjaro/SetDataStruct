#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <variant>

template <typename T>
class Set {
private:
    std::vector<T> elements;

public:
    void insert(const T& value) {
        if (!contains(value)) {
            elements.push_back(value);
        }
    }

    void remove(const T& value) {
        elements.erase(std::remove(elements.begin(), elements.end(), value), elements.end());
    }

    bool contains(const T& value) const {
        return std::find(elements.begin(), elements.end(), value) != elements.end();
    }

    size_t size() const {
        return elements.size();
    }

    void print() const {
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
        std::cout << "{";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i];
            if (i < elements.size() - 1) {
                std::cout << ","; // Print comma only between elements
            }
        }
        std::cout << "}";
    }

    void printPowerSet() const {
        if (elements.empty()) {
            std::cout << "empty"; // Explicitly label the empty set
        } else {
            for (size_t i = 0; i < elements.size(); ++i) {
                for (size_t j = 0; j < elements[i].size(); ++j) {
                    std::cout << elements[i][j];
                    if (j < elements[i].size() - 1) {
                        std::cout << ",";
                    }
                }
                if (i < elements.size() - 1) {
                    std::cout << " ,";
                }
            }
        }
        std::cout << "\n";
    }    

    bool isSubset(const Set<T>& other) const {
        for (const auto& elem : elements) {
            if (!other.contains(elem)) {
                return false;
            }
        }
        return true;
    }

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

    std::vector<Set<T>> powerSet() const {
        std::vector<Set<T>> result;
        size_t powerSize = std::pow(2, elements.size());
        for (size_t i = 0; i < powerSize; ++i) {
            Set<T> subset;
            for (size_t j = 0; j < elements.size(); ++j) {
                if (i & (1 << j)) {
                    subset.insert(elements[j]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }

    void insertFromInput() {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream stream(line);
        T value;
        while (stream >> value) {
            insert(value);
        }
    }
};

void tokenize(const std::string &line, std::vector<std::string> &tokens) {
    std::istringstream ss(line);
    std::string token;
    while (ss >> token) {  // Extracts words separated by spaces
        tokens.push_back(token);
    }
}

void processTokens(const std::vector<std::string> &tokens, int &t1, int &t2, std::variant<int, double, char, std::string> &t3, int dt) {
    if (tokens.empty()) return;

    t1 = std::stoi(tokens[0]);  // Convert first token to an int

    if (t1 == 1 || t1 == 2) {  // Insert or Remove operations
        if (tokens.size() > 1) t2 = std::stoi(tokens[1]);  // Read set number
        if (tokens.size() > 2) {  // Read value
            if (dt == 1) t3 = std::stoi(tokens[2]);
            else if (dt == 2) t3 = std::stod(tokens[2]);
            else if (dt == 3) t3 = tokens[2][0];  // First char
            else t3 = tokens[2];  // Assume string
        }
    }
}

int main() {
    Set<std::string> set1, set2;
    int t1, t2, dt , n, tc;
    std::string input;
    std::variant<int, double, char, std::string> value;
    std::stringstream ss;
    std::cin >> tc;

    for (int j=0; j < tc; j++) {
        Set<std::string> set1, set2; // Clearing sets by creating new instances
        std::cin >> dt;
        if (dt==5){ 
            std::cin >> dt;
        }
        std::cin.ignore(); 

        set1.insertFromInput();
        set1.print();
        
        set2.insertFromInput();
        set2.print();

        std::cin >> n;
        std::cin.ignore(); // Clears the newline character after number input
        std::vector<Set<std::string>> powerSet;
        std::vector<Set<std::string>>::iterator it;

        for (int i = 0; i < n; i++) {

            if (!std::getline(std::cin, input) || input.empty()) {
                return 0;  // Stop if input is empty
            }
            std::vector<std::string> tokens;
            tokenize(input, tokens);

            std::cout << "Tokens: ";
            for (const auto &token : tokens) {
                std::cout << "\"" << token << "\" ";
            }
            std::cout << std::endl;

            processTokens(tokens, t1, t2, value, dt);
            std::visit([](const auto& val) { std::cout << val; }, value);
            std::visit([](const auto &val) { 
                std::cout << "\n(" << typeid(val).name() << ") " << std::endl; 
            }, value);

            // switch (t1) {
            //     case 1:
            //         if (t2 == 1) {
            //             set1.insert(value);
            //             set1.print();
            //         } else {
            //             set2.insert(value);
            //             set2.print();
            //         }
            //         break;
        
            //     case 2:
            //         if (t2 == 1) {
            //             set1.remove(value);
            //             set1.print();
            //         } else {
            //             set2.remove(value);
            //             set2.print();
            //         }
            //         break;
        
            //     case 3:
            //         std::cout << (set1.isSubset(set2) ? "true\n" : "false\n");
            //         break;
        
            //     case 4:
            //         set1.setUnion(set2).print();
            //         break;
        
            //     case 5:
            //         set1.intersection(set2).print();
            //         break;
        
            //     case 6:
            //         set1.difference(set2).print();
            //         break;
        
            //     case 7: {

            //         std::cout << "{empty,";
        
            //         powerSet = (t2 == 1) ? set1.powerSet() : set2.powerSet();
            //         auto it = powerSet.begin();
            //         if (it != powerSet.end()) ++it;
        
            //         for (auto last = powerSet.end(); it != last;) {
            //             it->powerPrint();
            //             ++it;
            //             if (it != last) {
            //                 std::cout << ",";
            //             }
            //         }
        
            //         std::cout << "}\n";
            //         break;
            //     }
        
            //     default:
            //         std::cout << "Invalid choice. Try again.\n";
            //         break;
            // }
        }
    }
}    