#define redpin  10    //Se define el pin 10 del Arduino para conectar el PIN RED del modulo KY-011
#define greenpin  9  //Se define el pin 9 del Arduino para conectar el PIN GREEN del modulo KY-011
int val;
 
void setup()
{
  //Se definen los pines como salidas
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT); 
}

void loop()
{

//Se cambia a color verde por 1 segundo
  digitalWrite(redpin, LOW);
  digitalWrite(greenpin, HIGH);
  delay(1000);

//Se enciende el color rojo por 1 segundo
  digitalWrite(redpin, HIGH);
  digitalWrite(greenpin, LOW);
  delay(1000);  
  
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, LOW);
  
  delay(500);  

  for(val = 255; val > 0; val--) { 
    analogWrite(redpin, val); //dim red
    analogWrite(greenpin, 255 - val); // brighten green
    
    delay(15);
  }
  for(val = 0; val < 255; val++) { 
    analogWrite(redpin, val); //brighten red
    analogWrite(greenpin, 255 - val); //dim green
  
    delay(15);
  }    

  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, LOW);  
  
  delay(1000);
}
