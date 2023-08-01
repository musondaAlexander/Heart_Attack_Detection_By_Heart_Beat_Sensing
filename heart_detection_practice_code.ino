  /*
  This code demonstrates How the Heart Beat Sensor works When it is connected to an Aduino Board.

  */

  // add the needed libraries 
  #define USE_ARDUINO_INTERRUPTS true    
  #define DEBUG true
  #include <PulseSensorPlayground.h>
   #include <SoftwareSerial.h>

  
    //  Variables
  const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
  const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
  int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
  SoftwareSerial mySerial(9, 10);// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                                  // Otherwise leave the default "550" value. 
  int greenLED = 6;
  int redLED = 7;
  int buzzer = 2;
                                
  PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


  void setup() {   
    // led setup
    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(buzzer,OUTPUT);
    mySerial.begin(9600);        // Setting the baud rate of GSM Module 
    Serial.begin(9600);          // For Serial Monitor

    // Configure the PulseSensor object, by assigning our variables to it. 
    pulseSensor.analogInput(PulseWire);   
    pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
    pulseSensor.setThreshold(Threshold);   

    // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
    if (pulseSensor.begin()) {
      Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
    }
  }



  void loop() {
  
  digitalWrite(greenLED,HIGH);
  delay(700);
  digitalWrite(greenLED,HIGH);
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                // "myBPM" hold this BPM value now. 

  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
  Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
  Serial.print("BPM: ");                        // Print phrase "BPM: " 
  Serial.println(myBPM);                        // Print the value inside of myBPM. 
  }
 
    if(int myBPM = pulseSensor.getBeatsPerMinute() > 50){
      digitalWrite(greenLED,LOW);
      digitalWrite(buzzer,HIGH);
      digitalWrite(redLED,HIGH);
      delay(700);
      digitalWrite(redLED,HIGH);
       sendMessage();
       Serial.print("BPM:  too High!!"); 
       Serial.println(myBPM);
     }
     else if (int myBPM = pulseSensor.getBeatsPerMinute() < 50){
      digitalWrite(buzzer,LOW);
      digitalWrite(redLED,LOW);
     }

    delay(20);                    // considered best practice in a simple sketch.
  }

  // The send Message Function.
    void sendMessage()
    {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+1251234567\"\r"); // Replace with mobile number
      delay(1000);
      mySerial.println("Heart Rate Too High ");// The SMS text you want to send
       int myBPM = pulseSensor.getBeatsPerMinute();
      mySerial.println(myBPM); 
      delay(100);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }

