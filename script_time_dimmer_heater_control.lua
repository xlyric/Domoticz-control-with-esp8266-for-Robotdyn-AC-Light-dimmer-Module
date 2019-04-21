-- simplest program for adapt load to the production and noise. refresh every one minute

-- variables ----- 
-- Noise in ampere 
Noise=100/220
-- Resistance of the load ( W ) 
Resistance=800/220

-- security -- caliber of your fuse or for dimmer max input power. 
fuse=2 --Ampere max

-- variables from Domoticz 

-- dimmer name on domoticz ( case sensitive )
DIMMERNAME="Relay délestage"
-- production intensity name ( case sensitive )
POWERNAME="intensité"

-- main program -------------------------- 

commandArray = {}
		
		-- get production Intensity  
	val_production = tonumber(otherdevices_svalues[POWERNAME])
	
		-- get dimmer information
	val_dimmer=tonumber(otherdevices_svalues[DIMMERNAME])

	-- security max input power or fuse
        if val_production > fuse then 
		val_production = fuse
	end


	if val_production > Noise  then 
		
		-- calcul needed power for the  dimmer
		Dimmer_Power=val_production-Noise
		
		-- converte information 0-100 
		-- Command_Dimmer=math.floor(Dimmer_Power*1023/Resistance)
		Info_Domoticz=math.floor(Dimmer_Power*100/Resistance)


	else 
		-- Command_Dimmer=0
		Info_Domoticz=0

	end

		-- test for make modification is only needed 
	if Info_Domoticz ~= val_dimmer then

		print("production = "..val_production*220)   -- convert to watt
		-- return information in Domoticz
		commandArray[DIMMERNAME]='Set Level '..Info_Domoticz

		
		-- et sur le controleur ( plus necessaire ) 
		-- print("commande faite à "..Info_Domoticz.."%")
	end

	
return commandArray

