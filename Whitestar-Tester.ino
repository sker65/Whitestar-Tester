
#define A15 30 // PC7
#define Q 31   // PC6
#define E 33   // PC4
typedef unsigned char BYTE;

void setup()
{
  DDRA = 0xFF;      // port A = out
  DDRC = B11010000; // port C 7,6,4 = out
  digitalWrite(A15, LOW);
  digitalWrite(Q, LOW);
  digitalWrite(E, LOW);
}

void latchData(int data)
{
  PORTA = data;
  digitalWrite(Q, HIGH);
  delayMicroseconds(10);
  digitalWrite(Q, LOW);
  delayMicroseconds(10);
}

void strobe()
{
  digitalWrite(E, HIGH);
  delayMicroseconds(10);
  digitalWrite(E, LOW);
  delayMicroseconds(10);
}

void setSoundActive(bool active)
{
  digitalWrite(A15, active ? LOW : HIGH);
}

int sound[] = {0xFD, 0x1A, 5000, 0xfd, 0xcd, 2000, 0xfc, 0x3d, 4000, 0xfe, 0x64, 1000, 0xfd, 0x02, 6000, 0};

void loop()
{
  int i = 0;
  while (sound[i])
  {
    latchData(sound[i++]);
    strobe();
    latchData(sound[i++]);
    strobe();
    delay(sound[i++]);
  }
  delay(10000);
}
