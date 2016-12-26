#ifndef PltSensorHit_h
#define PltSensorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"


class PltSensorHit : public G4VHit
{
public:
  PltSensorHit();
  ~PltSensorHit();
  PltSensorHit(const PltSensorHit&);
  const PltSensorHit& operator=(const PltSensorHit&);
  G4int operator==(const PltSensorHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();
  
public:
  
  void Set(G4int id, G4double eLosss, const G4Track* track);
  
  G4int  GetSensorID() const  { return sensorID; };
  G4double GetTime()  const  { return time; };      
  G4double GetEdep()  const  { return eDep; };      
  void     AddEdep(G4double val)     { eDep += val; };      

  G4int GetPDGcode()            const  { return codePDG; };
  G4int GetTrackID()            const  { return trackID; };
  G4double GetEnergy()          const  { return energy; };      
  //const G4ThreeVector& GetPos() const  { return pos; };
  const G4ThreeVector GetPos() const  { return pos; };
        
private:
  G4int         sensorID;
  G4double      time;
  G4double      eDep;

  G4int         codePDG;
  G4int         trackID;
  G4double      energy;
  G4ThreeVector pos;
};


typedef G4THitsCollection<PltSensorHit> PltSensorHitsCollection;

extern G4Allocator<PltSensorHit> PltSensorHitAllocator;


inline void* PltSensorHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) PltSensorHitAllocator.MallocSingle();
  return aHit;
}


inline void PltSensorHit::operator delete(void *aHit)
{
  PltSensorHitAllocator.FreeSingle((PltSensorHit*) aHit);
}


#endif
