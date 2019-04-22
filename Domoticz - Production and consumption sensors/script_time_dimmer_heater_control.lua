-- simplest program for adapt load to the production and noise. refresh every one minute

require "dimmer_heater"

-- main program -------------------------- 

commandArray = {}
	
--	if CONSUMPTION~=NONE then
--	Noise = 
--	end
        
	
		-- get production Intensity  
	val_production = tonumber(otherdevices_svalues[INTENSITYNAME])
	
		-- get main external intensity
	val_linky = tonumber(otherdevices_svalues[INTENSITYNAME])

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

	-- detecting activity on house. 
	if  val_linky > activityload then 

		Info_Domoticz=0

	end


		-- test for make modification is only needed 
 	if Info_Domoticz ~= val_dimmer then

		print("production = "..val_production*220)   -- convert to watt

		-- return information in Domoticz
		commandArray[DIMMERNAME]='Set Level '..Info_Domoticz

		
	end

	
return commandArray

