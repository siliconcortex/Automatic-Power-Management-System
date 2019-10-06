/*--------------------------------------------------------------
 Program:      Automatic Power Management System
 
 Gizduino IOT 644 interfaced with PIC16f877a and PIC16f628a to
 for a Ethernet-based power management system.
 
 Hardware: Gizduino IOT644 board attached with
 PIC16f877a and PIC16f628a. 
 Should work with other Gizduinos and
 compatible Ethernet shields.
 2Gb to 8Gb micro SD card formatted FAT32.
 A0 as power measurement pin, A5 as buzzer pin, and several
 DIOs as comms to PICs. See declarations for specifics. 
 
 Software:     Developed using Arduino 1.0.6 software
 Should be compatible with Arduino 1.0 +
 SD card contains web page called index.txt,

 several setting and configuration files; savefile.txt
 ,including the file that contains
 the schedule for the scheduler feature, schedule.txt,
 
 Secondary processors developed using PIC Simulator IDE
 and using PICkit2 USB Flash and EEPROM programmer.
 
 
 References:   
 - WebServer example by David A. Mellis and 
 modified by Tom Igoe
 - SD card examples by David A. Mellis and
 Tom Igoe
 - Ethernet library documentation:
 http://arduino.cc/en/Reference/Ethernet
 - SD Card library documentation:
 http://arduino.cc/en/Reference/SD
 -Arduino Ajax webserver tutorials by W.A. Smith, 
 http://startingelectronics.com
 -Several other minor sources
 
 Date:           June 2015
 Last Modified:  January 2016
 
 Author:         Leslie S. Caminade     
 --------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
//#include "RTClib.h"

 
// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   110
// size of buffer that stores the incoming string
#define TXT_BUF_SZ   50
//power timer interval
#define interval1 1000
#define interval2 15000
#define interval3 1000
//sdcard CS
#define sdcard 27
#define CBDelay 10

unsigned long temp[2];
int serialData=0;


//LONGBYTE CONV
long long_conv;
byte byte_conv[4];  



//POWER and ENERGY VARIABLES
long powerRaw;
float actualPower;
float energymicroWh=0;
long energyWh=0;
int maxPower = 412;
long energykWh=0;
int energyFactor = 278; //scaling factor for energy measurement 
float powerFactor; //scaling factor for displayed power, not used in measurement
//powerfactor is nonlinear, see code and documentation for details of calibration
float ADCPowerLimit = 750.0; //holds max power value, in binary 10-bit format


//POWER AND ENERGY VARIABLES 2
long powerRaw2;
float actualPower2;
int maxPower2 = 412;
int energyFactor2 = 278; //scaling factor for energy measurement 
float powerFactor2; //scaling factor for displayed power, not used in measurement
//powerfactor is nonlinear, see code and documentation for details of calibration
float ADCPowerLimit2 = 750.0; //holds max power value, in binary 10-bit format


float costPerkWh = 8; //depending on dasureco
float costPerHour = 0; //estimated cost per hour

//ETHERNET VARIABLES
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(169, 254, 7, 7); // IP address
EthernetServer server(80);  // port
File webFile;               // the web page file on the SD card
char HTTP_req[REQ_BUF_SZ] = {
  0}; // buffered HTTP request 
//char HHTP_req_cache[REQ_BUF_SZ] = {0}; //cache for request handling
char req_index = 0;              // index into HTTP_req 
char txt_buf[TXT_BUF_SZ] = {
  0};  // buffer to save text to
boolean HMDATAreq = 0; //stores a pending HM DATA request flag
String HMLoadStr = ""; //storage for string xml response
char alphabet[] = {
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

byte ethernetManualFlag = 0; //flags any manual control done via ethernet
byte ethernetManualFlag2 = 0; //flags any manual control done via ethernet


//STATUS VARIABLES  
boolean LED_state[4] = {
  0}; // stores the states of the LEDs (temp)
boolean AUTO1 = 0;    //stores by channel flag
byte autoTemp;
boolean MODE1[10] = {
  0}; //stores by-slot mode flags (1 is to-ON, 0 is to-OFF)
boolean CH1AUTO = 0; //stores status of ch1 if auto is on - submissive to LED_state[0]
boolean CH1MANUAL = 0; //stores status of ch1 if auto is on - submissive to LED_state[0]
//unsigned int powerTemp = 0; //power Accumulator cache [per 15s, per 1 min, per hour, per day, per month] moving average
boolean switchFlag = 0; //flag for button toggle/debouncing.
boolean holdFlag = 0; //flag for debouncing
boolean fuseFlag = 0; //flag when power exceeds certain value
boolean switchFlag2 = 0; //flag for button toggle/debouncing.
boolean holdFlag2 = 0; //flag for debouncing
boolean fuseFlag2 = 0; //flag when power exceeds certain value

//STATUS VARIABLES CH2
boolean AUTO2 = 0;    //stores by channel flag
byte autoTemp2;
boolean MODE2[10] = {
  0}; //stores by-slot mode flags (1 is to-ON, 0 is to-OFF)
boolean CH2AUTO = 0; //stores status of ch1 if auto is on - submissive to LED_state[0]
boolean CH2MANUAL = 0; //stores status of ch1 if auto is on - submissive to LED_state[0]
boolean readSDStatus = 0;//stores if SD is read or not.

//SCHEDULER VARIABLES
const int timeTableColumns = 4; //timeTable columns ([mode] [hour] [minute] [second])
const int timeTableRows = 10; //timeTable rows
int ch1[timeTableRows][timeTableColumns]; //99 as disabled
//TIMETABLE Array Format row1[mode][hour][minute][second]-row2[....


//SCHEDULER CH2 VARAIBLES
int ch2[timeTableRows][timeTableColumns]; //99 as disabled
//TIMETABLE Array Format row1[mode][hour][minute][second]-row2[....


//COMMUNICATION VARIABLES
byte D[4]; //extract Digits function pass
const byte dataSize = 48;
boolean dataBuf[dataSize]; //data buffer
//start condition[lsb--->msb] SEE PIC CODE
const boolean startByte[8] = {
  1,1,1,1,1,1,1,1};  
boolean startFlag = 0;
boolean errorFlag = 0;
boolean timeOutFlag = 0;
boolean clockLatch = 0;
boolean RXLatch = 0;

//GSM VARIABLES
boolean screenFlag =0;
int SMSTimer=0;
int SMSTimerNow=0;

//PIN ASSIGNMENTS

const byte reqPin = 2;
const byte dataPin = 3;
const byte clockPin = 4;
const byte reqPin2 = 5; //datapin2 and clockpin2 shared by cpu2 and 3
const byte dataPin2 = 6;
const byte clockPin2 = 7;
const byte outPin1 = 8;
const byte outPin2 = 9;
//const byte reqPin3 = 10;
const byte autoPin = 28;
const byte manualPin = 29;

const byte buzPin = 19;
const byte switchPin = 18;
const byte switchPin2 = 17;

//TIMING VARIABLES
unsigned int milliSeconds = 0;
byte debugCount = 0;
unsigned int currentTime[6]; //0year 1month 2day 3hour 4minute 5second
boolean setupFlag = 0;
int safetyTime = 0; //safety timer for 1
int safetyTime2 = 0; //safety timer for 2
unsigned long prevMillis1 = 0;
unsigned long currentMillis1 = 0;
unsigned long currentMillis2 = 0;
unsigned long prevMillis2 = 0;
unsigned long currentMillis3 = 0;
unsigned long prevMillis3 = 0;
unsigned long timeStamp; //currenttime equivalent, minutes resolution, one year overflow

void setup()
{
  
}

void loop()
{

  if(setupFlag<1){
    beep(250,500,1);
    Serial.begin(9600);       // for debugging
    Serial.println("Starting up...");
    // INS
    //D3=4;
    //D2=3;
    //D1=2;
    //D0=1;

    //    pinMode(dataPin, INPUT);
    //    pinMode(clockPin, INPUT);

    // OUTS
    pinMode(outPin1, OUTPUT);  //relay 1
    pinMode(outPin2, OUTPUT);  //relay 2
    pinMode(reqPin, OUTPUT);  //interrupt for PIC16f628a
    pinMode(reqPin2, OUTPUT);  //interrupt for PIC16f877a #1
    pinMode(clockPin2, OUTPUT);  //clk line for 877a
    pinMode(dataPin2, OUTPUT);   //data line for 877a
    pinMode(autoPin, OUTPUT);   //auto indicator
    pinMode(manualPin, OUTPUT);   //auto indicator
    digitalWrite(autoPin,1);  //just making sure
    digitalWrite(manualPin,1);  //just making sure
    //pinMode(reqPin3, OUTPUT);   ////interrupt for PIC16f877a #2
    //digitalWrite(buzSwitchPin,0);
    digitalWrite(reqPin,0);  //just making sure

    ethernetInit(); //to ETH.ino
    //ethernet initialization

    Ethernet.begin(mac, ip);  // initialize Ethernet module
    server.begin();           // start to listen for clients
    timeTableInit();          //Initalize timetable
    
    readSDSettings(0);//SCHED         //load SD values to RAM
    readSDSettings(1);//SAVE
    readSDSettings(2);//SCHED2    
    
    transferToMemory(); //to SCHD.ino
    
    sortSchedule();           //sort read values chronologically
    //rtcSet();

    picRTCRead();              //Read PIC 16f628a for time


    setupFlag ++;
    
    digitalWrite(autoPin,0);  //just making sure
    digitalWrite(manualPin,0);  //just making sure
    
    
    delay(5000);
    ethernetMain(); //to ETH.ino 
    beep(50,200,2); 
  }

  currentMillis1 = millis();
  currentMillis2 = millis()+100;
  currentMillis3 = millis()+200;

  //1SEC REFRESH PROCESSES
  if ((currentMillis1 - prevMillis1) > interval1){
    
//    transferToScheduler(); //to SCHD.ino 
    //update chs along mode
    
    checkSched(); //to SCHD.ino 
    //check sched for values that might hit a sched
     
    microRTC((currentMillis1-prevMillis1)/interval1); //to RTC.ino 
    //time update
    
    safetyTimerDecrement();//to HW.ino 
    //decrement safety timer if there is
    Serial.print("."); 


    //--------------------
    prevMillis1 = currentMillis1; //for timing
    debugCount++; //debugger
  }

  //5SEC Refresh Process
  
  if ((currentMillis3 - prevMillis3) > interval3){

    power(); //to PWR.ino 
    //measure power and energy
    
    
    prevMillis3 = currentMillis3;
  }

  if ((currentMillis2 - prevMillis2) > interval2){

    CPU2Main(); //to CPU2.ino
    //handles data to send to CPU2
    //handles screen
    //debug();
    writeSD();
    overloadRecover();
    //----------------------------
    prevMillis2 = currentMillis2;
  }

  //INSTANTANEOUS (not so) PROCESSES
  ethernetMain(); //to ETH.ino 
  //accomodate ethernet server
  checkShutdown(); //to ST_SH.ino
  //check shutdown request from pic  
  checkManual(); //to HW.ino
  //check manual controls for update
  selectAutoManual(); //to CTRL.ino 
  //selection of LED state
  realTimePowerCheck(); //to PWR.ino
  //check of power draw, realtime, not measuring
  serialControl();
  //control for arduino via serial
}


