// main.cc
// Raw data shaping source
// Author Mizukoshi Keita
// 2016.Dec.27

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"
#include <unistd.h>

using namespace std;

int main(){
	ifstream ifs("./M10Ev.txt"); // raw data file
	string buffer;
	vector<string> result;
	string delim(" "); // delimitor space
	TFile *f = new TFile("data.root","recreate");

	Int_t		track;
	Int_t		code;
	Double_t	E;
	Int_t		sensor;
	Double_t	targetE;
	Double_t	X;
	Double_t	Y;
	Double_t	Z;

	TTree* t = new TTree("t","geometry test");
	t->Branch("track",&track,"track/I");
	t->Branch("code",&code,"code/I");
	t->Branch("E",&E,"E/D");
	t->Branch("sensor",&sensor,"sensor/I");
	t->Branch("targetE",&targetE,"targetE/D");
	t->Branch("X",&X,"X/D");
	t->Branch("Y",&Y,"Y/D");
	t->Branch("Z",&Z,"Z/D");


	//read one line
	while(getline(ifs,buffer)){
		if(buffer[0]!='#'){
		boost::split(result,buffer,boost::is_any_of(delim),boost::algorithm::token_compress_on);
		track = stoi(result.at(0));
		code = stoi(result.at(1));
		E = stod(result.at(2));
		sensor = stoi(result.at(3));
		targetE = stod(result.at(4));
		X = stod(result.at(5));
		Y = stod(result.at(6));
		Z = stod(result.at(7));
		t->Fill();
		}
	}
	t->Write();
	f->Close();
	delete f;
	return 0;
}
