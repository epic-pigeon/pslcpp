#include <iostream>
#include <vector>
#include "Parser/collection.cpp"

int main() {
    collection<int> arr;
    arr.add(1);
    arr.add(2);
    for (auto i = arr.begin(); i < arr.end(); ++i) {
        std::cout << *i;
    }
}