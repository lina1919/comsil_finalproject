#include "ofApp.h"
#include "math.h"
#include "time.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);// 속도를 60으로 제한한다. 
	rate = 1; //속도를 의미하는 rate를 초기에 1로 설정한다. 
	score = 0; //점수를 1로 설정한다. 
	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255); //배경을 하얀색으로 칠한다. 
	ofSetLineWidth(4); //선의 굵기를 4로 설정한다. 
	gamesound.load("gamesound.mp3"); //게임에 필요한 사운드들을 로드한다. 
	clear.load("clear.wav");
	gameover.load("gameover.mp3");
	gameend.load("images/gameover.jpg");
	currentIndex = 0; 
	draw_flag = 0; //화면에 초기 그림을 그리기 위한 flag인 draw_flag을 0으로 설정한다. 
	load_flag = 0; //데이터가 load 되었는지 확인하기 위한 load_flag을 0으로 설정한다. 
	dot_diameter = 20.0f; //점의 크기를 설정한다. 
	selection_dot = 0; 
	meetflag = 0; //물이 선과 만났는지를 나타내는 meetflag를 설정한다.
	waterfall_start_flag = 0; //물이 떨어지기 시작함을 나타내는 flag를 0으로 설정한다. 
}

//--------------------------------------------------------------
void ofApp::update() { //update는 프로그램이 실행되는 동안 계속해서 실행된다. 
	int i;
	float grad; //선분의 기울기를 뜻한다. 
	float temp; //임시 변수를 설정한다. 
	if (waterfall_start_flag) { //waterfall이 시작되었다면,

		if (wat.watery <= 728) { //그리고 물의 y 좌표값이 728보다 작다면
			for (i = 0; i < num_of_line; i++) { //선의 개수까지 반복문을 돌면서
				grad = (float)(lineseg[i].y2 - lineseg[i].y1) / (float)(lineseg[i].x2 - lineseg[i].x1); //선분의 기울기를 구한다.
				temp= grad * (float)(wat.waterx - lineseg[i].x1) - (float)wat.watery + (float)lineseg[i].y1; 
				//물의 x좌표와 선분의 첫번째 x좌표를 뺀 값을 기울기에 곱하고 그 값에 물의 y좌표와 선분의 첫번째 y좌표를 더하면 물과 선분 사이의 거리를 구할 수 있다.
				if ((temp < 9) && (temp >= 4)) { //그 temp의 값이 오차범위를 고려하여 4이상 9이하일때
					if ((wat.waterx >= lineseg[i].x1) && (wat.waterx <= lineseg[i].x2)) { //그리고 물의 x좌표가 선분의 x좌표 사이에 있을 때
						meetflag = 1; //meetflag를 set한다.
						break;
					}
				}
			}
			if (meetflag == 0) { //만나지 않았다면
				wat.watery+= rate; //값을 계속 더한다. rate는 속도를 뜻하는 변수이며 물이 떨어지는 횟수가 늘어날수록 값이 증가한다. 
			}
			if(meetflag !=0) { //만났다면
				if (grad > 0) { //기울기가 양수라면
					wat.waterx += rate;
					wat.watery += grad*rate; //물의 x,y좌표를 다시 설정한다. 
				}
				else { //기울기가 음수라면
					wat.waterx -= rate;
					wat.watery += grad*rate; //물의 x,y좌표를 다시 설정한다. 
				}
			}
			meetflag = 0; //선분을 다 지나왔다면 meetflag를 다시 0으로 설정한다. 
		}
		if (wat.watery >= 705) { //물의 y 좌표가 705 이상일때
			if (wat.waterx >= (float)(bottomline[0].x1 - 5) && wat.waterx <= (float)(bottomline[0].x2 + 5)) {
				//그리고 밑에 움직이는 선분의 x좌표 사이에 물이 있을 때(오차값을 고려하여 +- 5를 해주었다)
				clear.play(); //닿았다는 것을 나타내주기 위한 bgm을 튼다. 
				score = score + rate; //점수를 계산한다. 속도의 버림 값을 더한다. 
				waterfall_start_flag = 0; //flag을 다시 으로 설정하고 
				ofSeedRandom(); //함수를 호출한다. 
			}
			else {
				gamesound.stop(); //게임의 bgm을 끈다
				gameover.play(); //게임이 끝났음을 알려주는 bgm을 튼다. 
				draw_flag = 0; //배경을 지우기 위해 draw_flag를 0으로 설정한다. 
				game_end = 1; //게임이 끝났음을 나타내는 변수를 1로 설정한다. 
				waterfall_start_flag = 0; //이 flag도 0으로 설정한다. 
			}
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(127, 23, 31);  // 색을 brown으로 설정한다. 

	// 천장과 바닥을 그린다. 
	ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofSetLineWidth(5);
	//게임이 끝났다면
	if (game_end) {
		draw_flag = 0; //배경을 지우기 위해 draw_flag를 0으로 설정한다.
		ofClear(255,255,255); //흰색으로 clear한다.
		ofSetColor(255, 255, 255); //색깔을 흰색으로 설정한다.
		gameend.draw(10,100,1000,600); //미리 첨부해둔 사진을 load한다. 
		ofSetColor(255, 0, 0); //색을 빨간색으로 바꾼다.
		//최종 속도와 점수를 화면에 나타낸다.
		ofDrawBitmapString("Final Score : ", 450, 550);
		ofDrawBitmapString(score, 590, 550);
		ofDrawBitmapString("Final Speed : ", 450, 575);
		ofDrawBitmapString(rate,570, 575);
	}
	//최초 선분과 점을 그린다. 
	if (draw_flag) {
		//빨간색으로 나의 점수와 현재 속도를 화면에 나타낸다. 
		ofSetColor(255, 0, 0);
		ofDrawBitmapString("Your Score : ", 830, 150);
		ofDrawBitmapString(score, 950, 150);
		ofDrawBitmapString("Current Speed : ", 810, 175);
		ofDrawBitmapString(rate, 950, 175);
		
		int i;
		int num = 0;
		ofSetColor(127, 23, 31);
		//반복문을 돌면서 미리 저장해둔 선분들의 정보를 화면에 그린다. 
		for (i = 0; i < num_of_line; i++) {
			ofDrawLine(lineseg[i].x1, lineseg[i].y1, lineseg[i].x2, lineseg[i].y2);
		}
		//반복문을 돌면서 점들을 화면에 그린다. 
		for (i = 0; i < num_of_dot; i++) {
			ofSetColor(0, 0, 255);
			ofDrawCircle(dot[i].x1, dot[i].y1, dot_diameter / 2);
		}
		//색을 바꾼다 .
		ofSetColor(0, 255, 0);
		//선분의 굵기를 바꾸고 게임을 위한 밑 선분을 화면에 나타낸다.
		ofSetLineWidth(10);
		
		ofDrawLine(bottomline[num].x1, bottomline[num].y1, bottomline[num].x2, bottomline[num].y2);
		/* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
		 Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
		 */

		 // 2nd week portion.
		ofSetLineWidth(2);
		if (waterfall_start_flag) {

			ofSetColor(0, 0, 255);
			ofDrawCircle(wat.waterx, wat.watery, dot_diameter / 2);

		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'v') {
		// HACK: only needed on windows, when using ofSetAutoBackground(false)
		glReadBuffer(GL_FRONT);
		ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
	}
	//오른쪽 key가 눌렸다면 bottom line을 오른쪽으로 이동한다. 
	if (key == OF_KEY_RIGHT) {
		draw_flag = 1;
		bottomline[0].x1 = bottomline[0].x1 + 15;
		bottomline[0].x2 = bottomline[0].x2 + 15;
	}
	//왼쪽 키가 눌렸다면 bottomline을 오른쪽으로 이동한다. 
	if (key == OF_KEY_LEFT) {
		draw_flag = 1;
		bottomline[0].x1 = bottomline[0].x1 - 15;
		bottomline[0].x2 = bottomline[0].x2 - 15;
	}
	//q를 누른다면 할당했던 메모리들을 해제하고 게임을 종료한다. 
	if (key == 'q') {
		if (!load_flag) return;
		// Reset flags
		draw_flag = 0;
		waterfall_start_flag = 0;
		// Free the dynamically allocated memory exits.
		if (lineseg != NULL) {
			free(lineseg);
			lineseg = NULL;
		}
		if (bottomline != NULL) {
			free(bottomline);
			bottomline = NULL;
		}
		cout << "Memory for line segment has been freed." << endl;
		if (dot != NULL) {
			free(dot);
			dot = NULL;
		}
		cout << "Memory for dot has been freed." << endl;
		_Exit(0);
	}
	//d를 누른다면 화면에 선분과 점을 표시한다. 
	if (key == 'd') {
		if (!load_flag) return;
		gamesound.play();
		draw_flag = 1;
		target_dot.x = dot[selection_dot].x1;
		target_dot.y = dot[selection_dot].y1;
		/* COMSIL1-TODO 2: This is draw control part.
		You should draw only after when the key 'd' has been pressed.
		*/
	}
	//s를 누른다면 게임을 시작한다. 
	if (key == 's') {
		srand(time(NULL));
		int randtemp;
		randtemp = rand() % num_of_dot;
		target_dot.x = dot[randtemp].x1;
		target_dot.y = dot[randtemp].y1;
		if (load_flag) {
			if (draw_flag) {
				initializeWaterLines();
				waterfall_start_flag = 1;
			}
		}
		// 2nd week portion.
	}
	if (key == 'e') {
		if (draw_flag)
			waterfall_start_flag = 0;
		// 2nd week portion.
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	//ㅣ을 누른다면 선택한 파일의 정보를 불러와 미리 설정해놓은 변수에 저장한다. 
	if (key == 'l') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			processOpenFileSelection(openFileResult);
			load_flag = 1;
		}
	}

	/* COMSIL1-TODO 4: This is selection dot control part.
	 You can select dot in which water starts to flow by left, right direction key (<- , ->).
	 */

	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
//파일의 정보를 읽어 저장한다. 
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
	//Path to the comma delimited file
	//string fileName = "input.txt";

	string fileName = openFileResult.getName();
	ofFile file(fileName);

	if (!file.exists()) {
		cout << "Target file does not exists." << endl;
	}
	else {
		cout << "We found the target file." << endl;
	}

	ofBuffer buffer(file);

	/* This variable is for indicating which type of input is being received.
	 IF input_type == 0, then work of getting line input is in progress.
	 IF input_type == 1, then work of getting dot input is in progress.
	 */
	int input_type = 0;
	int idx = 0;

	/* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
	 You must maintain those information. But, currently below code is not complete.
	 Also, note that all of coordinate should not be out of screen size.
	 However, all of coordinate do not always turn out to be the case.
	 So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
	*/


	// Read file line by line
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;

		// Split line into strings
		vector<string> words = ofSplitString(line, " ");
		if (!bottomline) {
			bottomline = (LineSegment*)malloc(sizeof(LineSegment) * 1);
			bottomline[0].x1 = 300;
			bottomline[0].y1 = 710;
			bottomline[0].x2 = 420;
			bottomline[0].y2 = 710;
		}
		if (words.size() == 1) {
			if (input_type == 0) { // Input for the number of lines.
				num_of_line = atoi(words[0].c_str());
				cout << "The number of line is: " << num_of_line << endl;
				if (!lineseg)
					lineseg = (LineSegment*)malloc(sizeof(LineSegment) * num_of_line);
			}
			else { // Input for the number of dots.
				num_of_dot = atoi(words[0].c_str());
				cout << "The number of dot is: " << num_of_dot << endl;
				if (!dot)
					dot = (Dot*)malloc(sizeof(Dot) * num_of_dot);
			}
		}
		else if (words.size() >= 2) {
			int x1, y1, x2, y2;
			if (input_type == 0) { // Input for actual information of lines
				lineseg[idx].x1 = atoi(words[0].c_str());
				lineseg[idx].y1 = atoi(words[1].c_str());
				lineseg[idx].x2 = atoi(words[2].c_str());
				lineseg[idx].y2 = atoi(words[3].c_str());
				// Out-of-range error handling
				if (lineseg[idx].x1 < 0 || lineseg[idx].x1 > ofGetWidth()) {
					cout << "Out-of-range: " << lineseg[idx].x1 << endl;
					return;
				}
				else if (lineseg[idx].y1 < 0 || lineseg[idx].y1 > ofGetHeight()) {
					cout << "Out-of-range: " << lineseg[idx].y1 << endl;
					return;
				}
				else if (lineseg[idx].x2 < 0 || lineseg[idx].x2 > ofGetWidth()) {
					cout << "Out-of-range: " << lineseg[idx].x2 << endl;
					return;
				}
				else if (lineseg[idx].y2 < 0 || lineseg[idx].y2 > ofGetHeight()) {
					cout << "Out-of-range: " << lineseg[idx].y2 << endl;
					return;
				}
				idx++;
				if (idx >= num_of_line) {
					input_type = 1;
					idx = 0;
				}
			}

			else { // Input for actual information of dots.
				dot[idx].x1 = atoi(words[0].c_str());
				dot[idx].y1 = atoi(words[1].c_str());

				idx++;

				if (idx >= num_of_dot)
					input_type = 0;
			}
		} // End of else if.
	} // End of for-loop (Read file line by line).

	initializeWaterLines();
}
//물줄기를 초기화하여 선택한 점에서 물이 나오게한다. 
void ofApp::initializeWaterLines() {
	//wl[i].start_dot.x = ofRandom(dot[selection_dot].x1-dot_diameter/2, dot[selection_dot].x1+dot_diameter/2);
	wat.waterx = target_dot.x;
	wat.watery = target_dot.y;
}
//랜덤하게 점들을 골라서 이를 target_dot에 저장한다. 그 다음 물줄기를 초기화한다. 
void ofApp::ofSeedRandom() {
	rate = rate + 0.2;
	int randtemp = (int)ofRandom(0, num_of_dot);
	target_dot.x = dot[randtemp].x1;
	target_dot.y = dot[randtemp].y1;
	if (load_flag) {
		if (draw_flag) {
			initializeWaterLines();
			waterfall_start_flag = 1;
		}
	}
}
