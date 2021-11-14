#include "lispNode.hpp"

lispNode::lispNode(){
	cdrp= nullptr;
}

lispNode::~lispNode(){
	if(cdrp!=nullptr)
		delete cdrp;
	if(list)
		delete carp;
}

bool lispNode::lastTerm(){
	return cdrp==nullptr;
}

lispNode *lispNode::cdr(){
	if(lastTerm())
		cdrp=new lispNode;
	return cdrp;
}

lispNode &lispNode::car(){
	list=true;
	value=false;
	return *carp;
}

lispNode &lispNode::carsym(){
	list=true;
	value=true;
	return *carp;
}

std::string &lispNode::sym(){
	list=false;
	value=false;
	return symbol;
}

std::string &lispNode::string(){
	list=false;
	value=true;
	return symbol;
}
