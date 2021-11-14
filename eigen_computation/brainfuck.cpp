#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::map;
using std::setw;
using std::string;
using std::vector;

#define NOW                                                     \
	(_time = std::time(nullptr), _ltime = std::localtime(&_time), \
	 std::put_time(_ltime, "%Y-%j %H:%M:%S"))

auto _time = std::time(nullptr);
auto _ltime = std::localtime(&_time);

#define MAX_TIME 10000000

#define DEBUG 0
#if DEBUG > 0
#define DPRINT(x)                                                            \
	(std::cout << "DPRINT: File:" << __FILE__ << " Line:" << __LINE__ << " - " \
	           << x << std::endl)
#else
#define DPRINT(x) (NULL)
#endif

// clang-format off
enum CODE {
  INCR = '+', DECR = '-',
  LEFT = '<', RIGT = '>',
  WHIL = '[', DONE = ']',
  INPT = ',', OUTP = '.' };
// clang-format on

class num {
	long long int number;

 public:
	num() : number(0) {}
	num(int n) : number(n) {}
	operator long long int const() const { return number; }
	num& operator++() {
		number++;
		return *this;
	}
	num& operator++(int) {
		auto ret = *this;
		++*this;
		return ret;
	}
	num& operator--() {
		number--;
		return *this;
	}
	num& operator--(int) {
		auto ret = *this;
		--*this;
		return ret;
	}
};

struct TapeMachine {
	map<num, num> tape;
	num head;
} machine;

struct StateMachine {
	vector<CODE> states;
	num state;
} program;

struct Stats {
	num Cycles;
} stats;

std::ostream& operator<<(std::ostream& o, Stats const& s) {
	return o  //<< "Program_Length=" << program.states.size()
	          // that isn't a helpful stat in this situation
	       << "States =" << setw(11) << machine.tape.size()
	       << " Cycles =" << setw(21) << s.Cycles;
	// 80 chars with date and flag/read print
}

#if DEBUG
std::ostream& operator<<(std::ostream& o, TapeMachine const& tm) {
	o << "Tape='";
	for (auto& t : tm.tape)
		if (t.first == tm.head)
			o << "->" << t.first << "(" << (isprint(t.second) ? (char)t.second : '.')
			  << t.second << ") ";
		else
			o << t.first << "(" << (isprint(t.second) ? (char)t.second : '.')
			  << t.second << ") ";
	return o << "'";
}
std::ostream& operator<<(std::ostream& o, StateMachine const& sm) {
	o << "states='";
	if (sm.state < (int)sm.states.size()) {
		for (num i = 0; i < sm.state; i++) o << (char)sm.states[i];
		o << "(" << (char)sm.states[sm.state] << ")";
		for (size_t i = sm.state + 1; i < sm.states.size(); i++)
			o << (char)sm.states[i];
	} else {
		for (size_t i = 0; i < sm.states.size(); i++) o << (char)sm.states[i];
	}
	return o << "'";
}
#endif

char ch;
#define CURCHAR (ch)
#define NEXT_CHAR  \
	(ch = getchar(), \
	 DPRINT("Got char " << (int)ch << "=" << (isprint(ch) ? ch : '.')), ch)

/**
 * Load the states into the machine.
 */
void PrimeMachine() {
	while (NEXT_CHAR != EOF) switch (CURCHAR) {
				// clang-format off
			case '[': case ']':
			case '+': case '-':
			case '<': case '>':
			case ',': case '.':
				// clang-format on
				program.states.push_back((CODE)CURCHAR);
				break;
			case '!':
				return;
		}
	DPRINT("Done Priming");
}

/**
 * Run the machine.
 *
 * Run the machine until it halts or fails to read.
 */
void RunMachine() {
	// run the machine until state=states.size() or state<0
	DPRINT("Starting Machine : " << program);
	static bool INPUT_DEBUG = false;
	static int INPUT_FLAGS = 0;
	while (0 <= program.state && program.state < (int)program.states.size()) {
		stats.Cycles++;
		// if (stats.Cycles == MAX_TIME)
		// exit(-1);
		switch (program.states[program.state]) {
			case INCR:
				machine.tape[machine.head]++;
				program.state++;
				break;
			case DECR:
				machine.tape[machine.head]--;
				program.state++;
				break;
			case LEFT:
				machine.head--;
				program.state++;
				break;
			case RIGT:
				machine.head++;
				program.state++;
				break;
			case WHIL:
				program.state++;
				if (machine.tape[machine.head]) {
					break;
				}
				for (int b = 1; program.state < program.states.size() && b;
				     program.state++) {
					switch (program.states[program.state]) {
						case INCR:
						case DECR:
						case INPT:
						case OUTP:
						case LEFT:
						case RIGT:

							break;
						case WHIL:
							b++;
							break;
						case DONE:
							b--;
							break;
					}
				}
				break;
			case DONE:
				if (!machine.tape[machine.head]) {
					program.state++;
					break;
				}
				program.state--;
				for (int b = 1; program.state < program.states.size() && b;
				     program.state--) {
					switch (program.states[program.state]) {
						case INCR:
						case DECR:
						case INPT:
						case OUTP:
						case LEFT:
						case RIGT:

							break;
						case WHIL:
							b--;
							break;
						case DONE:
							b++;
							break;
					}
				}
				program.state++;
				break;
			case INPT:
				machine.tape[machine.head] = NEXT_CHAR;
				if (CURCHAR == 'F')
					cout << NOW << " : Flag " << setw(3) << INPUT_FLAGS++ << " : "
					     << stats << std::flush << endl;  // 80 Chars exatly
				else if (CURCHAR == 'D') {
					INPUT_DEBUG = !INPUT_DEBUG;
					if (INPUT_DEBUG)
						cout << "Debugging Enabled" << std::flush << endl;
					else
						cout << "Debugging Disabled" << std::flush << endl;
				} else {
					if (INPUT_DEBUG)
						cout << NOW << " : Read '" << (CURCHAR == '\n' ? 'n' : CURCHAR)
						     << "' : " << stats << std::flush << endl;
					// 80 Chars exatly
					program.state++;
					// only advance the state if a real read happened
				}
				break;
			case OUTP:
				if (' ' <= machine.tape[machine.head] &&
				    machine.tape[machine.head] <= '~')
					if (INPUT_DEBUG)
						cout << NOW << " : Prnt '"
						     << (((char)machine.tape[machine.head]) == '\n'
						             ? 'n'
						             : ((char)machine.tape[machine.head]))
						     << "' : " << stats << std::flush << endl;
					else
						cout << (char)machine.tape[machine.head] << std::flush;
				program.state++;
				break;
		}
		// DPRINT( program << "\t" << machine);
		// DPRINT(endl << program << endl << machine);
		DPRINT(program.state << endl << machine);
	}
}

void PrintStats() { cout << endl << NOW << stats << endl; }

int main() {
	PrimeMachine();
	RunMachine();
	PrintStats();
	return 0;
}
