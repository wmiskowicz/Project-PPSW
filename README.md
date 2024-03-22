======  GENERAL INFORMATION ======

The project was created as a part of subject
Basics of Embedded Systems Programming(PPSW) at AGH University of Krakow.
The instructions and code templates were delivered by prof. dr hab. Miroslaw Zoladz.
The target device is  ARM LPC2132 with additional Servo kit.


====== HOW IT WORKS ====== 

The project covers basic GPIO, Servo and UART transmission managment.
When program is finished loading Servo is being callibrated.
When controller is set to trasmission mode it realises simple timer functionality.
It sends through UART communicates:
-sec 0x<sec_val>
-min 0x<min_val>

User can communicate back with the board:
-calc 0x<num_val> - returns calc 0x<num_val*2>
-callib           - callibrates servo
-goto 0x<num>     - sets position of servo to <num>
-id               - makes board identify itself

Any other communicate will be aswered "Unknown command".

