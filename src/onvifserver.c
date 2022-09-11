#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "soapH.h"
#include "onvifserver.h"

#define ONVIF_DISCOVERY_PORT 3702
#define ONVIF_SERVER_PORT    8000

char g_manufacturer [33] = "APICAL";
char g_device_model [33] = "IPC-19206";
char g_device_name  [33] = "MyIPCamera";
char g_device_fwver [33] = "v1.0.0.0";
char g_device_sn    [33] = "2145983366589413";
char g_device_hwid  [33] = "01-01-20";
int  g_onvif_server_port = ONVIF_SERVER_PORT;

#define MAX_STREAM_NUM  3
int               g_stream_info_num = 1;
ONVIF_STREAM_INFO g_stream_info_list[MAX_STREAM_NUM] = {
    { 1920, 1080, 20, 1, 1500, 1, 1, 0, 8, 64 },
};

PFN_ONVIF_CALLBACK g_onvif_callback = NULL;
void              *g_onvif_cbctx    = NULL;

static int       s_exit_server = 0;
static pthread_t s_hthread_discovery  = (pthread_t)NULL;
static pthread_t s_hthread_servermain = (pthread_t)NULL;

static void def_onvif_callback(void *cbctx, int cmd, void *arg1, int len1, void *arg2, int len2)
{
    switch (cmd) {
    case ONVIF_CBCMD_GET_IP : strncpy(arg1, "192.168.0.100", len1); break;
    case ONVIF_CBCMD_GET_MAC: strncpy(arg1, "123456789ABC" , len1); break;
    }
}

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

    while (!s_exit_server) {
        if (soap_serve(&soap_udp)) {
            soap_print_fault(&soap_udp, stderr);
        }
        soap_destroy(&soap_udp);
        soap_end(&soap_udp);
    }

done:
    soap_done(&soap_udp);
    return NULL;
}

static void* onvif_server_main(void *param)
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

    while (!s_exit_server) {
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
    return NULL;
}

int onvif_server_start(char *manufacturer, char *dev_model, char *dev_name, char *dev_fwver, char *dev_sn, char *dev_hwid,
                       ONVIF_STREAM_INFO *stream_info_list, int stream_info_num, PFN_ONVIF_CALLBACK callback, void *cbctx)
{
    if (manufacturer) strncpy(g_manufacturer, manufacturer, sizeof(g_manufacturer));
    if (dev_model   ) strncpy(g_device_model, dev_model   , sizeof(g_device_model));
    if (dev_name    ) strncpy(g_device_name , dev_name    , sizeof(g_device_name ));
    if (dev_fwver   ) strncpy(g_device_fwver, dev_fwver   , sizeof(g_device_fwver));
    if (dev_sn      ) strncpy(g_device_sn   , dev_sn      , sizeof(g_device_sn   ));
    if (dev_hwid    ) strncpy(g_device_hwid , dev_hwid    , sizeof(g_device_hwid ));

    if (stream_info_list) {
        g_stream_info_num = stream_info_num < MAX_STREAM_NUM ? stream_info_num : MAX_STREAM_NUM;
        memcpy(g_stream_info_list, stream_info_list, sizeof(ONVIF_STREAM_INFO) * g_stream_info_num);
    }

    g_onvif_callback = callback ? callback : def_onvif_callback;
    g_onvif_cbctx    = cbctx;

    s_exit_server = 0;
    if (!s_hthread_discovery ) pthread_create(&s_hthread_discovery , NULL, discovery_server_proc, NULL);
    if (!s_hthread_servermain) pthread_create(&s_hthread_servermain, NULL, onvif_server_main    , NULL);
    return 0;
}

void onvif_server_stop(void)
{
    s_exit_server = 1;
    if (s_hthread_discovery ) { pthread_join(s_hthread_discovery , NULL); s_hthread_discovery = NULL; }
    if (s_hthread_servermain) { pthread_join(s_hthread_servermain, NULL); s_hthread_servermain= NULL; }
}

#ifdef _TEST_
int main(int argc, char *argv[])
{
    onvif_server_start(NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL);
    while (1) {
        char cmd[256];
        scanf("%256s", cmd);
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) break;
    }
    onvif_server_stop();
    return 0;
}
#endif

