#ifndef _NMEASOFWARESERIAL_H
#define _NMEASOFWARESERIAL_H
#include <SoftwareSerial.h>

#define MAX_BUFFER_LENGTH 256
#define MAX_VALUE_LENGTH 64
#define MAX_INDEX_SIZE 32
#define CHECKSUM_LENGTH 3

class NMEASoftwareSerial : public SoftwareSerial {

    private:
        char buffer[ MAX_BUFFER_LENGTH ];
        int index[ MAX_INDEX_SIZE ];
        char value[ MAX_VALUE_LENGTH ];
        unsigned int start;
        unsigned int end;
        unsigned int index_size;
        bool truncated;

        // for iterator
        unsigned int itr_pos;
        char itr_value[ MAX_VALUE_LENGTH ];
        
        int checksum();
        int nmea_checksum();
        bool substring( char *, int, int, int );
        bool at( int, char *, int );
        
    public:
        NMEASoftwareSerial( uint8_t, uint8_t);
        int readline();
        char * string();
        char * next();
        void reset();
        char * at( int );
        bool is_valid();
        bool is_truncated();
        int size();
};

#endif
