// main.cc
// Raw data shaping source
// Author Mizukoshi Keita
// 2016.Dec.30

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
	ifstream ifs("../bench/pfs.dat"); // raw data file
	//ifstream ifs("../bench/pfs.dat"); // raw data file
	string buffer;
	vector<string> result;
	string delim(" "); // delimitor space
	TFile *f = new TFile("data.root","recreate");

	Int_t		event = 0;
	vector<Int_t>		track;
	vector<Int_t>		code;
	vector<Double_t>	E;
	vector<Int_t>		sensor;
	vector<Double_t>	targetE;
	vector<Double_t>	X;
	vector<Double_t>	Y;
	vector<Double_t>	Z;

	TTree* mytree = new TTree("mytree","geometry test");

	mytree->Branch("event",&event,"event/I");
	mytree->Branch("track",&track);
	mytree->Branch("code",&code);
	mytree->Branch("E",&E);
	mytree->Branch("sensor",&sensor);
	mytree->Branch("targetE",&targetE);
	mytree->Branch("X",&X);
	mytree->Branch("Y",&Y);
	mytree->Branch("Z",&Z);

	getline(ifs,buffer);
	boost::split(result,buffer,boost::is_any_of(delim),boost::algorithm::token_compress_on);
		event = stoi(result.at(1));

	//read one line
	while(getline(ifs,buffer)){

		boost::split(result,buffer,boost::is_any_of(delim),boost::algorithm::token_compress_on);
		if(buffer[0] == '#'){
		mytree->Fill();

		//init vectors
		track.clear();
		code.clear();
		E.clear();
		sensor.clear();
		targetE.clear();
		X.clear();
		Y.clear();
		Z.clear();

		event = stoi(result.at(1));
		}else{
		track.push_back( stoi(result.at(0)));
		code.push_back( stoi(result.at(1)));
		E.push_back( stod(result.at(2)));
		sensor.push_back( stoi(result.at(3)));
		targetE.push_back( stod(result.at(4)));
		X.push_back( stod(result.at(5)));
		Y.push_back( stod(result.at(6)));
		Z.push_back( stod(result.at(7)));
		}

	}
	mytree->Fill();
	mytree->Write();
	f->Close();
	delete f;
	return 0;
}
