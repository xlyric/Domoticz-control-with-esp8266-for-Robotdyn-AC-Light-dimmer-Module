-- code de gestion de la puissance sur le dimmer en fonction de la production solaire

-- variables
-- bruit de la maison ( A ) >> 250W
Bruit=100/220
-- Resistance ( W ) 
Resistance=800/220
-- variables l'ESP8266
-- GPIO=14
IP="192.168.1.75"

commandArray = {}
		
		-- recuperation de la puissance produite 
	val_production = tonumber(otherdevices_svalues['intensité'])
--	val_production=otherdevices['0062']
	print("production = "..val_production*220)   
	val_dimmer=tonumber(otherdevices_svalues['Relay délestage'])


	if val_production > Bruit  then 
		
		-- calcul de la puissance souhaité sur le dimmer
		Dimmer_Power=val_production-Bruit
		
		-- convertion valeur 0-1023 
		Command_Dimmer=math.floor(Dimmer_Power*1023/Resistance)
		Info_Domoticz=math.floor(Dimmer_Power*100/Resistance)

	else 
		Command_Dimmer=0
		Info_Domoticz=0

	end

		if Command_Dimmer ~= val_dimmer then

		-- retour de l'info dans domoticz
		commandArray['Relay délestage']='Set Level '..Info_Domoticz

		
		-- et sur le controleur ( plus necessaire ) 
-- 		commandArray['OpenURL']=IP..'/control?cmd=pwm,'..GPIO..','..Command_Dimmer
		print("commande faite à "..Info_Domoticz.."%")
		end


	
return commandArray

