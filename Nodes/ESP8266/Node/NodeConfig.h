#ifndef NodeConfig_h
#define NodeConfig_h

#include "Arduino.h"
#include "FS.h"

class NodeConfig
{
  public:
    NodeConfig(const char* config_file);

    const char* getAPSSID();
    const char* getAPPassword();

    const char* getHubAddress();
    int getHubPort();

    const char* getNodeID();

  private:
    const char* _config_file;

    const char* _ap_ssid;
    const char* _ap_password;

    const char* _hubAddress;
    int _hubPort;

    const char* _nodeID = "xF30dKjd";
};

#endif
