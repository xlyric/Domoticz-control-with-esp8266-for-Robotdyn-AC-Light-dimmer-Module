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

Installation : 
you must install the wifimanager library in your library manager (https://github.com/tzapu/WiFiManager#install-through-library-manager ) 
push .ino file on the esp8266. at the first start it will create a new wifi network ( dimmer ) pwd : dimmer 
and you can configure your network.

copy script_device_dimmer_heater_control.lua and script_time_dimmer_heater_control.lua on domoticz ( domoticz/scripts/lua ) 

change IP of the esp8266 with the dimmer  on script_device_dimmer_heater_control.lua
-------------
IP="192.168.x.x"
-------------

create on domoticz a dimmer switch
and change variables on script_time_dimmer_heater_control.lua with your configuration. 

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
-- 20190908 : change 1st connection wifi process, create a network "dimmer" with password "dimmer"
-- 20190415 : add comment and translate into english 
-- 210904xx : creation and fonctionnal tests, bug corrections, limit verbosity and command sent








