======  GENERAL INFORMATION ======  

The project was created as a part of subject.  
Basics of Embedded Systems Programming(PPSW) at AGH University of Krakow.  
The instructions and code templates were delivered by prof. dr hab. Miroslaw Zoladz.  
The target device is  ARM LPC2132 with additional Servo kit.  
  
====== SETUP ======  

There are some pins that need to be connected between ARM and Servo controller.  
GND - GND  
DETECTOR_OUT - 0.10  
PO-0 - 1.16  
PO-1 - 1.17  
PO-2 - 1.18  
PO-3 - 1.19  

====== HOW IT WORKS ======  

The project covers basic GPIO, Servo and UART transmission managment.  
When program is finished loading Servo is being callibrated.  
When controller is set to trasmission mode (RST and ISP off)  
it realises simple timer functionality and sends communicates through UART:  
-sec 0x<sec_val>  
-min 0x<min_val>  

User can communicate back with the board:  
-calc 0x<num_val> - returns 'calc 0x<num_val*2>'  
-callib           - callibrates servo  
-goto 0x<pos>     - sets position of servo to <pos>  
-id               - makes board identify itself  

Any other communicate will be aswered "Unknown command".

