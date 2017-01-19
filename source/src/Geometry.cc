//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"	
#include "G4Element.hh"
#include "G4SDManager.hh"
#include "PltTargetSD.hh"
#include "PltSensorSD.hh"
#include "G4UniformMagField.hh"

//------------------------------------------------------------------------------
Geometry::Geometry()
	:magField(0)
{}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
Geometry::~Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
G4VPhysicalVolume* Geometry::Construct()
	//------------------------------------------------------------------------------
{

	// Sensitive Detectors
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  PltSensorSD* aSensorSD = (PltSensorSD*)SDman->FindSensitiveDetector( "Plt/SensorSD");
  if ( aSensorSD == 0){
    aSensorSD = new PltSensorSD(  "Plt/SensorSD" );
    SDman->AddNewDetector( aSensorSD );
  }
  PltTargetSD* aTargetSD = (PltTargetSD*)SDman->FindSensitiveDetector( "Plt/TargetSD");
  if ( aTargetSD == 0){
    aTargetSD = new PltTargetSD(  "Plt/TargetSD" );
    SDman->AddNewDetector( aTargetSD );
  }

	// Get pointer to 'Material Manager'
	G4NistManager* materi_Man = G4NistManager::Instance();

	// Define materials
	G4double density;
	G4int ncomponents;
	G4int natoms;
	G4double fractionmass;
	G4double z,a;
	G4String symbol;

	G4Element* Na = new G4Element("Sodium"   ,"Na", z=11., a=  22.99*g/mole);
	G4Element* I  = new G4Element("Iodine"   ,"I" , z=53., a= 126.90*g/mole);
	G4Element* Si = new G4Element("Scilicon",symbol="Si" , z= 14., a= 28.09*g/mole);
	G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
	G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
	G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);

	G4Material* Al = new G4Material("Aluminum", z=13., a=26.98*g/mole, density=2.700*g/cm3);
	G4Material* Fe = materi_Man->FindOrBuildMaterial("G4_Fe");
	G4Material* Pb = materi_Man->FindOrBuildMaterial("G4_Pb");
	//G4Material* Pb = new G4Material("Lead"     , z=82., a= 207.19*g/mole, density= 11.35*g/cm3);

	G4Material* Sci = new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
	Sci->AddElement(C, natoms=9);
	Sci->AddElement(H, natoms=10);

	G4Material* SilicaGel = new G4Material("SilicaGel", density= 0.55*g/cm3, ncomponents=2);
	SilicaGel->AddElement(Si, natoms=1);
	SilicaGel->AddElement(O, natoms= 2);

	G4Material* NaI = new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
	NaI->AddElement(Na, natoms=1);
	NaI->AddElement(I , natoms=1);
	NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);

	// For some test
	G4Material* vac    = materi_Man->FindOrBuildMaterial("G4_Galactic");

	// Define 'World Volume'
	// Define the shape of solid

	G4double leng_X_World = 2.0*m;         // X-full-length of world 
	G4double leng_Y_World = 2.0*m;         // Y-full-length of world 
	G4double leng_Z_World = 2.0*m;         // Z-full-length of world 

	G4Box* solid_World = 
		new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

	// Define logical volume
	G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
	G4LogicalVolume* logVol_World = 
		new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
	logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

	// Placement of logical volume
	G4int copyNum_World = 0;               // Set ID number of world

	const G4double sourceThickness = 5.0 * mm;

	G4PVPlacement* physVol_World  = new G4PVPlacement(

				G4Transform3D(),
			   	"PhysVol_World",
			   	logVol_World,	
			   	0, 
				false,
			   	copyNum_World);

	//case
	G4Tubs* env22NaCase = new G4Tubs(
			"env22NaCase",
			0,
			25.0/2.0 * mm,
			5.0 / 2.0 * mm,
			0,
			CLHEP::twopi);

	G4Tubs* solid22NaCase = new G4Tubs(
			"solid22NaCase",
			8.0 /2.0 * mm,
			25.0/2.0 * mm,
			sourceThickness /2.0,
			0.0,
			CLHEP::twopi);

	G4Tubs* solid22NaCaseBottom = new G4Tubs(
			"solid22NaCaseBottom",
			0,
			8.0/2.0 * mm,
			2.0 / 2.0 * mm,
			0.0,
			CLHEP::twopi);

	G4Tubs* solid22NaCaseWindow = new G4Tubs(
			"solid22NaCaseWindow",
			0,
			8.0/2.0 * mm,
			0.1 / 2.0 * mm,
			0.0,
			CLHEP::twopi);


	
	G4LogicalVolume* logenv22NaCase = new G4LogicalVolume(
			env22NaCase,
			vac,
			"logenv22NaCase",
			0,0,0,true);
	G4LogicalVolume* logSide22NaCase = new G4LogicalVolume(
			solid22NaCase,
			Sci,
			"logSide22NaCase",
			0,0,0,true);
	G4LogicalVolume* logBottom22NaCase = new G4LogicalVolume(
			solid22NaCaseBottom,
			Sci,
			"logBottom22NaCase",
			0,0,0,true);
	G4LogicalVolume* logWindow22NaCase = new G4LogicalVolume(
			solid22NaCaseWindow,
			Al,
			//vac,
			"logWindow22NaCase",
			0,0,0,true);

	const G4double lengthCollimatorX = 75.0 * mm;
	const G4double lengthCollimatorYZ = 50.0 * mm;

	const G4double phiHoleCollimator = 16.0 * mm;
	const G4double lengthHole = lengthCollimatorX-sourceThickness/2.0;

	//collimator
	G4Box* solidCollimator = new G4Box("solidCollimator",lengthCollimatorX,lengthCollimatorYZ,lengthCollimatorYZ);
	G4LogicalVolume* logCollimator = new G4LogicalVolume(solidCollimator,Pb,"logCollimator",0,0,0,true);

	G4Tubs* solidBlank = new G4Tubs("solidBrank",0,phiHoleCollimator/2.0,lengthHole/2.0,0,CLHEP::twopi);
	G4LogicalVolume* logBlank = new G4LogicalVolume(solidBlank,materi_World,"logBlank",0,0,0,true);

	new G4PVPlacement( 
			G4Transform3D(), //rotation and vector
			logSide22NaCase,	//logical volume
			"physEnv22NaCaseSide",//name
			logenv22NaCase, //mother logicall volume
			false,				//set to false
			9001,			//copy number
			true);			// check
	
	new G4PVPlacement( 
			G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,-1.5*mm)), //rotation and vector
			logBottom22NaCase,	//logical volume
			"physEnv22NaCaseBottom",//name
			logenv22NaCase, //mother logicall volume
			false,				//set to false
			9002,			//copy number
			true);			// check

	new G4PVPlacement( 
			G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,2.0*mm)), //rotation and vector
			logWindow22NaCase,	//logical volume
			"physEnv22NaCaseWindow",//name
			logenv22NaCase, //mother logicall volume
			false,				//set to false
			9003,			//copy number
			true);			// check


	//Set source case to world
	G4RotationMatrix mat_source  = G4RotationMatrix();
	mat_source.rotateY(90 * deg);

	new G4PVPlacement(
			G4Transform3D(mat_source,G4ThreeVector(0 *cm,0,0)),
			logenv22NaCase,
			"sourceCase",
			logCollimator,
			false,
			9004,
			true);

	new G4PVPlacement(
			G4Transform3D(mat_source,G4ThreeVector(sourceThickness/2.0+lengthHole/2.0,0,0)),
			logBlank,
			"blankInLead",
			logCollimator,
			false,
			9005,
			true);

	//World
	new G4PVPlacement(
			G4Transform3D(G4RotationMatrix(),G4ThreeVector(-10.0*cm,0,0)),
			"sourceBox",
			logCollimator,
		   	physVol_World, 
			false,
			10000,
			true);
			

	//Scilica Gel difinition
	
	const G4double radiusSilicagel = 4.0 * mm;
	const G4double depthSilicagel = 15.0 * mm;
	const G4double targetBoxX = 20.0 * mm;
	const G4double targetBoxYZ = 20.0 * mm;
	const G4double thicknessPlasticScintillator = 0.15 * mm;

	G4Box* solidEnvGelCase = new G4Box("silicagelCase", targetBoxX /2.0, targetBoxYZ/2.0, targetBoxYZ /2.0);
	G4Tubs* solidSilicagel = new G4Tubs("solidSilicagel"  , 0, radiusSilicagel,depthSilicagel/2.0,0, CLHEP::twopi);
	G4Tubs* solidTriggerSci = new G4Tubs("solidTriggerSci", 0, radiusSilicagel,thicknessPlasticScintillator/2.0,0, CLHEP::twopi);


	G4LogicalVolume* logEnvGelCase = new G4LogicalVolume(
			solidEnvGelCase,
			Sci,
			"logEnvGelCase",
			0,0,0,true);
	G4LogicalVolume* logSilicagel = new G4LogicalVolume(
			solidSilicagel,
			SilicaGel,
			"logSilicagel",
			0,0,0,true);
	G4LogicalVolume* logTriggerSci = new G4LogicalVolume(
			solidTriggerSci,
			Sci,
			"logTriggerSci",
			0,0,0,true);

	logSilicagel->SetSensitiveDetector(aTargetSD);

	//set to world
	G4RotationMatrix mat_silica  = G4RotationMatrix();
	mat_silica.rotateY(-90 * deg);

	new G4PVPlacement( 
			G4Transform3D(mat_silica,G4ThreeVector( -(targetBoxX/2.0 - thicknessPlasticScintillator/2.0 - thicknessPlasticScintillator - depthSilicagel/2.0)-thicknessPlasticScintillator/2.0,0,0)),
			logSilicagel,	//logical volume
			"physSilicaGel",//name
			logEnvGelCase, //mother logicall volume
			false,				//set to false
			3001,			//copy number
			true);			// check


	new G4PVPlacement( 
			G4Transform3D(mat_silica,G4ThreeVector( +thicknessPlasticScintillator - targetBoxX/2.0-thicknessPlasticScintillator/2.0,0,0)), //rotation and vector
			logTriggerSci,	//logical volume
			"physTriggerSci",//name
			logEnvGelCase, //mother logicall volume
			false,				//set to false
			3002,			//copy number
			true);			// check

	new G4PVPlacement(
			G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.5*cm-0.15*mm+5.0*mm,0,0)),
			"silicaCase",
			logEnvGelCase,
		   	physVol_World, 
			false,
			3003,
			true);
			
	
	//NaI
	G4double NaILength = 50.0* mm;
	G4double NaIDiameter = 50.0 * mm;

	G4Tubs* solidNaI = new G4Tubs(
			"solidNaI",//name
			0,//Inner radius
			NaILength / 2.0,//outer radius
			NaIDiameter / 2.0,//half length in Z
			0,//the starting phi angle in radians
			CLHEP::twopi//the angle of the segment in radians
			);


	G4LogicalVolume* logNaI = new G4LogicalVolume(solidNaI,NaI,"logNaI",0,0,0);
	logNaI->SetSensitiveDetector(aSensorSD);

	G4double pos_X_LogV = 0.0*cm;           // X-location LogV 
	G4double pos_Y_LogV = 0.0*cm;           // Y-location LogV
	G4double pos_Z_LogV = 7.5*cm;           // Z-location LogV

	G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
	G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
	G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);

	G4int copyNum_LogV = 1;                // Set ID number of LogV

	threeVect_LogV.rotateX(-45.0 * deg);
	rotMtrx_LogV.rotateX(-45.0 * deg);
	copyNum_LogV = 1;                // Set ID number of LogV
	new G4PVPlacement(G4Transform3D(rotMtrx_LogV,threeVect_LogV), "PhysVol_NaI", logNaI, physVol_World, false, copyNum_LogV,true);

	threeVect_LogV.rotateX(90.0 * deg);
	rotMtrx_LogV.rotateX(90.0 * deg);
	copyNum_LogV = 2;                // Set ID number of LogV
	new G4PVPlacement(G4Transform3D(rotMtrx_LogV,threeVect_LogV), "PhysVol_NaI", logNaI, physVol_World, false, copyNum_LogV,true);

	threeVect_LogV.rotateX(90.0 * deg);
	rotMtrx_LogV.rotateX(90.0 * deg);
	copyNum_LogV = 3;                // Set ID number of LogV
	new G4PVPlacement(G4Transform3D(rotMtrx_LogV,threeVect_LogV), "PhysVol_NaI", logNaI, physVol_World, false, copyNum_LogV,true);

	threeVect_LogV.rotateX(90.0 * deg);
	rotMtrx_LogV.rotateX(90.0 * deg);
	copyNum_LogV = 4;                // Set ID number of LogV
	new G4PVPlacement(G4Transform3D(rotMtrx_LogV,threeVect_LogV), "PhysVol_NaI", logNaI, physVol_World, false, copyNum_LogV,true);


	//SetMagField(0.0 * tesla);
	SetMagField(0.1 * tesla);
	
	// Return the physical world
	//
	return physVol_World;
}

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

void Geometry::SetMagField(G4double value){
	//apply a global uniform magnetic field along Z axis                         
	G4FieldManager* fieldMgr                                                     
		= G4TransportationManager::GetTransportationManager()->GetFieldManager();   

	if(magField) delete magField;     //delete the existing magn field           

	if(value!=0.){            // create a new one if non nul                     
		fieldValue = value;
		magField = new G4UniformMagField(G4ThreeVector(fieldValue,0.,0.));         
		fieldMgr->SetDetectorField(magField);                                      
		fieldMgr->CreateChordFinder(magField);                                     
	} else {
		magField = 0;
		fieldMgr->SetDetectorField(magField);                                      
	}
}
