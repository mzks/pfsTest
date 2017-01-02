//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan  2 12:01:28 2017 by ROOT version 6.06/04
// from TTree mytree/geometry test
// found on file: data.root
//////////////////////////////////////////////////////////

#ifndef mytree_h
#define mytree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class mytree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   vector<int>     *track;
   vector<int>     *code;
   vector<double>  *E;
   vector<int>     *sensor;
   vector<double>  *targetE;
   vector<double>  *X;
   vector<double>  *Y;
   vector<double>  *Z;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_track;   //!
   TBranch        *b_code;   //!
   TBranch        *b_E;   //!
   TBranch        *b_sensor;   //!
   TBranch        *b_targetE;   //!
   TBranch        *b_X;   //!
   TBranch        *b_Y;   //!
   TBranch        *b_Z;   //!

   mytree(TTree *tree=0);
   virtual ~mytree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef mytree_cxx
mytree::mytree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("data.root");
      }
      f->GetObject("mytree",tree);

   }
   Init(tree);
}

mytree::~mytree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mytree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mytree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void mytree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   track = 0;
   code = 0;
   E = 0;
   sensor = 0;
   targetE = 0;
   X = 0;
   Y = 0;
   Z = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("track", &track, &b_track);
   fChain->SetBranchAddress("code", &code, &b_code);
   fChain->SetBranchAddress("E", &E, &b_E);
   fChain->SetBranchAddress("sensor", &sensor, &b_sensor);
   fChain->SetBranchAddress("targetE", &targetE, &b_targetE);
   fChain->SetBranchAddress("X", &X, &b_X);
   fChain->SetBranchAddress("Y", &Y, &b_Y);
   fChain->SetBranchAddress("Z", &Z, &b_Z);
   Notify();
}

Bool_t mytree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mytree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mytree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mytree_cxx
