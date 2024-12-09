let SERVER_ADDRESS = "http://192.168.1.239/data";

let readyToLoad;
let cBackgroundColor;

function parseData(res) {
  let data = res.data;
  let a0 = data.A0;

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
    loadJSON(SERVER_ADDRESS, parseData);
  }
}
