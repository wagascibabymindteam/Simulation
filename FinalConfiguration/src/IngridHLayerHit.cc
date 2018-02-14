#include "IngridHLayerHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <fstream>

#include "INGRID_Dimension.hh"
#include "Const.hh"

#define SideView 0 // resolution of vertical-direction

// allocator
G4Allocator<IngridHLayerHit> IngridHLayerHitAllocator;

//IngridHLayerHit::IngridHLayerHit(G4int dID0, G4int P0, G4int trkid, G4double e, G4double e_q, const G4ThreeVector& pos, G4double t) 
IngridHLayerHit::IngridHLayerHit(G4int dID0, G4int P0, G4int trkid, G4double e, G4double eq, G4ThreeVector pos, G4double t) 
{
  detID = dID0;
  trackID = trkid;
  edep = e;
  edep_q = eq;
  Particle = P0;
  //for(int i=0;i<3;i++) position[i] = pos[i];
  position = pos;
  time = t;

    mod = dID0/264;              // 264 scnti-bar / module
    pln = (dID0-mod*264)/24;     // 24 channel / plane
    ch = dID0-mod*264-pln*24;    //24 ch /plane  


    view = SideView;


  if(mod>20){
    mod = dID0/(PLNMAX*CHMAX) -20;              // 550 scnti-bar / module
    pln = (dID0-(mod+20)*PLNMAX*CHMAX)/CHMAX;     // 50 channel / channel
    ch = dID0-(mod+20)*PLNMAX*CHMAX-pln*CHMAX;    //50 ch /plane  
  } 
 
    if(ch>CHMAX||ch<0)G4cout<<"error ch"<<ch<<endl;/////////////////
    if(pln>PLNMAX||pln<0)G4cout<<"error pln"<<pln<<endl;/////////////



    //2014/6/11
    if(mod==1){
      posinmod[0] = pos[0] + 572.2*cm;
      posinmod[1] = pos[1] + 444.4*cm;
      posinmod[2] = pos[2] - 170.0*cm - 284.5*cm;
    }
    if(mod==2){
      posinmod[0] = pos[0] - 572.2*cm + 144.5*cm;
      posinmod[1] = pos[1] + 444.4*cm;
      posinmod[2] = pos[2] - 170.0*cm;
    }
    if(mod==3){
      posinmod[0] = pos[0] + 572.2*cm;
      posinmod[1] = pos[1] + 444.4*cm;
      posinmod[2] = pos[2] - 170.0*cm + 184.5*cm;
    }
    if(mod==4 || mod==5 || mod==6){
      posinmod[0] = pos[0] + 572.2*cm;
      posinmod[1] = pos[1] + 444.4*cm;
      posinmod[2] = pos[2] - 170.0*cm;
    }


}

IngridHLayerHit::IngridHLayerHit(G4int dID0, G4double e,G4int P0) 
{
  detID = dID0;
  edep = e;
  Particle = P0;

}

IngridHLayerHit::IngridHLayerHit(G4int dID0, G4double e) 
{
  detID = dID0;
  edep = e;

}


IngridHLayerHit::~IngridHLayerHit() 
{
}

IngridHLayerHit::IngridHLayerHit(const IngridHLayerHit &right)
  : G4VHit()
{
  detID = right.detID;
  edep       = right.edep;
  Particle = right.Particle;

  for(int i=0;i<3;i++) position[i] = right.position[i];
  eventID = right.eventID;

}

const IngridHLayerHit& IngridHLayerHit::operator=(const IngridHLayerHit &right)
{
  detID = right.detID;
  edep       = right.edep;
  Particle = right.Particle; 
  
  for(int i=0;i<3;i++) position[i] = right.position[i];
  eventID = right.eventID;


  return *this;
}

G4int IngridHLayerHit::operator==(const IngridHLayerHit &right) const
{
  return (this==&right) ? 1 : 0;
}  

G4int IngridHLayerHit::CompareID(const IngridHLayerHit right) 
{
  return (detID==right.detID) ? 1 : 0;
}


G4int IngridHLayerHit::CompareP(const IngridHLayerHit right) 
{
  return (Particle==right.Particle) ? 1 : 0;
}

G4int IngridHLayerHit::isFaster(const IngridHLayerHit right)
{
  return (time>right.time) ? 1 : 0;
}
G4int IngridHLayerHit::LargerEdep(const IngridHLayerHit right)
{
  //return (Particle==11||right.Particle!=11) ? 1 : 0;
  if(Particle==11) return 1;
  else if(right.Particle==11) return 0;
  else return (edep<right.edep) ? 1 : 0;
}

void IngridHLayerHit::Draw()
{
    double size = edep + 7.;
    if( edep>9 ) size = 16.;
  #if 1
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
    {
      G4ThreeVector pos; 
      for(int i=0;i<3;i++) pos[i] = position[i]*mm;
      G4Circle circle(pos);
      circle.SetScreenSize(size); 
      circle.SetFillStyle(G4Circle::filled);
      G4Colour colour(0.,1.,1.3); //cyan
      G4VisAttributes attribs(colour);
      circle.SetVisAttributes(attribs);
      pVVisManager->Draw(circle);
    }
  #endif
}

void IngridHLayerHit::Print()
{
  G4cout.precision(4);
  
  G4cout << " Mod:" << mod 
		 //<< " detID:" << detID
         << " Pln:" << pln 
		 << " Ch:" << ch 
		 << " Time:" << time
	//<< "  Edep:" << G4BestUnit(edep,"Energy")
		 << " Edep:" << edep
		 << " p.e.:" << pe
         << " PID:" << Particle
//		 << G4endl;
		 << " Trk:" << trackID
         << " pos:{" << position[0]/cm << ", "
         << position[1]/cm << ", " << position[2]/cm
         << "}" << G4endl;

}


void IngridHLayerHit::Print_Hit()
{

  std::ofstream yokoHit_ofs;
  yokoHit_ofs.open("yokoHit", std::ofstream::app);
  if (yokoHit_ofs.good()){
    yokoHit_ofs  << eventID << "   " << detID << "   " << Particle << "   " << edep << "   ";
  }
  
  yokoHit_ofs.close();
  
}

