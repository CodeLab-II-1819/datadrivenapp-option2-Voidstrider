/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:	MIT
*/


#include "ofApp.h"
#include <string>
#include <sstream>
#include <vector>
std::stringstream dataStream;
string wrappedTweets;
//initial app setup
void ofApp::setup()
{
	//loads up the images to be drawn
	myFont.load("font.ttf", 10,true, true);
	myFont.setLineHeight(20.0f);
	logo.load("twitterLogo.png");
	upArrow.load("upArrow.png");
	downArrow.load("downArrow.png");
	trendingButton.load("trendingButton.png");
	trumpButton.load("trumpButton.png");
	moneyButton.load("moneyButton.png");
	brexitButton.load("brexitButton.png");
	politicsButton.load("politicsButton.png");
	socialButton.load("socialbutton.png");
	climateButton.load("climateButton.png");
	worldEventsButton.load("worldEventsButton.png");
	reviewButton.load("reviewButton.png");
	americaButton.load("americaButton.png");
	btn1.set(700, 0, 20, 20); //UP arrow -
	btn2.set(700, 460, 20, 20); //DOWN arrow -
	btn3.set(600, 100, 75, 25); //TRENDING -
	btn4.set(600, 126, 75, 25); //TRUMP - 1
	btn5.set(600, 152, 75, 25); //MONEY - 2
	btn6.set(600, 178, 75, 25); //BREXIT - 3
	btn7.set(600, 204, 75, 25); //POLITICS - 4
	btn8.set(600, 230, 75, 25); //SOCIAL - 5
	btn9.set(600, 256, 75, 25); //CLIMATE - 6
	btn10.set(600, 282, 75, 25); //WORLD EVENTS - 7
	btn11.set(600, 308, 75, 25); //REVIEW - 8
	btn12.set(600, 334, 75, 25); //AMERICA - 9

    //lower app frameRate
    ofSetFrameRate(30);

    // Easily register for all search events.
    client.registerSearchEvents(this);

    /* Ensure you have created and app and updated the credentials file
     in the bin/data folder. You can create app at:
     https://apps.twitter.com */
    //Load in the credentials for access to twitter
    client.setCredentialsFromFile("credentials.json");

    /* Sets the polling interval for 6 seconds. This means new tweets
    are retrived every 6 seconds*/
    client.setPollingInterval(6000);

    // This starts a simple search for an emoticon.
    client.search(":)");
    // Tweets are retured in the callbacks onStatus(..), onError(...), etc.

    /*
     To design more complex searches, see the the API documentation here:
     https://dev.twitter.com/rest/public/search
     and:
     https://developer.twitter.com/en/docs/tweets/rules-and-filtering/overview/standard-operators
     You can then use the search object ofxTwitter::SearchQuery like this:
     
        ofxTwitter::SearchQuery query(":)");
        query.setLanguage("en");
        client.search(query);

     This would return only tweets in English
    
     To see how else you can refine the queries you should explore
     the .h files included in:
     openFrameworks/addons/ofxTwitter/libs/ofxTwitter/include/ofx/Twitter
     In particular search.h
    */

}

/*
 Draw function is used to draw to GUI.
 Current setup simply draws tweet count info to a small GUI
 Tweets are displayed in console
*/
void ofApp::draw()
{
	
	count++;
	
	//sets background to blue
	ofSetColor(255);
	
	//Draws images and buttons
    ofBackground(75, 150, 255);
	logo.draw(350, 10, 50, 50);
	upArrow.draw(btn1);
	downArrow.draw(btn2);
	trendingButton.draw(btn3);
	trumpButton.draw(btn4);
	moneyButton.draw(btn5);
	brexitButton.draw(btn6);
	politicsButton.draw(btn7);
	socialButton.draw(btn8);
	climateButton.draw(btn9);
	worldEventsButton.draw(btn10);
	reviewButton.draw(btn11);
	americaButton.draw(btn12);
    //counts number of tweets
    int total = count + countMissed;

    //string stream used to display number of tweets recived
    std::stringstream ss;
    ss << "  Received: " << count << std::endl;
    ss << "    Missed: " << countMissed << std::endl;
    ss << "     Total: " << total << std::endl;
	
    /*
     Draw string stream info to the GUI window at x: 14 / y: 14
     Bitmap string is default text with limited customisation optimisations
     Load in fonts to enhance design
    */
    ofDrawBitmapString(ss.str(), 14, 14);
	ofDrawBitmapString(wrappedTweets, 14, yPos);

}

string ofApp::wrapString(string text, int width) {
	string typeWrapped = "";
	string tempString = "";
	vector <string> words = ofSplitString(text, " ");

	for (int i = 0; i < words.size(); i++) {
		string wrd = words[i];

		if (i > 0) {
			tempString += " ";
		}
		tempString += wrd;
		int stringwidth = myFont.stringWidth(tempString);
		if (stringwidth >= width) {
			typeWrapped += "\n";
			tempString = wrd;
		}
		else if (i > 0){
			typeWrapped += " ";
		}
		typeWrapped += wrd;
	}
	return typeWrapped;
}

//This function is called everytime the a new tweet is recieved
void ofApp::onStatus(const ofxTwitter::Status& status)
{
    //increase tweet count
    count++;
    
    //output the tweet author and text
    std::cout << "User: " << status.user()->name() << endl;
    std::cout << "Tweet: " << status.text() << endl;
    std::cout << "\n -----------------------------\n" << endl;
	
	dataStream << "User: " << status.user()->name() << std::endl;
	dataStream << "Tweet: " << status.text() << std::endl;
	dataStream << "\n -----------------------------\n" << std::endl;
	string tempTweet = dataStream.str();
	wrappedTweets = wrapString(tempTweet, 350);
	if (count > 14) {
		client.stop();
	}
    /*
     To see what other information you can display you should explore
     the .h files included in:
     openFrameworks/addons/ofxTwitter/libs/ofxTwitter/include/ofx/Twitter
     In particular status.h
    */
}

//returns an error message if error encountered recieving tweets
void ofApp::onError(const ofxTwitter::Error& error)
{
    std::cout << "Error: " << error.code() << " " << error.message();
}

//returns an exception message if exception encountered recieving tweets
void ofApp::onException(const std::exception& notice)
{
    std::cout << "Exception: " << notice.what();
}

void ofApp::onMessage(const ofJson& json)
{
	// This is the raw message json and is ignored here.
}

void ofApp::keyPressed(int key) {
	switch (key) {

	}
}
void ofApp::mousePressed(int x, int y, int button) {
	if (btn1.inside(x,y)) {
		yPos = yPos - 15;
	}
	if (btn2.inside(x,y)) {
		yPos = yPos + 15;
	}
	if (btn3.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("#trending or #Trending");
	}
	if (btn4.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Donald Trump or @realDonaldTrump");
	}
	if (btn5.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Money or money");
	}
	if (btn6.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Brexit or brexit");
	}
	if (btn7.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Politics or politics");
	}
	if (btn8.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Social or social");
	}
	if (btn9.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Climate or climate");
	}
	if (btn10.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("World events or world events or World Events or world Events");
	}
	if (btn11.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("Review or review");
	}
	if (btn12.inside(x,y)) {
		count = 0;
		yPos = 50;
		dataStream.str("");
		client.search("America or america");
	}
}
