# Wireless_Trickle_Network
The objective of this project was to use a series of SAM4S microcontrollers with Xbee wireless radios attached to each to act as nodes in a wireless communication network.

Each node, except for the ‘seed’ node, begins in a state of simply listening for a signal from a specific node. When that signal is received it maintains it’s listening state, but also transmits a signal of its own to another specific node. This propagates throughout the network until each node is both receiving and sending. If the communication chain is broken all nodes after where the break occurs stop sending until a signal is again received at the break.

The seed node begins in an inactive state and is primed via a button push. Once instigated the seed node will continuously send information to the next node in line until it is told to stop.

## Hardware

The main hardware used for this project:

*SAM4SD32 Microcontroller*

## Implementation
Once a packet was received from the correct node the one of the LEDs on the SAM4S was set to blink. The blink timing depended on the RSSI signal strength received from the sending node. The closer the node, the faster the blink. Similarly, the OLED screen on the Xplained Pro extension was configured to display the actual RSSI value, though this proved to be inconsistent.

## Challenges
Troubleshooting wireless communication proved to be difficult. In some cases a signal would be received when no signal was sent and, more commonly, a signal sent with no acknowledgement of being received. Trying to track down and pin point what was causing this errors simply came down to trial and error in many cases.

We were not able to solve why our OLED display gave us strange and inconsistent RSSI values. These discrepancies could have been from a wireless communication error or a bug in our code that we weren’t able to track down.

An issue arose with our wiring for connecting the Xbees to the SAM4S. The wires we manufactured worked, however they were the wrong size for the extensions on the SAM4S, this led to some wires contacting each other, which caused odd behaviour. After troubleshooting wireless communication issues a decision was made to manufacture new wires for the nodes that were giving us trouble, this time ensuring proper shielding on the end connections.

## Special Thanks
A huge part of this project is built on top of MiniOS, an operating system built for the SAM4S micro controller by [Rafael Roman Otero](http://embedntks.com/author/romanot/)
