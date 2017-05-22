# ofxPathFitter
An OpenFrameworks addon for obtaining a Bezier curve through a set of points
Based on [Paper.js path simplification](http://paperjs.org/examples/path-simplification/)

# Usage

    vector<ofPoint> vertices = line.getVertices();
    double tolerance = 10;
    bool closed = false;
    ofxPathFitter fitter(vertices, closed);
    vector<Segment> bezier = fitter.fit(tolerance);

Segment contains 3 fields:

    ofPoint point; // the point
    ofPoint handleIn; // the first control point
    ofPoint handleOut // the second control point

Note: the control points contain the coordinates relative to the point. To get the absolute coordinates:

    Segment s = ofxPathFitter::handleAbsolute(bezier[i]);

or

    vector<Segment> bezierAbs = ofxPathFitter::handlesAbsolute(bezier);
