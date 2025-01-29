const addon = require('../build/Release/addon.node');

console.log(addon.startLoops()); // "Loops started"
console.log(addon.getPIDs()); // Array de PIDs
console.log(addon.getIteration(1));
