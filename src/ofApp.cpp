#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetBackgroundAuto( false );
    int numFilters = 40;
    //VIDEO PLAYER //
    myVideoPlayer.loadMovie("NYCPower.mov");
    myVideoPlayer.play();
    myVideoPlayer.setLoopState(OF_LOOP_NORMAL);
    
    ofBackground(0,0,0);
    
    //FILTER//
    for (int i =0; i<numFilters; i++){
        filter[i].setType(OFX_BIQUAD_TYPE_BANDPASS);
        filter[i].setQ(2); // 2 is good for steam power plant
        filter[i].setFc(0.8);
    }
    
    circle.setFc(.02);
    //GUI//
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(bThresh.set( "Brightness", 20, 10, 100 ));
    gui.add(FREQ.set( "Filter Frequency", .3, .0, 1.0 ));
    gui.add(Inst1.set( "Instrument1", 1, 1, 10 ));
    gui.add(Inst2.set( "Instrument2", 2, 1, 10 ));
    gui.add(Inst3.set( "Instrument3", 3, 1, 10 ));
    gui.add(Inst4.set( "Instrument4", 4, 1, 10 ));
    gui.add(Inst5.set( "Instrument5", 5, 1, 10 ));
    gui.add(Inst6.set( "Instrument6", 6, 1, 10 ));
    gui.add(Recording.set("Record", false));
}

//--------------------------------------------------------------
void ofApp::update(){
    myVideoPlayer.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //    for (int i =0; i<numFilters; i++){
    //        filter[i].setFc(FREQ);
    //    }
    //    bThresh = 100;
    unsigned char *pixels = myVideoPlayer.getPixels();
    //    currentLine.draw();
    for(int i=0; i<myRectangles.size(); i++){
        recPos = myRectangles[i].getPosition();
        ofSetColor(255,255,255);
        int avgBri = 0;
        int xWidth = myRectangles[i].getMaxX()-myRectangles[i].getMinX();
        int yWidth = myRectangles[i].getMaxY()-myRectangles[i].getMinY();
        for(int j=myRectangles[i].getMinX(); j<myRectangles[i].getMaxX(); j++){
            for(int k=myRectangles[i].getMinY(); k<myRectangles[i].getMaxY(); k++){
                int pixelPos = (k*myVideoPlayer.getWidth()+j);
                avgBri += (pixels[pixelPos*3]+pixels[pixelPos*3+1]+pixels[pixelPos*3+2])/3;
            }
        }
        avgBri /= xWidth*yWidth;
        filter[i].update(avgBri);
        float avgfBri = filter[i].value();
        cout<<avgBri<<endl;
        if(avgBri*3 > bThresh){
            ofSetColor(255, 0, 0);
            ofRect(recPos.x,recPos.y,myRectangles[i].getWidth(),myRectangles[i].getHeight());
        }
    }
    ofSetColor(255, 255, 255, 100);
    myVideoPlayer.draw(0,0);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    currentLine.addVertex(x,y);
    //    cout<<points.size()<<endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mousePos.set(x, y);
    for(int i=0; i<myRectangles.size(); i++){
        if(myRectangles[i].inside(mousePos.x, mousePos.y)){
            myRectangles.erase(myRectangles.begin()+i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    lines.push_back(currentLine);
    ofSetColor(180,180,180);
    for(int i=0; i<lines.size(); i++){
        lines[i].draw();
    }
    if (abs(currentLine.getArea())>2){
        myRectangles.push_back(currentLine.getBoundingBox());
    }
    currentLine.clear();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
