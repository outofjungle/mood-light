#ifndef _NMEASOFWARESERIAL_H
#define _NMEASOFWARESERIAL_H
#include <SoftwareSerial.h>

class NMEASoftwareSerial : public SoftwareSerial {

    private:
        char buffer[256];
        int index[32];
        int start;
        int end;
        int itr_pos;
        char itr_value[16];
        
        int checksum();
        int nmea_checksum();
        bool substring( char *, int, int, int );
        
    public:
        NMEASoftwareSerial( uint8_t, uint8_t);
        int readline();
        char * string();
        char * next();
        void reset();
        bool is_valid();
};

#endif
