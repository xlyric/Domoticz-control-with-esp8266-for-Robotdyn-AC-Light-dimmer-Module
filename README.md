# Domoticz control with esp8266 for Robotdyn AC Light dimmer Module

Work with an ESP8266 and Domoticz ( and Dimmer switch ) 

Needed : 
ESP8266 
Robotdyn AC light Dimmer Module ( 1 channel ) 
Librairy : https://github.com/RobotDynOfficial/RBDDimmer
A domoticz server with one or more power information

Connection  : 
GND > GND
VCC > 3V 
ZC > D5
PWM > D6 

Control : 
http://IP/?POWER=xx
 
xx max = 99 

Optional : 
- Dallas 18b20 Connected on D7 with 3.3 or 5V power and 4.7 or 5.6Kohms resistance between D7 and power


Installation : 

you must install the wifimanager library in your library manager (https://github.com/tzapu/WiFiManager#install-through-library-manager ) 
push .ino file on the esp8266.


At the first start it will create a new wifi network ( dimmer ) pwd : dimmer 
and you can configure your network.

For Domoticz 
copy script_device_dimmer_heater_control.lua and script_time_dimmer_heater_control.lua on domoticz ( domoticz/scripts/lua ) 


change IP of the esp8266 with the dimmer  on script_device_dimmer_heater_control.lua
-------------
IP="192.168.x.x"
-------------

create on domoticz a dimmer switch
and change variables on script_time_dimmer_heater_control.lua with your configuration. 


with option Dallas 18b20 there is an alert limit send by MQTT 


---------- working process  ---- 

--- script_device_dimmer_heater_control --- 
get change on the domoticz dimmer information and send http command to change the dimmer. 

--- script_time_dimmer_heater_control --- 
script_time_dimmer_heater_control is the most simplistic script 
it will compare production with static noise value. 
and use dimmer to adapt the power on heater ( water heater, etc ) 
the power of resistive load is a static value to adapt with your load. 
if production > noise >> dimmer is adjusted else dimmer = off

--- 

Special use: can be used with my pv router https://github.com/xlyric/Pv-router
or with my 2 pzem program https://github.com/xlyric/multi-Pzem-esp8266-domoticz



changelog
-- 20200402 ; Add MQTT support, Dallas Options and max temp alert and cut the dimmer ( with trigger of 5° ) 
-- 20190908 : change 1st connection wifi process, create a network "dimmer" with password "dimmer"
-- 20190415 : add comment and translate into english 
-- 210904xx : creation and fonctionnal tests, bug corrections, limit verbosity and command sent


----- fresh install of IDE
IDE

https://www.arduino.cc/download.php?f=/arduino-nightly-windows.zip ( or other OS ) 

Dimmer Librairy

https://github.com/RobotDynOfficial/RBDDimmer

Start Arduino and open Preferences window.
Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
Open Boards Manager from Tools > Board menu and find esp8266 platform.
Select the version you need from a drop-down box.
Click install button.
Don't forget to select your ESP8266 board from Tools > Board menu after installation.


librairy of wifimanager : >> search  'wifimanager'  by tzapu in the library installation  ( ctrl + maj + i )






