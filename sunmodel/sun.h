#ifndef SUN_H
#define SUN_H
// C++ program calculating the solar position for
// the current date and a set location (latitude, longitude)
// Jarmo Lammi 1999
//
// Code refreshed to work in the newer versions of C++
// Compiled and tested with
// Apple LLVM version 6.0 (clang-600.0.56) (based on LLVM 3.5svn)
// Target: x86_64-apple-darwin14.0.0
// Jarmo Lammi 4-Jan-2015

#include <iostream>
#include <math.h>
#include <time.h>
using std::cout;
using std::cin;
using std::ios;
using std::endl;

#define pi      3.14159265359
#define tpi     2 * pi
#define degs    180.0/pi
#define rads    pi/180.0
#define SunDia  0.53
#define AirRefr 34.0/60.0


class sun
{
public: //Constructors
    sun(int year, int m, int day, double UT, double longit, double latit);

    double getDegress() const;
    double getAltmax()  const;
    double getJd()      const;
    double getDec()     const;
    double getNoont()   const;
    double getRiset()   const;
    double getSettm()   const;
    double getRA()      const;
    double getDaylen()  const;
    double getDelta()   const;
    double getAltit()   const;
    double getAzim()    const;

private: // Methods

    double FNday    (int y, int m, int d, float h);
    double FNrange  (double x);
    double f0       (double lat, double declin);
    double FNsun    (double d);
    void   showhrmn (double dhr);


private: //variables
    double azim;
    double altit;
    double riset;
    double settm;
    double noont;
    double degress;
    double altmax;
    double jd;
    double dec;
    double L;
    double RA;
    double g;
    double daylen;
    double delta;
    double x;
    double y;
    double z;
};
#endif
