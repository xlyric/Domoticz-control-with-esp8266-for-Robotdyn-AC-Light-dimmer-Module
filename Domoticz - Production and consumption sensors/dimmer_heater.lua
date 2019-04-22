-- soft fuse security -- caliber of your fuse or for dimmer max input power.
fuse=2 -- in Ampere max
load=800 -- in watt for 220v 
valuemax = fuse * 220 / load * 100 -- max load to percent


-- Noise in ampere
Noise=100/220
-- Resistance of the load ( W )
Resistance=800/220
-- load by activity
activityload=300/220 -- in watt 

-- variables from Domoticz

-- dimmer name on domoticz ( case sensitive )
DIMMERNAME="Relay délestage"

-- production intensity name ( case sensitive )
INTENSITYNAME="intensité" -- 
-- main external intensity
LINKYINTENSITY="Intensite Linky"

-- consumption intensity name
CONSUMPTION=NONE

-- variables  for ESP8266 connection
IP="192.168.1.75"
-- IDXNAME="Relay délestage"

