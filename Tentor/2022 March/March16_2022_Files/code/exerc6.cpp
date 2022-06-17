// =======================================================
// Exerc6
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, LiU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

/**********************************
 * Class Document                  *
 ***********************************/


/******************************
 * Class Email                 *
 *******************************/


/*****************************
 * Class Report               *
 *****************************/


/*******************
 * Main function    *
 ********************/

int main() {
    std::vector<Document*> V;

    /*******************************************************/
    std::cout << "\n***PHASE 1: Test Email class\n\n";
    /*******************************************************/

    std::string mesg1("The exam of TNG033 runs 8-13, march 16.");
    std::string mesg2(
        "TNG033 tentavisning will be announced soon by an e-mail sent to all students.");

    // Create an Email
    // sender: aidvi, receiver: devil007, subject: TNG033 exam
    V.push_back(new Email{"aidvi", "devil007", "TNG033 exam", mesg1});

    // Create another Email
    // sender: devil007, receiver: all, subject: TNG033 tentavisning
    V.push_back(new Email("devil007", "all", "TNG033 tentavisning", mesg2));

    std::cout << *V[0] << "\n\n";
    std::cout << *V[1] << "\n\n";

    /*******************************************************/
    std::cout << "\n***PHASE 2: Test Essay class\n\n";
    /*******************************************************/

    std::string text1 =
        "To read and write binary files\nObjectives: To write programs in C++ with vectors and "
        "records (struct).\nTo structure programs with functions.";

    std::string text2 =
        "Endians are a confusing topic for many people.\nHopefully, by reading this article you "
        "will understand both what endian means.\nBla, bla ...";

    // Create a report
    V.push_back(new Report{"Aida Nordman", "Lab1"});
    V[2]->setText(text1);

    // Create another report
    V.push_back(new Report{"Aida Nordman", "Endian problem"});
    V[3]->setText(text2);

    std::cout << *V[2] << "\n\n";
    std::cout << *V[3] << "\n\n";

    /**********************************************************/
    std::cout << "\n***PHASE 3: add keywords\n\n";
    /**********************************************************/

    V[1]->add_keyword("tng033");
    V[2]->add_keyword("tng033");
    V[2]->add_keyword("c++");
    V[3]->add_keyword("endian");
    V[3]->add_keyword("exam");

    std::cout << *V[1] << "\n\n";
    std::cout << *V[2] << "\n\n";
    std::cout << *V[3] << "\n\n";

    /**********************************************************/
    std::cout << "\n***PHASE 4: list documents by key \n\n";
    /**********************************************************/

    std::cout << "**Documents associated to keyword = exam\n\n";
    // ADD CODE here to display all documents associated to keyword "exam"

    std::cout << "**Documents associated to keyword = tng033\n\n";
    // ADD CODE here to display all documents associated to keyword "tng033"

    std::cout << "Delete all documents ...\n\n";

    // Free memory for all documents
    for (auto ptr : V) {
        delete ptr;
    }

    std::cout << "**Documents associated to keyword = exam\n";
    // ADD CODE here to display again all documents associated to keyword "exam"
}
