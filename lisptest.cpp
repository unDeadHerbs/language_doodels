#define test
#include "lisp.cpp"
#include <iostream>

int main(int argc, char *argv[]){
	parse("");
	parse("(+)");
	parse("(");
	return 0;
}
