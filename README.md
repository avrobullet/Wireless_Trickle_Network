# Wireless_Trickle_Network
The objective of this project was to use a series of SAM4S microcontrollers with Xbee wireless radios attached to each to act as nodes in a wireless communication network.

Each node, except for the ‘seed’ node, begins in a state of simply listening for a signal from a specific node. When that signal is received it maintains it’s listening state, but also transmits a signal of its own to another specific node. This propagates throughout the network until each node is both receiving and sending. If the communication chain is broken all nodes after where the break occurs stop sending until a signal is again received at the break.

The seed node begins in an inactive state and is primed via a button push. Once instigated the seed node will continuously send information to the next node in line until it is told to stop.

## Hardware

The main hardware used for this project:

