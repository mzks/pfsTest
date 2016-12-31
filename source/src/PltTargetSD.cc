#include "PltTargetSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////
const G4String PltTargetSD::HCname="targetCollection";

/////////////////////////////////////////////////////
PltTargetSD::PltTargetSD(G4String name)
  :G4VSensitiveDetector(name)
{
  collectionName.insert(HCname);
  
  //G4String fileName = "pfsTarget.dat";  
  //outFileTarget.open(fileName, std::ios::out);
  //outFileTarget << "#run start" << G4endl;

  verboseLevel =3; 
}

/////////////////////////////////////////////////////

PltTargetSD::~PltTargetSD()
{ 
	//outFileTarget.close();
}

/////////////////////////////////////////////////////

void PltTargetSD::Initialize(G4HCofThisEvent* HCE)
{
  targetCollection = new PltTargetHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
  static G4int HCID = -1;
  if(HCID<0){ 
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
  }
  HCE->AddHitsCollection( HCID, targetCollection ); 
}

/////////////////////////////////////////////////////

G4bool PltTargetSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{ 
  const G4Track * aTrack =  aStep->GetTrack();
  // Check Track ID
  //if (aTrack->GetTrackID()!=1) return false;
  // Check Particle ID is e+ 
  if (aTrack->GetDefinition()->GetPDGEncoding()!=-11) return false;
  
  G4int targetID = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  G4double zPos = (aStep->GetPostStepPoint()->GetPosition()).z();
  G4int NbHits = targetCollection->entries();
  G4bool found = false;
  for (G4int iHit=0; (iHit<NbHits) && (!found) ;iHit++) {
    found = (targetID == (*targetCollection)[iHit]->GetTargetID() ) ;
    if (found) {    
      (*targetCollection)[iHit]->Set(targetID, zPos, aTrack);
      return true; 
    }
  }
  // create new hit
  PltTargetHit* newHit = new PltTargetHit();
  newHit->Set(targetID,  zPos, aTrack);
  targetCollection->insert( newHit );
  
  return true;
}

  
///////////////////////////////////////////////////////


void PltTargetSD::EndOfEvent(G4HCofThisEvent*)
{
	G4int NbHits = targetCollection->entries();
	if (NbHits==0) return;
	//static G4int eventId = 0;
	//outFileTarget << eventId <<  " :Hit!" << G4endl;
	//G4cout <<  "Hit!" << G4endl;
	//eventId++;

	//if (verboseLevel>1){(*targetCollection)[0]->Print();}
}




