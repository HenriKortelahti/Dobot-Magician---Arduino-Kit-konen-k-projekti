// Uncomment one of these to enable another type of serial interface
#define I2C
//#define UART
//#define SPI_SS
   
#ifdef I2C

#include <Pixy2I2C.h>
Pixy2I2C pixy;

#else 
#ifdef UART

#include <Pixy2UART.h>
Pixy2UART pixy;

#else 
#ifdef SPI_SS

#include <Pixy2SPI_SS.h>
Pixy2SPI_SS pixy;

#else

#include <Pixy2.h>
Pixy2 pixy;

#endif
#endif
#endif

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  pixy.init();
}

void loop()
{ 
  int k;
  int i; 
  // grab blocks!
  k = pixy.ccc.getBlocks();
  if (k < 0)
  {
    Serial.print(k);Serial.print("\n");
  }
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }
  }  
}