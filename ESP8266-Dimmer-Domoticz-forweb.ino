/**************
 *  RobotDyn
 *  Dimmer Library
 *  **************
 *  Updated By Cyril Poisssonnier 2019 
 * 
 * The following sketch is meant to define the dimming value through the serial port of the controller, 
 * using USE_SERIAL.begin 
 *    void printSpace() function is used for adding of space after functional data
 *    void loop()  serial port evaluator, used to register and define values in dimmer.setPower(outVal);
 *    
 * 
 *  ---------------------- OUTPUT & INPUT Pin table ---------------------
 *  +---------------+-------------------------+-------------------------+
 *  |   Board       | INPUT Pin               | OUTPUT Pin              |
 *  |               | Zero-Cross              |                         |
 *  +---------------+-------------------------+-------------------------+
 *  | Lenardo       | D7 (NOT CHANGABLE)      | D0-D6, D8-D13           |
 *  +---------------+-------------------------+-------------------------+
 *  | Mega          | D2 (NOT CHANGABLE)      | D0-D1, D3-D70           |
 *  +---------------+-------------------------+-------------------------+
 *  | Uno           | D2 (NOT CHANGABLE)      | D0-D1, D3-D20           |
 *  +---------------+-------------------------+-------------------------+
 *  | ESP8266       | D1(IO5),    D2(IO4),    | D0(IO16),   D1(IO5),    |
 *  |               | D5(IO14),   D6(IO12),   | D2(IO4),    D5(IO14),   |
 *  |               | D7(IO13),   D8(IO15),   | D6(IO12),   D7(IO13),   |
 *  |               |                         | D8(IO15)                |
 *  +---------------+-------------------------+-------------------------+
 *  | ESP32         | 4(GPI36),   6(GPI34),   | 8(GPO32),   9(GP033),   |
 *  |               | 5(GPI39),   7(GPI35),   | 10(GPIO25), 11(GPIO26), |
 *  |               | 8(GPO32),   9(GP033),   | 12(GPIO27), 13(GPIO14), |
 *  |               | 10(GPI025), 11(GPIO26), | 14(GPIO12), 16(GPIO13), |
 *  |               | 12(GPIO27), 13(GPIO14), | 23(GPIO15), 24(GPIO2),  |
 *  |               | 14(GPIO12), 16(GPIO13), | 25(GPIO0),  26(GPIO4),  |
 *  |               | 21(GPIO7),  23(GPIO15), | 27(GPIO16), 28(GPIO17), |
 *  |               | 24(GPIO2),  25(GPIO0),  | 29(GPIO5),  30(GPIO18), |
 *  |               | 26(GPIO4),  27(GPIO16), | 31(GPIO19), 33(GPIO21), |
 *  |               | 28(GPIO17), 29(GPIO5),  | 34(GPIO3),  35(GPIO1),  |
 *  |               | 30(GPIO18), 31(GPIO19), | 36(GPIO22), 37(GPIO23), |
 *  |               | 33(GPIO21), 35(GPIO1),  |                         |
 *  |               | 36(GPIO22), 37(GPIO23), |                         |
 *  +---------------+-------------------------+-------------------------+
 *  | Arduino M0    | D7 (NOT CHANGABLE)      | D0-D6, D8-D13           |
 *  | Arduino Zero  |                         |                         |
 *  +---------------+-------------------------+-------------------------+
 *  | Arduino Due   | D0-D53                  | D0-D53                  |
 *  +---------------+-------------------------+-------------------------+
 *  | STM32         | PA0-PA15,PB0-PB15       | PA0-PA15,PB0-PB15       |
 *  | Black Pill    | PC13-PC15               | PC13-PC15               |
 *  | BluePill      |                         |                         |
 *  | Etc...        |                         |                         |
 *  +---------------+-------------------------+-------------------------+
 *  
 *  
 *  Work for dimmer on Domoticz or Web command :
 *  http://URL/?POWER=XX 
 *  0 -> 99 
 *  more than 99 = 99 
 *  
 *    
 *  Update 2019 04 28 
 *  correct issue full power for many seconds at start 
 */




#include <RBDdimmer.h>//
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  /// librairy : >> search  'wifimanager'  by tzapu

/***************************
 * Begin Settings
 **************************/

// WIFI
// At first launch, create wifi network 'dimmer'  ( pwd : dimmer ) 

/// Webserver init
ESP8266WebServer server ( 80 );

int puissance = 0 ;

//#define USE_SERIAL  SerialUSB //Serial for boards whith USB serial port
#define USE_SERIAL  Serial
#define outputPin  D6 
#define zerocross  D5 // for boards with CHANGEBLE input pins

/***************************
 * End Settings
 **************************/



///// init Dimmer

dimmerLamp dimmer(outputPin, zerocross); //initialase port for dimmer for ESP8266, ESP32, Arduino due boards
//dimmerLamp dimmer(outputPin); //initialase port for dimmer for MEGA, Leonardo, UNO, Arduino M0, Arduino Zero

int outVal = 0;

///

String getPage(){
  String page = "<html lang=fr-FR><head>";
  page += "<title>ESP8266 Dimmer </title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
  page += "</head><body><h1>ESP8266 Dimmer</h1>";
  page += "<h3>Use : URL?POWER=% </h3>";
  page += "<ul><li>puissance : ";
  page += puissance;
  page += " %</li></ul>";
  page += "</body></html>";
  return page;
}



void handleRoot(){ 
  if ( server.hasArg("POWER") ) {
   handleSubmit();
    
  } else {
    server.send ( 200, "text/html", getPage() );
  }
}

void handleSubmit() {
  // Actualise le GPIO / Update GPIO 
  String PowerValue;
  int ReturnPower;
  PowerValue = server.arg("POWER");
  ReturnPower = PowerValue.toInt();
  dimmer.setPower(ReturnPower);
  Serial.println("Set power "); Serial.print(PowerValue);
  server.send ( 200, "text/html", getPage() );
  
    }


void setup() {
  USE_SERIAL.begin(9600); 

  /// Correction issue full power at start
  pinMode(outputPin, OUTPUT); 
  digitalWrite(outputPin, LOW);

  
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
  dimmer.setPower(outVal); 
  
  USE_SERIAL.println("Dimmer Program is starting...");

  /// wifi 
  WiFiManager wifiManager;
  wifiManager.autoConnect("dimmer", "dimmer");
  

 // connexion OK, we start web server // Start the server
  
  server.on ( "/", handleRoot );
  
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  
  USE_SERIAL.println("Set value");
}

void printSpace(int val)
{
  if ((val / 100) == 0) USE_SERIAL.print(" ");
  if ((val / 10) == 0) USE_SERIAL.print(" ");
}

void loop() {
  int preVal = outVal;

  if (USE_SERIAL.available())
  {
    int buf = USE_SERIAL.parseInt();
    if (buf != 0) outVal = buf;
    delay(200);
  }
 // dimmer.setPower(outVal); // setPower(0-100%);

  if (preVal != outVal)
  {
    USE_SERIAL.print("lampValue -> ");
    printSpace(dimmer.getPower());
    USE_SERIAL.print(dimmer.getPower());
    USE_SERIAL.println("%");

  }
  delay(50);

server.handleClient();

puissance = dimmer.getPower();

}
