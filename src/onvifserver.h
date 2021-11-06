#ifndef __ONVIFSERVER_H__
#define __ONVIFSERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

extern char    g_manufacturer [];
extern char    g_device_model [];
extern char    g_device_name  [];
extern char    g_device_fwver [];
extern char    g_device_sn    [];
extern char    g_device_hwid  [];
extern char    g_device_ipaddr[];
extern uint8_t g_device_mac   [];
extern int     g_onvif_server_port;

#ifdef __cplusplus
}
#endif

#endif

