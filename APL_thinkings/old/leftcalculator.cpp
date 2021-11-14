/**
 * @file
 * @author  Murray Forydyce <undeadherbs@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program is a simple calculator that parses
 *  from right to left and is created as a stepping stone
 *  to making an APL calculator.
 */

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#define DEBUG 9

/**
 * This class is an impimentaiton of a binary parse tree.
 *
 *
 */
class parse{
private:
public:
	std::string op;
	parse *l;
	parse *r;
	parse():l(NULL),r(NULL){}
	/**
	 * If passed a string make that the only data element.
	 */
	explicit parse(std::string opr)
		:op(opr),l(NULL),r(NULL){
		if(DEBUG>5)std::cout<<"          string"<<std::endl;
	}
	/**
	 * If initilizsd with three elms make them left, oper, and right respectively.
	 *
	 * This also handels strings for the left and right parameter due to the first initializer.
	 */
	parse(parse lft,std::string opr,parse rit)
		:op(opr){
		if(DEBUG>5)std::cout<<"          lopr"<<std::endl;
		if(DEBUG>6)std::cout<<"            op:"<<op<<std::endl;
		if(DEBUG>6)std::cout<<"            lop:"<<lft.op<<std::endl;
		if(DEBUG>6)std::cout<<"            rop:"<<rit.op<<std::endl;
		l=new parse(lft);
		r=new parse(rit);
	}
	/**
	 * If initilizsd with three elms make them left, oper, and right respectively.
	 *
	 * This also handels strings for the left and right parameter due to the first initializer.
	 */
	parse(std::string opr,parse rit)
		:op(opr){
		if(DEBUG>5)std::cout<<"          lopr"<<std::endl;
		if(DEBUG>6)std::cout<<"            op:"<<op<<std::endl;
		//		if(DEBUG>6)std::cout<<"            lop:"<<lft.op<<std::endl;
		if(DEBUG>6)std::cout<<"            rop:"<<rit.op<<std::endl;
		l=0;
		r=new parse(rit);
	}
	/**
	 * Copy constructor.
	 */
	parse(const parse &p):op(p.op){
		if(DEBUG>5)std::cout<<"          copy"<<op<<std::endl;
		if(p.l!=NULL){
			if(DEBUG>6)std::cout<<"            l"<<std::endl;
			l=new parse(*p.l);
		}else{
			l=NULL;
		}
		if(p.r!=NULL){
			if(DEBUG>6)std::cout<<"            r"<<std::endl;
			r=new parse(*p.r);
		}else{
			r=NULL;
		}
	}
	/**
	 * Move constructor. (notably dose not move yet.)
	 */
	parse(parse&& p):op(p.op){
		if(DEBUG>5)std::cout<<"          move"<<std::endl;
		if(p.l!=NULL){
			l=new parse(*p.l);
		}else{
			l=NULL;
		}
		if(p.r!=NULL){
			r=new parse(*p.r);
		}else{
			r=NULL;
		}
	}
	~parse(){
		if(DEBUG>5)std::cout<<"          distruct"<<std::endl;
		delete l;
		delete r;
	}
	/**
	 * Used in case one needs to change the left parameter.
	 */
	void setl(parse tl){
		if(DEBUG>5)std::cout<<"    setl"<<std::endl;
		l=new parse(tl);
	}
	/**
	 * Used in case one needs to change the right parameter.
	 */
	void setr(parse tr){
		if(DEBUG>5)std::cout<<"    setr"<<std::endl;
		r=new parse(tr);
	}
};

/**
 * Dereferences a diadic operator string.
 *
 * @param l Left operand.
 * @param op The operator.
 * @param r Right operand.
 */
float exec(float l,std::string op,float r){
	if(DEBUG>0)std::cout<<"exec diadic"<<std::endl;
	if(op=="*"){
		if(DEBUG>2)std::cout<<"    *"<<std::endl;
		return l*r;
	}else if(op=="/"){
		if(DEBUG>2)std::cout<<"    /"<<std::endl;
		return l/r;
	}else if(op=="\\"){
		if(DEBUG>2)std::cout<<"    \\"<<std::endl;
		return r/l;
	}else if(op=="+"){
		if(DEBUG>2)std::cout<<"    +"<<std::endl;
		return l+r;
	}else if(op=="-"){
		if(DEBUG>2)std::cout<<"    -"<<std::endl;
		return l-r;
	}else /*if(op=="^")*/{
		//if(DEBUG>2)std::cout<<"    ^"<<std::endl;
		//return math.pow(l,r);
	}//else{
}

/**
 * Dereferences a monadic operator string.
 *
 * @param op The operator.
 * @param r Right operand.
 */
float exec(std::string op,float r){
	if(DEBUG>0)std::cout<<"exec monadic oper"<<std::endl;
	if(op=="-"){
		return -r;
	}
}

/**
 * Takes a parse tree and returns it's evaluation.
 *
 * @param p The parse tree to evaluate.
 */
float exec(parse p){
	if(DEBUG>0)std::cout<<"exec"<<p.op<<std::endl;
	if(p.l==NULL){
		if(p.r==NULL){
			if(DEBUG>2)std::cout<<"    val"<<std::endl;
			return stof(p.op);
		}else{
			if(DEBUG>2)std::cout<<"    right"<<std::endl;
			return exec(p.op,exec(*p.r));
		}
	}else{
		if(p.r==NULL){
			if(DEBUG>2)std::cout<<"    left"<<std::endl;
			// no return so that it reaches end of function
		}else{
			if(DEBUG>2)std::cout<<"    both"<<std::endl;
			return exec(exec(*p.l),p.op,exec(*p.r));
		}
	}
}

/**
 * This function retuns if a string is a known operator.
 */
bool oper(std::string o){
	if(o=="-"){
		return true;
	}
	if(o=="+"){
		return true;
	}
	if(o=="*"){
		return true;
	}
	if(o=="/"){
		return true;
	}
	if(o=="\\"){
		return true;
	}
	return false;
}

/**
 * Takes a string and parsees it (destuctivly) up to the next end of scope.
 *
 * @param exp The string that will be (distructivly) parsed.
 *
 * @return The parse tree of the expression passed,
 *           upto the first unmatched end of scope.
 */
parse evalp(std::string& exp){
	if(DEBUG>0)std::cout<<"evalp"<<std::endl;
	std::deque<parse> t;
	if(DEBUG>1)std::cout<<"  tokenise the string"<<std::endl;
	exp.erase(exp.begin(),
						std::find_if(exp.begin(),
												 exp.end(),
												 std::not1(std::ptr_fun<int, int>(std::isspace))));
	if(DEBUG>1)std::cout<<"  remove leading space"<<std::endl;
	if(DEBUG>1)std::cout<<"  "<<exp<<std::endl;
	while(exp.front()!=')'&&exp.size()){
		std::string tmp;
		//optionally insert a * if no preceding operator
		if(exp.front()=='('){
			if(DEBUG>2)std::cout<<"    found ("<<std::endl;
			exp.erase(0,1);
			t.push_back(evalp(exp));
			if(DEBUG>2)std::cout<<"    remove )"<<std::endl;
			exp.erase(0,1);
		}else{
			//change split to be more intelligent
			tmp=exp.substr(0,exp.find(' '));
			if(tmp!=exp){
				exp=exp.substr(exp.find(' ')+1);
				t.push_back(parse(tmp));
				if(DEBUG>2)std::cout<<"    push char"<<std::endl;
			}else{
				t.push_back(parse(exp));
				if(DEBUG>2)std::cout<<"    push rest"<<std::endl;
				exp="";
			}
		}
		if(DEBUG>2)std::cout<<"    "<<exp<<" t:"<<t.size()<<" tmp:"<<tmp<<std::endl;
		exp.erase(exp.begin(),
							std::find_if(exp.begin(),
													 exp.end(),
													 std::not1(std::ptr_fun<int, int>(std::isspace))));
		if(DEBUG>1)std::cout<<"  remove leading space"<<std::endl;
		if(DEBUG>1)std::cout<<"  "<<exp<<std::endl;
	}
	{
		if(DEBUG>2)std::cout<<"    reverse for easier parsing"<<std::endl;
		std::deque<parse> f;
		while(t.size()){
			f.push_front(t.front());
			t.pop_front();
		}
		while(f.size()){
			t.push_back(f.front());
			f.pop_front();
		}
	}
	if(DEBUG>1)std::cout<<"  right to left"<<std::endl;
	while(t.size()>3){
		if(DEBUG>2)std::cout<<"    read to the left untill a opperator is satisfyed"<<std::endl;
		if(DEBUG>3)std::cout<<"      check next"<<std::endl;
		if(oper(t[2].op)){
			if(DEBUG>3)std::cout<<"      monadic operator"<<std::endl;
			parse tmp(t[1].op,t[0]);
			if(DEBUG>3)std::cout<<"      pop"<<std::endl;
			t.pop_front();
			t.pop_front();
			t.push_front(tmp);
		}else{
			if(DEBUG>3)std::cout<<"      diadic operator"<<std::endl;
			parse tmp(t[2],t[1].op,t[0]);
			t.pop_front();
			t.pop_front();
			t.pop_front();
			t.push_front(tmp);
		}
	}
	if(t.size()==3){
		if(DEBUG>2)std::cout<<"  make last diadic parse t:"<<t.size()<<std::endl;
		parse tmp(t[2],t[1].op,t[0]);
		if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;
		return tmp;
	}
	if(t.size()==2){
		if(DEBUG>2)std::cout<<"  make last monadic parse t:"<<t.size()<<std::endl;
		parse tmp(t[1].op,t[0]);
		if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;
		return tmp;
	}
	if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;
	return t[0];
}

/**
 * This function takes an expression and reruns it's evaluation.
 */
float eval(std::string exp){
	if(DEBUG>0)std::cout<<"eval"<<std::endl;
	return exec(evalp(exp));
}

int main(int argc,char*argv[]){
	if(DEBUG>0)std::cout<<"main"<<std::endl;
	std::string exp;
	std::cout<<":";
	std::getline(std::cin,exp);
	std::cout<<eval(exp)<<std::endl;
	if(DEBUG>1)std::cout<<"done"<<std::endl;
	return 0;
}
