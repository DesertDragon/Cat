using Views = vector<void(*)(void*, ostream&)>;

template<class C> Views& getViews(){ static Views v; return v; }

#define VIEW(v) static void out_##v(void* c, ostream& o)	\
{															\
	o << #v << ": " << ((Self*)c)->v;						\
}															\
inline static bool CAT2(_,__COUNTER__) = []{				\
	getViews<Self>().push_back(out_##v); return true;	\
}();

struct Viewable
{
	virtual void show(ostream& out){}
};

struct View
{
	//void show(struct Cat& cat);
	void show();
	//View(ostream& out): out(out) {}
	//View(ostream& out, Viewable* obj): out(out), obj(obj) {}
	template<class C> View(ostream& out, C* obj):
		out(out), views(getViews<C>()), obj(obj), objType(typeid(C).name()) {}
private:
	ostream& out;
	//Viewable* obj;
	Views& views;
	void* obj;
	const char* objType;
};