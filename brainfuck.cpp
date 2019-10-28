#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

#define MAX_TIME 10000000

#define DEBUG 0
#if DEBUG > 0
#include <ctype.h>
#include <iostream>
#define DPRINT(x)                                                              \
  (std::cout << "DPRINT: File:" << __FILE__ << " Line:" << __LINE__ << " - "   \
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
  operator int const() const { return number; }
  num &operator++() {
    number++;
    return *this;
  }
  num &operator++(int) {
    number++;
    return *this;
  }
  num &operator--() {
    number--;
    return *this;
  }
  num &operator--(int) {
    number--;
    return *this;
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
  num States_Used;
  num Cycles;
  num Program_Length;
} stats;

std::ostream &operator<<(std::ostream &o, Stats const &s) {
  return o << "Program_Length=" << s.Program_Length
           << " States_Used=" << s.States_Used << " Cycles=" << s.Cycles;
}

#if DEBUG
std::ostream &operator<<(std::ostream &o, TapeMachine const &tm) {
  o << "Tape='";
  for (auto &t : tm.tape)
    if (t.first == tm.head)
      o << "->" << t.first << "(" << (isprint(t.second) ? (char)t.second : '.')
        << t.second << ") ";
    else
      o << t.first << "(" << (isprint(t.second) ? (char)t.second : '.')
        << t.second << ") ";
  return o << "'";
}
std::ostream &operator<<(std::ostream &o, StateMachine const &sm) {
  o << "states='";
  if (sm.state < (int)sm.states.size()) {
    for (num i = 0; i < sm.state; i++)
      o << (char)sm.states[i];
    o << "(" << (char)sm.states[sm.state] << ")";
    for (size_t i = sm.state + 1; i < sm.states.size(); i++)
      o << (char)sm.states[i];
  } else {
    for (size_t i = 0; i < sm.states.size(); i++)
      o << (char)sm.states[i];
  }
  return o << "'";
}
#endif

char ch;
#define CURCHAR (ch)
#define NEXT_CHAR                                                              \
  (ch = getchar(),                                                             \
   DPRINT("Got char " << (int)ch << "=" << (isprint(ch) ? ch : '.')), ch)

/**
 * Load the states into the machine.
 */
void PrimeMachine() {
  while (NEXT_CHAR != EOF)
    switch (CURCHAR) {
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
      program.state++;
      break;
    case OUTP:
      if (' ' <= machine.tape[machine.head] &&
          machine.tape[machine.head] <= '~')
        cout << (char)machine.tape[machine.head] << std::flush;
      program.state++;
      break;
    }
    // DPRINT( program << "\t" << machine);
    // DPRINT(endl << program << endl << machine);
    DPRINT(program.state << endl << machine);
  }
}

void PrintStats() { cout << endl << stats << endl; }

int main() {
  PrimeMachine();
  stats.Program_Length = program.states.size();
  RunMachine();
  stats.States_Used = machine.tape.size();
  PrintStats();
  return 0;
}
