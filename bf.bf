Memory is divided into two regions, the states and the tape
states = { symbol ; working space ; '' }
Tape = { cell 0 ; ws ; cell 1 ; ws ; _1 ; ws ; 2 ; ws ; _2 ; '' }
Between the tape and the states is a divider


First we read in the program
The program is terminated by a bang
+[,   Tape = Curr Char ; Continue Flag
   read symbol
   switch LEFT RIGHT UP DOWN IN OUT WHILE DONE BANG DEFAULT

   UP     = 43 = 1
   [<]> if on blank then prevent left shift otherwise do nothing
   if char [ char ; tmpChar
     copy tmpChar char [->+>+<<]>>[-<<+>>]<
     tmpChar sub 43 -------------------------------------------
     if not 0 [  set flag to 1 ->[-]+< ]
     move not flag to here (accept) +>[-<->]<
     if accept [clear -< set char to 1 [-]+ >> set tmp 1 +<] mov tmp to flag >[[-]<+>]<
     if flag [ flag now cont flag ; mov to blank char > exta for check >]
   ]< end UP
   
   IN     = 44 = 3
   DOWN   = 45 = 2
   OUT    = 46 = 4
   LEFT   = 60 = 5
   RIGHT  = 62 = 6
   WHILE  = 91 = 7
   DONE   = 93 = 8

   BANG   = 33
   [<]> if on blank then prevent left shift
   if char [ char ; tmpChar
     copy tmpChar char [->+>+<<]>>[-<<+>>]<
     tmpChar sub 33 ---------------------------------
     if not 0 [ set flag to 1 ->[-]+< ]
     move not flag to here (accept) +>[-<->]<
     if accept [ clear -
                 set char to 0 <[-]
		 on blank cell
		 exta for check >]
   ]< end BANG

   DEFAULT
   [ clear char [-]
     set cont flag <+
     move to next blank (current) >
   ]

  if cont flag move to here <[->+<]>
] loop else done
move to last char <<

make the divider
  just a temp divider +>+<

setup the head
    move to the start of the tape <<[<<]>>

run the program
   switch LEFT RIGHT UP DOWN IN OUT WHILE DONE BANG
