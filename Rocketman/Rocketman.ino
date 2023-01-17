#define SWITCH_PIN      10 // input for toggle switch
#define STROBE_COUNT_DELAY7 18000 // [ms] time between strobe cycles
#define STROBE_COUNT_DELAY8 16000 // [ms] time between strobe cycles

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int num_presses = 0;
int strobe_count1 = 0;
int strobe_count2 = 0;

// byte target, current; // target and current pwm value

int FADE_INTERVAL_7 = 	30; // [ms] time between fade steps
int NEXTFADE_INTERVAL_7 = 150; // [ms] time between fade cycles
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
  pinMode(0, OUTPUT); //base smoke white LED
  pinMode(2, OUTPUT); //base smoke white LED
  pinMode(3, OUTPUT); //flickering LED
  pinMode(4, OUTPUT); //base smoke white LED
  pinMode(5, OUTPUT); //Solid yellow LED
  pinMode(6, OUTPUT); //flickering LED
  pinMode(7, OUTPUT); //base smoke white LED
  pinMode(8, OUTPUT); //flickering LED
  pinMode(9, OUTPUT); //base smoke white LED

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
      analogWrite(0, LOW);
      analogWrite(2, LOW);
      analogWrite(3, LOW);
      analogWrite(4, LOW);
      analogWrite(5, LOW);
      analogWrite(6, LOW);
    	analogWrite(7, LOW);
      analogWrite(8, LOW);
      analogWrite(9, LOW);
      Serial.println("num_presses 0");
    }
    // button has been pressed once!
    if (num_presses == 1)
    {
      analogWrite(0, 255);
      analogWrite(2, 255);
      analogWrite(3, LOW);
      analogWrite(4, 255);
      analogWrite(5, LOW);
      analogWrite(6, LOW);
    	analogWrite(7, 255);
      analogWrite(8, LOW);
      analogWrite(9, 255);
      Serial.println("num_presses 1"); 
    }
  // button has been pressed twice!
    if (num_presses == 2)
    {        
      analogWrite(0, 180);
      analogWrite(2, 180);
      analogWrite(4, 180);
      analogWrite(7, 180);
      analogWrite(9, 180);
      Serial.println("num_presses 2");
  
    //LED_PIN1
  //if (millis() > time_for_nextfade_7) {
   // time_for_nextfade_7 = millis() + (unsigned long)NEXTFADE_INTERVAL_7;
    analogWrite(3, random(120)+135);
    analogWrite(6, random(120)+135);
    analogWrite(8, random(120)+135);
    analogWrite(5, random(254)+1);
    Serial.println("strobe_count1");
  }
  
    if (digitalRead(2) == HIGH && num_presses == 3)
    {
        Serial.println("num_presses 3, resetting num_presses to 0");
        num_presses = 0;
    }
}
    
