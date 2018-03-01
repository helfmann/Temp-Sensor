#include <SPI.h>

#define SS 10;  //chip select pin
#define MOSI 11;  //master out slave in pin
#define MISO 12;  //master in slave out pin
#define CLK 13;  //clock pin

unsigned int data;
byte DACA = B00011000;  //send to set channel A on DAC
byte DACB = B00011001;  //send to set channel B on DAC
byte bothDAC = B00011111;  //send to set both channels on DAC

word bothPower = 39900;  //will have to adjust to change output

word fullOff = 0xffff;   //turns selected channel(s) of DAC off
word fullOn = 0x0000;  //turns selected channel(s) of DAC to full power
word halfPower = 0x2ee0;  //turns selected channel(s) of DAC to half power


const int slaveSelectPin = 10;  

void setup()
{
  //Serial.begin(115200);  // Serial0 @ 115200 (115200) Baud
  pinMode(slaveSelectPin,OUTPUT);   //must include for spi
  SPI.begin();  //initialize spi communications
  SPI.setDataMode(SPI_MODE1);  //set spi communications to mode 1 standards
  SPI.setClockDivider(SPI_CLOCK_DIV2);  //set spi clock to 4MHz (16MHz system clock, 2 clocks per cycle, divided by 2)
  SPI.setBitOrder(MSBFIRST);  //set to most sig bit first
  digitalWrite(10, HIGH);  //set chip select pin high as SS on chip is active low
  
  delay(200);  //wait 200ms
  digitalWrite(10,LOW);  //set SS low to begin communications
  SPI.transfer(DACA);  //writes to DAC to set both channels
  data= highByte(bothPower);  //gets the first 8 bits of 16 bit value
  SPI.transfer(data);  //writes first 8 bits of 16 bit value from above
  data= lowByte(bothPower);  //gets the second 8 bits of 16 bit value
  SPI.transfer(data);  //writes the second 8 bits of 16 bit value from above
  digitalWrite(10, HIGH);  //set SS high to end communications

  digitalWrite(10,LOW);  //set SS low to begin communications
  SPI.transfer(DACB);  //writes to DAC to set both channels
  data= highByte(bothPower);  //gets the first 8 bits of 16 bit value
  SPI.transfer(data);  //writes first 8 bits of 16 bit value from above
  data= lowByte(halfPower);  //gets the second 8 bits of 16 bit value
  SPI.transfer(data);  //writes the second 8 bits of 16 bit value from above
  digitalWrite(10, HIGH);  //set SS high to end communications
}

void loop()
{
  //nothing in loop 
}
