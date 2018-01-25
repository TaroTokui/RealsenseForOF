#pragma once

#include "ofMain.h"

#include <librealsense2/rs.hpp>


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
		
private:
	rs2::pipeline pipe;
	rs2::colorizer color_map;

	rs2::frameset data;
	rs2::frame depth;

	int w, h;

	ofImage img;

};
