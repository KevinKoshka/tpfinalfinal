// Example by Tom Igoe

import processing.serial.*;
import ddf.minim.*;
import ddf.minim.signals.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;


int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

Minim m;
AudioPlayer[] sonido = new AudioPlayer[9];

String[] estado = new String[9];


void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  
  m = new Minim(this);
  sonido[0] = m.loadFile("File000631.wav");
  sonido[1] = m.loadFile("File001004.wav");
  
  for(int i = 0; i < estado.length; i++){
    estado[i] = "CAOS";  
  }
  
  
 

}

void draw() {
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      println("myString: " + myString);
      int[] currentKeys = int[2];
      if(myString.length == 1){
        currentKeys[0] = Integer.parseInt(myString);
      } else if(myString.length > 1) {
        for(int i = 0; i < 2; i++) {
          currentKeys[i] = 
        }
      }
      
      float aaa = PApplet.parseFloat(myString);
      int which = int(aaa);
      println(which);
      if (estado[which] == "CAOS" && !sonido[which].isPlaying()) {
        estado[which] = "ORDEN";
        println("Camino " + which);
        sonido[which].play(0);
      }
      for(int i = 0; i < sonido.length; i++){
        if(sonido[i] != null){
          if(estado[i] == "ORDEN" && !sonido[i].isPlaying()){
            estado[i] = "CAOS";
          }
        }
      }
    }
  }
}

void stop() {
  sonido[0].close();
  estado[0] = "CAOS";
  sonido[1].close();
  estado[1] = "CAOS";
  m.stop();

  super.stop();
}

