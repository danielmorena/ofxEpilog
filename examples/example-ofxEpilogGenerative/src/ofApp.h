#pragma once

#include "ofMain.h"

#include "ofxEpilog.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

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
    
        // epilog laser object
        ofxEpilog epilogLaser;
    
        // process parameters of each output
        OutputConfig out_conf;
    
        // polyline for cutting process
        //ofPolyline line;
    
        vector <ofPoint> trail;
    
        bool send_vertexes = false;
        float dist_threshold = 2;
};