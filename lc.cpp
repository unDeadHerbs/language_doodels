#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
#include <string>
using std::string;

/*
class l {
        string C;

      public:
        explicit l(string c) : C(c) {
          //
        }
        friend std::ostream &operator<<(std::ostream &o, l rhs) {
                return o << rhs.C;
        }
        void b() {}
};
//*/

int find_match(const string l, const int p) {
	switch (l[p]) {
	case ')':
		return p;
	case '(':
		return find_match(l, find_match(l, p + 1) + 1);
	case '\0':
		exit(-1);
	default:
		return find_match(l, p + 1);
	}
}

string brep(const string l, const string v, const int d= 0) {
	if (!l.size()) return l;
	if (d == 0) return brep(l.substr(1), v, 1);
	if (l[0] == 'l') return 'l' + brep(l.substr(1), v, d + 1);
	if (l[0] == '0' + d) return v + brep(l.substr(1), v, d);
	if (l[0] == ')') return ')' + brep(l.substr(1), v, d - 1);
	return l[0] + brep(l.substr(1), v, d);
}

string b(const string l) {
	if (l[0] == '(') {
		const int f= find_match(l, 1);
		if (l[1] == '(') { return "TODO: call b on sub and ret"; }
		if (!(l.size() - f)) return l.substr(1, f - 1);
		if (l[f + 1] == '(') {
			int s= find_match(l, f + 2);
			return brep(l.substr(1, f - 1), l.substr(f + 1, s - 1))
			       + l.substr(s + 1);
		} else {
			return brep(l.substr(1, f - 1), l.substr(f + 1));
		}
	} else
		return l;
}

/*
class char_str{
  //only createable as temp value?
  vector<char> buffer;
public:
  operator<<(char){
    push to buffer;
  }
  oper<<(char_str){
    hold mutex
    puch from other to self
    when other is destroyed release mutex
  }
  opper<<(ostream,this){
    hold out mutex
    push to ostream untill self dead
  }
};
//*/

int main() {
	string cmd;
	while (getline(cin, cmd)) cout << b(cmd) << endl;
	return 0;
}
