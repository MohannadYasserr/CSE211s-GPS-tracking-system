#include <stdio.h>
#include <math.h>
#include "io.h"

#define EARTH_RADIUS 6371000 // Earth radius in meters

// Function to convert degrees to radians
double toRadians(double degree) {
    return degree * PI / 180.0;
}

// Function to calculate distance between two points using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitude and longitude from degrees to radians
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    // Haversine formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Distance calculation
    double distance = EARTH_RADIUS * c;
    return distance;
}

int main() {
    // Coordinates of two points (example)
    double lat1 = 30.10410; // Latitude of point 1
    double lon1 = 31.60165; // Longitude of point 1
    double lat2 = 30.10487; // Latitude of point 2
    double lon2 = 31.60235; // Longitude of point 2

    // Calculate distance
    double distance = calculateDistance(lat1, lon1, lat2, lon2);


    // Output the distance
    printf("Distance between the two points is: %.2f meters\n", distance);

    return 0;
}