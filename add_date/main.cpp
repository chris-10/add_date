//
//  main.cpp
//  add_date
//
//  Created by Christen Dsouza on 16/07/19.
//  Copyright © 2019 Christen Dsouza. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

class Time
{
    private:
        int seconds;
        int dd,MM,yyyy;
        int hh,mm,ss;
    public:
        void getTime(void);
        void setTime(int,int,int);
        void convertIntoSeconds(void);
        void displayTime(void);
        bool isLeap(int);
        int offsetDays(int,int,int);
        void revoffsetDays(int,int,int* d,int* m);
        void addDays(int);
        int getDate(void);
        int getMonth(void);
        int getYear(void);
        int getSeconds(void);
};

int Time::getDate()
{
    return dd;
}

int Time::getMonth()
{
    return MM;
}

int Time::getYear()
{
    return yyyy;
}

void Time::setTime(int d, int m,int yy)
{
    dd=d;
    MM=m;
    yyyy=yy;
}

int Time::getSeconds()
{
    return seconds;
}

void Time::getTime(void)
{
    cout << "Enter time:" << endl;
    cout << "Day?   ";  cin >> dd;
    cout << "Month? ";  cin >> MM;
    cout << "Year? ";  cin >> yyyy;
    cout << "Hours?   ";  cin >> hh;
    cout << "Minutes? ";  cin >> mm;
    cout << "Seconds? ";  cin >> ss;
}

void Time::convertIntoSeconds(void)
{
    seconds = hh*3600 + mm*60 + ss;
}

void Time::displayTime(void)
{
    cout << "After addition, the time is = " << dd << "/" << MM
    
    << "/" << yyyy << " ";
}

// Return if year is leap year or not.
bool Time::isLeap(int y)
{
    if (y%100 != 0 && y%4 == 0 || y %400 == 0)
        return true;
    return false;
}


// Given a date, returns number of days elapsed
// from the  beginning of the current year (1st
// jan).

int Time::offsetDays(int d, int m, int y)
{
    
    int offset = d;
    
    
    
    switch (m - 1)
    
    {
            
        case 11:
            
            offset += 30;
            
        case 10:
            
            offset += 31;
            
        case 9:
            
            offset += 30;
            
        case 8:
            
            offset += 31;
            
        case 7:
            
            offset += 31;
            
        case 6:
            
            offset += 30;
            
        case 5:
            
            offset += 31;
            
        case 4:
            
            offset += 30;
            
        case 3:
            
            offset += 31;
            
        case 2:
            
            offset += 28;
            
        case 1:
            
            offset += 31;
            
    }
    
    
    
    if (isLeap(y) && m > 2)
        
        offset += 1;
    
    
    
    return offset;
}


// Given a year and days elapsed in it, finds
// date by storing results in d and m.

void Time::revoffsetDays(int offset, int y, int *d, int *m)
{
    
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
        
        31, 31, 30, 31, 30, 31 };
    
    
    
    if (isLeap(y))
        
        month[2] = 29;
    
    
    
    int i;
    
    for (i = 1; i <= 12; i++)
        
    {
        
        if (offset <= month[i])
            
            break;
        
        offset = offset - month[i];
        
    }
    
    
    
    *d = offset;
    
    *m = i;
}


// Add x days to the given date.

void Time::addDays(int x)
{
    
    int offset1 = offsetDays(getDate(), getMonth(), getYear());
    
    int remDays = isLeap(getYear())?(366-offset1):(365-offset1);
    
    
    
    // y2 is going to store result year and
    
    // offset2 is going to store offset days
    
    // in result year.
    
    int y2, offset2;
    
    if (x <= remDays)
        
    {
        
        y2 = getYear();
        
        offset2 = offset1 + x;
        
    }
    
    
    
    else
        
    {
        
        // x may store thousands of days.
        
        // We find correct year and offset
        
        // in the year.
        
        x -= remDays;
        
        y2 = getYear() + 1;
        
        int y2days = isLeap(y2)?366:365;
        
        while (x >= y2days)
            
        {
            
            x -= y2days;
            
            y2++;
            
            y2days = isLeap(y2)?366:365;
            
        }
        
        offset2 = x;
        
    }
    
    
    
    // Find values of day and month from
    
    // offset of result year.
    
    int m2, d2;
    
    revoffsetDays(offset2, y2, &d2, &m2);
    
    setTime(d2, m2, y2);
}


// Driven Program

int main()
{
    Time T; //creating objects
    
    T.getTime();
    T.convertIntoSeconds();
    
    int adays = 0;//days to add
    int ahh = 0;//hours to add
    int amm = 0;//minutes to add
    int ass = 0;//seconds to add
    
    cout << "Days to add?   ";  cin >> adays;
    cout << "Hours to add?   ";  cin >> ahh;
    cout << "Minutes to add?   ";  cin >> amm;
    cout << "Seconds to add?   ";  cin >> ass;
    
    
    int to_add_seconds = ahh*3600 + amm*60 + ass;
    int result_seconds = T.getSeconds() + to_add_seconds;
    
    int n = result_seconds;
    //convert seconds to hh:mm:ss
    int days = n / (24 * 3600);
    
    n = n % (24 * 3600);
    int hh = n / 3600;
    
    n %= 3600;
    int mm = n / 60 ;
    
    n %= 60;
    int ss = n;

    adays += days;

    T.addDays(adays);
    T.displayTime();
    cout << setw(2) << setfill('0') << hh << ":"
    << setw(2) << setfill('0') << mm << ":"
    << setw(2) << setfill('0') << ss << endl;
    return 0;
}
