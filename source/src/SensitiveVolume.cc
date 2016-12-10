//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SensitiveVolume.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SensitiveVolume.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4HCofThisEvent.hh"
#include "G4VProcess.hh"

//------------------------------------------------------------------------------
  SensitiveVolume::SensitiveVolume(G4String name)
  : G4VSensitiveDetector(name)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  SensitiveVolume::~SensitiveVolume()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void SensitiveVolume::Initialize(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void SensitiveVolume::EndOfEvent(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  G4bool SensitiveVolume::ProcessHits(G4Step* aStep, G4TouchableHistory*)
//------------------------------------------------------------------------------
{
// Print out the pre-message
//   G4cout << "=== SenstiveVolume-ProcessHits: Output of Information ===" << G4endl;

// Retrieve information from the track object
   G4int nTrack = aStep->GetTrack()->GetTrackID();

// Only Primary track is picked up and handled
if (nTrack != 1) return false;
    
    G4int nStep  = aStep->GetTrack()->GetCurrentStepNumber();
    G4String particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();

	G4cout << "Hi!" << G4endl;
    G4cout << "  Track Number: " << nTrack << G4endl;
    G4cout << "  Step  Number: " << nStep << G4endl;
    G4cout << "  Particle Name: " << particleName << G4endl;

// Get PreStepPoint and TouchableHandle objects
   G4StepPoint* preStepPoint=aStep->GetPreStepPoint();
   G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
    G4String preStatus = preStepPoint->GetStepStatus();
    G4cout << "preStepPoint Status: " << preStatus << G4endl;

  // Touchable infomation: Start position of the current step
  G4ThreeVector position_World = preStepPoint->GetPosition();
  G4ThreeVector position_Local = theTouchable->GetHistory()
                                  -> GetTopTransform().TransformPoint(position_World);

  G4cout << "  World(x,y,z): " 
         << position_World.x() << ", " << position_World.y() << ", " 
         << position_World.z() << G4endl; 
  G4cout << "  Local(x,y,z): " 
         << position_Local.x() << ", " << position_Local.y() << ", " 
         << position_Local.z() << G4endl;

// Touchable information: Volume name and copy# at the current step
  G4String volumeName = theTouchable->GetVolume()->GetName();
  G4int copyNo = theTouchable->GetCopyNumber();

  G4String motherVolumeName;
  G4int motherCopyNo;
  if (volumeName != "LogVol_PixElmt" ) {
     motherVolumeName = theTouchable->GetVolume(1)->GetName();
     motherCopyNo = theTouchable->GetCopyNumber(1);
  } 
  else {
     motherVolumeName = "None";
     motherCopyNo = 0;
  }


// coordinates world and local
G4cout << "  Volume Name: Mother Volume Name: " << volumeName <<"  :  " << motherVolumeName << G4endl;
G4cout  << "(CopyNo, motherCopyNo) : " <<copyNo << " , "<< motherCopyNo<< G4endl;

// energy deposit in this step
G4double eDep = aStep->GetTotalEnergyDeposit();
// process
G4StepPoint* postStepPoint=aStep->GetPostStepPoint();

G4String procName = postStepPoint->GetProcessDefinedStep()->GetProcessName();
G4cout << "process of the step :" <<procName << G4endl;
G4cout << "Energy Deposit along this step: " << eDep << G4endl;

  return true;
}






