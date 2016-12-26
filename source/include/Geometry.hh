//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.hh
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef Geometry_h
#define Geometry_h 1

#include "G4VUserDetectorConstruction.hh"
class G4VPhysicalVolume;
class G4UniformMagField;

//------------------------------------------------------------------------------
  class Geometry : public G4VUserDetectorConstruction
//------------------------------------------------------------------------------
{
  public:
    Geometry();
   ~Geometry();
   void SetMagField(G4double);
    G4VPhysicalVolume* Construct();
private:
	G4UniformMagField* magField;
	G4double fieldValue;
};
#endif
