#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "soapStub.h"

#define ONVIF_LISTEN_PORT 3702

static void* discovery_server_proc(void *param)
{
    struct soap soap_udp;
    struct ip_mreq mcast;

    soap_init1(&soap_udp, SOAP_IO_UDP);
    soap_set_namespaces(&soap_udp,  namespaces);

    if (!soap_valid_socket(soap_bind(&soap_udp, NULL, ONVIF_LISTEN_PORT, 10))) {
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
    m = soap_bind(&onvif_soap, NULL, 82, 100);
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

