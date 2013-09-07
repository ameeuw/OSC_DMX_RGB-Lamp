void loadConfig(){
  Serial.println("Reading Data from EEPROM:\n");
  Serial.print("RAW-DATA:\t");  
 for (unsigned int t=0; t<sizeof(IPConfig); t++){
  *((char*)&IPConfig + t) = EEPROM.read(t);
  Serial.print(EEPROM.read(t));
 }
  Serial.println("\nDone...");
}

void saveConfig(){
  for (unsigned int t=0; t<sizeof(IPConfig); t++)
    EEPROM.write(t, *((char*)&IPConfig+t));

  Serial.println("Saved Data to EEPROM:\n");
  Serial.print("RAW-DATA:\t");
  for (unsigned int t=0; t<sizeof(IPConfig); t++)
  Serial.print(EEPROM.read(t));
  Serial.println("\nDone...");
}
