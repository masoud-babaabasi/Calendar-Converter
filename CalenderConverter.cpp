#include "CalenderConverter.h"

uint8_t isShamsiLeap(int shamsiYear){
	for(uint8_t i = 0 ; i < 8 ; i++){
		if( (shamsiYear % 33) == pgm_read_byte(&shamsiLeap[i]) ) return 1;
	}
	return 0;
}

Time::Time(uint16_t _year,uint8_t _mon,uint8_t _date, uint8_t _type ,uint8_t _dow)
{
	if( _year < 1300 ) year = 1398;
	else year = _year;
	if(_mon > 12 || _mon < 1 ) mon = 1;
	else mon  = _mon;
	if(_date >31 || _date < 1) date = 1;
	else date = _date;
	if( _type > 2 ) type = 0;
	else type = _type;
	if(_dow > 7 || _dow < 1) dow  = 1;
	else dow = _dow;
	//offset = 0;
	//offMon = 13;
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
void Time::setTime(uint16_t _year,uint8_t _mon,uint8_t _date,uint8_t _type){
	if( _year < 1300 ) year = 1398;
	else year = _year;
	if(_mon > 12 || _mon < 1 ) mon = 1;
	else mon  = _mon;
	if(_date >31 || _date < 1) date = 1;
	else date = _date;
	if( _type > 1 ) type = 0;
	else type = _type;
	setDOW();
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
void Time::operator=(Time t){
	year = t.year;
	mon  = t.mon;
	date = t.date;
	dow  = t.dow;
	type = t.type;
	//setDOW();
}
unsigned char Time::operator==(Time t){
	if( this->year == t.year &&	this->mon  == t.mon && this->date == t.date && this->dow  == t.dow && this->type == t.type) return 1;
	return 0;
	//setDOW();
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
void Time::setDOW(){
	switch(type){
		case MILADI:
		dow = (year % 100);
		dow = dow*1.25;
		dow += date;
		dow += (pgm_read_byte(&mArr[mon-1]));
		if (((year % 4)==0) && (mon<3)) dow -= 1;
		while(dow > 7 ) dow -= 7;
		break;
		case SHAMSI:
		toMiladi();
		dow = (year % 100);
		dow = dow*1.25;
		dow += date;
		dow += (pgm_read_byte(&mArr[mon-1]));
		if (((year % 4)==0) && (mon<3)) dow -= 1;
		while(dow > 7 ) dow -= 7;
		toShamsi();
		break;
	}
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
void Time::toShamsi(){
	if(type == MILADI){
	uint8_t shamsiMonth[] = { 31 , 31 , 31 , 31 , 31 , 31 , 30 , 30 , 30 , 30 , 30 , 29};
	const int SH_year_ref = 1354 , M_year_ref = 1975;
	const uint8_t SH_month_ref = 1 ,SH_date_ref = 1 , M_month_ref = 3 , M_date_ref = 21;
    int yy;
	int  daysCount;
	Time miladi;
	miladi=*this;
	yy = M_year_ref;
	if(miladi.year > M_year_ref ){
		daysCount = 365 - ( pgm_read_word(&sumDayMiladiMonth[M_month_ref-1]) + M_date_ref  - 1); // count the days left in M_year_ref
		yy++;
	}
	while( yy < miladi.year){
     daysCount += 365 + MiladiIsLeap(yy);
     yy++;
	}
	if( MiladiIsLeap(miladi.year) )	daysCount += pgm_read_word(&sumDayMiladiMonthLeap[miladi.mon-1]) + miladi.date;
	else daysCount += pgm_read_word(&sumDayMiladiMonth[miladi.mon-1]) + miladi.date;
	year = SH_year_ref;
	mon =SH_month_ref;
	while( daysCount > ( 365 + isShamsiLeap(year) ) ){
		daysCount = daysCount - ( 365 + isShamsiLeap(year));
		year++;
	}
	if( isShamsiLeap(year) ) shamsiMonth[11] = 30;
	while( daysCount > shamsiMonth[mon-1] ){
		daysCount -=shamsiMonth[mon-1];
		mon++;
	}
	date = daysCount;
	}
	else if(type == GHAMARI){
	}
	this->type = SHAMSI;
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
void Time::toMiladi()
{	
	if(type == GHAMARI ) toShamsi();
	if(type == SHAMSI){
		uint8_t miladidays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        const int SH_year_ref = 1353 , M_year_ref = 1975;
		const uint8_t SH_month_ref = 10 ,SH_date_ref = 11 , M_month_ref = 1 , M_date_ref = 1;
		int yy;
		int  daysCount;
		Time shamsi = *this;
        yy = SH_year_ref;
		if(shamsi.year > SH_year_ref ){
			daysCount = 365 - ( pgm_read_word(&sumshamsi[SH_month_ref-1]) + SH_date_ref  - 1); // count the days left in M_year_ref
			yy++;
		}
		while( yy < shamsi.year){
		 daysCount += 365 + isShamsiLeap(yy);
		 yy++;
		}
		daysCount += pgm_read_word(&sumshamsi[shamsi.mon-1]) + shamsi.date;
		year = M_year_ref;
		mon =M_month_ref;
		while( daysCount > ( 365 + MiladiIsLeap(year) ) ){
			daysCount = daysCount - ( 365 + MiladiIsLeap(year));
			year++;
		}
		if( MiladiIsLeap(year) ) miladidays[1] = 29;
		while( daysCount > miladidays[mon-1] ){
			daysCount -=miladidays[mon-1];
			mon++;
		}
		date = daysCount;
		type = MILADI;
	}
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
char *Time::getType(){
	if(type > 2 ) type = 0;
	static char str[10];
	strcpy_P(str,(char*)pgm_read_word(&(types[type])));
	return (char*)&str;
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
char *Time::getDay(){
	static char str[15];
	if(dow < 1 || dow > 7 ) dow = 1;
	switch(type){
		case MILADI:
		strcpy_P(str,(char*)pgm_read_word(&(MiladiDaysLong[dow-1])));
		break;
		case SHAMSI:
		strcpy_P(str,(char*)pgm_read_word(&(PersianDays[dow-1])));
		break;
	}
	return (char*)&str;
}
/****************************************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************************************/
char *Time::getMonth(){
	static char str[15];
	if(mon < 1 || mon >12 ) mon = 1;
	switch(type){
		case MILADI:
		strcpy_P(str,(char*)pgm_read_word(&(MiladiMonthLong[mon-1])));
		break;
		case SHAMSI:
		strcpy_P(str,(char*)pgm_read_word(&(ShamsiMonth[mon-1])));
		break;
	}
	return (char*)&str;
}
