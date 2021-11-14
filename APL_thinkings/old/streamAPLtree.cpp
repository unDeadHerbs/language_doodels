//APRL : A Print Read Loop
//APL+PERL
//Array Print Read Loop
//Array Processing Recurrence Language
//APLISP
//

#include <iostream>
#include <string>
#include <map>
#include <deque>

bool PROMPT=true;
bool DUMBCHECK=true;
int RUNNING=1;
bool ERROR=0;
std::string ERRORNAM;
int INPUTNUM=1;
//std::deque<std::string> hist;

//*
class APLvector{
	bool base=true;
	std::string a;
	std::deque<APLvector> subs;
};//*/

class parseed{
public:
	bool base=true;//if contains val or oper
	bool isvector=false;
	std::string val;
	APLvector vec;
	std::map<int,parseed> oper;//ands-ator
	//0=αα 1=α 2=op 3=ω 4=ωω
	parseed(std::string exp){
		//read from left matching () and '' pairs
			//if find ⍝ discard unill find an unescaped \n
		//find inline vectors
		//split remaining operators by ' '
		//if a string is not found greedly read chars from it to form operators
		//if (while in greedy) an op is dyadic and dose not accept ⍵⍵ then it is to be marked as wrong
			//
		//have to check for ⍵⍵ and ⍺⍺ in def as ⍴⍴⍳ dose not invoke it
	}
	parseed(const parseed& p){
		//copy
	}
	//move constructor
	std::string op(){
		if(oper[2].base){
			if(/*len(oper[2].val)==*/1)
				return oper[2].val;
			return "";//something that's not an operator so default is reached
		}
		return "0";
	}
	std::string vecstring(){
		//convert vec to a string for printing
	}
	bool mono(){
		//return if monadic
	}
};

class State{
public:
	std::map<std::string,int> builtins;
	std::map<std::string,std::string> defs;
	bool hasParent(false);
	State* p=NULL;
	void State(){}
	void State(bool global){
		if(global){
			//add basic symbol defs
		}
	}
	State(State*P):p(P),hasParent(true){}
	
	//if inited with 1 add global vals
	//copy constructor
	//move constructor
};

void readLine(std::string& line){
	//ads some sort of unmatched '(' check for multi line
	//add up arrow for history
	if(PROMPT)
		std::cout<<"APL:"<<INPUTNUM<<"> ";
	std::cin>>line;
}

void displayLine(std::string& out){
	if(ERROR)
		std::cout<<ERRORNAM;
	else
		std::cout<<out;
	ERROR=0;
}

APLvector apply(APLvector l,auto f,APLvector r){
}

/*
 * operators in progress
 * strip
 *   modifies the fllowing operator
 *   instead of wrapping the operand vectors to the longer it truncates to the shorter
 * overwrap
 *   modifies the following operand
 *   instead of wrapping the operand vectors to the longer it wraps them to the LCM of their lenghts
 * compleat
 *   modifies the boolean operators such that it recursivly ANDs the result for all elements
 *   could probably be done with a "flatten" operator
 *   ⍲/∊ dose that
 * λ
 *   refers to the funciton ⍵ up from the curent in the current evaluation tree
 *   count by {}s and defns
 *   operates on all values in ⍵, regardless to the structure there of
 * '
 *   quote the folowing funciton as to refer to it as a data object
 *   before evaluating a function check if the preceding sym is '
 * ⍎
 *   if ⍵ is not a '' treat it as a parse tree
 *   this will require the makeing of a reasonable in language parse tree
 *   read ⍺ as the structure of arguments for ⍵
 *     that is to say that one walks structres and passes the respective part of ⍺ to the funciton
 * ]
 *   acts as () around the preceding function and it's minimal number of parameters (1 or 2)
 * ]]
 *   acts as a () around the preceding function and it's maximal number of parameters (2 or 1)
 * function that is 1 or 0 if {is funciton, is number, is enclosed structure, is array(tree,marix)}
 * script f
 *   if preceding argument then be following as a funciton
 *   {⍎⍺/⍵}
 */
parseed evalBlock(parseed b,State& s){
	switch(char(b.op())){
		//big switch statement of cpp implementations
	case '?'://U+003F
		//Roll    ?B   One integer selected randomly from the first B integers
		//Deal   A?B   A distinct integers selected randomly from the first B integers
	case '⌈'://U+2308
		//Ceiling              ⌈B   Least integer greater than or equal to B
		//Maximum, Ceiling    A⌈B   The greater value of A or B
	case '⌊'://U+230A
		//Floor              ⌊B   Greatest integer less than or equal to B
		//Minimum, Floor    A⌊B   The smaller value of A or B
	case '⍴'://U+2374
		//Shape, Rho             ⍴B   Number of components in each dimension of B
		//Reshape, Dyadic Rho   A⍴B   Array of shape A with data B
	case '∼'://U+223C
		//Not, Tilde   ∼B   Logical: ∼1 is 0, ∼0 is 1
		//~∨ = 'not Or' and  ~∧ = 'not And'
	case '∣'://U+2223
		//Absolute value   ∣B   Magnitude of B
		//Residue   A∣B   B modulo A
	case '⍳'://U+2373
		//Index generator, Iota    ⍳B   Vector of the first B integers
		//Index of, Dyadic Iota   A⍳B   The location (index) of B in A; 1+⌈/⍳⍴A if not found
	case '⋆'://U+22C6
		//Exponential       ⋆B   e to the B power
		//Exponentiation   A⋆B   A raised to the B power
	case '−'://U+2212
		//Negation    −B   Changes sign of B
		//Subtract   A−B   A minus B
	case '+'://U+002B
		//Identity    +B   No change to B
		//Add        A+B   Sum of A and B
	case '×'://U+00D7
		//Signum      ×B   ¯1 if B<0; 0 if B=0; 1 if B>0
		//Multiply   A×B   A multiplied by B
	case '÷'://U+00F7
		//Reciprocal   ÷B   1 divided by B
		//Divide      A÷B   A divided by B
	case ','://U+002C
		//Ravel, Catenate, Laminate    ,B   Reshapes B into a vector
		//Catenation                  A,B   Elements of B appended to the elements of A
	case '⌹'://U+2339
		//Matrix inverse, Monadic Quad Divide    ⌹B   Inverse of matrix B
		//Matrix divide, Dyadic Quad Divide     A⌹B   Solution to system of linear equations, multiple regression Ax = B
	case '○'://U+25CB
		//Pi times    ○B   Multiply by π
		//Circle     A○B   Trigonometric functions of B selected by A  ---
		//  A=1: sin(B)
		//  A=2: cos(B)
		//  A=3: tan(B)
	case '⍟'://U+235F
		//Logarithm    ⍟B   Natural logarithm of B
		//Logarithm   A⍟B   Logarithm of B to base A
	case '⌽'://U+233D
		//Reversal    ⌽B   Reverse elements of B along last axis
		//Rotation   A⌽B   The elements of B are rotated A positions
	case '⊖'://U+2296 ⊖
		//Reversal    ⊖B   Reverse elements of B along first axis
		//Rotation   A⊖B   The elements of B are rotated A positions along the first axis
	case '⍋'://U+234B
		//Grade up   ⍋B   Indices of B which will arrange B in ascending order
	case '⍒'://U+2352
		//Grade down   ⍒B   Indices of B which will arrange B in descending order
	case '⍎'://U+234E
		//Execute   ⍎B   Execute an APL expression
		//eval operand
		//asert that evald operand is string
		//parse and eval string
	case '⍕'://U+2355
		//Monadic format   ⍕B   A character representation of B
		//Dyadic format   A⍕B   Format B into a character matrix according to A
	case '⍉'://U+2349
		//Monadic transpose    ⍉B   Reverse the axes of B
		//General transpose   A⍉B   The axes of B are ordered by A
	case '!'://U+0021
		//Factorial       !B   Product of integers 1 to B
		//Combinations   A!B   Number of combinations of B taken A at a time

	case '↑'://U+2191
		//Take   A↑B   elect the first (or last) A elements of B according to ×A
	case '↓'://U+2193
		//Drop   ↓B   Remove the first (or last) A elements of B according to ×A
	case '⊥'://U+22A5
		//Decode   A⊥B   Value of a polynomial whose coefficients are B at A
	case '⊤'://U+22A4
		//Encode   A⊤B   Base-A representation of the value of B
	case '\\'://U+005C
		//Expansion, Dyadic Backslash   A\B   Insert zeros (or blanks) in B corresponding to zeros in A
		//Scan (last axis), Backslash    \    +\B   Running sum across B
	case '⍀'://U+2340
		//Scan (first axis)   ⍀   +⍀B   Running sum down B
	case '/'://U+002F
		//Compression, Dyadic Slash   A/B   Select elements in B corresponding to ones in A
		//Reduce (last axis), Slash    /    +/B   Sum across B
	case '⌿'://U+233F
		//Reduce (first axis)   ⌿   +⌿B   Sum down B
	case '¨'://U+00A8
		//Diaeresis, Dieresis, Double-Dot   A¨B   Over each, or perform each separately; B = on these; A = operation to perform or using(e.g. iota)
	case '.'://U+002E
		//Inner product    .   A+.×B   Matrix product of A and B
		//Outer product   ∘.   A∘.×B   Outer product of A and
	case '∘'://U+2218 ∘
		//Inner product    .   A+.×B   Matrix product of A and B
		//Outer product   ∘.   A∘.×B   Outer product of A and B

	/*The boolean operators*/

	case '∈'://U+2208
		//Membership, Epsilon   A∈B   1 for elements of A present in B; 0 where not.
	case '<'://U+003C
		//Less than   A<B   Comparison: 1 if true, 0 if false
	case '≤'://U+2264
		//Less than or equal   A≤B   Comparison: 1 if true, 0 if false
	case '='://U+003D
		//Equal   A=B   Comparison: 1 if true, 0 if false
	case '≥'://U+2265
		//Greater than or equal   A≥B   Comparison: 1 if true, 0 if false
	case '>'://U+003E
		//Greater than   A>B   Comparison: 1 if true, 0 if false
	case '≠'://U+2260 ≠
		//Not equal   A≠B   Comparison: 1 if true, 0 if false
	case '∨'://U+2228
		//Or   A∨B   Boolean Logic: 0(False) if both A and B = 0, 1 otherwise. Alt: 1(True) if A or B = 1(True)
	case '∧'://U+2227
		//And   A∧B   Boolean Logic: 1(True) if both A and B = 1, 0(False) otherwise
	case '⍱'://U+2371
		//Nor   A⍱B   Boolean Logic: 1 if both A and B are 0, otherwise 0.
	case '⍲'://U+2372
		//Nand   A⍲B   Boolean Logic: 0 if both A and B are 1, otherwise 1.


	case 0:
		//simplify operator
	default:
		//substitue op with def in state
		//if not in state return error
		break;
	}
}

std::string evalLine(std::string eq,State& state){
	parseed b(parseBlock(eq));
	while(!(b.base||ERROR))
		b=evalBlock(b,state);
	if(b.isvec)
		return b.vecString();
	return b.val;
}

int main(){
	State global(1);
	State state,statetmp;
	state.parent(&global);
	std::string in,out;
	for(;RUNNING;){
		//check if passed -q or is in |stream
		statetmp=state;
		readLine(in);
		out=evalLine(in,statetmp);
		if(!ERROR)
			state=statetmp;
		displayLine(out);
	}
}
