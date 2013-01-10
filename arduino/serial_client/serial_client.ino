#include <string.h>
#include <SoftwareSerial.h>

SoftwareSerial xbee(11, 12); // RX, TX

int chr = -1;
char buffer[256] = "";
char match[] = "$COSM";
unsigned int index[64];

int buffer_count = 0;
int match_count=0;
int index_count = 0;

void setup() {
    xbee.begin(9600);
    Serial.begin(9600);
}

void loop() {
     
    chr = xbee.read();

    if ( chr == -1 ) {
        delay(100);
    } else {
        buffer[buffer_count]=chr;
        buffer_count++;
        
        //Serial.write(chr);

        if ( chr == 13 ){
            
            buffer[buffer_count] = '\0';
            
            index_count=0;
            match_count=0;

            int x = 0;
            while ( buffer[x] != match[0] ) {
                x++;
            }

            for ( int i=0; i<strlen(match); i++ ){
                if (buffer[i+x]==match[i]){
                    match_count++;
                }
            }

            if( match_count == 5 ){
                for (int i=0; i<256; i++){
                    if (buffer[i]==','){
                        index[index_count]=i;
                        index_count++;
                    }
                    if (buffer[i]=='*'){
                        index[index_count]=i;
                        index_count++;
                    }
                    if (buffer[i]=='\r'){
                        index[index_count]=i;
                    }
                }

                for (int i=0; i<index_count; i++){

                    Serial.print("Index: ");
                    Serial.print(i);
                    Serial.print(", ");
                    
                    for (int j=index[i]; j<(index[i+1]-1); j++){
                        Serial.write(buffer[j+1]); 
                    }

                    Serial.println("");
                }
            }
            buffer_count=0;
        }
    }
}

