#pragma once

#include "ofMain.h"

#include "ofxPathFitter.h"

#define SELECTPADDING	10

#define POINT		0
#define HANDLEIN	1
#define HANDLEOUT	2

class Stroke
{
	void drawEditableVertex(BezPoint vertex);

public:
	Stroke();
	~Stroke();
	Stroke(int i);
	
	void clear();

	void draw();
	void drawActive(int smoothness);
	void drawEditable(int iSelectedVertex);

	void startStroke();
	void addVertex(ofVec2f v);
	void finishStroke(int smoothness);

	void updateBez();
	void updateLine(bool simplify = true);
	void modifyHandle(int id, int selectedHandle, int x, int y);
	void modifyVertex(int id, int x, int y);
	
	int getSelectedVertex(int iSelectedVertex, int &handle, int x, int y);
	static int getSelectedStroke(vector<Stroke> *strokes, ofVec2f mousePos);

	void translateLine(ofVec2f lastMousePos, int x, int y);
	
	ofPolyline line;
	vector<BezPoint> lineBez;

};


