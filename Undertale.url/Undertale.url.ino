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

const int numReadings = 5;

int duration, switch_pressed = 0;
int calculate_distance;

int distances [numReadings];
int readindex = 0;
int total = 0 ;
int average_distance = 0;





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
    
  calculate_distance = 0.5 * 1e-4 * duration * 340.0*1.41; // 1.41 was for distance correction
//   
//  Serial.print (calculate_distance);
//  Serial.println (" m");

  
//averaging the distance
  

  total = total - distances[readindex];

  distances[readindex] = calculate_distance;

  total = total + distances[readindex];

  readindex = readindex + 1;

  if (readindex >= numReadings )
  {
    readindex = 0;
  }
  

  average_distance = total/numReadings ;
  Serial.print (average_distance);
  Serial.println (" m");
  

 switch_pressed = digitalRead(9); // switch input
   
  if (switch_pressed == 1)
  {
    reset();
  }
  
  else if (switch_pressed == 0, average_distance < 50)
  {
    forward();   
  }
  
  else if (switch_pressed == 0,average_distance > 50)
  {
    turn_right();  
  }
}

void forward(){
    digitalWrite(2, HIGH);      //LED on

    digitalWrite(3, HIGH);      //wheel 1 (Forward)Left
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);       //wheel 2 (Forward)Right
    digitalWrite(8, HIGH);
}

void turn_right(){
    digitalWrite(2, LOW);      //LED off

    digitalWrite(3, LOW);      //wheel 1 (Reverse)Left
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);      //wheel 2 (Forward)Right
    digitalWrite(8, HIGH);
}

void reset(){
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


  
