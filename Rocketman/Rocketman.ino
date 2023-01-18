#define SWITCH_PIN      10 // input for toggle switch
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int num_presses = 0;
unsigned long lastDebounceTime;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int ledPins[] = {1, 2, 4, 7, 9}; // array of pin numbers for the LEDs
int numOfLEDs = sizeof(ledPins) / sizeof(ledPins[5]); // number of LEDs
unsigned long prevMillis;
int randomLED;
int randomSpeed;
unsigned long randomDelay;


void setup() {
  pinMode(SWITCH_PIN, INPUT);
  pinMode(3, OUTPUT); //flickering LED
  pinMode(5, OUTPUT); //Solid yellow LED
  pinMode(6, OUTPUT); //flickering LED
  pinMode(8, OUTPUT); //flickering LED
  prevMillis = millis();
  randomSeed(analogRead(A0));
  for (int i = 0; i < numOfLEDs; i++) {
  pinMode(ledPins[i], OUTPUT); // set the pin mode for each LED
  }
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
      analogWrite(1, LOW);
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
    if (num_presses == 1){
    Serial.println("num_presses 1"); 
    if (5 <=254)
    {
      analogWrite(1, 255);
      analogWrite(2, 255);
      analogWrite(4, 255);
      analogWrite(5, 255);
    	analogWrite(7, 255);
      analogWrite(9, 255);
      
    }}
  // button has been pressed twice!
    if (num_presses == 2)
    {      
      if(millis() - prevMillis > randomDelay) {
    randomLED = random(numOfLEDs); // select a random LED
    randomSpeed = random(100, 255); // select a random speed
    analogWrite(ledPins[randomLED], randomSpeed); // set the LED's brightness
    randomDelay = random(50, 250);
    prevMillis = millis();
  }  
    Serial.println("num_presses 2");
    analogWrite(3, random(120)+135);
    analogWrite(6, random(120)+135);
    analogWrite(8, random(120)+135);
    analogWrite(5, random(254)+1);
  }
  
    if (digitalRead(2) == HIGH && num_presses == 3)
    {
        Serial.println("num_presses 3, resetting num_presses to 0");
        num_presses = 0;
    }
}
    
