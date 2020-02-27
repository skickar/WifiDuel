# WifiDuel
Shoot em up wifi game

RSA Wi-Fi Duel Game

To use this game:

1) wire two esp8266 boards together: Pin D1 to D2, D2 to D1, and GND to GND.
2) Flash the AP sketch to one board, the Reciever sketch to the other
3) Connect the board flashed with the AP sketch, open a serial monitor in Arduino with baud rate 115200
4) Send the command: "ap -ssid "NetworkName" -password "NetworkPassword" -channel 11" over serial
(make sure to change the NetworkName and NetworkPassword
5) Check the output, if you see "Connected" then handshakes are being generated. If you see "error", try sending again
