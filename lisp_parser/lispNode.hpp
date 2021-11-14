#include <string>

class lispNode{
	lispNode *carp,*cdrp;
	std::string symbol;
	bool list,value;
	//if list then car
	//if value then symbol is a string
	//else symbol is a symbol name
public:
	lispNode();
	virtual ~lispNode();
	bool lastTerm();
	lispNode *cdr();
	lispNode &car();
	lispNode &carsym();
	std::string &sym();
	std::string &string();
};
