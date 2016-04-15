# ESP8266-Web-LED
A web based LED built on the Arduino platform with a simple AJAX driven interface.

## Installation Requirements
1. ESP8266 (preferably one with a breakout so you have access to the pins)
2. LED
3. Arduino IDE v1.6.7
    Required library:
	* Additional Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
   * Then the board named ESP8266 by ESP8266 Community

## Installation instructions
1. After installing the required esp8266 board you will want to select the appropriate board.
2. Open the arduino sketch. Be sure to update your wireless SSID and Password
3. Upload the sketch to your ESP8266
4. Navigate to http://LED.local/
5. ???
6. Enjoy your web connected LED, maybe open a port in your firewall and control your ESP remotely. More importantly, use this as an exercise to familiarize yourself with the ESP8266.

### Have fun!
 
 

## Help
Troubleshooting step 4.

    Open the serial monitor and the ESP should tell you its IP on your network or if it had difficulty connecting.
