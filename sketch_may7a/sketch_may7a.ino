#include <Servo.h>
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

Servo servom1;
Servo servom2;
Servo servom3;
Servo servom4;


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
}

void loop() 
{
  adc1=analogRead(control1); //Leemos los adc´s
  adc2=analogRead(control2); //Leemos los adc´s
  adc3=analogRead(control3); //Leemos los adc´s
  adc4=analogRead(control4); //Leemos los adc´s

  angulo1=map(adc1,0, 1023, 0, 180);
  angulo2=map(adc2,0, 1023, 0, 180);
  angulo3=map(adc3,0, 1023, 0, 180);
  angulo4=map(adc4,0, 1023, 0, 180);
  if(digitalRead(cambiomodo)==LOW)
  {
    if(modo==1)
    {
      modo=2;
    }
    else if(modo==2)
    {
      modo=1;
    }
  }else if(digitalRead(cambiomodo)==HIGH)
  {
    modo=modo;
  }
  switch(modo)
  {
    case 1:
      servom1.write(angulo1);
      servom2.write(angulo2);
      servom3.write(angulo3);
      servom4.write(angulo4);
      break;
    case 2:
      if(digitalRead(guardar)==LOW)
      {
        // Guardamos la configuración actual
          configuraciones[configuracionActual].servo1 = angulo1;
          configuraciones[configuracionActual].servo2 = angulo2;
          configuraciones[configuracionActual].servo3 = angulo3;
          configuraciones[configuracionActual].servo4 = angulo4;
      
          configuracionActual=(configuracionActual +1)%4;
      }
      if(digitalRead(reproducir)==LOW)
      {
      
      }
      break;
  }
  Serial.print("Angulo1: ");
  Serial.print(angulo1);
  Serial.print(" Angulo2: ");
  Serial.print(angulo2);
  Serial.print(" Angulo3: ");
  Serial.print(angulo3);
  Serial.print(" Angulo4: ");
  Serial.println(angulo4);
}
