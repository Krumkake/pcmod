
#include <LCD.h>

#include <LiquidCrystal_I2C.h>


#include <IRremote.h>
#include <Wire.h>

#define knapp1 30
#define kanpp2 42
#define knapp3 312
#define knapp4 325
#define knapp5 184
#define knapp6 2
#define knapp7 261
#define knapp8 885
#define knapp9 13

LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

byte grader[8] = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};


int lm35 = A1;

int knappPin = A0;
int knappVal;
int x = 0;
int x1 = 0;
int x2 = 0;
int x3 = 0;

int farge = -1;
int b = 0;

int resetpin = 4;

int tid = 500;

int y = 0;
int y1 = 0;
int y2 = 0;

int z1 = 0;
int z2 = 0;
int z3 = 0;

int a = 0;

int red = 0;
int green = 0;
int blue = 0;

int tid1 = 60;
int temp;

int red_step = red + 2;
int green_step = green + 4;
int blue_step = blue + 2;


int receiver_pin = 9;
int greenPin = 5;
int redPin = 10;
int bluePin = 6;
IRrecv receiver(receiver_pin);
decode_results results;

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3;


void setColor(int red, int green, int blue);

void setup()
{
  lcd.begin (16, 2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print("");
  lcd.setCursor (0, 1);
  lcd.print("");
  pinMode(resetpin, OUTPUT);
  digitalWrite(resetpin, HIGH);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  receiver.enableIRIn();
  lcd.createChar(0, grader);

}

void loop()
{
  knappVal = analogRead(knappPin);
  temp = analogRead(lm35);
  temp = (temp * 0.48828125);
  Serial.println(farge);
  //Serial.println(knappVal);
  unsigned long currentMillis = millis();

  if (knappVal == knapp1)
  {
    lcd.home ();
    lcd.print("Temp = ");
    lcd.print(temp);
    lcd.write(byte(0));
    lcd.print("c");
    previousMillis3 = currentMillis;
    a = 0;
  }

  if ((knappVal == knapp6)&&(farge >= 0))
  {
    b = 1;
    farge = (farge + 1);
    
  }

  if ((knappVal == knapp5)&&(farge >= 0))
  {
    b = 1;
    farge = (farge - 1);
  }

  if((farge == -1)&&(knappVal == knapp5))
{
  b = 1;
  farge = 3;
}
if((farge == -1)&&(knappVal == knapp6))
{
  b = 1;
  farge = 1;
}

  if ((farge == 1) && (b == 1))
  {
    x = 0;
    setColor (255, 0, 0);
    x1 = 0; x2 = 0; x3 = 0;
    y1 = 0; y2 = 0;
    b = 0;
    lcd.setCursor (0, 1);
    lcd.print("Red             ");
    previousMillis3 = currentMillis;
     a = 0;
    delay(250);
  }

  if ((farge == 2) && (b == 1))
  {
    x = 0;
    setColor (0, 255, 0);
    x1 = 0; x2 = 0; x3 = 0;
    y1 = 0; y2 = 0;
    b = 0;
    lcd.setCursor (0, 1);
    lcd.print("Green           ");
    previousMillis3 = currentMillis;
     a = 0;
    delay(250);
  }

  if ((farge == 3) && (b == 1))
  {
    x = 0;
    setColor (0, 0, 255);
    x1 = 0; x2 = 0; x3 = 0;
    y1 = 0; y2 = 0;
    b = 0;
    lcd.setCursor (0, 1);
    lcd.print("Blue            ");
    previousMillis3 = currentMillis;
    a = 0;
    delay(250);
  }
  if (farge == 4)
  {
    farge = 1;
    delay(100);
  }
  if (farge == 0)
  {
    farge = 3;
    delay(100);
  }

  if ((knappVal == 0) && (a == 0) && ((currentMillis - previousMillis3) >= 4000))
  {
    lcd.home ();
    lcd.print("                ");
    lcd.setCursor (0, 1);
    lcd.print("                ");

    a = 1;
  }

  //lys off
  if (knappVal == knapp7)
  {
    setColor(0, 0, 0);
    x = 0; x1 = 0; x2 = 0; x3 = 0;
    y1 = 0; y2 = 0;
  }
  //lgbth
  if (knappVal == knapp8)
  {
    lcd.setCursor (0, 1);
    lcd.print("LGBT Strobe");
    previousMillis3 = currentMillis;
    a = 0;
    x = 1;
    y1 = 0; y2 = 0;
  }
  //smooth
  if (knappVal == knapp9)
  {

    lcd.setCursor (0, 1);
    lcd.print("Smooth Strobe");
    previousMillis3 = currentMillis;
    a = 0;
    y = 1;
    y1 = 0; y2 = 0;
  }








  if (receiver.decode(&results))
  {
    Serial.println(results.value, HEX);
    receiver.resume(); // Receive the next value;


    //fortere
    if (results.value == 16187647)
    {
      if (y1 == 1)
      {
        tid1 = tid1 - 5;
      }
      if ((x == 1) || (x1 == 1) || (x2 == 1) || (x3 == 1))
      {
        tid = tid - 20;
      }
    }

    //saktere
    if (results.value == 16220287)
    {
      if (y1 == 1)
      {
        tid1 = tid1 + 5;
      }
      if ((x == 1) || (x1 == 1) || (x2 == 1) || (x3 == 1))
      {
        tid = tid + 20;
      }
    }

    //rød
    if (results.value == 16195807)
    {
      x = 0;
      setColor (255, 0, 0);
      x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //grønn
    if (results.value == 16228447)
    {

      setColor (0, 255, 0);
      x = 0;
      x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }



    //blå
    if (results.value == 16212127)
    {
      setColor (0, 0, 255);
      x = 0;
      x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //yellow
    if (results.value == 16197847)
    {
      setColor(255, 200, 0);
      x = 0; x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //lilla
    if (results.value == 16206007)
    {
      setColor(255, 0, 255);
      x = 0; x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //aqua
    if (results.value == 16232527)
    {
      setColor(0, 255, 255);
      x = 0; x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //oransje
    if (results.value == 16199887)
    {
      setColor(255, 50, 0);
      x = 0; x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //hvit
    if (results.value == 16244767)
    {
      setColor (255, 255, 255);
      x = 0; x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //off
    if (results.value == 16203967)
    {
      setColor(0, 0, 0);
      x = 0; x1 = 0; x2 = 0; x3 = 0;
      y1 = 0; y2 = 0;
    }

    //strobe
    if (results.value == 16248847)
    {
      lcd.setCursor (0, 1);
      lcd.print("LGBT Strobe");
      previousMillis3 = currentMillis;
      a = 0;
      x = 1;
      y1 = 0; y2 = 0;
    }

    //smooth
    if (results.value == 16246807)
    {

      lcd.setCursor (0, 1);
      lcd.print("Smooth Strobe");
      previousMillis3 = currentMillis;
      a = 0;
      y = 1;
      y1 = 0; y2 = 0;
    }

  }


  //strobe void
  if (x == 1)
  {

    setColor(255, 0, 0);  // red
    previousMillis = currentMillis;
    x1 = 1;
    x = 0;
    Serial.println("red");
  }
  if ((x1 == 1) && ((currentMillis - previousMillis) >= tid))
  {
    setColor(0, 255, 0);  // green
    previousMillis = currentMillis;
    x1 = 0;
    x2 = 1;
    Serial.println("green");
  }
  if ((x2 == 1) && ((currentMillis - previousMillis) >= tid))
  {
    setColor(0, 0, 255); //blue
    previousMillis = currentMillis;
    x2 = 0;
    x3 = 1;
    Serial.println("blue");
  }
  if ((x3 == 1) && ((currentMillis - previousMillis) >= tid))
  {
    x = 1;
    x3 = 0;

  }


  //smooth void
  if (y == 1)
  {

    red = 0;
    green = 0;
    blue = 0;
    green_step = green + 4;
    setColor(red, green, blue);
    previousMillis = currentMillis;
    y1 = 1;
    y = 0;
    z1 = 1;
    delay(10);
  }




  if ((z1 == 1) && (y1 == 1) && ((currentMillis - previousMillis) >= tid1) )
  {
    red = red + red_step;
    green = green + green_step;
    // blue = blue + blue_step;
    y2 = 1;
    y1 = 0;
  }
  if ((red >= 200) && (green == 0))
  {
    z1 = 0;
    z2 = 1;
    green_step = green + 2;
  }

  if ((z2 == 1) && (y1 == 1) && ((currentMillis - previousMillis) >= tid1) )
  {
    red = red + red_step;
    // green = green + green_step;
    blue = blue + blue_step;
    y2 = 1;
    y1 = 0;
  }
  if ((blue >= 200) && (red == 0))
  {
    z2 = 0;
    z3 = 1;
  }
  if ((z3 == 1) && (y1 == 1) && ((currentMillis - previousMillis) >= tid1) )
  {
    // red = red + red_step;
    green = green + green_step;
    blue = blue + blue_step;
    y2 = 1;
    y1 = 0;
  }
  if ((green >= 200) && (blue == 0))
  {
    z3 = 0;
    z1 = 1;
  }





  if (y2 == 1)
  {
    setColor(red, green, blue);
    previousMillis = currentMillis;
    previousMillis2 = currentMillis;
    y1 = 1;
    y2 = 0;
    // Serial.println(red);
    //Serial.println(green);
    // Serial.println(blue);
  }

  if ((red + red_step > 200) || (red + red_step < 0))
  {
    red_step = red_step * -1;
  }
  if ((green + green_step > 200) || (green + green_step < 0))
  {
    green_step = green_step * -1;
  }
  if ((blue + blue_step > 200) || (blue + blue_step < 0))
  {
    blue_step = blue_step * -1;
  }
}




// setColor(255, 0, 0);  // red
// delay(1000);
// setColor(0, 255, 0);  // green
// delay(1000);
// setColor(0, 0, 255);  // blue
// delay(1000);
// setColor(255, 255, 0);  // yellow
// delay(1000);
// setColor(80, 0, 80);  // purple
// delay(1000);
// setColor(0, 255, 255);  // aqua
// delay(1000);
// setColor(255, 255, 255);
// delay(1000);


void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
