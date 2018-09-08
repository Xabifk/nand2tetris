// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(MAINLOOP)
//XOR
@SCREEN
D=M
@M1
D;JLT
@R0
M=0
@M1END
0;JMP
(M1)
@R0
M=1
(M1END)

@KBD
D=M
@M2
D;JGT
@R1
M=0
@M2END
0;JMP
(M2)
@R1
M=1
(M2END)

@R0
D=M
@R1
D=D|M
@R3
M=D

@R0
D=M
@R1
D=D&M
D=!D

@R3
D=D&M

@NSCREEN
D;JGT
@MAINLOOP
0;JMP

(NSCREEN)

@KBD
D=A
@n
M=D
M=M-1

@SCREEN
D=A
@i
M=D
(LOOP)
@n
D=D-M
@END
D;JGT
@i
D=M
A=D
M=!M
D=D+1
@i
M=D
@LOOP
0;JMP
(END)

@MAINLOOP
0;JMP
(MAINLOOPEND)
