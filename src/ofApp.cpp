#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// allocate ofImage
	color_img.allocate(COLOR_W, COLOR_H, OF_IMAGE_COLOR);
	depth_img.allocate(DEPTH_W, DEPTH_H, OF_IMAGE_COLOR);

	//Create a configuration for configuring the pipeline with a non default profile
	rs2::config cfg;

	//Add desired streams to configuration
	cfg.enable_stream(RS2_STREAM_COLOR, COLOR_W, COLOR_H, RS2_FORMAT_RGB8, FPS_COLOR);
	//cfg.enable_stream(RS2_STREAM_DEPTH, DEPTH_W, DEPTH_H, RS2_FORMAT_Z16, FPS_DEPTH);

	// The pipeline profile includes a device and a selection of active streams, with specific profile.
	selection = pipe.start(cfg);

	// Retrieve the device used by the pipeline.
	selected_device = selection.get_device();

	// the list of adjacent devices
	sensors = selected_device.query_sensors();

	//cout << "sensor count " << sensors.size() << endl;

	// init gui
	auto s = sensors[1];
	int min = 0;
	int max = 0;

	color_params.setName("rgb camera params");
	if (s.supports(RS2_OPTION_BACKLIGHT_COMPENSATION))
	{
		auto range = s.get_option_range(RS2_OPTION_BACKLIGHT_COMPENSATION);
		color_params.add(backlight_compensation_c.set("backlight_compensation", range.def));
	}
	if (s.supports(RS2_OPTION_BRIGHTNESS))
	{
		auto range = s.get_option_range(RS2_OPTION_BRIGHTNESS);
		color_params.add(brightness_c.set("brightness", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_CONTRAST))
	{
		auto range = s.get_option_range(RS2_OPTION_CONTRAST);
		color_params.add(contrast_c.set("contrast", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_EXPOSURE))
	{
		auto range = s.get_option_range(RS2_OPTION_EXPOSURE);
		color_params.add(exposure_c.set("exposure", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_GAIN))
	{
		auto range = s.get_option_range(RS2_OPTION_GAIN);
		color_params.add(gain_c.set("gain", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_GAMMA))
	{
		auto range = s.get_option_range(RS2_OPTION_GAMMA);
		color_params.add(gamma_c.set("gamma", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_HUE))
	{
		auto range = s.get_option_range(RS2_OPTION_HUE);
		color_params.add(hue_c.set("hue", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_SATURATION))
	{
		auto range = s.get_option_range(RS2_OPTION_SATURATION);
		color_params.add(saturation_c.set("saturation", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_SHARPNESS))
	{
		auto range = s.get_option_range(RS2_OPTION_SHARPNESS);
		color_params.add(sharpness_c.set("sharpness", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_WHITE_BALANCE))
	{
		auto range = s.get_option_range(RS2_OPTION_WHITE_BALANCE);
		color_params.add(white_balance_c.set("white_balance", range.def, range.min, range.max));
	}
	if (s.supports(RS2_OPTION_ENABLE_AUTO_EXPOSURE))
	{
		auto range = s.get_option_range(RS2_OPTION_ENABLE_AUTO_EXPOSURE);
		color_params.add(enable_auto_exposure_c.set("enable_auto_exposure", range.def));
	}
	if (s.supports(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE))
	{
		auto range = s.get_option_range(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE);
		color_params.add(enable_auto_white_balance_c.set("enable_auto_white_balance", range.def));
	}

	gui.setup(color_params, "rgb_camera_settings.xml");
	gui.loadFromFile("rgb_camera_settings.xml");
	showGui = true;

	//for (auto s : sensors)
	//{
	//	cout << s.get_info(RS2_CAMERA_INFO_NAME) << endl;

	//	// 1個目はstereo camera
	//	// 2籠めはcolor camera
	//	if (s.supports(RS2_OPTION_EXPOSURE))
	//	{
	//		auto range = s.get_option_range(RS2_OPTION_EXPOSURE);
	//		//REQUIRE_NOTHROW(s.set_option(RS2_OPTION_EXPOSURE, range.min));

	//		s.set_option(RS2_OPTION_EXPOSURE, 850);
	//	}

	//}

//	auto color_sensor = selected_device.first<rs2::sensor>();
//
//
//	// white balanceを設定できない？？
//	// カラーカメラだけにする必要がある？
//	if (color_sensor.supports(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE))
//	{
//		cout << "current auto wb: " << color_sensor.get_option(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE) << endl;
//	}
//
//	if (color_sensor.supports(RS2_OPTION_WHITE_BALANCE))
//	{
//		cout << "current wb: " << color_sensor.get_option(RS2_OPTION_WHITE_BALANCE) << endl;
//	}
//#if 1
//	if (color_sensor.supports(RS2_OPTION_EXPOSURE))
//	{
//		cout << "current exposure: " << color_sensor.get_option(RS2_OPTION_EXPOSURE) << endl;
//
//		rs2::option_range range;
//		range = color_sensor.get_option_range(RS2_OPTION_EXPOSURE);
//		color_sensor.set_option(RS2_OPTION_EXPOSURE, 85000);
//
//		cout << "new exposure: " << color_sensor.get_option(RS2_OPTION_EXPOSURE) << endl;
//
//		cout << "min:" << range.min << " max:" << range.max << " def:" << range.def << " step:" << range.step << endl;
//	}
//#endif
//
//#if 1
//	if (color_sensor.supports(RS2_OPTION_GAIN))
//	{
//		cout << "current gain: " << color_sensor.get_option(RS2_OPTION_GAIN) << endl;
//
//		rs2::option_range range;
//		range = color_sensor.get_option_range(RS2_OPTION_GAIN);
//		color_sensor.set_option(RS2_OPTION_GAIN, 16);
//
//		cout << "new gain: " << color_sensor.get_option(RS2_OPTION_GAIN) << endl;
//
//		cout << "min:" << range.min << " max:" << range.max << " def:" << range.def << " step:" << range.step << endl;
//	}
//#endif

	// セットした情報をpipe lineに反映させる処理が必要？
	// RealSense viewerのコードを読む

	// color cameraのstreamに対して設定しないとだめ？

}

//--------------------------------------------------------------
void ofApp::update(){

	update_camera_params_color();

//	auto color_sensor = selected_device.first<rs2::sensor>();
//
//#if 1
//	if (color_sensor.supports(RS2_OPTION_EXPOSURE))
//	{
//		color_sensor.set_option(RS2_OPTION_EXPOSURE, 85000);
//	}
//#endif
//
//#if 1
//	if (color_sensor.supports(RS2_OPTION_GAIN))
//	{
//		color_sensor.set_option(RS2_OPTION_GAIN, 16);
//	}
//#endif

	data = pipe.wait_for_frames();
	//depth = color_map(data.get_depth_frame());

	//depth_img.setFromPixels((unsigned char*)depth.get_data(), DEPTH_W, DEPTH_H, OF_IMAGE_COLOR);

	color = data.get_color_frame();
	color_img.setFromPixels((unsigned char*)color.get_data(), COLOR_W, COLOR_H, OF_IMAGE_COLOR);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255);
	color_img.draw(0, 0, 640, 480);
	//depth_img.draw(0, 0, 640, 480);

	if (showGui)
	{
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::update_camera_params_color()
{
	// sensors[0]: stereo camera
	// sensors[1]: rgb camera
	if (sensors.size() < 2) return;

	auto s = sensors[1];

	if (s.supports(RS2_OPTION_BACKLIGHT_COMPENSATION))
	{
		s.set_option(RS2_OPTION_BACKLIGHT_COMPENSATION, backlight_compensation_c);
	}
	if (s.supports(RS2_OPTION_BRIGHTNESS))
	{
		s.set_option(RS2_OPTION_BRIGHTNESS, brightness_c);
	}
	if (s.supports(RS2_OPTION_CONTRAST))
	{
		s.set_option(RS2_OPTION_CONTRAST, contrast_c);
	}
	if (s.supports(RS2_OPTION_EXPOSURE))
	{
		s.set_option(RS2_OPTION_EXPOSURE, exposure_c);
	}
	if (s.supports(RS2_OPTION_GAIN))
	{
		s.set_option(RS2_OPTION_GAIN, gain_c);
	}
	if (s.supports(RS2_OPTION_GAMMA))
	{
		s.set_option(RS2_OPTION_GAMMA, gamma_c);
	}
	if (s.supports(RS2_OPTION_HUE))
	{
		s.set_option(RS2_OPTION_HUE, hue_c);
	}
	if (s.supports(RS2_OPTION_SATURATION))
	{
		s.set_option(RS2_OPTION_SATURATION, saturation_c);
	}
	if (s.supports(RS2_OPTION_SHARPNESS))
	{
		s.set_option(RS2_OPTION_SHARPNESS, sharpness_c);
	}
	if (s.supports(RS2_OPTION_WHITE_BALANCE))
	{
		auto range = s.get_option_range(RS2_OPTION_WHITE_BALANCE);
		s.set_option(RS2_OPTION_WHITE_BALANCE, int(white_balance_c / range.step) * range.step);
	}
	if (s.supports(RS2_OPTION_ENABLE_AUTO_EXPOSURE) && enable_auto_exposure_c)
	{
		s.set_option(RS2_OPTION_ENABLE_AUTO_EXPOSURE, enable_auto_exposure_c);
	}
	if (s.supports(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE))
	{
		s.set_option(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE, enable_auto_white_balance_c);
	}

}

//--------------------------------------------------------------
void ofApp::update_camera_params_depth()
{
	if (sensors.size() < 2) return;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{
	case 'g':
		showGui = !showGui;
		break;

	//case ' ':
	//	update_camera_params_color();
	//	break;

	default:
		break;
	}
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
