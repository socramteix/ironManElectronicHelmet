#include <Servo.h>
//servo 1
Servo myservo;
Servo myservo1;
int val; // variable for reading the pin status
int val2; // variable for reading the delayed/debounced status
int buttonState = 0;
int servostatus = 0;
int botaoPin = 2; // porta aonde o pino será conectado, pode ser qualquer porta digital
int ledPin1 = 5; //pino do led 1 a porta deve ser PWM
int ledPin2 = 6;//pino do led 2 a porta deve ser PWM
int valorInicial = 0; //valor inicial do servo, tipo 0 graus
int valorFinal = 90;  //valor final do servo, tipo 90 graus
int portaServo1 = 9;
int portaServo2 = 10;
//Variável abaixo para quando o led irá piscar após fechar a tampa. Neste caso o led pisca depois de 1s.
int tempoEspera = 1000; //tempo em miliSegundos (1000 = 1s)

void setup() {// run once, when the sketch starts
  myservo.attach(portaServo1);
  myservo1.attach(portaServo2);
  pinMode(botaoPin,  INPUT);
  pinMode(ledPin1,   OUTPUT);
  pinMode(ledPin2,   OUTPUT);
  buttonState = digitalRead(botaoPin);
  myservo.write(90);
  myservo1.write(90);
  Serial.begin(9600);
}

void fecharTampa(){
  myservo.write(180);
  myservo1.write(0);
}

void abrirTampa(){
  myservo.write(90);
  myservo1.write(90);
}

void piscaLed(){
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(50);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  delay(50);
}

//Efeito fading, ascende devagarinho
void ascendeLed(){
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin1, fadeValue);
    analogWrite(ledPin2, fadeValue);
    delay(30);
  }
}

void loop() { // run over and over again
  
  val = digitalRead(botaoPin); //lê o botão
  delay(10); // 10 milliseconds is a good amount of time
  val2 = digitalRead(botaoPin); //lê o botão de novo pra ter certeza
  if (val == val2) { //As duas leituras forem consistentes?
    if (val != buttonState) { //Verifica se mudou o estado do botão
      if (val == LOW) { //o botão está pressionado?
        if (servostatus == 0) { // is the light off?
          servostatus = 1; // turn light on!
          fecharTampa();
          delay(tempoEspera);
          piscaLed();
          //Efeito fading
          ascendeLed();
        }
        else {
          servostatus = 0; // apaga led
          digitalWrite(ledPin1, LOW);
          digitalWrite(ledPin2, LOW);
          abrirTampa();
        }
      }
    }
    buttonState = val; // save the new state in our variable
  }
}
