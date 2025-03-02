#include <iostream>
#include <set>

template <typename T>
class Set {
private:
    std::set<T> elements;  // Internal storage using std::set

public:
    // Insert an element into the set
    void insert(const T& value) {
        elements.insert(value);
    }

    // Remove an element from the set
    void remove(const T& value) {
        elements.erase(value);
    }

    // Check if an element exists
    bool getter(const T& value) const {
        return elements.find(value) != elements.end();
    }

    // Get the size of the set
    size_t size() const {
        return elements.size();
    }

    // Print elements
    void print() const {
        std::cout << "{ ";
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << "}\n";
    }
};



int main() {    
    Set<int> s;
    int n;
    int type;
    std:: cin >> n;
    std::cin.ignore();
    std:: cin >> type   ;
    std::cin.ignore();




    for (int i = 0; i < n; ++i) {


    }


    s.insert(5);
    s.insert(10);
    s.insert(5);
    s.print();  // Output: { 5 10 }

    Set<std::string> s1;
    s1.insert("hello");
    s1.insert("world");
    s1.print();  // Output: { hello world }

    Set<Set<int>> s2;
    Set<int> subset1;
    subset1.insert(1);
    subset1.insert(2);

    Set<int> subset2;
    subset2.insert(3);
    subset2.insert(4);

    s2.insert(subset1);
    s2.insert(subset2);

    std::cout << s2 << std::endl;  // Output: { { 1 2 } { 3 4 } }

    return 0;
}
