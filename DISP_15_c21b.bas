'Program: Complete Display and transmission
'for PIC16f877a

'Descript: Handles display readout for
'the Automatic Power Management System
'via a 128-bit UNIPOLAR encoding scheme transmission

'Hardware: Display readout used in the included
'display_XX.bas, some LEDs (see declarations for specifics)
'and connection to Gizduino IOT-644

'Software: PIC Simulator IDE

'Author: Leslie S. Caminade

'COMMUNICATION NOTE:
'uses an improvised ACTIVE HIGH UNIPOLAR SCHEME which anticipates
'an interrupt, then
'a full 8-bit HIGH burst as start bit value = 255
'then the next 8bits as an ADDRESS or internal data type (saved in variable "type")
'then the rest as the data, grouped by 8 bits.

'Updated: March 2016

Include "display_01e.bas"

TRISC = 00000100b
TRISD = 00h
TRISA = ffh
TRISB = ffh

Symbol datapin = RB4
Symbol clockpin = RB5

Symbol timeled = RD2
Symbol powerled = RD3
Symbol power2led = RD1
Symbol buttonstr = RC3
Symbol button = RC2

Call lamptest()

powerled = 1
timeled = 1
power2led = 1
WaitMs 1000
powerled = 0
timeled = 0
power2led = 0

Const ttime = 500  'transmission time in us

Dim type As Byte

Dim h1 As Byte  'clock 0
Dim h0 As Byte
Dim m1 As Byte
Dim m0 As Byte
Dim tdur As Byte

Dim p3 As Byte  'power1 1
Dim p2 As Byte
Dim p1 As Byte
Dim p0 As Byte
Dim pdur As Byte

Dim p23 As Byte  'energy
Dim p22 As Byte
Dim p21 As Byte
Dim p20 As Byte
Dim p2dur As Byte

Dim buf4 As Word
Dim buf3 As Word
Dim buf2 As Word
Dim buf1 As Word

Dim bufdata As Bit
Dim clockflag As Bit
Dim continue As Bit
Dim empty As Bit
Dim disp_en As Bit
Dim debounce As Byte

Dim scrolldot As Byte

empty = 1
continue = 1
clockflag = 0
disp_en = 1

INTCON.INTE = 1
Enable

Dim timer As Word
timer = 0
Dim mode As Byte
Dim longtimer As Byte
WaitMs 1000
'-----------------------------------------------------------------------------------------------------------------------------
main:


If empty = 0 And disp_en = 1 Then

Select Case mode
Case 0
Call display(h1, h0, m1, m0, 3)  'display time
powerled = 0
timeled = 1
power2led = 0

Case 1
	If p0 > 0 Or p1 > 0 Or p2 > 0 Or p3 > 0 Then
		Call display(p3, p2, p1, p0, 0)  'display power only if it has nonzero value
powerled = 1
timeled = 0
power2led = 0
	Else
		Call display(h1, h0, m1, m0, 3)  'or else display time
powerled = 0
timeled = 1
power2led = 0
	Endif
Case 2
	If p20 > 0 Or p21 > 0 Or p22 > 0 Or p23 > 0 Then
		Call display(p23, p22, p21, p20, 0)  'display power2 only if it has nonzero value
powerled = 0
timeled = 0
power2led = 1
	Else
		Call display(h1, h0, m1, m0, 3)  'or else display time
powerled = 0
timeled = 1
power2led = 0
	Endif
EndSelect

WaitMs 1
timer = timer + 1

If timer > 100 Then
mode = mode + 1
timer = 0
Endif

If mode = 3 Then
mode = 0
Endif

Endif


Goto main
End                                               
On Interrupt
Save System
timer = 100

scan:

	If clockpin = 1 And clockflag = 0 Then
	bufdata = datapin
	buf4 = ShiftLeft(buf4, 1)
	buf4.0 = buf3.15
	buf3 = ShiftLeft(buf3, 1)
	buf3.0 = buf2.15
	buf2 = ShiftLeft(buf2, 1)
	buf2.0 = buf1.15
	buf1 = ShiftLeft(buf1, 1)
	buf1.0 = bufdata
	clockflag = 1
	Endif
	
	If clockpin = 0 Then
	clockflag = 0
	Endif
	
	If timer = 0 Then
	Goto goout  'receive timeout handler
	Endif

	If buf4.HB = 255 Then
	type = buf4.LB
	empty = 0
	Goto patch
	Endif

	timer = timer - 1
Goto scan

patch:
	
	Select Case type
	Case 0
	h1 = buf3.HB
	h0 = buf3.LB
	m1 = buf2.HB
	m0 = buf2.LB
	tdur = buf1.HB
	Case 1
	p3 = buf3.HB
	p2 = buf3.LB
	p1 = buf2.HB
	p0 = buf2.LB
	pdur = buf1.HB
	Case 2
	p23 = buf3.HB
	p22 = buf3.LB
	p21 = buf2.HB
	p20 = buf2.LB
	pdur = buf1.HB
	EndSelect
	
	buf4 = 0
	buf3 = 0
	buf2 = 0
	buf1 = 0

goout:
INTCON.INTF = 0
Resume                                            
