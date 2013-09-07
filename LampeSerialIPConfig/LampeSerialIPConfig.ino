#include <SPI.h>
#include <Ethernet.h>
#include <DmxSimple.h>
#include <EEPROM.h>
#include <ArdOSC.h>
#include <avr/pgmspace.h>

prog_char string_0[] PROGMEM = "___________\n  Config:  \n-----------\n";
prog_char string_1[] PROGMEM = "IP-Address:\t";
prog_char string_2[] PROGMEM = "MAC-Address:\t";
prog_char string_3[] PROGMEM = "PORT-Number:\t";

prog_char string_4[] PROGMEM = "__________\nIP-Config:\n----------";
prog_char string_5[] PROGMEM = "Enter the IP seperated by Comma (',')";
prog_char string_6[] PROGMEM = "I.e.: ' 192,168,1,1 '";
prog_char string_7[] PROGMEM = "IP-Address set to:";
prog_char string_8[] PROGMEM = "\nIs this IP-Address Correct? (Y/N)\n";

prog_char string_9[] PROGMEM = "___________\nMAC-Config:\n-----------";
prog_char string_10[] PROGMEM = "Enter the MAC seperated by Comma (',')";
prog_char string_11[] PROGMEM = "I.e.: ' 255,255,255,255,255,255 '";
prog_char string_12[] PROGMEM = "MAC-Address set to:";
prog_char string_13[] PROGMEM = "\nIs this MAC-Address Correct? (Y/N)\n";

prog_char string_14[] PROGMEM = "____________\nPORT-Config:\n------------";
prog_char string_15[] PROGMEM = "Enter the PORT-Number";
prog_char string_16[] PROGMEM = "I.e.: ' 10000 '";
prog_char string_17[] PROGMEM = "PORT set to:";
prog_char string_18[] PROGMEM = "\nIs this PORT-Number Correct? (Y/N)\n";

prog_char string_19[] PROGMEM = "\nDEBUG-Mode ENABLED";
prog_char string_20[] PROGMEM = "\nDEBUG-Mode DISABLED";

prog_char string_21[] PROGMEM = "________\nDMX-TEST:\n--------";
prog_char string_22[] PROGMEM = "Enter RGB-Values seperated by Comma (',')";
prog_char string_23[] PROGMEM = "I.e.: ' 255,255,255 '";
prog_char string_24[] PROGMEM = "\nExit TEST-MODE? (Y/N)\n";

prog_char string_25[] PROGMEM = "\nPress 'I' for IP-Config, 'M' for MAC-Config and 'P' for PORT-Config";
prog_char string_26[] PROGMEM = "Press 'V' to VIEW Config, 'L' to LOAD and 'S' to SAVE Config to EEPROM";
prog_char string_27[] PROGMEM = "Press 'D' to enable/disable DEBUG-Mode, 'T' to enter TEST-Mode";

PROGMEM const char *string_table[] = 	   // change "string_table" name to suit
{   
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5,
  string_6,
  string_7,
  string_8,
  string_9,
  string_10,
  string_11,
  string_12,
  string_13,
  string_14,
  string_15,
  string_16,
  string_17,
  string_18,
  string_19,
  string_20,
  string_21,
  string_22,
  string_23,
  string_24,
  string_25,
  string_26,
  string_27,
};

struct ConfigStruct {
  byte IP[4];
  byte MAC[6];
  int PORT;
} 
//Default Values
IPConfig={
  { 10, 150, 56, 175 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED },
  10000
};

OSCServer server;
byte printed=0;
byte debug=0;

void setup(){
 Serial.begin(9600); 
 loadConfig();
 
 Ethernet.begin(IPConfig.MAC ,IPConfig.IP); 
 server.begin(IPConfig.PORT);
 server.addCallback("/rgb",&RGBset);
 
 DmxSimple.usePin(3);
 DmxSimple.maxChannel(6);
 for (int i=1;i<7;i++)  DmxSimple.write(i,0);
}

void loop(){
 if(printed==0){
   for(int i=25; i<28; i++){
   prm(i);
   }
   printed=1;}
 
 if(server.aviableCheck()>0)
  if(debug==1)Serial.println("incoming msg!");
}

void RGBset(OSCMessage *_mes){
  if(debug==1)logIp(_mes);
  if(debug==1)logOscAddress(_mes);

  int tmpI=_mes->getArgInt32(0);
  int tmpII=_mes->getArgInt32(1);
  int tmpIII=_mes->getArgInt32(2);  
  
  DmxSimple.write(1, tmpI);
  delay(20);
  DmxSimple.write(2, tmpII);
  delay(20);
  DmxSimple.write(3, tmpIII);
  
  if(debug==1){
  Serial.print("RGB Argument is: (");
  Serial.print(tmpI);
  Serial.print(" , ");
  Serial.print(tmpII);
  Serial.print(" , ");
  Serial.print(tmpIII);
  Serial.println(")");}
}

void logIp(OSCMessage *_mes){
  byte *ip = _mes->getIpAddress();
  Serial.print("IP:");
  Serial.print(ip[0],DEC);
  Serial.print(".");
  Serial.print(ip[1],DEC);
  Serial.print(".");
  Serial.print(ip[2],DEC);
  Serial.print(".");
  Serial.print(ip[3],DEC);
  Serial.print(" ");
}

void logOscAddress(OSCMessage *_mes){
  Serial.println(_mes->getOSCAddress());
}
void serialEvent(){
   int inByte=Serial.read();
   switch (inByte) {
    case 'i':
    case 'I': ipc();
     break;
    case 'm':
    case 'M': mac();
     break;
    case 'p':
    case 'P': poc();
     break;
    case 'v':
    case 'V': vic();
     break;
    case 'l':
    case 'L': loadConfig(); printed=0;
     break;
    case 's':
    case 'S': saveConfig(); printed=0;
     break;
    case 'd':
    case 'D': dbm();
     break;
    case 't':
    case 'T': tem();
     break;
    default: break;
   }
}
