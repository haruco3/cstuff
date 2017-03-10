
#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

int main(int argc, const char *argv[])
{
  ExpList *l = nullptr;
  ExpList *m = nullptr;
  Exp *e1 = nullptr;
  Exp *e2 = nullptr;
  // test let bind
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Constant(3), l);
  l = new ExpList(new Constant(2), l);
  e1 = new OpApp(plusop, l);
  l = nullptr;
  l = new ExpList(new Var("x"), l);
  l = new ExpList(new Var("x"), l);
  l = new ExpList(new Var("x"), l);
  e2 = new OpApp(timesop, l);
  e1 = new Let("x", e1, e2);
  if (e1->eval(nullptr)==1000)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl;  
  // test let bind with more than one variables
  l = nullptr;
  m = new ExpList(new Var("z"), m);
  m = new ExpList(new Constant(10), m);
  l = new ExpList(new Let("z", new Constant(2), new OpApp(timesop, m)), l);
  l = new ExpList(new Let("y", new Constant(10), new Var("y")), l);
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Var("x"), l);
  e1 = new Let("x", new Constant(2), new OpApp(plusop, l));
  if (e1->eval(nullptr)==37)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl; 
  // test let bind when there are different scopes for one variable 
  l = nullptr;
  m = nullptr;
  m = new ExpList(new Var("y"), m);
  m = new ExpList(new Constant(10), m);
  l = new ExpList(new Let("y", new Constant(2), new OpApp(timesop, m)), l);
  l = new ExpList(new Let("y", new Constant(10), new Var("y")), l);
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Var("y"), l);
  e1 = new Let("y", new Constant(2), new OpApp(plusop, l));
  if (e1->eval(nullptr)==37)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl; 
  
  //(= x 2 (+ x 5 1 (= x 10 x) (= x 2 (* 10 x 2 (+ 2 3 (= y 1 (* y 2)))))))
  l = nullptr;
  m = nullptr;
  //(= y 1 (* y 2))
  l = new ExpList(new Constant(2), l);
  l = new ExpList(new Var("y"), l);
  e1 = new Let("y", new Constant(1), new OpApp(timesop, l));
  //(+ 2 3 e1)
  l = nullptr;
  l = new ExpList(e1, l);
  l = new ExpList(new Constant(3), l);
  l = new ExpList(new Constant(2), l);
  e1 = new OpApp(plusop, l);
  //(= x 2 (* 10 x 2 e1))
  l = nullptr;
  l = new ExpList(e1, l);
  l = new ExpList(new Constant(2), l);
  l = new ExpList(new Var("x"), l);
  l = new ExpList(new Constant(10), l);
  e1 = new OpApp(timesop, l);
  e1 = new Let("x", new Constant(2), e1);
  //(= x 2 (+ x 5 1 (= x 10 x) e1))
  l = nullptr;
  l = new ExpList(e1, l);
  l = new ExpList(new Let("x", new Constant(10), new Var("x")), l);
  l = new ExpList(new Constant(1), l);
  l = new ExpList(new Constant(5), l);
  l = new ExpList(new Var("x"), l);
  e1 = new OpApp(plusop, l);
  e1 = new Let("x", new Constant(2), e1);
  if (e1->eval(nullptr)==298)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl; 
     
}
