# A basic Minetest mod to interact with an MCU in the game
The MCU creates a web server and do some specific actions when some specific pages are requested.

The Minetest mod defines a new node the reacts to mesecons, when the node is activated, it sends a request to the MCU to do something (enable an output that light up an LED). When it is deactivated, it sends another request to disable the output.
It also request a page every 200ms to get the state of a button connected to the MCU, if the button is pressed, it places a node at a specific location.

Two different MCUs are supported here, the ESP8266 (NodeMcuMinetest folder) and the ESP32 (ESP32 Minetest folder)

## Configuration
### Enable mod in Minetest
TODO

### Mod settings
There are a couple of usefull mod settings :
- **IP_ADDRESS** : The MCU IP address
- **POS_X** | **POS_Y** | **POS_Z** : The coordonates where the node will be placed
- **NODE_TYPE** : The kind of node that will be placed

### MCU settings
There are two important settings in the MCU source file :
- **ssid** : The WiFi network name
- **password** : the WiFi network password

You can also change the pin used to connect the led and the button :
- **LED_PIN** : The pin used to power the LED
- **BTN_PIN** : The pin used to connect the button

## Schematics
### NodeMCU schematic
![schematic](/schematics/NodeMCU.png)

### ESP32 schematic
TODO

## Communication principles
### MCU -> Minetest communication
TODO

### Minetest -> MCU communication
TODO
