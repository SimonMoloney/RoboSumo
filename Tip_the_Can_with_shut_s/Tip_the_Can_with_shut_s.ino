//
// RoboSlam Target Finding
// Written by Ciaran Gibson and Simon Moloney
//

//
// HC-SR Rangfinder test
// Written by Simon Moloney Ref Ted Burke 9/10/2018
//

//
// Switch
// Written by Simon Moloney 17/10/2018
//

// The setup routine runs once when the power is switched on.
void setup()
{

  // Digital output for LED 
  pinMode(2, OUTPUT); //LED

  // Digital output for Wheels on H-bridge
  pinMode(3, OUTPUT); //wheel 1 (Forward)Left
  pinMode(4, OUTPUT); //wheel 1 (Reverse)Left
  pinMode(7, OUTPUT); //wheel 2 (Reverse)Right
  pinMode(8, OUTPUT); //wheel 2 (Forward)Right

  //Digital Outputs for Rangefinder
  pinMode(5, OUTPUT); // rangefinder trigger
  

  Serial.begin(9600);
}


void loop()
{
  int duration, has_hit = 0, target_hit = 0;
  
  double distance;
   
  // Send trigger pulse
  digitalWrite(5, HIGH);            //Trig Pulse
  delayMicroseconds(20);
  digitalWrite(5, LOW);
 
  // Wait for start of echo pulse     
  while(digitalRead(6) == 0);
 
  // No measure duration of echo pulse
  duration = 0;
  while(digitalRead(6) == 1)
  {
    duration = duration + 10;
    delayMicroseconds(10);
  }
    
  distance = 0.5 * 1e-6 * duration * 340.0*1.41; // 1.41 was for distance correction

  //Want to find median of distance
  
  Serial.print (distance);
  Serial.println (" m");

 has_hit = digitalRead(9); // switch input
   
  if (has_hit == 1)
  
  {
   
    delay(500);
    
    //Reverse
    
    digitalWrite(3, LOW);       //wheel 1 (Reverse)Left
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);      //wheel 2 (Reverse)Right
    digitalWrite(8, LOW);
    
    
    delay(2000);
    
    
    digitalWrite(3, LOW);       //wheel 1 stop
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);      //wheel 2 Stop
    digitalWrite(8, LOW);
    delay(2000);
    

  while(1);

    
  }

  else if (has_hit == 0, distance < 0.5)
  {
    digitalWrite(2, HIGH);

    digitalWrite(3, HIGH);     //wheel 1 (Forward)Left
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);      //wheel 2 (Forward)Right
    digitalWrite(8, HIGH);
    
  }
  else if (has_hit == 0, distance > 0.5)
  {
    
    digitalWrite(2, LOW);

    digitalWrite(3, LOW);      //wheel 1 (Reverse)Left
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);      //wheel 2 (Forward)Right
    digitalWrite(8, HIGH);
 
  }
  
  


}
