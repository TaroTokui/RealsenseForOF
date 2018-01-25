#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	pipe.start();

	w = 1280;
	h = 720;
	img.allocate(w, h, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){

	data = pipe.wait_for_frames();
	depth = color_map(data.get_depth_frame());

	//std::cout << depth.get_frame_number() << std::endl;

	img.setFromPixels((unsigned char*)depth.get_data(), w, h, OF_IMAGE_COLOR);

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255);
	img.draw(0, 0);
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
