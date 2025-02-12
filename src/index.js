const addon = require('../build/Release/addon.node');

// Callback function to handle the completion of the loops
function loopCallback(err, result) {
  if (err) {
    console.error(err);
    return;
  }
  console.log(result);
}

// Start the loops
console.log(addon.startLoops(loopCallback));

// Delay function
function delay(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

async function run() {
  // Get the state of the loops with delay
  await delay(5000);
  console.log('Iteration 1:', addon.getIteration(1));
  console.log('Iteration 2:', addon.getIteration(2));
  console.log('Iteration 3:', addon.getIteration(3));

  // Reset the first loop with delay
  console.log(addon.resetIteration(1));
  console.log(addon.resetIteration(2));
  //   console.log(addon.resetIteration(3));

  // Get the state of the first loop after reset with delay
  await delay(1000);
  console.log('Iteration 1 after reset:', addon.getIteration(1));
  console.log('Iteration 2 after reset:', addon.getIteration(2));
  console.log('Iteration 3 after reset:', addon.getIteration(3));

  await delay(5000);
  console.log('Iteration despues de ', addon.getIteration(1));
  console.log('Iteration despues de ', addon.getIteration(2));
  console.log('Iteration despues de ', addon.getIteration(3));
}

run();
