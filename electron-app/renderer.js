// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
const ipc = require('electron').ipcRenderer

ipc.on('updateOSCValue', function (event, arg) {
  const message = `OSC: ${arg.address} , ${arg.value}`
  document.getElementById('value').innerHTML = message
})