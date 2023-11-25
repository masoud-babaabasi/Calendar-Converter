#include "CalenderConverter.h"
const int  DayMiladiMonth[12]      = {31,28,31,30,31,30,31,31,30,31,30,31};
const int  DayMiladiMonthLeap[12]  = {31,29,31,30,31,30,31,31,30,31,30,31};
Time t1,t2;
uint16_t y=2022;
uint8_t m = 5,d = 16;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);//5 seconds
}
void loop() {
 char str[256];
 if(y <= 2040){
  t1.setTime( y , m , d , MILADI);
  t2 = t1;
  t1.toShamsi();
  sprintf(str," %d/%d/%d , %s , %s , %s ,",t1.year,t1.mon,t1.date,t1.getType(),t1.getDay(),t1.getMonth());
  Serial.print(str);
  sprintf(str," %d/%d/%d , %s , %s , %s\n",t2.year,t2.mon,t2.date,t2.getType(),t2.getDay(),t2.getMonth());
  Serial.print(str);
  t1.toMiladi();
  if( !(t1 == t2) ){
    sprintf(str,"t1 = %d/%d/%d , t2 = %d/%d/%d \n",t1.year,t1.mon,t1.date,t2.year,t2.mon,t2.date);
    Serial.print(str);
  } 
  d++;
  if( ((MiladiIsLeap(y)) && d > DayMiladiMonthLeap[m - 1]) || ( (!MiladiIsLeap(y)) && d > DayMiladiMonth[m - 1])){
    d = 1;
    m++;
    if( m > 12 ){
      m = 1;
      y++;
    }
  }
 }
 
}
