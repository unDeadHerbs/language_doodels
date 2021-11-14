BrainFuck Language Definition
=============================

The abstract machine modeled by the BrainFuck language is a state
machine with tape. Each state is represented by a single symbol in the
language and is assumed to advance to the next state, the exception to
this are the looping commands. Each state may increment or decrement
the point (the value on the tape where the head is) or shift the head
one location right or left.

The operations are:
- `+` Increment the value at the point.
- `-` Decrement the value at the point.
- `<` Shift the head one cell left.
- `>` Shift the head one cell right.
- `[` If the value at the point is 0 jump to the matching `]`.
- `]` If the value at the point is not 0 jump to the matching `[`.
- `,` Write the value on the standard input to the point.
- `.` Write the value at the point to the standard output.

The input to a BrainFuck interperter is a valid brainfuck program followed by a `!` and the input to the program.
