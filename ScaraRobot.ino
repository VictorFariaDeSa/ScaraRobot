#include <Servo.h>

Servo junta1;
Servo junta2;
double dt=0.01; //segundos
double L1=63.2;
double L2=63.25;
double x,y,o1,o2;
double c2,s2,k1,k2;
const double pi=3.14159265;

double cininv()
{
  // argumentos: x e y globais
  // retorno: o1 e o2 globais
  c2=(x*x+y*y-L1*L1-L2*L2)/(2*L1*L2);
  if ((c2>=-1)&&(c2<=1))
  {
    s2=+sqrt(1-c2*c2);
    o2=atan2(s2,c2);
    k1=L1+L2*c2;
    k2=L2*s2;
    o1=atan2(y,x)-atan2(k2,k1);
  }
  else
  {
    Serial.println("Posição fora do espaço de trabalho");
  }  
}

void movimento(double x0, double y0, double xf, double yf, double vm, double am)
{
    double tb,tf,t,d;
    double d0=0;
    double df=sqrt(sq(xf-x0)+sq(yf-y0));

    if (am >= (vm*vm/(df-d0)) )
    {
        Serial.println("Atinge velocidade máxima");
        tb=vm/am;
        tf=(am*tb*tb+(df-d0))/(am*tb);
        for(int i=0;i<=(tf/dt);i++)
        {
            t=i*dt;
            if(t<=tb)
            {
                //aceleração
                d=d0+1.0/2.0*am*t*t;
            }
            else if ((t>tb)&&(t<(tf-tb)))
            {
                //velocidade constante
                d=d0+1.0/2.0*am*tb*tb+vm*(t-tb);
            }
            else
            {
                //desaceleração constante
                d=df-1.0/2.0*am*sq(tf-t);
            }
            x=x0+d/df*(xf-x0);
            y=y0+d/df*(yf-y0);
            // Serial.print(x);
            // Serial.print("   ");
            // Serial.println(y);
            cininv();
            double a1 = o1*180/pi;
            double a2 = o2*180/pi+90;
            junta1.write(a1);
            junta2.write(a2-90);
                Serial.print("Angulo 1: ");
                Serial.print(a1);
                Serial.print("\t Angulo2: ");
                Serial.println(a2);    
            delay(dt*1000);
        }
    }    
    else
    {
        Serial.println("Não atinge velocidade máxima");
        tf=2*sqrt((df-d0)/am);
        tb=tf/2;
        for(int i=0;i<=(tf/dt);i++)
        {
            t=i*dt;
            if(t<=tb)
            {
                d=d0+1.0/2*am*t*t;
            }
            else
            {
                d=df-1.0/2*am*sq(tf-t);
            }  
            
            x=x0+d/df*(xf-x0);
            y=y0+d/df*(yf-y0);
            cininv();
            double a1 = o1*180/pi;
            double a2 = o2*180/pi+90;
            junta1.write(a1);
            junta2.write(a2-90);
                Serial.print("Angulo 1: ");
                Serial.print(a1);
                Serial.print("\t Angulo2: ");
                Serial.println(a2);      
            delay(dt*1000);
        }
    }

}

void setup() {
  // put your setup code here, to run once:
  junta1.attach(9);
  junta2.attach(11);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float p1 = 70;
  float p2 = 80;
  delay(1000);
  junta1.write(0);
  junta2.write(90);
  movimento(-p1,p1,p1,p1,10,5);
  // Serial.println("Fim da reta");
  movimento(p1,p1,p1,p2,10,5);
  // Serial.println("Fim da reta");
  movimento(p1,p2,-p1,p2,10,5);
  // Serial.println("Fim da reta");
  movimento(-p1,p2,-p1,p1,10,5);
  // Serial.println("Fim do ciclo");

}
