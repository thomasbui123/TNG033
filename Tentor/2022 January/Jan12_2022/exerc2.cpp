// =======================================================
// Exerc2
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, LiU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

// See also Set3 of course exercises/exercise3

class DayOfWeek {
public:
    explicit DayOfWeek(const std::string& d) {  // 1p
        if (auto it = std::find(days.begin(), days.end(), d); it != days.end()) {
            days_index = static_cast<int>(std::distance(days.begin(), it));
        } else {
            days_index = 0;  // Sunday
        }
    }

    DayOfWeek& operator++() {  // 0.5p
        (++days_index) %= 7;

        return *this;
    }

    DayOfWeek& operator--() {  // 0.5p
        if ((--days_index) == -1) {
            days_index = 6;
        }
        return *this;
    }

    DayOfWeek operator+(int n) const {  // 1p
        assert(n >= 0); // not required

        DayOfWeek res{*this};
        for (int i = 0; i < n % 7; ++i, ++res)
            ;
        return res;
    }

    friend DayOfWeek operator+(int n, const DayOfWeek& d) {  // 1p
        return d + n;
    }

    DayOfWeek operator-(int n) const {  // 1p
        DayOfWeek res{*this};
        for (int i = 0; i < n % 7; ++i, --res)
            ;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const DayOfWeek& d) {
        os << DayOfWeek::days[d.days_index];

        return os;
    }

private:
    const static std::vector<std::string> days;

    int days_index = 0;
};

const std::vector<std::string> DayOfWeek::days{std::string{"Sunday"},   std::string{"Monday"},
                                               std::string{"Tuesday"},  std::string{"Wednesday"},
                                               std::string{"Thursday"}, std::string{"Friday"},
                                               std::string{"Saturday"}};

/**************************************
 * Main function  -- test              *
 * DELIVER UNMODIFIED                  *
 ***************************************/

void foo(DayOfWeek d) {
    std::cout << "Should not be here: " << d << "\n";
}

int main() {
     std::cout << sunday << "\n";*/

    DayOfWeek tng033_exam_day{"Wednesday"};
    std::cout << "Day after tng033 exam: " << ++tng033_exam_day << "\n";       // Thursday
    std::cout << "Day before tng033 exam: " << --(--tng033_exam_day) << "\n";  // Tuesday
    ++tng033_exam_day;
    std::cout << "X-tmas 2022: " << tng033_exam_day + 347 << "\n";  // Sunday

    std::cout << "TNG033 exam grading ready: " << 21 + tng033_exam_day << "\n";  // Wednesday

    DayOfWeek first_day_Feb_22{"Tuesday"};
    std::cout << "Last day of February 2022: " << first_day_Feb_22 + 27 << "\n";  // Monday

    DayOfWeek first_day_2022{"Saturday"};
    std::cout << "First day of 2021: " << first_day_2022 - 365 << "\n";  // Friday

    // std::cout << "First day of 2021: " << 365 - first_day_2022 << "\n"; // should not compile
    // foo("Friday"); // should not compile
}