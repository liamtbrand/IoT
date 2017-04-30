#include "NodeConfig.h"

NodeConfig::NodeConfig(const char* config_file)
{
  _config_file = config_file;

  _ap_ssid = _nodeID;
  _ap_password = "IoT Setup";

  _hubAddress = "172.20.10.5"; // HUB ADDRESS
  _hubPort = 9999;
}

const char* NodeConfig::getAPSSID()
{
  return _ap_ssid;
}

const char* NodeConfig::getAPPassword()
{
  return _ap_password;
}

const char* NodeConfig::getHubAddress()
{
  return _hubAddress;
}

int NodeConfig::getHubPort()
{
  return _hubPort;
}
