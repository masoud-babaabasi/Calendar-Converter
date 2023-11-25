#include "CalenderConverter.h"

Time t1;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);//5 seconds
  Serial.println("Enter time miladi like : 14/3/2020");
}
void loop() {
 char str[64];
 if(Serial.available() >= 9){
  uint16_t y;
  uint8_t m,d;
  String temp;
  temp = Serial.readStringUntil('/');
  d = temp.toInt();
  temp = Serial.readStringUntil('/');
  m = temp.toInt();
  temp = Serial.readStringUntil('\n');
  y = temp.toInt();
  t1.setTime( y , m , d , MILADI);
  //t1.offMon = 1;
  sprintf(str,"\n%d/%d/%d , %s , %s , %s\n",t1.year,t1.mon,t1.date,t1.getType(),t1.getDay(),t1.getMonth());
  Serial.print(str);
  
  t1.toShamsi();
  sprintf(str,"\n%d/%d/%d , %s , %s , %s\n",t1.year,t1.mon,t1.date,t1.getType(),t1.getDay(),t1.getMonth());
  Serial.print(str);
  
  t1.toMiladi();
  sprintf(str,"\n%d/%d/%d , %s , %s , %s\n",t1.year,t1.mon,t1.date,t1.getType(),t1.getDay(),t1.getMonth());
  Serial.print(str);

  Serial.println("Enter time miladi like : 14/3/2020");
 }
 
}
