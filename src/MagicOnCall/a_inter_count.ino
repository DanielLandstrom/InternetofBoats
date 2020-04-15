
// the number of the PWM pin
const int pwmPin = 27;  // GPIO27 for the motor built-in PWM 
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
                                                  // GPIO25 for the motor built-in hall sensor
                                                  // GPIO23 for the IR line sensor
const byte        interruptPin = 25;              // Assign the interrupt pin
volatile uint64_t StartValue;                     // First interrupt value
volatile uint64_t PeriodCount;                    // period in counts of 0.000001 of a second
double            Freg;                           // frequency  
double            averageRPM5;                    // average frequency 
double            averageRPM10;                   // average frequency    
double            averageRPM20;                   // average frequency 
//char              str[21];                        // for printing uint64_t values
int               dutyCycle = 128;

hw_timer_t * timer = NULL;                        // pointer to a variable of type hw_timer_t 
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;  // synchs between maon cose and interrupt?

// Digital Event Interrupt
// Enters on falling edge in this example
//=======================================
void IRAM_ATTR handleInterrupt() 
{
  portENTER_CRITICAL_ISR(&mux);
      uint64_t TempVal= timerRead(timer);         // value of timer at interrupt
      PeriodCount= TempVal - StartValue;          // period count between rising edges in 0.000001 of a second
      StartValue = TempVal;                       // puts latest reading as start for next calculation
  portEXIT_CRITICAL_ISR(&mux);
}

/*
void setup(){
  pinMode(interruptPin, INPUT_PULLUP);                                            // sets pin high
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING); // attaches pin to interrupt on Falling Edge
  timer = timerBegin(0, 80, true);                                                // this returns a pointer to the hw_timer_t global variable
                                                                                  // 0 = first timer
                                                                                  // 80 is prescaler so 80MHZ divided by 80 = 1MHZ signal ie 0.000001 of a second
                                                                                  // true - counts up
  timerStart(timer);                                                              // starts the timer

  // configure PWM functionalities
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin, ledChannel);
}
*/
/*
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the motor speed with PWM
    ledcWrite(ledChannel, dutyCycle);

  portENTER_CRITICAL(&mux);
  Freg =30.0*1000000.00/PeriodCount;                       // PeriodCount in 0.000001 of a second
  portEXIT_CRITICAL(&mux);

 //float speedAnemo() {
//  if (validAneo == true) {
//    float Freg =30.0*1000000.00/PeriodCount; 
    averageRPM5   = ((4.0  * averageRPM5)  + Freg) /  5.0;
    averageRPM10  = ((9.0  * averageRPM10) + Freg) / 10.0;
    averageRPM20  = ((19.0 * averageRPM20) + Freg) / 20.0;
    if (Freg < 0.9) {
      averageRPM5  = 0.0;
      averageRPM10 = 0.0;
      averageRPM20 = 0.0;
    }
//    validAneo = false;
//  }
//  return averageAnemo;
//}
 
  SendN2kRapidData();
  //SendN2kSlowData();
  NMEA2000.ParseMessages();

    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the motor speed with PWM
    ledcWrite(ledChannel, dutyCycle);   
  portENTER_CRITICAL(&mux);
  Freg =30.0*1000000.00/PeriodCount;                       // PeriodCount in 0.000001 of a second
  portEXIT_CRITICAL(&mux);

 //float speedAnemo() {
//  if (validAneo == true) {
//    float Freg =30.0*1000000.00/PeriodCount; 
    averageRPM5   = ((4.0  * averageRPM5)  + Freg) /  5.0;
    averageRPM10  = ((9.0  * averageRPM10) + Freg) / 10.0;
    averageRPM20  = ((19.0 * averageRPM20) + Freg) / 20.0;
    if (Freg < 10) {
      averageRPM5  = 0.0;
      averageRPM10 = 0.0;
      averageRPM20 = 0.0;
    }
//    validAneo = false;
//  }
//  return averageAnemo;
//}
 
  SendN2kRapidData();
  //SendN2kSlowData();
  NMEA2000.ParseMessages();

    delay(15);
  }


  
}

#define RapidDataUpdatePeriod 167 // Some strange periot to cause Slow and rapid to run unsync.

void SendN2kRapidData() {
  static unsigned long RapidDataUpdated=millis();
  tN2kMsg N2kMsg;

  if ( RapidDataUpdated+RapidDataUpdatePeriod<millis() ) {
    RapidDataUpdated=millis();

    SetN2kEngineParamRapid(N2kMsg,0, (double) averageRPM10); 
    NMEA2000.SendMsg(N2kMsg);
    SetN2kCOGSOGRapid(N2kMsg,1,N2khr_true,DegToRad(115.6),msToKnots(0.01*averageRPM10));
    NMEA2000.SendMsg(N2kMsg);
  }
}
