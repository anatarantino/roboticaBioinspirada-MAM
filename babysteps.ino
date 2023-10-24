// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

const int Trigger = 13;   //Pin digital 2 para el Trigger del sensor
const int Echo = 12;   //Pin digital 3 para el Echo del sensor

// These variables store the flash pattern
// and the current state of the LED

int ledRed1 =  2;      // the number of the LED pin
int ledState1 = LOW;             // ledState used to set the LED
unsigned long previousMillis1 = 0;        // will store last time LED was updated
long OnTime1 = 250;           // milliseconds of on-time
long OffTime1 = 350;          // milliseconds of off-time

int ledYellow2 =  11;      // the number of the LED pin
int ledState2 = LOW;             // ledState used to set the LED
unsigned long previousMillis2 = 0;        // will store last time LED was updated
long OnTime2 = 350;           // milliseconds of on-time
long OffTime2 = 450;          // milliseconds of off-time

int ledGreen3 =  10;      // the number of the LED pin
int ledState3 = LOW;             // ledState used to set the LED
unsigned long previousMillis3 = 0;        // will store last time LED was updated
long OnTime3 = 450;           // milliseconds of on-time
long OffTime3 = 550;          // milliseconds of off-time

void setup() {
  //leds
  // set the digital pin as output:
  pinMode(ledRed1, OUTPUT);      
  pinMode(ledYellow2, OUTPUT);   
  pinMode(ledGreen3,OUTPUT);


  //motor
  //sensor
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

  digitalWrite(ledGreen3, HIGH);
  digitalWrite(ledRed1, HIGH);
  digitalWrite(ledYellow2, HIGH);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

}

void loop() {

  //leds
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
 
  // if((ledState1 == HIGH) && (currentMillis - previousMillis1 >= OnTime1))
  // {
  //   ledState1 = LOW;  // Turn it off
  //   previousMillis1 = currentMillis;  // Remember the time
  //   digitalWrite(ledRed1, ledState1);  // Update the actual LED
  // }
  // else if ((ledState1 == LOW) && (currentMillis - previousMillis1 >= OffTime1))
  // {
  //   ledState1 = HIGH;  // turn it on
  //   previousMillis1 = currentMillis;   // Remember the time
  //   digitalWrite(ledRed1, ledState1);	  // Update the actual LED
  // }
  
  // if((ledState2 == HIGH) && (currentMillis - previousMillis2 >= OnTime2))
  // {
  //   ledState2 = LOW;  // Turn it off
  //   previousMillis2 = currentMillis;  // Remember the time
  //   digitalWrite(ledYellow2, ledState2);  // Update the actual LED
  // }
  // else if ((ledState2 == LOW) && (currentMillis - previousMillis2 >= OffTime2))
  // {
  //   ledState2 = HIGH;  // turn it on
  //   previousMillis2 = currentMillis;   // Remember the time
  //   digitalWrite(ledYellow2, ledState2);	  // Update the actual LED
  // }

  // if((ledState3 == HIGH) && (currentMillis - previousMillis3 >= OnTime3))
  // {
  //   ledState3 = LOW;  // Turn it off
  //   previousMillis3 = currentMillis;  // Remember the time
  //   digitalWrite(ledGreen3, ledState3);  // Update the actual LED
  // }
  // else if ((ledState3 == LOW) && (currentMillis - previousMillis3 >= OffTime3))
  // {
  //   ledState3 = HIGH;  // turn it on
  //   previousMillis3 = currentMillis;   // Remember the time
  //   digitalWrite(ledGreen3, ledState3);	  // Update the actual LED
  // }


  //motor
  int d = sensor();

  // Serial.print(d);

  analogWrite(enA, 100);
	analogWrite(enB, 100);

  if(d < 40){
    digitalWrite(ledRed1, LOW);	  // Update the actual LED
    digitalWrite(ledGreen3, HIGH);

    slowDown();


  }
  else{
    digitalWrite(ledGreen3, LOW);
    digitalWrite(ledRed1, HIGH);

    // Turn on motor A & B
	  digitalWrite(in1, HIGH);
	  digitalWrite(in2, LOW);
	  digitalWrite(in3, HIGH);
	  digitalWrite(in4, LOW);
  }
}





void slowDown(){
	// Decelerate from maximum speed to zero
  digitalWrite(ledYellow2, LOW);
	for (int i = 100; i >= 0; --i) {
		analogWrite(enA, i);
		analogWrite(enB, i);
	}
}

int sensor(){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  return d;
}

// This function lets you control spinning direction of motors
void directionControl() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, 255);
	analogWrite(enB, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2000);

}

// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}