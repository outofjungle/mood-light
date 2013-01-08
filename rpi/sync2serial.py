#! /usr/bin/env python
import serial, urllib2, json, ConfigParser, argparse

if __name__ == '__main__':

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

    args = parser.parse_args()
    config = ConfigParser.ConfigParser()
    config.readfp( args.config )

    API_KEY = config.get('cosm', 'API_KEY')
    FEED = config.get('cosm', 'FEED_ID')
    API_URL = 'http://api.cosm.com/v2/feeds/{feed}.json' .format(feed = FEED)

    request = urllib2.Request( API_URL )
    request.add_header( 'X-ApiKey', API_KEY )
    response = urllib2.urlopen( request )

    data = json.loads( response.read() )

    payload = [ '$COSM', FEED.__str__() ]
    for datastream in  data['datastreams']:
        payload.append( '{key},{value}'.format( key = datastream['id'], value = datastream['current_value'] ) )

    payload = ','.join( payload )

    print payload
