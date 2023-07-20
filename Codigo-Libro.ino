#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//MODULO MP3
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

//lcedi2c
LiquidCrystal_I2C lcd(0x27, 16, 2);

//MANEJO ENCODER PULSADOR
const int enter = 4;
const int channelPinA = 2;
const int channelPinB = 3;
const int timeThreshold = 5;
long timeCounter = 0;
const int maxSteps = 255;
volatile int ISRCounter = 0;
int counter = 0;
bool IsCW = true;

//MENU
int menu = 0;
int nummenu = 0;
int menugeneral = 0;
int enterVal = 0;
int a = 0;
int b = 0;
int pagina = 0;
//paginas
//const int pag1 = 52;//amer norte
//const int pag2 = 50;//amer centr
//const int pag3 = 48;//amer sur

int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int permi = 0;

//PROVINCIAS
const int prov1 = 23;
const int prov2 = 25;
const int prov3 = 27;
const int prov4 = 29;
const int prov5 = 31;
const int prov6 = 33;
const int prov7 = 35;
const int prov8 = 37;
const int prov9 = 39;
const int prov10 = 41;
const int prov11 = 43;
const int prov12 = 45;
const int prov13 = 47;
const int prov14 = 48;
const int prov15 = 49;
const int prov16 = 51;
const int prov17 = 53;
const int prov18 = 52;
const int prov19 = 50;
const int prov20 = 48;
const int prov21 = 46;
const int prov22 = 44;
const int prov23 = 42;
const int prov24 = 40;

//PAISES
const int pais1 = 36;
const int pais2 = 34;
const int pais3 = 32;
const int pais4 = 30;
const int pais5 = 28;
const int pais6 = 26;
const int pais7 = 24;
const int pais8 = 22;
const int pais9 = 6;
const int pais10 = 7;
const int pais11 = 8;
const int pais12 = 9;
const int pais13 = 10;
const int pais14 = 11;
const int pais15 = 12;

//CONTINENTES
//const int conti1 = 53;//amer norte
//const int conti2 = 51;//amer centr
//const int conti3 = 49;//amer sur
//const int conti4 = 47;//europa
//const int conti5 = 45;//asia
//const int conti6 = 43;//africa
//const int conti7 = 41;//oceania

int sele = 0;

void showMessage(String line1, String line2 = "")
{
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
void encerovar()
{
  menu = 0;
  nummenu = 0;
  counter = 0;
  a = 0;
  b = 0;
  n1 = 0;
  n2 = 0;
  n3 = 0;
  n4 = 0;
}



void setup()
{
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial.begin(9600);
  Wire.begin();

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  //Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);


  //CONFIGURACION ENCODER
  pinMode(enter, INPUT_PULLUP);
  pinMode(channelPinA, INPUT_PULLUP);
  pinMode(channelPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(channelPinA), doEncodeA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(channelPinB), doEncodeB, CHANGE);

  ////lcd

  lcd.init();
  lcd.backlight();
  showMessage("  MODULO DE", "   GEOGRAFIA");

  //PAGINAS
  //  pinMode(pag1, INPUT_PULLUP);
  //  pinMode(pag2, INPUT_PULLUP);
  //  pinMode(pag3, INPUT_PULLUP);

  //PROVINCIAS
  pinMode(prov1, INPUT_PULLUP);
  pinMode(prov2, INPUT_PULLUP);
  pinMode(prov3, INPUT_PULLUP);
  pinMode(prov4, INPUT_PULLUP);
  pinMode(prov5, INPUT_PULLUP);
  pinMode(prov6, INPUT_PULLUP);
  pinMode(prov7, INPUT_PULLUP);
  pinMode(prov8, INPUT_PULLUP);
  pinMode(prov9, INPUT_PULLUP);
  pinMode(prov10, INPUT_PULLUP);
  pinMode(prov11, INPUT_PULLUP);
  pinMode(prov12, INPUT_PULLUP);
  pinMode(prov13, INPUT_PULLUP);
  pinMode(prov14, INPUT_PULLUP);
  pinMode(prov15, INPUT_PULLUP);
  pinMode(prov16, INPUT_PULLUP);
  pinMode(prov17, INPUT_PULLUP);
  pinMode(prov18, INPUT_PULLUP);
  pinMode(prov19, INPUT_PULLUP);
  pinMode(prov20, INPUT_PULLUP);
  pinMode(prov21, INPUT_PULLUP);
  pinMode(prov22, INPUT_PULLUP);
  pinMode(prov23, INPUT_PULLUP);
  pinMode(prov24, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);

  // PAISES
  pinMode(36, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  // CONTINENTES
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(A8, INPUT_PULLUP);
  pinMode(A10, INPUT_PULLUP);

  //SALUDO
  myDFPlayer.play(1);  //Play the first mp3
  delay(5000);
  lcd.clear();
}
void doEncodeA()
{
  if (millis() > timeCounter + timeThreshold)
  {
    if (digitalRead(channelPinA) == digitalRead(channelPinB))
    {
      IsCW = true;
      if (ISRCounter + 1 <= maxSteps)
      {
        ISRCounter++;
        nummenu++;
      }

    }
    else
    {
      IsCW = false;
      if (ISRCounter - 1 > 0)
      {
        ISRCounter--;
        nummenu--;
      }
    }
    timeCounter = millis();
  }
}
void doEncodeB()
{
  if (millis() > timeCounter + timeThreshold)
  {
    if (digitalRead(channelPinA) != digitalRead(channelPinB))
    {
      IsCW = true;

      if (ISRCounter + 1 <= maxSteps) ISRCounter++;
    }
    else
    {
      IsCW = false;
      if (ISRCounter - 1 > 0) ISRCounter--;
    }
    timeCounter = millis();
  }
}

void selection(String modo)
{
  lcd.clear();
  showMessage(modo);
  int n1 = 0;
  int n2 = 0;
  int n3 = 0;
  int n4 = 0;
  int n5 = 0;
  int sel = 0;
  if (modo == "PROVINCIAS")
  {
    sele = 1;

  }
  if (modo == "PAISES")
  {
    sele = 2;
  }
  if (modo == "CONTINENTES")
  {
    sele = 3;
  }

  while (true)
  {
    Serial.print(menu);
    Serial.print(",");
    Serial.println( nummenu);
    bool B = digitalRead(enter);
    if (!B)
    {
      if (menu == 1)
      {
        myDFPlayer.play(107);  //cambiar modo libre
        delay(1000);
        encerovar();
        Serial.println("*Toponimia");
        toponimia();
        break;
      }
      if (menu == 2)
      {
        myDFPlayer.play(107);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*Historia");
        historia();
        lcd.clear();
        break;

      }
      if (menu == 3)
      {
        myDFPlayer.play(107);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*Geografía");
        geografia();
        break;
      }
      if (menu == 4)
      {
        myDFPlayer.play(211);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*Demografia       ");
        demografia();
        break;
      }
      if (menu == 5)
      {
        myDFPlayer.play(106);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*Salir          ");
        lcd.clear();
        break;
      }
    }
    if (counter != ISRCounter)
    {

      counter = ISRCounter;
      if (nummenu < 0)
      {
        nummenu = 0;
      }
      if (nummenu > 25)
      {
        nummenu = 25;
      }
      if (nummenu > 0 && nummenu <= 5)
      {
        menu = 1;

        a = 1;

      }
      if (nummenu > 5 && nummenu <= 10)
      {
        menu = 2;
        a = 2;
      }
      if (nummenu > 10 && nummenu <= 15)
      {
        menu = 3;
        a = 3;
      }

      if (nummenu > 15 && nummenu <= 20)
      {
        menu = 4;
        a = 4;
      }
      if (nummenu > 20 && nummenu <= 25)
      {
        menu = 5;
        a = 5;
      }
    }
    if (a == 1)
    {
      if (n1 == 0)
      {
        myDFPlayer.play(108);  //Play the first mp3
        delay(1000);
        b = 1;
        //lcd.clear();
        showMessage(modo, "*Toponimia         ");
        n1 = 1;
        n2 = 0;
        n3 = 0;
        n4 = 0;
        n5 = 0;
      }

    }
    if (a == 2)
    {
      if (n2 == 0)
      {
        myDFPlayer.play(109);  //hay que poner paises mp3
        delay(1000);
        b = 2;
        //lcd.clear();
        showMessage(modo, "*Historia          ");
        n1 = 0;
        n2 = 1;
        n3 = 0;
        n4 = 0;
        n5 = 0;
      }

    }
    if (a == 3)
    {
      if (n3 == 0)
      {
        myDFPlayer.play(110);  //hay que poner continentes
        delay(1000);
        b = 3;
        //lcd.clear();
        showMessage(modo, "*Geografía          ");
        n1 = 0;
        n2 = 0;
        n3 = 1;
        n4 = 0;
        n5 = 0;
      }
    }
    if (a == 4)
    {
      if (n4 == 0)
      {
        myDFPlayer.play(211);  //hay que poner continentes
        delay(1000);
        b = 4;
        //lcd.clear();
        showMessage(modo, "*Demografia           ");
        n1 = 0;
        n2 = 0;
        n3 = 0;
        n4 = 1;
        n5 = 0;
      }
    }
    if (a == 5)
    {
      if (n5 == 0)
      {
        myDFPlayer.play(106);  //hay que poner continentes
        delay(1000);
        b = 4;
        //lcd.clear();
        showMessage(modo, "Salir           ");
        n1 = 0;
        n2 = 0;
        n3 = 0;
        n4 = 0;
        n5 = 1;
      }
    }
  }
}
void toponimia()
{
  switch (sele) {
    case 1:
      Serial.println("provincias");
      showMessage("A .Provincias    ", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);//salir
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        int val1 = digitalRead(23);
        int val2 = digitalRead(25);
        int val3 = digitalRead(27);
        int val4 = digitalRead(29);
        int val5 = digitalRead(31);
        int val6 = digitalRead(33);
        int val7 = digitalRead(35);
        int val8 = digitalRead(37);;
        int val9 = digitalRead(39);
        int val10 = digitalRead(41);
        int val11 = digitalRead(43);
        int val12 = digitalRead(45);
        int val13 = digitalRead(47);
        int val14 = digitalRead(49);
        int val15 = digitalRead(51);
        int val16 = digitalRead(53);
        int val17 = digitalRead(50);
        int val18 = digitalRead(52);
        int val19 = digitalRead(44);
        int val20 = digitalRead(42);
        int val21 = digitalRead(40);
        int val22 = digitalRead(48);
        int val23 = digitalRead(46);
        int val24 = digitalRead(38);
        //PROVINCIAS
        if (val1 == LOW)
        {
          Serial.println("carchi");
          myDFPlayer.play(113);  //CARCHI topminia
          delay(1000);
        }
        if (val2 == LOW)
        {
          Serial.println("iMBABURA");
          myDFPlayer.play(114);  //IMBABURA topminia
          delay(1000);
        }
        if (val3 == LOW)
        {
          Serial.println("PICHINCHA");
          myDFPlayer.play(115);  //PICHINCHA topminia
          delay(1000);
        }
        if (val4 == LOW)
        {
          Serial.println("COTOPAXI");
          myDFPlayer.play(116);  //COTOPAXI topminia
          delay(1000);
        }
        if (val5 == LOW)
        {
          Serial.println("TUNGURAHUA");
          myDFPlayer.play(117);  //tunguragua topminia
          delay(1000);
        }
        if (val6 == LOW)
        {
          Serial.println("BOLIVAR");
          myDFPlayer.play(118);  //tunguragua topminia
          delay(1000);
        }
        if (val7 == LOW)
        {
          Serial.println("CHIMBORAZO");
          myDFPlayer.play(119);  //Bolivar topminia
          delay(1000);
        }
        if (val8 == LOW)
        {
          Serial.println("CAÑAR");
          myDFPlayer.play(120);  //Chimborazo topminia
          delay(1000);
        }
        if (val9 == LOW)
        {
          Serial.println("AZUAY");
          myDFPlayer.play(121);  //azuay topminia
          delay(1000);
        }
        if (val10 == LOW)
        {
          Serial.println("LOJA");
          myDFPlayer.play(122);  //lojaq topminia
          delay(1000);
        }
        //costa
        if (val11 == LOW)

        {
          Serial.println("ESMERALDAS");
          myDFPlayer.play(123);  //esmeraldas topminia
          delay(1000);
        }
        if (val12 == LOW)
        {
          Serial.println("MANABI");
          myDFPlayer.play(124);  //manabi topminia
          delay(1000);
        }
        if (val13 == LOW)
        {
          Serial.println("SANTA ELENA");
          myDFPlayer.play(125);  //santaelena topminia
          delay(1000);
        }
        if (val14 == LOW)
        {
          Serial.println("GUAYAQUIL");
          myDFPlayer.play(126);  //guayaquil topminia
          delay(1000);
        }
        if (val15 == LOW)
        {
          Serial.println("EL ORO");
          myDFPlayer.play(127);  //el oro topminia
          delay(1000);
        }
        if (val16 == LOW)
        {
          Serial.println("SANTO DOMINGO");
          myDFPlayer.play(128);  //santo domingo topminia
          delay(1000);
        }
        if (val17 == LOW)
        {
          Serial.println("LOS RIOS");
          myDFPlayer.play(129);  //los rios topminia
          delay(1000);
        }
        //GALAPAGOS
        if (val18 == LOW)
        {
          Serial.println("GALAPAGOS");
          myDFPlayer.play(130);  //galapagos topminia
          delay(1000);
        }
        //AMAZONIA
        if (val19 == LOW)
        {
          Serial.println("PASTAZA");
          myDFPlayer.play(131);  //pastaza topminia
          delay(1000);
        }
        if (val20 == LOW)
        {
          Serial.println("ORELLANA");
          myDFPlayer.play(132);  //orellana topminia
          delay(1000);
        }
        if (val21 == LOW)
        {
          Serial.println("NAPO");
          myDFPlayer.play(133);  //napo topminia
          delay(1000);
        }
        if (val22 == LOW)
        {
          Serial.println("ZAMORA");
          myDFPlayer.play(134);  //zamora topminia
          delay(1000);
        }
        if (val23 == LOW)
        {
          Serial.println("MORONA SANTIAGO");
          myDFPlayer.play(135);  //morona topminia
          delay(1000);
        }
        if (val24 == LOW)
        {
          Serial.println("SUCUMBIOS");
          myDFPlayer.play(136);  //sucmbiios topminia
          delay(1000);
        }
      }
      break;
    case 2:
      Serial.println("paises");
      showMessage("A .Provincias", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        //PAISES
        int val25 = digitalRead(36);
        int val26 = digitalRead(34);
        int val27 = digitalRead(32);
        int val28 = digitalRead(30);
        int val29 = digitalRead(28);
        int val30 = digitalRead(26);
        int val31 = digitalRead(24);
        int val32 = digitalRead(22);;
        int val36 = digitalRead(5);
        int val37 = digitalRead(6);
        int val38 = digitalRead(7);
        int val39 = digitalRead(8);
        int val40 = digitalRead(9);
        int val41 = digitalRead(10);
        int val42 = digitalRead(11);
        int val43 = digitalRead(12);

        //PAISES
        if (val25 == LOW)
        {
          Serial.println("BOLIVIA");
          myDFPlayer.play(14);  //BOLIVIA toponia
          delay(1000);
        }
        if (val26 == LOW)
        {
          Serial.println("URUGUAY");
          myDFPlayer.play(25);  //URUGUAY toponia
          delay(1000);
        }
        if (val27 == LOW)
        {
          Serial.println("CENTRALINOS");
          myDFPlayer.play(22);  //CENTRALINO toponia
          delay(1000);
        }
        if (val28 == LOW)
        {
          Serial.println("PERU");
          myDFPlayer.play(24);  //PERU toponia
          delay(1000);
        }
        if (val29 == LOW)
        {
          Serial.println("ARGENTINA");
          myDFPlayer.play(13);  //ARGENTINA toponia
          delay(1000);
        }
        if (val30 == LOW)
        {
          Serial.println("CANADA");
          myDFPlayer.play(16);  //CANADA toponia
          delay(1000);
        }
        if (val31 == LOW)
        {
          Serial.println("ECUADOR");
          myDFPlayer.play(19);  //ECUADOR toponia
          delay(1000);
        }
        if (val32 == LOW)
        {
          Serial.println("BRASIL");
          myDFPlayer.play(15);  //BRASIL toponia
          delay(1000);
        }

        if (val36 == LOW)
        {
          Serial.println("GUAYANAS");
          myDFPlayer.play(21);  //GUAYANAS toponia
          delay(1000);
        }
        if (val37 == LOW)
        {
          Serial.println("venezuela");
          myDFPlayer.play(26);  //VENEZUELA toponia
          delay(1000);
        }
        if (val38 == LOW)
        {
          Serial.println("MEXICO");
          myDFPlayer.play(12);  //MEXICO toponia
          delay(1000);
        }
        if (val39 == LOW)
        {
          Serial.println("CHILE");
          myDFPlayer.play(17);  //CHILE toponia
          delay(1000);
        }
        if (val40 == LOW)
        {
          Serial.println("usa");
          myDFPlayer.play(20);  //USA toponia
          delay(1000);
        }
        if (val41 == LOW)
        {
          Serial.println("alaska");
          myDFPlayer.play(11);  //ALASKA PISTA 28
          delay(1000);
        }

        if (val42 == LOW)
        {
          Serial.println("paraguay");
          myDFPlayer.play(23);  //PARAGUAY PISTA 28
          delay(1000);
        }
        if (val43 == LOW)
        {
          Serial.println("_");
          myDFPlayer.play(18);  //azuay PISTA 28
          delay(1000);
        }
      }
      // Acciones cuando el valor es 100
      break;
    case 3:
      Serial.println("continentes");
      showMessage("M.L.Continente     ", "                ");
      while (true) {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(106);
          delay(3000);
          lcd.clear();
          encerovar();


          break;
          libre();
        }
        int val44 = digitalRead(A0);
        int val45 = digitalRead(A2);
        int val46 = digitalRead(A4);
        int val47 = digitalRead(A6);
        int val48 = digitalRead(A8);
        delay(10);
        //paises

        if (val44 == LOW)
        {
          myDFPlayer.play(9);
          delay(1000);
        }
        if (val45 == LOW)
        {
          myDFPlayer.play(112);
          delay(1000);
        }
        if (val46 == LOW)
        {
          myDFPlayer.play(8);
          delay(1000);
        }
        if (val47 == LOW)
        {
          myDFPlayer.play(11);
          delay(1000);
        }
        if (val48 == LOW)
        {
          myDFPlayer.play(10);
          delay(1000);
        }

      }
      break;
    default:
      Serial.println("Valor del sensor no reconocido");
      // Acciones cuando el valor no coincide con ningún caso
      break;
  }
}
void historia()
{
  switch (sele) {
    case 1:
      Serial.println(" historia provincias");
      showMessage("A .Provincias    ", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);//salir
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        int val1 = digitalRead(23);
        int val2 = digitalRead(25);
        int val3 = digitalRead(27);
        int val4 = digitalRead(29);
        int val5 = digitalRead(31);
        int val6 = digitalRead(33);
        int val7 = digitalRead(35);
        int val8 = digitalRead(37);;
        int val9 = digitalRead(39);
        int val10 = digitalRead(41);
        int val11 = digitalRead(43);
        int val12 = digitalRead(45);
        int val13 = digitalRead(47);
        int val14 = digitalRead(49);
        int val15 = digitalRead(51);
        int val16 = digitalRead(53);
        int val17 = digitalRead(50);
        int val18 = digitalRead(52);
        int val19 = digitalRead(44);
        int val20 = digitalRead(42);
        int val21 = digitalRead(40);
        int val22 = digitalRead(48);
        int val23 = digitalRead(46);
        int val24 = digitalRead(38);
        //PROVINCIAS
        if (val1 == LOW)
        {
          Serial.println("carchi");
          myDFPlayer.play(137);  //CARCHI historia
          delay(1000);
        }
        if (val2 == LOW)
        {
          Serial.println("iMBABURA");
          myDFPlayer.play(138);  //IMBABURA historia
          delay(1000);
        }
        if (val3 == LOW)
        {
          Serial.println("PICHINCHA");
          myDFPlayer.play(139);  //PICHINCHA topminia
          delay(1000);
        }
        if (val4 == LOW)
        {
          Serial.println("COTOPAXI");
          myDFPlayer.play(140);  //COTOPAXI topminia
          delay(1000);
        }
        if (val5 == LOW)
        {
          Serial.println("TUNGURAHUA");
          myDFPlayer.play(141);  //tunguragua topminia
          delay(1000);
        }
        if (val6 == LOW)
        {
          Serial.println("BOLIVAR");
          myDFPlayer.play(142);  //tunguragua topminia
          delay(1000);
        }
        if (val7 == LOW)
        {
          Serial.println("CHIMBORAZO");
          myDFPlayer.play(143);  //Bolivar topminia
          delay(1000);
        }
        if (val8 == LOW)
        {
          Serial.println("CAÑAR");
          myDFPlayer.play(144);  //Chimborazo topminia
          delay(1000);
        }
        if (val9 == LOW)
        {
          Serial.println("AZUAY");
          myDFPlayer.play(145);  //azuay topminia
          delay(1000);
        }
        if (val10 == LOW)
        {
          Serial.println("LOJA");
          myDFPlayer.play(146);  //lojaq topminia
          delay(1000);
        }
        //costa
        if (val11 == LOW)

        {
          Serial.println("ESMERALDAS");
          myDFPlayer.play(147);  //esmeraldas topminia
          delay(1000);
        }
        if (val12 == LOW)
        {
          Serial.println("MANABI");
          myDFPlayer.play(148);  //manabi topminia
          delay(1000);
        }
        if (val13 == LOW)
        {
          Serial.println("SANTA ELENA");
          myDFPlayer.play(149);  //santaelena topminia
          delay(1000);
        }
        if (val14 == LOW)
        {
          Serial.println("GUAYAQUIL");
          myDFPlayer.play(150);  //guayaquil topminia
          delay(1000);
        }
        if (val15 == LOW)
        {
          Serial.println("EL ORO");
          myDFPlayer.play(151);  //el oro topminia
          delay(1000);
        }
        if (val16 == LOW)
        {
          Serial.println("SANTO DOMINGO");
          myDFPlayer.play(152);  //santo domingo topminia
          delay(1000);
        }
        if (val17 == LOW)
        {
          Serial.println("LOS RIOS");
          myDFPlayer.play(153);  //los rios topminia
          delay(1000);
        }
        //GALAPAGOS
        if (val18 == LOW)
        {
          Serial.println("GALAPAGOS");
          myDFPlayer.play(154);  //galapagos topminia
          delay(1000);
        }
        //AMAZONIA
        if (val19 == LOW)
        {
          Serial.println("PASTAZA");
          myDFPlayer.play(155);  //pastaza topminia
          delay(1000);
        }
        if (val20 == LOW)
        {
          Serial.println("ORELLANA");
          myDFPlayer.play(156);  //orellana topminia
          delay(1000);
        }
        if (val21 == LOW)
        {
          Serial.println("NAPO");
          myDFPlayer.play(157);  //napo topminia
          delay(1000);
        }
        if (val22 == LOW)
        {
          Serial.println("ZAMORA");
          myDFPlayer.play(158);  //zamora topminia
          delay(1000);
        }
        if (val23 == LOW)
        {
          Serial.println("MORONA SANTIAGO");
          myDFPlayer.play(159);  //morona topminia
          delay(1000);
        }
        if (val24 == LOW)
        {
          Serial.println("SUCUMBIOS");
          myDFPlayer.play(136);  //sucmbiios topminia
          delay(1000);
        }
      }
      break;
    case 2:
      Serial.println("paises");
      showMessage("A .Provincias", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        //PAISES
        int val25 = digitalRead(36);
        int val26 = digitalRead(34);
        int val27 = digitalRead(32);
        int val28 = digitalRead(30);
        int val29 = digitalRead(28);
        int val30 = digitalRead(26);
        int val31 = digitalRead(24);
        int val32 = digitalRead(22);;
        int val36 = digitalRead(5);
        int val37 = digitalRead(6);
        int val38 = digitalRead(7);
        int val39 = digitalRead(8);
        int val40 = digitalRead(9);
        int val41 = digitalRead(10);
        int val42 = digitalRead(11);
        int val43 = digitalRead(12);

        //PAISES
        if (val25 == LOW)
        {
          Serial.println("BOLIVIA");
          myDFPlayer.play(14);  //BOLIVIA toponia
          delay(1000);
        }
        if (val26 == LOW)
        {
          Serial.println("URUGUAY");
          myDFPlayer.play(25);  //URUGUAY toponia
          delay(1000);
        }
        if (val27 == LOW)
        {
          Serial.println("CENTRALINOS");
          myDFPlayer.play(22);  //CENTRALINO toponia
          delay(1000);
        }
        if (val28 == LOW)
        {
          Serial.println("PERU");
          myDFPlayer.play(24);  //PERU toponia
          delay(1000);
        }
        if (val29 == LOW)
        {
          Serial.println("ARGENTINA");
          myDFPlayer.play(13);  //ARGENTINA toponia
          delay(1000);
        }
        if (val30 == LOW)
        {
          Serial.println("CANADA");
          myDFPlayer.play(16);  //CANADA toponia
          delay(1000);
        }
        if (val31 == LOW)
        {
          Serial.println("ECUADOR");
          myDFPlayer.play(19);  //ECUADOR toponia
          delay(1000);
        }
        if (val32 == LOW)
        {
          Serial.println("BRASIL");
          myDFPlayer.play(15);  //BRASIL toponia
          delay(1000);
        }

        if (val36 == LOW)
        {
          Serial.println("GUAYANAS");
          myDFPlayer.play(21);  //GUAYANAS toponia
          delay(1000);
        }
        if (val37 == LOW)
        {
          Serial.println("venezuela");
          myDFPlayer.play(26);  //VENEZUELA toponia
          delay(1000);
        }
        if (val38 == LOW)
        {
          Serial.println("MEXICO");
          myDFPlayer.play(12);  //MEXICO toponia
          delay(1000);
        }
        if (val39 == LOW)
        {
          Serial.println("CHILE");
          myDFPlayer.play(17);  //CHILE toponia
          delay(1000);
        }
        if (val40 == LOW)
        {
          Serial.println("usa");
          myDFPlayer.play(20);  //USA toponia
          delay(1000);
        }
        if (val41 == LOW)
        {
          Serial.println("alaska");
          myDFPlayer.play(11);  //ALASKA PISTA 28
          delay(1000);
        }

        if (val42 == LOW)
        {
          Serial.println("paraguay");
          myDFPlayer.play(23);  //PARAGUAY PISTA 28
          delay(1000);
        }
        if (val43 == LOW)
        {
          Serial.println("_");
          myDFPlayer.play(18);  //azuay PISTA 28
          delay(1000);
        }
      }
      // Acciones cuando el valor es 100
      break;
    case 3:
      Serial.println("continentes");
      showMessage("M.L.Continente     ", "                ");
      while (true) {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(106);
          delay(3000);
          lcd.clear();
          encerovar();


          break;
          libre();
        }
        int val44 = digitalRead(A0);
        int val45 = digitalRead(A2);
        int val46 = digitalRead(A4);
        int val47 = digitalRead(A6);
        int val48 = digitalRead(A8);
        delay(10);
        //paises

        if (val44 == LOW)
        {
          myDFPlayer.play(9);
          delay(1000);
        }
        if (val45 == LOW)
        {
          myDFPlayer.play(112);
          delay(1000);
        }
        if (val46 == LOW)
        {
          myDFPlayer.play(8);
          delay(1000);
        }
        if (val47 == LOW)
        {
          myDFPlayer.play(11);
          delay(1000);
        }
        if (val48 == LOW)
        {
          myDFPlayer.play(10);
          delay(1000);
        }

      }
      break;
    default:
      Serial.println("Valor del sensor no reconocido");
      // Acciones cuando el valor no coincide con ningún caso
      break;
  }
}
void geografia()//demografia
{
  switch (sele) {
    case 1:
      Serial.println(" Geografia provincias");
      showMessage("A .Provincias    ", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);//salir
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        int val1 = digitalRead(23);
        int val2 = digitalRead(25);
        int val3 = digitalRead(27);
        int val4 = digitalRead(29);
        int val5 = digitalRead(31);
        int val6 = digitalRead(33);
        int val7 = digitalRead(35);
        int val8 = digitalRead(37);;
        int val9 = digitalRead(39);
        int val10 = digitalRead(41);
        int val11 = digitalRead(43);
        int val12 = digitalRead(45);
        int val13 = digitalRead(47);
        int val14 = digitalRead(49);
        int val15 = digitalRead(51);
        int val16 = digitalRead(53);
        int val17 = digitalRead(50);
        int val18 = digitalRead(52);
        int val19 = digitalRead(44);
        int val20 = digitalRead(42);
        int val21 = digitalRead(40);
        int val22 = digitalRead(48);
        int val23 = digitalRead(46);
        int val24 = digitalRead(38);
        //PROVINCIAS
        if (val1 == LOW)
        {
          Serial.println("carchi");
          myDFPlayer.play(161);  //CARCHI historia
          delay(1000);
        }
        if (val2 == LOW)
        {
          Serial.println("iMBABURA");
          myDFPlayer.play(162);  //IMBABURA historia
          delay(1000);
        }
        if (val3 == LOW)
        {
          Serial.println("PICHINCHA");
          myDFPlayer.play(163);  //PICHINCHA topminia
          delay(1000);
        }
        if (val4 == LOW)
        {
          Serial.println("COTOPAXI");
          myDFPlayer.play(164);  //COTOPAXI topminia
          delay(1000);
        }
        if (val5 == LOW)
        {
          Serial.println("TUNGURAHUA");
          myDFPlayer.play(165);  //tunguragua topminia
          delay(1000);
        }
        if (val6 == LOW)
        {
          Serial.println("BOLIVAR");
          myDFPlayer.play(166);  //tunguragua topminia
          delay(1000);
        }
        if (val7 == LOW)
        {
          Serial.println("CHIMBORAZO");
          myDFPlayer.play(167);  //Bolivar topminia
          delay(1000);
        }
        if (val8 == LOW)
        {
          Serial.println("CAÑAR");
          myDFPlayer.play(168);  //Chimborazo topminia
          delay(1000);
        }
        if (val9 == LOW)
        {
          Serial.println("AZUAY");
          myDFPlayer.play(169);  //azuay topminia
          delay(1000);
        }
        if (val10 == LOW)
        {
          Serial.println("LOJA");
          myDFPlayer.play(170);  //lojaq topminia
          delay(1000);
        }
        //costa
        if (val11 == LOW)

        {
          Serial.println("ESMERALDAS");
          myDFPlayer.play(171);  //esmeraldas topminia
          delay(1000);
        }
        if (val12 == LOW)
        {
          Serial.println("MANABI");
          myDFPlayer.play(172);  //manabi topminia
          delay(1000);
        }
        if (val13 == LOW)
        {
          Serial.println("SANTA ELENA");
          myDFPlayer.play(173);  //santaelena topminia
          delay(1000);
        }
        if (val14 == LOW)
        {
          Serial.println("GUAYAQUIL");
          myDFPlayer.play(174);  //guayaquil topminia
          delay(1000);
        }
        if (val15 == LOW)
        {
          Serial.println("EL ORO");
          myDFPlayer.play(175);  //el oro topminia
          delay(1000);
        }
        if (val16 == LOW)
        {
          Serial.println("SANTO DOMINGO");
          myDFPlayer.play(176);  //santo domingo topminia
          delay(1000);
        }
        if (val17 == LOW)
        {
          Serial.println("LOS RIOS");
          myDFPlayer.play(177);  //los rios topminia
          delay(1000);
        }
        //GALAPAGOS
        if (val18 == LOW)
        {
          Serial.println("GALAPAGOS");
          myDFPlayer.play(178);  //galapagos topminia
          delay(1000);
        }
        //AMAZONIA
        if (val19 == LOW)
        {
          Serial.println("PASTAZA");
          myDFPlayer.play(179);  //pastaza topminia
          delay(1000);
        }
        if (val20 == LOW)
        {
          Serial.println("ORELLANA");
          myDFPlayer.play(180);  //orellana topminia
          delay(1000);
        }
        if (val21 == LOW)
        {
          Serial.println("NAPO");
          myDFPlayer.play(181);  //napo topminia
          delay(1000);
        }
        if (val22 == LOW)
        {
          Serial.println("ZAMORA");
          myDFPlayer.play(182);  //zamora topminia
          delay(1000);
        }
        if (val23 == LOW)
        {
          Serial.println("MORONA SANTIAGO");
          myDFPlayer.play(183);  //morona topminia
          delay(1000);
        }
        if (val24 == LOW)
        {
          Serial.println("SUCUMBIOS");
          myDFPlayer.play(184);  //sucmbiios topminia
          delay(1000);
        }
      }
      break;
    case 2:
      Serial.println("paises");
      showMessage("A .Provincias", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        //PAISES
        int val25 = digitalRead(36);
        int val26 = digitalRead(34);
        int val27 = digitalRead(32);
        int val28 = digitalRead(30);
        int val29 = digitalRead(28);
        int val30 = digitalRead(26);
        int val31 = digitalRead(24);
        int val32 = digitalRead(22);;
        int val36 = digitalRead(5);
        int val37 = digitalRead(6);
        int val38 = digitalRead(7);
        int val39 = digitalRead(8);
        int val40 = digitalRead(9);
        int val41 = digitalRead(10);
        int val42 = digitalRead(11);
        int val43 = digitalRead(12);

        //PAISES
        if (val25 == LOW)
        {
          Serial.println("BOLIVIA");
          myDFPlayer.play(14);  //BOLIVIA toponia
          delay(1000);
        }
        if (val26 == LOW)
        {
          Serial.println("URUGUAY");
          myDFPlayer.play(25);  //URUGUAY toponia
          delay(1000);
        }
        if (val27 == LOW)
        {
          Serial.println("CENTRALINOS");
          myDFPlayer.play(22);  //CENTRALINO toponia
          delay(1000);
        }
        if (val28 == LOW)
        {
          Serial.println("PERU");
          myDFPlayer.play(24);  //PERU toponia
          delay(1000);
        }
        if (val29 == LOW)
        {
          Serial.println("ARGENTINA");
          myDFPlayer.play(13);  //ARGENTINA toponia
          delay(1000);
        }
        if (val30 == LOW)
        {
          Serial.println("CANADA");
          myDFPlayer.play(16);  //CANADA toponia
          delay(1000);
        }
        if (val31 == LOW)
        {
          Serial.println("ECUADOR");
          myDFPlayer.play(19);  //ECUADOR toponia
          delay(1000);
        }
        if (val32 == LOW)
        {
          Serial.println("BRASIL");
          myDFPlayer.play(15);  //BRASIL toponia
          delay(1000);
        }

        if (val36 == LOW)
        {
          Serial.println("GUAYANAS");
          myDFPlayer.play(21);  //GUAYANAS toponia
          delay(1000);
        }
        if (val37 == LOW)
        {
          Serial.println("venezuela");
          myDFPlayer.play(26);  //VENEZUELA toponia
          delay(1000);
        }
        if (val38 == LOW)
        {
          Serial.println("MEXICO");
          myDFPlayer.play(12);  //MEXICO toponia
          delay(1000);
        }
        if (val39 == LOW)
        {
          Serial.println("CHILE");
          myDFPlayer.play(17);  //CHILE toponia
          delay(1000);
        }
        if (val40 == LOW)
        {
          Serial.println("usa");
          myDFPlayer.play(20);  //USA toponia
          delay(1000);
        }
        if (val41 == LOW)
        {
          Serial.println("alaska");
          myDFPlayer.play(11);  //ALASKA PISTA 28
          delay(1000);
        }

        if (val42 == LOW)
        {
          Serial.println("paraguay");
          myDFPlayer.play(23);  //PARAGUAY PISTA 28
          delay(1000);
        }
        if (val43 == LOW)
        {
          Serial.println("_");
          myDFPlayer.play(18);  //azuay PISTA 28
          delay(1000);
        }
      }
      // Acciones cuando el valor es 100
      break;
    case 3:
      Serial.println("continentes");
      showMessage("M.L.Continente     ", "                ");
      while (true) {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(106);
          delay(3000);
          lcd.clear();
          encerovar();


          break;
          libre();
        }
        int val44 = digitalRead(A0);
        int val45 = digitalRead(A2);
        int val46 = digitalRead(A4);
        int val47 = digitalRead(A6);
        int val48 = digitalRead(A8);
        delay(10);
        //paises

        if (val44 == LOW)
        {
          myDFPlayer.play(9);
          delay(1000);
        }
        if (val45 == LOW)
        {
          myDFPlayer.play(112);
          delay(1000);
        }
        if (val46 == LOW)
        {
          myDFPlayer.play(8);
          delay(1000);
        }
        if (val47 == LOW)
        {
          myDFPlayer.play(11);
          delay(1000);
        }
        if (val48 == LOW)
        {
          myDFPlayer.play(10);
          delay(1000);
        }

      }
      break;
    default:
      Serial.println("Valor del sensor no reconocido");
      // Acciones cuando el valor no coincide con ningún caso
      break;
  }
}
void demografia()//demografia
{
  switch (sele) {
    case 1:
      Serial.println(" demografia provincias");
      showMessage("A .Provincias    ", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);//salir
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        int val1 = digitalRead(23);
        int val2 = digitalRead(25);
        int val3 = digitalRead(27);
        int val4 = digitalRead(29);
        int val5 = digitalRead(31);
        int val6 = digitalRead(33);
        int val7 = digitalRead(35);
        int val8 = digitalRead(37);;
        int val9 = digitalRead(39);
        int val10 = digitalRead(41);
        int val11 = digitalRead(43);
        int val12 = digitalRead(45);
        int val13 = digitalRead(47);
        int val14 = digitalRead(49);
        int val15 = digitalRead(51);
        int val16 = digitalRead(53);
        int val17 = digitalRead(50);
        int val18 = digitalRead(52);
        int val19 = digitalRead(44);
        int val20 = digitalRead(42);
        int val21 = digitalRead(40);
        int val22 = digitalRead(48);
        int val23 = digitalRead(46);
        int val24 = digitalRead(38);
        //PROVINCIAS
        if (val1 == LOW)
        {
          Serial.println("carchi");
          myDFPlayer.play(185);  //CARCHI historia
          delay(1000);
        }
        if (val2 == LOW)
        {
          Serial.println("iMBABURA");
          myDFPlayer.play(186);  //IMBABURA historia
          delay(1000);
        }
        if (val3 == LOW)
        {
          Serial.println("PICHINCHA");
          myDFPlayer.play(187);  //PICHINCHA topminia
          delay(1000);
        }
        if (val4 == LOW)
        {
          Serial.println("COTOPAXI");
          myDFPlayer.play(188);  //COTOPAXI topminia
          delay(1000);
        }
        if (val5 == LOW)
        {
          Serial.println("TUNGURAHUA");
          myDFPlayer.play(189);  //tunguragua topminia
          delay(1000);
        }
        if (val6 == LOW)
        {
          Serial.println("BOLIVAR");
          myDFPlayer.play(190);  //tunguragua topminia
          delay(1000);
        }
        if (val7 == LOW)
        {
          Serial.println("CHIMBORAZO");
          myDFPlayer.play(191);  //Bolivar topminia
          delay(1000);
        }
        if (val8 == LOW)
        {
          Serial.println("CAÑAR");
          myDFPlayer.play(192);  //Chimborazo topminia
          delay(1000);
        }
        if (val9 == LOW)
        {
          Serial.println("AZUAY");
          myDFPlayer.play(193);  //azuay topminia
          delay(1000);
        }
        if (val10 == LOW)
        {
          Serial.println("LOJA");
          myDFPlayer.play(194);  //lojaq topminia
          delay(1000);
        }
        //costa
        if (val11 == LOW)

        {
          Serial.println("ESMERALDAS");
          myDFPlayer.play(195);  //esmeraldas topminia
          delay(1000);
        }
        if (val12 == LOW)
        {
          Serial.println("MANABI");
          myDFPlayer.play(196);  //manabi topminia
          delay(1000);
        }
        if (val13 == LOW)
        {
          Serial.println("SANTA ELENA");
          myDFPlayer.play(197);  //santaelena topminia
          delay(1000);
        }
        if (val14 == LOW)
        {
          Serial.println("GUAYAQUIL");
          myDFPlayer.play(198);  //guayaquil topminia
          delay(1000);
        }
        if (val15 == LOW)
        {
          Serial.println("EL ORO");
          myDFPlayer.play(199);  //el oro topminia
          delay(1000);
        }
        if (val16 == LOW)
        {
          Serial.println("SANTO DOMINGO");
          myDFPlayer.play(200);  //santo domingo topminia
          delay(1000);
        }
        if (val17 == LOW)
        {
          Serial.println("LOS RIOS");
          myDFPlayer.play(201);  //los rios topminia
          delay(1000);
        }
        //GALAPAGOS
        if (val18 == LOW)
        {
          Serial.println("GALAPAGOS");
          myDFPlayer.play(202);  //galapagos topminia
          delay(1000);
        }
        //AMAZONIA
        if (val19 == LOW)
        {
          Serial.println("PASTAZA");
          myDFPlayer.play(203);  //pastaza topminia
          delay(1000);
        }
        if (val20 == LOW)
        {
          Serial.println("ORELLANA");
          myDFPlayer.play(204);  //orellana topminia
          delay(1000);
        }
        if (val21 == LOW)
        {
          Serial.println("NAPO");
          myDFPlayer.play(205);  //napo topminia
          delay(1000);
        }
        if (val22 == LOW)
        {
          Serial.println("ZAMORA");
          myDFPlayer.play(206);  //zamora topminia
          delay(1000);
        }
        if (val23 == LOW)
        {
          Serial.println("MORONA SANTIAGO");
          myDFPlayer.play(207);  //morona topminia
          delay(1000);
        }
        if (val24 == LOW)
        {
          Serial.println("SUCUMBIOS");
          myDFPlayer.play(208);  //sucmbiios topminia
          delay(1000);
        }
      }
      break;
    case 2:
      Serial.println("paises");
      showMessage("A .Provincias", "                ");
      while (true)
      {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(107);
          delay(3000);
          lcd.clear();
          encerovar();
          break;
        }
        //PAISES
        int val25 = digitalRead(36);
        int val26 = digitalRead(34);
        int val27 = digitalRead(32);
        int val28 = digitalRead(30);
        int val29 = digitalRead(28);
        int val30 = digitalRead(26);
        int val31 = digitalRead(24);
        int val32 = digitalRead(22);;
        int val36 = digitalRead(5);
        int val37 = digitalRead(6);
        int val38 = digitalRead(7);
        int val39 = digitalRead(8);
        int val40 = digitalRead(9);
        int val41 = digitalRead(10);
        int val42 = digitalRead(11);
        int val43 = digitalRead(12);

        //PAISES
        if (val25 == LOW)
        {
          Serial.println("BOLIVIA");
          myDFPlayer.play(14);  //BOLIVIA toponia
          delay(1000);
        }
        if (val26 == LOW)
        {
          Serial.println("URUGUAY");
          myDFPlayer.play(25);  //URUGUAY toponia
          delay(1000);
        }
        if (val27 == LOW)
        {
          Serial.println("CENTRALINOS");
          myDFPlayer.play(22);  //CENTRALINO toponia
          delay(1000);
        }
        if (val28 == LOW)
        {
          Serial.println("PERU");
          myDFPlayer.play(24);  //PERU toponia
          delay(1000);
        }
        if (val29 == LOW)
        {
          Serial.println("ARGENTINA");
          myDFPlayer.play(13);  //ARGENTINA toponia
          delay(1000);
        }
        if (val30 == LOW)
        {
          Serial.println("CANADA");
          myDFPlayer.play(16);  //CANADA toponia
          delay(1000);
        }
        if (val31 == LOW)
        {
          Serial.println("ECUADOR");
          myDFPlayer.play(19);  //ECUADOR toponia
          delay(1000);
        }
        if (val32 == LOW)
        {
          Serial.println("BRASIL");
          myDFPlayer.play(15);  //BRASIL toponia
          delay(1000);
        }

        if (val36 == LOW)
        {
          Serial.println("GUAYANAS");
          myDFPlayer.play(21);  //GUAYANAS toponia
          delay(1000);
        }
        if (val37 == LOW)
        {
          Serial.println("venezuela");
          myDFPlayer.play(26);  //VENEZUELA toponia
          delay(1000);
        }
        if (val38 == LOW)
        {
          Serial.println("MEXICO");
          myDFPlayer.play(12);  //MEXICO toponia
          delay(1000);
        }
        if (val39 == LOW)
        {
          Serial.println("CHILE");
          myDFPlayer.play(17);  //CHILE toponia
          delay(1000);
        }
        if (val40 == LOW)
        {
          Serial.println("usa");
          myDFPlayer.play(20);  //USA toponia
          delay(1000);
        }
        if (val41 == LOW)
        {
          Serial.println("alaska");
          myDFPlayer.play(11);  //ALASKA PISTA 28
          delay(1000);
        }

        if (val42 == LOW)
        {
          Serial.println("paraguay");
          myDFPlayer.play(23);  //PARAGUAY PISTA 28
          delay(1000);
        }
        if (val43 == LOW)
        {
          Serial.println("_");
          myDFPlayer.play(18);  //azuay PISTA 28
          delay(1000);
        }
      }
      // Acciones cuando el valor es 100
      break;
    case 3:
      Serial.println("continentes");
      showMessage("M.L.Continente     ", "                ");
      while (true) {
        bool B = digitalRead(enter);
        if (!B)
        {
          myDFPlayer.play(106);
          delay(3000);
          lcd.clear();
          encerovar();


          break;
          libre();
        }
        int val44 = digitalRead(A0);
        int val45 = digitalRead(A2);
        int val46 = digitalRead(A4);
        int val47 = digitalRead(A6);
        int val48 = digitalRead(A8);
        delay(10);
        //paises

        if (val44 == LOW)
        {
          myDFPlayer.play(9);
          delay(1000);
        }
        if (val45 == LOW)
        {
          myDFPlayer.play(112);
          delay(1000);
        }
        if (val46 == LOW)
        {
          myDFPlayer.play(8);
          delay(1000);
        }
        if (val47 == LOW)
        {
          myDFPlayer.play(11);
          delay(1000);
        }
        if (val48 == LOW)
        {
          myDFPlayer.play(10);
          delay(1000);
        }

      }
      break;
    default:
      Serial.println("Valor del sensor no reconocido");
      // Acciones cuando el valor no coincide con ningún caso
      break;
  }
}

int nn1 = 0;
int nn2 = 0;
int nn3 = 0;


void loop()
{
  showMessage("MENU PRINCIPAL");
  //libreconti();
  bool B = digitalRead(enter);
  if (!B)
  {
    if (menu == 1)
    {
      myDFPlayer.play(104);  //Play the first mp3
      delay(1000);
      Serial.println("ha selecionado practica libre");
      encerovar();
      libre();
      encerovar();

      menu = 0;

    }
    if (menu == 2)
    {
      myDFPlayer.play(102);  //Play the first mp3
      delay(1000);
      Serial.println("ha selecionado modo aprendizaje");
      encerovar();
      aprendizaje();
      encerovar();

      menu = 0;
      //break;
    }
    if (menu == 3)
    {
      myDFPlayer.play(103);  //cambiar a pista salir
      delay(1000);
      eva();
      Serial.println("ha seleccionado modo evaluación");


    }
  }
  if (counter != ISRCounter)
  {

    counter = ISRCounter;
    if (nummenu < 0)
    {
      nummenu = 0;
    }
    if (nummenu > 15)
    {
      nummenu = 15;
    }
    if (nummenu > 0 && nummenu <= 5)
    {
      menu = 1;

      a = 1;

    }
    if (nummenu > 5 && nummenu <= 10)
    {
      menu = 2;
      a = 2;
    }
    if (nummenu > 10 && nummenu <= 15)
    {
      menu = 3;
      a = 3;
    }


    if (a == 1)
    {
      if (nn1 == 0)
      {
        nn1 = 1;
        nn2 = 0;
        nn3 = 0;
        myDFPlayer.play(104);  //Play the first mp3
        delay(1000);

        showMessage("MENU PRINCIPAL", "* M. Libre      ");
      }

    }
    if (a == 2)
    {
      if (nn2 == 0)
      {
        nn1 = 0;
        nn2 = 1;
        nn3 = 0;
        myDFPlayer.play(102);  //Play the first mp3
        delay(1000);

        showMessage("MENU PRINCIPAL", "* M. Aprendizaje     ");
      }
    }
    if (a == 3)
    {
      if (nn3 == 0)
      {
        nn1 = 0;
        nn2 = 0;
        nn3 = 1;
        myDFPlayer.play(103);  //Play the first mp3
        delay(1000);

        showMessage("MENU PRINCIPAL", "* M. Evaluacion     ");

      }
    }
    Serial.println(menu);

  }
  delay(100);
}
void libre()
{

  showMessage("MODO LIBRE     ", "                ");

  int n1 = 0;
  int n2 = 0;
  int n3 = 0;
  int n4 = 0;
  encerovar();
  a = 1;
  while (true)
  {

    Serial.print(nummenu);
    Serial.print(" , ");
    Serial.println(a);
    bool B = digitalRead(enter);

    if (!B)
    {

      if (menu == 1)
      {

        myDFPlayer.play(107);  //cambiar modo libre
        delay(1000);
        Serial.println("provincias");
        encerovar();
        libreprov();
        lcd.clear();
        libre();
        break;

      }
      if (menu == 2)
      {

        myDFPlayer.play(107);  //cambiar a pista salir
        delay(1000);
        Serial.println("paises");
        lcd.clear();
        encerovar();
        librepais();
        libre();
        break;

      }
      if (menu == 3)
      {

        myDFPlayer.play(107);  //cambiar a pista salir
        delay(1000);
        Serial.println("continente");
        lcd.clear();
        encerovar();
        libreconti();
        libre();
        break;


      }
      if (menu == 4)
      {

        myDFPlayer.play(106);  //cambiar a pista salir
        delay(1000);
        Serial.println("salir");
        lcd.clear();
        encerovar();
        loop();
        break;

      }
    }
    if (counter != ISRCounter)
    {
      counter = ISRCounter;
      if (nummenu < 0)
      {
        nummenu = 0;
      }
      if (nummenu > 20)
      {
        nummenu = 20;
      }
      if (nummenu > 0 && nummenu <= 5)
      {
        menu = 1;

        a = 1;

      }
      if (nummenu > 5 && nummenu <= 10)
      {
        menu = 2;
        a = 2;
      }
      if (nummenu > 10 && nummenu <= 15)
      {
        menu = 3;

        a = 3;

      }
      if (nummenu > 15 && nummenu <= 20)
      {
        menu = 4;
        a = 4;
      }
    }
    if (a == 1)
    {
      if (n1 == 0) {
        myDFPlayer.play(4);  //Play the first mp3
        delay(1000);


        //lcd.clear();
        showMessage("MODO LIBRE", "* Provincias   ");

        b = 1;

        n1 = 1;
        n2 = 0;
        n3 = 0;
        n4 = 0;
      }
    }
    if (a == 2)
    {
      if (n2 == 0) {
        myDFPlayer.play(3);  //Play the first mp3
        delay(1000);

        //lcd.clear();
        showMessage("MODO LIBRE", "* Pais       ");

        n1 = 0;
        n2 = 1;
        n3 = 0;
        n4 = 0;
      }

    }
    if (a == 3)
    {
      if (n3 == 0) {
        myDFPlayer.play(2);  //Play the first mp3
        delay(1000);

        //lcd.clear();
        showMessage("MODO LIBRE", "* Continentes    ");
        n1 = 0;
        n2 = 0;
        n3 = 1;
        n4 = 0;
      }
    }
    if (a == 4)
    {
      if (n4 == 0) {
        myDFPlayer.play(106);  //Play the first mp3
        delay(1000);

        //lcd.clear();
        showMessage("MODO LIBRE", "* Salir          ");
        n1 = 0;
        n2 = 0;
        n3 = 0;
        n4 = 1;
      }
    }
  }
}
void libreprov()
{
  //provincias
  showMessage("M.L.Provincias    ", "                ");
  while (true)
  {
    bool B = digitalRead(enter);
    if (!B)
    {
      myDFPlayer.play(106);
      delay(3000);
      lcd.clear();
      encerovar();
      break;
    }
    int val1 = digitalRead(23);
    int val2 = digitalRead(25);
    int val3 = digitalRead(27);
    int val4 = digitalRead(29);
    int val5 = digitalRead(31);
    int val6 = digitalRead(33);
    int val7 = digitalRead(35);
    int val8 = digitalRead(37);;
    int val9 = digitalRead(39);
    int val10 = digitalRead(41);
    int val11 = digitalRead(43);
    int val12 = digitalRead(45);
    int val13 = digitalRead(47);
    int val14 = digitalRead(49);
    int val15 = digitalRead(51);
    int val16 = digitalRead(53);
    int val17 = digitalRead(50);
    int val18 = digitalRead(52);
    int val19 = digitalRead(44);
    int val20 = digitalRead(42);
    int val21 = digitalRead(40);
    int val22 = digitalRead(48);
    int val23 = digitalRead(46);
    int val24 = digitalRead(38);
    //PROVINCIAS
    if (val1 == LOW)
    {
      Serial.println("carchi");
      myDFPlayer.play(31);  //CARCHI PISTA 31
      delay(1000);
    }
    if (val2 == LOW)
    {
      Serial.println("iMBABURA");
      myDFPlayer.play(105);  //IMBABURA PISTA 35
      delay(1000);
    }
    if (val3 == LOW)
    {
      Serial.println("PICHINCHA");
      myDFPlayer.play(43);  //PICHINCHA PISTA 43
      delay(1000);
    }
    if (val4 == LOW)
    {
      Serial.println("COTOPAXI");
      myDFPlayer.play(33);  //COTOPAXI PISTA 33
      delay(1000);
    }
    if (val5 == LOW)
    {
      Serial.println("TUNGURAHUA");
      myDFPlayer.play(47);  //tunguragua PISTA 47
      delay(1000);
    }
    if (val6 == LOW)
    {
      Serial.println("BOLIVAR");
      myDFPlayer.play(29);  //Bolivar PISTA 47
      delay(1000);
    }
    if (val7 == LOW)
    {
      Serial.println("CHIMBORAZO");
      myDFPlayer.play(32);  //chimborazo PISTA 29
      delay(1000);
    }
    if (val8 == LOW)
    {
      Serial.println("CAÑAR");
      myDFPlayer.play(30);  //Cañar PISTA 32
      delay(1000);
    }
    if (val9 == LOW)
    {
      Serial.println("AZUAY");
      myDFPlayer.play(28);  //azuay PISTA 30
      delay(1000);
    }
    if (val10 == LOW)
    {
      Serial.println("LOJA");
      myDFPlayer.play(36);  //loja PISTA 28
      delay(1000);
    }
    //costa
    if (val11 == LOW)

    {
      Serial.println("ESMERALDAS");
      myDFPlayer.play(35);  //azuay PISTA 28
      delay(1000);
    }
    if (val12 == LOW)
    {
      Serial.println("MANABI");
      myDFPlayer.play(38);  //azuay PISTA 28
      delay(1000);
    }
    if (val13 == LOW)
    {
      Serial.println("SANTA ELENA");
      myDFPlayer.play(44);  //azuay PISTA 28
      delay(1000);
    }
    if (val14 == LOW)
    {
      Serial.println("GUAYAQUIL");
      myDFPlayer.play(209);  //azuay PISTA 28
      delay(1000);
    }
    if (val15 == LOW)
    {
      Serial.println("EL ORO");
      myDFPlayer.play(34);  //azuay PISTA 28
      delay(1000);
    }
    if (val16 == LOW)
    {
      Serial.println("SANTO DOMINGO");
      myDFPlayer.play(45);  //azuay PISTA 28
      delay(1000);
    }
    if (val17 == LOW)
    {
      Serial.println("LOS RIOS");
      myDFPlayer.play(37);  //azuay PISTA 28
      delay(1000);
    }
    //GALAPAGOS
    if (val18 == LOW)
    {
      Serial.println("GALAPAGOS");
      myDFPlayer.play(210);  //azuay PISTA 28
      delay(1000);
    }
    //AMAZONIA
    if (val19 == LOW)
    {
      Serial.println("PASTAZA");
      myDFPlayer.play(42);  //azuay PISTA 28
      delay(1000);
    }
    if (val20 == LOW)
    {
      Serial.println("ORELLANA");
      myDFPlayer.play(41);  //azuay PISTA 28
      delay(1000);
    }
    if (val21 == LOW)
    {
      Serial.println("NAPO");
      myDFPlayer.play(40);  //azuay PISTA 28
      delay(1000);
    }
    if (val22 == LOW)
    {
      Serial.println("ZAMORA");
      myDFPlayer.play(48);  //azuay PISTA 28
      delay(1000);
    }
    if (val23 == LOW)
    {
      Serial.println("MORONA SANTIAGO");
      myDFPlayer.play(39);  //azuay PISTA 28
      delay(1000);
    }
    if (val24 == LOW)
    {
      Serial.println("SUCUMBIOS");
      myDFPlayer.play(46);  //azuay PISTA 28
      delay(1000);
    }
  }
}
void librepais()
{
  showMessage("M.L.Pais    ", "                ");
  while (true) {
    bool B = digitalRead(enter);
    if (!B)
    {
      myDFPlayer.play(106);
      delay(3000);
      lcd.clear();
      encerovar();
      break;
    }
    //PAISES
    int val25 = digitalRead(36);
    int val26 = digitalRead(34);
    int val27 = digitalRead(32);
    int val28 = digitalRead(30);
    int val29 = digitalRead(28);
    int val30 = digitalRead(26);
    int val31 = digitalRead(24);
    int val32 = digitalRead(22);;
    int val36 = digitalRead(5);
    int val37 = digitalRead(6);
    int val38 = digitalRead(7);
    int val39 = digitalRead(8);
    int val40 = digitalRead(9);
    int val41 = digitalRead(10);
    int val42 = digitalRead(11);
    int val43 = digitalRead(12);

    //PAISES
    if (val25 == LOW)
    {
      Serial.println("BOLIVIA");
      myDFPlayer.play(15);  //BOLIVIA PISTA 31
      delay(1000);
    }
    if (val26 == LOW)
    {
      Serial.println("URUGUAY");
      myDFPlayer.play(26);  //IMBABURA PISTA 35
      delay(1000);
    }
    if (val27 == LOW)
    {
      Serial.println("CENTRALINOS");
      myDFPlayer.play(23);  //CENTRALINO PISTA 43
      delay(1000);
    }
    if (val28 == LOW)
    {
      Serial.println("PERU");
      myDFPlayer.play(25);  //PERU PISTA 33
      delay(1000);
    }
    if (val29 == LOW)
    {
      Serial.println("ARGENTINA");
      myDFPlayer.play(14);  //tunguragua PISTA 47
      delay(1000);
    }
    if (val30 == LOW)
    {
      Serial.println("CANADA");
      myDFPlayer.play(17);  //tunguragua PISTA 47
      delay(1000);
    }
    if (val31 == LOW)
    {
      Serial.println("ECUADOR");
      myDFPlayer.play(20);  //Bolivar PISTA 29
      delay(1000);
    }
    if (val32 == LOW)
    {
      Serial.println("BRASIL");
      myDFPlayer.play(16);  //Chimborazo PISTA 32
      delay(1000);
    }

    if (val36 == LOW)
    {
      Serial.println("GUAYANAS");
      myDFPlayer.play(22);  //azuay PISTA 28
      delay(1000);
    }
    if (val37 == LOW)
    {
      Serial.println("venezuela");
      myDFPlayer.play(27);  //azuay PISTA 28
      delay(1000);
    }
    if (val38 == LOW)
    {
      Serial.println("MEXICO");
      myDFPlayer.play(13);  //azuay PISTA 28
      delay(1000);
    }
    if (val39 == LOW)
    {
      Serial.println("CHILE");
      myDFPlayer.play(18);  //azuay PISTA 28
      delay(1000);
    }
    if (val40 == LOW)
    {
      Serial.println("usa");
      myDFPlayer.play(21);  //azuay PISTA 28
      delay(1000);
    }
    if (val41 == LOW)
    {
      Serial.println("alaska");
      myDFPlayer.play(12);  //azuay PISTA 28
      delay(1000);
    }

    if (val42 == LOW)
    {
      Serial.println("paraguay");
      myDFPlayer.play(24);  //azuay PISTA 28
      delay(1000);
    }
    if (val43 == LOW)
    {
      Serial.println("colombia");
      myDFPlayer.play(19);  //azuay PISTA 28
      delay(1000);
    }
  }
}
void libreconti()
{
  showMessage("M.L.Continente     ", "                ");
  while (true) {
    bool B = digitalRead(enter);
    if (!B)
    {
      myDFPlayer.play(106);
      delay(3000);
      lcd.clear();
      encerovar();


      break;
      libre();
    }
    int val44 = digitalRead(A0);
    int val45 = digitalRead(A2);
    int val46 = digitalRead(A4);
    int val47 = digitalRead(A6);
    int val48 = digitalRead(A8);
    delay(10);
    //paises

    if (val44 == LOW)
    {
      myDFPlayer.play(9);
      delay(1000);
    }
    if (val45 == LOW)
    {
      myDFPlayer.play(112);
      delay(1000);
    }
    if (val46 == LOW)
    {
      myDFPlayer.play(8);
      delay(1000);
    }
    if (val47 == LOW)
    {
      myDFPlayer.play(11);
      delay(1000);
    }
    if (val48 == LOW)
    {
      myDFPlayer.play(10);
      delay(1000);
    }

  }
}

void aprendizaje()
{

  lcd.clear();
  showMessage("MODO APRENDIZAJE   ");
  int n1 = 0;
  int n2 = 0;
  int n3 = 0;
  int n4 = 0;

  while (true)
  {
    Serial.print(menu);
    Serial.print(",");
    Serial.print( nummenu);
    Serial.print(",");
    Serial.print( n1);
    Serial.print(",");
    Serial.print( n2);
    Serial.print(",");
    Serial.print( n3);
    Serial.print(",");
    Serial.println( n4);
    bool B = digitalRead(enter);
    if (!B)
    {
      if (menu == 1)
      {

        myDFPlayer.play(107);  //cambiar modo libre
        delay(1000);
        encerovar();
        Serial.println("*provincias");
        lcd.clear();
        selection("PROVINCIAS");
        break;
      }
      if (menu == 2)
      {
        myDFPlayer.play(107);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*paises");
        lcd.clear();
        selection("PAISES");
        lcd.clear();
        break;
      }
      if (menu == 3)
      {
        myDFPlayer.play(107);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*continentes");
        lcd.clear();
        selection("CONTINENTES");
        lcd.clear();
        break;
      }
      if (menu == 4)
      {
        myDFPlayer.play(106);  //cambiar a pista salir
        delay(1000);
        encerovar();
        Serial.println("*salir");
        lcd.clear();
        break;

      }
    }
    if (counter != ISRCounter)
    {

      counter = ISRCounter;
      if (nummenu < 0)
      {
        nummenu = 0;
      }
      if (nummenu > 20)
      {
        nummenu = 20;
      }
      if (nummenu > 0 && nummenu <= 5)
      {
        menu = 1;

        a = 1;

      }
      if (nummenu > 5 && nummenu <= 10)
      {
        menu = 2;
        a = 2;
      }
      if (nummenu > 10 && nummenu <= 15)
      {
        menu = 3;
        a = 3;
      }

      if (nummenu > 15 && nummenu <= 20)
      {
        menu = 4;
        a = 4;
      }
    }
    if (a == 1)
    {
      if (n1 == 0)
      {
        n1 = 1;
        n2 = 0;
        n3 = 0;
        n4 = 0;
        myDFPlayer.play(4);  //Play the first mp3

        //lcd.clear();
        showMessage("MODO APRENDIZAJE", "* Provincias      ");

      }


    }
    if (a == 2)
    {
      if (n2 == 0)
      {
        myDFPlayer.play(3);  //hay que poner paises mp3

        //lcd.clear();
        showMessage("MODO APRENDIZAJE", "* Paises Americanos");

        n1 = 0;
        n2 = 1;
        n3 = 0;
        n4 = 0;
      }
    }
    if (a == 3)
    {
      if (n3 == 0)
      {
        myDFPlayer.play(2);  //hay que poner continentes
        delay(1000);
        b = 3;
        showMessage("MODO APRENDIZAJE", "* Continentes        ");
        n1 = 0;
        n2 = 0;
        n3 = 1;
        n4 = 0;
      }

    }
    if (a == 4)
    {
      if (n4 == 0)
      {
        myDFPlayer.play(106);  //hay que poner continentes
        delay(1000);
        b = 4;
        //lcd.clear();
        showMessage("MODO APRENDIZAJE", "* Salir         ");
        n1 = 0;
        n2 = 0;
        n3 = 0;
        n4 = 1;
      }

    }
  }
}

void eva()
{
  lcd.clear();
  showMessage("MODO EVALUACION   ");
  String dato;
  
  while (true)
  {

    if (Serial1.available()) { // Verifica si hay datos disponibles en Serial2 (Bluetooth)
      String message = Serial1.readStringUntil('\n'); // Lee la cadena de caracteres hasta que se reciba un salto de línea ('\n')
      dato = message;
      // Imprime el mensaje recibido a través del puerto serie principal
      Serial.println(message);
      if (dato == "A")
      {
        Serial.println(" Dato recibido: A");
        permi = 1;

      }
    }
    bool B = digitalRead(enter);
    if (!B)
    {
      myDFPlayer.play(106);
      delay(3000);
      lcd.clear();
      encerovar();
      break;
    }
    if (permi == 1)
    {
      activeall();
    }
  }
}

void activeall()
{
  //PAISES
  int val25 = digitalRead(36);
  int val26 = digitalRead(34);
  int val27 = digitalRead(32);
  int val28 = digitalRead(30);
  int val29 = digitalRead(28);
  int val30 = digitalRead(26);
  int val31 = digitalRead(24);
  int val32 = digitalRead(22);
  int val36 = digitalRead(5);
  int val37 = digitalRead(6);
  int val38 = digitalRead(7);
  int val39 = digitalRead(8);
  int val40 = digitalRead(9);
  int val41 = digitalRead(10);
  int val42 = digitalRead(11);
  int val43 = digitalRead(12);
  //CONTINENTES
  int val44 = digitalRead(A0);
  int val49 = digitalRead(A10);
  int val45 = digitalRead(A2);
  int val46 = digitalRead(A4);
  int val47 = digitalRead(A6);
  int val48 = digitalRead(A8);
  //PROVINCIAS
  int val1 = digitalRead(23);
  int val2 = digitalRead(25);
  int val3 = digitalRead(27);
  int val4 = digitalRead(29);
  int val5 = digitalRead(31);
  int val6 = digitalRead(33);
  int val7 = digitalRead(35);
  int val8 = digitalRead(37);;
  int val9 = digitalRead(39);
  int val10 = digitalRead(41);
  int val11 = digitalRead(43);
  int val12 = digitalRead(45);
  int val13 = digitalRead(47);
  int val14 = digitalRead(49);
  int val15 = digitalRead(51);
  int val16 = digitalRead(53);
  int val17 = digitalRead(50);
  int val18 = digitalRead(52);
  int val19 = digitalRead(44);
  int val20 = digitalRead(42);
  int val21 = digitalRead(40);
  int val22 = digitalRead(48);
  int val23 = digitalRead(46);
  int val24 = digitalRead(38);
  //botones continentes

  if (val44 == LOW)
  {
    delay(1000);
    myDFPlayer.play(9);
    Serial.println("asia");
    Serial1.println("1");
    delay(3000);
    permi = 0;
  }
  if (val45 == LOW)
  {
    myDFPlayer.play(5);
    Serial.println("norte america");
    Serial1.println("2");
    delay(1000);
    permi = 0;
  }
  if (val46 == LOW)
  {
    delay(1000);
    myDFPlayer.play(8);
    Serial.println("europa");
    Serial1.println("3");
    delay(3000);
    permi = 0;
  }
  if (val47 == LOW)
  {
    delay(1000);
    myDFPlayer.play(11);
    Serial.println("oceania");
    Serial1.println("4");
    delay(3000);
    permi = 0;
  }
  if (val48 == LOW)
  {
    delay(1000);
    myDFPlayer.play(10);
    Serial.println("africa");
    Serial1.println("5");
    delay(3000);
    permi = 0;
  }
  if (val49 == LOW)
  {
    delay(1000);
    myDFPlayer.play(6);
    delay(2000);
    myDFPlayer.play(7);
    Serial.println("sur america y america central");
    Serial1.println("6");
    delay(3000);
    permi = 0;
  }

  //botones paises
  //PAISES
  if (val25 == LOW)
  {
    delay(1000);
    Serial.println("BOLIVIA");
    myDFPlayer.play(15);  //BOLIVIA PISTA 31
    Serial1.println("7");
    delay(3000);
    permi = 0;
  }
  if (val26 == LOW)
  {
    delay(1000);
    Serial.println("URUGUAY");
    myDFPlayer.play(26);  //IMBABURA PISTA 35
    Serial1.println("8");
    delay(3000);
    permi = 0;
  }
  if (val27 == LOW)
  {
    delay(1000);
    Serial.println("CENTRALINOS");
    myDFPlayer.play(23);  //CENTRALINO PISTA 43
    Serial1.println("9");
    delay(3000);
    permi = 0;
  }
  if (val28 == LOW)
  {
    delay(1000);
    Serial.println("PERU");
    myDFPlayer.play(25);  //PERU PISTA 33
    Serial1.println("10");
    delay(3000);
    permi = 0;
  }
  if (val29 == LOW)
  {
    delay(1000);
    Serial.println("ARGENTINA");
    myDFPlayer.play(14);  //tunguragua PISTA 47
    Serial1.println("11");
    delay(3000);
    permi = 0;
  }
  if (val30 == LOW)
  {
    delay(1000);
    Serial.println("CANADA");
    myDFPlayer.play(17);  //tunguragua PISTA 47
    Serial1.println("12");
    delay(3000);
    permi = 0;
  }
  if (val31 == LOW)
  {
    delay(1000);
    Serial.println("ECUADOR");
    myDFPlayer.play(20);  //Bolivar PISTA 29
    Serial1.println("13");
    delay(3000);
    permi = 0;
  }
  if (val32 == LOW)
  {
    delay(1000);
    Serial.println("BRASIL");
    myDFPlayer.play(16);  //Chimborazo PISTA 32
    Serial1.println("14");
    delay(3000);
    permi = 0;
  }

  if (val36 == LOW)
  {
    delay(1000);
    Serial.println("GUAYANAS");
    myDFPlayer.play(22);  //azuay PISTA 28
    Serial1.println("15");
    delay(3000);
    permi = 0;
  }
  if (val37 == LOW)
  {
    delay(1000);
    Serial.println("venezuela");
    myDFPlayer.play(27);  //azuay PISTA 28
    Serial1.println("16");
    delay(3000);
    permi = 0;
  }
  if (val38 == LOW)
  {
    delay(1000);
    Serial.println("MEXICO");
    myDFPlayer.play(13);  //azuay PISTA 28
    Serial1.println("17");
    delay(3000);
    permi = 0;
  }
  if (val39 == LOW)
  {
    delay(1000);
    Serial.println("CHILE");
    myDFPlayer.play(18);  //azuay PISTA 28
    Serial1.println("18");
    delay(3000);
    permi = 0;
  }
  if (val40 == LOW)
  {
    delay(1000);
    Serial.println("usa");
    myDFPlayer.play(21);  //azuay PISTA 28
    Serial1.println("19");
    delay(3000);
    permi = 0;
  }
  if (val41 == LOW)
  {
    delay(1000);
    Serial.println("alaska");
    myDFPlayer.play(12);  //azuay PISTA 28
    Serial1.println("20");
    delay(3000);
    permi = 0;
  }

  if (val42 == LOW)
  {
    delay(1000);
    Serial.println("paraguay");
    myDFPlayer.play(24);  //azuay PISTA 28
    Serial1.println("21");
    delay(3000);
    permi = 0;
  }
  if (val43 == LOW)
  {
    delay(1000);
    Serial.println("colombia");
    myDFPlayer.play(19);  //azuay PISTA 28
    Serial1.println("22");
    delay(3000);
    permi = 0;
  }

  //provincias
  if (val1 == LOW)
  {
    delay(1000);
    Serial.println("carchi");
    myDFPlayer.play(31);  //CARCHI PISTA 31
    Serial1.println("23");
    delay(3000);
    permi = 0;
  }
  if (val2 == LOW)
  {
    delay(1000);
    Serial.println("iMBABURA");
    myDFPlayer.play(105);  //IMBABURA PISTA 35
    Serial1.println("24");
    delay(3000);
    permi = 0;
  }
  if (val3 == LOW)
  {
    delay(1000);
    Serial.println("PICHINCHA");
    myDFPlayer.play(43);  //PICHINCHA PISTA 43
    Serial1.println("25");
    delay(3000);
    permi = 0;
  }
  if (val4 == LOW)
  {
    delay(1000);
    Serial.println("COTOPAXI");
    myDFPlayer.play(33);  //COTOPAXI PISTA 33
    Serial1.println("26");
    delay(3000);
    permi = 0;
  }
  if (val5 == LOW)
  {
    delay(1000);
    Serial.println("TUNGURAHUA");
    myDFPlayer.play(47);  //tunguragua PISTA 47
    Serial1.println("27");
    delay(3000);
    permi = 0;
  }
  if (val6 == LOW)
  {
    delay(1000);
    Serial.println("BOLIVAR");
    myDFPlayer.play(29);  //Bolivar PISTA 47
    Serial1.println("28");
    delay(3000);
    permi = 0;
  }
  if (val7 == LOW)
  {
    delay(1000);
    Serial.println("CHIMBORAZO");
    myDFPlayer.play(32);  //chimborazo PISTA 29
    Serial1.println("29");
    delay(3000);
    permi = 0;
  }
  if (val8 == LOW)
  {
    delay(1000);
    Serial.println("CAÑAR");
    myDFPlayer.play(30);  //Cañar PISTA 32
    Serial1.println("30");
    delay(3000);
    permi = 0;
  }
  if (val9 == LOW)
  {
    delay(1000);
    Serial.println("AZUAY");
    myDFPlayer.play(28);  //azuay PISTA 30
    Serial1.println("31");
    delay(3000);
    permi = 0;
  }
  if (val10 == LOW)
  {
    delay(1000);
    Serial.println("LOJA");
    myDFPlayer.play(36);  //loja PISTA 28
    Serial1.println("32");
    delay(3000);
    permi = 0;
  }
  //costa
  if (val11 == LOW)

  {
    delay(1000);
    Serial.println("ESMERALDAS");
    myDFPlayer.play(35);  //azuay PISTA 28
    Serial1.println("33");
    delay(3000);
    permi = 0;
  }
  if (val12 == LOW)
  {
    delay(1000);
    Serial.println("MANABI");
    myDFPlayer.play(38);  //azuay PISTA 28
    Serial1.println("34");
    delay(3000);
    permi = 0;
  }
  if (val13 == LOW)
  {
    delay(1000);
    Serial.println("SANTA ELENA");
    myDFPlayer.play(44);  //azuay PISTA 28
    Serial1.println("35");
    delay(3000);
    permi = 0;
  }
  if (val14 == LOW)
  {
    delay(1000);
    Serial.println("GUAYAQUIL");
    myDFPlayer.play(209);  //azuay PISTA 28
    Serial1.println("36");
    delay(3000);
    permi = 0;
  }
  if (val15 == LOW)
  {
    delay(1000);
    Serial.println("EL ORO");
    myDFPlayer.play(34);  //azuay PISTA 28
    Serial1.println("37");
    delay(3000);
    permi = 0;
  }
  if (val16 == LOW)
  {
    delay(1000);
    Serial.println("SANTO DOMINGO");
    myDFPlayer.play(45);  //azuay PISTA 28
    Serial1.println("38");
    permi = 0;
    delay(3000);
  }
  if (val17 == LOW)
  {
    delay(1000);
    Serial.println("LOS RIOS");
    myDFPlayer.play(37);  //azuay PISTA 28
    Serial1.println("39");
    permi = 0;
    delay(3000);
  }
  //GALAPAGOS
  if (val18 == LOW)
  {
    delay(1000);
    Serial.println("GALAPAGOS");
    myDFPlayer.play(210);  //azuay PISTA 28
    Serial1.println("40");
    permi = 0;
    delay(3000);
  }
  //AMAZONIA
  if (val19 == LOW)
  {
    delay(1000);
    Serial.println("PASTAZA");
    myDFPlayer.play(42);  //azuay PISTA 28
    Serial1.println("41");
    permi = 0;
    delay(3000);
  }
  if (val20 == LOW)
  {
    delay(1000);
    Serial.println("ORELLANA");
    myDFPlayer.play(41);  //azuay PISTA 28
    Serial1.println("42");
    permi = 0;
    delay(3000);
  }
  if (val21 == LOW)
  {
    delay(1000);
    Serial.println("NAPO");
    myDFPlayer.play(40);  //azuay PISTA 28
    Serial1.println("43");
    permi = 0;
    delay(3000);
  }
  if (val22 == LOW)
  {
    delay(1000);
    Serial.println("ZAMORA");
    myDFPlayer.play(48);  //azuay PISTA 28
    Serial1.println("44");
    permi = 0;
    delay(3000);
  }
  if (val23 == LOW)
  {
    delay(1000);
    Serial.println("MORONA SANTIAGO");
    myDFPlayer.play(39);  //azuay PISTA 28
    Serial1.println("45");
    permi = 0;
    delay(3000);
  }
  if (val24 == LOW)
  {
    delay(1000);
    Serial.println("SUCUMBIOS");
    myDFPlayer.play(46);  //azuay PISTA 28
    Serial1.println("46");
    permi = 0;
    delay(3000);
  }
}
