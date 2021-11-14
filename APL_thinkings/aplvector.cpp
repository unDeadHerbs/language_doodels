#include "aplvector.hpp"
/**
 * If this node has no children.
 */
bool aplvector::isbase()const{
	return below.size()==0;
}

/**
 * Default constructor.
 */
aplvector::aplvector():val(0){
	if(DEBUG>5)std::cout<<"          apl default"<<std::endl;
}
/**
 * Value constructor.
 */
aplvector::aplvector(float v):val(v){
	if(DEBUG>5)std::cout<<"          apl float:"<<v<<std::endl;
}
/**
 * Value constructor.
 */
aplvector::aplvector(std::string s):val(stof(s)){
	if(DEBUG>5)std::cout<<"          apl string:"<<s<<std::endl;
	if(DEBUG>6)std::cout<<"            as float:"<<stof(s)<<std::endl;
}
/**
 * Copy constructor,
 */
aplvector::aplvector(const aplvector&n):below(n.below),val(n.val){
	if(DEBUG>5)std::cout<<"          apl copy"<<std::endl;
	if(DEBUG>6)std::cout<<"            val:"<<val<<std::endl;
}

/**
 * Prepends a value to the list of children.
 * If is currently a leaf, demodte self and then append on parent.
 */
void aplvector::join(float v){
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
void aplvector::join(aplvector v){
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
void aplvector::append(float v){
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
void aplvector::append(aplvector v){
	if(DEBUG>5)std::cout<<"          apl append apl"<<std::endl;
	if(isbase()){
		below.push_front(aplvector(val));
		val=0;
	}
	below.push_back(v);
}

//inplace arithmetic operators
aplvector aplvector::operator+=(const aplvector&rhs){
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
aplvector aplvector::operator-=(const aplvector&rhs){
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
aplvector aplvector::operator*=(const aplvector&rhs){
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
aplvector aplvector::operator/=(const aplvector&rhs){
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
aplvector aplvector::operator+(const aplvector&rhs)const{
	if(DEBUG>5)std::cout<<"          apl + apl"<<std::endl;
	return aplvector(*this)+=rhs;
}
aplvector aplvector::operator-(const aplvector&rhs)const{
	if(DEBUG>5)std::cout<<"          apl - apl"<<std::endl;
	return aplvector(*this)-=rhs;
}
//the negitive operator
aplvector aplvector::operator*(const aplvector&rhs)const{
	if(DEBUG>5)std::cout<<"          apl * apl"<<std::endl;
	return aplvector(*this)*=rhs;
}
aplvector aplvector::operator/(const aplvector&rhs)const{
	if(DEBUG>5)std::cout<<"          apl / apl"<<std::endl;
	return aplvector(*this)/=rhs;
}

//inplace int arithmetic integer operators
aplvector aplvector::operator+=(const float&rhs){
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
aplvector aplvector::operator*=(const float&rhs){
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
aplvector aplvector::operator/=(const float&rhs){
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
aplvector aplvector::operator-=(const float&rhs){
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
aplvector aplvector::inv(const int&t=1){
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
aplvector operator+(const aplvector&lhs,const int&rhs){
	if(DEBUG>5)std::cout<<"          apl + int:"<<rhs<<std::endl;
	return aplvector(lhs)+=rhs;
}
aplvector operator-(const aplvector&lhs,const int&rhs){
	if(DEBUG>5)std::cout<<"          apl - int:"<<rhs<<std::endl;
	return aplvector(lhs)-=rhs;
}
aplvector operator*(const aplvector&lhs,const int&rhs){
	if(DEBUG>5)std::cout<<"          apl * int:"<<rhs<<std::endl;
	return aplvector(lhs)*=rhs;
}
aplvector operator/(const aplvector&lhs,const int&rhs){
	if(DEBUG>5)std::cout<<"          apl / int:"<<rhs<<std::endl;
	return aplvector(lhs)/=rhs;
}
aplvector operator/(const int&lhs,const aplvector&rhs){
	if(DEBUG>5)std::cout<<"          apl / int:"<<lhs<<std::endl;
	return aplvector(rhs).inv(lhs);
}
//and the reverse operatos
aplvector operator+(const int&lhs,const aplvector&rhs){
	if(DEBUG>5)std::cout<<"          int + apl:"<<lhs<<std::endl;
	return rhs+lhs;
}
aplvector operator-(const int&lhs,const aplvector&rhs){
	if(DEBUG>5)std::cout<<"          int - apl:"<<lhs<<std::endl;
	return (rhs*-1)+lhs;
}
aplvector operator*(const int&lhs,const aplvector&rhs){
	if(DEBUG>5)std::cout<<"          int * apl:"<<lhs<<std::endl;
	return rhs*lhs;
}

aplvector& aplvector::operator[](int v){
	return below[v];
}

/**
 * The greatest depth of any node.
 */
int aplvector::depth()const{
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
void aplvector::print(){
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
void aplvector::display(std::ostream& out,std::string delim,std::string linefeed){
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
