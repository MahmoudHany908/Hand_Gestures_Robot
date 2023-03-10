const int trigger1 = 4; //Trigger pin of 1st Sesnor
const int echo1 = 5 ; //Echo pin of 1st Sesnor
const int trigger2 = 6; //Trigger pin of 2nd Sesnor
const int echo2 = 7;//Echo pin of 2nd Sesnor

long time_taken;
int dist,distL,distR;   // distance in general is stored inside the "dist" variable then we assign it to distL or distR according to what we need




long duration;      // duration is the time taken by the wave to go out from the tx and back to the rx
float r;

int l=0;

  
 

void setup() {
Serial.begin(9600); // tells the arduino tht it will transfer data by the rate of 9600 bits/sec
  
pinMode(trigger1, OUTPUT); // setting trig1 as an output device or component  - since it sends the ultrasonic waves-
pinMode(echo1, INPUT);    // setting echo1 as an input device  - since it receives the ultrasonic waves
pinMode(trigger2, OUTPUT); // same as trig1
pinMode(echo2, INPUT);    // same as echo2
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)  // the function takes a trig and an echo as arguments ... can be called for either so that we can use it on both sensors
{
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    // the previous 5 lines of code are used to send pulses to the Trigger or tx

time_taken = pulseIn(echo, HIGH);   // pulse in returns the time taken by the waves to return to the echo or the rx
dist= time_taken*0.034/2;     // distance = time_taken * speed of sound all divided by 2 since pulseIn returns the twice the time taken by the wave to travel from the arduino to the object
if (dist>50)  // just a limitation .. since the following conditions will work on values between 0 aand 50
dist = 50;
}

void loop() { //infinite loopy
// we initially calculate the distances for the two sensord, and then work on the calculated distance for the rest of the loop
  
calculate_distance(trigger1,echo1);   // calculating the distance for the left sensor
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);   // calculating the distance for the right sensor
distR =dist; //get distance of right sensor

if ((distL >25 && distR>25) && (distL <50 && distR<50)) //Detect both hands   ... both hands are within 25 and 50 cm from the sensors
{Serial.println("Play/Pause"); delay (500);}
 

//Control Modes

//Lock Left - Control Mode
if (distL>=10 && distL<=20)   // the vup and vdown dont work before the program makes sure that ur hand is between 10-20 cm away from the sensor
{
  // 
  delay(50); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  if (distL>=10 && distL<=20)
  {
    Serial.println("Left Locked");
  // now that ur hand is 10-20 cm away the following loop repeatedly check if ur hand is going up or down
    
    while(distL<=40)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<15) //Hand pushed in 
      {Serial.println ("Vdown"); delay (300);}
      if (distL>20) //Hand pulled out
      {Serial.println ("Vup"); delay (300);}
    }
  }
}

// same thing that happened up there, happens here with the other sensor so no need to write it again


//Lock Right - Control Mode
if (distR>=10 && distR<=20)
{
  delay(50); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=10 && distR<=20)
  {
    Serial.println("Right Locked");
    while(distR<=40)
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if (distR<15 ) //Right hand pushed in
      {Serial.println ("Rewind"); delay (300);}
      if (distR>20) //Right hand pulled out
      {Serial.println ("Forward"); delay (300);}
    }
  }
}




delay(200);
}
