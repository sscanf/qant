#include "sun.h"
#include <QString>

//   Get the days to J2000
//   h is UT in decimal hours
//   FNday only works between 1901 to 2099 - see Meeus chapter 7
double sun::FNday(int y, int m, int d, float h)
{
    int luku = - 7 * (y + (m + 9)/12)/4 + 275*m/9 + d;
    // type casting necessary on PC DOS and TClite to avoid overflow
    luku+= (long int)y*367;
    return (double)luku - 730530.0 + h/24.0;
}

//   the function below returns an angle in the range
//   0 to 2*pi
double sun::FNrange(double x)
{
    double b = x / tpi;
    double a = tpi * (b - (long)(b));
    if (a < 0) a = tpi + a;
    return a;
}

// Calculating the hourangle
//
double sun::f0(double lat, double declin)
{
    double fo,dfo;
    dfo = rads*(0.5*SunDia + AirRefr);
    if (lat < 0.0) dfo = -dfo;	// Southern hemisphere
    fo = tan(declin + dfo) * tan(lat*rads);
    if (fo>0.99999) fo=1.0; // to avoid overflow //
    fo = asin(fo) + pi/2.0;
    return fo;
}

double sun::FNsun(double d)
{
    double w,M,v,r;
    //   mean longitude of the Sun
    w = 282.9404 + 4.70935E-5 * d;
    M = 356.047 + 0.9856002585 * d;
    // Sun's mean longitude
    L = FNrange(w * rads + M * rads);

    //   mean anomaly of the Sun

    g = FNrange(M * rads);

    // eccentricity
    double ecc = 0.016709 - 1.151E-9 * d;

    //   Obliquity of the ecliptic

    double obliq = 23.4393 * rads - 3.563E-7 * rads * d;
    double E = M + degs * ecc * sin(g) * (1.0 + ecc * cos(g));
    E = degs*FNrange(E*rads);
    x = cos(E*rads) - ecc;
    y = sin(E*rads) * sqrt(1.0 - ecc*ecc);
    r = sqrt(x*x + y*y);
    v = atan2(y,x)*degs;
    // longitude of sun
    double lonsun = v + w;
    lonsun-= 360.0*(lonsun>360.0);

    // sun's ecliptic rectangular coordinates
    x = r * cos(lonsun*rads);
    y = r * sin(lonsun*rads);
    double yequat = y * cos(obliq);
    double zequat = y * sin(obliq);
    RA = atan2(yequat,x);
    delta = atan2(zequat,sqrt(x*x + yequat*yequat));
    RA*= degs;

    //   Ecliptic longitude of the Sun

    return FNrange(L + 1.915 * rads * sin(g) + .02 * rads * sin(2 * g));
}

double sun::getAzim() const
{
    return azim;
}

double sun::getAltit() const
{
    return altit;
}

/*
// Display decimal hours in hours and minutes
QString sun::showhrmn(double dhr)
{
    QString str;
    int hr,mn;
    hr=(int) dhr;
    mn = (dhr - (double) hr)*60;
    if (hr < 10) cout << '0';
    str = (QString ("%1:")).arg (hr);
    if (mn < 10) str+='0';
    str+=QString ("%1").arg(mn);
}
*/
sun::sun(int year, int m, int day, double UT, double longit, double latit)
{
    jd = FNday(year, m, day, UT);

    //   Use FNsun to find the ecliptic longitude of the
    //   Sun
    double lambda = FNsun(jd);

    //   Obliquity of the ecliptic
    double obliq = 23.4393 * rads - 3.563E-7 * rads * jd;

    // Sidereal time at Greenwich meridian
    double GMST0 = L*degs/15.0 + 12.0;	// hours
    double SIDTIME = GMST0 + UT + longit/15.0;
    // Hour Angle
    double ha;
    ha = 15.0*SIDTIME - RA;	// degrees
    ha = FNrange(rads*ha);
    x = cos(ha) * cos(delta);
    y = sin(ha) * cos(delta);
    z = sin(delta);
    double xhor = x * sin(latit*rads) - z * cos(latit*rads);
    double yhor = y;
    double zhor = x * cos(latit*rads) + z * sin(latit*rads);
    azim = atan2(yhor,xhor) + pi;
    azim = FNrange(azim);
    altit = asin(zhor) * degs;

    // cout << "L = " <<  L* degs << " degr\n";
    // cout << "RA = " << RA << " degr\n";
    // cout << "GMST0 = " << GMST0 << " hours\n" << endl;
    // cout << "SIDTIME = " << SIDTIME << " hours\n" << endl;
    // cout << "Hour Angle = " << ha*degs << " degr\n";

    // delta = asin(sin(obliq) * sin(lambda));
    double alpha = atan2(cos(obliq) * sin(lambda), cos(lambda));
    //   Find the Equation of Time in minutes
    double equation = 1440 - (L - alpha) * degs * 4;

    ha = f0(latit,delta);

    // Conversion of angle to hours and minutes //
    daylen = degs*ha/7.5;
    if (daylen<0.0001) {daylen = 0.0;}
    // arctic winter     //

    riset = 12.0 - 12.0 * ha/pi - longit/15.0 + equation/60.0;
    settm = 12.0 + 12.0 * ha/pi - longit/15.0 + equation/60.0;
    noont = riset + 12.0 * ha/pi;
    altmax = 90.0 + delta*degs - latit;
    if (altmax > 90.0) altmax=180.0 - altmax; //to express as degrees from the N horizon

    noont-= 24*(noont>24);

    if (riset > 24.0) riset-= 24.0;
    if (settm > 24.0) settm-= 24.0;

    dec = delta * degs;
}

double sun::getRA() const
{
    return RA;
}

double sun::getSettm() const
{
    return settm;
}

double sun::getRiset() const
{
    return riset;
}

double sun::getNoont() const
{
    return noont;
}

double sun::getDaylen() const
{
    return daylen;
}

double sun::getDelta() const
{
    return delta;
}

double sun::getDegress() const
{
    return degress;
}

double sun::getAltmax() const
{
    return altmax;
}

double sun::getJd() const
{
    return jd;
}

double sun::getDec() const
{
    return dec;
}
