/* 
 * TimeSerial.pde
 * example code illustrating Time library set through serial port messages.
 *
 * Messages consist of the letter T followed by ten digit time (as seconds since Jan 1 1970)
 * you can send the text on the next line using Serial Monitor to set the clock to noon Jan 1 2013
 T1357041600  
 *
 * A Processing example sketch to automatically send the messages is included in the download
 * On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
 */ 
 
#include <TimeLib.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

////////////////////////////

int sensorPin = A0; // Connect sensor to analog pin A0
int ledPin = 9; // Connect LED to digital pin 9

// Define time intervals for day and night
int startTime = 5*3600; // 5am in seconds
int peakStart = 12*3600;// 12pm in seconds
int peakStart2 = 13.5*3600; // 1:30pm ins seconds
int peakEnd = 15*3600; // 3pm in seconds
int endTime = 19*3600; // 7pm in seconds
///////////////////////////////////////////
void setup()  {
  Serial.begin(9600);
 // while (!Serial) ; // Needed for Leonardo only
  pinMode(13, OUTPUT);
   pinMode(ledPin, OUTPUT); // Set LED pin as output
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
}

void loop(){    
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }
  if (timeStatus() == timeSet) {
    digitalWrite(13, HIGH); // LED on if synced
  } else {
    digitalWrite(13, LOW);  // LED off if needs refresh
  }
  delay(1000);
  int hour_var = hour(); // Extract hour from current time
  int minute_var = minute(now); // Extract minute from current time
  int second_var = second(now); // Extract second from current time
  int timeInSeconds = hour_var*3600 + minute_var*60 + second_var; // Compute current time in seconds

  int lightIntensity = 0; // Initialize light intensity

if (timeInSeconds >= startTime && timeInSeconds < peakStart) { // Before peak
    lightIntensity = map(timeInSeconds, startTime, peakStart, 0, 180); // Map time to light intensity (linearly increasing)
  }
  else if (timeInSeconds >= peakStart && timeInSeconds < peakStart2) { // During peak
    lightIntensity = map(timeInSeconds, peakStart, peakEnd, 180, 255); // Map time to light intensity (linearly increasing)
  } 
  else if (timeInSeconds >= peakStart2 && timeInSeconds < peakEnd) { // After peak
    lightIntensity = map(timeInSeconds, peakEnd, endTime, 255, 180); // Map time to light intensity (linearly decreasing)
  } 
  else if (timeInSeconds >= peakEnd && timeInSeconds < endTime) { // After peak
    lightIntensity = map(timeInSeconds, peakEnd, endTime, 180, 0); // Map time to light intensity (linearly decreasing)
  }
  else if (timeInSeconds >= endTime) { // Turn off LED at 7pm
    lightIntensity = 0;
  } //////////////////////////////////////////////////////////////
/////////////////////////////////////////  ////////////////////////


 /* int sensorValue = analogRead(sensorPin); // Read sensor value
  float voltage = sensorValue * (5.0 / 1023.0); // Convert sensor value to voltage
  float lux = voltage * 100; // Convert voltage to lux (calibration factor is 100)
  
  Serial.print("Current time: ");
  Serial.print(hour_var);
  Serial.print(":");
  Serial.print(minute_var);
  Serial.print(":");
  Serial.println(second_var);
  
  Serial.print("Light intensity: ");
  Serial.println(lightIntensity);
  
  Serial.print("Ambient light level: ");
  Serial.print(lux);
  Serial.println(" lux");
  
  */
  /////////////////////////////////////
  ///////////////////////////////////////
  
  
  
  
  
  
  
  analogWrite(ledPin, lightIntensity);
  delay(1000);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt()+ 19800;
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
