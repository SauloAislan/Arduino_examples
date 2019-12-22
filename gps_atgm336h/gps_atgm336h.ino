/******************************************************************************
 *
 *
 * Copyright 2019 Saulo Aislan - https://github.com/SauloAislan
 *
 * Description: Software to get Longitude, Latitude, Altitude, Speed and Sats using GPS ATGM336H and Arduino Uno [10(RX) 11(TX)],
 * datasheet https://www.electrodragon.com/w/images/8/83/ATGM336H-5N.pdf. More info: https://www.electrodragon.com/w/Category:GPS
 *
 * 
 *******************************************************************************/
 
 
 // Necessary libraries
#include "NMEAGPS.h"
#include <Wire.h>
#include <SoftwareSerial.h>

//---------------------------GPS------------------------------------------------------
#define GPSBAUD 9600 // baud rate of our GPS module. Change for your GPS module if different
NMEAGPS gps;  // Create an instance of the GPS object
void getgps(NMEAGPS &gps);   // This is where you declare prototypes for the functions that will be
                            // using the GPS library.

SoftwareSerial ss(10, 11);


void setup()
{

 ss.begin(GPSBAUD); // setup sketch for data output speed of GPS module
 Serial.begin(9600);
 
}


void loop()
{
GPS_LOC ( );
}

int GPS_LOC( )
{
 if (gps.available(ss))
   getgps(gps);  // then grab the data.
}

void getgps( NMEAGPS &gps )   // The getgps function will get and print the values we want.
{
 float latitude, longitude;   // Define the variables that will be used
 
 gps_fix fix = gps.read();
 
 Serial.println("\n   Low accuracy  \n");
 
 Serial.print("Latitude : ");
 if (fix.valid.location) {
   Serial.println( fix.latitude(), 6 );
 }  
 
 Serial.print("Longitude: ");
 if (fix.valid.location) {
   Serial.println( fix.longitude(), 6 );
 }

 Serial.println("\n   High accuracy  \n");

 Serial.print("Latitude : ");
 if (fix.valid.location) {
   Serial.println( fix.latitudeL());
 }  
 
 Serial.print("Longitude: ");
 if (fix.valid.location) {
   Serial.println( fix.longitudeL());
 }

 Serial.println("\n");
 Serial.print("Altitude : ");
 if (fix.valid.altitude) {
   Serial.print( fix.altitude(), 2 );
   Serial.println("m");
 }
 
 Serial.print("Speed: ");
 if (fix.valid.speed) {
   Serial.print(fix.speed_kph(), 2);
   Serial.println("K/h");
 }

 Serial.print("Sats: ");
 if (fix.valid.satellites)
   Serial.println(fix.satellites);
}
