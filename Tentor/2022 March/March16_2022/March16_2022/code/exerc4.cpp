// =======================================================
// Exerc4
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, LiU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iterator>  //istream_iterator
#include <vector>
#include <algorithm>  //copy, copy_if, sort
#include <fstream>
#include <set>

class Select_smaller_than {  // used in STEP 5
public:
    Select_smaller_than(int i) : val{i} {
    }

    bool operator()(int k) {
        return k < val;
    }

private:
    int val;
};

int main() {
    std::cout << "STEP 1 :\n";

    std::ifstream file("../code/numbers.txt");

    if (!file) {
        std::cout << "Input file cannot be opened!!\n";
        return 0;
    }

    std::istream_iterator<int> start(file), end_;
    std::vector<int> V(start, end_);
    file.close();

    std::cout << "Number of values: " << V.size() << "\n";
    std::copy(std::begin(V), std::end(V), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    /* *************************** */
    std::cout << "STEP 2\n";

    std::sort(std::begin(V), std::end(V));
    //std::copy(std::begin(V), std::end(V), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // std::nth_element could also be used

    if (V.size() % 2) {
        std::cout << "Median = " << V[V.size() / 2 - 1] << "\n\n";
    } else {
        std::cout << "Median = " << (V[V.size() / 2 - 1] + V[V.size() / 2]) / 2.0 << "\n\n";
    }

    /* *************************** */
    std::cout << "STEP 3:\n";

    std::set<int> even{};
    std::set<int> odd{};

    std::copy_if(V.begin(), V.end(), std::inserter(even, even.end()),
                 [](int i) { return (i % 2 == 0); });

    std::copy_if(V.begin(), V.end(), std::inserter(odd, odd.end()),
                 [](int i) { return (i % 2 == 1); });

    std::cout << "\n\n";

    /* *************************** */
    std::cout << "STEP 4:\n";

    std::cout << "Odd values: ";
    std::copy(std::rbegin(odd), std::rend(odd), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\n";

    std::cout << "Even values: ";
    std::copy(std::begin(even), std::end(even), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\n\n";

    /* *************************** */
    std::cout << "STEP 5\n";

    std::vector<int> V1;

    if (odd.size() > 0) {
        std::copy_if(std::begin(even), std::end(even), std::back_inserter(V1),
                     Select_smaller_than(*std::begin(odd)));
        std::copy(std::begin(V1), std::end(V1), std::ostream_iterator<int>(std::cout, " "));
    }
    std::cout << "\n\n";
}
