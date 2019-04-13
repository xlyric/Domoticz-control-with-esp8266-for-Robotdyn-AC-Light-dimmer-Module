-- Control ESP8266 with Dimmer

-- variables l'ESP8266
IP="192.168.1.75"

commandArray = {}

if (devicechanged['Relay délestage']) then

		-- recuperation de la puissance produite 
	val_production = tonumber(otherdevices_svalues['Relay délestage'])
--	val_production=otherdevices['0062']
--	print("production = "..val_production*220)   

		commandArray['OpenURL']=IP..'/?POWER='..val_production
		print("commande faite à "..Info_Domoticz.."%")
end
	
return commandArray

