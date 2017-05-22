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
    
    ofPoint point;
    ofPoint handleIn;
    ofPoint handleOut;
};

class ofxPathFitter {
public: 
    ~ofxPathFitter();
    ofxPathFitter();
    ofxPathFitter(vector<ofPoint> pts, bool isClosed);

	vector<BezPoint> fit(double error = 2.5);
	static BezPoint handleAbsolute(BezPoint s);
	static vector<BezPoint> handlesAbsolute(vector<BezPoint> BezPoints);
    
private:
    vector<ofPoint> points;
    bool closed;
    
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
