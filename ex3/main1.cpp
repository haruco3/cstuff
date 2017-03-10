
#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

int main(int argc, const char *argv[])
{
  ExpList *l = nullptr;
  Exp *e = nullptr;
  //testing add 2 elements
  l = new ExpList(new Constant(20), l);
  l = new ExpList(new Constant(42), l);
  e = new OpApp(plusop, l);
  if (e->eval(nullptr)==62)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << e->eval(nullptr) << endl;  
  l = nullptr;
  //testing add
  l = new ExpList(new Constant(23), l);
  l = new ExpList(new Constant(42), l);
  l = new ExpList(new Constant(666), l);
  l = new ExpList(new Constant(2), l);
  e = new OpApp(plusop, l);
  if (e->eval(nullptr)==733)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << e->eval(nullptr) << endl;  
  l = nullptr;
  //testing multiplication 2 elements
  l = new ExpList(new Constant(10), l);
  l = new ExpList(new Constant(20), l);
  e = new OpApp(timesop, l);
  if (e->eval(nullptr)==200)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl;  
  l = nullptr;
  
  //testing multiplication
  l = new ExpList(new Constant(10), l);
  l = new ExpList(new Constant(20), l);
  l = new ExpList(new Constant(30), l);
  l = new ExpList(new Constant(2), l);
  e = new OpApp(timesop, l);
  if (e->eval(nullptr)==12000)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl;  
  
  //testing multiplication and addition together
  l = nullptr;
  l = new ExpList(new Constant(10), l);
  l = new ExpList(new Constant(20), l);
  e = new OpApp(timesop, l);
  l = new ExpList(e, l);
  l = new ExpList(new Constant(4), l);
  l = new ExpList(new Constant(2), l);
  e = new OpApp(plusop, l);
  if (e->eval(nullptr)==236)
  	cout << "Passed." << endl;
  else
	  cout << "Failed." << endl;  
}
