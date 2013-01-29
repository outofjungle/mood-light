#include <string.h>
#include <SoftwareSerial.h>
#include "NMEASoftwareSerial.h"
#include "Feed.h"

#define FEED_ID 45856
#define FEED_NAME "COSM"
#define POS_FEED_NAME 0
#define POS_FEED_ID 1

#define POS_SW 3
#define POS_RED 5
#define POS_GREEN 7
#define POS_BLUE 9
#define POS_WHITE 11

#define RX 11
#define TX 12

#define LED_RED 3
#define LED_GREEN 5
#define LED_BLUE 6
#define LED_WHITE 9

NMEASoftwareSerial xbee( RX, TX ); // RX, TX
char feed_name[] = FEED_NAME;
unsigned int feed_id = FEED_ID;
Feed feed = { 0, 0, 0, 0, 0 };

void setup() {
    xbee.begin(9600);

    Serial.begin(9600);
    while (!Serial) ;
    
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_WHITE, OUTPUT);
}

void loop() {
    xbee.readline();
    Serial.println( xbee.string() );

    if (
        strcmp( xbee.at( POS_FEED_NAME ), feed_name ) && 
        atol( xbee.at( POS_FEED_ID ) ) == feed_id
    ) {
        feed.sw = atoi( xbee.at( POS_SW ) );
        feed.red = atoi( xbee.at( POS_RED ) );
        feed.green = atoi( xbee.at( POS_GREEN ) );
        feed.blue = atoi( xbee.at( POS_BLUE ) );
        feed.white = atoi( xbee.at( POS_WHITE ) );
        
        if ( feed.sw > 0 ) {
            switch_on( feed );
        } else {
            switch_off();
        }
    }

}

void switch_on( const Feed & feed ) {
    analogWrite( LED_RED, feed.red );
    analogWrite( LED_GREEN, feed.green );
    analogWrite( LED_BLUE, feed.blue );
    analogWrite( LED_WHITE, feed.white );
}

void switch_off() {
    analogWrite( LED_RED, 0 );
    analogWrite( LED_GREEN, 0 );
    analogWrite( LED_BLUE, 0 );
    analogWrite( LED_WHITE, 0 );
}

