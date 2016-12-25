#include "PltSensorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


G4Allocator<PltSensorHit> PltSensorHitAllocator;


PltSensorHit::PltSensorHit():
              sensorID(-1),
	      time(999.0*s),
	      eDep(0.0),
 	      codePDG(0),
 	      trackID(0),
	      energy(0.0),
	      pos(0.,0.,0.)
{}


PltSensorHit::~PltSensorHit() 
{}



PltSensorHit::PltSensorHit(const PltSensorHit& right)
  : G4VHit()
{
  *this = right;
}


const PltSensorHit& PltSensorHit::operator=(const PltSensorHit& right)
{
  if (this != &right) {
    sensorID    = right.sensorID;
    time        = right.time;
    eDep        = right.eDep;
    codePDG     = right.codePDG;
    trackID     = right.trackID;
    energy      = right.energy;
    pos         = right.pos;
  }
  return *this;
}



G4int PltSensorHit::operator==(const PltSensorHit& right) const
{
  return (this==&right) ? 1 : 0;
}


void PltSensorHit::Set(G4int id, G4double eLoss, const G4Track* track)
{
  sensorID   =  id;
  eDep       = eLoss;
  if (  time > track->GetGlobalTime() ){
    time = track->GetGlobalTime(); 
  } 
  if (codePDG ==0) {
    trackID  = track->GetTrackID();
    codePDG  =  track->GetDefinition()->GetPDGEncoding();
    energy   =  track->GetKineticEnergy();
    pos      =  track->GetPosition();
  }
}

void PltSensorHit::Draw()
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



void PltSensorHit::Print()
{
  G4cout << "SensorID: " << sensorID 
	 << "  time: "<< time/ns << "ns"
	 << "  enegy deposit:" << eDep/keV << "keV" << G4endl;
  G4cout << "PDG code: "<< codePDG << "  " 
         << "track ID: "<< trackID << "  " 
	 << "  enregy: " << energy /keV  << "keV" << G4endl;
  G4cout << "  position: "<< pos.x()/mm << " "
	 << pos.y()/mm << " "
	 << pos.z()/mm << "[mm]" << G4endl;
}



