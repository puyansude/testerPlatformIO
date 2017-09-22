/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 * Petit test de git
 */

#include "Arduino.h"
#include <TaskScheduler.h>

// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();

//Tasks
Task t4();
Task t1(2000, 10, &t1Callback);
Task t2(3000, TASK_FOREVER, &t2Callback);
Task t3(5000, TASK_FOREVER, &t3Callback);

Scheduler runner;


void t1Callback() {
    Serial.print("t1: ");
    Serial.println(millis());
    
    if (t1.isFirstIteration()) {
      runner.addTask(t3);
      t3.enable();
      Serial.println("t1: enabled t3 and added to the chain");
    }
    
    if (t1.isLastIteration()) {
      t3.disable();
      runner.deleteTask(t3);
      t2.setInterval(50);
      Serial.println("t1: disable t3 and delete it from the chain. t2 interval set to 500");
    }
}

void t2Callback() {
    Serial.print("t2: ");
    Serial.println(millis());
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  
}

void t3Callback() {
    Serial.print("t3: ");
    Serial.println(millis());
  
}

void setup () {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Scheduler TEST");
  
  runner.init();
  Serial.println("Initialized scheduler");
  
  runner.addTask(t1);
  Serial.println("added t1");
  
  runner.addTask(t2);
  Serial.println("added t2");

  delay(5000);
  
  t1.enable();
  Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");
}


void loop () {
  runner.execute();
}


/*
void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  Serial.println("Attendre une seconde a ON");
  delay(100);
  
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
   Serial.println("Attendre une seconde a OFF");
   delay(100);
}
*/