An Arduino based Car Controlled with a Mobile Phones Accelerometer

For accomplish to communications between mobile phone and the car, there ara several process. First ESP8266 and the mobile
phone should connect to the same WiFi. Basicly, Mobile Phone sends the x and y directional measurements to ESP8266 via
WebSocket connections which WebSocket server created by the ESP8266. ESP8266 collects all data and sends directly to Arduino 
Uno via Serial Port.When finally data comes to Arduino, it parses them and uses an algortihm to decide which motor moves to 
wich direction and at wich speed. With PWM and logic signals and the help of the H bridged motor driver L298N, car moves as 
like the mobile phones direction.


Components:
- Arduino Uno
- L298N Motor Driver
- ESP8266-01 WiFi Module
- 4 DC Motors
- Wheels and some platforms

Since I couldn't find a propper online circut schematic draw service, I will try to tell the connections here.

ESP8266-01   to   Arduino UNO

VCC  ---------------- 3.3 V Output

GND  ----------------  GND

EN   ----------------  3.3 V Output

RX   ---------------- TX

TX   ---------------- RX


L298N      to     Arduino UNO
5V   ----------------   5V
GND  ----------------   GND
IN1 ------------------  8
IN2 ------------------  6
IN3 ------------------  5
IN4 ------------------  7
ENA ------------------ 10
ENB ------------------ 9

L298N can control two motors but I connect every output with two motors so this way I could managed to conrol 4 motors. I 
think you should use at least 12V of supply in case of the situations thah can appear from tha lack of power.
