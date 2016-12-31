#include "PltSensorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////
const G4String PltSensorSD::HCname="sensorCollection";

/////////////////////////////////////////////////////

PltSensorSD::PltSensorSD(G4String name)
  :G4VSensitiveDetector(name)
{
  collectionName.insert(HCname);

  //--- open file -----
  G4String fileName = "pfs.dat";  
  outFile.open(fileName, std::ios::out);
  //outFile << "#run_number:0" << G4endl;
  //outFile << "#comment: MC generated events"   << G4endl;
  
  
  //Threshold energy 
  //--- Hit will be recorded if deposit energy is larger than threshold
  eThreshold = 10.0 * keV;
 
  // double pulse separtiom
  // --- hit will be merged if hit time is inside resolution
  tResolution = 30.0 * ns;

  verboseLevel =1; 
}

/////////////////////////////////////////////////////

PltSensorSD::~PltSensorSD()
{ 
  outFile.close();
}

/////////////////////////////////////////////////////

void PltSensorSD::Initialize(G4HCofThisEvent* HCE)
{
  sensorCollection = new PltSensorHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, sensorCollection ); 
}

/////////////////////////////////////////////////////

G4bool PltSensorSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  
  const G4Track * aTrack =  aStep->GetTrack();
  // Check Energy Deposit
  G4double eLoss = aStep->GetTotalEnergyDeposit();
  if (eLoss <= 0.0 ) return false;
  G4double time = aTrack->GetGlobalTime();
 
  G4int sensorID = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(0);
  //G4int sensorID = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(1);

  G4int NbHits = sensorCollection->entries();
  G4bool found = false;
  for (G4int iHit=0; (iHit<NbHits) && (!found) ;iHit++) {
    found = (sensorID == (*sensorCollection)[iHit]->GetSensorID() ) ;
    if (found) {    
      // check time
      if (std::abs(time-(*sensorCollection)[iHit]->GetTime()) < tResolution) {
	// merge hit
	(*sensorCollection)[iHit]->AddEdep(eLoss);
	return true;
      } 
    }
  }
  // create new hit
  PltSensorHit* newHit = new PltSensorHit();
  newHit->Set(sensorID, eLoss, aTrack);
  sensorCollection->insert( newHit );
  
  return true;
}

  
///////////////////////////////////////////////////////
#include "PltTargetSD.hh"

void PltSensorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  const G4double offset = 0.0*ns;
  static G4int eventId = 0;

  // Traget Hit
  static G4int targetHCID = -1;
  if(targetHCID<0) { 
    G4String name = PltTargetSD::GetCollectionName();
    targetHCID = G4SDManager::GetSDMpointer()->GetCollectionID(name);
  }
  PltTargetHitsCollection* targetCollection = 
    dynamic_cast<PltTargetHitsCollection*>(HCE->GetHC(targetHCID));
  PltTargetHit* tHit = 0;
  if (targetCollection !=0) {
    if (targetCollection->entries()>0) {
      tHit = (*targetCollection)[0];
    }
  }

  // Sensor Hit
  G4int NbHits = sensorCollection->entries();
  if (verboseLevel>2) {
    G4cout << " -------->Hits Collection: in event " << eventId 
	   << "  there are " << NbHits << " hits  " << G4endl;
  }else if (verboseLevel>1 && NbHits>2 ) {
    G4cout << "  -------->Hits Collection: in event " << eventId 
	   << "  there are " << NbHits << " hits  " << G4endl;
  }
  
 eventId += 1;

  if (verboseLevel>1){
    G4cout << "  -------->Hits Collection: in event " << eventId 
	   << "  there are " << NbHits << " hits  " << G4endl;
  }

  
  outFile.setf( std::ios:: scientific, std::ios::floatfield );
  outFile << std::setprecision(4);

  G4bool isFirstHit = true;  
  G4bool hasHit=false;
  for (G4int i=0;i<NbHits;i++){
    PltSensorHit* hit = (*sensorCollection)[i];
    if (verboseLevel>1) hit->Print();
    // output hits other than trigger counters
    G4int ch = hit->GetSensorID();
    if (hit->GetEdep() < eThreshold ) continue;

    if (isFirstHit) {
      outFile << "#EV " << eventId << G4endl;
      isFirstHit = false;
      hasHit = true;
    }

	//hit
	if(tHit != 0) {
    outFile << hit->GetTrackID() <<" " 
	    << hit->GetPDGcode() <<" " 
	    << hit->GetEnergy()/MeV  <<" " 
		<< ch << " "
		<< tHit->GetEnergy()/MeV << " "
		<< (tHit->GetPos()).getX()/mm << " "
		<< (tHit->GetPos()).getY()/mm << " "
		<< (tHit->GetPos()).getZ()/mm << " "
	    << G4endl;
	}else{
    outFile << hit->GetTrackID() <<" " 
	    << hit->GetPDGcode() <<" " 
	    << hit->GetEnergy()/MeV  <<" " 
		<< ch << " "
		<< "-1 0 0 0"
	    << G4endl;
	}

	//hit->Print();


//    G4int ch_a = 100+ch;
//	G4int ch_l = 16+ch*2;
//    G4int ch_h = 17+ch*2;
//    outFile << "    "
//	    << ch_a   <<  "   " 
//	    << (hit->GetEdep())/keV  <<"   " 
//	    << int((hit->GetEdep())/keV*20 + 100) << "   " 
//	    << G4endl;
//   outFile << "    "
//	   << ch_l   <<  "   " 
//	   << (hit->GetTime()+offset)/ns << "   " 
//	   << int(10000-0.7*(hit->GetTime()+offset)/ns) << "   " 
//	   << G4endl;
//   outFile << "    "
//	   << ch_h   <<  "   " 
//	   << (hit->GetTime()+offset)/ns + 10.0 << "   " 
//	   << int(10000-0.7*(hit->GetTime()+offset)/ns-10) << "   " 
//	   << G4endl;


  }

//  if (hasHit){
//    outFile << "    "
//	    << 103  <<  "   " 
//	    << 1275.  <<"   " 
//	    << 8000 << "   " 
//	    << G4endl;
//   outFile << "    "
//	   << 22   <<  "   " 
//	   << offset/ns << "   " 
//	   << int(10000-0.7*(offset)/ns) << "   " 
//	   << G4endl;
//   outFile << "    "
//	   << 23   <<  "   " 
//	   << offset/ns + 10.0 << "   " 
//	   << int(10000-0.7*(offset)/ns-10) << "   " 
//	   << G4endl;
//
//
//  }
}




