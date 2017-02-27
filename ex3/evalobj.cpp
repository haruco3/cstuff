#include <string>
using namespace std;
#include "evalobj.h"

int find(string s, env *v) {
	while(v) {
		if (v->var == s) return v->value;
		v = v->next;
	};
	//error
	return 0;
};

int Constant::eval(env *v) {
	return this->n;
};

int Var::eval(env *v) {
	return find(this->name, v);
};

int Let::eval(env *v) {
	env vn;
	env *ll = &vn;
	ll->var = this->bvar;
	ll->value = bexp->eval(v);
	ll->next = v;
	return body->eval(ll);
};

int OpApp::eval(env *v) {
	int ret;
	ExpList *t = this->args;
	switch(this->op) {
		case plusop:
			ret = 0;
			while(t) {
				ret += t->head->eval(v);
				t = t->tail;
			};
		case timesop:
			if (t) {
				ret = t->head->eval(v);
				t = t->tail;
			};
			while(t) {
				ret *= t->head->eval(v);
				t = t->tail;
			};
	};
	return ret;
};
