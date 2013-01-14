#include <string.h>
#include <SoftwareSerial.h>
#include "NMEASoftwareSerial.h"

NMEASoftwareSerial xbee(11, 12); // RX, TX

char match[] = "$COSM";
    int * index;
    
void setup() {
    xbee.begin(9600);
    Serial.begin(9600);
}

void loop() {

    char * field;
    xbee.readline();

    Serial.println( xbee.string() );

    int i = 0;
    do {
        field = xbee.next();
        Serial.print( i++ );
        Serial.print( " : " );
        Serial.println( field );
    } while ( strlen( field ) > 0 );

    Serial.print( "Valid : " );
    Serial.println( xbee.is_valid() );

}

