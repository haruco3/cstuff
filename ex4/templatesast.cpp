using namespace std;
#include "templatesast.h"

template<typename V>
V find(string s, env<V> *p) {
	while(p) {
		if (p->var == s) return p->value;
		p = p->next;
	};
	//error
	return 0;
}

template<typename V>
V Let<V>::eval(env<V> *p) {
	env<V> t;
	env<V> *ll = &t;
	ll->var = this->bvar;
	ll->value = this->bexp->eval(p);
	ll->next = p;
	return this->body->eval(ll);
}

template<typename V>
V Constant<V>::eval(env<V> *p) {
	return this->c;
}

template<typename V>
V Var<V>::eval(env<V> *p) {
	return find(this->name, p);
}

template<typename V>
V OpApp<V>::eval(env<V> *p) {
	V ret = this->ops.unit;
	ExpList<V> *t = this->args;
	while(t) {
		ret = this->ops.binop(ret, t->head->eval(p));
		t = t->tail;
	}
	return ret;
}
