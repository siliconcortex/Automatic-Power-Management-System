//----------CONVERSION FUNCTIONS---------------------------------------------------
 // converting string to Float
 float toFloat(String settingValue){
 char floatbuf[settingValue.length()+1]; //char array container
 settingValue.toCharArray(floatbuf, sizeof(floatbuf));
 float f = atof(floatbuf);
 return f;
 }
 //String to long
 long toLong(String settingValue){
 char longbuf[settingValue.length()+1];
 settingValue.toCharArray(longbuf, sizeof(longbuf)); //what is this line?
 long l = atol(longbuf);
 return l;
 }
 
 // Converting String to integer and then to boolean
 // 1 = true
 // 0 = false
 boolean toBoolean(String settingValue) {
 if(settingValue.toInt()==1){
 return true;
 } else {
 return false;
 }
 }


int tenPower(int num){

  int result;
  if(num ==0 ){
  return 1;
  }else{
    
    
    result = 10*num;
    
    return result;
  }
  
  
}

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
boolean StrContains(char *str, char *sfind)
{
    unsigned int found = 0;
    unsigned int index = 0;
    unsigned int len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}

int raise(int num, int pow){

  int result=1;
  
  for(int i = 0; i<pow; i++){
    result *=num;
  }
  
  return result;
  
}

unsigned int daysSince(unsigned int qmonth){
unsigned int dayq=0;
switch(qmonth){
case 1:
dayq = 0;
//break;
case 2:
dayq = 31;//28
//break;
case 3:
dayq = 59;//31
//break;
case 4:
dayq = 90;//30
//break;
case 5:
dayq = 120;//31
//break;
case 6:
dayq = 151;//30
//break;
case 7:
dayq = 181;//31
//break;
case 8:
dayq = 212;//31
//break;
case 9:
dayq = 243;//30
//break;
case 10:
dayq = 273;//31
//break;
case 11:
dayq = 304;//30
//break;
case 12:
dayq = 334;//31
//break;
}  
//Serial.println(dayq);
return dayq;
}


void beep(int ton,int toff,int rep){
  
  pinMode(buzPin, OUTPUT);  //buzzer
  
  for(int i = 0; i<rep;i++){
  digitalWrite(buzPin,1);
  delay(ton);
  digitalWrite(buzPin,0);
  delay(toff);
  }
  
  pinMode(buzPin, INPUT);  //buzzer
}

void extractDigits(int num){
    
 
   D[3] = num/1000; 
   D[2] = (num - D[3]*1000)/100;
   D[1] = (num-(D[3]*1000)-(D[2]*100))/10;
   D[0] = num-(D[3]*1000)-(D[2]*100)-(D[1]*10);
   
   return;
}

float squareFloat(float num){
num = num*num;
return num;
}

void serialControl(){
  
  serialData=0;
  
  if (Serial.available() > 0)
  {
    serialData = Serial.read();
  }
  
  if (serialData==1){
  energyWh=0;
  }  


}

