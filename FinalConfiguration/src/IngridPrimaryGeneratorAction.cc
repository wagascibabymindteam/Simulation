#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/RandGauss.h"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "globals.hh"

#include "IngridPrimaryGeneratorAction.hh"
#include "IngridDetectorConstruction.hh"
#include "IngridRunAction.hh"
#include "Const.hh"

// IRON 120x120x6.5 -------------------------

//

/* new value ?
const double total_mass_fe = 6.6165e3; //kg
const double total_mass_sci = 3.1738e2; //kg
*/

const double total_mass_fe = 99.54; //ton
const double total_mass_sci = 3.74; //ton
const double scinti_start = -54.5;  // the surface of the first scintillator by akira
const double iron_start = scinti_start + 2.0 + 1.1;  // the surface fo the first scinti + 2 scnti + air gap  by akira
const double width_fe = 6.5; // cm
const double width_sci = 2.0; // 1.0cm * 2
const double GAP = 10.7; // 6.5 + 2 + 2.2

//const double HallX = -216.7; //cm 
const double HallX = -322.2; //cm //2014/6/11
const double HallZ = 170.;    //cm
//const double HallRadiusMax = 1320.;//cm
//const double HallRadiusMax = 1150.;//cm
//const double HallRadiusMax = 1350.;//cm //change for B2 2014/1/9
//const double HallRadiusMax = 1395.;//cm //2014/6/11
const double HallRadiusMax = 1695.;//cm //2014/8/24
//const double HallRadiusMin = 850.;//cm
const double HallRadiusMin = 895.;//cm  //2014/6/11

//for Proton Module added by kikawa
//const double total_mass_sci_pm = 0.556 ;//ton (total mass)
const double total_mass_sci_pm = 0.56904 ;//ton (total mass)
const double total_mass_front_pm = 0.028848 ;//ton (total mass of front veto)
const double ingrid_width = 1 ;//(cm) (total mass of ingrid type)
const double scibar_width = 1.3; //(cm) (total mass of scibar type)
const double width_ingrid =1.0; //INGRID type 
const double width_scibar =1.3; //SciBar type 
const double scibar_region=44.2;//(cm)
const double sciing_region=39.1;//(cm)
const double ingrid_region=34;//(cm)
const double Pscinti_start=-40.95;//(cm)
const double distance_first=2.7;//(cm)
const double distance_pln=2.3;//(cm)
const double diff=-0.15;//(cm) difference of scibar and ingrid type start

//for Mod03
const double GAP03 = GAP - 0.2;
const double scinti_start03 = scinti_start + 1.0;
const double iron_start03 = iron_start + 0.9;

//#define MOD3
//#define DEBUG 
//#define DEBUG2 

//
IngridPrimaryGeneratorAction::
IngridPrimaryGeneratorAction(Neut *neut0,IngridRunAction* rac, IngridEventAction* evt,int nd,int flavor0)
  :runaction(rac)
{
  eventaction = evt;
  neut_fe = neut0;
  module_mode = nd;
  neutrino_flavor = flavor0;
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;

  runaction->NotEntry = 0;
}

//
IngridPrimaryGeneratorAction::~IngridPrimaryGeneratorAction()
{
  if( particleGun!=NULL ) { delete particleGun; particleGun=NULL; }
}

//
void IngridPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  SecondaryVector Secondary;
  Neut *neut = neut_fe;
  int fdid = 0;
  int mode = 0;
  float pos[3];
  int ID=-1;
  float direction[3];
  int vertex_flag=0;
  int flayer;
  double prob;//for Proton Module
  int scitype;//scintillator type

  // start loop of neut file
  while(1){

    mode = neut->NtupleReadEvent(Secondary,direction);
    if( mode==-1111 ){
      G4cout <<"Aboart Run (mode =" << mode << G4endl;
      G4RunManager* runManager = G4RunManager::GetRunManager();
      eventaction->SetWriteFlag(-1); 
      runManager->AbortRun(1);
      return;
    }

    // Check flavor ====================
//    G4cout << "mode "    << (neut->Vector).Neutrino.ProductionMode << "\n";
    int  neutrino_flavor_tmp =  (int)(((neut->Vector).Neutrino.ProductionMode)/10);
//    G4cout << "flavor " << neutrino_flavor_tmp << "\n";
    if( neutrino_flavor_tmp != neutrino_flavor ) {
#ifdef DEBUG
      G4cout << " === This neutrino id : " << neutrino_flavor_tmp
             << " ,not selected now === " << G4endl;
#endif
      continue;
    }

  // Define neutrino interaction vertex
    fdid = (neut->Vector).Neutrino.FDID;

    // X-Y vertex
    pos[0] = (neut->Vector).Neutrino.x;
    pos[1] = (neut->Vector).Neutrino.y;



//B2//////////////////////////////////
    if( fdid==5 && module_mode==5) {//change 2to5
	pos[2] = -75.0 + (G4UniformRand())*150.0;
    }
    if( fdid==7 && module_mode==5) {//change 2to5
	//pos[2] = -75.0 + (G4UniformRand())*150.0;
	pos[2] = -100.0 + (G4UniformRand())*200.0;//2014/6/11
    }

//////////////////////////////////


    // jnubeam ndid = 7 (INGRID-upstream surface for BG study)
//commentout for B2
/*    else if(fdid==7){ // jnubeam ndid = 7(INGRID-upstream surface for BG study 
      G4double lx = pos[0]- HallX;
      if( fabs(lx) < HallRadiusMin ){
	pos[2] = -1.0 * sqrt( HallRadiusMin * HallRadiusMin - lx * lx ) - G4UniformRand()*(HallRadiusMax-HallRadiusMin)+HallZ;
      }
      else{
	pos[2] = -1.0 *  G4UniformRand()*(HallRadiusMax-HallRadiusMin)+HallZ;
	//pos[2] = -1.*G4UniformRand()*(HallRadiusMax-HallRadiusMin)/370. * (1261.7-fabs(lx))+HallZ;
      }
    }
*/



    // jnubeam ndid = 8 (B2-upstream surface for BG study)
    else if(fdid==8){ // jnubeam ndid = 8(INGRID-upstream surface for BG study 
      //G4double lx = pos[0]- 350;
      G4double lx = pos[0]- (B2OFFX+HallX);//2014/6/13
      if( fabs(lx) < HallRadiusMin ){
	pos[2] = -1.0 * sqrt( HallRadiusMin * HallRadiusMin - lx * lx ) - G4UniformRand()*(HallRadiusMax-HallRadiusMin)+HallZ;
      }
      else{
	pos[2] = -1.0 *  G4UniformRand()*(HallRadiusMax-HallRadiusMin)+HallZ;
      }
    }


    // jnubeam ndid = 9 (B2-floor for BG study)
    else if(fdid==9){ // jnubeam ndid = 9(INGRID-upstream surface for BG study 
	pos[2] = 200.0  -   (G4UniformRand())*1050.0;
    }

    // jnubeam ndid = 6 (B2-Pillar for BG study)
    else if(fdid==6){ // jnubeam ndid = 9(INGRID-upstream surface for BG study 
	pos[2] = 200.0  -   (G4UniformRand())*400.0;
    }


    //B2 Fe BG study
    //side Fe
    else if( fdid==7 && module_mode==6) {
	//pos[2] = (G4UniformRand())*250. - 125.;
	pos[2] = (G4UniformRand())*300. - 150.; //2014/7/28
    }
    //downstream Fe
    else if( fdid==7 && module_mode==7) {
	flayer = (int)(30*(G4UniformRand()));     // 0 < 30*rand < 30
	//pos[2] = flayer*7.7 + (G4UniformRand())*3.5;
	pos[2] = flayer*7.7 + (G4UniformRand())*3.0;
    }
    //opposite side Fe
    else if( fdid==7 && module_mode==8) {
	//pos[2] = (G4UniformRand())*250. - 125.;
	pos[2] = (G4UniformRand())*300. - 150.;  //2014/7/28
    }





// define vertex module
    ID = -1;


//for ND280 B2
    if( fdid==5 && module_mode == 5 ) {//change 2to5////////////////////
	if(fabs(pos[0])<=75 && fabs(pos[1]) <=75){
	ID = 17;
	goto NEXTSTEP;
	}
    }

//for B2
    if( fdid==7 && module_mode == 5 ) {//change 2to5////////////////////
	//if(fabs(pos[0])<=75 && fabs(pos[1]) <=75){
	if(fabs(pos[0])<=50. && fabs(pos[1]) <=50.){//2014/6/11
	ID = 19;
	goto NEXTSTEP;
	}
    }


//for B2-upstream surface 
    if( fdid==8 && module_mode == 5 ) {
	//if( fabs(pos[0]-350) < HallRadiusMin ){
	//if( fabs(pos[0]-(B2OFFX + HallX)) < HallRadiusMin ){//2014/6/13
	ID = 20;
	goto NEXTSTEP;
	//}
    }

//for B2-floor BG 
    if( fdid==9 && module_mode == 5 ) {
      //G4double lx = pos[0]- 350;
      G4double lx = pos[0]- (B2OFFX + HallX);
	//if( (lx*lx + pos[2]*pos[2] < HallRadiusMin*HallRadiusMin) && fabs(pos[1]) <=185){
	if( (lx*lx + pos[2]*pos[2] < HallRadiusMin*HallRadiusMin) && fabs(pos[1]) <= (B2FLOORDEPTH-B2OFFYFLOOR)/2.){
	pos[2] = pos[2] + HallZ;
	ID = 21;
	goto NEXTSTEP;
	}
    }

//for B2-Pillar BG
    if( fdid==6 && module_mode == 5 ) {
        if( fabs(pos[0]) <= 50 && fabs(pos[1]) <= 150  ) {
          ID = 25;
          goto NEXTSTEP;
        }
    }


//for B2 Fe BG

    //side Fe
    if( fdid==7 && module_mode == 6){
      //pos[0]= pos[0] + 3.0;//temporary
      flayer = (int) pos[0]/7.7; 
      //if( (pos[0] - 7.7*flayer < 3.5) && pos[0] > 0 && flayer < 10 && fabs(pos[1])<=125. ){
      if( (pos[0] - 7.7*flayer < 3.0) && pos[0] > 0 && flayer < 10 && fabs(pos[1])<=100. ){
         ID = 22;
         goto NEXTSTEP;
      }
    }
    //downstream Fe
    if( fdid==7 && module_mode == 7){
       //if(fabs(pos[0])<=125 && fabs(pos[1]) <=125){
       if(fabs(pos[0])<=200 && fabs(pos[1]) <=100){
	  ID = 23;
          goto NEXTSTEP;
       }
    }
    //opposite side Fe
    if( fdid==7 && module_mode == 8){
      //pos[0]= pos[0] + 3.0;//temporary
      flayer = (int) pos[0]/7.7; 
      //if( (pos[0] - 7.7*flayer < -3.5) && pos[0] < 0 && flayer > -10 && fabs(pos[1])<=125. ){
      if( (pos[0] - 7.7*flayer < -3.0) && pos[0] < 0 && flayer > -10 && fabs(pos[1])<=100. ){
         ID = 24;
         goto NEXTSTEP;
      }
    }


    // count events which have vertex out of modules
#ifdef DEBUG
    G4cout << "##### Interaction vertex is out of modules #####" << G4endl;
    G4cout << "##### Skip this event                      #####" << G4endl;
#endif
    runaction->NotEntry++; 

  } // end while loop

//
NEXTSTEP:


    if(ID == 17)  pos[2] = pos[2] + B2OFF;             /////////////////////////////
    else if(ID == 19){ 
	 pos[0] = pos[0] - B2OFFX;             /////////////////////////////
	 pos[1] = pos[1] - B2OFFY;             /////////////////////////////
	 pos[2] = pos[2] + B2OFFZ;             /////////////////////////////
    }
    else if(ID == 20){ 
	 pos[0] = pos[0] - B2OFFX;             /////////////////////////////
	 pos[1] = pos[1] - B2OFFY;             /////////////////////////////
    }
    else if(ID == 21){ 
	 pos[0] = pos[0] - B2OFFX;             /////////////////////////////
	 pos[1] = pos[1] - B2OFFYFLOOR - (B2FLOORDEPTH-B2OFFYFLOOR)/2.;             /////////////////////////////
    }
    else if(ID == 22){ 
	 pos[0] = pos[0] - B2OFFX + B2OFFXFE;             /////////////////////////////
	 pos[1] = pos[1] - B2OFFY;             /////////////////////////////
	 pos[2] = pos[2] + B2OFFZ;             /////////////////////////////
    }
    else if(ID == 23){ 
	 pos[0] = pos[0] - B2OFFX;             /////////////////////////////
	 pos[1] = pos[1] - B2OFFY;             /////////////////////////////
	 pos[2] = pos[2] + B2OFFZ + B2OFFZFE;             /////////////////////////////
    }
    else if(ID == 24){ 
	 pos[0] = pos[0] - B2OFFX - B2OFFXFE;             /////////////////////////////
	 pos[1] = pos[1] - B2OFFY;             /////////////////////////////
	 pos[2] = pos[2] + B2OFFZ;             /////////////////////////////
    }
    else if(ID == 25){ 
	 pos[0] = pos[0] - B2PillarOFFX;             /////////////////////////////
	 pos[1] = pos[1] - B2PillarOFFY;             /////////////////////////////
	 pos[2] = pos[2] + B2PillarOFFZ;             /////////////////////////////
    }


    // Input Neut file info to output ROOT class
    neut->ID = ID;
    for(int i=0;i<3;i++) (runaction->vertex)[i] = pos[i];

    IngridSimVertexSummary* simvertex = new IngridSimVertexSummary();
    simvertex -> Clear();
    simvertex -> nutype   = neutrino_flavor;
    simvertex -> inttype  = (neut->Vector).Primary.Mode;
    simvertex -> nuE      = (neut->Vector).Neutrino.Energy;
    simvertex -> xnu      = pos[0];
    simvertex -> ynu      = pos[1];
    simvertex -> znu      = pos[2];
    simvertex -> mod      = ID;
    simvertex -> norm			= (neut->Vector).Neutrino.Norm;
    simvertex -> totcrsne	= (neut->Vector).neutcrs.Totcrsne;

    //removed for 11b (before using t2kreweight)                                                
    /*
    simvertex -> ng = (neut->Vector).Neutrino.ancestor.ng;
    for(int i=0;i<(neut->Vector).Neutrino.ancestor.ng;i++) {
      simvertex -> gpid.push_back   ( (neut->Vector).Neutrino.ancestor.gpid[i] );
      simvertex -> gmec.push_back   ( (neut->Vector).Neutrino.ancestor.gmec[i] );
      simvertex -> gcosbm.push_back ( (neut->Vector).Neutrino.ancestor.gcosbm[i] );
      simvertex -> gposx.push_back  ( (neut->Vector).Neutrino.ancestor.gvx[i] );
      simvertex -> gposy.push_back  ( (neut->Vector).Neutrino.ancestor.gvy[i] );
      simvertex -> gposz.push_back  ( (neut->Vector).Neutrino.ancestor.gvz[i] );
      simvertex -> gmomx.push_back  ( (neut->Vector).Neutrino.ancestor.gpx[i] );
      simvertex -> gmomy.push_back  ( (neut->Vector).Neutrino.ancestor.gpy[i] );
      simvertex -> gmomz.push_back  ( (neut->Vector).Neutrino.ancestor.gpz[i] );
    }
    */

    runaction  -> GetEvtSum() -> AddSimVertex( simvertex );

    G4cout.precision( 3 );

#ifdef DEBUG
    G4cout << "\n=== Neutrino Information from Jnubeam ===" << G4endl;
		G4cout << "Norm: " <<  (neut->Vector).Neutrino.Norm << G4endl;
		G4cout << "Totcrsne: " <<  (neut->Vector).neutcrs.Totcrsne << G4endl;
    G4cout << "ParentID: " << (neut->Vector).Neutrino.ParentID;
    G4cout << "  Neut Production Mode: " << (neut->Vector).Neutrino.ProductionMode;
    G4cout << "  Neutrino.FDID: " << (neut->Vector).Neutrino.FDID << G4endl;
    G4cout << "Neut interaction Mode: " << (neut->Vector).Primary.Mode << G4endl;
    G4cout << "Energy[GeV]: " << (neut->Vector).Neutrino.Energy;
    G4cout << "  Direction: {" << direction[0] << "," << direction[1] << "," << direction[2] << "}" << G4endl;
    G4cout << "Vertex(cm): {" << pos[0] << ", "<< pos[1] << ", "<< pos[2] << "}";
    G4cout << "  Module: " << ID << "\n\n";
#endif

    particleGun->SetParticlePosition(G4ThreeVector(pos[0]*cm,pos[1]*cm,pos[2]*cm));

    // Input Neut info for T2KReWeight to SK__h1 class
    runaction -> numnu = (neut->Vector).Primary.NumParticle;
    runaction -> mode  = (neut->Vector).Primary.Mode;
    for ( int i = 0; i<50; i++ ) {
      runaction -> ipnu[i] = (neut->Vector).Primary.ParticleID[i];
      runaction -> pnu[i] = (neut->Vector).Primary.AbsMomentum[i];
      for ( int j = 0 ; j < 3 ; j++ ){
        runaction -> dirnu[i][j] = (neut->Vector).Primary.Momentum[i][j] / (neut->Vector).Primary.AbsMomentum[i];
      }
    }

    runaction -> Crsx   = (neut->Vector).Crs.Crsx;
    runaction -> Crsy   = (neut->Vector).Crs.Crsy;
    runaction -> Crsz   = (neut->Vector).Crs.Crsz;
    runaction -> Crsphi = (neut->Vector).Crs.Crsphi;

    runaction -> Nvert = (neut->Vector).Fsi.Nvert;
    for (int ivert=0; ivert<150; ivert++) {
      runaction -> Iflgvert[ivert] = (neut->Vector).Fsi.Iflgvert[ivert];
      for (int j=0; j<3; j++)
        runaction -> Posvert[ivert][j] = (neut->Vector).Fsi.Posvert[ivert][j];
    }

    runaction -> Nvcvert = (neut->Vector).Fsi.Nvcvert;
    for (int ip=0; ip<900; ip++) {

      runaction -> Abspvert[ip]  = (neut->Vector).Fsi.Abspvert[ip];
      runaction -> Abstpvert[ip] = (neut->Vector).Fsi.Abstpvert[ip];
      runaction -> Ipvert[ip]    = (neut->Vector).Fsi.Ipvert[ip];
      runaction -> Iverti[ip]    = (neut->Vector).Fsi.Iverti[ip];
      runaction -> Ivertf[ip]    = (neut->Vector).Fsi.Ivertf[ip];

      for (int j=0; j<3; j++)
        runaction -> Dirvert[ip][j] = (neut->Vector).Fsi.Dirvert[ip][j];
    }

    runaction -> Fsiprob = (neut->Vector).Fsi.Fsiprob;
    runaction -> Numbndn = (neut->Vector).target_info.Numbndn;
    runaction -> Numbndp = (neut->Vector).target_info.Numbndp;
    runaction -> Numfrep = (neut->Vector).target_info.Numfrep;
    runaction -> Numatom = (neut->Vector).target_info.Numatom;
    runaction -> Ibound  = (neut->Vector).Fsi.Ibound;
    runaction -> Npvc    = (neut->Vector).Secondary.NumParticle;
    for (int i=0; i<100; i++) {
      runaction -> Ipvc[i]    = (neut->Vector).Secondary.ParticleID[i];
      runaction -> Ichvc[i]   = (neut->Vector).Secondary.TrackingFlag[i];
      runaction -> Iorgvc[i]  = (neut->Vector).Secondary.ParentID[i];
      runaction -> Iflvc[i]   = (neut->Vector).Secondary.InteractionCode[i];
      runaction -> Abspvc[i]  = (neut->Vector).Secondary.AbsMomentum[i];
      for (int j=0; j<3; j++)
        runaction -> Pvc[i][j]     = (neut->Vector).Secondary.Momentum[i][j];
    }


  // #############################################################################
  // ### Fill primary state info of partcle generated at neutrino interaction
  // #############################################################################
    /*
      NeutInfoSummary* neutinfo = new NeutInfoSummary();
  neutinfo -> Clear();
  neutinfo -> Mode = (neut->Vector).Primary.Mode;
  neutinfo -> Numnu = (neut->Vector).Primary.NumParticle;
  for(int i=0;i<(neutinfo->Numnu);i++) {
    neutinfo -> Ipnu[i] = (neut->Vector).Primary.ParticleID[i];
    neutinfo -> Abspnu[i] = (neut->Vector).Primary.AbsMomentum[i];
    for(int j=0;j<3;j++) neutinfo -> Pnu[i][j] = (neut->Vector).Primary.Momentum[i][j];
  }
  runaction -> GetEvtSum() -> AddNeut( neutinfo );
    */
	for(int ipart=0; ipart<Secondary.NumParticle; ipart++) {
  // #############################################################################
	// ### consider only TrackingFlag for use non interacted particle in neucleus ###
  // #############################################################################
		if( Secondary.TrackingFlag[ipart]==1 ) {

#ifdef DEBUG2
	    G4cout << "Particle:" << (neut->Vector).Secondary.ParticleID[ipart];
	    G4cout << "  Index: " << ipart;
	    G4cout << "  Parent Index: " << (neut->Vector).Secondary.ParentID[ipart] -1 << "\n";
	    G4cout << "Tracking Flag: " << (neut->Vector).Secondary.TrackingFlag[ipart];
	    G4cout << "  Interaction code: " << (neut->Vector).Secondary.InteractionCode[ipart] << "\n";
	    G4cout << " Momentum[MeV/c]:";
	    for (int k=0;k<3;k++)   G4cout << (neut->Vector).Secondary.Momentum[ipart][k]*MeV << " ";
	    G4cout << "\n";
#endif

			G4ParticleDefinition* particle;
			particle = particleTable->FindParticle(Secondary.ParticleID[ipart]);
			particleGun->SetParticleDefinition(particle);

			double nvec[3];
			for(int ixyz=0; ixyz<3; ixyz++)
				nvec[ixyz] = Secondary.Momentum[ipart][ixyz]/ Secondary.AbsMomentum[ipart];
			G4ThreeVector dir(nvec[0], nvec[1], nvec[2]);
			particleGun->SetParticleMomentumDirection(dir);

			G4double mass = particle->GetPDGMass();
			G4double mom = Secondary.AbsMomentum[ipart]*MeV;
			G4double energy = sqrt(mass*mass+mom*mom) - mass;
			particleGun->SetParticleEnergy(energy);
		
			particleGun->SetParticleTime(0.0*ns);

			//
			particleGun->GeneratePrimaryVertex(anEvent);

#ifdef DEBUG2
	    G4cout << "ipart: " << ipart << "\n";
	    G4cout << "PID:" << (neut->Vector).Secondary.ParticleID[ipart] << "\n";
	    G4cout << "Tracking Flag: " << (neut->Vector).Secondary.TrackingFlag[ipart] << "\n";
	    G4cout << "  Kinetic Energy[MeV]: " << energy << G4endl;;
	    G4cout << "  Momentum:";
	    for (int k=0;k<3;k++)   G4cout << (neut->Vector).Secondary.Momentum[ipart][k]*MeV << " ";
	    G4cout << " [MeV]\n";
#endif

		} // end of if
	} // end of for loop
}
