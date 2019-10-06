'Program: Complete Automated Cellphone Typing
'for PIC16f877a

'Descript: Automatically types text to cellphone
'according to data received from Gizduino IOt 644
'using a arbitrary DIY serial transmission

'Hardware: a myphone hardwre QWERTY keypad, 
'and connection to Gizduino IOT-644

'Software: PIC Simulator IDE

'Author: Leslie S. Caminade

'COMMUNICATION NOTE:
'uses an improvised ACTIVE HIGH UNIPOLAR SCHEME which anticipates
'an interrupt, then
'a full 8-bit HIGH burst as start bit value = 170
'then the next 8bits as an ADDRESS or internal data type (saved in variable "type")
'then the rest as the data, grouped by 8 bits.


Define SIMULATION_WAITMS_VALUE = 0
Include "type_engine2_1.bas"
Include "message_library2.bas"
TRISA = 00000000b
TRISB = 00h
TRISD = 00000001b
TRISC = 00001000b

PORTA = 0
PORTB = 0
PORTC = 0
PORTD = 0
PORTE = 0

Symbol clockpin = RC3
Symbol datapin = RD0

Dim data As Byte
Dim type As Byte
Dim data2 As Byte
Dim data1 As Byte
Dim data0 As Byte
Dim watthour As Long


Dim empty As Bit

Dim buf1 As Word
Dim buf2 As Word
Dim buf3 As Word
Dim buf4 As Word

Dim bufdata As Bit
Dim timer As Word
Dim i As Byte
Dim incoming As Word
Dim clockflag As Bit
Dim counter As Word

Dim sendflag As Byte
Read 0, sendflag

Call poweron()
WaitMs 12000
Call test()


main:
counter = counter + 1
Call rx()

If type = 0 And data2 = 1 And data1 = 4 And data0 = 3 Then
Dim testmsg As Long
testmsg = 123456789
Call typethis(testmsg)
Endif

If type = 1 Then
watthour = data0 + (data1 * 256) + (data2 * 65536)
Call typethis(watthour)

Endif







'clear
type = 0
data2 = 0
data1 = 0
data0 = 0

Goto main
End                                               
Proc rx()

timer = 100

scan:

	If clockpin = 1 And clockflag = 0 Then
	bufdata = datapin
	statuspin = 1
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
	statuspin = 0
	clockflag = 0
	Endif
	
	If timer = 0 Then
	Goto goout  'receive timeout handler
	Endif

	If buf3.LB = 170 Then
	type = buf2.HB
	data2 = buf2.LB
	data1 = buf1.HB
	data0 = buf1.LB
	empty = 0
	Endif

	timer = timer - 1
Goto scan

goout:
	buf4 = 0
	buf3 = 0
	buf2 = 0
	buf1 = 0




End Proc                                          

