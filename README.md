# Wireless Trickle Network

Click the image below to view the Wireless Trickle Network in action (pardon the choice cheesy music and cheeky sound effects...)
[![Wireless Trickle Network](https://img.youtube.com/vi/FVWkvPiDZ3Y/0.jpg)](https://www.youtube.com/watch?v=FVWkvPiDZ3Y&feature=youtu.be)

## Contents
- [Introduction](#introduction)
- [Hardware](#hardware)
- [Implementation](#implementation)
- [Challenges](#challenges)
- [Special Thanks](#special-hanks)
- [License](#license)

## Introduction

The objective of this project was to use a series of SAM4S microcontrollers with Xbee wireless radios attached to each to act as nodes in a wireless communication network.

Each node, except for the ‘seed’ node, begins in a state of simply listening for a signal from a specific node. When that signal is received it maintains it’s listening state, but also transmits a signal of its own to another specific node. This propagates throughout the network until each node is both receiving and sending. If the communication chain is broken all nodes after where the break occurs stop sending until a signal is again received at the break.

The seed node begins in an inactive state and is primed via a button push. Once instigated the seed node will continuously send information to the next node in line until it is told to stop.

## Hardware

The main hardware used for this project:

**SAM4SD32 Microcontroller**

<img src="https://mdrakos.github.io/images/sam4s.png" width="300" height="250">

* This is the brain of the project.
* Code is flashed and stored on the ROM
* Extension pins allow for connection to all other hardware components

**ATMEL OLED1 Xplained Pro**

<img src="https://mdrakos.github.io/images/oled.png" width="350" height="250">

* Used to initialize the program via a button push
* Display statistics (number of rotations) on OLED display

**Xbee Wireless Radio**

<img src="https://mdrakos.github.io/images/xbee-ant.png" width="350" height="250">

* Xbee RF modules for easy deployment and connectivity
* Configured using XCTU software
* Configured so each module would accept packets from a specific broadcast address


## Implementation
Once a packet was received from the correct node the one of the LEDs on the SAM4S was set to blink. The blink timing depended on the RSSI signal strength received from the sending node. The closer the node, the faster the blink. Similarly, the OLED screen on the Xplained Pro extension was configured to display the actual RSSI value, though this proved to be inconsistent.

## Challenges
Troubleshooting wireless communication proved to be difficult. In some cases a signal would be received when no signal was sent and, more commonly, a signal sent with no acknowledgement of being received. Trying to track down and pin point what was causing this errors simply came down to trial and error in many cases.

We were not able to solve why our OLED display gave us strange and inconsistent RSSI values. These discrepancies could have been from a wireless communication error or a bug in our code that we weren’t able to track down.

An issue arose with our wiring for connecting the Xbees to the SAM4S. The wires we manufactured worked, however they were the wrong size for the extensions on the SAM4S, this led to some wires contacting each other, which caused odd behaviour. After troubleshooting wireless communication issues a decision was made to manufacture new wires for the nodes that were giving us trouble, this time ensuring proper shielding on the end connections.

## Special Thanks
A huge part of this project is built on top of MiniOS, an operating system built for the SAM4S micro controller by [Rafael Roman Otero](http://embedntks.com/author/romanot/).

## License
This project is licensed under the [MIT License](https://github.com/avrobullet/Wireless_Trickle_Network/blob/master/LICENSE) - see the LICENSE file for details
