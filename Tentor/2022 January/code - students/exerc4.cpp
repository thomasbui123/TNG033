// =======================================================
// Exerc4
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, LiU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iterator> //ostream och istream
#include <fstream>
#include <map>
#include <algorithm> //copy
#include <vector>
#include <string>
#include <set>


int main() {
    // Step 1: 
    std::ifstream file("C:/Users/Voysys/Desktop/C++ Recap/Tentor/2022 January/code - students/integers.txt");

    if (!file) {
        std::cout << "Could not open file\n";
        return 0;
    }

    std::map<int, std::set<std::string>> mapOut;
    
    std::istream_iterator<std::string> start(file), eos;
    std::vector<std::string> vString(start, eos);

    std::set<int> sInt;
    std::transform(vString.begin(), vString.end(), std::inserter(sInt,sInt.end()), [](std::string x) {return std::stoi(x); });

    m

    
    



    //std::ostream_iterator<int> streamOut(std::cout, " ");

    //std::vector<double> V(start, eos);
    //std::vector<std::string> v_String;
    //Gör om vector av ints till vektor av string;
    //std::transform(V.begin(), V.end(), std::back_inserter(v_String), [](double x) {return std::to_string(x); });
    //std::map<std::string, int> Map(start, eos);


    file.close();

   

  


    // Step 2: 
   

    // Step 3: 

    // Step 4: 

    // Step 5: 

    // Step 6:
}