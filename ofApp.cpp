#include "ofApp.h"
#include "math.h"
#include "time.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);// �ӵ��� 60���� �����Ѵ�. 
	rate = 1; //�ӵ��� �ǹ��ϴ� rate�� �ʱ⿡ 1�� �����Ѵ�. 
	score = 0; //������ 1�� �����Ѵ�. 
	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255); //����� �Ͼ������ ĥ�Ѵ�. 
	ofSetLineWidth(4); //���� ���⸦ 4�� �����Ѵ�. 
	gamesound.load("gamesound.mp3"); //���ӿ� �ʿ��� ������� �ε��Ѵ�. 
	clear.load("clear.wav");
	gameover.load("gameover.mp3");
	gameend.load("images/gameover.jpg");
	currentIndex = 0; 
	draw_flag = 0; //ȭ�鿡 �ʱ� �׸��� �׸��� ���� flag�� draw_flag�� 0���� �����Ѵ�. 
	load_flag = 0; //�����Ͱ� load �Ǿ����� Ȯ���ϱ� ���� load_flag�� 0���� �����Ѵ�. 
	dot_diameter = 20.0f; //���� ũ�⸦ �����Ѵ�. 
	selection_dot = 0; 
	meetflag = 0; //���� ���� ���������� ��Ÿ���� meetflag�� �����Ѵ�.
	waterfall_start_flag = 0; //���� �������� �������� ��Ÿ���� flag�� 0���� �����Ѵ�. 
}

//--------------------------------------------------------------
void ofApp::update() { //update�� ���α׷��� ����Ǵ� ���� ����ؼ� ����ȴ�. 
	int i;
	float grad; //������ ���⸦ ���Ѵ�. 
	float temp; //�ӽ� ������ �����Ѵ�. 
	if (waterfall_start_flag) { //waterfall�� ���۵Ǿ��ٸ�,

		if (wat.watery <= 728) { //�׸��� ���� y ��ǥ���� 728���� �۴ٸ�
			for (i = 0; i < num_of_line; i++) { //���� �������� �ݺ����� ���鼭
				grad = (float)(lineseg[i].y2 - lineseg[i].y1) / (float)(lineseg[i].x2 - lineseg[i].x1); //������ ���⸦ ���Ѵ�.
				temp= grad * (float)(wat.waterx - lineseg[i].x1) - (float)wat.watery + (float)lineseg[i].y1; 
				//���� x��ǥ�� ������ ù��° x��ǥ�� �� ���� ���⿡ ���ϰ� �� ���� ���� y��ǥ�� ������ ù��° y��ǥ�� ���ϸ� ���� ���� ������ �Ÿ��� ���� �� �ִ�.
				if ((temp < 9) && (temp >= 4)) { //�� temp�� ���� ���������� ����Ͽ� 4�̻� 9�����϶�
					if ((wat.waterx >= lineseg[i].x1) && (wat.waterx <= lineseg[i].x2)) { //�׸��� ���� x��ǥ�� ������ x��ǥ ���̿� ���� ��
						meetflag = 1; //meetflag�� set�Ѵ�.
						break;
					}
				}
			}
			if (meetflag == 0) { //������ �ʾҴٸ�
				wat.watery+= rate; //���� ��� ���Ѵ�. rate�� �ӵ��� ���ϴ� �����̸� ���� �������� Ƚ���� �þ���� ���� �����Ѵ�. 
			}
			if(meetflag !=0) { //�����ٸ�
				if (grad > 0) { //���Ⱑ ������
					wat.waterx += rate;
					wat.watery += grad*rate; //���� x,y��ǥ�� �ٽ� �����Ѵ�. 
				}
				else { //���Ⱑ �������
					wat.waterx -= rate;
					wat.watery += grad*rate; //���� x,y��ǥ�� �ٽ� �����Ѵ�. 
				}
			}
			meetflag = 0; //������ �� �����Դٸ� meetflag�� �ٽ� 0���� �����Ѵ�. 
		}
		if (wat.watery >= 705) { //���� y ��ǥ�� 705 �̻��϶�
			if (wat.waterx >= (float)(bottomline[0].x1 - 5) && wat.waterx <= (float)(bottomline[0].x2 + 5)) {
				//�׸��� �ؿ� �����̴� ������ x��ǥ ���̿� ���� ���� ��(�������� ����Ͽ� +- 5�� ���־���)
				clear.play(); //��Ҵٴ� ���� ��Ÿ���ֱ� ���� bgm�� ư��. 
				score = score + rate; //������ ����Ѵ�. �ӵ��� ���� ���� ���Ѵ�. 
				waterfall_start_flag = 0; //flag�� �ٽ� ���� �����ϰ� 
				ofSeedRandom(); //�Լ��� ȣ���Ѵ�. 
			}
			else {
				gamesound.stop(); //������ bgm�� ����
				gameover.play(); //������ �������� �˷��ִ� bgm�� ư��. 
				draw_flag = 0; //����� ����� ���� draw_flag�� 0���� �����Ѵ�. 
				game_end = 1; //������ �������� ��Ÿ���� ������ 1�� �����Ѵ�. 
				waterfall_start_flag = 0; //�� flag�� 0���� �����Ѵ�. 
			}
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(127, 23, 31);  // ���� brown���� �����Ѵ�. 

	// õ��� �ٴ��� �׸���. 
	ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofSetLineWidth(5);
	//������ �����ٸ�
	if (game_end) {
		draw_flag = 0; //����� ����� ���� draw_flag�� 0���� �����Ѵ�.
		ofClear(255,255,255); //������� clear�Ѵ�.
		ofSetColor(255, 255, 255); //������ ������� �����Ѵ�.
		gameend.draw(10,100,1000,600); //�̸� ÷���ص� ������ load�Ѵ�. 
		ofSetColor(255, 0, 0); //���� ���������� �ٲ۴�.
		//���� �ӵ��� ������ ȭ�鿡 ��Ÿ����.
		ofDrawBitmapString("Final Score : ", 450, 550);
		ofDrawBitmapString(score, 590, 550);
		ofDrawBitmapString("Final Speed : ", 450, 575);
		ofDrawBitmapString(rate,570, 575);
	}
	//���� ���а� ���� �׸���. 
	if (draw_flag) {
		//���������� ���� ������ ���� �ӵ��� ȭ�鿡 ��Ÿ����. 
		ofSetColor(255, 0, 0);
		ofDrawBitmapString("Your Score : ", 830, 150);
		ofDrawBitmapString(score, 950, 150);
		ofDrawBitmapString("Current Speed : ", 810, 175);
		ofDrawBitmapString(rate, 950, 175);
		
		int i;
		int num = 0;
		ofSetColor(127, 23, 31);
		//�ݺ����� ���鼭 �̸� �����ص� ���е��� ������ ȭ�鿡 �׸���. 
		for (i = 0; i < num_of_line; i++) {
			ofDrawLine(lineseg[i].x1, lineseg[i].y1, lineseg[i].x2, lineseg[i].y2);
		}
		//�ݺ����� ���鼭 ������ ȭ�鿡 �׸���. 
		for (i = 0; i < num_of_dot; i++) {
			ofSetColor(0, 0, 255);
			ofDrawCircle(dot[i].x1, dot[i].y1, dot_diameter / 2);
		}
		//���� �ٲ۴� .
		ofSetColor(0, 255, 0);
		//������ ���⸦ �ٲٰ� ������ ���� �� ������ ȭ�鿡 ��Ÿ����.
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
	//������ key�� ���ȴٸ� bottom line�� ���������� �̵��Ѵ�. 
	if (key == OF_KEY_RIGHT) {
		draw_flag = 1;
		bottomline[0].x1 = bottomline[0].x1 + 15;
		bottomline[0].x2 = bottomline[0].x2 + 15;
	}
	//���� Ű�� ���ȴٸ� bottomline�� ���������� �̵��Ѵ�. 
	if (key == OF_KEY_LEFT) {
		draw_flag = 1;
		bottomline[0].x1 = bottomline[0].x1 - 15;
		bottomline[0].x2 = bottomline[0].x2 - 15;
	}
	//q�� �����ٸ� �Ҵ��ߴ� �޸𸮵��� �����ϰ� ������ �����Ѵ�. 
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
	//d�� �����ٸ� ȭ�鿡 ���а� ���� ǥ���Ѵ�. 
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
	//s�� �����ٸ� ������ �����Ѵ�. 
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
	//���� �����ٸ� ������ ������ ������ �ҷ��� �̸� �����س��� ������ �����Ѵ�. 
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
//������ ������ �о� �����Ѵ�. 
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
//���ٱ⸦ �ʱ�ȭ�Ͽ� ������ ������ ���� �������Ѵ�. 
void ofApp::initializeWaterLines() {
	//wl[i].start_dot.x = ofRandom(dot[selection_dot].x1-dot_diameter/2, dot[selection_dot].x1+dot_diameter/2);
	wat.waterx = target_dot.x;
	wat.watery = target_dot.y;
}
//�����ϰ� ������ ��� �̸� target_dot�� �����Ѵ�. �� ���� ���ٱ⸦ �ʱ�ȭ�Ѵ�. 
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
