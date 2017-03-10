
#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

void test(int t1, int t2) {
	if (t1 == t2) {cout << "pass " << t1 << endl;}
	else {cout << "fail " << t1 << endl;}
};

int main(int argc, const char *argv[])
{
	//test let bind
	ExpList *el = new ExpList(new Constant(5), nullptr);
	el = new ExpList(new Constant(3), el);
	el = new ExpList(new Constant(2), el);
	Exp *t = new OpApp(plusop, el);

	el = new ExpList(new Var("x"), nullptr);
	el = new ExpList(new Var("x"), el);
	el = new ExpList(new Var("x"), el);
	Exp *t2 = new OpApp(timesop, el);
	t = new Let("x", t, t2);
	test(t->eval(nullptr), 1000);

	//test let bind with more than one variable
	ExpList *m = new ExpList(new Var("z"), nullptr);
	m = new ExpList(new Constant(10), m);

	el = new ExpList(new Let("z", new Constant(2), new OpApp(timesop, m)), nullptr);
	el = new ExpList(new Let("y", new Constant(10), new Var("y")), el);
	el = new ExpList(new Constant(5), el);
	el = new ExpList(new Var("x"), el);
	t = new Let("x", new Constant(2), new OpApp(plusop, el));
	test(t->eval(nullptr), 37);

	//test let bind when there are different scopes for one variable (1)
	el = new ExpList(new Var("y"), nullptr);
	el = new ExpList(new Let("y", new Constant(10), new Var("y")), el);
	el = new ExpList(new Var("y"), el);
	t = new Let("y", new Constant(2), new OpApp(plusop, el));
	test(t->eval(nullptr), 14);

	//test let bind when there are different scopes for one variable (1)
	m = new ExpList(new Var("x"), nullptr);
	m = new ExpList(new Constant(10), m);

	el = new ExpList(new Let("x", new Constant(2), new OpApp(timesop, m)), nullptr);
	el = new ExpList(new Let("x", new Constant(10), new Var("x")), el);
	el = new ExpList(new Constant(5), el);
	el = new ExpList(new Var("x"), el);
	t = new Let("x", new Constant(2), new OpApp(plusop, el));
	test(t->eval(nullptr), 37);

	return 0;
}
