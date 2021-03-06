/*
||
|| @file FiniteStateMachine.cpp
|| @version 1.7
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making finite state machines
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/

#include "FiniteStateMachine.h"

// FINITE STATE
State::State(void (*updateFunction)()) {
  init(0, 0, updateFunction, 0);
}

State::State(int id, void (*updateFunction)()) {
  init(id, 0, updateFunction, 0);
}

State::State(int id, void (*enterFunction)(), void (*updateFunction)(),
             void (*exitFunction)()) {
  init(id, enterFunction, updateFunction, exitFunction);
}

void State::init(int id, void (*enterFunction)(), void (*updateFunction)(),
             void (*exitFunction)()) {
  _id = id;
  userEnter = enterFunction;
  userUpdate = updateFunction;
  userExit = exitFunction;
}

// what to do when entering this state
void State::enter() {
  if (userEnter) {
    userEnter();
  }
}

// what to do when this state updates
void State::update() {
  if (userUpdate) {
    userUpdate();
  }
}

// what to do when exiting this state
void State::exit() {
  if (userExit) {
    userExit();
  }
}

int State::id() { return _id; }
// END FINITE STATE

// FINITE STATE MACHINE
FiniteStateMachine::FiniteStateMachine(State &current) {
  currentState = nextState = &current;
  stateChangeTime = 0;
}

FiniteStateMachine &FiniteStateMachine::update() {
  if (currentState != nextState) {
    currentState->exit();
    currentState = nextState;
    currentState->enter();    
    stateChangeTime = millis();
  }
  
  currentState->update();
  
  return *this;
}

FiniteStateMachine &FiniteStateMachine::transitionTo(State &state) {
  nextState = &state;
  return *this;
}

FiniteStateMachine &FiniteStateMachine::immediateTransitionTo(State &state) {
  currentState = nextState = &state;
  currentState->enter();
  return *this;
}

// return the current state
State &FiniteStateMachine::getCurrentState() { return *currentState; }

// check if state is equal to the currentState
boolean FiniteStateMachine::isInState(State &state) const {
  if (&state == currentState) {
    return true;
  } else {
    return false;
  }
}

unsigned long FiniteStateMachine::timeInCurrentState() {
  millis() - stateChangeTime;
}
// END FINITE STATE MACHINE
