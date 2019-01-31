/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:    MIT
 */

//Declaration of additions or extentions
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
	ofImage upArrow;
	ofImage downArrow;
	ofImage moneyButton;
	ofImage natureButton;
	ofImage brexitButton;
	ofImage trendingButton;
	ofImage trumpButton;
	ofImage politicsButton;
	ofImage socialButton;
	ofImage climateButton;
	ofImage worldEventsButton;
	ofImage reviewButton;
	ofImage americaButton;
	ofRectangle btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10, btn11, btn12; 
	ofTrueTypeFont myFont;
	//Comments below for the purpose of keeping track of which button does what. 
	//bt1: Up Arrow, btn2: Down Arrow, btn3: Trending Button, btn4: Trump Button, 
	//btn5: Money Button, btn6: Brexit button, 
	//btn7: Politics Button, btn8: Social Button, 
	//btn9: Climate Button, btn10: World Events Button, btn11: Review, btn12: America.
};
