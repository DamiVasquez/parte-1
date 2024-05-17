//Segunda parte de la practica numero 6.
/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM / EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Interfaces de visualización e Interacción
   Dev: Damasco Oxcal Vasquez
   Fecha: 17 de mayo
*/

#include <Keypad.h>; // Con esta linea llamamos a la librería Keypad para que arduino reconozca el teclado
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h> //libreria que me permite usar el servo
//Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

char contrasena[]="40390096"; // En esta linea creamos la constante de cadena llamada contraseña (el numero 2222 puede ser cambiado)
char codigo[8]; // Creamos otra constante, en esta se guardaran los caracteres que presionemos en nuestro teclado matricial 4x4
int cont=0; // Esta es una variable que nos servirá más adelante
int LedVerde=12;
int LedRojo=2; 
const byte filas_teclado = 4; //Este código se estable para definir que nuestro teclado tiene 4 filas 
const byte columnas_teclado = 4; //Este código se estable para definir que nuestro teclado tiene 4 columnas
const int pinBuzzer = 17;//pin 17 para el pinBuzzer.

char hexaKeys[filas_teclado][columnas_teclado] = //En el siguiente matriz se agregan en orden las teclas que posee nuestro teclado
{
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
  
byte pines_filas[filas_teclado] = {11, 10, 9, 8}; // Estos son los pines de conexión de Arduino de las columnas
byte pines_columnas[columnas_teclado] = {7, 6, 5, 4}; //Estos son los pines de conexión de Arduino de las filas
  
Keypad oxcalv = Keypad(makeKeymap(hexaKeys), pines_filas, pines_columnas, filas_teclado, columnas_teclado); //En este punto el teclado se inicia y realiza el mapeo de sus teclas con respecto a la matriz colocada arriba

//Directivas de preprocesador
#define pin_Servo 3


//Constructor
Servo Servo_Oxcal;  //mi servo

void setup()
{
    // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Puerta Cerrada");

 pinMode(LedVerde, OUTPUT); //El pin 2 sera nuestra salida digital 
 pinMode(LedRojo, OUTPUT); //El pin 3 sera nuestra salida digital
 Serial.begin(9600); //Se inicia el puerto serial
  
 //Servo_Oxcal.attach(pin_Servo);           //Especifico que en el pin5 voy a usar un servomotor.
 Servo_Oxcal.attach(pin_Servo);   //Especifico que en el pin5 voy a usar un servomotor.

}
  
void loop()
{
    char tecla = oxcalv.getKey(); //esta linea indica que el carácter presionado se guardara en la variable customKey
 if (tecla != NO_KEY) //Con este siclo preguntamos si se presiono una tecla, si se presiono entonce el ciclo continua
 {
 codigo[cont]=tecla; //se guardaran los caracteres presionados en codigo[cont]
 Serial.print(codigo[cont]); //Se imprime en nuestro monitor serial lo que este guardado en codigo[cont]
 cont=cont+1; //incrementamos la variable cont (esto con el fin de tener los 8 dígitos que requerimos)
 if(cont==8) //Ahora comienza otro siclo if, en el cual se pregunta si ya hay 8 datos guardados y si es así entonce el siclo continua
  
 {
  
 if(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3])
 {
  digitalWrite(LedRojo, LOW);
  digitalWrite(LedVerde, HIGH);
  Servo_Oxcal.write(90);
 Serial.println("Puerta Abierta"); //si la contraseña es correcta entonces se imprime ""Password correcta")
 lcd.setCursor(0,1);
 lcd.print("Puerta Abierta");
   tone(pinBuzzer, 900);//generar tono de 250Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono
  delay(1000);
   tone(pinBuzzer, 900);//generar tono de 250Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono  
   delay(10000);
   digitalWrite(LedVerde, LOW);
   Servo_Oxcal.write(0);

 }
 if(codigo!=contrasena) //empieza un nuevo ciclo, esta vez indicamos si el código es diferente que la contraseña siga con el siclo
 {
  digitalWrite(LedRojo, HIGH);
  Serial.println("Puerta Cerrada"); // se imprime que que la Password es incorrecta
  lcd.setCursor(0,1);
  lcd.print("Puerta Cerrada");
   tone(pinBuzzer, 1500);//generar tono de 1500Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono
  delay(1000);
   tone(pinBuzzer, 1500);//generar tono de 1500Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono
  delay(1000);
   tone(pinBuzzer, 1500);//generar tono de 1500Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono
  delay(1000);
   tone(pinBuzzer, 1500);//generar tono de 1500Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono
  delay(1000);
   tone(pinBuzzer, 1500);//generar tono de 1500Hz durante 1000 ms.
  delay(1000);
   noTone(pinBuzzer);//detener tono
  delay(1000); 
 }
   cont=0; //resetear a 0 la variable cont
 }
 }
}
