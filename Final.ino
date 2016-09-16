// Example sketch for Sensing Motion with PIR and interfacing with Arduino
// Dharminder Singh
// HBTU, Knapur
// Can Contact me @ Dsinghhbtu@gmail.com
// Get complete information about this @
// Here we are using two sensors to cover more of the area 
// first one is pir1 and similarly second is pir2
//=================================================================================================
// Singhhbtu.wordpress.com
//=================================================================================================
const int pirPin1 = 12;//the digital pin connected to the PIR1 sensor's output
const int pirPin2 = 11;//the digital pin connected to the PIR2 sensor's output
const int relayPin = 13;// taking output from 13th pin
boolean first = true;
boolean reset = true;


/*
  Setup function
  **/
void my_delay(int x)
{
  for (int i = 0; i < x; i++)
  {
    delay(1);
    if ((digitalRead(pirPin1) == HIGH)||(digitalRead(pirPin2) == HIGH)) // both PIR's in OR condition, Logical OR
    {
      digitalWrite(relayPin, HIGH);

    }
  }
}         //**************my delay for continously cheching any movement*******//


void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);

  //pinMode(2, OUTPUT);


  digitalWrite(pirPin1, INPUT);
  digitalWrite(pirPin2, INPUT);

  digitalWrite(relayPin, LOW);  // Set all the initial conditions

  Serial.println("ALLOW HUMAN TO GET OUT OF THE WAY OF SENSOR");
  for (int i = 10; i > 0; i--)
  {
    Serial.println(i);
    delay(100);                 // time for the PIR to set up
  }

  // give the sensor some time to calibrate
  Serial.println();
  Serial.println("SENSOR IS ACTIVE");
  Serial.println();
}






/*
 Loop function
 **/
void loop()
{

  first = true;
  
  if ((digitalRead(pirPin1) == HIGH)||(digitalRead(pirPin2) == HIGH))
  { // object detected
    if (first)
    {
      Serial.println("---------------");
      Serial.println("MOTION DETECTED");
      Serial.println("---------------");
      Serial.println();
      first = false;
    }
    digitalWrite(relayPin, HIGH);

  }


  /*
  Check for reset motion during the last minute of activation time
  **/
  for (int i = 1; i <=60;  i++)
  {
    if ((digitalRead(pirPin1) == HIGH)||(digitalRead(pirPin2) == HIGH))
    {
      if (reset)
      {
        digitalWrite(relayPin, HIGH);

        Serial.println("---------------");
        Serial.println("REACTIVATE TIMER");
        Serial.println("---------------");
        Serial.println();
        i = 1; // reset timer value
        reset = false;
      }
      delay(2000);
      Serial.println(i);

    }
    else
    {
      delay(2000);
      Serial.println(i);
      reset = true;
    }
  }
  // end if


  if ((digitalRead(pirPin1) == LOW)&&(digitalRead(pirPin2) == LOW))
  {

    digitalWrite(relayPin, LOW);

    digitalWrite(2, HIGH);
    my_delay(30000);
    digitalWrite(2, LOW);

    first = true;
  }
}
// Hope it will help you:)
// end loop()
