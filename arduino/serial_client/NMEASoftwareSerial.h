#ifndef _NMEASOFWARESERIAL_H
#define _NMEASOFWARESERIAL_H
#include <SoftwareSerial.h>

class NMEASoftwareSerial : public SoftwareSerial {

    private:
        char buffer[256];
        int index[32];
        bool valid;
 
        int itr_pos;
        char itr_value[16];
        
    public:
        NMEASoftwareSerial( uint8_t rx, uint8_t tx) : 
            SoftwareSerial( rx, tx ) 
            {}
        int readline();
        char * string();
        char * next();
        void reset();
};

#endif
