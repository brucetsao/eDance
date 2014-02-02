import processing.serial.*;
Serial myPort;      
int i;
//int [] incoming={0,0,0,0,0,0,0,0,0,0};
int in_index = 0;
char read_in;
int comchosen=-1;
String incoming;
int baud_rate=115200;

void setup(){
    println(Serial.list());
  size (800,1000);
  background(100);
  
    fill(50);
    rect(0,750,800,250);
    fill(250);
    text("Available Ports:",100,790);
   text("Created By: Patrick McCabe",520,970);
    while(i<Serial.list().length) {
      fill(100);
      rect(10,i*30+800,350,30);
      fill(250);
   text("port  "+i+": " +Serial.list()[i],20,i*30+820); // display all available ports
    i++;
    
  
}


}


void draw(){
  
 if(comchosen>=0){
   while(myPort.available() > 0){
       incoming = myPort.readStringUntil('n');
        if(incoming != null){
          println(incoming);
          println(incoming.length());
          display();
          myPort.clear();
        }
        
      }
 }
 
}


void mousePressed(){
  if(mouseButton== LEFT){
if(comchosen==-1){
   if(mouseX>10 && mouseX<350 && mouseY>800 && mouseY<i*30+830){
     comchosen=(mouseY-800)/30;
     print("com:");
     println(comchosen);
      fill(0,0,170);
      rect(10,comchosen*30+800,350,30);
      fill(250);
     text("port  "+comchosen+": " +Serial.list()[comchosen],20,comchosen*30+820); // display all available ports
      myPort = new Serial(this, Serial.list()[comchosen], baud_rate); //connect to the serial port (arduino running at 115200 baud)
   }
}
}
}

void display(){
  fill(100);
  rect(0,0,800,750); //clear screen
String red_button = Character.toString(incoming.charAt(0));
String green_button = Character.toString(incoming.charAt(1));
String blue_button = Character.toString(incoming.charAt(2));
String yellow_button = Character.toString(incoming.charAt(3));
String orange_button = Character.toString(incoming.charAt(4));
String height_value = Character.toString(incoming.charAt(5));

int redbutton=int(red_button);
int greenbutton=int(green_button);
int bluebutton=int(blue_button);
int yellowbutton=int(yellow_button);
int orangebutton=int(orange_button);
int heightvalue=int(height_value);

if(incoming.length()==8){
    println(heightvalue);
  heightvalue*=10;
 String height_value2 = Character.toString(incoming.charAt(6));
 int heightvalue2=int(height_value2);
 heightvalue+=heightvalue2;
}
if(incoming.length()==9){
  println(heightvalue);
   heightvalue*=10;
 String height_value4 = Character.toString(incoming.charAt(6));
 int heightvalue4=int(height_value4);
 heightvalue+=heightvalue4;
  heightvalue*=10;
 String height_value3 = Character.toString(incoming.charAt(7));
 int heightvalue3=int(height_value3);
 heightvalue+=heightvalue3;
}
fill(250);
text("Height Value:",480,580);
text(heightvalue,500,600);

println(heightvalue);

  fill(200,0,0);
  rect(10,700,60,redbutton*heightvalue*-3); //display red
  fill(0,200,0);
  rect(90,700,60,greenbutton*heightvalue*-3);//display green
  fill(0,0,200);
  rect(170,700,60,bluebutton*heightvalue*-3);//display blue
  fill(255,255,0);
  rect(250,700,60,yellowbutton*heightvalue*-3);//display yellow
  fill(255,140,0);
  rect(330,700,60,orangebutton*heightvalue*-3);//display orange
    
  
  
}

