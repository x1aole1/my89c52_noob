	ORG		0000H
	AJMP	MAIN
	ORG		0003H
	AJMP	INTZD1
	ORG		0030H
	MOV		A,#00H
MAIN:;MOV	A,#01H
	MOV		P1,A
	LCALL	DELAY
	SETB	IT0
	SETB	EX0
	SETB	EA
	SETB	PX0
	;JMP		$
	LCALL	MAIN
	ORG		0100H
INTZD1:PUSH	PSW
	MOV		P1,#0F0H
	LCALL	DELAY
	MOV		P1,#0FH
	LCALL	DELAY
	POP		PSW
	;LCALL	INTZD1
	RETI
DELAY:MOV  R5, #25
DLY1: MOV  R6, #100
DLY2: MOV  R7, #100
      DJNZ R7, $
      DJNZ R6, DLY2
      DJNZ R5, DLY1
      RET
      END