#include <ModbusMaster.h>
#define MAX485_DE  2
#define MAX485_RE  2
// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_RE, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE, 0);
  digitalWrite(MAX485_DE, 0);
}

void DeclareOutput(){
  pinMode(MAX485_RE, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE, 0);
  digitalWrite(MAX485_DE, 0);
 }

void SetSerial(long BAUD, int RX, int TX){
  Serial.begin(BAUD, SERIAL_8N1, RX, TX);
}

void SetNode(int ID){
  node.begin(ID,Serial); // Inicializa el objeto ModbusMaster con el ID del esclavo y el objeto Serial
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

uint32_t* ReadAddress(ModbusMaster& node, uint16_t registroInicial, uint16_t cantidadDatos)
{
  uint32_t result;
  uint32_t* data = new uint32_t[cantidadDatos];
  
  result = node.readInputRegisters(registroInicial - 1, cantidadDatos);
  if (result == node.ku8MBSuccess)
  {
    for (uint16_t i = 0; i < cantidadDatos; i++)
    {
      data[i] = node.getResponseBuffer(i);
    }
  }
  else
  {
    Serial.println("Error al leer los registros.");
    delete[] data; // Liberar memoria en caso de error
    return nullptr;
  }

  return data;
}
