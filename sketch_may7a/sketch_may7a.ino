#include <Servo.h>
const int ledPin = 7; //Indicador de slot
const int ledmodo = 8; //Indicador de Modo.

const int servo2=9;
const int servo3=10;
const int servo4=11;
const int servo1=3;

const int control1=A1;
const int control2=A2;
const int control3=A3;
const int control4=A4;

const int cambiomodo=4;
const int guardar=5;
const int reproducir=6;

int adc1=0;
int adc2=0;
int adc3=0;
int adc4=0;

int angulo1=0;
int angulo2=0;
int angulo3=0;
int angulo4=0;

int modo=1;

struct ConfiguracionServos 
{
  int servo1;
  int servo2;
  int servo3;
  int servo4;
};

ConfiguracionServos configuraciones[4];
int configuracionActual = 0;
int indiceReproduccion = 0;

Servo servom1;
Servo servom2;
Servo servom3;
Servo servom4;

int leerAngulo(const int pinADC)
{
  int valorADC = analogRead(pinADC);
  return map(valorADC, 0, 1023, 0, 180);
}

void setup() {
  Serial.begin(9600);//comunicación serial con BuadRate de 9600
  servom1.attach(servo1);//La salida del servo1 en el pin 3
  servom2.attach(servo2);//La salida del servo1 en el pin 9
  servom3.attach(servo3);//La salida del servo1 en el pin 10
  servom4.attach(servo4);//La salida del servo1 en el pin 11
  // Inicializar todas las configuraciones a 0
  for (int i = 0; i < 4; i++) {
    configuraciones[i].servo1 = 0;
    configuraciones[i].servo2 = 0;
    configuraciones[i].servo3 = 0;
    configuraciones[i].servo4 = 0;
  }
  pinMode(ledPin, OUTPUT);
  pinMode(ledmodo, OUTPUT);
  pinMode(cambiomodo, INPUT_PULLUP);
  pinMode(guardar, INPUT_PULLUP);
  pinMode(reproducir, INPUT_PULLUP);
}

void loop() 
{
  if(digitalRead(cambiomodo)==LOW)
  {
    delay(100);
    if(digitalRead(cambiomodo)==LOW)
    {
      modo = (modo == 1) ? 2 : 1;
    }
  }
 
  switch(modo)
  {
    case 1:
      digitalWrite(ledmodo, HIGH);
      angulo1 = leerAngulo(control1);
      angulo2 = leerAngulo(control2);
      angulo3 = leerAngulo(control3);
      angulo4 = leerAngulo(control4);
      servom1.write(angulo1);
      servom2.write(angulo2);
      servom3.write(angulo3);
      servom4.write(angulo4);
      comunicacion(angulo1, angulo2, angulo3, angulo4);
      break;
    case 2:
      digitalWrite(ledmodo, LOW);
      if(digitalRead(guardar)==LOW)
      {
        delay(100);//Antirebote
        if(digitalRead(guardar)==LOW)
        {
          
          configuraciones[configuracionActual].servo1 = angulo1;
          configuraciones[configuracionActual].servo2 = angulo2;
          configuraciones[configuracionActual].servo3 = angulo3;
          configuraciones[configuracionActual].servo4 = angulo4;

          for (int i=0; i<= configuracionActual; i++ )//Indicador de poscicion guardada
          {
            digitalWrite(ledPin, HIGH);
            delay(150);
            digitalWrite(ledPin, LOW);
            delay(150);
          }
          configuracionActual=(configuracionActual +1)%4;
          Serial.print("Angulo1: ");
          Serial.print(angulo1);
          Serial.print(" Angulo2: ");
          Serial.print(angulo2);
          Serial.print(" Angulo3: ");
          Serial.print(angulo3);
          Serial.print(" Angulo4: ");
          Serial.println(angulo4);
      
        }
      }
      if(digitalRead(reproducir)==LOW)
      {
        delay(100); // Antirrebote
        if (digitalRead(reproducir) == LOW) 
        {
          angulo1=configuraciones[indiceReproduccion].servo1;
          angulo2=configuraciones[indiceReproduccion].servo2;
          angulo3=configuraciones[indiceReproduccion].servo3;
          angulo4=configuraciones[indiceReproduccion].servo4;
          servom1.write(angulo1);
          servom2.write(angulo2);
          servom3.write(angulo3);
          servom4.write(angulo4);
          comunicacion(angulo1, angulo2, angulo3, angulo4);
          for (int i = 0; i <= indiceReproduccion; i++)
          {
           digitalWrite(ledPin, HIGH);  
           delay(150);
           digitalWrite(ledPin, LOW);
           delay(150);
          }
          indiceReproduccion = (indiceReproduccion + 1) % 4;
        }
      }
      break;
  }
}


void comunicacion(const int angle1, const int angle2, const int angle3, const int angle4)
{
  Serial.print("Angulo1: ");
  Serial.print(angle1);
  Serial.print(" Angulo2: ");
  Serial.print(angle2);
  Serial.print(" Angulo3: ");
  Serial.print(angle3);
  Serial.print(" Angulo4: ");
  Serial.println(angle4);
}
