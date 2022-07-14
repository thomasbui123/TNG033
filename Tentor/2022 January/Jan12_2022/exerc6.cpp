// =======================================================
// Exerc6
// Name:
// LiU-id:
// Personal number:
// =======================================================
// Write your name, LiU-id, and personal number. Otherwise, your exam is not graded.

#include <iostream>
#include <string>
#include <vector>

// #include "vld.h"

/* ***************************
 * Class Boolean_expression  *
 * ***************************/

class Boolean_expression {  // Abstract class
public:
    virtual ~Boolean_expression() = default;

    virtual bool evaluate() const = 0;

    virtual Boolean_expression *clone() const = 0;

    // Overload stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Boolean_expression &E) {
        E.display(os);  // dynamic binding
        return os;
    }

protected:
    Boolean_expression() = default;  // call by the constructors of sub-classes

    virtual void display(std::ostream &) const = 0;

    // Copy constructor
    Boolean_expression(const Boolean_expression &) = default;

    // Assignment operator is disabled  -- by default it will disable operator= in the derived
    // classes
    Boolean_expression &operator=(const Boolean_expression &) = delete;
};

/* ************************
 * Class Truth_value      *
 * *************************/

class Truth_value : public Boolean_expression {
public:
    Truth_value(bool b) : value{b} {
    }

    bool evaluate() const override {
        return value;
    }

    virtual Truth_value *clone() const override {
        return (new Truth_value{*this});
    }

private:
    const bool value;

protected:
    Truth_value(const Truth_value &) = default;

    void display(std::ostream &os) const override {
        os << (value ? "T" : "F");
    }
};

/* ******************************
 * Class Not                    *
 * ******************************/

class Not : public Boolean_expression {
public:
    Not(const Boolean_expression &e) : arg{e.clone()} {
    }

    ~Not() {
        delete arg;
        arg = nullptr;
    }

    bool evaluate() const override {
        return !arg->evaluate();
    }

    virtual Not *clone() const override {
        return (new Not{*this});
    };

protected:
    Boolean_expression *arg;

    // Copy constructor
    Not(const Not &e) : arg{e.arg->clone()} {
    }

    void display(std::ostream &os) const override {
        os << "!" << *arg;
    }
};

/* ******************************
 * Class Binary_bool_expression *
 * ******************************/
// This class is also an abstract class

class Binary_bool_expression : public Boolean_expression {
public:
    ~Binary_bool_expression() {
        delete left_arg;
        delete right_arg;
        left_arg = right_arg = nullptr;
    }

protected:
    Boolean_expression *left_arg;
    Boolean_expression *right_arg;
    const std::string op_symbol;

    // Constructor
    Binary_bool_expression(const Boolean_expression &arg1, const Boolean_expression &arg2,
                           std::string op)
        : left_arg{arg1.clone()}, right_arg(arg2.clone()), op_symbol{op} {
    }

    // Copy constructor
    Binary_bool_expression(const Binary_bool_expression &e)
        : left_arg{e.left_arg->clone()}, right_arg{e.right_arg->clone()}, op_symbol{e.op_symbol} {
    }

    void display(std::ostream &os) const override {
        os << "(" << *left_arg << op_symbol << *right_arg << ")";
    }
};

/* ************************
 * Class And              *
 * *************************/

class And : public Binary_bool_expression {
public:
    // Constructor
    And(const Boolean_expression &arg1, const Boolean_expression &arg2)
        : Binary_bool_expression(arg1, arg2, " * ") {
    }

    bool evaluate() const override {
        return (left_arg->evaluate() && right_arg->evaluate());
    }

    virtual And *clone() const override {
        return (new And{*this});
    }

protected:
    And(const And &) = default;  // only way to copy boolean expressions is through function clone
};

/* ************************
 * Class Or               *
 * *************************/

class Or : public Binary_bool_expression {
public:
    Or(const Boolean_expression &arg1, const Boolean_expression &arg2)
        : Binary_bool_expression(arg1, arg2, " + ") {
    }

    bool evaluate() const override {
        return (left_arg->evaluate() || right_arg->evaluate());
    }

    virtual Or *clone() const override {
        return (new Or{*this});
    }

protected:
    Or(const Or &) = default;  // only way to copy boolean expressions is through function clone
};

/* ************************
 * MAIN: do not modify     *
 * *************************/

std::string to_string(bool b) {
    return (b ? "True" : "False");
}

int main() {
    int i{10};

    std::vector<Boolean_expression *> V1{
        new Truth_value{false}, new Not{Truth_value{true}},
        new And{Truth_value{i % 2 == 0}, Truth_value{i % 5 == 0}},
        new Or{Truth_value{i % 2 == 0}, Truth_value{i % 3 == 0}},
        new Or{Truth_value{i % 6 == 0}, Truth_value{i % 3 == 0}}};

    for (auto e : V1) {
        std::cout << *e << ": " << to_string(e->evaluate()) << "\n";
    }

    std::cout << "\n";

    // More complex boolean expressions
    std::vector<Boolean_expression *> V2{new And{*V1[3], *V1[2]}, new Not{*V1[4]},
                                         new And{Not{*V1[3]}, *V1[2]}};

    for (auto e : V2) {
        std::cout << *e << ": " << to_string(e->evaluate()) << "\n";
    }

    // Deallocate memory
    for (auto e : V1) {
        delete e;
    }

    for (auto e : V2) {
        delete e;
    }
}

/*
 * "*" represents AND
 * "+" represents OR
 * "!" represents "not"
 *
 * * Expected output
F: False
!T: False
(T * T): True
(T + F): True
(F + F): False

((T + F) * (T * T)): True
!(F + F): True
(!(T + F) * (T * T)): False

 */