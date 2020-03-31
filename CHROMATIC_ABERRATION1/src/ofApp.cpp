



#include "ofApp.h"


#include <iostream>

//actual variables for this project
//0 is picaputre, 1 is usbinput
bool inputswitch=1;


int power=1;

bool bright_switch1=0;
bool hue_switch1=1;
bool bright_switch2=0;
bool hue_switch2=1;
bool bright_switch3=0;
bool hue_switch3=1;
bool bright_switch4=0;
bool hue_switch4=1;


bool bright_switch_lfo1=0;
bool hue_switch_lfo1=1;
bool bright_switch_lfo2=0;
bool hue_switch_lfo2=1;
bool bright_switch_lfo3=0;
bool hue_switch_lfo3=1;
bool bright_switch_lfo4=0;
bool hue_switch_lfo4=1;

float hue1=0;
float bright1=0;
float hue2=0;
float bright2=0;
float hue3=0;
float bright3=0;
float hue4=0;
float bright4=0;

float hue1_theta=0;
float hue1_theta_add=0;
float hue1_amp=0;
float hue2_theta=0;
float hue2_theta_add=0;
float hue2_amp=0;
float hue3_theta=0;
float hue3_theta_add=0;
float hue3_amp=0;
float hue4_theta=0;
float hue4_theta_add=0;
float hue4_amp=0;


float bright1_theta=0;
float bright1_theta_add=0;
float bright1_amp=0;
float bright2_theta=0;
float bright2_theta_add=0;
float bright2_amp=0;
float bright3_theta=0;
float bright3_theta_add=0;
float bright3_amp=0;
float bright4_theta=0;
float bright4_theta_add=0;
float bright4_amp=0;



ofPolyline tetrahedron;

float az=0;
float sx=0;
float dc=0;
float fv=0;
float gb=0;
float hn=0;
float jm=0;
float kk=0;
float ll=0;
float qw=0;
float er=0;
float ty=0;
float ui=0;
float op=0;




float c1=0.0;
float c2=0.0;
float c3=0.0;
float c4=0.0;
float c5=0.0;
float c6=0.0;
float c7=0.0;
float c8=0.0;
float c9=0.0;
float c10=0.0;
float c11=0.0;
float c12=0.0;
float c13=0.0;
float c14=0.0;
float c15=.0;
float c16=.0;







int width=640;
int height=480;



//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofBackground(0);
	ofHideCursor();
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    
    /**MIDIBIX***/
    
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
    
    
    //shadersbiz
    shader_colorize.load("shadersES2/shader_colorize");
    
    /*******/
    
    
    //cam1.setVerbose(true);
    cam1.setDeviceID(0);
    //cam1.setup(width,height);
    
   
 
    
	omx_settings();
	
	 //pass in the settings and it will start the camera
	if(inputswitch==0){
		videoGrabber.setup(settings);
	}

	
	if(inputswitch==1){
		cam1.initGrabber(width,height);
	}
	
	
	fb0.allocate(width,height);
	
	fb0.begin();
	ofClear(0,0,0,255);
	fb0.end();
   
}

//--------------------------------------------------------------
void ofApp::update() {

   if(inputswitch==1){
		cam1.update();
	}
	
	if(inputswitch==0){
		
		omx_updates();
		
	}
    
    /*midimessagesbiz**/
    midibiz();

   
    
    
    
    
   
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);
    
   
    
   
    fb0.begin();
    
    shader_colorize.begin();
    
    if(inputswitch==0){
			videoGrabber.draw(0,0);
		}
		
	if(inputswitch==1){
			cam1.draw(0,0);
		}
    
    
    //so modes to try
    //1 can be linear
    //2 can be squared
    shader_colorize.setUniform1f("power",power);
    
    
    shader_colorize.setUniform1i("glitch_switch3",0);
    
    shader_colorize.setUniform1f("hue_select1",hue1);
    shader_colorize.setUniform1f("saturation_amount1",c1);
    shader_colorize.setUniform1f("bright1",bright1);
    
    hue1_theta+=.05*hue1_theta_add;
    bright1_theta+=.05*bright1_theta_add;
    shader_colorize.setUniform1f("hue1_theta",hue1_theta);
    shader_colorize.setUniform1f("hue1_amp",4*hue1_amp);
    
    shader_colorize.setUniform1f("bright1_theta",bright1_theta);
    shader_colorize.setUniform1f("bright1_amp",2*bright1_amp);

    
    
    
    shader_colorize.setUniform1f("hue_select2",hue2);
    shader_colorize.setUniform1f("saturation_amount2",c2);
    shader_colorize.setUniform1f("bright2",bright2);
    
    hue2_theta+=.05*hue2_theta_add;
    bright2_theta+=.05*bright2_theta_add;
    shader_colorize.setUniform1f("hue2_theta",hue2_theta);
    shader_colorize.setUniform1f("hue2_amp",4*hue2_amp);
    
    shader_colorize.setUniform1f("bright2_theta",bright2_theta);
    shader_colorize.setUniform1f("bright2_amp",2*bright2_amp);
    
    shader_colorize.setUniform1f("hue_select3",hue3);
    shader_colorize.setUniform1f("saturation_amount3",c3);
    shader_colorize.setUniform1f("bright3",bright3);
    
    hue3_theta+=.05*hue3_theta_add;
    bright3_theta+=.05*bright3_theta_add;
    shader_colorize.setUniform1f("hue3_theta",hue3_theta);
    shader_colorize.setUniform1f("hue3_amp",4*hue3_amp);
    
    shader_colorize.setUniform1f("bright3_theta",bright3_theta);
    shader_colorize.setUniform1f("bright3_amp",2*bright3_amp);
    
    shader_colorize.setUniform1f("hue_select4",hue4);
    shader_colorize.setUniform1f("saturation_amount4",c4);
    shader_colorize.setUniform1f("bright4",bright4);
    
    hue4_theta+=.05*hue4_theta_add;
    bright4_theta+=.05*bright4_theta_add;
    shader_colorize.setUniform1f("hue4_theta",hue4_theta);
    shader_colorize.setUniform1f("hue4_amp",4*hue4_amp);
    
    shader_colorize.setUniform1f("bright4_theta",bright4_theta);
    shader_colorize.setUniform1f("bright4_amp",2*bright4_amp);
    //in order to do bright switch things
    //will need to freeze the value of the color
   //so perhaps down in the midi controls areay
    //have seperate variables for hue select and bright down theres
    //and then when the button is hit
    //we freeze the value at that time
    shader_colorize.setUniform1i("bright_switch1",bright_switch1);
    shader_colorize.setUniform1i("bright_switch2",bright_switch2);
    shader_colorize.setUniform1i("bright_switch3",bright_switch3);
    shader_colorize.setUniform1i("bright_switch4",bright_switch4);
    
    //shader_displace.setUniformTexture("x_noise_texture",x_noise_image.getTexture(),1);
    
    //shader_displace.setUniform1f("luma_key_level",c1+gui->lumakey_value);
   
   
    shader_colorize.end();
    fb0.end();
   
   // ofPushMatrix();
    
    //cam1.draw(0,0);
    //ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
    fb0.draw(0,0,720,480);
    //ofPopMatrix();
    
    
    ofSetColor(255);
    
    
    string msg="fps="+ofToString(ofGetFrameRate(),2);//+" clear switch"+ofToString(clear_switch,5);//+" z="+ofToString(az,5);
    //ofDrawBitmapString(msg,10,10);
    
   
    
    
    
    
   
}



//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//__------------------------------------------------------------

void ofApp::omx_settings(){
	
	settings.sensorWidth = 640;
    settings.sensorHeight = 480;
    settings.framerate = 30;
    settings.enableTexture = true;
    settings.sensorMode=7;
    
    settings.whiteBalance ="Off";
    settings.exposurePreset ="Off";
    settings.whiteBalanceGainR = 1.0;
    settings.whiteBalanceGainB = 1.0;
	
	}
//------------------------------------------------------------

void ofApp::omx_updates(){
	
		videoGrabber.setSharpness(50);
		videoGrabber.setBrightness(40);
		videoGrabber.setContrast(25);
		videoGrabber.setSaturation(0);
	
	}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    
    
   
    //if(key=='q'){sw1==0;}
    
    if(key=='s'){sx+=1;}
    if(key=='x'){sx-=1;}
    
    if(key=='d'){dc+=0.01;}
    if(key=='c'){dc-=0.01;}
    
    if(key=='f'){fv+=0.1;}
    if(key=='v'){fv-=0.1;}
    
    if(key=='g'){gb+=0.01;}
    if(key=='b'){gb-=0.01;}
    if(key=='h'){hn+=0.01;}
    if(key=='n'){hn-=0.01;}
    
    
    if(key=='j'){jm+=0.1;}
    if(key=='m'){jm-=0.1;}
    if(key=='k'){kk+=0.1;}
    if(key==','){kk-=0.1;}
    
    if(key=='l'){ll+=0.01;}
    if(key=='.'){ll-=0.01;}
    
    if(key=='t'){ty+=0.01;}
    if(key=='y'){ty-=0.01;}
    
    if(key=='e'){er+=0.1;}
    if(key=='r'){er-=0.1;}
    
   
 
    
    
    
    
   
}


//---------------------
void ofApp:: midibiz(){
    
    for(unsigned int i = 0; i < midiMessages.size(); ++i) {
        
        ofxMidiMessage &message = midiMessages[i];
        
        
        //cout << "envcount="<< envcount<< endl;
        
        if(message.status < MIDI_SYSEX) {
            //text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                //  cout << "message.control"<< message.control<< endl;
                //  cout << "message.value"<< message.value<< endl;
                
                
                
                
                //nanokontrol2 controls
                if(message.control==16){
                    //  c1=(message.value-63.0)/63.0;
                    c1=(message.value)/127.00;
                    
                }
                
                
                if(message.control==17){
                     //c2=(message.value-63.0)/63.0;
                    c2=(message.value)/127.00;
                    
                }
                
                
                if(message.control==18){
                   // c3=(message.value-63.0)/63.00;
                      c3=(message.value)/127.00;
                }
                
                
                if(message.control==19){
                   // c4=(message.value-63.0)/63.00;
                     c4=(message.value)/127.00;
                    
                }
                
                
                
                
                
                
                
                
               
                
                
                
                
                
                
                if(message.control==32){
                    if(message.value==127){
                        bright_switch1=1;
                        hue_switch1=0;
                    }
                    if(message.value==0){
                        bright_switch1=0;
                        hue_switch1=1;
                    }
                    
                }
                
                
                
                if(message.control==120){
                   // c9=(message.value-63.0)/63.0;
                    
                    if(hue_switch1==1){
                        hue1=(message.value)/127.00;
                    }
                    
                    if(bright_switch1==1){
                        bright1=(message.value)/127.00;
                    }
                }
                
                
                if(message.control==33){
                    if(message.value==127){
                        bright_switch2=1;
                        hue_switch2=0;
                    }
                    if(message.value==0){
                        bright_switch2=0;
                        hue_switch2=1;
                    }
                    
                }

                if(message.control==121){
                    if(hue_switch2==1){
                        hue2=(message.value)/127.00;
                    }
                    
                    if(bright_switch2==1){
                        bright2=(message.value)/127.00;
                    }
                    
                }
                
                if(message.control==34){
                    if(message.value==127){
                        bright_switch3=1;
                        hue_switch3=0;
                    }
                    if(message.value==0){
                        bright_switch3=0;
                        hue_switch3=1;
                    }
                    
                }

                
                if(message.control==122){
                    if(hue_switch3==1){
                        hue3=(message.value)/127.00;
                    }
                    
                    if(bright_switch3==1){
                        bright3=(message.value)/127.00;
                    }
                  
                   

                }
                
                
                if(message.control==35){
                    if(message.value==127){
                        bright_switch4=1;
                        hue_switch4=0;
                    }
                    if(message.value==0){
                        bright_switch4=0;
                        hue_switch4=1;
                    }
                    
                }

                
                if(message.control==123){
                    if(hue_switch4==1){
                        hue4=(message.value)/127.00;
                    }
                    
                    if(bright_switch4==1){
                        bright4=(message.value)/127.00;
                    }
                    
                }
                
                
                if(message.control==36){
                    if(message.value==127){
                        bright_switch_lfo1=1;
                        hue_switch_lfo1=0;
                    }
                    if(message.value==0){
                        bright_switch_lfo1=0;
                        hue_switch_lfo1=1;
                    }
                    
                }

                
                
                if(message.control==124){
                    c13=(message.value-63.0)/63.00;
                    
                    if(hue_switch_lfo1==1){
                        hue1_amp=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo1==1){
                        bright1_amp=(message.value)/127.00;
                    }
                    

                    
                }
                
                
                if(message.control==20){
                    c5=(message.value-63.0)/63.00;
                    //  c5=(message.value)/127.00;
                    
                    if(hue_switch_lfo1==1){
                        hue1_theta_add=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo1==1){
                        bright1_theta_add=(message.value)/127.00;
                    }
                    
                }
                
                
                if(message.control==37){
                    if(message.value==127){
                        bright_switch_lfo2=1;
                        hue_switch_lfo2=0;
                    }
                    if(message.value==0){
                        bright_switch_lfo2=0;
                        hue_switch_lfo2=1;
                    }
                    
                }
                if(message.control==125){
                    c14=(message.value-63.0)/63.0;
                    
                    if(hue_switch_lfo2==1){
                        hue2_amp=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo2==1){
                        bright2_amp=(message.value)/127.00;
                    }
                }
                
                if(message.control==21){
                    if(hue_switch_lfo2==1){
                        hue2_theta_add=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo2==1){
                        bright2_theta_add=(message.value)/127.00;
                    }

                }
                
                
                if(message.control==38){
                    if(message.value==127){
                        bright_switch_lfo3=1;
                        hue_switch_lfo3=0;
                    }
                    if(message.value==0){
                        bright_switch_lfo3=0;
                        hue_switch_lfo3=1;
                    }
                    
                }
                
                if(message.control==126){
                    c15=(message.value-63.0)/63.0;
                    if(hue_switch_lfo3==1){
                        hue3_amp=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo2==1){
                        bright3_amp=(message.value)/127.00;
                    }
                   
                }
                
                
                if(message.control==22){
                    if(hue_switch_lfo3==1){
                        hue3_theta_add=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo3==1){
                        bright3_theta_add=(message.value)/127.00;
                    }

                }
                
                
                if(message.control==39){
                    if(message.value==127){
                        bright_switch_lfo4=1;
                        hue_switch_lfo4=0;
                    }
                    if(message.value==0){
                        bright_switch_lfo4=0;
                        hue_switch_lfo4=1;
                    }
                    
                }

                
                if(message.control==127){
                    c16=(message.value-63.0)/63.00;
                    if(hue_switch_lfo4==1){
                        hue4_amp=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo4==1){
                        bright4_amp=(message.value)/127.00;
                    }
                    
                }
                
                
                if(message.control==23){
                    
                    if(hue_switch_lfo4==1){
                        hue4_theta_add=(message.value)/127.00;
                    }
                    
                    if(bright_switch_lfo4==1){
                        bright4_theta_add=(message.value)/127.00;
                    }

                    
                }
                
                
                //switches and whatnot
                if(message.control==43){
                    if(message.value==127){
                        power=2;
                    }
                    
                    if(message.value==0){
                        power=1;
                    }
                }
                
                //switches and whatnot
                if(message.control==44){
                    if(message.value==127){
                        power=3;
                    }
                    
                    if(message.value==0){
                        power=1;
                    }
                }
                
                if(message.control==42){
                    if(message.value==127){
                        power=4;
                    }
                    
                    if(message.value==0){
                        power=1;
                    }
                }
              
                
                //text << "\tctl: " << message.control;
                //ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                //	ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
            }
            
            
            //text << " "; // pad for delta print
        }//
        
        
    }
    
    
    /******* endmidimessagesbiz*********/
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}



//--------------------------------------------------------------




//--------------------------------------------------------------


