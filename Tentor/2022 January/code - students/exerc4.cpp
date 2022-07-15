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

using Table = std::map<int, std::set<std::string>>;
using My_pair = std::pair<int, std::set<std::string>>;
// Note: rename types to make the code more readable

struct insert_table {
    // Constructor
    explicit insert_table(Table& T) : T_{ T } {
    }

    void operator()(const std::string& w) {
        T_[std::stoi(w)].insert(w);
    }

private:
    Table& T_;
};

struct display_ints {
    // Constructor
    explicit display_ints(std::ostream& os = std::cout) : os_{ os } {
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
    // Step 1: 
    std::ifstream file("C:/Users/Voysys/Desktop/C++ Recap/Tentor/2022 January/code - students/integers.txt");

    if (!file) {
        std::cout << "Could not open file\n";
        return 0;
    }


    
    std::istream_iterator<std::string> start(file), eos;

    auto ints_table = Table{};

    std::for_each(start, eos, [ints_table](const std::string w) { 
        int int_ = std::stoi(w);
        ints_table[insert(int_)];
        
    });
    
    file.close();
    std::cout << "** Table sorted by integer value **\n";
    std::for_each(ints_table.begin(), ints_table.end(), display_ints{});
   
   


    //std::set<std::string> sString(start, eos);

    //std::vector<int> sInt;
    ////String to int
    //std::transform(start, eos, std::inserter(sInt,sInt.end()), [](std::string x) {return std::stoi(x); });

    
   
  
   

    //std::copy(vString.begin(), vString.end(), std::ostream_iterator<std::string>(std::cout << " "));

    //Skriv ut vString
    //std::for_each(vString.begin(), vString.end(), [&]() {std::cout << vString.first << "\n"; });

    //std::set<int> sInt;
    //Gör om alla strings i vektorn till ints i ett nytt set. Transform itererar genom vektorenrna och stoi (string to integer). to_string gör motsatsen.
    //std::transform(vString.begin(), vString.end(), std::inserter(sInt,sInt.end()), [](std::string x) {return std::stoi(x); });

  
    

    
    



    //std::ostream_iterator<int> streamOut(std::cout, " ");

    //std::vector<double> V(start, eos);
    //std::vector<std::string> v_String;
    //Gör om vector av ints till vektor av string;
    //std::transform(V.begin(), V.end(), std::back_inserter(v_String), [](double x) {return std::to_string(x); });
    //std::map<std::string, int> Map(start, eos);


    

   

  


    // Step 2: 
   

    // Step 3: 

    // Step 4: 

    // Step 5: 

    // Step 6:
}