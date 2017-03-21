#include <stdlib.h>

struct N {
  struct N *x;
  struct N *y;
  struct N *z;
  long data;
};

struct llist {
  struct N *data;
  struct llist *next;
};

struct ret {
  long result;
  struct llist *list;
};

long countLL(struct llist *l) {
  struct llist *t = l;
  long retVal = 0;
  while(t) {
    if (t->data) {
      retVal += t->data->data;
    };
    t = t->next;
  };
  return retVal;
};

void deallocateLL(struct llist *l) {
  struct llist *t;
  while (l) {
    t = l;
    l = l->next;
    free(t);
  };
};

int isInLL(struct N *p, struct llist *l) {
  struct llist *t = l;
  while (t) {
    if (t->data == p) return 1;
    else t = t->next;
  };
  return 0;
};

void addToLList(struct llist *l, struct N *p) {
  struct llist *r = malloc(sizeof(struct llist));
  r->next = NULL;
  struct llist *t = l;
  r->data = p;
  if (t) {
    while (t->next) {
      t = t->next;
    };
    t->next = r;
  }
  else t = r;
};

struct llist * unqNodes(struct llist *l, struct N *p) {
  if (l) {
    if (isInLL(p, l) == 0) {
      addToLList(l, p);
      l = unqNodes(l, p->x);
      l = unqNodes(l, p->y);
      l = unqNodes(l, p->z);
    };
  };
  return l;
};

void deallocate(struct N *p) {
  struct llist *t1 = malloc(sizeof(struct llist));
  t1->data = NULL;
  t1->next = NULL;
  struct llist *t2;
  t1 = unqNodes(t1, p);
  t2 = t1;
  while(t1) {
    free(t1->data);
    t1 = t1->next;
  };
  deallocateLL(t2);
};

long sum2(struct N *p) {
  long sumRet = 0;
  struct llist *l = malloc(sizeof(struct llist));
  l->data = NULL;
  l->next = NULL;
  l = unqNodes(l, p);
  sumRet = countLL(l);
  deallocateLL(l);
  return sumRet;
};

long sum(struct N *p) {
  long r;
  r = sum2(p);
  return r;
};
