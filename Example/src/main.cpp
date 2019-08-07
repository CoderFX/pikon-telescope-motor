/*     Stepper Motor Control Exaple Code
 *      
 *  Using NEMA 17
 *  
*/

/* Enable Input (ENABLE). This input turns on or off all of the
FET outputs. When set to a logic high, the outputs are disabled.
When set to a logic low, the internal control enables the outputs
as required. The translator inputs STEP, DIR, and MSx, as well as
the internal sequencing logic, all remain active, independent of the ENABLE input state

Sleep Mode SLEEP. To minimize power consumption
when the motor is not in use, this input disables much of the
internal circuitry including the output FETs, current regulator,
and charge pump. A logic low on the SLEEP  pin puts the A4988
into Sleep mode. A logic high allows normal operation, as well as
start-up (at which time the A4988 drives the motor to the Home
microstep position). When emerging from Sleep mode, in order
to allow the charge pump to stabilize, provide a delay of 1 ms
before issuing a Step command
 */

#include <Arduino.h>

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 
const int SLEEP = 5; //This pin is active low, so by default the board is NOT sleeping 
const int RESET = 6; //The RESET pin is floating on the breakout (not pulled high or low), you can simply connect this to the SLEEP pin if you want, otherwise you will want to (so it will be pulled high also), or control it as you wish.
const int FULL_ROTATION = 540; // 540 full stepper rotations on planetary gear is 1 rotation
const int ROTATE = 10;
int y = 0;
 
void setup() {
  //Run once
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(SLEEP,OUTPUT); 
  pinMode(RESET,OUTPUT);
}
void loop() {
  // Loop
  digitalWrite(SLEEP,HIGH); // Bring back from sleep
  delayMicroseconds(1000); // Wait 1ms for board to wake up
  digitalWrite(RESET,HIGH); // Reset needs to be high in order for motor to work

  digitalWrite(dirPin,LOW); // Enables the motor to move clockwise; LOW - Clockwise; HIGH - Counter-clockwise
  while (y < ROTATE) // Does 540 rotations, on planetary gear this is a full rotation
  {
    for(int x = 0; x < 200; x++) // Makes 200 pulses for making one full cycle rotation
      {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(500); 
      }
    y++;
  }
  y = 0;
  delay(5000); // During these 10 seconds motor is in set position (holding torque). It should be getting warm and make high pitch noise
  digitalWrite(SLEEP,LOW); // Setting board to sleep
  delayMicroseconds(1000); // Wait 1ms for board to go to sleep
  digitalWrite(RESET,HIGH);
  delay(5000); // During these 10 seconds motor is deactivated. It is not holding any torque. Should be silent
}
