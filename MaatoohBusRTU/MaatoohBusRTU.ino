#include "MaatoohBusRTU.h"

void setup()
{
  DeclareOutput();
  SetSerial(9600,16,17);
  SetNode(1);
}

void loop()
{
  uint32_t* corrienteFases = ReadAddress(node, 1100, 3);
  if (corrienteFases != nullptr)
  {
    Serial.println("");
    Serial.print("Corriente de fase A: ");
    Serial.println(corrienteFases[0]);
    Serial.print("Corriente de fase B: ");
    Serial.println(corrienteFases[1]);
    Serial.print("Corriente de fase C: ");
    Serial.println(corrienteFases[2]);
    delete[] corrienteFases; // Liberar memoria asignada dinámicamente
  }

  delay(1000);
}
