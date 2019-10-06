'Program: Display Module handler

'Descript: Used to call basic function on displaying
'numerals on a 4-digit common anode 7segment display with decimal
'point integration. Modify Pin assignments and variable
'names if necessary

'Hardware: 4 7Segments with a BCD-7Seg decoder and
'BJT driving lines for strobe.

'Software: PIC Simulator IDE

'Author: Leslie S. Caminade

'Updated: March 2016

'time to show each digit, in us

'pin assignments (this is for 16f877a)

Symbol d8 = RD7
Symbol d4 = RD6
Symbol d2 = RD5
Symbol d1 = RD4
Symbol ds4 = RC7
Symbol ds3 = RC6
Symbol ds2 = RC5
Symbol ds1 = RC4
Symbol pnt = RD0



Function display(num3 As Byte, num2 As Byte, num1 As Byte, num0 As Byte, point As Byte) As Byte

Dim strobeon As Word
strobeon = 2000

Dim counter As Byte
Dim n3 As Byte
Dim n2 As Byte
Dim n1 As Byte
Dim n0 As Byte

pnt = 1
n3 = num3
n2 = num2
n1 = num1
n0 = num0



'display part
While counter < 2
d8 = n3.3
d4 = n3.2
d2 = n3.1
d1 = n3.0
If point = 4 Then
pnt = 0
Else
pnt = 1
Endif
ds4 = 1
WaitUs strobeon
ds4 = 0

d8 = n2.3
d4 = n2.2
d2 = n2.1
d1 = n2.0

If point = 3 Then
pnt = 0
Else
pnt = 1
Endif

ds3 = 1
WaitUs strobeon
ds3 = 0

d8 = n1.3
d4 = n1.2
d2 = n1.1
d1 = n1.0

If point = 2 Then
pnt = 0
Else
pnt = 1
Endif

ds2 = 1
WaitUs strobeon
ds2 = 0

d8 = n0.3
d4 = n0.2
d2 = n0.1
d1 = n0.0

If point = 1 Then
pnt = 0
Else
pnt = 1
Endif

ds1 = 1
WaitUs strobeon
ds1 = 0

counter = counter + 1
Wend
End Function                                      
Function lamptest() As Byte
'lamp test---------------
For timer = 0 To 100 Step 1
Call display(0, 0, 0, 0, 0)
Next timer

For timer = 0 To 100 Step 1
Call display(1, 1, 1, 1, 0)
Next timer

For timer = 0 To 100 Step 1
Call display(2, 2, 2, 2, 0)
Next timer

For timer = 0 To 100 Step 1
Call display(4, 4, 4, 4, 0)
Next timer

For timer = 0 To 100 Step 1
Call display(8, 8, 8, 8, 0)
Next timer

For timer = 0 To 100 Step 1
Call display(9, 9, 9, 9, 0)
Next timer

For timer = 0 To 100 Step 1
Call display(9, 8, 7, 6, 4)
Next timer

For timer = 0 To 100 Step 1
Call display(5, 4, 3, 2, 3)
Next timer

For timer = 0 To 100 Step 1
Call display(1, 0, 0, 0, 2)
Next timer

For timer = 0 To 100 Step 1
Call display(0, 0, 0, 0, 1)
Next timer
'lamp test end-----------
End Function                                      
