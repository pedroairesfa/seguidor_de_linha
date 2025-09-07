#define SENSOR_DIREITO 7 // Pino do sensor
#define SENSOR_ESQUERDO 6
#define VELOCIDADE_MOTOR_D 150
#define VELOCIDADE_MOTOR_E 200

// Motor direito
int enMotorDir = 3; // Enable do motor
int motorDirPin1 = 9; // Pino 1
int motorDirPin2 = 8; // Pino 2

// Motor esquerdo
int enMotorEsq = 5;
int motorEsqPin1 = 11;
int motorEsqPin2 = 10;

void setup() // Função padrão do arduino para setar pinos e configurações iniciais
{
  // Seta frequência em 7812.5 Hz
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // Seta os pinos do motor direito como pinos de saída/output (recebem informação)
  pinMode(enMotorDir, OUTPUT);
  pinMode(motorDirPin1, OUTPUT);
  pinMode(motorDirPin2, OUTPUT);

  pinMode(enMotorEsq, OUTPUT);
  pinMode(motorEsqPin1, OUTPUT);
  pinMode(motorEsqPin2, OUTPUT);

  // Seta os pinos dos sensores como entrada/input (fornecem informação) 
  pinMode(SENSOR_DIREITO, INPUT);
  pinMode(SENSOR_ESQUERDO, INPUT);
  rotateMotor(0, 0);
}

void loop() // Função padrão do arduino para realizar as ações, ela se repete (loop)
{

  // Branco = 0 e Preto = 1 para estes sensores
  int valorSensorEsq = !digitalRead(SENSOR_ESQUERDO); // Lógica negada para seguir linha branca
  int valorSensorDir = !digitalRead(SENSOR_DIREITO);

  // Ambos andam
  if (valorSensorDir == LOW && valorSensorEsq == LOW)
  {
    rotateMotor(VELOCIDADE_MOTOR_D, VELOCIDADE_MOTOR_E); // Função rotate que recebe as velocidades a serem enviadas pra cada motor 
  }

  // Vira pra esquerda
  else if (valorSensorDir == HIGH && valorSensorEsq == LOW)
  {
    rotateMotor(0, VELOCIDADE_MOTOR_E); // Direita não roda, esquerda roda 'certo'

  }

  // Vira pra direita
  else if (valorSensorDir == LOW && valorSensorEsq == HIGH)
  {
    rotateMotor(VELOCIDADE_MOTOR_D, 0);
  }

  // Para
  else
  {
    rotateMotor(0, 0);
  }

}

void rotateMotor(int velMotorDir, int velMotorEsq) // Função rotate que recebe os valores (inteiros) de velocidade e retorna nada
{
  // Os dois motores funcionam
  if (velMotorDir > 0 and velMotorEsq > 0)
  {
    digitalWrite(motorDirPin1, HIGH); // Escreve (write) de forma digital (true ou false)
    digitalWrite(motorDirPin2, LOW);
    
    digitalWrite(motorEsqPin1, HIGH);
    digitalWrite(motorEsqPin2, LOW);
  }

  // Só o motor direito funciona
  else if (velMotorDir > 0 and velMotorEsq == 0)
  {
    digitalWrite(motorDirPin1, HIGH);
    digitalWrite(motorDirPin2, LOW);

    digitalWrite(motorEsqPin1, LOW);
    digitalWrite(motorEsqPin2, LOW);
  }

  // Só o motor esquerdo funciona
  else if (velMotorEsq > 0 and velMotorDir == 0)
  {
    digitalWrite(motorDirPin1, LOW);
    digitalWrite(motorDirPin2, LOW);

    digitalWrite(motorEsqPin1, HIGH);
    digitalWrite(motorEsqPin2, LOW);
  }

  // Nenhum dos dois funcionam
  else
  {
    digitalWrite(motorEsqPin1, LOW);
    digitalWrite(motorEsqPin2, LOW);

    digitalWrite(motorDirPin1, LOW);
    digitalWrite(motorDirPin2, LOW);

  }

  // Liga (enable) o motor
  analogWrite(enMotorDir, abs(velMotorDir));
  analogWrite(enMotorEsq, abs(velMotorEsq));
}

// FIM 
