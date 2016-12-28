//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Medicine Users: 2016.11.29 @Sendai
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "UserActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "LBE.hh"
//#include "QGSP_BERT.hh"

//-------------------------------------------------------------------------------
  int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
   // ============= [ Setting up the application environment ] =================
      G4String nameMainMacro = "GlobalSetup.mac";   // Initialization  macros
   // ==========================================================================

   G4UIExecutive* ui = 0;
   if (argc == 1){
   ui = new G4UIExecutive(argc,argv);
   }

// Construct the default run manager
   G4RunManager* runManager = new G4RunManager;

// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new Geometry );

// Set up mandatory user initialization: Physics-List
   runManager->SetUserInitialization( new LBE );
   //runManager->SetUserInitialization( new QGSP_BERT );

// Set up user initialization: User Actions
   runManager->SetUserInitialization( new UserActionInitialization );

// Initialize G4 kernel
   runManager->Initialize();

// Create visualization environment
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();

// Start interactive session
   //G4UImanager*   uiManager = G4UImanager::GetUIpointer();
   //G4UIExecutive* ui    = new G4UIExecutive(argc, argv);
   //uiManager->ApplyCommand("/control/execute " + nameMainMacro);
   //uiExec->SessionStart();
   G4UImanager* UImanager = G4UImanager::GetUIpointer();

   if(! ui ){
	   //batch
	   G4String command = "/control/execute ";
	   G4String fileName = argv[1];
	   UImanager->ApplyCommand(command+fileName);
   }else{
	   //interactive
	   UImanager->ApplyCommand("/control/execute " + nameMainMacro);
	   ui->SessionStart();
	   delete ui;
   }
   
// Job termination
   //delete ui;
   //delete UImanager;
   //delete uiExec;
   delete visManager;
   delete runManager;

   return 0;
}
