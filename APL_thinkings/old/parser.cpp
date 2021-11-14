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

#define DEBUG 0
class aplenv{
private:
	/**
	 * APL vector container.
	 *
	 * This class describes a tree container for floats.
	 * There is no coded limitation on the number of nodes on any given level.
	 * Element wise operators are also defined.
	 */
	class aplvector{
	private:
	public:
		float val;
		std::deque<aplvector> below;

		/**
		 * If this node has no children.
		 */
		bool isbase()const{return below.size()==0;}

		/**
		 * Default constructor.
		 */
		aplvector():val(0){
			if(DEBUG>5)std::cout<<"          apl default"<<std::endl;
		}
		/**
		 * Value constructor.
		 */
		aplvector(float v):val(v){
			if(DEBUG>5)std::cout<<"          apl float:"<<v<<std::endl;
		}
		/**
		 * Value constructor.
		 */
		aplvector(std::string s):val(stof(s)){
			if(DEBUG>5)std::cout<<"          apl string:"<<s<<std::endl;
			if(DEBUG>6)std::cout<<"            as float:"<<stof(s)<<std::endl;
		}
		/**
		 * Copy constructor,
		 */
		aplvector(const aplvector&n):val(n.val),below(n.below){
			if(DEBUG>5)std::cout<<"          apl copy"<<std::endl;
			if(DEBUG>6)std::cout<<"            val:"<<val<<std::endl;
		}

		/**
		 * Prepends a value to the list of children.
		 * If is currently a leaf, demodte self and then append on parent.
		 */
		void join(float v){
			if(DEBUG>5)std::cout<<"          apl join float:"<<v<<std::endl;
			if(isbase()){
				below.push_front(aplvector(val));
				val=0;
			}
			below.push_front(v);
		}
		/**
		 * Prepends a value to the list of children.
		 * If is currently a leaf, demodte self and then append on parent.
		 */
		void join(aplvector v){
			if(DEBUG>5)std::cout<<"          apl join apl"<<std::endl;
			if(isbase()){
				below.push_front(aplvector(val));
				val=0;
			}
			below.push_front(v);
		}
		/**
		 * Appends a value to the list of children.
		 * If is currently a leaf, demodte self and then append on parent.
		 */
		void append(float v){
			if(DEBUG>5)std::cout<<"          apl append float:"<<v<<std::endl;
			if(isbase()){
				below.push_front(aplvector(val));
				val=0;
			}
			below.push_back(v);
		}
		/**
		 * Appends a value to the list of children.
		 * If is currently a leaf, demodte self and then append on parent.
		 */
		void append(aplvector v){
			if(DEBUG>5)std::cout<<"          apl append apl"<<std::endl;
			if(isbase()){
				below.push_front(aplvector(val));
				val=0;
			}
			below.push_back(v);
		}

		//inplace arithmetic operators
		aplvector operator+=(const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          apl +=apl"<<std::endl;
			if(isbase()){
				val+=rhs.val;
			}else{
				for(unsigned int i=0;i<below.size();++i){
					below[i]+=rhs.below[i];
				}
			}
			return *this;
		}
		aplvector operator-=(const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          apl -= apl"<<std::endl;
			if(isbase()){
				val-=rhs.val;
			}else{
				for(unsigned int i=0;i<below.size();++i){
					below[i]-=rhs.below[i];
				}
			}
			return *this;
		}
		aplvector operator*=(const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          apl *= apl"<<std::endl;
			if(isbase()){
				val*=rhs.val;
			}else{
				for(unsigned int i=0;i<below.size();++i){
					below[i]*=rhs.below[i];
				}
			}
			return *this;
		}
		aplvector operator/=(const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          apl /= apl"<<std::endl;
			if(isbase()){
				val/=rhs.val;
			}else{
				for(unsigned int i=0;i<below.size();++i){
					below[i]/=rhs.below[i];
				}
			}
			return *this;
		}

		//arithmetic operators
		aplvector operator+(const aplvector&rhs)const{
			if(DEBUG>5)std::cout<<"          apl + apl"<<std::endl;
			return aplvector(*this)+=rhs;
		}
		aplvector operator-(const aplvector&rhs)const{
			if(DEBUG>5)std::cout<<"          apl - apl"<<std::endl;
			return aplvector(*this)-=rhs;
		}
		//the negitive operator
		aplvector operator*(const aplvector&rhs)const{
			if(DEBUG>5)std::cout<<"          apl * apl"<<std::endl;
			return aplvector(*this)*=rhs;
		}
		aplvector operator/(const aplvector&rhs)const{
			if(DEBUG>5)std::cout<<"          apl / apl"<<std::endl;
			return aplvector(*this)/=rhs;
		}

		//inplace int arithmetic integer operators
		aplvector operator+=(const int&rhs){
			if(DEBUG>5)std::cout<<"          apl += float"<<rhs<<std::endl;
			if(isbase()){
				val+=rhs;
			}else{
				for(aplvector&s:below){
					s+=rhs;
				}
			}
			return *this;
		}
		aplvector operator*=(const int&rhs){
			if(DEBUG>5)std::cout<<"          apl *= float"<<rhs<<std::endl;
			if(isbase()){
				val*=rhs;
			}else{
				for(aplvector&s:below){
					s+=rhs;
				}
			}
			return *this;
		}
		aplvector operator/=(const int&rhs){
			if(DEBUG>5)std::cout<<"          apl /= float"<<rhs<<std::endl;
			if(isbase()){
				val/=rhs;
			}else{
				for(aplvector&s:below){
					s+=rhs;
				}
			}
			return *this;
		}
		aplvector operator-=(const int&rhs){
			if(DEBUG>5)std::cout<<"          apl -= float"<<rhs<<std::endl;
			if(isbase()){
				val-=rhs;
			}else{
				for(aplvector&s:below){
					s+=rhs;
				}
			}
			return *this;
		}
		aplvector inv(const int&t=1){
			if(DEBUG>5)std::cout<<"          apl \\ int:"<<t<<std::endl;
			if(isbase()){
				val=t/val;
			}else{
				for(auto&s:below){
					s.inv(t);
				}
			}
			return *this;
		}

		//arithmetic integer operators
		friend aplvector operator+(const aplvector&lhs,const int&rhs){
			if(DEBUG>5)std::cout<<"          apl + int:"<<rhs<<std::endl;
			return aplvector(lhs)+=rhs;
		}
		friend aplvector operator-(const aplvector&lhs,const int&rhs){
			if(DEBUG>5)std::cout<<"          apl - int:"<<rhs<<std::endl;
			return aplvector(lhs)-=rhs;
		}
		friend aplvector operator*(const aplvector&lhs,const int&rhs){
			if(DEBUG>5)std::cout<<"          apl * int:"<<rhs<<std::endl;
			return aplvector(lhs)*=rhs;
		}
		friend aplvector operator/(const aplvector&lhs,const int&rhs){
			if(DEBUG>5)std::cout<<"          apl / int:"<<rhs<<std::endl;
			return aplvector(lhs)/=rhs;
		}
		friend aplvector operator/(const int&lhs,const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          apl / int:"<<lhs<<std::endl;
			return aplvector(rhs).inv(lhs);
		}
		//and the reverse operatos
		friend aplvector operator+(const int&lhs,const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          int + apl:"<<lhs<<std::endl;
			return rhs+lhs;
		}
		friend aplvector operator-(const int&lhs,const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          int - apl:"<<lhs<<std::endl;
			return (rhs*-1)+lhs;
		}
		friend aplvector operator*(const int&lhs,const aplvector&rhs){
			if(DEBUG>5)std::cout<<"          int * apl:"<<lhs<<std::endl;
			return rhs*lhs;
		}

		aplvector& operator[](int v){
			return below[v];
		}

		/**
		 * The greatest depth of any node.
		 */
		int depth()const{
			int d=0;
			for(auto&s:below){
				int t=s.depth();
				if(t>d){
					d=t;
				}
			}
			return ++d;
		}

		//#if DEBUG>0
		void print(){
			if(isbase()){
				std::cout<<"v"<<val;
			}else{
				std::cout<<"v(";
				for(auto&s:below){
					s.print();
				}
				std::cout<<")";
			}
		}
		//#endif

		/**
		 * Pushs the standard display of *this* onto stream *out*.
		 */
		void display(std::ostream& out,std::string delim=" ",std::string linefeed="\n"){
			int d=depth()-1;
			if(DEBUG>5)std::cout<<"          apl display d:"<<d<<std::endl;
			if(DEBUG>6){std::cout<<"          v: ";print();std::cout<<std::endl;}
			if(d==0){
				out<<val<<linefeed;
			}else if(d==1){
				for(auto&s:below){
					out<<s.val<<delim;
				}
				out<<linefeed;
			}else if(d==2){
				for(auto&s:below){
					for(auto&b:s.below){
						out<<b.val<<delim;
					}
					out<<linefeed;
				}
			}else if(d==3){
				//list of squares
			}else if(d==4){
				//square of squares
			}
		}
	};

	/**
	 * This class is an impimentaiton of a binary parsenode tree.
	 */
	class parsenode{
	private:
	public:
		std::string op;
		parsenode *l;
		parsenode *r;
		aplvector val;

		/**
		 * Default constructor.
		 *
		 * Set both l and r to null, allow for default construction of op and val.
		 */
		parsenode():l(nullptr),r(nullptr){}
		/**
		 * If passed a string make that the only data element.
		 */
		explicit parsenode(std::string opr)
			:op(opr),l(nullptr),r(nullptr){
			if(DEBUG>5)std::cout<<"          parsenode string"<<std::endl;
		}
		/**
		 * If passed a vector make that the Value.
		 */
		parsenode(const aplvector& v):l(nullptr),r(nullptr),val(v){
			if(DEBUG>5)std::cout<<"          parsenode apl"<<std::endl;
		}
		/**
		 * If initilizsd with three elms make them left, oper, and right respectively.
		 *
		 * This also handels strings for the left and right parameter due to the first initializer.
		 */
		parsenode(parsenode lft,std::string opr,parsenode rit)
			:op(opr){
			if(DEBUG>5)std::cout<<"          parsenode lopr"<<std::endl;
			if(DEBUG>6)std::cout<<"            op:"<<op<<std::endl;
			if(DEBUG>6)std::cout<<"            lop:"<<lft.op<<std::endl;
			if(DEBUG>6)std::cout<<"            rop:"<<rit.op<<std::endl;
			l=new parsenode(lft);
			r=new parsenode(rit);
		}
		/**
		 * If initilizsd with two elms make them oper, and right respectively (APL convention).
		 *
		 * This also handels strings for the right parameter due to the first initializer.
		 */
		parsenode(std::string opr,parsenode rit)
			:op(opr),l(nullptr){
			if(DEBUG>5)std::cout<<"          parsenode opr"<<std::endl;
			if(DEBUG>6)std::cout<<"            op:"<<op<<std::endl;
			if(DEBUG>6)std::cout<<"            rop:"<<rit.op<<std::endl;
			r=new parsenode(rit);
		}
		/**
		 * Copy constructor.
		 */
		parsenode(const parsenode &p):op(p.op),val(p.val){
			if(op==""){
				if(DEBUG>5){std::cout<<"          parsenode copy:";val.print();std::cout<<std::endl;}
				l=nullptr;
				r=nullptr;
			}else{
				if(DEBUG>5)std::cout<<"          parsenode copy:"<<op<<std::endl;
				if(p.l!=nullptr){
					if(DEBUG>6)std::cout<<"            l"<<std::endl;
					l=new parsenode(*p.l);
				}else{
					l=nullptr;
				}
				if(p.r!=nullptr){
					if(DEBUG>6)std::cout<<"            r"<<std::endl;
					r=new parsenode(*p.r);
				}else{
					r=nullptr;
				}
			}
		}
		/**
		 * Move constructor. (notably dose not move yet.)
		 */
		parsenode(parsenode&& p):op(p.op),val(p.val){
			if(DEBUG>5)std::cout<<"          parsenode move:"<<op<<std::endl;
			if(p.l!=nullptr){
				if(DEBUG>6)std::cout<<"            l"<<std::endl;
				l=new parsenode(*p.l);
			}else{
				l=nullptr;
			}
			if(p.r!=nullptr){
				if(DEBUG>6)std::cout<<"            r"<<std::endl;
				r=new parsenode(*p.r);
			}else{
				r=nullptr;
			}
			if(DEBUG>7)std::cout<<"          move done"<<std::endl;
		}

		/**
		 * Delete l and r pointers and defualy destruct v and opx.
		 */
		~parsenode(){
			if(DEBUG>5)std::cout<<"          parsenode distruct"<<std::endl;
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
		void setl(parsenode tl){
			if(DEBUG>5)std::cout<<"    parsenode setl"<<std::endl;
			l=new parsenode(tl);
		}
		/**
		 * Used in case one needs to change the right parameter.
		 */
		void setr(parsenode tr){
			if(DEBUG>5)std::cout<<"    parsenode setr"<<std::endl;
			r=new parsenode(tr);
		}
		/**
		 * Used in case one needs to change the apl value.
		 */
		void setval(aplvector v){
			if(DEBUG>5)std::cout<<"          parsenode setv"<<std::endl;
			val=v;
		}

		//#if DEBUG>0
		void print(){
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
	} root;

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
	 * Takes a parsenode tree and returns it's evaluation.
	 *
	 * @param p The parsenode tree to evaluate.
	 */
	aplvector exec(parsenode p){
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
	//parsenode evalp(std::string& exp);
	//no longer needed as in a class

	/**
	 * Distructivly tokenize the passed expression.
	 *
	 * @param exp The string that will be (distructivly) parsenoded.
	 *
	 * @return The tokenized list from the expression passed,
	 *           upto the first unmatched end of scope with sub scopes parsenoded.
	 */
	std::deque<parsenode> tokenize(std::string& exp){
		if(DEBUG>1)std::cout<<"  tokenize the string"<<std::endl;
		std::deque<parsenode> t;
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
					t.push_back(parsenode(tmp));
					if(DEBUG>2)std::cout<<"    push char"<<std::endl;
				}else{
					t.push_back(parsenode(exp));
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
	 * @param exp The string that will be (distructivly) parsenoded.
	 *
	 * @return The tokenized list from the expression passed,
	 *           upto the first unmatched end of scope with sub-scopes parsenoded.
	 */
	std::deque<parsenode> vectorize(std::deque<parsenode> f){
		if(DEBUG>2)std::cout<<"vectorize"<<std::endl;
		std::deque<parsenode> t;

		if(DEBUG>5){std::cout<<"    p:";for(auto&s:f){s.print();std::cout<<" ";}std::cout<<std::endl;}

		bool lstwop=true;//as to prevent attempt to append vector
		while(f.size()){
			if(DEBUG>3)std::cout<<"  begin val"<<std::endl;
			if(!oper(f.front().op)){
				if(!lstwop){
					t.back().val.append(f.front().op);//merge into vector
				}else{
					t.push_back(parsenode(aplvector(f.front().op)));//push as new vector
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
	std::deque<parsenode> righttoleft(std::deque<parsenode> f){
		std::deque<parsenode> t;

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
	 * Forms the apropriate parsenode tree for a given set of tokens
	 */
	parsenode parze(std::deque<parsenode> t){
		if(DEBUG>2)std::cout<<"parsenode tokens s:"<<t.size()<<std::endl;

		if(DEBUG>5){std::cout<<"      p: ";for(auto&s:t){s.print();std::cout<<" ";}std::cout<<std::endl;}
		while(t.size()>3){
			if(DEBUG>2)std::cout<<"    read to the left untill a opperator is satisfyed"<<std::endl;
			if(DEBUG>3)std::cout<<"      check next"<<std::endl;
			if(oper(t[2].op)){
				if(DEBUG>3)std::cout<<"      monadic operator"<<std::endl;
				parsenode tmp(t[1].op,t[0]);
				if(DEBUG>3)std::cout<<"      pop"<<std::endl;
				t.pop_front();
				t.pop_front();
				t.push_front(tmp);
			}else{
				if(DEBUG>3)std::cout<<"      diadic operator"<<std::endl;
				parsenode tmp(t[2],t[1].op,t[0]);
				t.pop_front();
				t.pop_front();
				t.pop_front();
				t.push_front(tmp);
			}
		}
		if(DEBUG>7)std::cout<<"  one parsenode left"<<std::endl;

		if(t.size()==3){
			if(DEBUG>2)std::cout<<"  make last diadic parsenode ts:"<<t.size()<<std::endl;
			parsenode tmp(t[2],t[1].op,t[0]);
			if(DEBUG>1)std::cout<<"  return evalp"<<std::endl;
			return tmp;
		}
		if(t.size()==2){
			if(DEBUG>2)std::cout<<"  make last monadic parsenode ts:"<<t.size()<<std::endl;
			parsenode tmp(t[1].op,t[0]);
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
	 * Takes a string and parsenodees it (destuctivly) up to the next end of scope.
	 *
	 * @param exp The string that will be (distructivly) parsenoded.
	 *
	 * @return The parsenode tree of the expression passed,
	 *           upto the first unmatched end of scope.
	 */
	parsenode evalp(std::string& exp){
		if(DEBUG>0)std::cout<<"evalp"<<std::endl;

		std::deque<parsenode> t=tokenize(exp);
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
public:
	aplenv(){}
};

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
