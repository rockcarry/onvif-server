#include <stdlib.h>
#include <stdio.h>
#include "soapH.h"
#include "soapStub.h"
#include "onvifserver.h"

int __tds__GetScopes(struct soap* soap, struct _tds__GetScopes *tds__GetScopes, struct _tds__GetScopesResponse *tds__GetScopesResponse)
{
    const char *scopes_message[] = {
        "onvif://www.onvif.org/type/NetworkVideoTransmitter",
        "onvif://www.onvif.org/type/video_encoder",
        "onvif://www.onvif.org/hardware/%s",
        "onvif://www.onvif.org/name/%s",
        "onvif://www.onvif.org/location/city/Shenzhen",
        "onvif://www.onvif.org/location/country/China",
    };
    char str_tmp[1024];
    printf("%s\n", __func__);
    tds__GetScopesResponse->__sizeScopes = 6;
    tds__GetScopesResponse->Scopes = soap_new_tt__Scope(soap, 6);

    tds__GetScopesResponse->Scopes[0].ScopeDef = tt__ScopeDefinition__Fixed;
    tds__GetScopesResponse->Scopes[0].ScopeItem = soap_strdup(soap, scopes_message[0]);

    tds__GetScopesResponse->Scopes[1].ScopeDef = tt__ScopeDefinition__Fixed;
    tds__GetScopesResponse->Scopes[1].ScopeItem = soap_strdup(soap, scopes_message[1]);

    snprintf(str_tmp, sizeof(str_tmp), scopes_message[2], g_device_model);
    tds__GetScopesResponse->Scopes[2].ScopeDef = tt__ScopeDefinition__Fixed;
    tds__GetScopesResponse->Scopes[2].ScopeItem = soap_strdup(soap, str_tmp);

    snprintf(str_tmp, sizeof(str_tmp), scopes_message[3], g_device_name);
    tds__GetScopesResponse->Scopes[3].ScopeDef = tt__ScopeDefinition__Fixed;
    tds__GetScopesResponse->Scopes[3].ScopeItem = soap_strdup(soap, str_tmp);

    tds__GetScopesResponse->Scopes[4].ScopeDef = tt__ScopeDefinition__Fixed;
    tds__GetScopesResponse->Scopes[4].ScopeItem = soap_strdup(soap, scopes_message[4]);

    tds__GetScopesResponse->Scopes[5].ScopeDef = tt__ScopeDefinition__Fixed;
    tds__GetScopesResponse->Scopes[5].ScopeItem = soap_strdup(soap, scopes_message[5]);

    return SOAP_OK;
}

int __tds__GetDeviceInformation(struct soap* soap, struct _tds__GetDeviceInformation *tds__GetDeviceInformation, struct _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse)
{
    printf("%s\n", __func__);
    tds__GetDeviceInformationResponse->Manufacturer    = soap_strdup(soap, g_manufacturer);
    tds__GetDeviceInformationResponse->Model           = soap_strdup(soap, g_device_model);
    tds__GetDeviceInformationResponse->FirmwareVersion = soap_strdup(soap, g_device_fwver);
    tds__GetDeviceInformationResponse->SerialNumber    = soap_strdup(soap, g_device_sn   );
    tds__GetDeviceInformationResponse->HardwareId      = soap_strdup(soap, g_device_hwid );
    return SOAP_OK;
}

int __tds__GetCapabilities(struct soap* soap, struct _tds__GetCapabilities *tds__GetCapabilities, struct _tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse)
{
    char str_tmp[1024];
    char str_ip [16];

    printf("%s\n", __func__);
    g_onvif_callback(g_onvif_cbctx, ONVIF_CBCMD_GET_IP, str_ip, sizeof(str_ip), NULL, 0);

    tds__GetCapabilitiesResponse->Capabilities = (struct tt__Capabilities*)soap_malloc(soap, sizeof(struct tt__Capabilities));
    soap_default_tt__Capabilities(soap, tds__GetCapabilitiesResponse->Capabilities);

    tds__GetCapabilitiesResponse->Capabilities->Device = (struct tt__DeviceCapabilities*)soap_malloc(soap, sizeof(struct tt__DeviceCapabilities));
    soap_default_tt__DeviceCapabilities(soap, tds__GetCapabilitiesResponse->Capabilities->Device);
    snprintf(str_tmp, sizeof(str_tmp), "http://%s:%d/onvif/device_service", str_ip, g_onvif_server_port);
    tds__GetCapabilitiesResponse->Capabilities->Device->XAddr = soap_strdup(soap, str_tmp);

    tds__GetCapabilitiesResponse->Capabilities->Media = (struct tt__MediaCapabilities*)soap_malloc(soap, sizeof(struct tt__MediaCapabilities));
    soap_default_tt__MediaCapabilities(soap, tds__GetCapabilitiesResponse->Capabilities->Media);
    snprintf(str_tmp, sizeof(str_tmp), "http://%s:%d/onvif/media", str_ip, g_onvif_server_port);
    tds__GetCapabilitiesResponse->Capabilities->Media->XAddr = soap_strdup(soap, str_tmp);

    tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities = (struct tt__RealTimeStreamingCapabilities*)soap_malloc(soap, sizeof(struct tt__RealTimeStreamingCapabilities));
    soap_default_tt__RealTimeStreamingCapabilities(soap, tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities);

    tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast  = (enum xsd__boolean*)soap_malloc(soap, sizeof(enum xsd__boolean));
    tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP = (enum xsd__boolean*)soap_malloc(soap, sizeof(enum xsd__boolean));
    tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP = (enum xsd__boolean*)soap_malloc(soap, sizeof(enum xsd__boolean));
   *tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast  = xsd__boolean__false_;
   *tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP = xsd__boolean__true_;
   *tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP = xsd__boolean__true_;

    return SOAP_OK;
}

int __tds__GetServices(struct soap* soap, struct _tds__GetServices *tds__GetServices, struct _tds__GetServicesResponse *tds__GetServicesResponse)
{
    char str_tmp[1024];
    char str_ip [16];

    printf("%s\n", __func__);
    g_onvif_callback(g_onvif_cbctx, ONVIF_CBCMD_GET_IP, str_ip, sizeof(str_ip), NULL, 0);

    tds__GetServicesResponse->__sizeService = 2;
    tds__GetServicesResponse->Service       = (struct tds__Service*)soap_malloc(soap, sizeof(struct tds__Service) * tds__GetServicesResponse->__sizeService);
    soap_default_tds__Service(soap, tds__GetServicesResponse->Service + 0);
    soap_default_tds__Service(soap, tds__GetServicesResponse->Service + 1);

    snprintf(str_tmp, sizeof(str_tmp), "http://%s:%d/onvif/device_service", str_ip, g_onvif_server_port);
    tds__GetServicesResponse->Service[0].XAddr     = soap_strdup(soap, str_tmp);
    tds__GetServicesResponse->Service[0].Namespace = "http://www.onvif.org/ver10/device/wsdl";
    tds__GetServicesResponse->Service[0].Version   = (struct tt__OnvifVersion*)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[0].Version->Major = 2;
    tds__GetServicesResponse->Service[0].Version->Minor = 40;

    snprintf(str_tmp, sizeof(str_tmp), "http://%s:%d/onvif/media", str_ip, g_onvif_server_port);
    tds__GetServicesResponse->Service[1].XAddr     = soap_strdup(soap, str_tmp);
    tds__GetServicesResponse->Service[1].Namespace = "http://www.onvif.org/ver10/media/wsdl";
    tds__GetServicesResponse->Service[1].Version   = (struct tt__OnvifVersion*)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 2;
    tds__GetServicesResponse->Service[1].Version->Minor = 40;

    return SOAP_OK;
}

int __tds__GetServiceCapabilities(struct soap* soap, struct _tds__GetServiceCapabilities *tds__GetServiceCapabilities, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetSystemDateAndTime(struct soap* soap, struct _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, struct _tds__SetSystemDateAndTimeResponse *tds__SetSystemDateAndTimeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetSystemDateAndTime(struct soap* soap, struct _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, struct _tds__GetSystemDateAndTimeResponse *tds__GetSystemDateAndTimeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetSystemFactoryDefault(struct soap* soap, struct _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, struct _tds__SetSystemFactoryDefaultResponse *tds__SetSystemFactoryDefaultResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__UpgradeSystemFirmware(struct soap* soap, struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SystemReboot(struct soap* soap, struct _tds__SystemReboot *tds__SystemReboot, struct _tds__SystemRebootResponse *tds__SystemRebootResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__RestoreSystem(struct soap* soap, struct _tds__RestoreSystem *tds__RestoreSystem, struct _tds__RestoreSystemResponse *tds__RestoreSystemResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetSystemBackup(struct soap* soap, struct _tds__GetSystemBackup *tds__GetSystemBackup, struct _tds__GetSystemBackupResponse *tds__GetSystemBackupResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetSystemLog(struct soap* soap, struct _tds__GetSystemLog *tds__GetSystemLog, struct _tds__GetSystemLogResponse *tds__GetSystemLogResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetSystemSupportInformation(struct soap* soap, struct _tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, struct _tds__GetSystemSupportInformationResponse *tds__GetSystemSupportInformationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetScopes(struct soap* soap, struct _tds__SetScopes *tds__SetScopes, struct _tds__SetScopesResponse *tds__SetScopesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__AddScopes(struct soap* soap, struct _tds__AddScopes *tds__AddScopes, struct _tds__AddScopesResponse *tds__AddScopesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__RemoveScopes(struct soap* soap, struct _tds__RemoveScopes *tds__RemoveScopes, struct _tds__RemoveScopesResponse *tds__RemoveScopesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDiscoveryMode(struct soap* soap, struct _tds__GetDiscoveryMode *tds__GetDiscoveryMode, struct _tds__GetDiscoveryModeResponse *tds__GetDiscoveryModeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetDiscoveryMode(struct soap* soap, struct _tds__SetDiscoveryMode *tds__SetDiscoveryMode, struct _tds__SetDiscoveryModeResponse *tds__SetDiscoveryModeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetRemoteDiscoveryMode(struct soap* soap, struct _tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, struct _tds__GetRemoteDiscoveryModeResponse *tds__GetRemoteDiscoveryModeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetRemoteDiscoveryMode(struct soap* soap, struct _tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, struct _tds__SetRemoteDiscoveryModeResponse *tds__SetRemoteDiscoveryModeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDPAddresses(struct soap* soap, struct _tds__GetDPAddresses *tds__GetDPAddresses, struct _tds__GetDPAddressesResponse *tds__GetDPAddressesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetEndpointReference(struct soap* soap, struct _tds__GetEndpointReference *tds__GetEndpointReference, struct _tds__GetEndpointReferenceResponse *tds__GetEndpointReferenceResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetRemoteUser(struct soap* soap, struct _tds__GetRemoteUser *tds__GetRemoteUser, struct _tds__GetRemoteUserResponse *tds__GetRemoteUserResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetRemoteUser(struct soap* soap, struct _tds__SetRemoteUser *tds__SetRemoteUser, struct _tds__SetRemoteUserResponse *tds__SetRemoteUserResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetUsers(struct soap* soap, struct _tds__GetUsers *tds__GetUsers, struct _tds__GetUsersResponse *tds__GetUsersResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__CreateUsers(struct soap* soap, struct _tds__CreateUsers *tds__CreateUsers, struct _tds__CreateUsersResponse *tds__CreateUsersResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__DeleteUsers(struct soap* soap, struct _tds__DeleteUsers *tds__DeleteUsers, struct _tds__DeleteUsersResponse *tds__DeleteUsersResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetUser(struct soap* soap, struct _tds__SetUser *tds__SetUser, struct _tds__SetUserResponse *tds__SetUserResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetWsdlUrl(struct soap* soap, struct _tds__GetWsdlUrl *tds__GetWsdlUrl, struct _tds__GetWsdlUrlResponse *tds__GetWsdlUrlResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetDPAddresses(struct soap* soap, struct _tds__SetDPAddresses *tds__SetDPAddresses, struct _tds__SetDPAddressesResponse *tds__SetDPAddressesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetHostname(struct soap* soap, struct _tds__GetHostname *tds__GetHostname, struct _tds__GetHostnameResponse *tds__GetHostnameResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetHostname(struct soap* soap, struct _tds__SetHostname *tds__SetHostname, struct _tds__SetHostnameResponse *tds__SetHostnameResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetHostnameFromDHCP(struct soap* soap, struct _tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, struct _tds__SetHostnameFromDHCPResponse *tds__SetHostnameFromDHCPResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDNS(struct soap* soap, struct _tds__GetDNS *tds__GetDNS, struct _tds__GetDNSResponse *tds__GetDNSResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetDNS(struct soap* soap, struct _tds__SetDNS *tds__SetDNS, struct _tds__SetDNSResponse *tds__SetDNSResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetNTP(struct soap* soap, struct _tds__GetNTP *tds__GetNTP, struct _tds__GetNTPResponse *tds__GetNTPResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetNTP(struct soap* soap, struct _tds__SetNTP *tds__SetNTP, struct _tds__SetNTPResponse *tds__SetNTPResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDynamicDNS(struct soap* soap, struct _tds__GetDynamicDNS *tds__GetDynamicDNS, struct _tds__GetDynamicDNSResponse *tds__GetDynamicDNSResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetDynamicDNS(struct soap* soap, struct _tds__SetDynamicDNS *tds__SetDynamicDNS, struct _tds__SetDynamicDNSResponse *tds__SetDynamicDNSResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetNetworkInterfaces(struct soap* soap, struct _tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, struct _tds__GetNetworkInterfacesResponse *tds__GetNetworkInterfacesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetNetworkInterfaces(struct soap* soap, struct _tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, struct _tds__SetNetworkInterfacesResponse *tds__SetNetworkInterfacesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetNetworkProtocols(struct soap* soap, struct _tds__GetNetworkProtocols *tds__GetNetworkProtocols, struct _tds__GetNetworkProtocolsResponse *tds__GetNetworkProtocolsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetNetworkProtocols(struct soap* soap, struct _tds__SetNetworkProtocols *tds__SetNetworkProtocols, struct _tds__SetNetworkProtocolsResponse *tds__SetNetworkProtocolsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetNetworkDefaultGateway(struct soap* soap, struct _tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, struct _tds__GetNetworkDefaultGatewayResponse *tds__GetNetworkDefaultGatewayResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetNetworkDefaultGateway(struct soap* soap, struct _tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, struct _tds__SetNetworkDefaultGatewayResponse *tds__SetNetworkDefaultGatewayResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetZeroConfiguration(struct soap* soap, struct _tds__GetZeroConfiguration *tds__GetZeroConfiguration, struct _tds__GetZeroConfigurationResponse *tds__GetZeroConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetZeroConfiguration(struct soap* soap, struct _tds__SetZeroConfiguration *tds__SetZeroConfiguration, struct _tds__SetZeroConfigurationResponse *tds__SetZeroConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetIPAddressFilter(struct soap* soap, struct _tds__GetIPAddressFilter *tds__GetIPAddressFilter, struct _tds__GetIPAddressFilterResponse *tds__GetIPAddressFilterResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetIPAddressFilter(struct soap* soap, struct _tds__SetIPAddressFilter *tds__SetIPAddressFilter, struct _tds__SetIPAddressFilterResponse *tds__SetIPAddressFilterResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__AddIPAddressFilter(struct soap* soap, struct _tds__AddIPAddressFilter *tds__AddIPAddressFilter, struct _tds__AddIPAddressFilterResponse *tds__AddIPAddressFilterResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__RemoveIPAddressFilter(struct soap* soap, struct _tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, struct _tds__RemoveIPAddressFilterResponse *tds__RemoveIPAddressFilterResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetAccessPolicy(struct soap* soap, struct _tds__GetAccessPolicy *tds__GetAccessPolicy, struct _tds__GetAccessPolicyResponse *tds__GetAccessPolicyResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetAccessPolicy(struct soap* soap, struct _tds__SetAccessPolicy *tds__SetAccessPolicy, struct _tds__SetAccessPolicyResponse *tds__SetAccessPolicyResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__CreateCertificate(struct soap* soap, struct _tds__CreateCertificate *tds__CreateCertificate, struct _tds__CreateCertificateResponse *tds__CreateCertificateResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetCertificates(struct soap* soap, struct _tds__GetCertificates *tds__GetCertificates, struct _tds__GetCertificatesResponse *tds__GetCertificatesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetCertificatesStatus(struct soap* soap, struct _tds__GetCertificatesStatus *tds__GetCertificatesStatus, struct _tds__GetCertificatesStatusResponse *tds__GetCertificatesStatusResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetCertificatesStatus(struct soap* soap, struct _tds__SetCertificatesStatus *tds__SetCertificatesStatus, struct _tds__SetCertificatesStatusResponse *tds__SetCertificatesStatusResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__DeleteCertificates(struct soap* soap, struct _tds__DeleteCertificates *tds__DeleteCertificates, struct _tds__DeleteCertificatesResponse *tds__DeleteCertificatesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetPkcs10Request(struct soap* soap, struct _tds__GetPkcs10Request *tds__GetPkcs10Request, struct _tds__GetPkcs10RequestResponse *tds__GetPkcs10RequestResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__LoadCertificates(struct soap* soap, struct _tds__LoadCertificates *tds__LoadCertificates, struct _tds__LoadCertificatesResponse *tds__LoadCertificatesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetClientCertificateMode(struct soap* soap, struct _tds__GetClientCertificateMode *tds__GetClientCertificateMode, struct _tds__GetClientCertificateModeResponse *tds__GetClientCertificateModeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetClientCertificateMode(struct soap* soap, struct _tds__SetClientCertificateMode *tds__SetClientCertificateMode, struct _tds__SetClientCertificateModeResponse *tds__SetClientCertificateModeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetRelayOutputs(struct soap* soap, struct _tds__GetRelayOutputs *tds__GetRelayOutputs, struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetRelayOutputSettings(struct soap* soap, struct _tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, struct _tds__SetRelayOutputSettingsResponse *tds__SetRelayOutputSettingsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetRelayOutputState(struct soap* soap, struct _tds__SetRelayOutputState *tds__SetRelayOutputState, struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SendAuxiliaryCommand(struct soap* soap, struct _tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, struct _tds__SendAuxiliaryCommandResponse *tds__SendAuxiliaryCommandResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetCACertificates(struct soap* soap, struct _tds__GetCACertificates *tds__GetCACertificates, struct _tds__GetCACertificatesResponse *tds__GetCACertificatesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__LoadCertificateWithPrivateKey(struct soap* soap, struct _tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey, struct _tds__LoadCertificateWithPrivateKeyResponse *tds__LoadCertificateWithPrivateKeyResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetCertificateInformation(struct soap* soap, struct _tds__GetCertificateInformation *tds__GetCertificateInformation, struct _tds__GetCertificateInformationResponse *tds__GetCertificateInformationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__LoadCACertificates(struct soap* soap, struct _tds__LoadCACertificates *tds__LoadCACertificates, struct _tds__LoadCACertificatesResponse *tds__LoadCACertificatesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__CreateDot1XConfiguration(struct soap* soap, struct _tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration, struct _tds__CreateDot1XConfigurationResponse *tds__CreateDot1XConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetDot1XConfiguration(struct soap* soap, struct _tds__SetDot1XConfiguration *tds__SetDot1XConfiguration, struct _tds__SetDot1XConfigurationResponse *tds__SetDot1XConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDot1XConfiguration(struct soap* soap, struct _tds__GetDot1XConfiguration *tds__GetDot1XConfiguration, struct _tds__GetDot1XConfigurationResponse *tds__GetDot1XConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDot1XConfigurations(struct soap* soap, struct _tds__GetDot1XConfigurations *tds__GetDot1XConfigurations, struct _tds__GetDot1XConfigurationsResponse *tds__GetDot1XConfigurationsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__DeleteDot1XConfiguration(struct soap* soap, struct _tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration, struct _tds__DeleteDot1XConfigurationResponse *tds__DeleteDot1XConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDot11Capabilities(struct soap* soap, struct _tds__GetDot11Capabilities *tds__GetDot11Capabilities, struct _tds__GetDot11CapabilitiesResponse *tds__GetDot11CapabilitiesResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetDot11Status(struct soap* soap, struct _tds__GetDot11Status *tds__GetDot11Status, struct _tds__GetDot11StatusResponse *tds__GetDot11StatusResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__ScanAvailableDot11Networks(struct soap* soap, struct _tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, struct _tds__ScanAvailableDot11NetworksResponse *tds__ScanAvailableDot11NetworksResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetSystemUris(struct soap* soap, struct _tds__GetSystemUris *tds__GetSystemUris, struct _tds__GetSystemUrisResponse *tds__GetSystemUrisResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__StartFirmwareUpgrade(struct soap* soap, struct _tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, struct _tds__StartFirmwareUpgradeResponse *tds__StartFirmwareUpgradeResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__StartSystemRestore(struct soap* soap, struct _tds__StartSystemRestore *tds__StartSystemRestore, struct _tds__StartSystemRestoreResponse *tds__StartSystemRestoreResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetStorageConfigurations(struct soap* soap, struct _tds__GetStorageConfigurations *tds__GetStorageConfigurations, struct _tds__GetStorageConfigurationsResponse *tds__GetStorageConfigurationsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__CreateStorageConfiguration(struct soap* soap, struct _tds__CreateStorageConfiguration *tds__CreateStorageConfiguration, struct _tds__CreateStorageConfigurationResponse *tds__CreateStorageConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetStorageConfiguration(struct soap* soap, struct _tds__GetStorageConfiguration *tds__GetStorageConfiguration, struct _tds__GetStorageConfigurationResponse *tds__GetStorageConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetStorageConfiguration(struct soap* soap, struct _tds__SetStorageConfiguration *tds__SetStorageConfiguration, struct _tds__SetStorageConfigurationResponse *tds__SetStorageConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__DeleteStorageConfiguration(struct soap* soap, struct _tds__DeleteStorageConfiguration *tds__DeleteStorageConfiguration, struct _tds__DeleteStorageConfigurationResponse *tds__DeleteStorageConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetGeoLocation(struct soap* soap, struct _tds__GetGeoLocation *tds__GetGeoLocation, struct _tds__GetGeoLocationResponse *tds__GetGeoLocationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetGeoLocation(struct soap* soap, struct _tds__SetGeoLocation *tds__SetGeoLocation, struct _tds__SetGeoLocationResponse *tds__SetGeoLocationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__DeleteGeoLocation(struct soap* soap, struct _tds__DeleteGeoLocation *tds__DeleteGeoLocation, struct _tds__DeleteGeoLocationResponse *tds__DeleteGeoLocationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetPasswordComplexityOptions(struct soap* soap, struct _tds__GetPasswordComplexityOptions *tds__GetPasswordComplexityOptions, struct _tds__GetPasswordComplexityOptionsResponse *tds__GetPasswordComplexityOptionsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetPasswordComplexityConfiguration(struct soap* soap, struct _tds__GetPasswordComplexityConfiguration *tds__GetPasswordComplexityConfiguration, struct _tds__GetPasswordComplexityConfigurationResponse *tds__GetPasswordComplexityConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetPasswordComplexityConfiguration(struct soap* soap, struct _tds__SetPasswordComplexityConfiguration *tds__SetPasswordComplexityConfiguration, struct _tds__SetPasswordComplexityConfigurationResponse *tds__SetPasswordComplexityConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetPasswordHistoryConfiguration(struct soap* soap, struct _tds__GetPasswordHistoryConfiguration *tds__GetPasswordHistoryConfiguration, struct _tds__GetPasswordHistoryConfigurationResponse *tds__GetPasswordHistoryConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetPasswordHistoryConfiguration(struct soap* soap, struct _tds__SetPasswordHistoryConfiguration *tds__SetPasswordHistoryConfiguration, struct _tds__SetPasswordHistoryConfigurationResponse *tds__SetPasswordHistoryConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetAuthFailureWarningOptions(struct soap* soap, struct _tds__GetAuthFailureWarningOptions *tds__GetAuthFailureWarningOptions, struct _tds__GetAuthFailureWarningOptionsResponse *tds__GetAuthFailureWarningOptionsResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__GetAuthFailureWarningConfiguration(struct soap* soap, struct _tds__GetAuthFailureWarningConfiguration *tds__GetAuthFailureWarningConfiguration, struct _tds__GetAuthFailureWarningConfigurationResponse *tds__GetAuthFailureWarningConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
int __tds__SetAuthFailureWarningConfiguration(struct soap* soap, struct _tds__SetAuthFailureWarningConfiguration *tds__SetAuthFailureWarningConfiguration, struct _tds__SetAuthFailureWarningConfigurationResponse *tds__SetAuthFailureWarningConfigurationResponse) { printf("%s\n", __func__); return SOAP_OK; }
