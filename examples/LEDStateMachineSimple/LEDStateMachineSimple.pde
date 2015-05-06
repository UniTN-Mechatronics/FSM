//http://github.com/UniTN-Mechatronics/FSM
#include <FiniteStateMachine.h>
//http://github.com/UniTN-Mechatronics/Button
#include <Button.h>
//http://github.com/UniTN-Mechatronics/LED
#include <LED.h>

const byte NUMBER_OF_STATES = 4; //how many states are we cycling through?

//initialize states
State On = State(onEnter, ledOn, onExit);
State Off = State(offEnter, ledOff, NULL); 
State FadeIn = State(fadeInEnter, ledFadeIn, NULL);
State FadeOut = State(fadeOutEnter, ledFadeOut, NULL); 

FSM ledStateMachine = FSM(On);     //initialize state machine, start in state: On

Button button = Button(12,PULLUP); //initialize the button (wire between pin 12 and ground)
LED led = LED(13);                 //initialize the LED
byte buttonPresses = 0;            //counter variable, hols number of button presses

void setup(){
  Serial.begin(9600);
  Serial.println("FSM LED Example loaded.");
}

//poor example, but then again; it's just an example
void loop(){
  if (button.uniquePress()){
    //increment buttonPresses and constrain it to [ 0, 1, 2, 3 ]
    buttonPresses = ++buttonPresses % NUMBER_OF_STATES; 
    switch (buttonPresses){
      case 0: ledStateMachine.transitionTo(On); break;
      case 1: ledStateMachine.transitionTo(Off); break;
      case 2: ledStateMachine.transitionTo(FadeIn); break;
      case 3: ledStateMachine.transitionTo(FadeOut); break;
    }
  }
  ledStateMachine.update();
}

//utility functions
void onEnter() { Serial.println("Entering LED on"); }
void onExit() { Serial.println("Exiting LED on"); }
void offEnter() { Serial.println("LED off"); }
void fadeInEnter() { Serial.println("LED fade in"); }
void fadeOutEnter() { Serial.println("LED fade out"); }

void ledOn(){ led.on(); }
void ledOff(){ led.off(); }
void ledFadeIn(){ led.fadeIn(500); }
void ledFadeOut(){ led.fadeOut(500); }
//end utility functions