let SERVER_ADDRESS = "http://10.10.81.108/data"; // specify address of arduino (from arduino serial monitor)

let readyToLoad; // have i already asked something and waiting for something? if i did, do not re-run
let cBackgroundColor;

function parseData(res) { // res meaning response
  print(res); // to print the data (not necessary but good to see that it is working)
  let data = res.data; // grabbing the data element
  let a0 = data.A0; // component of data

  cBackgroundColor = map(a0.value, a0.min, a0.max, 0, 255);
  readyToLoad = true;
}

function setup() {
  createCanvas(windowWidth, windowHeight);
  readyToLoad = true;
  cBackgroundColor = 0;
}

function draw() {
  background(cBackgroundColor);

  if (readyToLoad) {
    readyToLoad = false;
    loadJSON(SERVER_ADDRESS, parseData); // this is a p5.js function (SERVER ADDRESS = once you get a response, parseData = run this function)
  }
}
