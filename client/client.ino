//Definindo os parâmetros da transmissão
char msg = 'A'; //Mensagem a ser enviada (A)
int msg_b = int(msg); // Transformando mensagem em inteiro
int clientPin = 8; //Pin a ser utilizado (8)
float baudrate = 9600; //Baudrate fixo em 9600

int contarBitsUmEmByte(unsigned char byte) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((byte & (1 << i)) != 0) { 
            count++;
        }
    }
    return count;
}

int bitParidade = contarBitsUmEmByte(msg_b)%2;

//16M é a frequencia natual do Arduino UNO (quao rapido manda informação)
//16M/Baudrate é qtd de clocks

void setup() {
  pinMode(clientPin, OUTPUT);
  Serial.begin(baudrate);
  digitalWrite(clientPin, HIGH);
  delay(1000);
  Serial.println("Inicio do loop");
}

void delay_ard(float t_espera = 1, float baudrate = 9600){
  float clck_num = floor(16000000/baudrate);
  for(int i=0; i< int(clck_num*t_espera); i++){
    asm("NOP");
    }
}


void loop(){
 ////////////////////////////StartBit///////////////////////
  //Startbit
  digitalWrite(clientPin,LOW);
  int qtd = 0;
  delay_ard();
  
////////////////////////////////PAYLOAD///////////////////////////////
  //Enviando a mensagem
  for(int b=0; b<8; b++){
    int bitAtual = 1 & (msg_b >> b); //
//    Serial.println(bitAtual);
    digitalWrite(clientPin, bitAtual);
    if (bitAtual == 1){
      qtd++;
    }
    delay_ard();
  }
/////////////////////////////////////////////////////////////////////
  //BitParidade
  digitalWrite(clientPin, bitParidade);
  delay_ard();
  
  //BitStop
  digitalWrite(clientPin, HIGH);
  delay_ard();

  //Serial.println("Fim do Loop");
  Serial.println(msg, HEX);
  delay(2000);
  
}