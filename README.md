# IoT

-
#### Hub:
The purpose of the hub is to talk to and manage local nodes.
The hub talks to the cloud and relays changes to/from the nodes.
Settings for the hub are stored locally, but can be managed from the cloud.

-
#### Nodes:
The nodes are designed to be linked to a hub which is linked to the cloud.

Nodes have two modes, setup and node mode.
When in setup mode, the hub acts as an AP,
where it will serve up a web page that allows a few basic settings to be changed.
These settings are for the accesspoint this node connects to, and for the hub ip.

Once the node has successfully established a connection with the hub,
it then talks to the hub, and verifies using the cloud.
