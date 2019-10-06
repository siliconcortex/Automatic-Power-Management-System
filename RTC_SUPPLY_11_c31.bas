'Program: Improvised PIC based RTC
'for PIC16f628a

'Descript: RTC functions for PIC16f628a 
'which has low cost and low power requirements

'Hardware:connection to Gizduino IOT-644

'Software: PIC Simulator IDE

'Author: Leslie S. Caminade

'COMMUNICATION NOTE:
'uses an improvised ACTIVE HIGH UNIPOLAR SCHEME which anticipates
'an interrupt, then
'a full 8-bit HIGH burst as start bit value = 255
'then the next 8bits as an ADDRESS or internal data type (saved in variable "type")
'then the rest as the data, grouped by 8 bits.

TRISA = ffh
TRISB = 11100111b

Const ttime = 250  'tx time in us
Dim x As Byte
Dim sec As Byte
Dim min As Byte
Dim hour As Byte
Dim day As Byte
Dim month As Byte
Dim year As Byte
Dim powerstate As Bit
Dim timer As Byte
Dim timerflag As Byte
Dim secondscalibrate As Byte

Dim queryvar As Byte
Symbol blinkpin = RB4
Symbol datapin = RB1
Symbol clockpin = RB2
Symbol powerpin = RB3
Symbol switchpin = RB5
Symbol powerdetectpin = RA6
clockpin = 0
datapin = 0

powerstate = 0
timer = 5
'set
Read 0, min
Read 1, hour
Read 2, day
Read 3, month
Read 4, year
Read 5, secondscalibrate

INTCON.INTE = 1
Enable
powerpin = 0

main:


If powerdetectpin = 0 Then
powerpin = 0
Endif


'power
If switchpin = 1 Then


	If powerpin = 0 And powerdetectpin = 1 Then  'if off
	powerpin = 1  'on
	Goto out
	Endif
	
	If powerpin = 1 Then  'if on
	timerflag = 1
	Config datapin = Output
	Config clockpin = Output
	datapin = 1
	clockpin = 1
	Config datapin = Input
	Config clockpin = Input
	Endif

Endif
out:

If timerflag = 1 Then
	timer = timer - 1
	'send gizduinotrigger
	If timer = 0 Then
	powerpin = 0  'off
	timer = 5
	timerflag = 0
	Endif
	
	If timer < 3 Then
	datapin = 0
	clockpin = 0
	Endif
Endif


WaitMs 995  'calibrate
blinkpin = 1
sec = sec + 1
WaitUs 4500
If secondscalibrate > 0 Then
WaitUs secondscalibrate
Endif
'calibrate to match 1 second
blinkpin = 0


If sec > 59 Then
sec = 0
min = min + 1

	If min > 59 Then
	min = 0
	hour = hour + 1
		
		If hour > 23 Then
		hour = 0
		day = day + 1
		Endif

			queryvar = dayq(month, year)
			If day > queryvar Then
			day = 1
			month = month + 1

				If month > 12 Then
				month = 1
				year = year + 1
					
					If year > 4 Then
					year = 1
					Endif

				Endif
			
			Endif

	Endif

Endif

Goto main
End                                               
On Interrupt
Save System
datapin = 0
clockpin = 0
Config datapin = Output
Config clockpin = Output
'transmit code
'WaitMs 5
'START
For x = 0 To 7 Step 1
datapin = 1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime
Next x

'MIN
datapin = min.7
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.6
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.5
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.4
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.3
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.2
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = min.0
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime



'HOUR
datapin = hour.7
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.6
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.5
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.4
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.3
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.2
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = hour.0
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

'day
datapin = day.7
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.6
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.5
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.4
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.3
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.2
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = day.0
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

'month
datapin = month.7
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.6
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.5
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.4
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.3
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.2
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = month.0
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

'year
datapin = year.7
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.6
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.5
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.4
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.3
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.2
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

datapin = year.0
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime

'END
For x = 0 To 7 Step 1
datapin = 1
clockpin = 1
WaitUs ttime
clockpin = 0
WaitUs ttime
Next x
datapin = 0
INTCON.INTF = 0


Resume                                            
Function dayq(qmonth As Byte, qyear As Byte) As Byte
Select Case qmonth
Case 1
dayq = 31
Case 2
	If qyear = 4 Then
	dayq = 29
	Else
	dayq = 28
	Endif
Case 3
dayq = 31
Case 4
dayq = 30
Case 5
dayq = 31
Case 6
dayq = 30
Case 7
dayq = 31
Case 8
dayq = 31
Case 9
dayq = 30
Case 10
dayq = 31
Case 11
dayq = 30
Case 12
dayq = 31
Case Else
dayq = 30
EndSelect
End Function                                      
