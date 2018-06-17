#include <string>
using std::string;

/*
 * Helpers
 */

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

/*
 * Lambda-Calc beta reducer
 */

string inc(const string l, const int v= 1, int d= 0) {
	if (!l.size()) return l;
	if (v > 1) return inc(inc(l), v - 1);
	if (l[0] == 'l') return l[0] + inc(l.substr(1), v, d + 1);
	if (l[0] == ')') return l[0] + inc(l.substr(1), v, d - 1);
	if (l[0] >= '1' && l[0] <= '9')
		if (l[0] - '0' > d)
			return char(l[0] + 1) + inc(l.substr(1), v, d);
	return l[0] + inc(l.substr(1), v, d);
}

string brep(const string l, const string v, const int d= 0) {
	if (!l.size()) return l;
	if (d == 0) return brep(l.substr(1), v, 1);
	switch (l[0]) {
	case 'l':
		return 'l' + brep(l.substr(1), v, d + 1);

	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		if (l[0] - '0' == d)
			return inc(v, d - 1) + brep(l.substr(1), v, d);
		else if (l[0] - '0' < d)
			return l[0] + brep(l.substr(1), v, d);
		else
			return char(l[0] - 1) + brep(l.substr(1), v, d);
	case ')':
		return ')' + brep(l.substr(1), v, d - 1);
	}
	return l[0] + brep(l.substr(1), v, d);
}

string b(const string l) {
	if (l[0] == '(') {
		const int f= find_match(l, 1);
		if (l[1] == '(') {
			const int s= find_match(l, 2);
			if (s + 1 == f)
				return l.substr(1, s) + l.substr(f + 1);
			else {
				return '(' + b(l.substr(1, f - 1)) + ')'
				       + l.substr(f + 1);
			}
		}
		if (!(l.size() - f - 1)) return l.substr(1, f - 1);
		if (l[f + 1] == '(') {
			int s= find_match(l, f + 2);
			return '(' + brep(l.substr(1, f - 1),
			                  l.substr(f + 1, s - f))
			       + ')' + l.substr(s + 1);
		} else {
			return brep(l.substr(1, f - 1), l.substr(f + 1));
		}
	} else
		return l;
}

/*
 * CLI Interface
 */

string handel(const string cmd) {
	if (cmd[0] == '(') return b(cmd);
	return cmd;
}

/*
 * REPL Prompt
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;

#define PROMPT "> "
int main() {
	string cmd;
	cout << PROMPT;
	while (getline(cin, cmd)) cout << handel(cmd) << endl << PROMPT;
	return 0;
}
