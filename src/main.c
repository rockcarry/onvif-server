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

int SOAP_ENV__Fault(struct soap* soap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __wsdd__Hello(struct soap* soap, struct wsdd__HelloType *wsdd__Hello)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __wsdd__Bye(struct soap* soap, struct wsdd__ByeType *wsdd__Bye)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __wsdd__Probe(struct soap* soap, struct wsdd__ProbeType *wsdd__Probe)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __wsdd__ProbeMatches(struct soap* soap, struct wsdd__ProbeMatchesType *wsdd__ProbeMatches)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __wsdd__Resolve(struct soap* soap, struct wsdd__ResolveType *wsdd__Resolve)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __wsdd__ResolveMatches(struct soap* soap, struct wsdd__ResolveMatchesType *wsdd__ResolveMatches)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __tdn__Hello(struct soap* soap, struct wsdd__HelloType tdn__Hello, struct wsdd__ResolveType *tdn__HelloResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __tdn__Bye(struct soap* soap, struct wsdd__ByeType tdn__Bye, struct wsdd__ResolveType *tdn__ByeResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __tdn__Probe(struct soap* soap, struct wsdd__ProbeType tdn__Probe, struct wsdd__ProbeMatchesType *tdn__ProbeResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}
