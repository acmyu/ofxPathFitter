#include "Stroke.h"

Stroke::Stroke() {
}

Stroke::~Stroke()
{
}

Stroke::Stroke(int i) {
}

void Stroke::clear() {
	line.clear();
	lineBez.clear();
}

void Stroke::draw() {
	line.draw();
}

void Stroke::drawActive(int smoothness) {
	Stroke displayStroke = *this;
	if (smoothness > 0) {
		displayStroke.line = line.getSmoothed(smoothness);
	}
	displayStroke.draw();
}

void Stroke::drawEditableVertex(Segment pt) {
	ofSetColor(255);
	ofDrawCircle(pt.point, 5);
	ofNoFill();
	Segment ptAbs = ofxPathFitter::handleAbsolute(pt);
	if (pt.handleIn.x != 0 && pt.handleIn.y != 0) {
		ofDrawLine(pt.point, ptAbs.handleIn);
		ofDrawCircle(ptAbs.handleIn, 5);
	}
	if (pt.handleOut.x != 0 && pt.handleOut.y != 0) {
		ofDrawLine(pt.point, ptAbs.handleOut);
		ofDrawCircle(ptAbs.handleOut, 5);
	}
	ofFill();
	ofSetColor(100);
}

void Stroke::drawEditable(int iSelectedVertex) {
	ofSetColor(100);
	for (int i = 0; i<lineBez.size(); i++) {
		Segment pt = lineBez[i];
		if (i == iSelectedVertex) {
			drawEditableVertex(pt);
		}
		else {
			ofDrawCircle(pt.point, 5);
		}
	}
}

void Stroke::startStroke() {
	
}

void Stroke::addVertex(ofVec2f v) {
	line.addVertex(v);
}

void Stroke::finishStroke(int smoothness) {
	line = line.getSmoothed(smoothness);
	line.simplify(0.5f);
	updateBez();
}

void Stroke::updateBez() {
	ofxPathFitter lineFitter(line.getVertices(), false);
	lineBez = lineFitter.fit(10);
}

void Stroke::updateLine(bool simplify) {
	ofPolyline newLine;
	vector<Segment> lineBezAbs = ofxPathFitter::handlesAbsolute(lineBez);
	newLine.addVertex(lineBezAbs.front().point);
	for (int i = 1; i < lineBezAbs.size(); i++) {
		newLine.bezierTo(lineBezAbs[i - 1].handleOut, lineBezAbs[i].handleIn, lineBezAbs[i].point);
	}
	line = newLine;
	if (simplify) {
		line.simplify(0.5f);
	}
	
}

void Stroke::modifyHandle(int id, int selectedHandle, int x, int y) {
	ofPoint pt = lineBez[id].point;
	if (selectedHandle == HANDLEIN) {
		lineBez[id].handleIn.x = x - pt.x;
		lineBez[id].handleIn.y = y - pt.y;
	}
	else {
		lineBez[id].handleOut.x = x - pt.x;
		lineBez[id].handleOut.y = y - pt.y;
	}
	updateLine();
}

void Stroke::modifyVertex(int id, int x, int y) {
	lineBez[id].point.x = x;
	lineBez[id].point.y = y;
	updateLine();
}

int Stroke::getSelectedVertex(int iSelectedVertex, int &handle, int x, int y) {
	handle = -1;
	for (int i = 0; i < lineBez.size(); i++) {
		Segment s = ofxPathFitter::handleAbsolute(lineBez[i]);
		if (ofDist(s.point.x, s.point.y, x, y) < SELECTPADDING) {
			handle = POINT;
		}
		else if (iSelectedVertex == i) {
			if (ofDist(s.handleIn.x, s.handleIn.y, x, y) < SELECTPADDING) {
				handle = HANDLEIN;
			}
			else if (ofDist(s.handleOut.x, s.handleOut.y, x, y) < SELECTPADDING) {
				handle = HANDLEOUT;
			}
		}
		if (handle != -1) {
			return i;
		}
	}
	return -1;
}

int distLine(ofPoint pt, ofPolyline *line) {
	ofPoint cl = (*line).getClosestPoint(pt);
	return cl.distance(pt);
}

int Stroke::getSelectedStroke(vector<Stroke> *strokes, ofVec2f mousePos) {
	for (int i = 0; i < (*strokes).size(); i++) {
		ofPolyline *line = &((*strokes)[i].line);
		if (distLine(mousePos, line) < SELECTPADDING) {
			return i;
		}
	}
	return -1;
}

void Stroke::translateLine(ofVec2f lastMousePos, int x, int y) {
	int xShift = x - lastMousePos.x;
	int yShift = y - lastMousePos.y;
	for (int i = 0; i < lineBez.size(); i++) {
		lineBez[i].point.x += xShift;
		lineBez[i].point.y += yShift;
	}
	for (int i = 0; i < line.size(); i++) {
		line[i].x += xShift;
		line[i].y += yShift;
	}
}


