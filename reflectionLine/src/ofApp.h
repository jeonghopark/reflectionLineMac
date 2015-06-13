#pragma once

#include "ofMain.h"


struct InputMovie {
    ofColor color;
    int index;
};

struct SortVideo {
    float sum;
    int index;
    
};

struct myclass {
    bool operator() (SortVideo _tmpsortVideoL, SortVideo _tmpsortVideoR) {
        return (_tmpsortVideoL.sum<_tmpsortVideoR.sum);
    }
} myobject;


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    

    ofVideoPlayer video;

    unsigned char * 	videoLeftHalf;
    unsigned char * 	videoRightHalf;
    ofTexture			videoLeftTexture;
    ofTexture			videoRightTexture;

    int videoWidth;
    int videoHeight;
    
    int videoLeftPos;
    int videoRightPos;
    
    void refelction180(unsigned char * pixels);
    void refelction180Draw();
    
    vector<ofColor> pixelColor;
    vector<float> colorNumber;
    vector<float> randomYPos;
    unsigned char * pixels;
    
    
    vector<InputMovie> inputVideo;
    vector<SortVideo> sortVideo;
};
