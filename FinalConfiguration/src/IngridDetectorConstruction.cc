#include <stdio.h>
#include <iostream>
#include <vector>

#include "IngridDetectorConstruction.hh"
#include "IngridHLayerSD.hh"
#include "IngridVLayerSD.hh"
#include "IngridVetoSD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"
#include "G4EllipticalTube.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"

#include "globals.hh"

#include "Const.hh"

//#define MOD3

IngridDetectorConstruction::IngridDetectorConstruction(int MODE)
{
    mode = MODE;
}

IngridDetectorConstruction::~IngridDetectorConstruction()
{
}


G4VPhysicalVolume* IngridDetectorConstruction::Construct()
{

  //Initialise materials
  DefineMaterial();

  //Initialise volumes
  DefineSpace();

  //Initialise detector elements parameters
  DefineStructures();

  //
  int start_mod,stop_mod;
  if(mode==WAGASCI){start_mod=20;stop_mod=32;}//target
  else if(mode==LEFTFE){start_mod=20;stop_mod=32;}//left side MRD
  else if(mode==DOWNFE){start_mod=20;stop_mod=32;}//downstream MRD 
  else if(mode==RIGHTFE){start_mod=20;stop_mod=32;}//right side MRD
  else { std::cout << "please set module number\n"; start_mod =0; stop_mod=0; }

  G4RotationMatrix *xrot = new G4RotationMatrix(G4ThreeVector(1,0,0),90.*degree);
  G4RotationMatrix *yrot = new G4RotationMatrix(G4ThreeVector(0,1,0),90.*degree);
  G4RotationMatrix *zrot = new G4RotationMatrix(G4ThreeVector(0,0,1),90.*degree);
  G4RotationMatrix *yyrot = new G4RotationMatrix(G4ThreeVector(0,1,0),180.*degree);

  
  //World volume
  G4Box* experimentalHall_box = new G4Box("Hall",WorldX,WorldY,WorldZ);
  G4LogicalVolume* worldLV = new G4LogicalVolume(experimentalHall_box, Air, "hall_log",0,0,0);
  G4VPhysicalVolume* worldPV    = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),worldLV,"hall",0,false,0);

  //Hall Dirt volume
  G4Tubs* HallDirtSLD = 
    new G4Tubs("halldirt", HallDirtRadiusMin, HallDirtRadiusMax, HallDirtHeight, HallDirtSPhi, HallDirtDPhi);
  G4LogicalVolume* HallDirtLV = new G4LogicalVolume(HallDirtSLD, Concrete, "HallDirt",0,0,0);
  G4VPhysicalVolume* HallDirtPV  = 
    new G4PVPlacement(xrot,G4ThreeVector(HallDirtX,HallDirtY,HallDirtZ),HallDirtLV,"HallDirt",worldLV,false,0);

  G4VisAttributes* HallDirtVisAtt = new G4VisAttributes(G4Color(1.,1.,1.));
  HallDirtVisAtt->SetForceWireframe(true);
  HallDirtLV->SetVisAttributes(HallDirtVisAtt);

  //for B2 BG study 2014/1/28
  G4Tubs* HallDirtfloor = 
    new G4Tubs("hallfloor", 0*cm, HallDirtRadiusMin-1*mm, (HallDirtHeight+Floorup)/2., HallDirtSPhi, HallDirtDPhi);//2014/6/11
  G4LogicalVolume* HallDirtfloorLV = new G4LogicalVolume(HallDirtfloor, Concrete, "HallDirtfloor",0,0,0);
  G4VPhysicalVolume* HallDirtfloorPV  = 
    new G4PVPlacement(xrot,G4ThreeVector(HallDirtX,HallDirtY - HallDirtHeight + (HallDirtHeight+Floorup)/2.,HallDirtZ),HallDirtfloorLV,"HallDirtfloor",worldLV,false,0);//2014/6/11

  G4VisAttributes* HallDirtfloorVisAtt = new G4VisAttributes(G4Color(1.,1.,1.));
  HallDirtfloorVisAtt->SetForceWireframe(true);
  HallDirtfloorLV->SetVisAttributes(HallDirtfloorVisAtt);

  //for B2 BG study 2014/6/26
  G4Box* Pillar_box = new G4Box("Pillar",PillarX,PillarY,PillarZ);
  G4LogicalVolume* PillarLV = new G4LogicalVolume(Pillar_box, Concrete, "Pillar",0,0,0);
  G4VPhysicalVolume* PillarPV  = 
    new G4PVPlacement(0,G4ThreeVector(PillarposX,PillarposY,PillarposZ),PillarLV,"Pillar",worldLV,false,0);

  G4VisAttributes* PillarVisAtt = new G4VisAttributes(G4Color(1.,0.,1.));
  PillarVisAtt->SetForceWireframe(true);
  PillarLV->SetVisAttributes(PillarVisAtt);

  G4VPhysicalVolume* PillarPV2  = 
    new G4PVPlacement(0,G4ThreeVector(PillarposX_rev,PillarposY,PillarposZ),PillarLV,"Pillar",worldLV,false,0);





  //Horizontal volume (for the 7 horizontal modules)
  G4Box* horizontalHall_box = new G4Box("HorizontalHall",HorizonX, HorizonY, HorizonZ);
  G4LogicalVolume* horizontalLV =new G4LogicalVolume(horizontalHall_box, Air, "horizon_log",0,0,0);
  G4VPhysicalVolume* horizontalPV  = new G4PVPlacement(0,G4ThreeVector(0., 0., 0.),horizontalLV,"horizontal",worldLV,false,0);

  //Vertical volume (for the 7 vertical modules)
  G4Box* verticalHall_box =  new G4Box("VerticalHall",HorizonY, HorizonX, HorizonZ);
  G4LogicalVolume* verticalLV =new G4LogicalVolume(verticalHall_box, Air, "vertical_log",0,0,0);
  G4VPhysicalVolume* verticalPV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-4.0*m),verticalLV,"vertical",worldLV,false,0);

  //WAGASCHI
  G4Box* B2Hall_box= new G4Box("B2Hall",WagaX,WagaY,WagaZ);//2014/6/11
  G4LogicalVolume* B2LV =new G4LogicalVolume(B2Hall_box, Air, "B2_log",0,0,0);
  G4VPhysicalVolume* B2PV = new G4PVPlacement(0,G4ThreeVector(WagaposX,WagaposY,WagaposZ),B2LV,"B2",worldLV,false,0);//2014/6/11
  //G4VPhysicalVolume* B2PV = new G4PVPlacement(0,G4ThreeVector(0,0,0),B2LV,"B2",worldLV,false,0);//2014/6/11 for vis

//////////////////////////////////////////////////////////////
//// We first create modules, than put materials inside /////
//////////////////////////////////////////////////////////////

  // MODULE ====================================
  //Modules objects:
  G4Box* module_box = new G4Box("Module",ModuleX, ModuleY, ModuleZ);
  //Proton Module object added by kikawa
  //B2 added by koga
  G4Box* B2_box= new G4Box("BModule",WagaboxX, WagaboxY, WagaboxZ);
  G4Box* B2_box_for= new G4Box("BModulefor",WagaboxforX,WagaboxforY,WagaboxforZ);
  G4Box* B2_box_side= new G4Box("BModuleside",WagaboxsideX, WagaboxsideY, WagaboxsideZ);
  G4Box* B2_box_back= new G4Box("BModuleback",WagaboxbackX, WagaboxbackY, WagaboxbackZ);
  G4Box* B2_box_bottom= new G4Box("BModulebottom",WagaboxbottomX, WagaboxbottomY,WagaboxbottomZ);
   
  G4LogicalVolume* moduleLV[35];//


  for(int k=start_mod;k<stop_mod;k++){

    //Set 7 horizontal modules:
    if( k>=0 && k<7 ) {
      moduleLV[k] = new G4LogicalVolume(module_box, Air, "module_log_h");
      char moduleName[14];
      sprintf(moduleName,"module%d",k);

      G4double x = ModuleStart + ModuleSpace*k;
      new G4PVPlacement(0,G4ThreeVector(x,0.,0.),moduleLV[k],moduleName,horizontalLV,false,k);
    }
    //Set 7 vertical modules
    else if( k>=7 && k<14 ) {
      moduleLV[k] = new G4LogicalVolume(module_box, Air, "module_log_v");
      char moduleName[14];
      sprintf(moduleName,"module%d",k);
      G4double y = ModuleStart + ModuleSpace*(k-7);    
      new G4PVPlacement(0,G4ThreeVector(0.,y,0.),moduleLV[k],moduleName,verticalLV,false,k);     
    }

    //set WAGASCHI added by koga
    else if(k==24){
      moduleLV[k] = new G4LogicalVolume(B2_box, Air, "module_log_b");
      new G4PVPlacement(0,G4ThreeVector(WagaboxposX,WagaboxposY,WagaboxposZ),moduleLV[k],"module24",B2LV,false,k);	
    }
  
    else if(k==21){
      moduleLV[k] = new G4LogicalVolume(B2_box_for, Air, "module_log_hb1");
      //new G4PVPlacement(0,G4ThreeVector(0.,0.,1.595*m),moduleLV[k],"module21",B2LV,false,k); 
      new G4PVPlacement(0,G4ThreeVector(WagaboxforposX,WagaboxforposY,WagaboxforposZ),moduleLV[k],"module21",B2LV,false,k);//2014/6/11
    }

    else if(k==22){
      moduleLV[k] = new G4LogicalVolume(B2_box_side, Air, "module_log_hb2");
      //new G4PVPlacement(0,G4ThreeVector(1.695*m,0.,-1.0*m),moduleLV[k],"module22",B2LV,false,k); 
      new G4PVPlacement(0,G4ThreeVector(WagaboxsideposX,WagaboxsideposY,WagaboxsideposZ),moduleLV[k],"module22",B2LV,false,k);//2014/6/11 
    }

    else if(k==28){//right side MRD
      moduleLV[k] = new G4LogicalVolume(B2_box_side, Air, "module_log_hb2");
      //new G4PVPlacement(0,G4ThreeVector(1.695*m,0.,-1.0*m),moduleLV[k],"module22",B2LV,false,k); 
      new G4PVPlacement(0,G4ThreeVector(-WagaboxsideposX,WagaboxsideposY,WagaboxsideposZ),moduleLV[k],"module28",B2LV,false,k);//2014/7/30
    } 

    else if(k==23){
      moduleLV[k] = new G4LogicalVolume(B2_box_back, Air, "module_log_hb2");
      //new G4PVPlacement(0,G4ThreeVector(0.,0.,(-2.595)*m),moduleLV[k],"module23",B2LV,false,k); 
      new G4PVPlacement(0,G4ThreeVector(WagaboxbackposX,WagaboxbackposY,WagaboxbackposZ),moduleLV[k],"module23",B2LV,false,k);//2014/6/11 
    }

    else if(k==29){//bottom MRD
      moduleLV[k] = new G4LogicalVolume(B2_box_bottom, Air, "module_log_hb2");
      //new G4PVPlacement(0,G4ThreeVector(1.695*m,0.,-1.0*m),moduleLV[k],"module22",B2LV,false,k); 
      new G4PVPlacement(0,G4ThreeVector(WagaboxbottomposX,WagaboxbottomposY,WagaboxbottomposZ),moduleLV[k],"module29",B2LV,false,k,1);//2014/7/30
    } 

    else if(k==30){//bottom MRD
      moduleLV[k] = new G4LogicalVolume(B2_box_bottom, Air, "module_log_hb2");
      //new G4PVPlacement(0,G4ThreeVector(1.695*m,0.,-1.0*m),moduleLV[k],"module22",B2LV,false,k); 
      new G4PVPlacement(0,G4ThreeVector(WagaboxbottomposX,-WagaboxbottomposY,WagaboxbottomposZ),moduleLV[k],"module30",B2LV,false,k,1);//2014/7/30
    } 
     
  }

  // IRON BLOCK ===================================================================================================================  
   
  G4Box* iron_block = new G4Box("Iron",iron_xy,iron_xy,iron_z);
  G4LogicalVolume* ironLV = new G4LogicalVolume(iron_block,Fe,"ironLV");
  
  G4VisAttributes* ironVisAtt = new G4VisAttributes(G4Color(0.7,0.,0.7)); // magenta
  ironVisAtt->SetForceWireframe(true);
  //ironVisAtt->SetForceSolid(true);
  ironLV->SetVisAttributes(ironVisAtt);
  //ironLV->SetVisAttributes(G4VisAttributes::Invisible);

  ////////////////////B2//////////////

  //side Fe 2014/6/11
  G4Box* iron_block2 = new G4Box("Iron2",Iron2X,Iron2Y,Iron2Z);//2014/6/11
  G4LogicalVolume* ironLV2 = new G4LogicalVolume(iron_block2,Fe,"ironLV2");  
  G4VisAttributes* ironVisAtt2 = new G4VisAttributes(G4Color(0.7,0.,0.7)); // magenta
  ironVisAtt2->SetForceWireframe(true);
  //ironVisAtt->SetForceSolid(true);
  ironLV2->SetVisAttributes(ironVisAtt2);			//change for vrml
  //ironLV->SetVisAttributes(G4VisAttributes::Invisible);

  //downstream fe 2014/6/11
  G4Box* iron_block3 = new G4Box("Iron3",Iron3X,Iron3Y,Iron3Z);
  G4LogicalVolume* ironLV3 = new G4LogicalVolume(iron_block3,Fe,"ironLV3");
  G4VisAttributes* ironVisAtt3 = new G4VisAttributes(G4Color(0.7,0.,0.7)); // magenta
  ironVisAtt3->SetForceWireframe(true);
  //ironVisAtt->SetForceSolid(true);
  ironLV3->SetVisAttributes(ironVisAtt3);			//change for vrml

  //bottom Fe 2014/7/30
  G4Box* iron_block4 = new G4Box("Iron4",Iron4X,Iron4Y,Iron4Z);
  G4LogicalVolume* ironLV4 = new G4LogicalVolume(iron_block4,Fe,"ironLV4");  
  G4VisAttributes* ironVisAtt4 = new G4VisAttributes(G4Color(0.7,0.,0.7)); // magenta
  ironVisAtt4->SetForceWireframe(true);
  //ironVisAtt->SetForceSolid(true);
  ironLV4->SetVisAttributes(ironVisAtt4);			//change for vrml
  //ironLV->SetVisAttributes(G4VisAttributes::Invisible);


  //SCINTILLATORS FOR TRACKING PLANES ==================================================================================================

  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> vdim;
  // horizontal-layer scintillator (internal)
  std::vector<G4TwoVector> hdim;

  //SciBar type for Proton module added by kikawa
  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> svdim;
  // horizontal-layer scintillator (internal)
  std::vector<G4TwoVector> shdim;

  //INGRID type for Proton module added by kikawa
  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> ivdim;
  // horizontal-layer scintillator (internal)
  std::vector<G4TwoVector> ihdim;

  for(int iver=0; iver<nSciVertex; iver++){
    vdim.push_back( G4TwoVector( SciVertex_x[iver], SciVertex_y[iver] ) );
    hdim.push_back( G4TwoVector( SciVertex_y[nSciVertex-1-iver], 
    SciVertex_x[nSciVertex-1-iver] ) );
  }

 
  //SciBar Scintillator dimension
  SciVertex2_x[0] = -11.7*mm; 
  SciVertex2_x[1] = -12.25*mm; 
  SciVertex2_x[2] = -12.25*mm; 
  SciVertex2_x[3] = -11.7*mm; 
  SciVertex2_x[4] =  11.7*mm; 
  SciVertex2_x[5] =  12.25*mm; 
  SciVertex2_x[6] =  12.25*mm; 
  SciVertex2_x[7] =  11.7*mm;

  SciVertex2_y[0] = - 6.5 *mm; 
  SciVertex2_y[1] = - 3.5*mm; 
  SciVertex2_y[2] =   3.5*mm; 
  SciVertex2_y[3] =   6.5 *mm; 
  SciVertex2_y[4] =   6.5 *mm; 
  SciVertex2_y[5] =   3.5*mm; 
  SciVertex2_y[6] =  -3.5*mm; 
  SciVertex2_y[7] =  -6.5 *mm; 

  //for SciBar type
  for(int iver=0; iver<nSciVertex; iver++){
    svdim.push_back( G4TwoVector( SciVertex2_x[iver], SciVertex2_y[iver] ) );
    shdim.push_back( G4TwoVector( SciVertex2_y[nSciVertex-1-iver], 
    SciVertex2_x[nSciVertex-1-iver] ) );
  }
 

  //INGRID Scintillator dimension for PM
  SciVertex3_x[0] = -23.65*mm; 
  SciVertex3_x[1] = -24.15*mm; 
  SciVertex3_x[2] = -24.15*mm; 
  SciVertex3_x[3] = -23.65*mm; 
  SciVertex3_x[4] =  23.65*mm; 
  SciVertex3_x[5] =  24.15*mm; 
  SciVertex3_x[6] =  24.15*mm; 
  SciVertex3_x[7] =  23.65*mm;

  SciVertex3_y[0] = - 5. *mm; 
  SciVertex3_y[1] = - 0.5*mm; 
  SciVertex3_y[2] =   0.5*mm; 
  SciVertex3_y[3] =   5. *mm; 
  SciVertex3_y[4] =   5. *mm; 
  SciVertex3_y[5] =   0.5*mm; 
  SciVertex3_y[6] =  -0.5*mm; 
  SciVertex3_y[7] =  -5. *mm; 


  //for INGRID type of PM
  for(int iver=0; iver<nSciVertex; iver++){
    ivdim.push_back( G4TwoVector( SciVertex3_x[iver], SciVertex3_y[iver] ) );
    ihdim.push_back( G4TwoVector( SciVertex3_y[nSciVertex-1-iver], 
    SciVertex3_x[nSciVertex-1-iver] ) );
  }

  std::vector<G4ExtrudedSolid::ZSection> zsec;
  zsec.push_back( G4ExtrudedSolid::ZSection(-600*mm, G4TwoVector(0*mm,0*mm), 1) );
  zsec.push_back( G4ExtrudedSolid::ZSection(600*mm, G4TwoVector(0*mm,0*mm), 1) );
  
  //INGRID type for INGRID
  //INGRID vertical scintillator
  G4ExtrudedSolid* vscint_tmp = new G4ExtrudedSolid("vscint_tmp", vdim, zsec);
  G4EllipticalTube* vsci_hole = new G4EllipticalTube("vsci_hole",1.3*mm,1.95*mm,600*mm);
  G4SubtractionSolid* vscint_int = new G4SubtractionSolid("vscint_int",  vscint_tmp, vsci_hole);
  G4LogicalVolume* vscint_intLV = new G4LogicalVolume(vscint_int,Scinti,"vscint_intLV");
  G4VisAttributes* vscint_intVisAtt = new G4VisAttributes(G4Color(0.,1.,0.));
  vscint_intVisAtt->SetForceWireframe(true);
  //vscint_intVisAtt->SetForceSolid(true);
  vscint_intLV->SetVisAttributes(vscint_intVisAtt);
  
  //INGRID horizontal scintillator
  G4ExtrudedSolid* hscint_tmp = new G4ExtrudedSolid("hscint_tmp", hdim, zsec);
  G4EllipticalTube* hsci_hole = new G4EllipticalTube("hsci_hole",1.95*mm,1.3*mm,600*mm);
  G4SubtractionSolid* hscint_int = new G4SubtractionSolid("hscint_int",  hscint_tmp, hsci_hole);
  G4LogicalVolume* hscint_intLV = new G4LogicalVolume(hscint_int,Scinti,"hscint_intLV");
  G4VisAttributes* hscint_intVisAtt = new G4VisAttributes(G4Color(0.,1.,0.));
  //hscint_intVisAtt->SetForceWireframe(true);
  hscint_intVisAtt->SetForceSolid(true);
  hscint_intLV->SetVisAttributes(hscint_intVisAtt);


  //SciBar type for proton module added by kikawa
  //SciBar vertical scintillator
  G4ExtrudedSolid* vscint2_tmp = new G4ExtrudedSolid("vscint2_tmp", svdim, zsec);
  G4EllipticalTube* vsci_hole2 = new G4EllipticalTube("vsci_hole2",0.9*mm,0.9*mm,600*mm);
  G4SubtractionSolid* vscint2_int = new G4SubtractionSolid("vscint2_int",  vscint2_tmp, vsci_hole2);
  G4LogicalVolume* vscint2_intLV = new G4LogicalVolume(vscint2_int,Scinti,"vscint2_intLV");
  G4VisAttributes* vscint2_intVisAtt = new G4VisAttributes(G4Color(0.,1.0,0.));
  //vscint2_intVisAtt->SetForceWireframe(true);
  vscint2_intVisAtt->SetForceSolid(true);
  vscint2_intLV->SetVisAttributes(vscint2_intVisAtt);

  //SciBar horizontal scintillator
  G4ExtrudedSolid* hscint2_tmp = new G4ExtrudedSolid("hscint2_tmp", shdim, zsec);
  G4EllipticalTube* hsci_hole2 = new G4EllipticalTube("hsci_hole2",0.9*mm,0.9*mm,600*mm);
  G4SubtractionSolid* hscint2_int = new G4SubtractionSolid("hscint2_int",  hscint2_tmp, hsci_hole2);
  G4LogicalVolume* hscint2_intLV = new G4LogicalVolume(hscint2_int,Scinti,"hscint2_intLV");
  G4VisAttributes* hscint2_intVisAtt = new G4VisAttributes(G4Color(0.,1.,0.));
  //hscint2_intVisAtt->SetForceWireframe(true);
  hscint2_intVisAtt->SetForceSolid(true);
  hscint2_intLV->SetVisAttributes(hscint2_intVisAtt);




  //INGRID type for proton module added by kikawa
  //INGRID vertical scintillator for PM
  G4ExtrudedSolid* vscint3_tmp = new G4ExtrudedSolid("vscint3_tmp", ivdim, zsec);
  G4EllipticalTube* vsci_hole3 = new G4EllipticalTube("vsci_hole3",1.3*mm,1.95*mm,600*mm);
  G4SubtractionSolid* vscint3_int = new G4SubtractionSolid("vscint3_int",  vscint3_tmp, vsci_hole3);
  G4LogicalVolume* vscint3_intLV = new G4LogicalVolume(vscint3_int,Scinti,"vscint3_intLV");
  G4VisAttributes* vscint3_intVisAtt = new G4VisAttributes(G4Color(0.,1.0,0.));
  //vscint3_intVisAtt->SetForceWireframe(true);
  vscint3_intVisAtt->SetForceSolid(true);
  vscint3_intLV->SetVisAttributes(vscint3_intVisAtt);

  //INGRID horizontal scintillator for PM
  G4ExtrudedSolid* hscint3_tmp = new G4ExtrudedSolid("hscint3_tmp", ihdim, zsec);
  G4EllipticalTube* hsci_hole3 = new G4EllipticalTube("hsci_hole3",1.95*mm,1.3*mm,600*mm);
  G4SubtractionSolid* hscint3_int = new G4SubtractionSolid("hscint3_int",  hscint3_tmp, hsci_hole3);
  G4LogicalVolume* hscint3_intLV = new G4LogicalVolume(hscint3_int,Scinti,"hscint3_intLV");
  G4VisAttributes* hscint3_intVisAtt = new G4VisAttributes(G4Color(0.,1.,0.));
  //hscint3_intVisAtt->SetForceWireframe(true);
  hscint3_intVisAtt->SetForceSolid(true);
  hscint3_intLV->SetVisAttributes(hscint3_intVisAtt);



  // horizontal-layer scintillator
  
  G4Box* hlayer = new G4Box("hlayer",scibar_x,scibar_y,scibar_z);
  G4LogicalVolume* hlayerLV = new G4LogicalVolume(hlayer,Scinti,"hlayerLV");
  G4VisAttributes* hlayerVisAtt = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt->SetForceWireframe(true);
  hlayerLV->SetVisAttributes(hlayerVisAtt);
  //////////////////////////////////////2/////////////////// 
  //for side MRD
  //G4Box* hlayer2 = new G4Box("hlayer2",1.25*m,2.5*cm,0.5*cm);
  G4Box* hlayer2 = new G4Box("hlayer2",Hlayer2X,Hlayer2Y,Hlayer2Z);//2014/6/11
  G4LogicalVolume* hlayerLV2 = new G4LogicalVolume(hlayer2,Scinti,"hlayerLV2");
  G4VisAttributes* hlayerVisAtt2 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt2->SetForceWireframe(true);
  hlayerLV2->SetVisAttributes(hlayerVisAtt2);

  //for downstream MRD
  G4Box* hlayer3 = new G4Box("hlayer3",Hlayer3X,Hlayer3Y,Hlayer3Z);//2014/6/11
  G4LogicalVolume* hlayerLV3 = new G4LogicalVolume(hlayer3,Scinti,"hlayerLV3");
  G4VisAttributes* hlayerVisAtt3 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt3->SetForceWireframe(true);
  hlayerLV3->SetVisAttributes(hlayerVisAtt3);

  G4Box* hlayer4 = new G4Box("hlayer4",Hlayer4X,Hlayer4Y,Hlayer4Z);
  G4LogicalVolume* hlayerLV4 = new G4LogicalVolume(hlayer4,Scinti,"hlayerLV4");
  G4VisAttributes* hlayerVisAtt4 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt4->SetForceWireframe(true);
  hlayerLV4->SetVisAttributes(hlayerVisAtt4);

  //for downstream veto
  //G4Box* hlayer5 = new G4Box("hlayer5",0.875*m,2.5*cm,0.5*cm);
  G4Box* hlayer5 = new G4Box("hlayer5",Hlayer5X,Hlayer5Y,Hlayer5Z);//2014/6/11
  G4LogicalVolume* hlayerLV5 = new G4LogicalVolume(hlayer5,Scinti,"hlayerLV5");
  G4VisAttributes* hlayerVisAtt5 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt5->SetForceWireframe(true);
  hlayerLV5->SetVisAttributes(hlayerVisAtt5);
  //hlayerLV5->SetVisAttributes(G4VisAttributes::Invisible);
  
  //for WAGASCI
  //G4Box* hlayer6 = new G4Box("hlayer6",0.75*m,1.25*cm,0.15*cm);
  G4Box* hlayer6 = new G4Box("hlayer6",Hlayer6X,Hlayer6Y,Hlayer6Z);//2014/6/11
  G4LogicalVolume* hlayerLV6 = new G4LogicalVolume(hlayer6,Scinti,"hlayerLV6");
  G4VisAttributes* hlayerVisAtt6 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt6->SetForceWireframe(true);
  hlayerLV6->SetVisAttributes(hlayerVisAtt6);
  //hlayerLV6->SetVisAttributes(G4VisAttributes::Invisible);

  //for side veto
  //G4Box* hlayer7 = new G4Box("hlayer7",0.80*m,2.5*cm,0.5*cm);
  G4Box* hlayer7 = new G4Box("hlayer7",Hlayer7X,Hlayer7Y,Hlayer7Z);//2014/6/11
  G4LogicalVolume* hlayerLV7 = new G4LogicalVolume(hlayer7,Scinti,"hlayerLV7");
  G4VisAttributes* hlayerVisAtt7 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt7->SetForceWireframe(true);
  hlayerLV7->SetVisAttributes(hlayerVisAtt7);
  //hlayerLV7->SetVisAttributes(G4VisAttributes::Invisible);

  //for up and down veto
  //G4Box* hlayer8 = new G4Box("hlayer8",0.875*m,2.5*cm,0.5*cm);
  G4Box* hlayer8 = new G4Box("hlayer8",Hlayer8X,Hlayer8Y,Hlayer8Z);
  G4LogicalVolume* hlayerLV8 = new G4LogicalVolume(hlayer8,Scinti,"hlayerLV8");
  G4VisAttributes* hlayerVisAtt8 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt8->SetForceWireframe(true);
  hlayerLV8->SetVisAttributes(hlayerVisAtt8);

  //for bottom MRD
  G4Box* hlayer9 = new G4Box("hlayer9",Hlayer9X,Hlayer9Y,Hlayer9Z);//2014/6/11
  G4LogicalVolume* hlayerLV9 = new G4LogicalVolume(hlayer9,Scinti,"hlayerLV9");
  G4VisAttributes* hlayerVisAtt9 = new G4VisAttributes(G4Color(0.,0.7,0.));
  hlayerVisAtt9->SetForceWireframe(true);
  hlayerLV9->SetVisAttributes(hlayerVisAtt9);



 ////////////////////////////////////////////////////////// 

  //vertical-layer scintillator
  G4Box* vlayer = new G4Box("vlayer",scibar_y,scibar_x,scibar_z);
  G4LogicalVolume* vlayerLV = new G4LogicalVolume(vlayer,Scinti,"vlayerLV");
  G4VisAttributes* vlayerVisAtt = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt->SetForceWireframe(true);
  vlayerLV->SetVisAttributes(vlayerVisAtt);
  //////////////////////////////////////////////////B2///////////////  

  //for side MRD
  //G4Box* vlayer2 = new G4Box("vlayer2",2.5*cm,1.25*m,0.5*cm);
  G4Box* vlayer2 = new G4Box("vlayer2",Vlayer2X,Vlayer2Y,Vlayer2Z);
  G4LogicalVolume* vlayerLV2 = new G4LogicalVolume(vlayer2,Scinti,"vlayerLV2");
  G4VisAttributes* vlayerVisAtt2 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt2->SetForceWireframe(true);
  vlayerLV2->SetVisAttributes(vlayerVisAtt2);

  //for downstream MRD
  //G4Box* vlayer3 = new G4Box("vlayer3",2.5*cm,0.75*m,0.5*cm);
  G4Box* vlayer3 = new G4Box("vlayer3",Vlayer3X,Vlayer3Y,Vlayer3Z);//2014/6/11
  G4LogicalVolume* vlayerLV3 = new G4LogicalVolume(vlayer3,Scinti,"vlayerLV3");
  G4VisAttributes* vlayerVisAtt3 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt3->SetForceWireframe(true);
  vlayerLV3->SetVisAttributes(vlayerVisAtt3);

  G4Box* vlayer4 = new G4Box("vlayer4",Vlayer4X,Vlayer4Y,Vlayer4Z);
  G4LogicalVolume* vlayerLV4 = new G4LogicalVolume(vlayer4,Scinti,"vlayerLV4");
  G4VisAttributes* vlayerVisAtt4 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt4->SetForceWireframe(true);
  vlayerLV4->SetVisAttributes(vlayerVisAtt4);

  //for downstream veto
  //G4Box* vlayer5 = new G4Box("vlayer5",2.5*cm,0.80*m,0.5*cm);
  G4Box* vlayer5 = new G4Box("vlayer5",Vlayer5X,Vlayer5Y,Vlayer5Z);//2014/6/11
  G4LogicalVolume* vlayerLV5 = new G4LogicalVolume(vlayer5,Scinti,"vlayerLV5");
  G4VisAttributes* vlayerVisAtt5 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt5->SetForceWireframe(true);
  vlayerLV5->SetVisAttributes(vlayerVisAtt5);
  //vlayerLV5->SetVisAttributes(G4VisAttributes::Invisible);

  //for WAGASCI
  //G4Box* vlayer6 = new G4Box("vlayer6",1.25*cm,0.75*m,0.15*cm);
  G4Box* vlayer6 = new G4Box("vlayer6",Vlayer6X,Vlayer6Y,Vlayer6Z);//2014/6/11
  G4LogicalVolume* vlayerLV6 = new G4LogicalVolume(vlayer6,Scinti,"vlayerLV6");
  G4VisAttributes* vlayerVisAtt6 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt4->SetForceWireframe(true);
  vlayerLV6->SetVisAttributes(vlayerVisAtt6);
  //vlayerLV6->SetVisAttributes(G4VisAttributes::Invisible);

  //for side veto
  //G4Box* vlayer7 = new G4Box("vlayer7",2.5*cm,0.80*m,0.5*cm);
  G4Box* vlayer7 = new G4Box("vlayer7",Vlayer7X,Vlayer7Y,Vlayer7Z);
  G4LogicalVolume* vlayerLV7 = new G4LogicalVolume(vlayer7,Scinti,"vlayerLV7");
  G4VisAttributes* vlayerVisAtt7 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt7->SetForceWireframe(true);
  vlayerLV7->SetVisAttributes(vlayerVisAtt7);
  //vlayerLV7->SetVisAttributes(G4VisAttributes::Invisible);

  //for up and down veto
  //G4Box* vlayer8 = new G4Box("vlayer8",2.5*cm,0.875*m,0.5*cm);
  G4Box* vlayer8 = new G4Box("vlayer8",Vlayer8X,Vlayer8Y,Vlayer8Z);
  G4LogicalVolume* vlayerLV8 = new G4LogicalVolume(vlayer8,Scinti,"vlayerLV8");
  G4VisAttributes* vlayerVisAtt8 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt8->SetForceWireframe(true);
  vlayerLV8->SetVisAttributes(vlayerVisAtt8);

  //for bottom MRD
  //G4Box* vlayer2 = new G4Box("vlayer2",2.5*cm,1.25*m,0.5*cm);
  G4Box* vlayer9 = new G4Box("vlayer9",Vlayer9X,Vlayer9Y,Vlayer9Z);
  G4LogicalVolume* vlayerLV9 = new G4LogicalVolume(vlayer9,Scinti,"vlayerLV9");
  G4VisAttributes* vlayerVisAtt9 = new G4VisAttributes(G4Color(0.,0.7,0.));
  vlayerVisAtt9->SetForceWireframe(true);
  vlayerLV9->SetVisAttributes(vlayerVisAtt9);


  ///////////////////////////////////////////////////////////

  
  //SCINTILLATORS FOR VETO PLANES ============================================================================================================

  G4VisAttributes* vetoVisAtt = new G4VisAttributes(G4Color(0.,0.6,0.5));
  vetoVisAtt->SetForceWireframe(true);

  //Long Veto plane
  G4Box* Lveto_box = new G4Box("Lveto_box",Lveto_x,Lveto_y,Lveto_z);
  G4LogicalVolume *LvetoLV = new G4LogicalVolume(Lveto_box,Scinti,"LvetoLV");

  //LvetoLV->SetVisAttributes(G4VisAttributes::Invisible);
  LvetoLV->SetVisAttributes(vetoVisAtt);
  
  //Short Veto plane
  G4Box* Sveto_box = new G4Box("Sveto_box",Sveto_x,Sveto_y,Sveto_z);
  G4LogicalVolume *SvetoLV = new G4LogicalVolume(Sveto_box,Scinti,"SvetoLV");

  //SvetoLV->SetVisAttributes(G4VisAttributes::Invisible);
  SvetoLV->SetVisAttributes(vetoVisAtt);



  //Proton module Long Veto plane added by kikawa
  G4Box* PLveto_box = new G4Box("PLveto_box",PLveto_x,PLveto_y,PLveto_z);
  G4LogicalVolume *PLvetoLV = new G4LogicalVolume(PLveto_box,Scinti,"PLvetoLV");

  PLvetoLV->SetVisAttributes(G4VisAttributes::Invisible);
  //PLvetoLV->SetVisAttributes(vetoVisAtt);
  
  //Proton module Short Veto plane added by kikawa
  G4Box* PSveto_box = new G4Box("PSveto_box",PSveto_x,PSveto_y,PSveto_z);
  G4LogicalVolume *PSvetoLV = new G4LogicalVolume(PSveto_box,Scinti,"PSvetoLV");

  PSvetoLV->SetVisAttributes(G4VisAttributes::Invisible);
  //PSvetoLV->SetVisAttributes(vetoVisAtt);


  //Rotation matrix for veto planes
  G4RotationMatrix *TB2LR = new G4RotationMatrix(G4ThreeVector(0,0,1.),90.*degree);


  //for 2D lattice
  G4VSolid* pHBarSolid = new G4Box("aHBarSolid",HbarLenX/2*mm,HbarLenY/2*mm,HbarLenZ/2*mm);
  G4VSolid* pVBarSolid = new G4Box("aVBarSolid",VbarLenX/2*mm,VbarLenY/2*mm,VbarLenZ/2*mm);
  G4VSolid* pSubHBarSolid = new G4Box("aSubHBarSolid",subHBarX/2*mm,subHBarY/2*mm,subHBarZ/2*mm);
  G4VSolid* pSubVBarSolid = new G4Box("aSubVBarSolid",subVBarX/2*mm,subVBarY/2*mm,subVBarZ/2*mm);
  //for plane
  G4VSolid* pHplnBarSolid = new G4Box("pHBarSolidpln",HplnbarLenX/2*mm,HplnbarLenY/2*mm,HplnbarLenZ/2*mm);
  G4VSolid* pVplnBarSolid = new G4Box("pVBarSolidpln",VplnbarLenX/2*mm,VplnbarLenY/2*mm,VplnbarLenZ/2*mm);
  //make space of lattice_bars
  for(int i=0;i<latice_sciNum;i++){
     //G4VSolid* pHSubtract =  new G4SubtractionSolid("",pHBarSolid,pSubHBarSolid,0,G4ThreeVector(((i+1)*sciSpace-HbarLenX/2-subHBarX/2)*mm,0*mm,(-HbarLenZ/2+subHBarZ/2)*mm));
     //G4VSolid* pVSubtract =  new G4SubtractionSolid("",pVBarSolid,pSubVBarSolid,0,G4ThreeVector(0*mm,((i+1)*sciSpace-VbarLenY/2-subVBarY/2)*mm,(VbarLenZ/2-subVBarZ/2)*mm));
     G4VSolid* pHSubtract =  new G4SubtractionSolid("",pHBarSolid,pSubHBarSolid,0,G4ThreeVector((i*sciSpace*2-HbarLenX/2-subHBarX/2 + firstdistance_mod5h)*mm,0*mm,(-HbarLenZ/2+subHBarZ/2)*mm));
     G4VSolid* pVSubtract =  new G4SubtractionSolid("",pVBarSolid,pSubVBarSolid,0,G4ThreeVector(0*mm,(i*sciSpace*2-VbarLenY/2-subVBarY/2 + firstdistance_mod5v)*mm,(VbarLenZ/2-subVBarZ/2)*mm));
     pHBarSolid = pHSubtract;
     pVBarSolid = pVSubtract;
  }

  G4LogicalVolume* pHBarLog = new G4LogicalVolume(pHBarSolid,Scinti,"pHBarLog");
  G4LogicalVolume* pVBarLog = new G4LogicalVolume(pVBarSolid,Scinti,"pVBarLog");
  G4LogicalVolume* pHplnBarLog = new G4LogicalVolume(pHplnBarSolid,Scinti,"pHplnBarLog");
  G4LogicalVolume* pVplnBarLog = new G4LogicalVolume(pVplnBarSolid,Scinti,"pVplnBarLog");

  G4VisAttributes* testVisAtt = new G4VisAttributes(G4Color(0.,0.7,0.));
  testVisAtt->SetForceWireframe(true);
  pHBarLog->SetVisAttributes(testVisAtt);
  pVBarLog->SetVisAttributes(testVisAtt);

  //B2///////////////////////////////////////////////
  //G4Box* Water_box = new G4Box("Water_box",50*cm,50*cm,100*cm);//2013/6/11
  G4Box* Water_box = new G4Box("Water_box",(CTargetX/2)*cm,(CTargetY/2)*cm,(CTargetZ/2)*cm);//2013/6/11
  G4LogicalVolume *WaterLV = new G4LogicalVolume(Water_box,Water,"WaterLV");
  G4VisAttributes* WaterVisAtt = new G4VisAttributes(G4Colour(0.,0.,1.));
  WaterLV->SetVisAttributes(WaterVisAtt);
  

  //POSITIONNING OF ALL THE ELEMENTS ====================================================================================================

  for(int k=start_mod;k<stop_mod;k++){

    //INGRID Fe
    if(k<14){
      //Module HO3 has gap 0.2cm shorter than other modules
      G4double Gap2;
      G4double iron_start2,scibar_start2;

      if(k==3){
        Gap2=Gap-0.2*cm; 
        iron_start2=iron_start+0.9*cm;
        scibar_start2=scibar_start+1*cm;
      }
      else{
        Gap2=Gap;
        iron_start2=iron_start;
        scibar_start2=scibar_start;
      }
    
      // 9 iron-blocs per module -----------------------------------------------------
      for(int i=0;i<9;i++){
        char ironname[30];
        sprintf(ironname,"iron[%d][%d]",k,i);
        G4double z = iron_start2 + Gap2*i;
        new G4PVPlacement(0,G4ThreeVector(0.,0.,z),ironLV,ironname,moduleLV[k],false,i+k*9 ); // the world in Module     
      }
    }//if(k<14)



    //WAGASCI
    else if(k==24){									
      //water	
      new G4PVPlacement(0,G4ThreeVector(0,0,0),WaterLV,"watertarget",moduleLV[k],false,0); 

      //mod4 veto planes
      G4double Gap2;

      //upstream
      Gap2=VetoGap;
      for(int i=0;i<CVetoNum;i++){
        G4double z = StartVetoupst_z + Vlayer5Z + Gap2*i; //2014/6/11
        for(int j=0;j<CChmax_VetoVupst;j++){
	  char name[100]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i,j);
          G4double x_scinti = StartVetoupst_v + 2*j*Vlayer5X; 
          new G4PVPlacement(0,G4ThreeVector(x_scinti,0.,z),vlayerLV5,name,moduleLV[24],false,j + (i)*CHMAX + k*CHMAX*PLNMAX);        
        } 
        for(int j=0;j<CChmax_VetoHupst;j++){
	  char name[100]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i,j); 
          G4double y_scinti = StartVetoupst_h + 2*j*Hlayer5Y;
          new G4PVPlacement(0,G4ThreeVector(0.,y_scinti,z+2*Hlayer5Z),hlayerLV5,name,moduleLV[24],false,j + (i)*CHMAX+ k*CHMAX*PLNMAX);
        }
      }

      //downstream
      Gap2=VetoGap;
      for(int i=0;i<CVetoNum;i++){
        G4double z = StartVetodown_z + Vlayer5Z + Gap2*i;

        for(int j=0;j<CChmax_VetoVdown;j++){
 	  char name[100]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i+10,j); 
          G4double x_scinti = StartVetodown_v + 2*j*Vlayer5X; 
          new G4PVPlacement(0,G4ThreeVector(x_scinti,0.,z),vlayerLV5,name,moduleLV[24],false,j + (i+10)*CHMAX + k*CHMAX*PLNMAX); //2014/7/2        
        }

        for(int j=0;j<CChmax_VetoHdown;j++){
	  char name[100]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i+10,j);
          G4double y_scinti = StartVetodown_h + 2*j*Hlayer5Y;
          new G4PVPlacement(0,G4ThreeVector(0.,y_scinti,z+2*Hlayer5Z),hlayerLV5,name,moduleLV[24],false,j + (i+10)*CHMAX+ k*CHMAX*PLNMAX); //2014/7/2
        }
      }


      //right side
      Gap2=VetoGap;
      for(int i=0;i<CVetoNum;i++){
        G4double z = StartVetoright_z - Vlayer7Z - Gap2*i;
        for(int j=0;j<CChmax_VetoVright;j++){
	  char name[100]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,-i+23,j);
          G4double x_scinti = StartVetoright_v + 2*j*Vlayer7X; 
          new G4PVPlacement(yrot,G4ThreeVector(z,0,x_scinti),vlayerLV7,name,moduleLV[24],false,j + (23-i)*CHMAX + k*CHMAX*PLNMAX); // 2014/7/2       
	}
        for(int j=0;j<CChmax_VetoHdown;j++){
	  char name[100]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,-i+23,j);
          G4double y_scinti = StartVetoright_h + 2*j*Hlayer7Y;
          new G4PVPlacement(yrot,G4ThreeVector(z-2*Hlayer7Z,y_scinti,0),hlayerLV7,name,moduleLV[24],false,j + (23-i)*CHMAX+ k*CHMAX*PLNMAX); // 2014/7/2
        }
      }

      //left side
      Gap2=VetoGap;
      for(int i=0;i<CVetoNum;i++){
        G4double z = StartVetoleft_z + Vlayer7Z + Gap2*i;
        for(int j=0;j<CChmax_VetoVleft;j++){//2014/6/11 
	  char name[100]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i+30,j); 
          G4double x_scinti = StartVetoleft_v + 2*j*Vlayer7X; 
          new G4PVPlacement(yrot,G4ThreeVector(z,0,x_scinti),vlayerLV7,name,moduleLV[24],false,j + (i+30)*CHMAX + k*CHMAX*PLNMAX); //2014/7/2       
	}
        for(int j=0;j<CChmax_VetoHleft;j++){//2014/6/11 
	  char name[100]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i+30,j);
          G4double y_scinti = StartVetoleft_h + 2*j*Hlayer7Y;
          new G4PVPlacement(yrot,G4ThreeVector(z+2*Hlayer7Z,y_scinti,0),hlayerLV7,name,moduleLV[24],false,j + (i+30)*CHMAX+ k*CHMAX*PLNMAX); // 2014/6/11
        }
      }
 
      //bottom
      Gap2=VetoGap;
      for(int i=0;i<CVetoNum;i++){
        G4double z = StartVetobottom_z - Vlayer8Z - Gap2*i;
        for(int j=0;j<CChmax_VetoVbottom;j++){ //2014/6/11
	  char name[100]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,43-i,j); 
          G4double x_scinti = StartVetobottom_v + 2*j*Vlayer8X; 
          new G4PVPlacement(xrot,G4ThreeVector(x_scinti,z,0),vlayerLV8,name,moduleLV[24],false,j + (43-i)*CHMAX + k*CHMAX*PLNMAX); //2014/7/2     
	}
        for(int j=0;j<CChmax_VetoHbottom;j++){ //2014/6/11
	  char name[100];
          sprintf(name,"hlayer[%d][%d][%d]",k,43-i,j);
          G4double y_scinti = StartVetobottom_h + 2*j*Hlayer8Y;
          new G4PVPlacement(xrot,G4ThreeVector(0,z-2*Hlayer8Z,y_scinti),hlayerLV8,name,moduleLV[24],false,j + (43-i)*CHMAX+ k*CHMAX*PLNMAX); //2014/7/2
        }
      }
 
      //up
      Gap2=VetoGap;
      for(int i=0;i<CVetoNum;i++){
        G4double z = StartVetoup_z - Vlayer8Z + Gap2*i;
        for(int j=0;j<CChmax_VetoVup;j++){
	  char name[100]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i+50,j); 
          G4double x_scinti = StartVetoup_v + 2*j*Vlayer8X; 
          new G4PVPlacement(xrot,G4ThreeVector(x_scinti,z,0),vlayerLV8,name,moduleLV[24],false,j + (i+50)*CHMAX + k*CHMAX*PLNMAX); //2014/7/2        
	}
        for(int j=0;j<CChmax_VetoHup;j++){
	  char name[100]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i+50,j);
          G4double y_scinti = StartVetoup_h + 2*j*Hlayer8Y;
          new G4PVPlacement(xrot,G4ThreeVector(0,z+2*Hlayer8Z,y_scinti),hlayerLV8,name,moduleLV[24],false,j + (i+50)*CHMAX+ k*CHMAX*PLNMAX); //2014/7/2
        }
      }

    }//if(k==24)

    else if(k==25){//pln in water//

      G4double Gap2; 
      Gap2=plnSpace*mm;
 
      for(int i=0;i<latice_plnNum+1;i++){//2014/6/11
        G4double z = -(waterLenZ/2.)*mm + (HbarLenY/2.)*mm + Gap2*i + firstdistance_mod5z*mm;//2014/6/11
        for(int j=0;j<40;j++){//2014/6/11 
	  char name[30]; 
          G4double x_scinti =  2*j*scibar2_y +offset_mod5_v + scibar2_y;//2014/7/4 
          sprintf(name,"vlayer[%d][%d][%d]",k,i+4,j);
          new G4PVPlacement(0,G4ThreeVector(x_scinti,0.,z),vlayerLV6,name,WaterLV,false,j + (i+4)*CHMAX + k*CHMAX*PLNMAX ); // in Module        

          G4double y_scinti =  2*j*scibar2_y +offset_mod5_h + scibar2_y;//2014/7/4   
          sprintf(name,"hlayer[%d][%d][%d]",k,i+4,j); 
          new G4PVPlacement(0,G4ThreeVector(0.,y_scinti,z+(HbarLenY+spacedistance_mod5)*mm),hlayerLV6,name,WaterLV,false,j + (i+4)*CHMAX + k*CHMAX*PLNMAX); // in Module
        }
      }


      //scintillator 3Dlattice
      for(int pln=0;pln<latice_plnNum;pln++){
 	        //positioning 2D lattice 
 	 	for(int j=0;j<latice_sciNum;j++){
		    std::stringstream VbarName;
		    VbarName << "VBar_pln:" << pln*2+4 << "_sci:" << j;
		    new G4PVPlacement(0, G4ThreeVector((-HbarLenX/2+j*sciSpace*2-subHBarX/2 + firstdistance_mod5v)*mm,0*mm,(pln*plnSpace-waterLenZ/2.+HbarLenZ/2.+firstdistance_mod5z + spacedistance_mod5*2 + HbarLenY*2.)*mm),pVBarLog,VbarName.str().c_str(),WaterLV,false, j + (pln*2+4)*CHMAX + (k+1)*CHMAX*PLNMAX,0);
		}
  		for(int j=0;j<latice_sciNum;j++){
		    std::stringstream HbarName;
		    HbarName << "HBar_pln:" << pln*2+4 << "_sci:" << j;
		    new G4PVPlacement(0, G4ThreeVector(0*mm,(-VbarLenY/2+j*sciSpace*2-subVBarY/2 + firstdistance_mod5h)*mm,(pln*plnSpace-waterLenZ/2.+VbarLenZ/2.+firstdistance_mod5z + spacedistance_mod5*2 + HbarLenY*2.)*mm),pHBarLog,HbarName.str().c_str(),WaterLV,false, j + (pln*2+4)*CHMAX + (k+1)*CHMAX*PLNMAX,0);
		}

 	        //positioning 2D lattice 
 	 	for(int j=0;j<latice_sciNum;j++){
		    std::stringstream VbarName;
		    VbarName << "VBar_pln:" << pln*2+4+1 << "_sci:" << j;
		    new G4PVPlacement(0, G4ThreeVector((-HbarLenX/2+j*sciSpace*2-subHBarX/2 + firstdistance_mod5v)*mm,0*mm,(pln*plnSpace-waterLenZ/2.+HbarLenZ/2.+firstdistance_mod5z + spacedistance_mod5*2 + HbarLenY*2. + HbarLenZ + spacedistance_mod5)*mm),pVBarLog,VbarName.str().c_str(),WaterLV,false, j + (pln*2+4+1)*CHMAX + (k+1)*CHMAX*PLNMAX,0);
		}
  		for(int j=0;j<latice_sciNum;j++){
		    std::stringstream HbarName;
		    HbarName << "HBar_pln:" << pln*2+4+1 << "_sci:" << j;
		    new G4PVPlacement(0, G4ThreeVector(0*mm,(-VbarLenY/2+j*sciSpace*2-subVBarY/2 + firstdistance_mod5h)*mm,(pln*plnSpace-waterLenZ/2.+VbarLenZ/2.+firstdistance_mod5z + spacedistance_mod5*2 + HbarLenY*2. + HbarLenZ + spacedistance_mod5)*mm),pHBarLog,HbarName.str().c_str(),WaterLV,false, j + (pln*2+4+1)*CHMAX + (k+1)*CHMAX*PLNMAX,0);
		}

      }


    }//if(k==25)

    else if(k==21){             								//forward
      G4double Gap2;
      Gap2=MRDGap;
    
      // 9 iron-blocs per module -----------------------------------------------------
      for(int i=0;i<30;i++){
        char ironname[30];
        sprintf(ironname,"iron[%d][%d]",k,i);
        G4double z = Startmod1_iron_z + Gap2*(i) + Iron3Z;
        new G4PVPlacement(0,G4ThreeVector(0.,0.,z),ironLV3,ironname,moduleLV[k],false,i+k*30);  
      }

      // 35 planes of scintillator per module-----------------------------------------
      for(int i=0;i<34;i++){
        G4double z = Startmod1_sci_z + Gap2*(i-2) + Vlayer3Z;
        for(int j=0;j<80;j++){ 
	    char name[30]; 
            sprintf(name,"vlayer[%d][%d][%d]",k,i,j); 
            G4double x_scinti =  Startmod1_sci_v + 2*j*Vlayer3X + Vlayer3X; //2014/6/11
            new G4PVPlacement(0,G4ThreeVector(x_scinti,0.,z),vlayerLV3,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); // in Module//2014/6/11        
	}
        for(int j=0;j<40;j++){ 
	    char name[30]; 
            sprintf(name,"hlayer[%d][%d][%d]",k,i,j);
            G4double y_scinti =  Startmod1_sci_h + 2*j*Hlayer3Y + Hlayer3Y;  //2014/6/11   
            new G4PVPlacement(0,G4ThreeVector(0.,y_scinti,z+2*Hlayer3Z),hlayerLV3,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); // in Module//2014/6/11
        }
      }


    }//if(k==21) 
   
    //left side MRD
    else if(k==22){          
      G4double Gap2;
      Gap2=MRDGap;

      // 10 iron-blocs per module -----------------------------------------------------
      for(int i=0;i<10;i++){
        char ironname[30];
        sprintf(ironname,"iron[%d][%d]",k,i);
        G4double z = Startmod2_iron_z + Gap2*(i) + Iron2Z;
        new G4PVPlacement(yrot,G4ThreeVector(z,0.,0.),ironLV2,ironname,moduleLV[k],false,i+k*50); 
      }

      // 14 planes of scintillator per module-----------------------------------------
      for(int i=0;i<14;i++){
        G4double z = Startmod2_sci_z + Gap2*(i-2) + Vlayer2Z;
        for(int j=0;j<64;j++){ 
  	  char name[30]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i,j);
          G4double y_scinti =  Startmod2_sci_v + 2*j*Vlayer2X + Vlayer2X; //2014/6/11
          new G4PVPlacement(yrot,G4ThreeVector(z,0.,y_scinti),vlayerLV2,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); 
	}
        for(int j=0;j<40;j++){ 
  	  char name[30]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i,j);
          G4double x_scinti =  Startmod2_sci_h + 2*j*Hlayer2Y + Hlayer2Y; //2014/6/11
          new G4PVPlacement(yrot,G4ThreeVector(z+2*Hlayer2Z,x_scinti,0.),hlayerLV2,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX);      
        }
      }

    }//if(k==22)

    //right side MRD
    else if(k==28){          
      G4double Gap2;
      Gap2=MRDGap;

      // 10 iron-blocs per module -----------------------------------------------------
      for(int i=0;i<10;i++){
        char ironname[30];
        sprintf(ironname,"iron[%d][%d]",k,i);
        G4double z = Startmod2_iron_z + Gap2*(i);
        new G4PVPlacement(yrot,G4ThreeVector(-z,0.,0.),ironLV2,ironname,moduleLV[k],false,i+k*50); 
      }

      // 14 planes of scintillator per module-----------------------------------------
      for(int i=0;i<14;i++){
        G4double z = Startmod2_sci_z + Gap2*(i-2) + Vlayer2Z;
        for(int j=0;j<64;j++){ 
  	  char name[30]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i,j);    
          G4double y_scinti =  Startmod2_sci_v + 2*j*Vlayer2X + Vlayer2X; //2014/6/11
          new G4PVPlacement(yrot,G4ThreeVector(-(z),0.,y_scinti),vlayerLV2,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); 
	}
        for(int j=0;j<40;j++){ 
  	  char name[30]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i,j); 
          G4double x_scinti =  Startmod2_sci_h + 2*j*Hlayer2Y + Hlayer2Y; //2014/6/11
          new G4PVPlacement(yrot,G4ThreeVector(-(z+2*Hlayer2Z),x_scinti,0.),hlayerLV2,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX);      
        }
      }

    }//if(k==28)

    //botom side MRD
    else if(k==29){          
      G4double Gap2;
      G4double iron_start2,scibar_start2;

      Gap2=MRDGap;
      iron_start2=-16.0*cm+1.5*cm+(1.+1.+1.1)*cm;

      // 3 iron-blocs per module -----------------------------------------------------
//      for(int i=0;i<3;i++){
//        char ironname[30];
//        G4double offz = 0.00*m;//////////////////////////////////////
//        
//        sprintf(ironname,"iron[%d][%d]",k,i);
//        G4double z = iron_start2 + Gap2*i;
//        new G4PVPlacement(0,G4ThreeVector(0.,-(z+offz),0.),ironLV4,ironname,moduleLV[k],false,i+k*50); 
//      }

      // 4 planes of scintillator per module-----------------------------------------
      //for(int i=0;i<4;i++){
      for(int i=0;i<3;i++){
        G4double z = Startmod9_sci_z + Vlayer9Y + Gap2*i; 
        for(int j=0;j<40;j++){ 
  	  char name[30];
          sprintf(name,"vlayer[%d][%d][%d]",k,i,j);
          G4double y_scinti =  Startmod9_sci_v + 2*j*Vlayer9X + Vlayer9X;//2014/6/11     
          new G4PVPlacement(0,G4ThreeVector(y_scinti,-(z),0.),vlayerLV9,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); 
	}
        for(int j=0;j<60;j++){ 
  	  char name[30]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i,j);
          G4double x_scinti =  Startmod9_sci_h + 2*j*Hlayer9Z + Hlayer9Z;//2014/6/11 
          new G4PVPlacement(0,G4ThreeVector(0.,-(z+2*Hlayer9Y),x_scinti),hlayerLV9,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX);      
        }
      }

    }//if(k==29)

    //up side MRD
    else if(k==30){          
      G4double Gap2;
      G4double iron_start2,scibar_start2;

      Gap2=MRDGap;
      iron_start2=-16.0*cm+1.5*cm+(1.+1.+1.1)*cm;
      scibar_start2=-16.0*cm;

      // 3 iron-blocs per module -----------------------------------------------------
//      for(int i=0;i<3;i++){
//        char ironname[30];
//        G4double offz = 0.00*m;//////////////////////////////////////
//        
//        sprintf(ironname,"iron[%d][%d]",k,i);
//        G4double z = iron_start2 + Gap2*i;
//        new G4PVPlacement(0,G4ThreeVector(0.,(z+offz),0.),ironLV4,ironname,moduleLV[k],false,i+k*50); 
//      }

      // 4 planes of scintillator per module-----------------------------------------
      //for(int i=0;i<4;i++){
      for(int i=0;i<3;i++){
        G4double z = Startmod9_sci_z + Vlayer9Y + Gap2*i; 

        for(int j=0;j<40;j++){ 
  	  char name[30]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i,j);    
          G4double y_scinti =  Startmod9_sci_v + 2*j*Vlayer9X + Vlayer9X;//2014/6/11     
          new G4PVPlacement(0,G4ThreeVector(y_scinti,(z),0.),vlayerLV9,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); 
	}
        for(int j=0;j<60;j++){ 
  	  char name[30]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i,j);
          G4double x_scinti =  Startmod9_sci_h + 2*j*Hlayer9Z + Hlayer9Z;//2014/6/11 
          new G4PVPlacement(0,G4ThreeVector(0.,(z+2*Hlayer9Y),x_scinti),hlayerLV9,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX);      
        }
      }

    }//if(k==30)






    //upstream
    else if(k==23){             								
      G4double Gap2;
      Gap2=UpstGap;						///////////////////////////////////
      
      // 3 planes of scintillator per module-----------------------------------------
      for(int i=0;i<3;i++){
        G4double z = -(Startmod3_sci_z + Gap2*i +Vlayer3Z);
        for(int j=0;j<80;j++){ 
	  char name[30]; 
          sprintf(name,"vlayer[%d][%d][%d]",k,i,j);
          G4double x_scinti = Startmod3_sci_v + 2*j*Vlayer3X + Vlayer3X; //2014/6/11
          new G4PVPlacement(0,G4ThreeVector(x_scinti,0.,z),vlayerLV3,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX);         
	}
        for(int j=0;j<40;j++){ 
	  char name[30]; 
          sprintf(name,"hlayer[%d][%d][%d]",k,i,j);
          G4double y_scinti = Startmod3_sci_h + 2*j*Hlayer3Y + Hlayer3Y; //2014/6/11
          new G4PVPlacement(0,G4ThreeVector(0.,y_scinti,z-2*Hlayer3Z),hlayerLV3,name,moduleLV[k],false,j + i*CHMAX + k*CHMAX*PLNMAX); 
        }
      }    
    }//if(k==23)

  }//for(int k=start_mod;k<stop_mod;k++){

///////////////////////////////////////////////////



  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  
  G4String hlayerSDname = "Ingrid/hlayerSD";
  ahlayerSD = new IngridHLayerSD( hlayerSDname );
  SDman->AddNewDetector( ahlayerSD );
  //hlayerLV->SetSensitiveDetector( ahlayerSD );////////////////
  //hlayer2LV->SetSensitiveDetector( ahlayerSD );
  hlayerLV2->SetSensitiveDetector( ahlayerSD );
  hlayerLV3->SetSensitiveDetector( ahlayerSD );
  hlayerLV4->SetSensitiveDetector( ahlayerSD );
  hlayerLV5->SetSensitiveDetector( ahlayerSD );
  hlayerLV6->SetSensitiveDetector( ahlayerSD );
  hlayerLV7->SetSensitiveDetector( ahlayerSD );
  hlayerLV8->SetSensitiveDetector( ahlayerSD );
  hlayerLV9->SetSensitiveDetector( ahlayerSD );
  //hscint_intLV->SetSensitiveDetector( ahlayerSD );
  //hscint2_intLV->SetSensitiveDetector( ahlayerSD );//SciBar type added by kikawa
  //hscint3_intLV->SetSensitiveDetector( ahlayerSD );//INGRID type added by kikawa

  pHBarLog->SetSensitiveDetector( ahlayerSD );//B2_lattice added by nchikuma
  pHplnBarLog->SetSensitiveDetector( ahlayerSD );//B2_lattice added by nchikuma
 
  G4String vlayerSDname = "Ingrid/vlayerSD";
  avlayerSD = new IngridVLayerSD( vlayerSDname );
  SDman->AddNewDetector( avlayerSD );
  //vlayerLV->SetSensitiveDetector( avlayerSD );////////////////
  //vlayer2LV->SetSensitiveDetector( avlayerSD );
  vlayerLV2->SetSensitiveDetector( avlayerSD );
  vlayerLV3->SetSensitiveDetector( avlayerSD );
  vlayerLV4->SetSensitiveDetector( avlayerSD );
  vlayerLV5->SetSensitiveDetector( avlayerSD );
  vlayerLV6->SetSensitiveDetector( avlayerSD );
  vlayerLV7->SetSensitiveDetector( avlayerSD );
  vlayerLV8->SetSensitiveDetector( avlayerSD );
  vlayerLV9->SetSensitiveDetector( avlayerSD );
  //vscint_intLV->SetSensitiveDetector( avlayerSD );
  //vscint2_intLV->SetSensitiveDetector( avlayerSD );//SciBar type added by kikawa
  //vscint3_intLV->SetSensitiveDetector( avlayerSD );//INGRID type added by kikawa

  pVBarLog->SetSensitiveDetector( avlayerSD );//B2_lattice added by nchikuma
  pVplnBarLog->SetSensitiveDetector( avlayerSD );//B2_lattice added by nchikuma
 
  G4String vetoSDname = "Ingrid/vetoSD";
  avetoSD = new IngridVetoSD( vetoSDname );
  SDman->AddNewDetector( avetoSD );

  //SvetoLV->SetSensitiveDetector( avetoSD );
  //LvetoLV->SetSensitiveDetector( avetoSD );
  //PSvetoLV->SetSensitiveDetector( avetoSD );//Veto for Proton Module added by kikawa
  //PLvetoLV->SetSensitiveDetector( avetoSD );//Veto for Proton Module added by kikawa

  return worldPV;

}

//___________________________________________________________________________________________________________

void IngridDetectorConstruction::DefineSpace()
{
  // The length at World volume, volume of 7 modules, and module volume means the half length.
  WorldX = CWorldX*m;
  WorldY = CWorldY*m;
  WorldZ = CWorldZ*m;

  //The dimension of Hall dirt volume
  HallDirtRadiusMin = CHallDirtRadiusMin*m;
  HallDirtRadiusMax = CHallDirtRadiusMax*m;
  HallDirtHeight    = CHallDirtHeight*m;
  HallDirtSPhi      = CHallDirtSPhi;
  HallDirtDPhi      = CHallDirtDPhi;
  HallDirtX         = CHallDirtX*m;
  HallDirtY         = CHallDirtY*m;
  HallDirtZ         = CHallDirtZ*m;
  HallX             = HallDirtX;
  HallZ             = HallDirtZ;

  //Volume of 7 modules
  HorizonX=CHorizonX*m;
  HorizonY=CHorizonY*m;
  HorizonZ=CHorizonZ*cm;

  //Volume of Proton module added by kikawa
  PHorizonZ=CPHorizonZ*cm;

  ModuleX=CModuleX*m;
  ModuleY=CModuleY*m;
  ModuleZ=CModuleZ*cm;

  //Proton Module volume
  PModuleZ=CPModuleZ*cm;
  
  //Positions of modules
  ModuleSpace= CModuleSpace*m;     // 120 + 30  distance between the centers of two consecutive modules
  ModuleStart= CModuleStart*m;     // -150*3 center of the first module

  Floorup = CFloorup*m;

  PillarX = CPillarX*m;
  PillarY = CPillarY*m;
  PillarZ = CPillarZ*m;

  PillarposX = CPillarposX*m;
  PillarposY = CPillarposY*m;
  PillarposZ = CPillarposZ*m;
  PillarposX_rev = CPillarposX_rev*m;

  WagaX = CWagaX*m;
  WagaY = CWagaY*m;
  WagaZ = CWagaZ*m;
  WagaposX = CWagaposX*m;
  WagaposY = CWagaposY*m;
  WagaposZ = CWagaposZ*m;

  WagaboxX = CWagaboxX*m;
  WagaboxY = CWagaboxY*m;
  WagaboxZ = CWagaboxZ*m;
  WagaboxforX = CWagaboxforX*m;
  WagaboxforY = CWagaboxforY*m;
  WagaboxforZ = CWagaboxforZ*m;
  WagaboxsideX = CWagaboxsideX*m;
  WagaboxsideY = CWagaboxsideY*m;
  WagaboxsideZ = CWagaboxsideZ*m;
  WagaboxbackX = CWagaboxbackX*m;
  WagaboxbackY = CWagaboxbackY*m;
  WagaboxbackZ = CWagaboxbackZ*m;
  WagaboxbottomX = CWagaboxbottomX*m;
  WagaboxbottomY = CWagaboxbottomY*m;
  WagaboxbottomZ = CWagaboxbottomZ*m;

  WagaboxposX = CWagaboxposX*m;
  WagaboxposY = CWagaboxposY*m;
  WagaboxposZ = CWagaboxposZ*m;
  WagaboxforposX = CWagaboxforposX*m;
  WagaboxforposY = CWagaboxforposY*m;
  WagaboxforposZ = CWagaboxforposZ*m;
  WagaboxsideposX = CWagaboxsideposX*m;
  WagaboxsideposY = CWagaboxsideposY*m;
  WagaboxsideposZ = CWagaboxsideposZ*m;
  WagaboxbackposX = CWagaboxbackposX*m;
  WagaboxbackposY = CWagaboxbackposY*m;
  WagaboxbackposZ = CWagaboxbackposZ*m;
  WagaboxbottomposX = CWagaboxbottomposX*m;
  WagaboxbottomposY = CWagaboxbottomposY*m;
  WagaboxbottomposZ = CWagaboxbottomposZ*m;

  Hlayer2X = CHlayer2X*m;  Hlayer2Y = CHlayer2Y*cm;  Hlayer2Z = CHlayer2Z*cm;
  Hlayer3X = CHlayer3X*m;  Hlayer3Y = CHlayer3Y*cm;  Hlayer3Z = CHlayer3Z*cm;
  Hlayer4X = CHlayer4X*m;  Hlayer4Y = CHlayer4Y*cm;  Hlayer4Z = CHlayer4Z*cm;
  Hlayer5X = CHlayer5X*m;  Hlayer5Y = CHlayer5Y*cm;  Hlayer5Z = CHlayer5Z*cm;
  Hlayer6X = CHlayer6X*m;  Hlayer6Y = CHlayer6Y*cm;  Hlayer6Z = CHlayer6Z*cm;
  Hlayer7X = CHlayer7X*m;  Hlayer7Y = CHlayer7Y*cm;  Hlayer7Z = CHlayer7Z*cm;
  Hlayer8X = CHlayer8X*m;  Hlayer8Y = CHlayer8Y*cm;  Hlayer8Z = CHlayer8Z*cm;
  Hlayer9X = CHlayer9X*m;  Hlayer9Y = CHlayer9Y*cm;  Hlayer9Z = CHlayer9Z*cm;
  Vlayer2X = CVlayer2X*cm;  Vlayer2Y = CVlayer2Y*m;  Vlayer2Z = CVlayer2Z*cm;
  Vlayer3X = CVlayer3X*cm;  Vlayer3Y = CVlayer3Y*m;  Vlayer3Z = CVlayer3Z*cm;
  Vlayer4X = CVlayer4X*cm;  Vlayer4Y = CVlayer4Y*m;  Vlayer4Z = CVlayer4Z*cm;
  Vlayer5X = CVlayer5X*cm;  Vlayer5Y = CVlayer5Y*m;  Vlayer5Z = CVlayer5Z*cm;
  Vlayer6X = CVlayer6X*cm;  Vlayer6Y = CVlayer6Y*m;  Vlayer6Z = CVlayer6Z*cm;
  Vlayer7X = CVlayer7X*cm;  Vlayer7Y = CVlayer7Y*m;  Vlayer7Z = CVlayer7Z*cm;
  Vlayer8X = CVlayer8X*cm;  Vlayer8Y = CVlayer8Y*m;  Vlayer8Z = CVlayer8Z*cm;
  Vlayer9X = CVlayer9X*cm;  Vlayer9Y = CVlayer9Y*cm;  Vlayer9Z = CVlayer9Z*m;

  VetoGap = CVetoGap*cm;
  MRDGap  = CMRDGap*cm;
  UpstGap  = CUpstGap*cm;

  StartVetodown_z = CStartVetodown_z*cm; StartVetodown_v = CStartVetodown_v*cm; StartVetodown_h = CStartVetodown_h*cm;
  StartVetoupst_z = CStartVetoupst_z*cm; StartVetoupst_v = CStartVetoupst_v*cm; StartVetoupst_h = CStartVetoupst_h*cm;
  StartVetoright_z = CStartVetoright_z*cm; StartVetoright_v = CStartVetoright_v*cm; StartVetoright_h = CStartVetoright_h*cm;
  StartVetoleft_z = CStartVetoleft_z*cm; StartVetoleft_v = CStartVetoleft_v*cm; StartVetoleft_h = CStartVetoleft_h*cm;
  StartVetobottom_z = CStartVetobottom_z*cm; StartVetobottom_v = CStartVetobottom_v*cm; StartVetobottom_h = CStartVetobottom_h*cm;
  StartVetoup_z = CStartVetoup_z*cm; StartVetoup_v = CStartVetoup_v*cm; StartVetoup_h = CStartVetoup_h*cm;

  
  Startmod1_iron_z = CStartmod1_iron_z*cm;
  Startmod1_sci_z  = CStartmod1_sci_z*cm;
  Startmod1_sci_v  = CStartmod1_sci_v*cm;
  Startmod1_sci_h  = CStartmod1_sci_h*cm;

  Startmod2_iron_z = CStartmod2_iron_z*cm;
  Startmod2_sci_z  = CStartmod2_sci_z*cm;
  Startmod2_sci_v  = CStartmod2_sci_v*cm;
  Startmod2_sci_h  = CStartmod2_sci_h*cm;

  Startmod3_sci_z  = CStartmod3_sci_z*cm;
  Startmod3_sci_v  = CStartmod3_sci_v*cm;
  Startmod3_sci_h  = CStartmod3_sci_h*cm;

  Startmod9_sci_z  = CStartmod9_sci_z*cm;
  Startmod9_sci_v  = CStartmod9_sci_v*cm;
  Startmod9_sci_h  = CStartmod9_sci_h*cm;


}

//___________________________________________________________________________________________________________

void IngridDetectorConstruction::DefineStructures()
{
  //Iron blocks
  iron_z= 3.25*cm;
  iron_xy= 62.0*cm;
  Gap= 10.7*cm;           // 6.5 + 2 +2*1.1 means " scinti-scinti-gap-iron-gap-scinti-scinti-... "
  iron_start= -48.15*cm;  // Position of the center of the first iron block  
	    		// = -54.5cm(1st plane surface) + 2cm(width of 1 plane) + 1.1cm(gap of scinti-iron) +3.25cm(half of iron)

  Iron2X = CIron2X*m;
  Iron2Y = CIron2Y*m;
  Iron2Z = CIron2Z*cm;
  Iron3X = CIron3X*m;
  Iron3Y = CIron3Y*m;
  Iron3Z = CIron3Z*cm;
  Iron4X = CIron4X*m;
  Iron4Y = CIron4Y*cm;
  Iron4Z = CIron4Z*m;
  
  //Same as before, but doubles instead of G4doubles for use by other functions
  Niron_start=-48.15;
  Niron_z=3.25;
  Nscibar_start=-54.5;
  NGap=10.7;
  NModuleSpace=150;

  //Scintillators
  scibar_x= 0.6*m;        // 120cm long
  scibar_y=2.5*cm;        // 5cm wide
  scibar_z= 5.0*mm;       // 1cm Thick

  //Scibar type for proton module added by kikawa
  scibar2_y=1.25*cm;        // 2.5cm wide
  scibar2_z= 6.5*mm;       // 1.3cm thick


  //Proton Module
  Pscibar_start=-40.95*cm;  
  Pveto_start=-40.95*cm-1.55*cm;  


  scibar_start=-54.5*cm;  // in Module , which is surface of 1st tracking x-layer
  scibar_xy_start= -57.5*cm; // in Module   57.5 = 12mai*5cm - 5cm/2

  //B2
  offset_mod5_v = -50.0*cm;
  offset_mod5_h = -50.0*cm;
  offset_mod5_vbar = 2.5*cm;
  offset_mod5_hbar = 2.5*cm;


  //Long veto planes
  Lveto_x= 0.65*m;        // 130cm long
  Lveto_y= 0.5*cm;        // 1cm thick
  Lveto_z= 2.5*cm;        // 5cm wide 
  veto_start=-52.5*cm;

  //Short veto planes
  Sveto_x=0.56*m;         // 112cm long
  Sveto_y=0.5*cm;         // 1cm thick
  Sveto_z=2.5*cm;         // 5cm wide 

  //Protn Module Long veto planes added by kikawa
  PLveto_x= 0.625*m;        // 125cm long
  PLveto_y= 0.5*cm;        // 1cm thick
  PLveto_z= 2.5*cm;        // 5cm wide 

  //Proton Module Short veto planes added by kikawa
  PSveto_x=0.6*m;         // 120cm long
  PSveto_y=0.5*cm;         // 1cm thick
  PSveto_z=2.5*cm;         // 5cm wide 


  //Distance between planes of Proton Module added by kikawa
  dist_first=2.7*cm;
  dist=2.3*cm;
  


  //**original
  SciVertex_x[0] = -23.8*mm; 
  SciVertex_x[1] = -24.3*mm; 
  SciVertex_x[2] = -24.3*mm; 
  SciVertex_x[3] = -23.8*mm; 
  SciVertex_x[4] =  23.8*mm; 
  SciVertex_x[5] =  24.3*mm; 
  SciVertex_x[6] =  24.3*mm; 
  SciVertex_x[7] =  23.8*mm;

  SciVertex_y[0] = - 5. *mm; 
  SciVertex_y[1] = - 0.5*mm; 
  SciVertex_y[2] =   0.5*mm; 
  SciVertex_y[3] =   5. *mm; 
  SciVertex_y[4] =   5. *mm; 
  SciVertex_y[5] =   0.5*mm; 
  SciVertex_y[6] =  -0.5*mm; 
  SciVertex_y[7] =  -5. *mm; 

 

}

//___________________________________________________________________________________________________________

void IngridDetectorConstruction::DefineMaterial()
{
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4String name, symbol;
  G4int nel;
  G4double iz;

  a = 14.01*g/mole;
  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", iz=7., a);
  a = 16.00*g/mole;
  G4Element* elO = new G4Element(name="Oxigen", symbol="O", iz=8., a);
  a = 1.01*g/mole;
  G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1., a);
  a = 12.01*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
  a = 28.1*g/mole;
  G4Element* elSi = new G4Element(name="Silicon", symbol="Si", z=14., a);
  a = 40.1*g/mole;
  G4Element* elCa = new G4Element(name="Calusium", symbol="Ca", z=20., a);
  a = 23.0*g/mole;
  G4Element* elNa = new G4Element(name="Sodium", symbol="Na", z=11., a);
  a = 55.8*g/mole;
  G4Element* elFe = new G4Element(name="Iron", symbol="Fe", z=26., a);
  a = 27.0*g/mole;
  G4Element* elAl = new G4Element(name="Aluminium", symbol="Al", z=13., a);

  //Air
  density = 1.29*mg/cm3;
  Air = new G4Material(name="Air", density, nel=2);
  Air->AddElement(elN, .7);
  Air->AddElement(elO, .3);

  //Iron
  a = 55.845*g/mole;
  density = 7.86*g/cm3;
  Fe = new G4Material(name="Iron", z=26., a, density);

  //Water
  density = 1.000*g/cm3;
  Water = new G4Material(name="Water",density,nel=2);
  Water->AddElement(elH,2);
  Water->AddElement(elO,1);

  //Scintillator
  density = 1.032*g/cm3;
  Scinti = new G4Material(name="Scintillator", density, nel=2);
  Scinti->AddElement(elC, 9);
  Scinti->AddElement(elH, 10);

  //Concrete
  density = 2.2*g/cm3;
  Concrete = new G4Material(name="Concrete", density, nel=6);

  Concrete->AddElement(elO, .53);
  Concrete->AddElement(elSi, .335);
  Concrete->AddElement(elCa, 0.06);
  Concrete->AddElement(elNa, 0.015);
  Concrete->AddElement(elFe, 0.02);
  Concrete->AddElement(elAl, 0.04);

}
