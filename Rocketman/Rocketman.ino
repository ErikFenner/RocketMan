#define SWITCH_PIN      2 // input for toggle switch
#define LED_PIN1      	7 // output to FET module
#define LED_PIN2      	8 // output to FET module

#define STROBE_COUNT_DELAY7 18000 // [ms] time between strobe cycles
#define STROBE_COUNT_DELAY8 16000 // [ms] time between strobe cycles

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int num_presses = 0;
int strobe_count1 = 0;
int strobe_count2 = 0;

// byte target, current; // target and current pwm value

int FADE_INTERVAL_7 = 	30; // [ms] time between fade steps
int NEXTFADE_INTERVAL_7 = 1500; // [ms] time between fade cycles
int FADE_INTERVAL_8 = 	30; // [ms] time between fade steps
int NEXTFADE_INTERVAL_8 = 1500; // [ms] time between fade cycles
int FADE_INTERVAL_9 = 	30; // [ms] time between fade steps
int NEXTFADE_INTERVAL_9 = 1500; // [ms] time between fade cycles

byte current1; // current pwm value
byte target1; // target pwm value
byte current2; // current pwm value
byte target2; // target pwm value
unsigned long time_for_fadestep_7;
unsigned long time_for_nextfade_7;
unsigned long time_for_fadestep_8;
unsigned long time_for_nextfade_8;
unsigned long time_for_fadestep_9;
unsigned long time_for_nextfade_9;
unsigned long time_for_strobe_delay7;
unsigned long time_for_strobe_delay8;
unsigned long time_for_strobe_delay9;
unsigned long lastDebounceTime;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(SWITCH_PIN, INPUT);
  pinMode(1, OUTPUT); //base smoke white LED
  pinMode(2, OUTPUT); //base smoke white LED
  pinMode(3, OUTPUT); //base smoke white LED
  pinMode(4, OUTPUT); //base smoke white LED
  pinMode(5, OUTPUT); //base smoke white LED
  pinMode(6, OUTPUT); //Solid yellow LED
  pinMode(7, OUTPUT); //flickering LED
  pinMode(8, OUTPUT); //flickering LED
  pinMode(9, OUTPUT); //flickering LED

  Serial.begin(9600);
}
             
void loop() 
{
// read the state of the switch into a local variable:
  int reading = digitalRead(SWITCH_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        // increment our count for number of times pressed
        num_presses += 1;
        Serial.println("button is being pressed!");
      }
    }
  }
   // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

    // button hasn't been pressed yet (or has been reset)
    if (num_presses == 0)
    {
      digitalWrite(1, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    	digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      Serial.println("num_presses 0");
    }
    // button has been pressed once!
    if (num_presses == 1)
    {
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
    	digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    	digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      Serial.println("num_presses 1"); 
    }
  // button has been pressed twice!
    if (num_presses == 2)
    {        
      digitalWrite(1, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      Serial.println("num_presses 2");
  
    //LED_PIN1
  if (millis() > time_for_nextfade_7) {
    time_for_nextfade_7 = millis() + (unsigned long)NEXTFADE_INTERVAL_7;
  if (current1 == 0) { 
    target1 = 20;
    strobe_count1 += 1;
    Serial.println("strobe_count1");
  }}
  
   if (current1 == 20) { 
    target1 = 0;
   }
  
  if (millis() > time_for_fadestep_7) {
    time_for_fadestep_7 = millis() + (unsigned long)FADE_INTERVAL_7;
    if (current1 < target1) current1 +=4; 
    if (current1 > target1) current1 -=1; 
    analogWrite(LED_PIN1, current1);
    Serial.print(target1);
    Serial.print("  ");
    Serial.println(current1);
  }
      
  //LED_PIN2
  if (millis() > time_for_nextfade_8) {
    time_for_nextfade_8 = millis() + (unsigned long)NEXTFADE_INTERVAL_8;
  if (current2 == 1) { 
    target2 = 20;
    strobe_count2 += 1;
    Serial.println("strobe_count2");
  }}
  
   if (current2 == 20) { 
    target2 = 0;
   }
  
  if (millis() > time_for_fadestep_8) {
    time_for_fadestep_8 = millis() + (unsigned long)FADE_INTERVAL_8;
    if (current2 < target2) current2 +=4; 
    if (current2 > target2) current2 -=1; 
    analogWrite(LED_PIN2, current2);
    Serial.print(target2);
    Serial.print("  ");
    Serial.println(current2);
  }
  }
  
  
    if (digitalRead(10) == HIGH && num_presses == 3)
    {
        Serial.println("num_presses 3, resetting num_presses to 0");
        num_presses = 0;
    }
  
  // stobe count 1 causes reset
    if (strobe_count1 == 6)
    {
      	num_presses = 1;
        Serial.println("stobe count delay1");
      
    if (millis() > time_for_strobe_delay7) {
    time_for_strobe_delay7 = millis() + (unsigned long)STROBE_COUNT_DELAY7;
        strobe_count1 = 0;
       	num_presses = 2;
    } 
  }

  // stobe count 2 causes reset
    if (strobe_count1 == 6)
    {
      	num_presses = 1;
        Serial.println("stobe count delay2");
      
    if (millis() > time_for_strobe_delay8) {
    time_for_strobe_delay8 = millis() + (unsigned long)STROBE_COUNT_DELAY8;
        strobe_count2 = 0;
       	num_presses = 2;
    } 
  }
}
    
