// C++ code

const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 11;
const int LED4 = 10;

const int time = 750;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop()
{
  digitalWrite(LED1, HIGH);
  delay(time + 250);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(time);
  
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(time);

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(time + 250);

  digitalWrite(LED4, LOW);
  digitalWrite(LED3, HIGH);
  delay(time);
  
  digitalWrite(LED3, LOW);
  digitalWrite(LED2, HIGH);
  delay(time);

  digitalWrite(LED2, LOW);  

}