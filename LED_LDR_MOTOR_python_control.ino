// Declare pin functions on RedBoard
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN 6
#define speedDelay 1
#define HEIGHT 18000

//Declare variables for functions
int sensorPin = A0;   // select the input pin for ldr
int sensorValue = 0;  // variable to store the value coming from the sensor
char user_input;  // for motor function communication
int x;
int y;
int state;


void setup() {
  // digital pins on Arduino are either input/output.
  /// we want to send data to the driver, so we choose output.
  pinMode(13, OUTPUT); //pin connected to the led
  pinMode(stp , OUTPUT);  // voltage to motor
  pinMode(dir, OUTPUT);  // polarity of motor voltage
  pinMode(A0, INPUT_PULLUP);  // pull-up resistor / signal from LDR
//  resetEDPins();  // Set step, dir, ms1/2 and en pins to default states
  // set an initial value of low to both our step and dir pins (FALSE or 0 are also acceptable)
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);

  Serial.begin(9600);     // sets serial port for communication

  Serial.println("1. Automatic Function");
  Serial.println("2. Roll shade up");
  Serial.println("3. Roll shade down");
  Serial.println("4. Show off");
  Serial.println();
  
}


void loop() {    

  while(Serial.available())
  {
    user_input = Serial.read();  // Read user input and trigger a function
    digitalWrite(EN, LOW);  // Pull enable pin LOW to allow motor control
    if (user_input == '1')
    {
      LightActivated();
    }
    else if(user_input == '2')
    {
       StepForwardDefault();
    }
    else if(user_input =='3')
    {
      ReverseStepDefault();
    }
    else if(user_input =='4')
    {
      ForwardBackwardStep();
    }
    else
    {
      Serial.println("Invalid option entered.");
      resetEDPins();
    }
    resetEDPins();
  }
}

void LightActivated() {
  delay(2000);
  Serial.println("Reading LDR Output");
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(200);
  if (sensorValue > 200 )
  {
  digitalWrite(dir, LOW);   // Pull direction pin LOW to move CW/'forward'
  for(x=0; x<HEIGHT; x++)    // ADJUST FOR HEIGHT OF SHADE!!
  {  
    digitalWrite(stp,HIGH); // Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); // Pull step pin low so it can be triggered again
    delay(1);
  }
  }
  else
  {
    Serial.println("It's dark outside. No action taken.");
    delay(200);
  }
  Serial.println("End Function.");
}  

void StepForwardDefault()
{
  Serial.println("Moving forward at defaul step mode.");
  digitalWrite(dir, LOW);   // Pull direction pin LOW to move CW/'forward'
  for(x=0; x<HEIGHT; x++)    // ADJUST FOR HEIGHT OF SHADE!!
  {
    digitalWrite(stp,HIGH); // Trigger one step forward
    delay(speedDelay);
    digitalWrite(stp,LOW); // Pull step pin low so it can be triggered again
    delay(speedDelay);
  }
  Serial.println("Hello, world! Enter new option:");
  Serial.println();
}  

void ReverseStepDefault()
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH);    // Pull direction pin HIGH to move CCW/'reverse'
  for(x=0; x<HEIGHT; x++)   // ADJUST FOR HEIGHT OF SHADE!!
  {
    digitalWrite(stp,HIGH); 
    delay(speedDelay);
    digitalWrite(stp,LOW);
    delay(speedDelay);
  }
  Serial.println("Throwing shade up in here. Enter new option:");
  Serial.println();
}

void ForwardBackwardStep()
{
  Serial.println("Alternate between stepping forward and reverse.");
  for(x=1; x<100; x++)  // ADJUST SO IT DOESN'T MAX OUT ON EITHER END!!
  {
    // Read direction pin state and change it
    state = digitalRead(dir);
    if(state == HIGH)
    {
      digitalWrite(dir, LOW);
    }
    else if(state == LOW)
    {
      digitalWrite(dir, HIGH);
    }

    for(y=0; y<100; y++)   
    {
      digitalWrite(stp, HIGH);  
      delay(speedDelay);
      digitalWrite(stp, LOW);  
      delay(speedDelay);
    }
  }
  Serial.println("Whoo. That was fun. Enter new option:");
  Serial.println();
}

void resetEDPins()    // Pins must be set back to default state to prevent unwanted action.
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}
