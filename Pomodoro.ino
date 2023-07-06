#include <SevSeg.h>//Pinagem mostrador de 7 segmentoss usado https://prnt.sc/SmdSGl9g9pqz
#define VintCinco 12
#define Cinco 5
#define PinLR 2
#define PinLG 13
//Pinagem mostrador de 7 segmentoss usado https://prnt.sc/SmdSGl9g9pqz
SevSeg sevseg; // Cria uma instância do objeto SevSeg
unsigned long Tempo = 0, TEmQDes = 0;
int Es = 0;
//Definicoes do display 7 segmentos
byte numDigits = 3;
byte digitPins[] = {10, 11, 12};
byte segmentPins[] = {3, 4, 5, 6, 7, 8, 9};
bool resistorsOnSegments = false; // 'false' se os resistores estiverem ligados nos pinos de digito
byte hardwareConfig = COMMON_ANODE; //Tipo de display - Anodo Comum
bool updateWithDelays = false;
bool leadingZeros = false; //Use 'true' se voce desejar completar o display com zeros
bool disableDecPoint = false; // Use 'true' se o ponto decimal nao existir ou nao for usado
//Armazena o valor do contador
int contador = 0;
//Ligado ao pino "coletor" do sensor óptico - Porta A5 ao Arduino
int pinosensor = A5;
//Armazena o valor lido pelo sensor (0 ou 1)
int leitura;
void setup(){
  pinMode(PinLR, OUTPUT);
  pinMode(PinLG, OUTPUT);
  Serial.begin(9600);
  //Inicializa o display com as definicoes anteriores
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  //Controla a luminosidade - 0 a 100
  sevseg.setBrightness(90);
  //Define o pino do sensor optico como entrada
  pinMode(pinosensor, INPUT);
}

void loop() {
  Tempo = millis() / 1000; //Transforma em minutos
  if ( (Es == 0) && ((Tempo - TEmQDes) < VintCinco)){
    digitalWrite(PinLG, LOW);
    digitalWrite(PinLR, HIGH);
  } else if( (Es == 0) && ((Tempo - TEmQDes) >= VintCinco)){
    Es = 1;
    TEmQDes = Tempo;  //Reseta
    
  } else if( (Es == 1) && ((Tempo - TEmQDes) < Cinco)){
    digitalWrite(PinLG, HIGH);
    digitalWrite(PinLR, LOW);
  } else if( (Es == 1) && ((Tempo - TEmQDes) >= Cinco)){
    Es = 0;
    TEmQDes = Tempo;  //Reseta
  }
  sevseg.setNumber(round(Tempo - TEmQDes), 0); // Define o número a ser exibido no mostrador
  sevseg.refreshDisplay(); // Atualiza o mostrador
  Serial.println("Estado: "+ String(Es) +" Tempo: " + String(Tempo - TEmQDes));
}
