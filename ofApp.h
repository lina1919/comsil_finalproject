#pragma once

#include "ofMain.h"
#include <cstdlib>
using namespace std;
typedef struct LineSegment {
	int x1;
	int y1;
	int x2;
	int y2;
} linesegment;

typedef struct Dot {
	int x1;
	int y1;
} dot;
typedef struct target {
	int x;
	int y;
} target;
typedef struct WaterL {
	float waterx;
	float watery;
}waterl;
class ofApp : public ofBaseApp {
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
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void ofSeedRandom();
	int score;
	/* WaterFall-related member variables Regions */

	// flag variables
	int draw_flag;
	int load_flag;

	// Line segment and dot related variables

	int num_of_line, num_of_dot;
	float dot_diameter;
	int waterfall_start_flag;
	int meetflag;
	int currentIndex;
	int selection_dot;
	float rate;
	int game_end;
	target target_dot;
	linesegment* lineseg;
	dot* dot;
	waterl wat;
	linesegment* bottomline;
	/* WaterFall-related member functions */
	ofSoundPlayer gamesound;
	ofSoundPlayer gameover;
	ofSoundPlayer clear;
	ofImage gameend;
	ofImage gamestart;
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.
	
};
