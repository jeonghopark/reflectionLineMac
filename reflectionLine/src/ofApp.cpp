#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofSetDataPathRoot("../Resources/data/");

    
    ofSetFrameRate(60);
    ofBackground( 0 );
    
//    ofDisableArbTex();
    
//    ofSetVerticalSync(true);
    
    video.load("27EG-28-EG-58_HOTRODS_720p.mp4"); //27EG-28-EG-58_HOTRODS_720p.mp4, SF144.mov, PET0981_R-1_LA_720p.mp4
    video.play();
    
    videoWidth = video.getWidth();
    videoHeight = video.getHeight();
    
	videoLeftHalf 	= new unsigned char[videoWidth*videoHeight*3];
	videoRightHalf 	= new unsigned char[videoWidth*videoHeight*3];
    pixels = new unsigned char[videoWidth*videoHeight*3];
    
	videoLeftTexture.allocate(videoWidth/2,videoHeight, GL_RGB);
	videoRightTexture.allocate(videoWidth/2,videoHeight, GL_RGB);
    
    ofNoFill();

    videoLeftPos = 360;
    videoRightPos = videoLeftPos;
    
    for (int i=0; i<ofGetHeight(); i++) {
        randomYPos.push_back(ofRandom(ofGetHeight()));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
    
    if (video.isFrameNew()) {
        
        pixels = video.getPixels();

        for (int i=0; i<videoHeight; i++){
            for (int j=0; j < videoWidth*3/2; j++){
                int _index = i * videoWidth*3 + j;
                videoLeftHalf[_index] = pixels[_index];
            }
        }
        videoLeftTexture.loadData(videoLeftHalf, videoWidth, videoHeight, GL_RGB);
        
        for (int i=0; i<videoHeight; i++){
            for (int j=videoWidth*3/2; j < videoWidth*3; j++){
                int _index = i * videoWidth*3 + j;
                videoRightHalf[_index] = pixels[_index];
            }
        }
        videoRightTexture.loadData(videoRightHalf, videoWidth, videoHeight, GL_RGB);
        
        
        if (colorNumber.size()>videoHeight) {
            pixelColor.clear();
            colorNumber.clear();
            inputVideo.clear();
            sortVideo.clear();
        }
        
        
        for (int i=0; i<videoHeight; i++){
            int _index = videoWidth*3 * i + videoWidth*3/2;
            
            ofColor _temp;
            _temp.r = pixels[_index] << 0;
            _temp.g = pixels[_index+1] << 0;
            _temp.b = pixels[_index+2] << 0;
            pixelColor.push_back(_temp);
            
            float _sum = (pixels[_index] << 0) + (pixels[_index+1] << 0) + (pixels[_index+2] << 0);
            colorNumber.push_back(_sum);
            
            InputMovie _tempInputVideo;
            _tempInputVideo.color.r = pixels[_index] << 0;
            _tempInputVideo.color.g = pixels[_index+1] << 0;
            _tempInputVideo.color.b = pixels[_index+2] << 0;
            _tempInputVideo.index = i;
            inputVideo.push_back(_tempInputVideo);
            
            SortVideo _tempsortVideo;
            _tempsortVideo.sum = (pixels[_index] << 0) + (pixels[_index+1] << 0) + (pixels[_index+2] << 0);
            _tempsortVideo.index = i;
            sortVideo.push_back(_tempsortVideo);
            
        }
        
        std::sort (sortVideo.begin(), sortVideo.end(), myobject);

    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(0, 0);
	
    videoLeftTexture.draw(0-videoLeftPos,0);
    videoRightTexture.draw(ofGetWidth()-videoWidth+videoRightPos,0);

    ofPopMatrix();
    
    
    ofPushMatrix();
    ofPushStyle();
    for (int i=0; i<pixelColor.size(); i+=1) {
        ofSetColor(pixelColor[i]);
        ofPoint _leftPoint = ofPoint(videoWidth/2-videoLeftPos, i);
        ofPoint _rightPoint = ofPoint(ofGetWidth()-videoWidth/2+videoRightPos, i);
        ofLine( _leftPoint, _rightPoint );

        ofSetCurveResolution(32);
//        ofBezier(_leftPoint.x, _leftPoint.y, ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2, _rightPoint.x, _rightPoint.y);
    }
    ofPopStyle();
    ofPopMatrix();
    
    
//
//    
//    ofPushMatrix();
//    ofPushStyle();
//    ofFill();
//    ofSetColor(ofColor::fromHsb(0, 0, 0, 120));
//    ofRect(ofGetWidth()/2-20, 0, 40, ofGetHeight());
//    ofPopStyle();
//    ofPopMatrix();
    

    
    if (sortVideo.size()>0) {
        
        ofPushMatrix();
        ofPushStyle();
        ofFill();
        ofSetColor(ofColor::fromHsb(0, 0, 0, 255));
        int _darkLineIndex = sortVideo.at(0).index;
        int _yPosDarkLine = inputVideo.at(_darkLineIndex).index;
        //    ofCircle(ofGetWidth()/2, _yPosDarkLine, 4);
        ofRect( ofGetWidth()/2-20, _yPosDarkLine-2, 40, 4 );
        ofPopStyle();
        ofPopMatrix();
        
        
        ofPushMatrix();
        ofPushStyle();
        ofFill();
        ofSetColor(ofColor::fromHsb(90, 0, 255, 255));
        int _brightLineIndex = sortVideo.at(sortVideo.size()-1).index;
        int _yPosBrightLine = inputVideo.at(_brightLineIndex).index;
        //    ofCircle(ofGetWidth()/2, _yPosBrightLine, 4);
        ofRect( ofGetWidth()/2-20, _yPosBrightLine-2, 40, 4 );
        ofPopStyle();
        ofPopMatrix();

    }

    
    ofPushMatrix();
    ofPushStyle();
    ofFill();
    ofSetColor( 0 );
    ofDrawRectangle( 0, video.getHeight(), video.getWidth(), ofGetHeight());
    ofPopStyle();
    ofPopMatrix();

    
}


void ofApp::refelction180(unsigned char * pixels){
    
    int _totalIndex = videoWidth*videoHeight*3;
    
    for (int j = videoHeight/2-2; j < videoHeight/2; j++){
        for (int i = 0; i < videoWidth*3; i++){
            int _index = (j * videoWidth*3 + i);
            
            videoRightHalf[_index-(videoHeight/2*videoWidth*3-(videoWidth*3)*2)] = pixels[_index];
        }
    }
    
    for (int j = 0; j < 1; j++){
        for (int i = 0; i < videoWidth*3; i++){
            int _index = (j * videoWidth*3 + i);
            
            videoRightHalf[_index-(videoHeight/2*videoWidth*3-(videoWidth*3)*(videoHeight-1))] = pixels[_index];
        }
    }
    
    videoRightTexture.loadData(videoRightHalf, videoWidth, videoHeight/2, GL_RGB);
    
}

void ofApp::refelction180Draw(){
 	videoRightTexture.draw(0,videoHeight/2+10,videoWidth,videoHeight/2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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