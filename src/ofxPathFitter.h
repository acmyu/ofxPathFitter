#pragma once

#include "ofMain.h"

struct PathFitterError {
public:
    ~PathFitterError();
    PathFitterError();
    PathFitterError(int i, double err);
    int index;
    double error;
};

class BezPoint : public ofPolyline {
public:

	~BezPoint();
	BezPoint();
    BezPoint(ofPoint pt);
	BezPoint(ofPoint pt, ofPoint h);
    BezPoint(ofPoint pt, ofPoint hIn, ofPoint hOut, bool abs = false);
    
    ofPoint point;
    ofPoint handleIn;
    ofPoint handleOut;
	bool isAbsolute;

	bool hasHandleIn();
	bool hasHandleOut();
	// Converts the handles of a Bezier point from relative coordinates to absolute coordinates
	BezPoint handlesAbsolute();
};

class ofxPathFitter {
public:
    // Simplify a Bezier line
	static vector<BezPoint> simplify(ofPolyline line, double tolerance = 2.5);
	static vector<BezPoint> simplify(vector<ofPoint> pts, bool isClosed, double tolerance = 2.5);
private:
    vector<ofPoint> points;
    bool closed;
    
    ~ofxPathFitter();
    ofxPathFitter();
    ofxPathFitter(vector<ofPoint> pts, bool isClosed);
    
    // Simplify the Bezier line from an existing ofxPathFitter instance
	vector<BezPoint> fit(double error = 2.5);
    
	static vector<BezPoint> handlesAbsolute(vector<BezPoint> BezPoints);
    
    void addCurve(vector<BezPoint> &BezPoints, vector<ofPoint> curve);
    void fitCubic(vector<BezPoint> &BezPoints, double error, int first, int last, ofPoint tan1, ofPoint tan2);
    vector<ofPoint> generateBezier(int first, int last, vector<double> uPrime, ofPoint tan1, ofPoint tan2);
    bool reparameterize(int first, int last, vector<double> uPrime, vector<ofPoint> curve);
    double findRoot(vector<ofPoint> curve, ofPoint point, double u);
    ofPoint evaluate(int degree, vector<ofPoint> curve, double t);
    vector<double> chordLengthParameterize(int first, int last);
    PathFitterError findMaxError(int first, int last, vector<ofPoint> curve, vector<double> uPrime);
    
    static ofPoint subtract(ofPoint p1, ofPoint p2);
	static ofPoint add(ofPoint p1, ofPoint p2);
	static ofPoint multiply(ofPoint p1, double p2);
	static ofPoint normalize(ofPoint p1, double length);
};
