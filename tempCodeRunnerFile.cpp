void processNumber(const std::string &line, int &t1, int &t2, double &t3) {
    std::istringstream ss(line);
    int first;
    ss >> first;

    t1 = -1; // Default values indicating no operation recorded
    t2 = -1;
    t3 = 0.0; // Default value for t3

    if (first == 1 || first == 2) {  // Insert or Remove
        t1 = first;
        ss >> t2; // Read the target set (1 or 2)
        if (ss >> t3) {
            // Round to two decimal places
            t3 = std::round(t3 * 100) / 100;
        }
    } else if (first >= 3 && first <= 6) { // Other operations
        t1 = first;
    } else {
        t1 = first;
        ss >> t2;
    }
}