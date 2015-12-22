#pragma once

#include "ofMain.h"
#include "ofxSecondWindow.h"
#include "ofxBiquadFilter.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    ofParameter<int> gridX;
    ofParameter<int> gridY;
    ofParameter<int> bThresh;
    ofParameter<float> FREQ;
    ofParameter<int> Inst1;
    ofParameter<int> Inst2;
    ofParameter<int> Inst3;
    ofParameter<int> Inst4;
    ofParameter<int> Inst5;
    ofParameter<int> Inst6;
    ofParameter<bool>Grid;
    ofParameter<bool>Recording;
    
    
    
    ofxPanel gui;
    
    
    ofVideoPlayer myVideoPlayer;
    int numFilters;
    ofxBiquadFilter1f filter[40];
    ofxBiquadFilter1f circle;
    
    vector<ofPolyline> lines;
    vector<ofRectangle> myRectangles;
    vector<int> lastBrightness;
    ofPolyline currentLine;
    ofVec2f mousePos;
    ofVec2f recPos;
    
    int brightness;
    
    //Drag Rect//
    ofVec2f rectStart;
    ofVec2f rectEnd;
    
    
};
