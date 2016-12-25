#include "PltTargetHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


G4Allocator<PltTargetHit> PltTargetHitAllocator;


PltTargetHit::PltTargetHit():
              targetID(-1),
	      time(999.0*s),
	      zPos(0.0),
 	      codePDG(0),
 	      trackID(0),
	      energy(0.0),
	      pos(0.,0.,0.)
{}


PltTargetHit::~PltTargetHit() 
{}



PltTargetHit::PltTargetHit(const PltTargetHit& right)
  : G4VHit()
{
  *this = right;
}


const PltTargetHit& PltTargetHit::operator=(const PltTargetHit& right)
{
  if (this != &right) {
    targetID    = right.targetID;
    time        = right.time;
    zPos        = right.zPos;
    codePDG     = right.codePDG;
    trackID     = right.trackID;
    energy      = right.energy;
    pos         = right.pos;
  }
  return *this;
}



G4int PltTargetHit::operator==(const PltTargetHit& right) const
{
  return (this==&right) ? 1 : 0;
}


void PltTargetHit::Set(G4int id, G4double z, const G4Track* track)
{
  targetID   =  id;
  time = track->GetGlobalTime(); 
  pos      =  track->GetPosition();
  zPos     =  z;
  if (codePDG ==0) {
    trackID  = track->GetTrackID();
    codePDG  =  track->GetDefinition()->GetPDGEncoding();
    energy   =  track->GetKineticEnergy();
  }
}

void PltTargetHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager){
    G4Circle circle(pos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}



void PltTargetHit::Print()
{
  G4cout << "TargetID: " << targetID 
	 << "  time: "<< time/ns << "ns"
	 << "  z position:" << zPos/mm << "mm" << G4endl;
  G4cout << "PDG code: "<< codePDG << "  " 
         << "track ID: "<< trackID << "  " 
	 << " enregy@entrance: " << energy /keV  << "keV" << G4endl;
}



