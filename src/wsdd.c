#include <stdlib.h>
#include <stdio.h>
#include "soapH.h"

extern char    g_device_model [32];
extern char    g_device_name  [32];
extern char    g_device_ipaddr[16];
extern uint8_t g_device_mac   [6 ];
extern int     g_onvif_server_port;

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

const char* soap_url(struct soap *soap, const char *s, const char *t)
{
    if (!t || (*t != '/' && *t != '?') || strlen(s) + strlen(t) >= sizeof(soap->msgbuf)) return s;
    strcpy(soap->msgbuf, s);
    strcat(soap->msgbuf, t);
    return soap->msgbuf;
}

int SOAP_FMAC6 soap_send___wsdd__ProbeMatches(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct wsdd__ProbeMatchesType *wsdd__ProbeMatches)
{   struct __wsdd__ProbeMatches soap_tmp___wsdd__ProbeMatches;
    if (soap_action == NULL)
        soap_action = "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches";
    soap_begin(soap);
    soap->encodingStyle = NULL;
    soap_tmp___wsdd__ProbeMatches.wsdd__ProbeMatches = wsdd__ProbeMatches;
    soap_serializeheader(soap);
    soap_serialize___wsdd__ProbeMatches(soap, &soap_tmp___wsdd__ProbeMatches);
    if (soap_begin_count(soap))
        return soap->error;
    if (soap->mode & SOAP_IO_LENGTH)
    {   if (soap_envelope_begin_out(soap)
         || soap_putheader(soap)
         || soap_body_begin_out(soap)
         || soap_put___wsdd__ProbeMatches(soap, &soap_tmp___wsdd__ProbeMatches, "-wsdd:ProbeMatches", NULL)
         || soap_body_end_out(soap)
         || soap_envelope_end_out(soap))
             return soap->error;
    }
    if (soap_end_count(soap))
        return soap->error;
    if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
     || soap_envelope_begin_out(soap)
     || soap_putheader(soap)
     || soap_body_begin_out(soap)
     || soap_put___wsdd__ProbeMatches(soap, &soap_tmp___wsdd__ProbeMatches, "-wsdd:ProbeMatches", NULL)
     || soap_body_end_out(soap)
     || soap_envelope_end_out(soap)
     || soap_end_send(soap))
        return soap_closesock(soap);
    return SOAP_OK;
}

int __wsdd__Probe(struct soap* soap, struct wsdd__ProbeType *wsdd__Probe)
{
    const char *scopes_message =
        "onvif://www.onvif.org/type/NetworkVideoTransmitter\r\n"
        "onvif://www.onvif.org/type/video_encoder\r\n"
        "onvif://www.onvif.org/type/video_encoder\r\n"
        "onvif://www.onvif.org/hardware/%s\r\n"
        "onvif://www.onvif.org/name/%s\r\n"
        "onvif://www.onvif.org/location/city/Shenzhen\r\n"
        "onvif://www.onvif.org/location/country/China\r\n";
    char str_tmp[1024];

    struct wsdd__ProbeMatchesType ProbeMatches = {0};
    ProbeMatches.__sizeProbeMatch   = 1;
    ProbeMatches.ProbeMatch         = (struct wsdd__ProbeMatchType*)soap_malloc(soap, sizeof(struct wsdd__ProbeMatchType));
    ProbeMatches.ProbeMatch->Scopes = (struct wsdd__ScopesType    *)soap_malloc(soap, sizeof(struct wsdd__ScopesType    ));
    ProbeMatches.ProbeMatch->MetadataVersion = 1;

    sprintf(str_tmp, scopes_message, g_device_model, g_device_name);
    ProbeMatches.ProbeMatch->Scopes->__item  = soap_strdup(soap, str_tmp);
    ProbeMatches.ProbeMatch->Scopes->MatchBy = NULL;

    sprintf(str_tmp, "http://%s:%d/onvif/device_service", g_device_ipaddr, g_onvif_server_port);
    ProbeMatches.ProbeMatch->XAddrs = soap_strdup(soap, str_tmp);
    ProbeMatches.ProbeMatch->Types  = (wsdd__Probe->Types && strlen(wsdd__Probe->Types)) ? wsdd__Probe->Types : "dn:NetworkVideoTransmitter tds:Device";

    soap_default_wsa__EndpointReferenceType(soap, &ProbeMatches.ProbeMatch->wsa__EndpointReference);
    sprintf(str_tmp, "urn:uuid:2419d68a-2dd2-21b2-a205-%02x%02x%02x%02x%02x%02x", g_device_mac[0], g_device_mac[1], g_device_mac[2], g_device_mac[3], g_device_mac[4], g_device_mac[5]);
    ProbeMatches.ProbeMatch->wsa__EndpointReference.Address = soap_strdup(soap, str_tmp);

    soap->header->wsa__To        = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
    soap->header->wsa__Action    = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
    soap->header->wsa__RelatesTo = (struct wsa__Relationship*)soap_malloc(soap, sizeof(struct wsa__Relationship));
    soap_default__wsa__RelatesTo(soap, soap->header->wsa__RelatesTo);
    soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;

    soap_send___wsdd__ProbeMatches(soap, "http://", NULL, &ProbeMatches);
    soap_dealloc(soap, ProbeMatches.ProbeMatch->wsa__EndpointReference.Address);
    soap_dealloc(soap, ProbeMatches.ProbeMatch->XAddrs);
    soap_dealloc(soap, ProbeMatches.ProbeMatch->Scopes->__item);
    soap_dealloc(soap, ProbeMatches.ProbeMatch->Scopes);
    soap_dealloc(soap, ProbeMatches.ProbeMatch);
    return SOAP_OK;
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
