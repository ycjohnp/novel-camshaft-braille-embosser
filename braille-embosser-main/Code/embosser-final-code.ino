#include <SoftwareSerial.h>
#include <Servo.h>
//SoftwareSerial Braille_Printer(12,13);
Servo myservo;
#define servoPin 7
#define zdirPin 13
#define zstepPin 12
#define down 0
#define up 1
#define left 1
#define right 0
#define xdirPin 5
#define xstepPin 6
#define ydirPin 8
#define ystepPin 9
int printfinished = 0;
int start = 1;
int ydistance = 20; //33 esteps/mm this is at 1/16 microstepping
int xdistance = 220; // 20 esteps/mm this is at 1/32 microstepping
float zdistance = 5.7; // 100 esteps/mm
float xtraveleddistance = 0;
int speed_stepprt = 400;
int num1, num2, j, length, totle, updig_sum = 0, updig_sum_last = 0, printcode;
String row[10];
String line[3], code[2];
String alphabet[31][3][2] = {
  {{"1", "0"}, {"0", "0"}, {"0", "0"}}, //a
  {{"1", "0"}, {"1", "0"}, {"0", "0"}}, //b
  {{"1", "1"}, {"0", "0"}, {"0", "0"}}, //c
  {{"1", "1"}, {"0", "1"}, {"0", "0"}}, //d
  {{"1", "0"}, {"0", "1"}, {"0", "0"}}, //e
  {{"1", "1"}, {"1", "0"}, {"0", "0"}}, //f
  {{"1", "1"}, {"1", "1"}, {"0", "0"}}, //g
  {{"1", "0"}, {"1", "1"}, {"0", "0"}}, //h
  {{"0", "1"}, {"1", "0"}, {"0", "0"}}, //i
  {{"0", "1"}, {"1", "1"}, {"0", "0"}}, //j
  {{"1", "0"}, {"0", "0"}, {"1", "0"}}, //k
  {{"1", "1"}, {"1", "0"}, {"1", "0"}}, //l
  {{"1", "1"}, {"0", "0"}, {"1", "0"}}, //m
  {{"1", "1"}, {"0", "1"}, {"1", "0"}}, //n
  {{"1", "0"}, {"0", "1"}, {"1", "0"}}, //o
  {{"1", "1"}, {"0", "0"}, {"0", "0"}}, //p
  {{"1", "1"}, {"1", "1"}, {"1", "0"}}, //q
  {{"1", "0"}, {"1", "1"}, {"1", "0"}}, //r
  {{"0", "1"}, {"1", "0"}, {"1", "0"}}, //s
  {{"0", "1"}, {"1", "1"}, {"1", "0"}}, //t
  {{"1", "0"}, {"0", "0"}, {"1", "1"}}, //u
  {{"1", "0"}, {"1", "0"}, {"1", "1"}}, //v
  {{"0", "1"}, {"1", "1"}, {"0", "1"}}, //w
  {{"1", "1"}, {"0", "0"}, {"1", "1"}}, //x
  {{"1", "1"}, {"0", "1"}, {"1", "1"}}, //y
  {{"1", "0"}, {"0", "1"}, {"1", "1"}}, //z
  {{"0", "1"}, {"0", "1"}, {"1", "1"}}, // hastag
  {{"0", "0"}, {"0", "0"}, {"0", "1"}}, // capitalization symbol
  {{"0", "0"}, {"0", "0"}, {"0", "0"}}, //empty
  {{"0", "0"}, {"1", "0"}, {"0", "0"}}, //,
  {{"0", "0"}, {"1", "1"}, {"0", "1"}} //.

};
//170  01   0
//30   10   50
//80   11   100
//130  00   160

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  Braille_Printer.begin(9600);
  pinMode(zstepPin, OUTPUT);
  pinMode(zdirPin, OUTPUT);
  pinMode(xstepPin, OUTPUT);
  pinMode(xdirPin, OUTPUT);
  pinMode(ystepPin, OUTPUT);
  pinMode(ydirPin, OUTPUT);
  digitalWrite(zdirPin, HIGH);
  myservo.attach(servoPin);
  code[0] = code[1] = "";
  ymove(200, down); delay (1000);
  zmove(19, down); delay (1000);

}

void loop() {

  myservo.write(160);
  
  if (Serial.available())
  {
    String str = Serial.readString();
    length = str.length();
    //if(length>0)      printfinished ==1;
    for (int k = 0; k < str.length(); k++)
    {
      if (isupper(str[k]))
        length++;
      if (isdigit(str[k]))
        length++;
    }

    for ( j = 0; j < length / 20 + 1; j++)
    {
      totle = 20;
      for (int k = j * 20 - updig_sum_last; k < j * 20 - updig_sum_last + totle; k++)
      {
        if (isupper(str[k]))
        {
          totle--; updig_sum++;
        }
        else if (isdigit(str[k]))
        {
          totle--; updig_sum++;
        }
        row[j] += str[ k];
        if (str[ k + 1] == '\0')  break;
      }
      updig_sum_last = updig_sum;
    }
    Serial.print("row[0]:"); Serial.println(row[0]);
    Serial.print("row[1]:"); Serial.println(row[1]);
    for (int m = 0; m < j; m++)
    {
      for (int i = 0; i < row[m].length(); i++)
      {
        if (row[m][i] == ' ')   num1 = 28;
        else if (isupper(row[m][i]))
        {

          line[0] = line[0] + alphabet[27][0][0] + alphabet[27][0][1];
          line[1] = line[1] + alphabet[27][1][0] + alphabet[27][1][1];
          line[2] = line[2] + alphabet[27][2][0] + alphabet[27][2][1];
          num1 = row[m][i] - 'A';
        }
        else if (isdigit(row[m][i]))
        {
          line[0] = line[0] + alphabet[26][0][0] + alphabet[26][0][1];
          line[1] = line[1] + alphabet[26][1][0] + alphabet[26][1][1];
          line[2] = line[2] + alphabet[26][2][0] + alphabet[26][2][1];
          num1 = row[m][i] - '0';
        }
        else if (islower(row[m][i]))
          num1 = row[m][i] - 'a';
        else if (row[m][i] == ',')
          num1 = 29;
        else if (row[m][i] == '.')
          num1 = 30;
        else  break;
        line[0] = line[0] + alphabet[num1][0][0] + alphabet[num1][0][1];
        line[1] = line[1] + alphabet[num1][1][0] + alphabet[num1][1][1];
        line[2] = line[2] + alphabet[num1][2][0] + alphabet[num1][2][1];
      }
      for (int c = 0; c < 3; c++)
        if (line[c].length() % 4 != 0)
          line[c] = line[c] + "0" + "0";
      Serial.print("line[0]:"); Serial.println(line[0]);
      Serial.print("line[1]:"); Serial.println(line[1]);
      Serial.print("line[2]:"); Serial.println(line[2]);
      for (int n = 0; n < 3; n++)
      {

        for (int p = line[n].length() - 1; p >= 0; p--)
        {
          //Serial.print("line[n].length():");Serial.println(line[n].length());
          if (((p + 1) % 4 == 0) && line[n][p - 3] != '\0')
          {
            code[0] = code[0] + line[n][p] + line[n][p - 2];
            code[1] = code[1] + line[n][p - 1] + line[n][p -  3];
            Serial.print("code[0]:"); Serial.println(code[0]);
            Serial.print("code[1]:"); Serial.println(code[1]);
          }
          if (code[0] != "")
          {
            //Serial.print("code[0]:");Serial.println(code[0]);
            //Serial.print("code[1]:");Serial.println(code[1]);
            printcode = code[0].toInt();
            print_code(printcode);
            xmove(3.5, right, 800); //11.5
            printcode = code[1].toInt();
            print_code(printcode);
            xmove(12.55, right, 600);//18.7
            xtraveleddistance += 16.05;//28/2
            Serial.print("xtraveleddistance:");
            Serial.println(xtraveleddistance);
          }
          code[0] = code[1] = "";
        }

        ymove(4, down);
        Serial.print("xtraveleddistance:");
        Serial.println(xtraveleddistance);
        xmove(xtraveleddistance, left, 400);
        xtraveleddistance = 0;
        delay(2000);
      }
      ymove(2.5, down);
      line[0] = line[1] = line[2] = "";
    }
    printfinished == 1;
    Serial.print("printfinished") ;
    ymove(400, down);
    zmove(27, up);
  }
  if (printfinished == 1) {
    Serial.print("printfinished") ;
    ymove(400, down);
    zmove(27, up);
  }

}
void print_code(int code) {
  switch (code) {
    case 00: myservo.write(140); delay(2000); zmove(zdistance, down); delay(800); zmove(zdistance, up); zmove(zdistance, down); delay(800); zmove(zdistance, up); break;
    case 10: myservo.write(30); delay (2000); zmove(zdistance, down); delay(800); zmove(zdistance, up); zmove(zdistance, down); delay(800); zmove(zdistance, up); break;
    case 01: myservo.write(180); delay (2000); zmove(zdistance, down); delay(800); zmove(zdistance, up); zmove(zdistance, down); delay(800); zmove(zdistance, up); break;
    case 11: myservo.write(90); delay (2000); zmove(zdistance, down); delay(800); zmove(zdistance, up); zmove(zdistance, down); delay(800); zmove(zdistance, up); break;
  }
}

void zmove(float mm, int direct) {
  int steps = 100 * mm;
  digitalWrite(zdirPin, direct);
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(zstepPin, HIGH);
    delayMicroseconds(speed_stepprt);
    digitalWrite(zstepPin, LOW);
    delayMicroseconds(speed_stepprt);
  }
}

void xmove(float mm, int direct, int speed) {
  int steps = mm * 76;
  digitalWrite(xdirPin, direct);
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(xstepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(xstepPin, LOW);
    delayMicroseconds(speed);
  }
}

void ymove(float mm, int direct) {
  int steps = mm * 33;
  digitalWrite(ydirPin, direct);
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(ystepPin, HIGH);
    delayMicroseconds(speed_stepprt);
    digitalWrite(ystepPin, LOW);
    delayMicroseconds(speed_stepprt);
  }
}
