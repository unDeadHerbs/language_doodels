/**
 * This class is an impimentaiton of a binary parse tree.
 */

#ifndef _APL_PARSE
#define _APL_PARSE 1
#include "defines.cpp"
#include "aplvector.hpp"
#include <iostream>
#include <string>

class parse{
private:
public:
	std::string op;
	parse *l;
	parse *r;
	aplvector val;
	parse();
	explicit parse(std::string);
	parse(const aplvector&);
	parse(parse,std::string,parse);
	parse(std::string,parse);
	parse(const parse &);
	parse(parse&&);
	~parse();
	void setl(parse tl);
	void setr(parse tr);
	void setval(aplvector v);
	void print();
};
#endif
