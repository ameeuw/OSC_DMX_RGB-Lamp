void prm(int line){
  char buffer[80];
  strcpy_P(buffer, (char*)pgm_read_word(&(string_table[line]))); 
   Serial.println(buffer);
}

void vic(){
      prm(0);
      prm(1);
   Serial.print(IPConfig.IP[0]); Serial.print(".");
   Serial.print(IPConfig.IP[1]); Serial.print(".");
   Serial.print(IPConfig.IP[2]); Serial.print(".");
   Serial.println(IPConfig.IP[3]);
   prm(2);
   Serial.print(IPConfig.MAC[0], HEX); Serial.print(":");
   Serial.print(IPConfig.MAC[1], HEX); Serial.print(":");
   Serial.print(IPConfig.MAC[2], HEX); Serial.print(":");
   Serial.print(IPConfig.MAC[3], HEX); Serial.print(":");
   Serial.print(IPConfig.MAC[4], HEX); Serial.print(":");
   Serial.println(IPConfig.IP[5], HEX);
   prm(3);
   Serial.println(IPConfig.PORT);
   
   printed=0;
}

void ipc(){
 byte IPtemp[4];
   for(int i=4; i<7; i++) prm(i);
 
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);  //Wait for User-Input
 
 while(Serial.available()>0){
   for(int i=0;i<4;i++)
     IPtemp[i]=(Serial.parseInt());
   if (Serial.read()=='\n') break;
 }
 
 prm(7);
 Serial.print(IPtemp[0]);
 Serial.print(".");
 Serial.print(IPtemp[1]);
 Serial.print(".");
 Serial.print(IPtemp[2]);
 Serial.print(".");
 Serial.println(IPtemp[3]);
   prm(8);
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);
 while(Serial.available()>0){
   int inByte=Serial.read();
   switch (inByte){
   case 'Y':
   case 'y': for(int i=0;i<4;i++) IPConfig.IP[i]=IPtemp[i];
     break;
   case 'N':
   case 'n': ipc();
     break;
    default: break;
   }
 }

  printed=0;
}

void mac(){
 byte MACtemp[6];
for(int i=9; i<12; i++) prm(i);
 
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);  //Wait for User-Input
 
 while(Serial.available()>0){
   for(int i=0;i<6;i++)
     MACtemp[i]=(Serial.parseInt());
   if (Serial.read()=='\n') break;
 }
 
   prm(12);
 Serial.print(MACtemp[0], HEX);
 Serial.print(":");
 Serial.print(MACtemp[1], HEX);
 Serial.print(":");
 Serial.print(MACtemp[2], HEX);
 Serial.print(":");
 Serial.print(MACtemp[3], HEX);
 Serial.print(":");
 Serial.print(MACtemp[4], HEX);
 Serial.print(":");
 Serial.println(MACtemp[5], HEX);
 
   prm(13);
 
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);
 while(Serial.available()>0){
   int inByte=Serial.read();
   switch (inByte){
   case 'Y':
   case 'y': for(int i=0;i<6;i++) IPConfig.MAC[i]=MACtemp[i];
     break;
   case 'N':
   case 'n': mac();
     break;
    default: break;
   }
 }
  printed=0;
}

void poc(){
 int PORTtemp;
for(int i=14; i<17; i++) prm(i);
 
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);  //Wait for User-Input
 
 while(Serial.available()>0){
     PORTtemp=(Serial.parseInt());
   if (Serial.read()=='\n') break;
 }
 
   prm(17);
 Serial.println(PORTtemp);
 
   prm(18);
 
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);
 while(Serial.available()>0){
   int inByte=Serial.read();
   switch (inByte){
   case 'Y':
   case 'y': IPConfig.PORT=PORTtemp;
     break;
   case 'N':
   case 'n': poc();
     break;
    default: break;
   }
 }  
  printed=0;
}

void dbm(){
 if(debug==0){
   debug=1;
   prm(19);
 } 
 else{
   debug=0;
   prm(20);
 }
 printed=0;
}

void tem(){
  for(int i=21; i<24; i++) prm(i);
 
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);  //Wait for User-Input
 
 while(Serial.available()>0){
   for(int i=1;i<4;i++)
     DmxSimple.write(i,Serial.parseInt());
   if (Serial.read()=='\n') break;
 }
 
   prm(24);
 while(Serial.available()>0) Serial.read();  //Flush incoming Buffer
 while(Serial.available()<1);
 while(Serial.available()>0){
   int inByte=Serial.read();
   switch (inByte){
   case 'Y':
   case 'y':
     break;
   case 'N':
   case 'n': tem();
     break;
    default: break;
   }
 }

  printed=0;
}
