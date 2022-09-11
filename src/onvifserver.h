#ifndef __ONVIFSERVER_H__
#define __ONVIFSERVER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int32_t video_width;
    int32_t video_height;
    int32_t video_frate;
    int32_t video_gop;     // in sec
    int32_t video_bitrate; // in kbps
    int32_t video_enctype; // 0 - h264, 1 - h265
    int32_t audio_channels;
    int32_t audio_enctype; // 0 - g711, 1 - aac
    int32_t audio_samprate;// in khz
    int32_t audio_bitrate; // in kbps
} ONVIF_STREAM_INFO;

enum {
    ONVIF_CBCMD_GET_IP  = 1, // arg1 is char* string, string format: xxx.xxx.xxx.xxx
    ONVIF_CBCMD_GET_MAC = 2, // arg1 is char* string, string format: AA:BB:CC:DD:EE:FF
};

typedef void (*PFN_ONVIF_CALLBACK)(void *cbctx, int cmd, void *arg1, int len1, void *arg2, int len2);

extern char g_manufacturer[];
extern char g_device_model[];
extern char g_device_name [];
extern char g_device_fwver[];
extern char g_device_sn   [];
extern char g_device_hwid [];
extern int  g_onvif_server_port;

extern int                g_stream_info_num;
extern ONVIF_STREAM_INFO  g_stream_info_list[];

extern PFN_ONVIF_CALLBACK g_onvif_callback;
extern void              *g_onvif_cbctx;

int  onvif_server_start(char *manufacturer, char *dev_model, char *dev_name, char *dev_fwver, char *dev_sn, char *dev_hwid,
                        ONVIF_STREAM_INFO *stream_list, int stream_num, PFN_ONVIF_CALLBACK callback, void *cbctx);
void onvif_server_stop (void);

#ifdef __cplusplus
}
#endif

#endif

