#include <iostream>
#include <sstream>

void processLine(const std::string &line, int &t1, int &t2, int &t3) {
    std::istringstream ss(line);
    int first;
    ss >> first;
    
    t1 = t2 = t3 = -1; // Default values indicating no value recorded
    
    if (first == 1 || first == 2) {
        t1 = first;
        ss >> t2 >> t3; // Read two more if available
    } else if (first >= 3 && first <= 6) {
        t1 = first;
    } else if (first == 7) {
        t1 = first;
        ss >> t2; // Read one more if available
    }
}

int main() {
    std::string input;
    while (std::getline(std::cin, input)) {
        int t1, t2, t3;
        processLine(input, t1, t2, t3);
        
        std::cout << "t1: " << t1;
        if (t2 != -1) std::cout << ", t2: " << t2;
        if (t3 != -1) std::cout << ", t3: " << t3;
        std::cout << std::endl;
    }
    return 0;
}
