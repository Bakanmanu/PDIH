// C++ code
//
void setup()
{
  // Led Rojo
  pinMode(13, OUTPUT);
  // Led Amarillo
  pinMode(12, OUTPUT);
  // Led Verde
  pinMode(11, OUTPUT);
}

void loop()
{
  // Led Rojo
  digitalWrite(13, HIGH);
  delay(1500); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  
  // Led Amarillo
  digitalWrite(12, HIGH);
  delay(1500); // Wait for 1000 millisecond(s)
  digitalWrite(12, LOW);
  
  // Led Verde
  digitalWrite(11, HIGH);
  delay(1500); // Wait for 1000 millisecond(s)
  digitalWrite(11, LOW);
  
  
  
  
  
}