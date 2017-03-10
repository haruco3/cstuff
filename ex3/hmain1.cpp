
#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

void test(int t1, int t2) {
	if (t1 == t2) {cout << "pass" << endl;}
	else {cout << "fail" << endl;}
};

int main(int argc, const char *argv[])
{
	//testing constant
	Exp *t = new Constant(2);
	test(t->eval(nullptr), 2);

	//testing multiplication
	ExpList *el = nullptr;
	el = new ExpList(new Constant(5), el);
	el = new ExpList(new Constant(3), el);
	el = new ExpList(new Constant(2), el);
	el = new ExpList(new Constant(2), el);
	t = new OpApp(timesop, el);
	test(t->eval(nullptr), 60);

	//testing multiplication one element
	el = new ExpList(new Constant(5), nullptr);
	t = new OpApp(timesop, el);
	test(t->eval(nullptr), 5);

	//testing multiplication two element
	el = new ExpList(new Constant(2), el);
	t = new OpApp(timesop, el);
	test(t->eval(nullptr), 10);

	//testing addition
	el = new ExpList(new Constant(5), nullptr);
	el = new ExpList(new Constant(3), el);
	el = new ExpList(new Constant(2), el);
	el = new ExpList(new Constant(2), el);
	t = new OpApp(plusop, el);
	test(t->eval(nullptr), 12);

	//testing addition one element
	el = new ExpList(new Constant(5), nullptr);
	t = new OpApp(plusop, el);
	test(t->eval(nullptr), 5);

	//testing addition two element
	el = new ExpList(new Constant(2), el);
	t = new OpApp(plusop, el);
	test(t->eval(nullptr), 7);

	el = new ExpList(new Constant(5), nullptr);
	el = new ExpList(new Constant(2), el);
	t = new OpApp(plusop, el);
	el = new ExpList(new Constant(t->eval(nullptr)), el);
	t = new OpApp(timesop, el);
	test(t->eval(nullptr), 70);

	return 0;
}
