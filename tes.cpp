#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

template <typename T>
class Set {
private:
    std::vector<T> elements;

public:
    void insert(const T& value) {
        if (!getter(value)) {
            elements.push_back(value);
        }
    }

    void remove(const T& value) {
        elements.erase(std::remove(elements.begin(), elements.end(), value), elements.end());
    }

    bool getter(const T& value) const {
        return std::find(elements.begin(), elements.end(), value) != elements.end();
    }

    size_t size() const {
        return elements.size();
    }

    void print() const {
        std::cout << "{ ";
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << "}\n";
    }

    bool isSubset(const Set<T>& other) const {
        for (const auto& elem : elements) {
            if (!other.getter(elem)) {
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
            if (other.getter(elem)) {
                result.insert(elem);
            }
        }
        return result;
    }

    Set<T> difference(const Set<T>& other) const {
        Set<T> result;
        for (const auto& elem : elements) {
            if (!other.getter(elem)) {
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
};

int main() {
    Set<int> set1, set2;
    int choice, value;

    do {
        std::cout << "\n1. Insert\n2. Remove\n3. Check Subset\n4. Union\n5. Intersection\n6. Difference\n7. Power Set\n0. Exit\nEnter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to insert in Set 1: ";
                std::cin >> value;
                set1.insert(value);
                set1.print();
                break;

            case 2:
                std::cout << "Enter value to remove from Set 1: ";
                std::cin >> value;
                set1.remove(value);
                set1.print();
                break;

            case 3:
                std::cout << "Enter elements for Set 2 (terminate with -1): ";
                while (std::cin >> value && value != -1) set2.insert(value);
                std::cout << (set1.isSubset(set2) ? "Set 1 is a subset of Set 2\n" : "Set 1 is NOT a subset of Set 2\n");
                break;

            case 4:
                std::cout << "Enter elements for Set 2 (terminate with -1): ";
                set2 = Set<int>();
                while (std::cin >> value && value != -1) set2.insert(value);
                set1.setUnion(set2).print();
                break;

            case 5:
                std::cout << "Enter elements for Set 2 (terminate with -1): ";
                set2 = Set<int>();
                while (std::cin >> value && value != -1) set2.insert(value);
                set1.intersection(set2).print();
                break;

            case 6:
                std::cout << "Enter elements for Set 2 (terminate with -1): ";
                set2 = Set<int>();
                while (std::cin >> value && value != -1) set2.insert(value);
                set1.difference(set2).print();
                break;

            case 7:
                std::cout << "Power Set:\n";
                for (const auto& subset : set1.powerSet()) {
                    subset.print();
                }
                break;

            case 0:
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);
    
    return 0;
}
