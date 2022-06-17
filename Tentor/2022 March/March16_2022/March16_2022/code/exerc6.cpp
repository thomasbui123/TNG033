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
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>  //istringstream

/**********************************
 * Class Document                  *
 ***********************************/

class Document {
public:
    // Constructor -- avoid implicit conversion from a string to Document
    explicit Document(const std::string& T = "") : text(T), keywords{} {
    }

    // Copy constructor disabled
    Document(const Document&) = delete;

    // Assignment is disabled
    Document& operator=(const Document&) = delete;

    virtual ~Document();  // Document is a polymorphic class

    std::string getText() const {
        return text;
    }

    void setText(const std::string& T) {
        text = T;
    }

    void add_keyword(const std::string& key);

    static void list_documents_by_key(const std::string& key);

    friend std::ostream& operator<<(std::ostream& out, const Document& T);

protected:
    std::string text;
    std::set<std::string>
        keywords;  // no repeated keywords, keywords are stored in lower-case letters

    // Table to associate each keyword with the list of documents where it occurs
    static std::map<std::string, std::set<Document*>> table_keys;

    virtual std::string document_type() const = 0;
    virtual std::ostream& display(std::ostream& out) const;
};

// static data member
std::map<std::string, std::set<Document*>> Document::table_keys;

Document::~Document() {
    // update the table_keys
    for (auto it1 = keywords.begin(); it1 != keywords.end(); it1++) {
        std::set<Document*>& S = table_keys[*it1];  // set of documents with keyword *it1
        S.erase(this);

        // if no other documents associated with the key then erase the key from the table
        if (table_keys[*it1].size() == 0)
            table_keys.erase(*it1);
    }
}

std::ostream& Document::display(std::ostream& out) const {
    out << document_type() << "\n";

    std::cout << "Keywords: ";
    std::copy(keywords.begin(), keywords.end(), std::ostream_iterator<std::string>(out, " "));

    out << "\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Document& T) {
    T.display(out);

    return out;
}

void Document::add_keyword(const std::string& key) {
    keywords.insert(key);
    table_keys[key].insert(this);
}

// static member function
void Document::list_documents_by_key(const std::string& key) {
    if (table_keys.find(key) != table_keys.end()) {  // key is in the table
        std::set<Document*>& S = table_keys[key];

        for (auto it = S.begin(); it != S.end(); ++it) {
            std::cout << **it << "\n";  //*it is a Document*
        }
    } else {
        std::cout << "No documents associated with keyword " << key << "!!\n";
    }
}

/******************************
 * Class Email                 *
 *******************************/

class Email : public Document {
public:
    Email(const std::string& s, const std::string& r, const std::string& sub,
          const std::string mesg = "")
        : Document(mesg), sender(s), receiver(r), subject(sub) {
    }

protected:
    const std::string sender;
    const std::string receiver;
    const std::string subject;

    virtual std::string document_type() const override {
        return "Email";
    }

    std::ostream& display(std::ostream& out) const override;
};

std::ostream& Email::display(std::ostream& out) const {
    Document::display(out);

    out << "Sender: " << sender << "\n";
    out << "Receiver: " << receiver << "\n";
    out << "Subject: " << subject << "\n";
    out << "Mesg: " << text << "\n";

    return out;
}

/*****************************
 * Class Report               *
 *****************************/

class Report : public Document {
public:
    Report(const std::string& a, const std::string& t) : Document(), author{a}, title{t} {
    }

protected:
    const std::string author;
    std::string title;

    virtual std::string document_type() const override {
        return "Report";
    }

    std::ostream& display(std::ostream& out) const override;
};

std::ostream& Report::display(std::ostream& out) const {
    Document::display(out);

    out << "Title: " << title << "\n";
    out << "Author: " << author << "\n";
    out << "=============================\n";

    std::istringstream in{text};
    std::string line;

    std::getline(in, line);  // get first line of the essay's text
    out << line << " ...\n";

    return out;
}

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
    std::cout << "\n***PHASE 2: Test Report class\n\n";
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

    // ADD CODE to display all documents associated to keyword "exam"
    std::cout << "**Documents associated to keyword = exam\n\n";
    Document::list_documents_by_key("exam");

    std::cout << "**Documents associated to keyword = tng033\n\n";
    // ADD CODE to display all documents associated to keyword "tng033"
    Document::list_documents_by_key("tng033");

    std::cout << "Delete all documents ...\n\n";

    // Free memory for all documents
    for (auto ptr : V) {
        delete ptr;
    }

    std::cout << "**Documents associated to keyword = exam\n";
    // ADD CODE to display again all documents associated to keyword "exam"
    Document::list_documents_by_key("exam");
}
