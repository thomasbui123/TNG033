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
    Select_smaller_than(int i) : val{ i } {
    }

    bool operator()(int k) {
        return k < val;
    }

private:
    int val;
};

int main() {
    
    std::cout << "STEP 1 :\n";

    std::ifstream file("C:/Users/Voysys/Desktop/C++ Recap/Tentor/2022 March/March16_2022/March16_2022/code/numbers.txt");

    if (!file) {
        std::cout << "Input file cannot be opened!!\n";
        return 0;
    }

    //std::istream_iterator<int> start(file), eos; //start och eos �r variabelnamn man kan anv�nda senare
    ////std::istream_iterator<int> eos; Man kan g�ra det s�h�r ocks� end of stream
    //std::vector<int> V(start, eos); //L�gg in i vektor med b�rjan av streamen till slutet av streamen
    //file.close();

    //std::cout << "Number of values: " << V.size() << "\n";
    //std::copy(std::begin(V), std::end(V), std::ostream_iterator<int>(std::cout, " ")); //
    //std::cout << "\n\n";

    //Kan �ven skriva s�h�r
    std::istream_iterator<int> start(file), eos;
    std::ostream_iterator<int> streamOut(std::cout, " "); //Itererar ut genom cout stream och s�tter " " mellanrum mellan varje data den itererar
    //std::copy(start, eos, streamOut); Detta funkar ocks�, men hon vill att man sparar allt i en vektor och skriver ut vektorn
    
    //Spara v�rdena i en vektor.
    std::vector<int> V(start, eos);
    //Gl�m inte att st�nga filen.
    file.close();
    //Kopiera ut till outstream.
    std::copy(V.begin(), V.end(), streamOut); //Kopiera f�rsta v�rde i V till slutet av V och kopiera till streamOut som i detta fall itererar ut det till cout-stream
    //Newline till step 2
    std::cout << "\n\n";



    /* *************************** */
    std::cout << "STEP 2\n";
    std::cout << "Amount of numbers in file: " << V.size() << "\n";
    std::cout << "V[V.size() / 2 - 1] = " << V[V.size() / 2 - 1] << "\n";
    std::cout << "V[V.size() / 2] = " << V[V.size() / 2] << "\n";

    if (V.size() % 2 == 0) {
        std::cout << "Median is: " << (V[V.size() / 2 - 1] + V[V.size() / 2]) / 2.0 << "\n";
    }
    else {
        std::cout << "Median is: " << V[V.size() / 2 - 1] << "\n";
    }

    std::cout << "STEP 3\n";
    std::set<int> even{};
    std::set<int> odd{};

    //std::copy_if(V.begin(), V.end(), std::inserter(even, even.end()), [](int V) {return (V % 2 == 0);});
    //Lagra j�mna v�rden i set even.
    std::copy_if(V.begin(), V.end(), std::inserter(even, even.end()), [](int x) {return (x % 2 == 0); });
    std::copy_if(V.begin(), V.end(), std::inserter(odd, odd.end()), [](int x) {return (x % 2 == 1); });
   

    std::cout << "STEP 4\n";
    std::cout << "Even values: ";
    std::copy(std::rbegin(even), std::rend(even), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::cout << "Odd values: ";
    std::copy(std::rbegin(odd), std::rend(odd), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "STEP 5\n";


  
    /* *************************** */
    std::cout << "STEP 5\n";

    std::vector<int> V1;

    if (odd.size() > 0) {
        std::copy_if(std::begin(even), std::end(even), std::back_inserter(V1), Select_smaller_than(*std::begin(odd)));
        std::copy(std::begin(V1), std::end(V1), std::ostream_iterator<int>(std::cout, " "));
    }
    std::cout << "\n\n";
}
