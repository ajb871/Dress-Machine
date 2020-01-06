//pin consts
const int ledPin = 2;
const int ledPin2 = 4;

const int gLed = 6;

const int switchPin = 12;

//switch detection
bool mvmt = false;
int mvmtWrite = 0;

int switchState = 0;
int lastState = 0;
int switchNum = 0;

int switchElapse = 0; //time since switch last open/closed

int elapseMax = 1200; //max time between open/closings (200 frames aka ~3 seconds)

//output
int gValue = 0;
int gDir = 1;


void setup() {
  Serial.begin(9600);
  
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(gLed, OUTPUT);

}

void loop() {
  //Kind of like keeping a ballon in the air - hitting it will reset the count to
  //0 and therefore, there is movement. If you stop hitting it, after X seconds it
  //will be determined that there is no movement (the balloon has hit the ground)
  //The "hitting"/ switch activation does not need to follow a certain pattern as
  //long as it is before the balloon drops (switchElapse reaches X)
  
  //detect if switch is opened or closed
  switchState = digitalRead(switchPin);

  //check if state has changed
  if(switchState != lastState){
    //If it has changed - no time elapsed since last switch
    switchElapse = 0;
    switchNum += 1; //one switch
    mvmt = true; //there has been movement
    digitalWrite(ledPin, HIGH);
  } else{
    //No change? +1 points towards turning mvmt off
    if(switchElapse <= elapseMax){
      switchElapse += 1;
    }
    digitalWrite(ledPin, LOW);
    if(switchState == LOW){
      //no mvmt and no fabric on machine
    }
  }
  
  //if it hasn't changed in X seconds and is open - no movement
  if (switchElapse >= elapseMax){
    mvmt = false;
  } else {
    //Serial.println(switchElapse);
  }


  //set previous state to current state at end of function
  lastState = switchState;
  if(mvmt == true){
    digitalWrite(ledPin2, HIGH);
    gLights();
  } else {
    digitalWrite(ledPin2, LOW);
  }

  if(mvmt == false){
    mvmtWrite = 0;
  } else {
    mvmtWrite = 1;
  }
  digitalWrite(gLed, gValue);
  Serial.write(mvmtWrite);


}

void gLights(){
  gValue += gDir;


  //Light pulsing
  if(gDir > 50){
    if (gValue >= 255){
      gDir = -gDir;
    }
  } else {
    if (gValue <= 0){
      gDir = -gDir;
    }
  }
  
}

void playAudio(){
  //for audio
  if(mvmt){
    //fade into audio here - maybe just turn up volume for continously playing clips
  }
}

void sendData(){
  //for sending to ESP/server
  //send mvmt boolean. simple
}


//make the elapse time since movemtn strarted affetc the max elapse time for no change
//direct 1-1
