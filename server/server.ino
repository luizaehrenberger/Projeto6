int pinServer = 8; 
float baudrate = 9600;
float periodo1 = 1/baudrate;
float periodo2 = 0.5*periodo1;
int time = 16000000/9600;
int msg;
float clck_num = floor(16000000/baudrate);

void setup() {
  pinMode(pinServer, INPUT);
  Serial.begin(baudrate);
}

// float delay_ard(float tempoDeEspera = 1, float baudrate = 9600, float T0 = 0){
//   double clock = 1 / (16 * pow(10, 6)); // tempo de 1 clock (T = 1/frequência), onde a frequência = 16MHz
//   double T = 1 / baudrate; // tempo entre cada clock, em segundos
//   int numeroDeClocks = floor(time); // número de clocks a esperar, arredondado para o inteiro mais próximo
//   for (int i = 0; i < int(numeroDeClocks * tempoDeEspera); i++){ asm("NOP"); } // aguarde o tempo especificado
// }

void delay_ard(float t_espera){
  for(int i=0; i<clck_num*t_espera; i++){
    asm("nop");
    }
}

void loop() {
  //Serial.println(digitalRead(pinServer));
  if (digitalRead(pinServer)== 0){
    int q_1s = 0;
    delay_ard(1.5);
    int bitAtual = digitalRead(pinServer); 
    for (int i = 0; i < 8; i++){
      delay_ard(1);
      if (bitAtual == 1){
        q_1s++; // Conta número de bits
      }
      msg |= (bitAtual << i); // Adiciona o bit atual na mensagem
    }
    int bitParidade = digitalRead(pinServer); // lê o bit de paridade
    int bitParidade_msg = (q_1s % 2); // Cálculo do bit de paridade da mensagem 
    if (bitParidade == bitParidade_msg) {
      //Serial.print("Dados Recebidos: ");
      Serial.println(msg);
      Serial.println("Bit de paridade está correto!");
    } else{
      Serial.println("ERRO, bit de paridade está incorreto");
    }
    delay_ard(1);
  }
}