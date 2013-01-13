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



    Serial.println("--");

    do {
        field = xbee.next();
        Serial.println( field );
    } while ( strlen( field ) > 0 );


}

