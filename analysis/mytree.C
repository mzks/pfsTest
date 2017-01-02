#define mytree_cxx
#include "mytree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void mytree::Loop()
{

//   In a ROOT session, you can do:
//      root> .L mytree.C
//      root> mytree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	//TH1D* hist = new TH1D("hist","hist",100,0,1.0);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int coinc = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
	  int nhit = E->size();
	  int evehit = 0;
	  
	  for(int i=0;i<nhit;i++){
		  if(code->at(i) == 22 && E->at(i) > 0) evehit++;
	  //cout << event  << ": " << code->at(i) << ": " << E->at(i) << endl;
	  }
	 if (evehit >1 ){
		 cout << "event:" << event << endl;
		 for(int i=0; i<nhit; i++){
			 if(code->at(i) == 22 && E->at(i) > 0) cout << sensor->at(i) << ":" << E->at(i) << endl;
		 }
		 coinc++;
	 } 
	  
   }
   cout << "total coincidense:" << coinc << endl;
}
