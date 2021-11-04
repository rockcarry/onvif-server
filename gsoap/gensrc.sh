#!/bin/sh

set -e

./wsdl2h -o onvif.h -c -s -t typemap.dat \
http://www.onvif.org/onvif/ver10/network/wsdl/remotediscovery.wsdl \
http://www.onvif.org/onvif/ver10/media/wsdl/media.wsdl \
http://www.onvif.org/onvif/ver20/ptz/wsdl/ptz.wsdl

./soapcpp2 -2 -c -w -x -S -L -f100 -Iimport -Icustom onvif.h
rm $PWD/onvif.h *.nsmap
mkdir -p $PWD/../src/
mv *.h *.c $PWD/../src/

