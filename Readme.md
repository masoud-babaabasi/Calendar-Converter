# Arduino Calender Converter Library

This library is written for Arduino using C++ language.
The purpose of this library is to convert date from `Persian` Calender (Shamsi) to `Gregorian` (Miladi) and vice versa.	
You can learn how to use this library from the examples provided in the example folder.
```C++
	Time t1;
	t1.setTime( 2022 , 11 , 24 , MILADI);
	t1.toShamsi();
	sprintf(str,"%d/%d/%d , %s , %s , %s\n",t1.year,t1.mon,t1.date,t1.getType(),t1.getDay(),t1.getMonth());
  Serial.print(str);
```