/*
 * AssemblerApplication1.asm
 *
 *  Created: 29.03.2018 13:58:45
 *   Author: 81moni1bif
 */ 

.def counter = r16
.def helper = r18

ldi counter, 0b00000000
ldi helper, 0b00111111
out DDRC, helper


loop:

	INC counter
	out PORTC, counter
	; ============================= 
	;    delay loop generator 
	;     16000000 cycles:
	; ----------------------------- 
	; delaying 15999993 cycles:
			  ldi  R17, $53
	WGLOOP0:  ldi  R18, $FB
	WGLOOP1:  ldi  R19, $FF
	WGLOOP2:  dec  R19
			  brne WGLOOP2
			  dec  R18
			  brne WGLOOP1
			  dec  R17
			  brne WGLOOP0
	; ----------------------------- 
	; delaying 6 cycles:
			  ldi  R17, $02
	WGLOOP3:  dec  R17
			  brne WGLOOP3
	; ----------------------------- 
	; delaying 1 cycle:
			  nop
	; =============================
	RJMP loop





/*; ============================= 
;    delay loop generator 
;     16000000 cycles:
; ----------------------------- 
; delaying 15999993 cycles:
          ldi  R17, $53
WGLOOP0:  ldi  R18, $FB
WGLOOP1:  ldi  R19, $FF
WGLOOP2:  dec  R19
          brne WGLOOP2
          dec  R18
          brne WGLOOP1
          dec  R17
          brne WGLOOP0
; ----------------------------- 
; delaying 6 cycles:
          ldi  R17, $02
WGLOOP3:  dec  R17
          brne WGLOOP3
; ----------------------------- 
; delaying 1 cycle:
          nop
; =============================*/