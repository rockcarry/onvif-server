#!/bin/sh

set -e

./wsdl2h -o onvif.h -c -s -t typemap.dat \
http://www.onvif.org/onvif/ver10/network/wsdl/remotediscovery.wsdl \
http://www.onvif.org/onvif/ver10/device/wsdl/devicemgmt.wsdl \
http://www.onvif.org/onvif/ver10/media/wsdl/media.wsdl

./soapcpp2 -2 -c -w -x -S -L -f100 -Iimport -Icustom onvif.h
mkdir -p $PWD/../src/
rm -f $PWD/onvif.h $PWD/src/soapC_*.c
mv wsdd.nsmap $PWD/../src/namespace.c
mv *.h *.c $PWD/../src/
rm -f *.nsmap
