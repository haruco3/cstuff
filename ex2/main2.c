// main function for evaluation expression exercise

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evalexp.h"

// tree construction functions

struct exp *mkvar(char *cp)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = isvar;
  strncpy(ep->var, cp, 8);
  return ep;
};

struct exp *mkconstant(int n)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = isconstant;
  ep->constant = n;
  return ep;
};

struct exp *mkopapp(enum op op, struct explist *el)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = isopapp;
  ep->op =  op;
  ep->exps =  el;
  return ep;
};

struct exp *mklet(char *cp, struct exp *e1, struct exp *e2)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = islet;
  strncpy(ep->bvar, cp, 8);
  ep->bexp = e1;
  ep->body = e2;
  return ep;
};

struct explist *cons(struct exp *e, struct explist *l)
{
  struct explist *l2 = malloc(sizeof(struct explist));
  l2->head = e;
  l2->tail = l;
  return l2;
}

// main for testing

int main(int argc, const char * argv[])
{
  struct exp *e1, *e2;
  struct explist *l, *m;
    
  
  // test let bind
  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(3), l);
  l = cons(mkconstant(2), l);
  e1 = mkopapp(isplus, l);

  l = NULL;
  l = cons(mkvar("x"), l);
  l = cons(mkvar("x"), l);
  l = cons(mkvar("x"), l);
  e2 = mkopapp(ismult, l);
  e1 = mklet("x", e1, e2);

  if (evalexp(e1)==1000)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }

  // test let bind with more than one variables
  m = NULL;
  m = cons(mkvar("z"), m);
  m = cons(mkconstant(10), m);
  
  l = NULL;
  l = cons(mklet("z", mkconstant(2), mkopapp(ismult, m)), l);
  l = cons(mklet("y", mkconstant(10), mkvar("y")), l);
  l = cons(mkconstant(5), l);
  l = cons(mkvar("x"), l);
  
  e1 = mklet("x", mkconstant(2), mkopapp(isplus, l));
  if (evalexp(e1)==37)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  
  // test let bind when there are different scopes for one variable (1)
  l = NULL;
  e1 = mkconstant(2);
  l = NULL;
  l = cons(mkvar("y"), l);
  l = cons(mklet("y", mkconstant(10), mkvar("y")), l);
  l = cons(mkvar("y"), l);
  e2 = mkopapp(isplus, l);
  e1 = mklet("y", e1, e2);
  if (evalexp(e1)==14)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  
  // test let bind when there are different scopes for one variable (2)
  m = NULL;
  m = cons(mkvar("x"), m);
  m = cons(mkconstant(10), m);
  
  l = NULL;
  l = cons(mklet("x", mkconstant(2), mkopapp(ismult, m)), l);
  l = cons(mklet("x", mkconstant(10), mkvar("x")), l);
  l = cons(mkconstant(5), l);
  l = cons(mkvar("x"), l);
  
  e1 = mklet("x", mkconstant(2), mkopapp(isplus, l));
  if (evalexp(e1)==37)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  return 0;
}
