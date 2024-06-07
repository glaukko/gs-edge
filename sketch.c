#include <RTClib.h> // Biblioteca para Relógio em Tempo Real
#include <EEPROM.h>

int ph_sensor = A0;
int temperature_sensor = A1;
int turbidity_sensor = A2;
int tds_sensor = A3;

#define SERIAL_OPTION 0  // Opção de comunicação serial: 0 para desligado, 1 para ligado
#define UTC_OFFSET -3    // Ajuste de fuso horário para UTC-3

RTC_DS1307 RTC;

// Configurações da EEPROM
const int maxRecords = 100;
const int recordSize = 8; // Tamanho de cada registro em bytes
int startAddress = 0;
int endAddress = maxRecords * recordSize;
int currentAddress = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.begin();
  
  RTC.begin();    // Inicialização do Relógio em Tempo Real
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));


}

void loop() {
  DateTime now = RTC.now();
  // put your main code here, to run repeatedly:

//  Serial.print("Hora atual: ");
//  Serial.println(now.timestamp(DateTime::TIMESTAMP_FULL));

  // Calculando o deslocamento do fuso horário
  int offsetSeconds = UTC_OFFSET * 3600; // Convertendo horas para segundos
  now = now.unixtime() + offsetSeconds; // Adicionando o deslocamento ao tempo atual

  // Convertendo o novo tempo para DateTime
  DateTime adjustedTime = DateTime(now);

Serial.print(adjustedTime.second());
get_log();

if (adjustedTime.second()==0) {

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second


  // Mapear os dados

  int ph = map(analogRead(ph_sensor), 0, 1023, 0, 14);
  int temperature = map(analogRead(temperature_sensor), 0, 1023, 0, 40);
  int turbidity = map(analogRead(turbidity_sensor), 0, 1023, 0, 100);
  int tds = map(analogRead(tds_sensor), 0, 1023, 0, 1200);

  // Escrever dados na EEPROM

  //Serial.println(adjustedTime);
  EEPROM.put(currentAddress, now);
  EEPROM.put(currentAddress + 4, ph);
  EEPROM.put(currentAddress + 6, temperature);
  EEPROM.put(currentAddress + 8, turbidity);
  EEPROM.put(currentAddress + 10, tds);



  // Atualiza o endereço para o próximo registro
  getNextAddress();
}

  if (SERIAL_OPTION) {
    Serial.print(adjustedTime.day()); 
    Serial.print("/");
    Serial.print(adjustedTime.month()); 
    Serial.print("/");
    Serial.print(adjustedTime.year());
    Serial.print(" ");
    Serial.print(adjustedTime.hour() < 10 ? "0" : ""); // Adiciona zero à esquerda se hora for menor que 10
    Serial.print(adjustedTime.hour()); 
    Serial.print(":");
    Serial.print(adjustedTime.minute() < 10 ? "0" : ""); // Adiciona zero à esquerda se minuto for menor que 10
    Serial.print(adjustedTime.minute()); 
    Serial.print(":");
    Serial.print(adjustedTime.second() < 10 ? "0" : ""); // Adiciona zero à esquerda se segundo for menor que 10
    Serial.print(adjustedTime.second()); 
    Serial.print("\n");
  }

  delay(1000);
}

void getNextAddress() {
  currentAddress += recordSize;
  if (currentAddress >= endAddress) {
    currentAddress = 0; // Volta para o começo se atingir o limite
  }
}

void get_log() {
  //Serial.begin(9600);
  //Wire.begin();

  Serial.println("Data stored in EEPROM:");
  Serial.println("Timestamp\tPH\tTemperatura\tTurbidez\tTDS");

  for (int address = startAddress; address < endAddress; address += recordSize) {
    long timeStamp;
    int phInt, tempInt, turbidityInt, tdsInt;

    // Ler dados da EEPROM
    EEPROM.get(address, timeStamp);
    EEPROM.get(address + 4, phInt);
    EEPROM.get(address + 6, tempInt);
    EEPROM.get(address + 8, turbidityInt);
    EEPROM.get(address + 10, tdsInt);

    // Verificar se os dados são válidos antes de imprimir
    if (timeStamp != 0xFFFFFFFF) { // 0xFFFFFFFF é o valor padrão de uma EEPROM não inicializada
      Serial.print(timeStamp);
      Serial.print("\t");
      Serial.print(phInt);
      Serial.print("\t");
      Serial.print(tempInt);
      Serial.print("\t");
      Serial.print(turbidityInt);
      Serial.print("\t");
      Serial.print(tdsInt);
      Serial.print("\t");

      Serial.println();
      
      
    }
  }
}