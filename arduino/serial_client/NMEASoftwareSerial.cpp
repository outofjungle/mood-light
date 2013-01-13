#include "NMEASoftwareSerial.h"

int NMEASoftwareSerial::readline() {

    int chr;            // char read from the serial port
    int position = 0;   // position in the buffer where the chr is copied into
    int count = 0;      // index count of important delimiters 

    bool append = false;
    bool delimiter;

    // initalize buffer and index to null
    *( this->buffer ) = '\0';
    this->index[0] = -1;
    this->valid = false;

    do {
        if (this->available()) {

            chr = this->read();
            delimiter = false;
            
            switch ( chr ) {
                case '$':
                    append = true;
                    delimiter = true;
                    break;
                case '\r':
                case '\n':
                    if ( append ) {
                        append = false;
                        delimiter = true;
                    }
                    break;
                case ',':
                    delimiter = true;
                    break;
                case '*':
                    delimiter = true;
                    break;    
            }

            if ( delimiter ) {
                this->index[count] = position;
                count++;
            }

            if ( append ) {
                *( this->buffer + position ) = (char) chr;
                position++;
            }
        }
    } while (
        chr != '\n'
        && position < sizeof( this->buffer )
    );
    
    *( this->buffer + position ) = '\0';
    this->index[count] = -1;
    this->valid = true;
    this->itr_pos = 0;
    
    return position;
}

char * NMEASoftwareSerial::string() {
    return this->buffer;
}

char * NMEASoftwareSerial::next() {
    
    int length = 0;
    
    if ( itr_pos > ( sizeof( this->index ) - 1 ) ) {
        return this->itr_value;
    }
    
    if ( this->index[this->itr_pos + 1] != -1 ) {
        
        length = this->index[this->itr_pos + 1] - this->index[this->itr_pos];
        for ( int i = 0; i < length; i++ ) {
            *( this->itr_value + i ) = *( this->buffer + (this->index[this->itr_pos] + i) );
        }
        this->itr_pos++;
    }
    
    *( this->itr_value + length ) = '\0';

    return this->itr_value;
}

void NMEASoftwareSerial::reset() {
    this->itr_pos = 0;
}
