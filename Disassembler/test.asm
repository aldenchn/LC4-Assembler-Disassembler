.DATA
.ADDR x4020
.FILL #1
.FILL #2

.CODE
.ADDR x0000
STARTLABEL
SUB R1 R2 R3
ADD R0 R0 #1
MUL R1 R2 R3
END
