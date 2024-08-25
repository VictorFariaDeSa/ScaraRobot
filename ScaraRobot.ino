#include <Servo.h>

Servo joint1; // First joint servo object
Servo joint2; // Second joint servo object
float dt=0.2; // Time discretization
const float L1=63.2; // First arm length
const float L2=63.25; // Second arm length
const double Pi=3.14159265; // Pi value

float* cininv(float x, float y, float l1, float l2) {
  double c2,s2,k1,k2;
  static float angles[2]; // Array for angle storage
  float o1,o2; // angles for joints 1 and 2 in rad
  c2 = (sq(x) + sq(y) - sq(l1) - sq(l2)) / (2 * l1 * l2); // cosine joint 2
  
  if (c2 >= -1 && c2 <= 1) {
    s2 = sqrt(1 - sq(c2));
    o2 = atan2(s2, c2);
    k1 = l1 + l2 * c2;
    k2 = l2 * s2;
    o1 = atan2(y, x) - atan2(k2, k1);
    
    float degJoint1 = o1 * 180.0 / Pi + 90;
    float degJoint2 = o2 * 180.0 / Pi + 90;
    
    angles[0] = degJoint1;
    angles[1] = degJoint2;
    
    return angles;
  } else {
    Serial.println("Posição fora do espaço de trabalho");
    return NULL;
  }
}

void move(float x0, float y0, float xf, float yf, float maxSpeed, float maxAccel) {
  double t,d; // Time and distance for current step
  double accelTime,finalTime;
  double d0=0;
  double df=sqrt(sq(xf-x0)+sq(yf-y0));
  float deg1;
  float deg2; 

  if (maxAccel >= (sq(maxSpeed)/(df-d0)) ){
    Serial.println("Atinge velocidade máxima");
    accelTime = maxSpeed/maxAccel;
    finalTime = (maxAccel*sq(accelTime)+(df-d0))/(maxAccel*accelTime);
  } else {
    Serial.println("Não atinge velocidade máxima");
    finalTime=2*sqrt((df-d0)/maxAccel);
    accelTime = finalTime/2;
  }
    
  for(int i=0;i<=(finalTime/dt);i++){
    t=i*dt;
    if(t<=accelTime){ // Acceleration
        d=d0+1.0/2*maxAccel*sq(t);

    } else if ((t>accelTime)&&(t<(finalTime-accelTime)) && (maxAccel >= (sq(maxSpeed)/(df-d0)))) { // Constant Speed
        d=d0+1.0/2*maxAccel*sq(accelTime)+maxSpeed*(t-accelTime);

    } else { // Decceleration
        d=df-1.0/2*maxAccel*sq(finalTime-t);
    }

      float x = x0+d/df*(xf-x0);
      float y = y0+d/df*(yf-y0);        
      float* angles = cininv(x, y, L1, L2);
      deg1 = angles[0];
      deg2 = angles[1];
      joint1.write(deg1);
      joint2.write(180-deg2);
      delay(dt*1000);
  }
}

void drawRectangle(float x1,float x2,float y1,float y2,float maxSpeed, float maxAccel){
  move(x1,y1,x1,y2,maxSpeed, maxAccel);
  move(x1,y2,x2,y2,maxSpeed, maxAccel);
  move(x2,y2,x2,y1,maxSpeed, maxAccel);
  move(x2,y1,x1,y1,maxSpeed, maxAccel);

}

void setup() {
  joint1.attach(9);
  joint2.attach(10);
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  drawRectangle(100,110,30,45,2,2);
}

