#ifndef PltTargetHit_h
#define PltTargetHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"


class PltTargetHit : public G4VHit
{
public:
  PltTargetHit();
  ~PltTargetHit();
  PltTargetHit(const PltTargetHit&);
  const PltTargetHit& operator=(const PltTargetHit&);
  G4int operator==(const PltTargetHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();
  
public:
  
  void Set(G4int id, G4double z, const G4Track* track);
  
  G4int    GetTargetID() const  { return targetID; };
  G4double GetTime()  const  { return time; };      
  G4double GetZ()     const  { return zPos; };      

  G4int GetPDGcode()            const  { return codePDG; };
  G4int GetTrackID()            const  { return trackID; };
  G4double GetEnergy()          const  { return energy; };      
  const G4ThreeVector& GetPos() const  { return pos; };
        
private:
  G4int         targetID;
  G4double      time;
  G4double      zPos;

  G4int         codePDG;
  G4int         trackID;
  G4double      energy;
  G4ThreeVector pos;
};


typedef G4THitsCollection<PltTargetHit> PltTargetHitsCollection;

extern G4Allocator<PltTargetHit> PltTargetHitAllocator;


inline void* PltTargetHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) PltTargetHitAllocator.MallocSingle();
  return aHit;
}


inline void PltTargetHit::operator delete(void *aHit)
{
  PltTargetHitAllocator.FreeSingle((PltTargetHit*) aHit);
}


#endif
