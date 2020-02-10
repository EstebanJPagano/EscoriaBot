
/* include library */
#include <Servo.h>           // Add Servo library
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
#include <AFMotor.h>


SoftwareSerial miBT(19, 18);   // pin 19 como RX, pin 18 como TX

// ----------- Puenteh

int ENA = 40;      // ENA de L298N a pin digital 5    gris
int ENB = 50;      // ENb de L298N a pin digital 5    naranja
//derecho
int IN1 = 42;      // IN1 de L298N a pin digital 2    violeta
int IN2 = 44;      // IN2 de L298N a pin digital 3    azul
//izquierdo
int IN3 = 46;      // IN2 de L298N a pin digital 2    verde
int IN4 = 48;      // IN3 de L298N a pin digital 3    amarillo
int ALIMENTACION1 = 52;      // pin de alimentacion siempre on

int speedCar = 1024;   // variable para almacenar valor de velocidad
int speedMAX = 1024;  // variable para almacenar valor de velocidad
int speedMED = 768;     // variable para almacenar valor de velocidad
int speedMIN = 130;      // variable para almacenar valor de velocidad
int speedOff = 0 ;

// ---------- Servo
Servo myservoH;               // Define any servo name
int contador;
int powerServ = 30;


// ----------- definir led
int PinLED0 = 32; //blanco adelante
int PinLED1 = 34; //blanco adelante
int PinLED2 = 36; //rojo
int PinLED3 = 38; //rojo

void setup(){
  
  Serial.begin(38400);
  Serial1.begin(38400);

  pinMode(ALIMENTACION1, OUTPUT);   // ENB como salida
  digitalWrite(ALIMENTACION1,HIGH);
  
  // l298n
  pinMode(IN1, OUTPUT);   // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida

 //Servos
   myservoH.attach (2);          // Define the servo signal pins
   pinMode(powerServ, OUTPUT);   // IN1 como salida  
   digitalWrite(powerServ, HIGH);
   
  // LED
  
  pinMode(PinLED0, OUTPUT);              
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED2, OUTPUT);
  pinMode(PinLED3, OUTPUT);
  
}

void loop(){

    //------------Bluetooth
  if (Serial1.available()){     // si hay informacion disponible desde modulo
    char DATO = Serial1.read();   // almacena en DATO el caracter recibido desde modulo
    Serial.write(DATO);
    Serial.println('\r\n'); 
     Serial.println("dato" + DATO);

    
      if(DATO == '1') { MotorForward();}
      else if(DATO == '3') {MotorBackward();}
      else if(DATO == '4') {TurnLeft();}
      else if(DATO == '2') {TurnRight();}
      else if(DATO == '0') {MotorStop(); }  //motor stop
      
      else if(DATO == 'a') SetSpeedCarMax ();
      else if(DATO == 'b') SetSpeedCarUp();
      else if(DATO == 'c') SetSpeedCarDown();
      
      else if(DATO == 'd') {goLuces();}
      else if(DATO == 'e') {goLucesOff();}
      else if(DATO == 'f') {led_blink();}
    
      else if(DATO == 'h') { rotarCabeza_H_I(); }//rotar horizontal izquierda
      else if(DATO == 'i') { rotarCabeza_H_D(); } //rotar horizontal derecha
      else if(DATO == 'j') { rotarCabeza_H_90(); } //rotar horizontal derecha
      else if(DATO == 'k') { goLucesColor(); } 
      else if(DATO == 'l') { goLucesOffColor(); }
      
  }
  delay(50);
  
}


// Funciones de motores
/* FORWARD */
void MotorForward(){
  Serial.println(speedCar);
  goLuces();
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

/* BACKWARD */
void MotorBackward(){
  Serial.println(speedCar);
  goLucesColor();
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB
  
  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
/* TURN RIGHT */
void TurnRight(){
  Serial.println(speedCar);

  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);  
}

/* TURN LEFT */
void TurnLeft(){
   Serial.println(speedCar);
  analogWrite(ENA, speedCar);  // velocidad mediante PWM en ENA
  analogWrite(ENB, speedCar);  // velocidad mediante PWM en ENB

  digitalWrite(IN1,LOW);  
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);  
}

void MotorStop(){
  analogWrite(ENA, speedOff);    // deshabilita motor A
  analogWrite(ENB, speedOff);    // deshabilita motor B
  goLucesOffColor();
  goLucesOff();
}

//  -----------------------  SPEED  -----------------------
int SetSpeedCarMax(){
  speedCar = speedMAX;
    Serial.print("speedCar "+ speedCar);

  delay(90);  
}


int SetSpeedCarUp(){
  speedCar = speedMED;
    Serial.print("speedCar "+ speedCar);

  delay(90);  
}


int SetSpeedCarDown(){
  speedCar = speedMIN;
  delay(90);  
}

//--------------------- SERVO --------------------- 

int rotarCabeza_H_I(){
  if(contador == 0){ contador = 90; }
  contador = contador + 25;               //Incrementa el contador
  delay (300);           // Retardo
  myservoH.write(contador); 
 }
 
void rotarCabeza_H_D(){ 
 if(contador == 0){ contador = 90;  }
 contador= contador - 25;               //Incrementa el contador
 delay (300);           // Retardo
 myservoH.write(contador);
}

void rotarCabeza_H_90(){ myservoH.write(90); }

// ----------------- LUCES  -----------------
void led_blink(){
 int var = 0;
  while (var < 3) {
    digitalWrite(PinLED0,  HIGH);
    delay(90); 
    digitalWrite(PinLED1, HIGH);
    delay(90);
    digitalWrite(PinLED2, HIGH);
    delay(90);
    digitalWrite(PinLED3, HIGH);
    delay(90);

    digitalWrite(PinLED0,  LOW);
    delay(90); 
    digitalWrite(PinLED1, LOW);
    delay(90);
    digitalWrite(PinLED2, LOW);
    delay(90); 
    digitalWrite(PinLED3, LOW);
    delay(90); 
    
    var ++;
  }
}

void goLuces(){ 
  digitalWrite(PinLED0, HIGH);
  digitalWrite(PinLED1, HIGH);
}

void goLucesOff(){ 
  digitalWrite(PinLED0, LOW);
  digitalWrite(PinLED1, LOW);
}

void goLucesColor(){ 
  digitalWrite(PinLED2, HIGH);
  digitalWrite(PinLED3, HIGH);
}

void goLucesOffColor(){ 
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED3, LOW);
}

