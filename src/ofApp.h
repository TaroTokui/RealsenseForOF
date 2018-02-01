#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include <librealsense2/rs.hpp>

//static const int COLOR_W = 1920;
//static const int COLOR_H = 1080;
//static const int FPS_COLOR = 30;
//
//static const int DEPTH_W = 1280;
//static const int DEPTH_H = 720;
//static const int FPS_DEPTH = 30;

static const int COLOR_W = 640;
static const int COLOR_H = 480;
static const int FPS_COLOR = 30;

static const int DEPTH_W = 640;
static const int DEPTH_H = 480;
static const int FPS_DEPTH = 30;

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void update_camera_params_color();
		void update_camera_params_depth();
		
private:
	rs2::pipeline pipe;
	rs2::colorizer color_map;

	rs2::frameset data;
	rs2::frame depth, color;

	rs2::pipeline_profile selection;
	rs2::device selected_device;
	vector<rs2::sensor> sensors;

	ofImage depth_img, color_img;

	//gui settings--------------------
	ofxPanel gui;
	ofParameterGroup color_params, depth_params;
	bool showGui;

	ofParameter<bool> backlight_compensation_c;
	ofParameter<int> brightness_c;
	ofParameter<int> contrast_c;
	ofParameter<int> exposure_c;
	ofParameter<int> gain_c;
	ofParameter<int> gamma_c;
	ofParameter<int> hue_c;
	ofParameter<int> saturation_c;
	ofParameter<int> sharpness_c;
	ofParameter<int> white_balance_c;
	ofParameter<bool> enable_auto_exposure_c;
	ofParameter<bool> enable_auto_white_balance_c;

};
