#! /usr/bin/env python
import serial
import urllib2
import json
import ConfigParser
import argparse
import logging
import os
import time

def checksum(sentence):

    checksum = 0
    for s in sentence.strip():
        checksum ^= ord(s)

    return checksum


if __name__ == '__main__':

    logging.basicConfig(
        filename='/var/log/mood-light/{name}.log'.format( name = os.path.splitext(os.path.basename(__file__))[0] ),
        format='%(asctime)s %(levelname)s: %(message)s',
        level=logging.DEBUG
    )

    parser = argparse.ArgumentParser(
        description='Script to fetch Cosm feed and push to serial port'
    )
    
    parser.add_argument(
        '-c', '--config',
        help='config file name',
        type=argparse.FileType('r'),
        required=True,
        dest='config'
    )

    parser.add_argument(
        '-d', '--device',
        help='device name',
        type=str,
        required=True,
        dest='device'
    )

    args = parser.parse_args()
    config = ConfigParser.ConfigParser()
    config.readfp( args.config )

    API_KEY = config.get( 'cosm', 'API_KEY' )
    FEED = config.get( 'cosm', 'FEED_ID' )
    API_URL = 'http://api.cosm.com/v2/feeds/{feed}.json'.format(feed = FEED)

    request = urllib2.Request( API_URL )
    request.add_header( 'X-ApiKey', API_KEY )
    response = urllib2.urlopen( request )

    data = json.loads( response.read() )

    payload = [ 'COSM', FEED.__str__() ]
    for datastream in  data['datastreams']:
        payload.append( '{key},{value}'.format( key = datastream['id'], value = datastream['current_value'] ) )

    payload = ','.join( payload )

    ser = serial.Serial(
        port = args.device,
        baudrate = 9600,
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        bytesize = serial.EIGHTBITS
    )

    time.sleep(1)

    logging.debug( 'Sending to {device}: {data}'.format( device = args.device, data = payload ) )

    ser.write( '${data}*{checksum}\r\n'.format( data = payload, checksum = checksum( payload ) ) )
    ser.close()
