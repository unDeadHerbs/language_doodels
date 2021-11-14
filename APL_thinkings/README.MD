Interactive APL Type Setting and Evaluation Environment
=======================================================

The purpose of this program is to add to APL some language features that I would like to have.
A secondary purpose is to offer both a graphical environment to program in APL and a documentation system therein as to bring APL into being a more usable language for the modern era.

Language Primitives
===================

⌶ɫ%'⍺⍵
_abcdefghijklmno   pqrstuvwxyz  y.⍬
0123456789 ⊢¥$£¢   ∆ABCDEFGHIJKLMNO
PQRSTUVWXYZ  ý     ⍙ÁÂÃÇÈÊËÌÍÎÏÐÒÓÔ
ÕÙÚÛÝþãìðòõ{€}⊣⌷   ¨ÀÄÅÆ⍨ÉÑÖØÜßàáâä
åæçèéêëíîïñ[/⌿\⍀   <≤=≥>≠∨∧-+÷×?∊⍴~
↑↓⍳○*⌈⌊∇∘(⊂⊃∩∪⊥⊤   |;,⍱⍲⍒⍋⍉⌽⊖⍟⌹!⍕⍎⍫
⍪≡≢óôöø"# &´┘┐┌└   ┼─├┤┴┬│@ùúû^ü`∣¶
:⍷¿¡⋄←→⍝)]  §⎕⍞⍣   "


⍳ indacies
⍬ empty
¯ negitive number
∊ is in
⊂⊃ enclose/disclose
⌿⍀
÷× div and times
¨ for each
⍨ reverse operands
⋄ comand separator

Values
------
* ⍺ Left Operand
* ⍵ Right operand
* [a-zA-Z]+ user defined identifier
* [0-9]+ a number
* % converts the following text into the symbol with the same name

Monadic Functions
-----------------
| Symbol | Name | Description |
|:------ |:---- |:----------- |
| `?` | Roll | Returns a number between INDEX_BASE and ⍵
| `⌈` | Celling | rounds ⍵ to the closest integer that is > or = to it
| `⌊` | Floor | rounds ⍵ to the closest integer that is < or = to it
| `⍴` | Shape | returns a vector of the sizes of each layer of a tensor
| `~` | Logical Not | returns 1 if ⍵ is 0, else 0
| `|` | Absolute Value | Returns the absolute value of ⍵
| `×` | Sign | Returns the sign of ⍵ (-1, 0, or 1)
| `⍟` | exp or log?
| `¯` | Negative | returns ⍵ time minus one
| `+` | Identity | returns ⍵
| `÷` | Reciprocal | returns the reciprocal ⍵
| `⌹` | Inverse | returns the matrix inverse of ⍵
| `○` | Circle | Converts ⍵ into rotations (multiplies by 2 pi)
| `⌽` | Reverse | Revers the ordering of the First index
| `⊖` | Rotate | Reverse the ordering of the Second index
| `⍉` | Transpose | Exchange the values between the first and second index
| `⍳` | Indecies | A vector from INDEX_BASE to ⍵ |
| `!` | Factorial | returns the factorial of the number (also works on decimals)

Dyadic Functions
----------------

Functional modifiers
--------------------

Environmental Modifiers
-----------------------
| Symbol | Description | Notes |
| ------ | ----------- | ----- |
| `INDEX_BASE` | The lowest number used for both %iota and array indexing | should be either 0 or 1 otherwise unintuitive behavior may result |
| `PRECISION` | The number of significant places to carry out calculations to
| `BASE_SYSTEM` | The base system to both preform the calculations in and to display the output in | if you don't want to mess with the calculation methodology this should be set for only the display stage |

Planned Features
================
* `λ`
   * refers to the funciton ⍵ up from the curent in the current evaluation tree
   * count by {}s and defns
   * operates on all values in ⍵, regardless to the structure there of
* `'`
   * quote the folowing funciton as to refer to it as a data object
   * before evaluating a function check if the preceding sym is '
* `⍎`
   * if ⍵ is not a '' treat it as a parse tree
   * this will require the makeing of a reasonable in language parse tree
   * read ⍺ as the structure of arguments for ⍵
   *   that is to say that one walks structres and passes the respective part of ⍺ to the funciton
* `⍎`
   * dyadic
* `]`
   * acts as () around the preceding function and it's minimal number of parameters (1 or 2)
* `]]`
   * acts as a () around the preceding function and it's maximal number of parameters (2 or 1)
* some form of lazy evaluation
