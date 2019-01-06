
# Overview

Electron app implementing OSC.js. This current sample work with a [Rotary Encoder](https://coolcomponents.co.uk/products/rotary-encoder-1024-p-r-quadrature) which is connected to an Arduino board. The arduino board sends data coming from the rotary encoder to the Electron app over OSC.

# Electron

## Dependencies

node library 
* [osc.js](https://www.npmjs.com/package/osc) 


## Installation

* Clone the repo

```shell
npm install
```

* change directory

```shell
cd electron-osc-boilerplate/electron
```

* install dependencies

```shell
npm i
```

* rebuild electron
```shell
npm run electron-app
```

This is necessary due to some features used by osc https://github.com/electron/electron-rebuild

Read the osc documentation about installation with Electron. https://github.com/colinbdclark/osc.js/

**make sure that you are using python 2 to make the build**

## Adding new mpm modules

Everytime a new npm module is added you need to run this command to rebuild electron

```shell
npm run electron-app
```

**make sure that you are using python 2 to make the build**

## Computer IP

The ethernet port where the device sending OSC data is connected needs to be set to 169, 254, 227, 11.

# Arduino

## Prerequisite libraries

* [Arduino 1.8.5](https://www.arduino.cc/en/Main/Software)
* 2 libraries need to be installed
  * [Ethernet2](https://www.arduinolibraries.info/libraries/ethernet2)
  * [OSCBundle](https://github.com/CNMAT/OSC)

## Wiring 

This is wiring digram that i used for this sample but any other sensor could be used.

![Alt text](assets/Wiring_diagram.png?raw=true "Wiring diagram")