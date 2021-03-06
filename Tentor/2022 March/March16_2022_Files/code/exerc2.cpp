// =======================================================
// Exerc2
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, liU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iomanip>
#include <cmath>  //log2

// ADD class Log2
class Log2 {
public:
    explicit Log2(unsigned long int i) : x{ i } {

    }

    double eval() {
        return log2(x);
    }
    
    Log2 operator++() { //pre
        x = x*2;
        return *this;
    }

    Log2 operator++(int) { //post, passing dummy parameter int to distinguish
        Log2 old_log{ *this };
        ++(*this);  // pre-increment

        return old_log;
    }

    Log2 operator+=(const Log2& rhs) {
        x = x * rhs.x;
        return *this;
    }

    Log2 operator+( Log2 rhs) const {
        return (rhs += *this);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Log2& rhs) {
        return stream << "log_2(" << rhs.x << ")";
    }

private:
    unsigned long x;  // x ?r det man vill ?t och anv?nda. den som blir this
};

/*
 * main: to test class Log2
 *       deliver unmodified
 */

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Log2 l1{1};
    std::cout << l1 << " = " << l1.eval() << "\n\n";  // log_2(1) = 0.00

    std::cout << "Pre and pos-increment:\n";
    std::cout << "++l1 = " << ++l1 << " = ";  // ++l1 = log_2(2) =
    std::cout << l1.eval() << "\n";           // 1.00

    std::cout << "l1++ = " << l1++ << "\n";   // l1++ = log_2(2)
    std::cout << "l1 = " << l1 << "\n\n";    // l1 = log_2(4)

    std::cout << "operator+= and operator+:\n";
    Log2 l2{5};  // log_2(5)

    l2 += l1;

    std::cout << "l2 = " << l2 << " = " << l2.eval() << "\n";  // l2 = log_2(20) = 4.32
    std::cout << "l2 + l1 = " << l2 + l1 << "\n\n";            // l2 + l1 = log_2(80)

    std::cout << "Other expressions:\n";
    Log2 l4{l2};
    std::cout << "l4 = " << l4 << " = " << l4.eval() << "\n";
    std::cout << "l1 = " << l1 << " = " << l1.eval() << "\n";

    l2 = (++l1 + ++l4) + Log2(6);
    std::cout << "l4 = " << l4 << " = " << l4.eval() << "\n";
    std::cout << "l1 = " << l1 << " = " << l1.eval() << "\n";
    std::cout << "l2 = " << l2 << " = " << l2.eval() << "\n";  // l2 = log_2(1920) = 10.91
}
