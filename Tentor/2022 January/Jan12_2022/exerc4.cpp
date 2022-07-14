// =======================================================
// Exerc4
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, LiU-id, and personal number. Otherwise, your exam is not graded.


#include <iostream>
#include <algorithm>  //std::for_each
#include <fstream>
#include <map>
#include <iomanip>
#include <utility>  //std::pair
#include <string>
#include <set>
#include <vector>
// See also set 5 of course exercises/exercise 5

using Table = std::map<int, std::set<std::string>>;
using My_pair = std::pair<int, std::set<std::string>>;
// Note: rename types to make the code more readable

struct insert_table {
    // Constructor
    explicit insert_table(Table& T) : T_{T} {
    }

    void operator()(const std::string& w) {
        T_[std::stoi(w)].insert(w);
    }

private:
    Table& T_;
};

struct display_ints {
    // Constructor
    explicit display_ints(std::ostream& os = std::cout) : os_{os} {
    }

    void operator()(const My_pair& a) {
        os_ << std::setw(6) << a.first << ": ";
        // Write the set of all forms of integer a.first to stream os_
        std::copy(std::begin(a.second), std::end(a.second),
                  std::ostream_iterator<std::string>(os_, " "));

        os_ << '\n';
    }

private:
    std::ostream& os_;
};

int main() {
    auto in_file = std::ifstream{"../code/integers.txt"};

    if (!in_file) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    auto inIt = std::istream_iterator<std::string>{in_file};
    auto inItEnd = std::istream_iterator<std::string>{};

    auto ints_table = Table{};

    // Step 1: Read the file and build the table -- 2p
    std::for_each(inIt, inItEnd, insert_table{ints_table});

    // Step 2: Write the table to std::cout     -- 2p
    std::cout << "** Table sorted by integer value **\n";
    std::for_each(ints_table.begin(), ints_table.end(), display_ints{});

    // Step 3: Copy table to a vector           -- 1p
    std::vector<My_pair> V(ints_table.begin(), ints_table.end());

    // Step 4: Sort vector by number of elements in the set for each integer value      -- 1p
    std::sort(V.begin(), V.end(), [](const My_pair& p1, const My_pair& p2) {
        return p1.second.size() < p2.second.size();
    });

    // Step 5: Write the vector V to std::cout     -- 1p
    std::cout << "\n** Table sorted by number of formats **\n";
    std::for_each(V.begin(), V.end(), display_ints{});

    // Step 6: Write to std::cout the number of different formats for each int    -- 1p
    std::cout << "\n** Table with number of formats **\n";
    auto outIt = std::ostream_iterator<std::string>{std::cout, "\n"};
    std::transform(V.begin(), V.end(), outIt, [](const My_pair& p) {
        return std::to_string(p.first) + ": " + std::to_string(p.second.size());
    });
}