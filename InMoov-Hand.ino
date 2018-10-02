/*  
 *  Controle de Servos para o projeto InMoov - Mão Robotica
 *  Criador por Vinicius Oliveira - MakerBar
 *  Mais informações - www.Makerbar.com.br
 *  Email para contato - vinicius@makerbar.com.br
 *  Data: 27/02/2017
 */
 #include <Servo.h>

#define forInt for(int i = 0; i < 6; i++)
#define forIntJ for(int j = 0; j < 100; j++)

Servo Fingers[6]; //Thumb, Index, Middle, Ring, Little, Wrist;
int pins[6] = {11,10,9,6,5,3};
int dir[6];
double range[6][2] = {{0,100}, {0,100}, {0,180}, {0,120}, {0,100}, {110, 135}};
double steps[6];
double Cmd[6] = {1,0,0,0,1,1};


void setup() {
  forInt
  {
    Fingers[i].attach(pins[i]);
    steps[i] = (range[i][1] - range[i][0])/100;
    dir[i] = 1;
  }
  Serial.setTimeout(1);
  Serial.begin(9600);
}


void loop() {
//CmdSet(0,0,0,0,0,0);
//dynamicPos(Cmd, 2);

CmdSet(1,1,0,0,0,0);
dynamicPos(Cmd, 2);
delay(2000);

CmdSet(0,0,1,1,1,1);
dynamicPos(Cmd, 2);
delay(2000);

//openHand();
//delay(2000);
//posRead();
}

void posRead()
{
  if(Serial.available())
  {
    delay(4);
    int p = Serial.parseInt();
    int a = Serial.parseInt();
    Fingers[p].write(a);
    Serial.print(p);
    Serial.print(":");
    Serial.println(a);
  }
}


void CmdSet(double a, double b, double c, double d, double e, double f)
{
Cmd[0] = a;
Cmd[1] = b;
Cmd[2] = c;
Cmd[3] = d;
Cmd[4] = e;
Cmd[5] = f;  
}

void handLoop()
{
  forInt
  {
   double nPos = Fingers[i].read();
   
   nPos >= range[i][1] ? dir[i] = -1 : nPos <= range[i][0] ? dir[i] = 1 : dir[i] = dir[i]; 
      
   Fingers[i].write(nPos + dir[i]);
  }
  //Serial.println(Fingers[i].read());
  delay(20); 
}


void openHand()
{
  forIntJ
  {
  forInt
  {
    double nPos = Fingers[i].read();
    if(range[i][0] <= Fingers[i].read())
    {
      Fingers[i].write(-1+nPos);
    }
  }  
  delay(20);
  }
}

void dynamicPos(double toGo[6], int dl)
{
    forInt
    {
      toGo[i] = (toGo[i]*-1 )+ 1;
      toGo[i] = (range[i][1] - range[i][0])*toGo[i] + range[i][0];  
    }

    forIntJ
    {
      forInt
      {
        double nPos = Fingers[i].read();
        nPos > toGo[i] ? Fingers[i].write(nPos-steps[i]) : (nPos < toGo[i] ? Fingers[i].write(nPos+steps[i]): Fingers[i].write(nPos));
      }  
      delay(dl);
    }
}
 
