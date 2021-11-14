#include "parse.hpp"
/**
 * Default constructor.
 *
 * Set both l and r to null, allow for default construction of op and val.
 */
parse::parse():l(nullptr),r(nullptr){}
/**
 * If passed a string make that the only data element.
 */
parse::parse(std::string opr)
	:op(opr),l(nullptr),r(nullptr){
	if(DEBUG>5)std::cout<<"          parse string"<<std::endl;
}
/**
 * If passed a vector make that the Value.
 */
parse::parse(const aplvector& v):l(nullptr),r(nullptr),val(v){
	if(DEBUG>5)std::cout<<"          parse apl"<<std::endl;
}
/**
 * If initilizsd with three elms make them left, oper, and right respectively.
 *
 * This also handels strings for the left and right parameter due to the first initializer.
 */
parse::parse(parse lft,std::string opr,parse rit)
	:op(opr){
	if(DEBUG>5)std::cout<<"          parse lopr"<<std::endl;
	if(DEBUG>6)std::cout<<"            op:"<<op<<std::endl;
	if(DEBUG>6)std::cout<<"            lop:"<<lft.op<<std::endl;
	if(DEBUG>6)std::cout<<"            rop:"<<rit.op<<std::endl;
	l=new parse(lft);
	r=new parse(rit);
}
/**
 * If initilizsd with two elms make them oper, and right respectively (APL convention).
 *
 * This also handels strings for the right parameter due to the first initializer.
 */
parse::parse(std::string opr,parse rit)
	:op(opr),l(nullptr){
	if(DEBUG>5)std::cout<<"          parse opr"<<std::endl;
	if(DEBUG>6)std::cout<<"            op:"<<op<<std::endl;
	if(DEBUG>6)std::cout<<"            rop:"<<rit.op<<std::endl;
	r=new parse(rit);
}
/**
 * Copy constructor.
 */
parse::parse(const parse &p):op(p.op),val(p.val){
	if(op==""){
		if(DEBUG>5){std::cout<<"          parse copy:";val.print();std::cout<<std::endl;}
		l=nullptr;
		r=nullptr;
	}else{
		if(DEBUG>5)std::cout<<"          parse copy:"<<op<<std::endl;
		if(p.l!=nullptr){
			if(DEBUG>6)std::cout<<"            l"<<std::endl;
			l=new parse(*p.l);
		}else{
			l=nullptr;
		}
		if(p.r!=nullptr){
			if(DEBUG>6)std::cout<<"            r"<<std::endl;
			r=new parse(*p.r);
		}else{
			r=nullptr;
		}
	}
}
/**
 * Move constructor. (notably dose not move yet.)
 */
parse::parse(parse&& p):op(p.op),val(p.val){
	if(DEBUG>5)std::cout<<"          parse move:"<<op<<std::endl;
	if(p.l!=nullptr){
		if(DEBUG>6)std::cout<<"            l"<<std::endl;
		l=new parse(*p.l);
	}else{
		l=nullptr;
	}
	if(p.r!=nullptr){
		if(DEBUG>6)std::cout<<"            r"<<std::endl;
		r=new parse(*p.r);
	}else{
		r=nullptr;
	}
	if(DEBUG>7)std::cout<<"          move done"<<std::endl;
}

/**
 * Delete l and r pointers and defualy destruct v and opx.
 */
parse::~parse(){
	if(DEBUG>5)std::cout<<"          parse distruct"<<std::endl;
	if(op==""){
		if(DEBUG>6){std::cout<<"          v:";val.print();std::cout<<std::endl;}
	}else{
		if(DEBUG>6)std::cout<<"          op:"<<op<<std::endl;
	}
	if(l!=nullptr){
		if(DEBUG>6){std::cout<<"          l";l->print();std::cout<<std::endl;}
		delete l;
	}
	if(r!=nullptr){
		if(DEBUG>6){std::cout<<"          r";r->print();std::cout<<std::endl;}
		delete r;
	}
}

/**
 * Used in case one needs to change the left parameter.
 */
void parse::setl(parse tl){
	if(DEBUG>5)std::cout<<"    parse setl"<<std::endl;
	l=new parse(tl);
}
/**
 * Used in case one needs to change the right parameter.
 */
void parse::setr(parse tr){
	if(DEBUG>5)std::cout<<"    parse setr"<<std::endl;
	r=new parse(tr);
}
/**
 * Used in case one needs to change the apl value.
 */
void parse::setval(aplvector v){
	if(DEBUG>5)std::cout<<"          parse setv"<<std::endl;
	val=v;
}

//#if DEBUG>0
void parse::print(){
	if(op==""){
		val.print();
	}else{
		std::cout<<"p(";
		if(l!=nullptr){
			l->print();
		}else{
			std::cout<<"N";
		}
		std::cout<<" "<<op<<" ";
		if(r!=nullptr){
			r->print();
		}else{
			std::cout<<"N";
		}
		std::cout<<")";
	}
}
//#endif
