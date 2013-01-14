#include "NMEASoftwareSerial.h"

NMEASoftwareSerial::NMEASoftwareSerial( uint8_t rx, uint8_t tx) : SoftwareSerial( rx, tx ) {
}

int
NMEASoftwareSerial::readline() {

    int chr;            // char read from the serial port
    int position = 0;   // position in the buffer where the chr is copied into
    int count = 0;      // index count of important delimiters 

    bool append = false;
    bool delimiter;

    // initalize
    *this->buffer = '\0';
    this->index[0] = -1;
    this->start = 0;
    this->end = 0;

    do {
        if (this->available()) {

            chr = this->read();
            delimiter = false;
            
            switch ( chr ) {
                case '$':
                    this->start = position + 1;
                    delimiter = true;
                    append = true;
                    break;
                case ',':
                    delimiter = true;
                    break;
                case '*':
                    this->end = position;
                    delimiter = true;
                    break;
                case '\r':
                case '\n':
                    if ( append ) {
                        delimiter = true;
                        append = false;
                    }
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
    this->itr_pos = 0;

    return position;
}

char *
NMEASoftwareSerial::string() {
    return this->buffer;
}

bool
NMEASoftwareSerial::substring( char * str, int strsize, int start, int end ) {

    *str = '\0';
    unsigned int length = end - start;

    if ( end > strlen( this->buffer ) && strsize < ( length + 1 ) ) {
        return false;
    }

    for ( int i = 0; i < length; i++ ) {
        *( str + i ) = this->buffer[ start + i ];
    }
    *( str + length ) = '\0';
    return true;
}

char * 
NMEASoftwareSerial::next() {

    *this->itr_value  = '\0';
    if ( itr_pos > ( sizeof( this->index ) - 1 ) ) {
        return this->itr_value;
    }
    
    if ( this->index[this->itr_pos + 1] != -1 ) {
        this->substring( this->itr_value, sizeof( this->itr_value ), this->index[this->itr_pos]  + 1, this->index[this->itr_pos + 1] );
        this->itr_pos++;
    }

    return this->itr_value;
}

void
NMEASoftwareSerial::reset() {
    this->itr_pos = 0;
}

int
NMEASoftwareSerial::checksum() {
    int checksum = 0;
    for ( int i = this->start; i < this->end; i++ ) {
        checksum = checksum ^ this->buffer[ i ];
    }
    return checksum;
}

int
NMEASoftwareSerial::nmea_checksum() {
    char checksum[4] = "";
    this->substring( checksum, sizeof( checksum ), this->end  + 1, strlen( this->buffer ) );
    return atoi( checksum );
}

bool
NMEASoftwareSerial::is_valid() {
    
    bool valid = true;
    
    if ( this->start >= this->end ) {
        valid = false;
    }
    
    if ( this->end >= strlen( this->buffer ) ) {
        valid = false;
    }
    
    if ( this->nmea_checksum() != this->checksum() ) {
        valid = false;
    }
    
    return valid;
}

