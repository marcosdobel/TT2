#include <SoftwareSerial.h>
#include <Wire.h>

 
#define RE 8
#define DE 7

//const byte ph[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
const byte ph[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};
byte values[11];
SoftwareSerial mod(2, 3); // UART pins
 

 
void setup()
{
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}
 
void loop()
{
  byte val;  // Instruccion que se envia para que el sensor la lea en la direccion 0x01
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(ph, sizeof(ph)) == 8)
  {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 11; i++) // Respuesta como salida donde obtendremos el valor de pH
    {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
   // float offset =18;
   float offset=0;
  float soil_ph = float(values[4])/ 10 - offset; //  El valor de pH haxadecimal se convierte en decimal 
 
  Serial.print("Soil Ph: ");
  Serial.println(soil_ph, 1);
 

  delay(1000);
}
