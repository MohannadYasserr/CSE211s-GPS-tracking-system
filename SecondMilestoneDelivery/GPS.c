#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  
#include <math.h> 
#include "GPIO.h"
#include "GPS.h"
#include "UART.h"
#include "LCD.h"
#include "SYSTICK.h"
#define PI 3.141592653589793238  // Value of pi
#define EARTH_RADIUS 6371000.0   // Mean radius of the Earth in meters
#define RS 0x01        // Bit mask for LCD RS pin
#define RW 0x02        // Bit mask for LCD RW pin
#define EN 0x04        // Bit mask for LCD EN pin
char GPS_logName[] = "$GPRMC,";  // GPS command string
                // Buffer to hold GPS data
char Valid[1];                 // Validity of GPS data
char N_or_S[1];                // North or South hemisphere
char E_or_W[1];                // East or West hemisphere
float currentLong, currentLat, speed; // Current longitude, latitude, and speed
char GPS[100]={0};
char lat[20] ={0}  ;           // Buffer to hold latitude data
char longi[20]={0}   ;            // Buffer to hold longitude data
char speedd[10]={0} ;           // Buffer to hold speed data
float longitude_vector[4] = { 0.0, 0.0, 0.0, 0.0 };
float latitude_vector[4] = { 0.0, 0.0, 0.0, 0.0 };

void GPS_read2() {

    char counter = 0;
    char recievedChar[1];
    char i = 0;
    char flag = 1;
    char c[1];
	
		UART2_interface_singleCharacter(GPS, 100);
	  GPS[sizeof(GPS) - 1] = '\0';

    // Loop until the GPS command is found in the incoming data
    do {
        UART2_interface_singleCharacter(c, 1);    // Read a character from the UART
        while (c[0] != GPS_logName[i]) { // Check if the character matches the current character in the GPS command string
            memset(c, 0, 1);              // Clear the character buffer
            UART2_interface_singleCharacter(c, 1);           // Read a new character from the UART
        }
        i++;
    } while (i != 7);

    // Loop until all necessary data has been extracted from the GPS string
    while (1) {
        if (flag) {
            UART2_interface_singleCharacter(recievedChar, 1); // Read a character from the UART
            if (recievedChar[0] == ',') { // Check if the character is a comma
                counter++;              // Increment the counter
            }
        }
        switch (counter) {
       case 1: UART2_interface_singleCharacter(Valid, 1); break; // Read the validity of the GPS data
        case 2: UART2_interface_multipleCharacters(lat, ',');  lat[sizeof(lat) - 1] = '\0'; counter++; flag = 0; break; // Read the latitude
        case 3: UART2_interface_singleCharacter(N_or_S, 1); flag = 1; break; // Read the hemisphere of the latitude
        case 4: UART2_interface_multipleCharacter(longi, ',');longi[sizeof(lat) - 1] = '\0'; counter++; flag = 0; break; // Read the longitude
        case 5: UART2_interface_singleCharacter(E_or_W, 1); flag = 1; break; // Read the hemisphere of the longitude
        case 6: UART2_interface_multipleCharacters(speedd, ','); counter++; flag = 0; break; // Read the speed
        
        }
        if (counter == 7) break; // If all necessary data has been extracted, break out of the loop
    }

    // Convert latitude and longitude from degrees and minutes to decimal degrees
    if (N_or_S[0] == 'N') {
        currentLat = atof(lat); // Convert the latitude to a floating-point value
    }
    else {
        currentLat = -atof(lat); // Convert the latitude to a floating-point value and negate it
    }
    if (E_or_W[0] == 'E') {
        currentLong = atof(longi); // Convert the longitude to a floating-point value
    }
    else {
        currentLong = -atof(longi); // Convert the longitude to a floating-point value and negate it
    }
}
double GPStoDeg(double val) {
    return (int)(val / 100) + (val - (int)(val / 100) * 100) / 60.0; // Convert the given GPS coordinate from degrees and minutes to decimal degrees
}

// Function to convert degrees to radians
float degrees_to_radians(float degrees) {
    return (float) degrees * PI / 180.0;
}

// Function to calculate distance between two GPS coordinates using Haversine formula
float haversine(float lat1, float lon1, float lat2, float lon2) {
    float dlat, dlon, a, c, d;

    // Convert GPS coordinates from degrees, minutes, seconds to decimal degrees
    lat1 = GPStoDeg(lat1);
    lon1 = GPStoDeg(lon1);
    lat2 = GPStoDeg(lat2);
    lon2 = GPStoDeg(lon2);

    // Convert latitude and longitude to radians
    dlat = degrees_to_radians(lat2 - lat1);
    dlon = degrees_to_radians(lon2 - lon1);

    // Calculate Haversine formula
    a = sin(dlat / 2.0f) * sin(dlat / 2.0f) + cos(degrees_to_radians(lat1)) * cos(degrees_to_radians(lat2)) * sin(dlon / 2.0f) * sin(dlon / 2);
    c = 2.0f * atan2(sqrt(a), sqrt(1.0f - a));
    d = EARTH_RADIUS * c;

    return d;
}
