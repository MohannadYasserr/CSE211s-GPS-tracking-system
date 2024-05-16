
#include <stdbool.h>  
#include <math.h> 


#ifndef GPS_INTERFACE
#define GPS_INTERFACE
void GPS_read(void);
void GPS_format(void);
void GPS_read2(void);
double GPStoDeg(double val);
float degrees_to_radians(float degrees);
float haversine(float lat1, float lon1, float lat2, float lon2);

extern char GPS_logName[];  // Declaration of GPS command string
extern char GPS[]   ;     // Declaration of buffer to hold GPS data
extern char Valid[];        // Declaration of validity of GPS data
extern char N_or_S[];       // Declaration of North or South hemisphere
extern char E_or_W[];       // Declaration of East or West hemisphere
extern float currentLong, currentLat, speed; // Declaration of current longitude, latitude, and speed
extern char lat[];          // Declaration of buffer to hold latitude data
extern char longi[];        // Declaration of buffer to hold longitude data
extern char speedd[];       // Declaration of buffer to hold speed data
extern float longitude_vector[]; // Declaration of longitude vector
extern float latitude_vector[];  // Declaration of latitude vector
#endif 