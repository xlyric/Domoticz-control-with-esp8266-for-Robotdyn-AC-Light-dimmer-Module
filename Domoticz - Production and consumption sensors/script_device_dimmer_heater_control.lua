-- Control ESP8266 with Dimmer

-- Connection  : 
-- GND > GND
-- VCC > 3V 
-- ZC > D5
-- PWM > D6 


-- main code 

-- All configuration is in dimmer_heater.lua
require "dimmer_heater"

commandArray = {}

if (devicechanged[DIMMERNAME]) then

		-- get Domoticz Dimmer information switch 
    	val_production = tonumber(otherdevices_svalues[DIMMERNAME])

	if val_production > valuemax then
		val_production = valuemax
		commandArray[DIMMERNAME]='Set Level '..val_production
		print("security mode")
	end
		

		-- send information to esp8266 dimmer
	commandArray['OpenURL']=IP..'/?POWER='..val_production
		
		-- log action
	print("commande send to :"..val_production.."%")

end
	
return commandArray

