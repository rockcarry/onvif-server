#include <stdlib.h>
#include <stdio.h>
#include "soapH.h"
#include "onvifserver.h"

int __trt__GetServiceCapabilities(struct soap* soap, struct _trt__GetServiceCapabilities *trt__GetServiceCapabilities, struct _trt__GetServiceCapabilitiesResponse *trt__GetServiceCapabilitiesResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoSources(struct soap* soap, struct _trt__GetVideoSources *trt__GetVideoSources, struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioSources(struct soap* soap, struct _trt__GetAudioSources *trt__GetAudioSources, struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioOutputs(struct soap* soap, struct _trt__GetAudioOutputs *trt__GetAudioOutputs, struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__CreateProfile(struct soap* soap, struct _trt__CreateProfile *trt__CreateProfile, struct _trt__CreateProfileResponse *trt__CreateProfileResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetProfile(struct soap* soap, struct _trt__GetProfile *trt__GetProfile, struct _trt__GetProfileResponse *trt__GetProfileResponse)
{
    struct _trt__GetProfiles trt__GetProfiles = {};
    struct _trt__GetProfilesResponse trt__GetProfilesResponse = {};
    int i;
    printf("%s\n", __func__);
    __trt__GetProfiles(soap, &trt__GetProfiles, &trt__GetProfilesResponse);
    for (i=0; i<trt__GetProfilesResponse.__sizeProfiles; i++) {
        if (strcmp(trt__GetProfilesResponse.Profiles[i].token, trt__GetProfile->ProfileToken) == 0) {
            trt__GetProfileResponse->Profile = trt__GetProfilesResponse.Profiles + i;
        }
    }
    return SOAP_OK;
}

int __trt__GetProfiles(struct soap* soap, struct _trt__GetProfiles *trt__GetProfiles, struct _trt__GetProfilesResponse *trt__GetProfilesResponse)
{
    printf("%s\n", __func__);
    trt__GetProfilesResponse->__sizeProfiles = 1;
    trt__GetProfilesResponse->Profiles = (struct tt__Profile*)soap_malloc(soap, sizeof(struct tt__Profile) * trt__GetProfilesResponse->__sizeProfiles);
    soap_default_tt__Profile(soap, &(trt__GetProfilesResponse->Profiles[0]));
    trt__GetProfilesResponse->Profiles[0].Name = "mainStream";
    trt__GetProfilesResponse->Profiles[0].token= "profile1";
    trt__GetProfilesResponse->Profiles[0].fixed= (enum xsd__boolean*)soap_malloc(soap, sizeof(enum xsd__boolean));
   *trt__GetProfilesResponse->Profiles[0].fixed= xsd__boolean__false_;

    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration = (struct tt__VideoSourceConfiguration*)soap_malloc(soap, sizeof(struct tt__VideoSourceConfiguration ));
    soap_default_tt__VideoSourceConfiguration(soap, trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration);
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Name        = "VideoSourceConfig";
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->token       ="VideoSourceToken";
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->SourceToken = "VideoSource_1";
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->UseCount    = 1;

    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds = (struct tt__IntRectangle*)soap_malloc(soap, sizeof(struct tt__IntRectangle));
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->x      = 0;
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->y      = 0;
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->width  = g_stream_info_list[0].video_width;
    trt__GetProfilesResponse->Profiles[0].VideoSourceConfiguration->Bounds->height = g_stream_info_list[0].video_height;

    trt__GetProfilesResponse->Profiles[0].AudioSourceConfiguration = (struct tt__AudioSourceConfiguration*)soap_malloc(soap, sizeof(struct tt__AudioSourceConfiguration ));
    soap_default_tt__AudioSourceConfiguration(soap, trt__GetProfilesResponse->Profiles[0].AudioSourceConfiguration);
    trt__GetProfilesResponse->Profiles[0].AudioSourceConfiguration->Name        = "AudioSourceConfig";
    trt__GetProfilesResponse->Profiles[0].AudioSourceConfiguration->token       = "AudioSourceToken";
    trt__GetProfilesResponse->Profiles[0].AudioSourceConfiguration->SourceToken = "AudioSource_1";
    trt__GetProfilesResponse->Profiles[0].AudioSourceConfiguration->UseCount    = 1;

    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration = (struct tt__VideoEncoderConfiguration*)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfiguration));
    soap_default_tt__VideoEncoderConfiguration(soap, trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration);
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Name       = "VideoEncoder_1";
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->token      = "VideoEncoder_Token";
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->UseCount   = 1;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Quality    = 3.0;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Encoding   = tt__VideoEncoding__H264; // g_stream_info_list[0].video_enctype ? tt__VideoEncoding__H265 : tt__VideoEncoding__H264;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Resolution = (struct tt__VideoResolution*)soap_malloc(soap, sizeof(struct tt__VideoResolution));
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Resolution->Width  = g_stream_info_list[0].video_width;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->Resolution->Height = g_stream_info_list[0].video_height;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl = (struct tt__VideoRateControl*)soap_malloc(soap, sizeof(struct tt__VideoRateControl));
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl->FrameRateLimit   = g_stream_info_list[0].video_frate;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl->EncodingInterval = g_stream_info_list[0].video_gop;
    trt__GetProfilesResponse->Profiles[0].VideoEncoderConfiguration->RateControl->BitrateLimit     = g_stream_info_list[0].video_bitrate;

    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration = (struct tt__AudioEncoderConfiguration*)soap_malloc(soap, sizeof(struct tt__AudioEncoderConfiguration));
    soap_default_tt__AudioEncoderConfiguration(soap, trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration);
    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration->Name       = "AudioEncoder_1";
    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration->token      = "AudioEncoder_Token";
    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration->UseCount   = 1;
    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration->Encoding   = g_stream_info_list[0].audio_enctype ? tt__AudioEncoding__AAC : tt__AudioEncoding__G711;
    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration->Bitrate    = g_stream_info_list[0].audio_bitrate;
    trt__GetProfilesResponse->Profiles[0].AudioEncoderConfiguration->SampleRate = g_stream_info_list[0].audio_samprate;
    return SOAP_OK;
}

int __trt__GetStreamUri(struct soap* soap, struct _trt__GetStreamUri *trt__GetStreamUri, struct _trt__GetStreamUriResponse *trt__GetStreamUriResponse)
{
    char str_tmp[1024];
    char str_ip [16];
    printf("%s\n", __func__); return SOAP_OK;
    trt__GetStreamUriResponse->MediaUri = (struct tt__MediaUri*)soap_malloc(soap, sizeof(struct tt__MediaUri));
    soap_default_tt__MediaUri(soap, trt__GetStreamUriResponse->MediaUri);
    g_onvif_callback(g_onvif_cbctx, ONVIF_CBCMD_GET_IP, str_ip, sizeof(str_ip), NULL, 0);
    snprintf(str_tmp, sizeof(str_tmp), "rtsp://%s/main", str_ip);
    trt__GetStreamUriResponse->MediaUri->Uri = soap_strdup(soap, str_tmp);
    trt__GetStreamUriResponse->MediaUri->InvalidAfterConnect = xsd__boolean__false_;
    trt__GetStreamUriResponse->MediaUri->InvalidAfterReboot  = xsd__boolean__false_;
    return SOAP_OK;
}

int __trt__AddVideoEncoderConfiguration(struct soap* soap, struct _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, struct _trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddVideoSourceConfiguration(struct soap* soap, struct _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, struct _trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddAudioEncoderConfiguration(struct soap* soap, struct _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, struct _trt__AddAudioEncoderConfigurationResponse *trt__AddAudioEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddAudioSourceConfiguration(struct soap* soap, struct _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, struct _trt__AddAudioSourceConfigurationResponse *trt__AddAudioSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddPTZConfiguration(struct soap* soap, struct _trt__AddPTZConfiguration *trt__AddPTZConfiguration, struct _trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddVideoAnalyticsConfiguration(struct soap* soap, struct _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, struct _trt__AddVideoAnalyticsConfigurationResponse *trt__AddVideoAnalyticsConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddMetadataConfiguration(struct soap* soap, struct _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, struct _trt__AddMetadataConfigurationResponse *trt__AddMetadataConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddAudioOutputConfiguration(struct soap* soap, struct _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, struct _trt__AddAudioOutputConfigurationResponse *trt__AddAudioOutputConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__AddAudioDecoderConfiguration(struct soap* soap, struct _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, struct _trt__AddAudioDecoderConfigurationResponse *trt__AddAudioDecoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveVideoEncoderConfiguration(struct soap* soap, struct _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, struct _trt__RemoveVideoEncoderConfigurationResponse *trt__RemoveVideoEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveVideoSourceConfiguration(struct soap* soap, struct _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, struct _trt__RemoveVideoSourceConfigurationResponse *trt__RemoveVideoSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveAudioEncoderConfiguration(struct soap* soap, struct _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, struct _trt__RemoveAudioEncoderConfigurationResponse *trt__RemoveAudioEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveAudioSourceConfiguration(struct soap* soap, struct _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, struct _trt__RemoveAudioSourceConfigurationResponse *trt__RemoveAudioSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemovePTZConfiguration(struct soap* soap, struct _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, struct _trt__RemovePTZConfigurationResponse *trt__RemovePTZConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveVideoAnalyticsConfiguration(struct soap* soap, struct _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, struct _trt__RemoveVideoAnalyticsConfigurationResponse *trt__RemoveVideoAnalyticsConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveMetadataConfiguration(struct soap* soap, struct _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, struct _trt__RemoveMetadataConfigurationResponse *trt__RemoveMetadataConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveAudioOutputConfiguration(struct soap* soap, struct _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, struct _trt__RemoveAudioOutputConfigurationResponse *trt__RemoveAudioOutputConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__RemoveAudioDecoderConfiguration(struct soap* soap, struct _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, struct _trt__RemoveAudioDecoderConfigurationResponse *trt__RemoveAudioDecoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__DeleteProfile(struct soap* soap, struct _trt__DeleteProfile *trt__DeleteProfile, struct _trt__DeleteProfileResponse *trt__DeleteProfileResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoSourceConfigurations(struct soap* soap, struct _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, struct _trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoEncoderConfigurations(struct soap* soap, struct _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, struct _trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioSourceConfigurations(struct soap* soap, struct _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, struct _trt__GetAudioSourceConfigurationsResponse *trt__GetAudioSourceConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioEncoderConfigurations(struct soap* soap, struct _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, struct _trt__GetAudioEncoderConfigurationsResponse *trt__GetAudioEncoderConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoAnalyticsConfigurations(struct soap* soap, struct _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, struct _trt__GetVideoAnalyticsConfigurationsResponse *trt__GetVideoAnalyticsConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetMetadataConfigurations(struct soap* soap, struct _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, struct _trt__GetMetadataConfigurationsResponse *trt__GetMetadataConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioOutputConfigurations(struct soap* soap, struct _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, struct _trt__GetAudioOutputConfigurationsResponse *trt__GetAudioOutputConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioDecoderConfigurations(struct soap* soap, struct _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, struct _trt__GetAudioDecoderConfigurationsResponse *trt__GetAudioDecoderConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoSourceConfiguration(struct soap* soap, struct _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, struct _trt__GetVideoSourceConfigurationResponse *trt__GetVideoSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoEncoderConfiguration(struct soap* soap, struct _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, struct _trt__GetVideoEncoderConfigurationResponse *trt__GetVideoEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioSourceConfiguration(struct soap* soap, struct _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, struct _trt__GetAudioSourceConfigurationResponse *trt__GetAudioSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioEncoderConfiguration(struct soap* soap, struct _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, struct _trt__GetAudioEncoderConfigurationResponse *trt__GetAudioEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoAnalyticsConfiguration(struct soap* soap, struct _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, struct _trt__GetVideoAnalyticsConfigurationResponse *trt__GetVideoAnalyticsConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetMetadataConfiguration(struct soap* soap, struct _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, struct _trt__GetMetadataConfigurationResponse *trt__GetMetadataConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioOutputConfiguration(struct soap* soap, struct _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, struct _trt__GetAudioOutputConfigurationResponse *trt__GetAudioOutputConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioDecoderConfiguration(struct soap* soap, struct _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, struct _trt__GetAudioDecoderConfigurationResponse *trt__GetAudioDecoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleVideoEncoderConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, struct _trt__GetCompatibleVideoEncoderConfigurationsResponse *trt__GetCompatibleVideoEncoderConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleVideoSourceConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, struct _trt__GetCompatibleVideoSourceConfigurationsResponse *trt__GetCompatibleVideoSourceConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleAudioEncoderConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, struct _trt__GetCompatibleAudioEncoderConfigurationsResponse *trt__GetCompatibleAudioEncoderConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleAudioSourceConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, struct _trt__GetCompatibleAudioSourceConfigurationsResponse *trt__GetCompatibleAudioSourceConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleVideoAnalyticsConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, struct _trt__GetCompatibleVideoAnalyticsConfigurationsResponse *trt__GetCompatibleVideoAnalyticsConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleMetadataConfigurations(struct soap* soap, struct _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, struct _trt__GetCompatibleMetadataConfigurationsResponse *trt__GetCompatibleMetadataConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleAudioOutputConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, struct _trt__GetCompatibleAudioOutputConfigurationsResponse *trt__GetCompatibleAudioOutputConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetCompatibleAudioDecoderConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, struct _trt__GetCompatibleAudioDecoderConfigurationsResponse *trt__GetCompatibleAudioDecoderConfigurationsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetVideoSourceConfiguration(struct soap* soap, struct _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, struct _trt__SetVideoSourceConfigurationResponse *trt__SetVideoSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetVideoEncoderConfiguration(struct soap* soap, struct _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, struct _trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetAudioSourceConfiguration(struct soap* soap, struct _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, struct _trt__SetAudioSourceConfigurationResponse *trt__SetAudioSourceConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetAudioEncoderConfiguration(struct soap* soap, struct _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, struct _trt__SetAudioEncoderConfigurationResponse *trt__SetAudioEncoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetVideoAnalyticsConfiguration(struct soap* soap, struct _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, struct _trt__SetVideoAnalyticsConfigurationResponse *trt__SetVideoAnalyticsConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetMetadataConfiguration(struct soap* soap, struct _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, struct _trt__SetMetadataConfigurationResponse *trt__SetMetadataConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetAudioOutputConfiguration(struct soap* soap, struct _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, struct _trt__SetAudioOutputConfigurationResponse *trt__SetAudioOutputConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetAudioDecoderConfiguration(struct soap* soap, struct _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, struct _trt__SetAudioDecoderConfigurationResponse *trt__SetAudioDecoderConfigurationResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoSourceConfigurationOptions(struct soap* soap, struct _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, struct _trt__GetVideoSourceConfigurationOptionsResponse *trt__GetVideoSourceConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoEncoderConfigurationOptions(struct soap* soap, struct _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, struct _trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioSourceConfigurationOptions(struct soap* soap, struct _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, struct _trt__GetAudioSourceConfigurationOptionsResponse *trt__GetAudioSourceConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioEncoderConfigurationOptions(struct soap* soap, struct _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, struct _trt__GetAudioEncoderConfigurationOptionsResponse *trt__GetAudioEncoderConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetMetadataConfigurationOptions(struct soap* soap, struct _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, struct _trt__GetMetadataConfigurationOptionsResponse *trt__GetMetadataConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioOutputConfigurationOptions(struct soap* soap, struct _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, struct _trt__GetAudioOutputConfigurationOptionsResponse *trt__GetAudioOutputConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetAudioDecoderConfigurationOptions(struct soap* soap, struct _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, struct _trt__GetAudioDecoderConfigurationOptionsResponse *trt__GetAudioDecoderConfigurationOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetGuaranteedNumberOfVideoEncoderInstances(struct soap* soap, struct _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, struct _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse *trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__StartMulticastStreaming(struct soap* soap, struct _trt__StartMulticastStreaming *trt__StartMulticastStreaming, struct _trt__StartMulticastStreamingResponse *trt__StartMulticastStreamingResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__StopMulticastStreaming(struct soap* soap, struct _trt__StopMulticastStreaming *trt__StopMulticastStreaming, struct _trt__StopMulticastStreamingResponse *trt__StopMulticastStreamingResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetSynchronizationPoint(struct soap* soap, struct _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, struct _trt__SetSynchronizationPointResponse *trt__SetSynchronizationPointResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetSnapshotUri(struct soap* soap, struct _trt__GetSnapshotUri *trt__GetSnapshotUri, struct _trt__GetSnapshotUriResponse *trt__GetSnapshotUriResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetVideoSourceModes(struct soap* soap, struct _trt__GetVideoSourceModes *trt__GetVideoSourceModes, struct _trt__GetVideoSourceModesResponse *trt__GetVideoSourceModesResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetVideoSourceMode(struct soap* soap, struct _trt__SetVideoSourceMode *trt__SetVideoSourceMode, struct _trt__SetVideoSourceModeResponse *trt__SetVideoSourceModeResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetOSDs(struct soap* soap, struct _trt__GetOSDs *trt__GetOSDs, struct _trt__GetOSDsResponse *trt__GetOSDsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetOSD(struct soap* soap, struct _trt__GetOSD *trt__GetOSD, struct _trt__GetOSDResponse *trt__GetOSDResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__GetOSDOptions(struct soap* soap, struct _trt__GetOSDOptions *trt__GetOSDOptions, struct _trt__GetOSDOptionsResponse *trt__GetOSDOptionsResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__SetOSD(struct soap* soap, struct _trt__SetOSD *trt__SetOSD, struct _trt__SetOSDResponse *trt__SetOSDResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__CreateOSD(struct soap* soap, struct _trt__CreateOSD *trt__CreateOSD, struct _trt__CreateOSDResponse *trt__CreateOSDResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}

int __trt__DeleteOSD(struct soap* soap, struct _trt__DeleteOSD *trt__DeleteOSD, struct _trt__DeleteOSDResponse *trt__DeleteOSDResponse)
{
    printf("%s\n", __func__); return SOAP_OK;
}
