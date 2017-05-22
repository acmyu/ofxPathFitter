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

class Segment : public ofPolyline {
public:
    ~Segment();
    Segment();
    Segment(ofPoint pt);
    Segment(ofPoint pt, ofPoint h);
    
    ofPoint point;
    ofPoint handleIn;
    ofPoint handleOut;
};

class ofxPathFitter {
public: 
    ~ofxPathFitter();
    ofxPathFitter();
    ofxPathFitter(vector<ofPoint> pts, bool isClosed);

	vector<Segment> fit(double error = 2.5);
	static Segment handleAbsolute(Segment s);
	static vector<Segment> handlesAbsolute(vector<Segment> segments);
    
private:
    vector<ofPoint> points;
    bool closed;
    
    void addCurve(vector<Segment> &segments, vector<ofPoint> curve);
    void fitCubic(vector<Segment> &segments, double error, int first, int last, ofPoint tan1, ofPoint tan2);
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
