// C++ code
//
// Constantes de los pines utilizados
const int LEDRojo = 13;
const int LEDAmarillo = 12;
const int LEDVerde = 11;
const int Button = 7;

// Variables que almacenarán los valores del botón
int buttonState = LOW;		// estado actual del boton
int lastButtonState = -1;	// Ultimo estado del boton(Le asignamos -1 para que sea distinto que el estado inicial y encienda los leds amarillo y verde desde un inicio

void setup()
{
  // Led Rojo
  pinMode(LEDRojo, OUTPUT);
  // Led Amarillo
  pinMode(LEDAmarillo, OUTPUT);
  // Led Verde
  pinMode(LEDVerde, OUTPUT);
  //Boton
  pinMode(Button, INPUT);  
}

void loop()
{
  // Leemos el valor del pulsador
  buttonState = digitalRead(7);
  
  // Si es distinto al valor de la anterior iteración realiza las acciones
  if(buttonState != lastButtonState){
	// Si el boton es pulsado, enciende el led rojo y apaga el resto
    if(buttonState == HIGH){
      digitalWrite(LEDRojo, HIGH);	// Encendemos led rojo
      digitalWrite(LEDAmarillo, LOW);	// Apagamos led amarillo
      digitalWrite(LEDVerde, LOW);	// Apagamos led verde
    }else{// Una vez dejamos de pulsar el boton, se apaga el led rojo y se encienden el resto
      digitalWrite(LEDRojo, LOW);
      digitalWrite(LEDAmarillo, HIGH);
      digitalWrite(LEDVerde, HIGH);
    }
  }
  // Cambiamos al último estado leído
  lastButtonState = buttonState;
  
 
}