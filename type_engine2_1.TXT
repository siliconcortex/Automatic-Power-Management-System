'Program: Text message low-level commands

'Descript: Used to call basic function on typing
'messages on cellphone specified. defines low-level
'pressing commands

'Hardware: Cellphone connection

'Software: PIC Simulator IDE

'Author: Leslie S. Caminade

'Updated: March 2016


Const timedownlong = 2000
Const timedown = 80
Const timeup = 80
Symbol one = RB5
Symbol four = RB4
Symbol seven = RB3
Symbol two = RB2
Symbol five = RB1

Symbol eight = RD7
Symbol three = RD6
Symbol six = RD5
Symbol nine = RD4

Symbol zero = RC7
Symbol left = RC6
Symbol up = RC5
Symbol ok = RC4
Symbol power = RD3


Symbol statuspin = RA0

Function press(data As Byte) As Byte
Select Case data
Case 0
zero = 1
Case 1
one = 1
Case 2
two = 1
Case 3
three = 1
Case 4
four = 1
Case 5
five = 1
Case 6
six = 1
Case 7
seven = 1
Case 8
eight = 1
Case 9
nine = 1
Case 10
ok = 1
Case 11
left = 1
Case 12
up = 1
Case 13
power = 1
EndSelect
WaitMs timedown
PORTC = 0
PORTD = 0
PORTB = 0
WaitMs timeup
End Function                                      
Function hold(data As Byte) As Byte
Select Case data
Case 0
zero = 1
Case 1
one = 1
Case 2
two = 1
Case 3
three = 1
Case 4
four = 1
Case 5
five = 1
Case 6
six = 1
Case 7
seven = 1
Case 8
eight = 1
Case 9
nine = 1
Case 10
ok = 1
Case 11
left = 1
Case 12
up = 1
Case 13
power = 1
EndSelect
WaitMs timedownlong
PORTC = 0
PORTD = 0
PORTB = 0
WaitMs timeup
End Function                                      
Proc poweron()
power = 1
WaitMs 3000
power = 0
End Proc                                          
Proc test()
statuspin = 1
Dim i As Byte
Dim j As Byte
For j = 0 To 9 Step 1
For i = 0 To 9 Step 1
Call press(i)
Next i
Next j

Call press(13)
statuspin = 0
End Proc                                          
Proc send()
	Call press(10)
	Call press(12)
	Call press(10)

	'09488913924
	Call press(0)
	Call press(9)
	Call press(4)
	Call press(8)
	Call press(8)
	Call press(9)
	Call press(1)
	Call press(3)
	Call press(9)
	Call press(2)
	Call press(4)
	
	If sendflag = 1 Then
	Call press(10)
	Call press(10)
	Endif

	WaitMs 1000
	Call press(13)


	
End Proc                                          
