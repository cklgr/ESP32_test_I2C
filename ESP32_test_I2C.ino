// ESP32 I2C Scanner
// Based on code of Nick Gammon  http://www.gammon.com.au/forum/?id=10896
// ESP32 DevKit - Arduino IDE 1.8.5
// Device tested PCF8574 - Use pullup resistors 3K3 ohms !
// PCF8574 Default Freq 100 KHz
//
// https://www.esp32.com/viewtopic.php?t=4742
//
// LO COJO Y LO UNICO QUE HAGO ES ASIGNAR PINES PARA I2C

/*  Funciona, en la CAM detecta 2,  el PCA adafruit sin enchufar.
 *   para el PCA adafruit detecta La 40, la otra sera la camara?
 *   Found address: 64 (0x40)
 *   Found address: 112 (0x70)
 *   
 *   MOSQUEO, DETECTA LOS DOS INCLUSO SIN ALIMENTAR EL PCA, SIN TIERRA NO, SI QUITO SDA PARA
 *   
 *   #define I2C_SDA_NUM 14 #define I2C_SCL_NUM 15 Los 1ºs probados
 *   #define I2C_SDA_NUM 13 #define I2C_SCL_NUM 12
 *   #define I2C_SDA_NUM 2 #define I2C_SCL_NUM 12
 *   
 *   YA QUE ESTOY, EXPERIMENTOS A LO GRANDE...
 *   
 *   #define I2C_SDA_NUM 16 #define I2C_SCL_NUM 12
 *   #define I2C_SDA_NUM 12 #define I2C_SCL_NUM 16
 *   
 *   AHORA A RIZAR EL RIZO...
 *   #define I2C_SDA_NUM 0 #define I2C_SCL_NUM 16  // ESTO ES YA MAS QUE MOSQUEO...
 *   #define I2C_SDA_NUM 16 #define I2C_SCL_NUM 0   
 *   
 *   https://tasmota.github.io/docs/PCA9685/  AQUI DICEN QUE LO DE 0X70 ES NORMAL
*/
#include <Wire.h>

#define I2C_SDA_NUM 16
#define I2C_SCL_NUM 0

void setup()
{
  Serial.begin (115200);  
  Wire.begin (I2C_SDA_NUM, I2C_SCL_NUM);   // sda= GPIO_21 /scl= GPIO_22
}

void Scanner ()
{
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  Wire.begin(I2C_SDA_NUM, I2C_SCL_NUM);
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);          // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);     // PCF8574 7 bit address
      Serial.println (")");
      count++;
    }
  }
  Serial.print ("Found ");      
  Serial.print (count, DEC);        // numbers of devices
  Serial.println (" device(s).");
}

void loop()
{
  Scanner ();
  delay (100);
}
