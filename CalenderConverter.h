/*
* This is writen by Masoud Babaabasi
* masoud.tafresh@gmail.com
*/

//#include <avr/pgmspace.h>
#include <arduino.h>
#include"names.h"

#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define MILADI 0
#define SHAMSI 1
#define GHAMARI 2

#define MiladiIsLeap(miladiYear) ((((miladiYear % 100)!= 0 && (miladiYear % 4) == 0) || \
								((miladiYear % 100)== 0 && (miladiYear % 400) == 0)) ? 1:0)
								

//#define isShamsiLeap(shamsiYear) (( shamsiYear - 1379 ) % 4 == 0 ) ? 1:0
#define round(f) ( ((float)(f) - (int)(f)) >= 0.5 )?((int)(f))+1:(int)(f)
uint8_t isShamsiLeap(int shamsiYear);

const uint16_t  sumDayMiladiMonth[12] PROGMEM = {0,31,59,90,120,151,181,212,243,273,304,334};
const uint16_t  sumDayMiladiMonthLeap[12] PROGMEM = {0,31,60,91,121,152,182,213,244,274,305,335};
const uint16_t sumshamsi[12] PROGMEM = { 0 ,31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336 };
const uint8_t mArr[12] PROGMEM = {6,2,2,5,0,3,5,1,4,6,2,4};
const uint8_t shamsiLeap[8] PROGMEM = {1, 5, 9, 13 , 17,22, 26 , 30};
//{0,4,8,12,16,20,24,29,33,37,41,45,49,53,57,62,66,70,74,78,82,86,90,95,99,103,107,111,115,119,124};
//const uint8_t ghamariLeapYear[] PROGMEM = {2, 5 , 7, 10, 13, 16, 18, 21, 24, 26, 29};
//const int ghamarisumdays[] PROGMEM = {0, 30 , 59, 89, 118, 148, 177, 207, 236, 266, 295 , 325 , 354};

class Time
{
public:
	uint8_t		date;
	uint8_t		mon;
	uint16_t	year;
	uint8_t		dow;
	uint8_t		type;

	Time(uint16_t _year=2020,uint8_t _mon=2,uint8_t _date=2,uint8_t _type = MILADI, uint8_t _dow = MONDAY);
	void setTime(uint16_t _year,uint8_t _mon,uint8_t _date,uint8_t _type);
	void toShamsi();
	void toMiladi();
	void setDOW();
	char *getType();
	char *getDay();
	char *getMonth();
	void operator=(Time t);
	unsigned char operator==(Time t);

};