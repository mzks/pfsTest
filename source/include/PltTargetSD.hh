#ifndef PltTargetSD_h
#define PltTargetSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PltTargetHit.hh"

#include <iomanip>
#include <fstream>       

class G4Step;
class G4HCofThisEvent;


class PltTargetSD : public G4VSensitiveDetector
{
public:
  PltTargetSD(G4String);
  ~PltTargetSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
  static const G4String& GetCollectionName() {return HCname;}

private:
  PltTargetHitsCollection* targetCollection;
  std::ofstream outFileTarget;
  static const G4String HCname;

};


#endif

