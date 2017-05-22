#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundAuto(false);

	ofBackground(0);

	ofSetFrameRate(60); //default 60

	canvas = ofRectangle(0, 0, 500, 500);

	lastMousePos = ofVec2f(0,0);
	isLeftMouseButtonPressed = false;
	isSavingSVG = false;
	isSavingRaster = false;
	usrtask = DRAWING;

	iSelectedStroke = -1;
	iSelectedVertex = -1;

	set_smoothness = 5;
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (flushCanvas || isLeftMouseButtonPressed) {  // If the left mouse button is pressed...
		flushCanvas = false;

		ofBackground(0);
		ofSetColor(255);  // saved strokes
		for (int i = 0; i<strokes.size(); i++) {
			strokes[i].draw();
		}

		// active stroke
		currentStroke.drawActive(set_smoothness);

		if (isSavingSVG) {
			isSavingSVG = false;
			ofEndSaveScreenAsSVG();
		}
		else if (isSavingRaster) {
			isSavingRaster = false;
			ofImage savedImg;
			glReadBuffer(GL_FRONT);
			savedImg.grabScreen(canvas.x, canvas.y, canvas.width, canvas.height);
			savedImg.save(save_name);
			savedImg.clear();
		}

// ---------- everything drawn after this will not be saved -------------
		if (usrtask == EDITING && iSelectedStroke != -1) {
			strokes[iSelectedStroke].drawEditable(iSelectedVertex);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'x') {
		isSavingRaster = true;
		save_name = "savedScreenshot.png";
	} 
	else if (key == 's') {
		save_name = "savedScreenshot_" + ofGetTimestampString() + ".svg";
		ofBeginSaveScreenAsSVG(save_name, false, false, canvas);
		isSavingSVG = true;
	}
	else if (key == 'd') {
		iSelectedStroke = -1;
		iSelectedVertex = -1;
		usrtask = DRAWING;
	}
	else if (key == 'e') {
		usrtask = EDITING;
	}
	flushCanvas = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (usrtask == EDITING && iSelectedStroke != -1) {

	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofVec2f mousePos(x, y);
	if (button == OF_MOUSE_BUTTON_LEFT) {
		if (usrtask == DRAWING) {
			currentStroke.addVertex(mousePos);
		}
		else if (usrtask == EDITING && iSelectedStroke != -1) {
			if (iSelectedVertex != -1) {
				if (selectedHandle == POINT) {
					strokes[iSelectedStroke].modifyVertex(iSelectedVertex, x, y);
				}
				else {
					strokes[iSelectedStroke].modifyHandle(iSelectedVertex, selectedHandle, x, y);
				}
			}
			else if (iSelectedStroke != -1 && mousePos.distance(lastMousePos)>1) {
				strokes[iSelectedStroke].translateLine(lastMousePos, x, y);
			}
		}
	}
	lastMousePos = mousePos;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofPoint mousePos(x, y);
	if (button == OF_MOUSE_BUTTON_LEFT) {
		isLeftMouseButtonPressed = true;

		if (usrtask == DRAWING) {
			currentStroke.startStroke();
		}
		else if (usrtask == EDITING) {
			if (iSelectedStroke != -1) {
				iSelectedVertex = strokes[iSelectedStroke].getSelectedVertex(iSelectedVertex, selectedHandle, x, y);
			}
			if (iSelectedVertex == -1) {
				iSelectedStroke = Stroke::getSelectedStroke(&strokes, mousePos);
			}
		}
	}
	lastMousePos = mousePos;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_LEFT) {
		isLeftMouseButtonPressed = false;
		
		if (usrtask == DRAWING) {
			if (currentStroke.line.size() > 1) {
				currentStroke.finishStroke(set_smoothness);
				strokes.push_back(currentStroke);
			}
			currentStroke.clear();  // Erase the vertices, allows us to start a new brush stroke
		}
	}
	//flushCanvas = true;
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


