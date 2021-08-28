#include "ofApp.h"

//--------------------------------------------------------------
void dCharacter::update(vector<string>& words) {

	if (ofGetFrameNum() % 5 && this->rect->getVelocity().length() > 1.5) {

		this->index = ofRandom(words.size());
	}
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->font_size = 20;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		//u8"!", u8"#", u8"$", u8"%", u8"&",
		//u8"'", u8"(", u8")", u8"*", u8"+",
		//u8",", u8"-", u8".", u8"/", u8"0",
		//u8"1", u8"2", u8"3", u8"4", u8"5",
		//u8"6", u8"7", u8"8", u8"9", u8"0",
		//u8":", u8";", u8"<", u8"=", u8">",
		//u8"?", u8"@",

		//u8"A", u8"B", u8"C", u8"D", u8"E",
		//u8"F", u8"G", u8"H", u8"I", u8"J",
		//u8"K", u8"L", u8"M", u8"N", u8"O",
		//u8"P", u8"Q", u8"R", u8"S", u8"T",
		//u8"U", u8"V", u8"W", u8"X", u8"Y", u8"Z",

		//u8"a", u8"b", u8"c", u8"d", u8"e",
		//u8"f", u8"g", u8"h", u8"i", u8"j",
		//u8"k", u8"l", u8"m", u8"n", u8"o",
		//u8"p", u8"q", u8"r", u8"s", u8"t",
		//u8"u", u8"v", u8"w", u8"x", u8"y", u8"z",

		u8"±", u8"²", u8"³", u8"´", u8"µ",
		u8"¶", u8"·", u8"¸", u8"¹", u8"º",
		u8"»", u8"¼", u8"½", u8"¾", u8"¿",
		u8"À", u8"Á", u8"Â", u8"Ã", u8"Ä",
		u8"Å", u8"Æ", u8"Ç", u8"È", u8"É",
		u8"Ê", u8"Ë", u8"Ì", u8"Í", u8"Î",
		u8"Ï", u8"Ð", u8"Ñ", u8"Ò", u8"Ó",
		u8"Ô", u8"Õ", u8"Ö",
		u8"×", u8"Ø", u8"Ù", u8"Ú", u8"Û",
		u8"Ü", u8"¦", u8"Ý",
	};

	this->box2d.init();
	this->box2d.setGravity(0, 15);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofRandom(100) < 35) {

		auto rect = make_shared<ofxBox2dRect>();
		rect->setPhysics(1.0, 0.3, 0.3);
		rect->setup(this->box2d.getWorld(), ofRandom(ofGetWidth() * 0.5 - 25, ofGetWidth() * 0.5 + 25), 25, this->font_size, this->font_size);

		auto drop_char = dCharacter();
		drop_char.rect = rect;
		drop_char.index = ofRandom(this->words.size());

		this->drop_char_list.push_back(drop_char);
	}

	for (auto& drop_char : this->drop_char_list) {

		drop_char.update(this->words);
	}

	this->box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& drop_char : this->drop_char_list) {

		ofPushMatrix();
		ofTranslate(drop_char.rect->getPosition().x, drop_char.rect->getPosition().y);
		ofRotate(drop_char.rect->getRotation());

		this->font.drawString(this->words[drop_char.index], -5, 10);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}