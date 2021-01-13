# A basic Minetest mod to interact with an NodeMCU in the game
The NodeMCU creates a web server and do some specific actions when some specific pages are requested.

The Minetest mod defines a new node the reacts to mesecons, when the node is activated, it sends a request to the NodeMCU to do something (enable an output). When it is deactivated, it sends another request to disable the output.
It also request a page every 200ms to get the state of a button connected to the NodeMCU, if the button is pressed, it places a node at a specific location.

## NodeMCU -> Minetest communication
TODO

## Minetest -> NodeMCU communication
TODO

## Enable mod in Minetest
TODO
