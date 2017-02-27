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
  struct explist *l;
    
  //testing constant
  if (evalexp(mkconstant(2))==2)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing multiplication
  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(3), l);
  l = cons(mkconstant(2), l);
  l = cons(mkconstant(2), l);
  if (evalexp(mkopapp(ismult, l))==60)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing multiplication one element
  l = NULL;
  l = cons(mkconstant(5), l);
  if (evalexp(mkopapp(ismult, l))==5)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing multiplication two element
  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(2), l);
  if (evalexp(mkopapp(ismult, l))==10)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing addition
  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(3), l);
  l = cons(mkconstant(2), l);
  l = cons(mkconstant(2), l);
  if (evalexp(mkopapp(isplus, l))==12)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing addition one element
  l = NULL;
  l = cons(mkconstant(5), l);
  if (evalexp(mkopapp(isplus, l))==5)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing addition two element
  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(2), l);
  if (evalexp(mkopapp(isplus, l))==7)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  //testing multiplication and addition together
  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(2), l);
  l = cons(mkopapp(isplus, l),l);
  if (evalexp(mkopapp(ismult, l))==70)
  {
  	printf("Pass.\n");
  }
  else{
  	printf("Fail.\n");
  }
  
  
  return 0;
}
