void debug(){
Serial.println("CH1:");
    for(int i =0;i<timeTableRows;i++){
      for(int j=0;j<timeTableColumns;j++){
      Serial.print(ch1[i][j]);
      Serial.print("/");
      
      
      }
    Serial.println("");
    }
    
    
    
    
    
Serial.println("CH2:");
    for(int i =0;i<timeTableRows;i++){
      for(int j=0;j<timeTableColumns;j++){
      Serial.print(ch2[i][j]);
      Serial.print("/");
      
      
      }
    Serial.println("");
    }
}


