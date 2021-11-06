#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "soapH.h"
#include "onvifserver.h"

#define ONVIF_DISCOVERY_PORT 3702
#define ONVIF_SERVER_PORT    8000
char    g_manufacturer [33] = "APICAL";
char    g_device_model [33] = "IPC-19206";
char    g_device_name  [33] = "MyIPCamera";
char    g_device_fwver [33] = "v1.0.0.0";
char    g_device_sn    [33] = "2145983366589413";
char    g_device_hwid  [33] = "01-01-20";
char    g_device_ipaddr[16] = "192.168.0.178";
uint8_t g_device_mac   [6 ] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC };
int     g_onvif_server_port = ONVIF_SERVER_PORT;

static void* discovery_server_proc(void *param)
{
    struct soap soap_udp;
    struct ip_mreq mcast;

    soap_init1(&soap_udp, SOAP_IO_UDP|SOAP_XML_IGNORENS);
    soap_set_namespaces(&soap_udp,  namespaces);

    if (!soap_valid_socket(soap_bind(&soap_udp, NULL, ONVIF_DISCOVERY_PORT, 10))) {
        soap_print_fault(&soap_udp, stderr);
        goto done;
    }

    mcast.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
    mcast.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(soap_udp.master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0) {
        printf("setsockopt error! error code = %d, err string = %s\n", errno, strerror(errno));
        goto done;
    }

    for (;;) {
        if (soap_serve(&soap_udp)) {
            soap_print_fault(&soap_udp, stderr);
        }
        soap_destroy(&soap_udp);
        soap_end(&soap_udp);
    }

done:
    soap_done(&soap_udp);
    return 0;
}

static void onvif_server_main(void)
{
    struct soap onvif_soap;
    int    m, s;

    soap_init(&onvif_soap);
    soap_set_namespaces(&onvif_soap, namespaces);
    m = soap_bind(&onvif_soap, NULL, ONVIF_SERVER_PORT, 10);
    if (m < 0) {
        soap_print_fault(&onvif_soap, stderr);
        goto done;
    }

    for (;;) {
        s = soap_accept(&onvif_soap);
        if (s < 0) {
            soap_print_fault(&onvif_soap, stderr);
        }
        soap_serve(&onvif_soap);
        soap_destroy(&onvif_soap);
        soap_end(&onvif_soap);
    }

done:
    soap_done(&onvif_soap);
}

int main(int argc, char *argv[])
{
    pthread_t hthread = (pthread_t)NULL;
    pthread_create(&hthread, NULL, discovery_server_proc, NULL);
    onvif_server_main();
    pthread_join(hthread, NULL);
    return 0;
}

