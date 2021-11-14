/**
 * @file
 * @author  Murray Forydyce <undeadherbs@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program is a simple calculator that parses vectors
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

#include "defines.cpp"
#include "aplvector.hpp"
#include "parse.hpp"

/**
 * Dereferences a diadic operator string.
 *
 * @param l Left operand.
 * @param op The operator.
 * @param r Right operand.
 */
aplvector exec(aplvector l,std::string op,aplvector r){
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
aplvector exec(std::string op,aplvector r){
	if(DEBUG>0)std::cout<<"exec monadic oper"<<std::endl;
	if(op=="-"){
		return 0-r;
	}else if(op=="+"){
		return r;
	}
}

/**
 * Takes a parse tree and returns it's evaluation.
 *
 * @param p The parse tree to evaluate.
 */
aplvector exec(parse p){
	if(DEBUG>0)std::cout<<"exec"<<p.op<<std::endl;
	if(DEBUG>3){std::cout<<"  p:";p.print();std::cout<<std::endl;}
	if(p.l==nullptr){
		if(p.r==nullptr){
			if(DEBUG>2)std::cout<<"    val"<<std::endl;
			return p.val;
		}else{
			if(DEBUG>2)std::cout<<"    right"<<std::endl;
			return exec(p.op,exec(*p.r));
		}
	}else{
		if(p.r==nullptr){
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

//prototyped for recursive parsing
parse evalp(std::string& exp);

/**
 * Distructivly tokenize the passed expression.
 *
 * @param exp The string that will be (distructivly) parsed.
 *
 * @return The tokenized list from the expression passed,
 *           upto the first unmatched end of scope with sub scopes parsed.
 */
std::deque<parse> tokenize(std::string& exp){
	if(DEBUG>1)std::cout<<"  tokenize the string"<<std::endl;
	std::deque<parse> t;
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
		if(DEBUG>1)std::cout<<"  exp:"<<exp<<std::endl;
	}
	return t;
}

/**
 * Vectorize the passed token list.
 *
 * @param exp The string that will be (distructivly) parsed.
 *
 * @return The tokenized list from the expression passed,
 *           upto the first unmatched end of scope with sub-scopes parsed.
 */
std::deque<parse> vectorize(std::deque<parse> f){
	if(DEBUG>2)std::cout<<"vectorize"<<std::endl;
	std::deque<parse> t;

	if(DEBUG>5){std::cout<<"    p:";for(auto&s:f){s.print();std::cout<<" ";}std::cout<<std::endl;}

	bool lstwop=true;//as to prevent attempt to append vector
	while(f.size()){
		if(DEBUG>3)std::cout<<"  begin val"<<std::endl;
		if(!oper(f.front().op)){
			if(!lstwop){
				t.back().val.append(f.front().op);//merge into vector
			}else{
				t.push_back(parse(aplvector(f.front().op)));//push as new vector
			}
			lstwop=false;
		}else{
			t.push_back(f.front());
			lstwop=true;
		}
		if(DEBUG>5)std::cout<<"  pop"<<std::endl;
		f.pop_front();
		if(DEBUG>5){std::cout<<"    f: ";for(auto&s:f){s.print();std::cout<<" ";}std::cout<<std::endl;}
		if(DEBUG>5){std::cout<<"    t: ";for(auto&s:t){s.print();std::cout<<" ";}std::cout<<std::endl;}
		if(DEBUG>5)std::cout<<"  next val"<<std::endl;
	}

	return t;
}

/**
 * Reverse the order of the passed token list for APL.
 */
std::deque<parse> righttoleft(std::deque<parse> f){
	std::deque<parse> t;

	if(DEBUG>2)std::cout<<"Reverse for rtl parsing"<<std::endl;
	while(f.size()){
		if(DEBUG>5){std::cout<<"  f:";for(auto&s:f){s.print();std::cout<<" ";}std::cout<<std::endl;}
		if(DEBUG>5){std::cout<<"  t:";for(auto&s:t){s.print();std::cout<<" ";}std::cout<<std::endl;}
		t.push_front(f.front());
		if(DEBUG>6)std::cout<<"    poped"<<std::endl;
		f.pop_front();
	}
	return t;
}

/**
 * Forms the apropriate parse tree for a given set of tokens
 */
parse parze(std::deque<parse> t){
	if(DEBUG>2)std::cout<<"parse tokens s:"<<t.size()<<std::endl;

	if(DEBUG>5){std::cout<<"      p: ";for(auto&s:t){s.print();std::cout<<" ";}std::cout<<std::endl;}
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
	if(DEBUG>7)std::cout<<"  one parse left"<<std::endl;

	if(t.size()==3){
		if(DEBUG>2)std::cout<<"  make last diadic parse ts:"<<t.size()<<std::endl;
		parse tmp(t[2],t[1].op,t[0]);
		if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;
		return tmp;
	}
	if(t.size()==2){
		if(DEBUG>2)std::cout<<"  make last monadic parse ts:"<<t.size()<<std::endl;
		parse tmp(t[1].op,t[0]);
		if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;
		return tmp;
	}
	if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;


	if(t.size()>1){
		return parze(t);
	}else{
		return t.front();
	}
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

	std::deque<parse> t=tokenize(exp);
	t=vectorize(t);
	t=righttoleft(t);
	return parze(t);
}

/**
 * This function takes an expression and reruns it's evaluation.
 */
aplvector eval(std::string exp){
	if(DEBUG>0)std::cout<<"eval"<<std::endl;
	return exec(evalp(exp));
}

int main(int argc,char*argv[]){
	if(DEBUG>0)std::cout<<"main"<<std::endl;
	std::string exp;
	std::cout<<":";
	std::getline(std::cin,exp);
	while(exp!="q"&&DEBUG==0){
		eval(exp).display(std::cout);
		std::cout<<":";
		std::getline(std::cin,exp);
	}
	if(DEBUG)eval(exp).display(std::cout);
	if(DEBUG>1)std::cout<<"done"<<std::endl;
	return 0;
}
