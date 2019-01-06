## Overview

Electron app implementing OSC.js. This current sample work with a [Rotary Encoder](https://coolcomponents.co.uk/products/rotary-encoder-1024-p-r-quadrature) which is connected to an Arduino board. The arduino board sends data coming from the rotary encoder to the Electron app over OSC.

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
cd electron-osc-boilerplate
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

## Running the Example

1. Run <code>npm run electron-app</code>

## Adding new mpm modules

Everytime a new npm module is added you need to run this command to rebuild electron

```shell
npm run electron-app
```

**make sure that you are using python 2 to make the build**

## Computer IP

The ethernet port where the device sending OSC data is connected needs to be set to 169, 254, 227, 11.
