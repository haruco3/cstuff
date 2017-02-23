#include <stdlib.h>
#include <string.h>

#include "evalexp.h"

struct pair {
	char c[8];
	int n;
};

struct env {
	struct pair *x;
	struct env *xs;
};

void deallocate(struct env *w) {
	struct env *t;
	while(w) {
		t = w;
		w = w->xs;
		if (t->x) free(t->x);
		free(t);
	};
};

//Find variable in env
int find(char *c, struct env *v) {
	struct env *t = v;
	while(t->x) {
		if (strcmp(t->x->c, c) == 0) return t->x->n;
		t = t->xs;
	};
	//not found
	return 0;
};

void deallocateHayoL(struct explist *e) {
	while(e) {
		struct explist *t = e;
		e = e->tail;
		free(t->head);
		free(t);
	};
};

//Optional function for deallocating exp structures
void deallocateHayo(struct exp *e) {
	switch(e->tag) {
		case islet:
			deallocateHayo(e->bexp);
			deallocateHayo(e->body);
			break;
		case isopapp:
			deallocateHayoL(e->exps);
			break;
		default:
			break;
	};
	free(e);
};

int evalexpenv(struct exp *e, struct env *v) {
	switch(e->tag) {
		case islet:{
			struct env *ll = malloc(sizeof(struct env));
			struct pair *t = malloc(sizeof(struct pair));
			strcpy(t->c, e->bvar);
			t->n = evalexpenv(e->bexp, v);
			ll->x = t;
			ll->xs = ll;
			int ret = evalexpenv(e->body, ll);
			free(t);
			free(ll);
			return ret;
		};
		case isconstant:
			return e->constant;
		case isvar:
			return find(e->var, v);
		case isopapp:
			switch(e->op) {
				case isplus:{
					int ret = 0;
					struct explist *t;
					t = e->exps;
					while(t) {
						ret += evalexpenv(t->head, v);
						t = t->tail;
					};
					return ret;
				};
				case(ismult):{
					struct explist *t;
					t = e->exps;
					// Check if list is empty
					if (!t || !t->head) return 1;
					int ret = evalexpenv(t->head, v);
					t = t->tail;
					while(t) {
						ret = ret * evalexpenv(t->head, v);
						t = t->tail;
					};
					return ret;
				};
			};
	};
};

int evalexp(struct exp *e) {
		struct env *ll = malloc(sizeof(struct env));
		ll->x = NULL;
		ll->xs = NULL;
		int ret = evalexpenv(e, ll);
		free(ll);
		deallocateHayo(e);
		return ret;
};
