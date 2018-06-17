#define ERROR(x)                                                               \
	do {                                                                   \
		puts(x);                                                       \
		exit(-1);                                                      \
	} while (0)

/*
 * Helpers
 */

#include <string>
using std::string;

int find_match(const string l, const int p) {
	switch (l[p]) {
	case ')':
		return p;
	case '(':
		return find_match(l, find_match(l, p + 1) + 1);
	case '\0':
		ERROR("find_match found no match");
	default:
		return find_match(l, p + 1);
	}
}
bool starts_with(const string l, const string v) {
	if (v.size() <= l.size())
		if (!l.compare(0, v.size(), v)) return true;
	return false;
}
string ParenClean(const string l) {
	if (l.size() < 3) return l;
	if (l[0] == '(')
		if (l[1] == '(')
			if (find_match(l, 1) == find_match(l, 2) + 1)
				return ParenClean(l.substr(1, find_match(l, 2)))
				       + ParenClean(
				             l.substr(find_match(l, 1) + 1));
	return l[0] + ParenClean(l.substr(1));
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
			const int s= find_match(l, f + 2);
			return '(' + brep(l.substr(1, f - 1),
			                  l.substr(f + 1, s - f))
			       + ')' + l.substr(s + 1);
		} else {
			return brep(l.substr(1, f - 1), l.substr(f + 1));
		}
	} else
		return l[0] + b(l.substr(1));
}

/*
 * Sub-expression Nameing
 */

#include <map>
using std::map;
map<char, string> defn;

string saveDef(const char n, const string v) {
	defn[n]= ParenClean(v);
	return n + ('=' + defn[n]);
}
string convertToPure(const string l) {
	if (!l.size()) return l;
	if (defn.count(l[0])) return defn[l[0]] + convertToPure(l.substr(1));
	return l[0] + convertToPure(l.substr(1));
}
string convertFromPure(const string l) {
	if (!l.size()) return l;
	for (const auto& kvp : defn)
		if (starts_with(l, kvp.second))
			return kvp.first
			       + convertFromPure(l.substr(kvp.second.size()));
	return l[0] + convertFromPure(l.substr(1));
}

/*
 * CLI Interface
 */

string handel(const string cmd) {
	if (cmd.size() > 1)
		if (cmd[1] == '=') {
			if (cmd[0] >= 'A' && cmd[0] <= 'Z')
				return saveDef(cmd[0], cmd.substr(2));
			else
				return "Parse Error";
		}
	if (cmd[0] == '(' || (cmd[0] >= 'A' && cmd[0] <= 'Z'))
		return ParenClean(convertFromPure(b(convertToPure(cmd))));
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
