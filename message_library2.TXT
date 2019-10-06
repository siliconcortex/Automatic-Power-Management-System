'Program: Text message library

'Descript: Used to call basic function on typing
'messages on cellphone specified. defines preset messages
'pressing commands

'Hardware: Cellphone connection

'Software: PIC Simulator IDE

'Author: Leslie S. Caminade

'Updated: March 2016



Proc overload()
Call press(13)  'whatever exit
Call press(11)  'left

'type
Call hold(0)  'o
Call press(8)  'v
Call press(1)  'R

'SEND
Call send()

End Proc                                          
Proc powerfail()
Call press(13)  'whatever exit
Call press(11)  'left

'type
Call hold(0)  'o
Call hold(0)  'o
Call hold(0)  'o

'SEND
Call send()

End Proc                                          

Proc writetest()
Call press(13)  'whatever exit
Call press(11)  'left

'type
Call hold(0)  'o
Call hold(1)  'o
Call hold(2)  'o
Call hold(3)  'o
Call hold(4)  'o
Call hold(5)  'o
Call hold(6)  'o
Call hold(7)  'o
Call hold(8)  'o
Call hold(9)  'o
'SEND
Call send()

End Proc                                          
Proc typethis(num As Long)
Call press(13)  'whatever exit
Call press(11)  'left

Dim numleft As Long
Dim divisor As Long
Dim digit As Byte
Dim a As Byte
Dim j As Byte
numleft = num

For a = 0 To 8 Step 1

Select Case a
Case 0
divisor = 100000000
Case 1
divisor = 10000000
Case 2
divisor = 1000000
Case 3
divisor = 100000
Case 4
divisor = 10000
Case 5
divisor = 1000
Case 6
divisor = 100
Case 7
divisor = 10
Case 8
divisor = 1

EndSelect

digit = numleft / divisor
numleft = numleft - (digit * divisor)
Call hold(digit)
Next a



'SEND
Call send()

End Proc                                          

