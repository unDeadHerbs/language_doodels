#include "lispNode.hpp"
#include <string>
//#include <algorithm>
//#include <functional>


#define DEBUG 1
#define nom(x) erase(0,x)
#if DEBUG==0
 #define eat(s,x); s.nom(sizeof(x)-1);//the -1 is to remove the '\0' at the end of the string
#else
 #include <cassert>
 #define eat(s,x); {assert(s.find(x)==0);s.nom(sizeof(x)-1);}
#endif
#define append(s,n) append(s,0,n)

lispNode parse(std::string& raw){
	while(raw.front()==' '){
		//time to go get that debug module you've been making to stack trace
		eat(raw," ");
	}
	lispNode ret,*cur=&ret;
	while(raw.front()!=')'&&raw.size()){
		switch(raw[0]){
		case '(':
			eat(raw,"(");
			cur->car()=parse(raw);
			eat(raw,")");
			break;
		case '"':
			eat(raw,"\"");
			while(raw.front()!='"'){
				cur->sym().append(raw,1);
				raw.nom(1);
			}
			eat(raw,"\"");
			break;
		case '\'':
			eat(raw,"'");
			if('('){
				eat(raw,"(");
				cur->carsym()=parse(raw);
				eat(raw,")");
			}else{
				while(raw.front()!=' '&&raw.front()!=')'&&raw.size()){
					cur->sym().append(raw,1);//=(eat till ' ' or ')')
					raw.nom(1);
				}
			}
			break;
		default:
			break;
		}
		cur=cur->cdr();
	}
	return ret;
}

lispNode parse(std::string&& raw){
	return parse(raw);
}

#if __INCLUDE_LEVEL__==0
int main(int argc, char *argv[]){
	lispNode prgn;
	std::string raw;
	//read program
	prgn=parse(raw);
	return 0;
}
#endif
