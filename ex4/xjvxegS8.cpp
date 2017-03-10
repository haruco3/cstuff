// Created by Rinaldy

#include <iostream>
#include <functional>

using namespace std;

#include "templatesast.h"

#include "templatesast.cpp" // this is where the eval functions should be

// instantiate the AST template and try it

// ints
int add(int x, int y) { return x + y; }
int times(int x, int y) { return x * y; }
int sub(int x, int y) { return x - y; }

// floats
float mult(float x, float y) { return x * y; }
float div(float x, float y) { return x / y; }


int main(int argc, const char *argv[]) {
    // Takes test cases from previous exercise and convert them to template-friendly
    operators<int> plusop = {add, 0};
    operators<int> timesop = {times, 1};
    ExpList<int> *l = nullptr;
    Exp<int> *e = nullptr;
    //testing add 2 elements
    l = new ExpList<int>(new Constant<int>(20), l);
    l = new ExpList<int>(new Constant<int>(42), l);
    e = new OpApp<int>(plusop, l);
    if (e->eval(nullptr)==62) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }
    l = nullptr;
    //testing add
    l = new ExpList<int>(new Constant<int>(23), l);
    l = new ExpList<int>(new Constant<int>(42), l);
    l = new ExpList<int>(new Constant<int>(666), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    e = new OpApp<int>(plusop, l);
    if (e->eval(nullptr)==733) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }
    l = nullptr;
    //testing multiplication 2 elements
    l = new ExpList<int>(new Constant<int>(10), l);
    l = new ExpList<int>(new Constant<int>(20), l);
    e = new OpApp<int>(timesop, l);
    if (e->eval(nullptr)==200) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }
    l = nullptr;

    //testing multiplication
    l = new ExpList<int>(new Constant<int>(10), l);
    l = new ExpList<int>(new Constant<int>(20), l);
    l = new ExpList<int>(new Constant<int>(30), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    e = new OpApp<int>(timesop, l);
    if (e->eval(nullptr)==12000) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }

    //testing multiplication and addition together
    l = nullptr;
    l = new ExpList<int>(new Constant<int>(10), l);
    l = new ExpList<int>(new Constant<int>(20), l);
    e = new OpApp<int>(timesop, l);
    l = new ExpList<int>(e, l);
    l = new ExpList<int>(new Constant<int>(4), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    e = new OpApp<int>(plusop, l);
    if (e->eval(nullptr)==236) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }
    l = nullptr;
    ExpList<int> *m = nullptr;
    Exp<int> *e1 = nullptr;
    Exp<int> *e2 = nullptr;
    // test let bind
    l = new ExpList<int>(new Constant<int>(5), l);
    l = new ExpList<int>(new Constant<int>(3), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    e1 = new OpApp<int>(plusop, l);
    l = nullptr;
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Var<int>("x"), l);
    e2 = new OpApp<int>(timesop, l);
    e1 = new Let<int>("x", e1, e2);
    if (e1->eval(nullptr)==1000) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }
    // test let bind with more than one variables
    l = nullptr;
    m = new ExpList<int>(new Var<int>("z"), m);
    m = new ExpList<int>(new Constant<int>(10), m);
    l = new ExpList<int>(new Let<int>("z", new Constant<int>(2), new OpApp<int>(timesop, m)), l);
    l = new ExpList<int>(new Let<int>("y", new Constant<int>(10), new Var<int>("y")), l);
    l = new ExpList<int>(new Constant<int>(5), l);
    l = new ExpList<int>(new Var<int>("x"), l);
    e1 = new Let<int>("x", new Constant<int>(2), new OpApp<int>(plusop, l));
    if (e1->eval(nullptr)==37) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }
    // test let bind when there are different scopes for one variable
    l = nullptr;
    m = nullptr;
    m = new ExpList<int>(new Var<int>("y"), m);
    m = new ExpList<int>(new Constant<int>(10), m);
    l = new ExpList<int>(new Let<int>("y", new Constant<int>(2), new OpApp<int>(timesop, m)), l);
    l = new ExpList<int>(new Let<int>("y", new Constant<int>(10), new Var<int>("y")), l);
    l = new ExpList<int>(new Constant<int>(5), l);
    l = new ExpList<int>(new Var<int>("y"), l);
    e1 = new Let<int>("y", new Constant<int>(2), new OpApp<int>(plusop, l));
    if (e1->eval(nullptr)==37) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }

    //(= x 2 (+ x 5 1 (= x 10 x) (= x 2 (* 10 x 2 (+ 2 3 (= y 1 (* y 2)))))))
    l = nullptr;
    m = nullptr;
    //(= y 1 (* y 2))
    l = new ExpList<int>(new Constant<int>(2), l);
    l = new ExpList<int>(new Var<int>("y"), l);
    e1 = new Let<int>("y", new Constant<int>(1), new OpApp<int>(timesop, l));
    //(+ 2 3 e1)
    l = nullptr;
    l = new ExpList<int>(e1, l);
    l = new ExpList<int>(new Constant<int>(3), l);
    l = new ExpList<int>(new Constant<int>(2), l);
    e1 = new OpApp<int>(plusop, l);
    //(= x 2 (* 10 x 2 e1))
    l = nullptr;
    l = new ExpList<int>(e1, l);
    l = new ExpList<int>(new Constant<int>(2), l);
    l = new ExpList<int>(new Var<int>("x"), l);
    l = new ExpList<int>(new Constant<int>(10), l);
    e1 = new OpApp<int>(timesop, l);
    e1 = new Let<int>("x", new Constant<int>(2), e1);
    //(= x 2 (+ x 5 1 (= x 10 x) e1))
    l = nullptr;
    l = new ExpList<int>(e1, l);
    l = new ExpList<int>(new Let<int>("x", new Constant<int>(10), new Var<int>("x")), l);
    l = new ExpList<int>(new Constant<int>(1), l);
    l = new ExpList<int>(new Constant<int>(5), l);
    l = new ExpList<int>(new Var<int>("x"), l);
    e1 = new OpApp<int>(plusop, l);
    e1 = new Let<int>("x", new Constant<int>(2), e1);
    if (e1->eval(nullptr)==298) {
        cout << "Passed." << endl;
    }
    else {
        cout << "Failed." << endl;
    }

    /* Original sample main code.. IGNORE THIS
    operators<int> intops = {add, 0};

    ExpList<int> *l = nullptr;
    l = new ExpList<int>(new Constant<int>(30), l);
    l = new ExpList<int>(new Constant<int>(12), l);
    Exp<int> *e = new OpApp<int>(intops, l);


    cout << e->eval(nullptr) << endl; // should print 0 + 12 + 30 = 42


    Exp<int> *e1 = new OpApp<int>(intops, nullptr);
    cout << e1->eval(nullptr) << endl; // should print 0

    operators<float> floatops = {mult, 1.0};

    ExpList<int><float> *l2 = nullptr;
    l2 = new ExpList<int><float>(new Constant<int><float>(.222), l2);
    l2 = new ExpList<int><float>(new Constant<int><float>(3.0), l2);
    Exp<int><float> *e2 = new OpApp<int><float>(floatops, l2);
    cout << e2->eval(nullptr) << endl; // should print 0.666 = 1.0 * 3.0 * .222

    operators<double> doubleops = {times, 1.0};
    ExpList<int><double> *l3 = nullptr;
    l3 = new ExpList<int><double>(new Constant<int><double>(2.5), l3);
    l3 = new ExpList<int><double>(new Constant<int><double>(100.5), l3);
    l3 = new ExpList<int><double>(new Constant<int><double>(2.0), l3);
    Exp<int><double> *e3 = new OpApp<int><double>(doubleops, l3);
    cout << e3->eval(nullptr) << endl; // should print 251.25
    */

    return 0;
}