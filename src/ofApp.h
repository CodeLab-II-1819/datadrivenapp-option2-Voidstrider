/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:    MIT
 */


#pragma once
#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxGui.h"

class ofApp: public ofBaseApp
{
public:
    //declare app functions
    void setup();
	void draw();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
    void onStatus(const ofxTwitter::Status& status);
    void onError(const ofxTwitter::Error& error);
    void onException(const std::exception& exception);
	void onMessage(const ofJson& json);
	string wrapString(string text, int width);
	//declare twitter search client
    ofxTwitter::SearchClient client;
    
    //declare variables
    int count = 0;
    int countMissed = 0;
	int yPos = 50;

	string wrappedTweets;

	ofxPanel controller;
	ofxFloatSlider xPos;

	ofImage logo;
	ofImage trendingButton;
	ofImage trumpButton;
	ofImage upArrow;
	ofImage downArrow;
	ofRectangle btn1, btn2, btn3, btn4;
	ofTrueTypeFont myFont;

};
