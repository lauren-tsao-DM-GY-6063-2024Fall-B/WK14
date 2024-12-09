let mSerial;

let connectButton;

let cBackgroundColor;

function connectToSerial() {
  if (!mSerial.opened()) {
    mSerial.open(9600);
    connectButton.hide();
  }
}

function setup() {
  createCanvas(windowWidth, windowHeight);

  mSerial = createSerial();

  connectButton = createButton("Connect To Serial");
  connectButton.position(width / 2, height / 2);
  connectButton.mousePressed(connectToSerial);

  cBackgroundColor = 0;
}

function draw() {
  background(cBackgroundColor);

  if (mSerial.opened() && mSerial.availableBytes() > 0) {
    let mLine = mSerial.readUntil("\n");
    let sensorVal = int(mLine);
    print(mLine, sensorVal);
    cBackgroundColor = map(sensorVal, 0, 2000, 0, 255, true);
  }
}
