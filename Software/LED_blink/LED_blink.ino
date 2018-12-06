/*
Flashing LED Code
Raj Borra (rkb15)
*/

#define BUTTON 2
#define LED 9
#define PWM_MAX 255
#define BLINK_RATE 2

int PWM_VAL = 0;
int current_state = 0;
int previous_state = 0;
bool BUTTON_STATE = false;
int prev_time = 0;

void setup() {
    Serial.begin(9600);  
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), button_pushed, FALLING);
    pinMode(LED, OUTPUT);
}

void loop() {
    // Check for Button Press
    if (BUTTON_STATE == true){
      current_state = current_state + 1;
      if (current_state == 5) current_state = 0;
    }
    BUTTON_STATE = false;
    
    // Set the Output given Current State
    set_output();
    
    // Update LED Value
    analogWrite(LED,PWM_VAL);
}

void button_pushed(){
  int cur_time = millis();
  if (cur_time -  prev_time > 300){
    BUTTON_STATE = true;
  }
  prev_time = cur_time;
}

void set_output(){
    switch(current_state){
      case 0:
        PWM_VAL = 0;
        Serial.print("0");   
        break;
      case 1:
        PWM_VAL = PWM_MAX;
        Serial.print("1");   
        break;
      case 2:
        PWM_VAL = int(PWM_MAX/2);
        Serial.print("2");   
        break;
      case 3:
        PWM_VAL = int(PWM_MAX/4);
        Serial.print("3");   
        break;
      case 4:
        Serial.print("4");
        PWM_VAL = 0;
        analogWrite(LED,PWM_VAL);
        delay(1000/BLINK_RATE/2);
        PWM_VAL = PWM_MAX;
        analogWrite(LED,PWM_VAL);
        delay(1000/BLINK_RATE/2);
        break;
    }
}
