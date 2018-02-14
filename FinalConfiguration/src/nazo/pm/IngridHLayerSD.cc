//#include "cfortran/cfortran.h"
//#include "cfortran/hbook.h"
//comment out by akira090918

#include "G4VPhysicalVolume.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "IngridHLayerSD.hh"

#define DEBUG 0

IngridHLayerSD::IngridHLayerSD(const G4String& name)
  : G4VSensitiveDetector(name)
{
  collectionName.insert("hlayerHitCollection");

  ingresp = new IngridResponse();
}


IngridHLayerSD::~IngridHLayerSD()
{
    if(ingresp!=NULL) delete ingresp;
}


void IngridHLayerSD::Initialize(G4HCofThisEvent* HCTE)
{
  hlayerHitCollection = 
    new IngridHLayerHitsCollection(SensitiveDetectorName,collectionName[0]);
  TotalhlayerDep = 0.;
  
  static int HCID = -1;
  if(HCID<0) HCID = GetCollectionID(0); 
  HCTE->AddHitsCollection(HCID,hlayerHitCollection);
}

//
G4bool IngridHLayerSD::ProcessHits(G4Step* aStep, 
				G4TouchableHistory* ROhist)
{
  // only when there is energy deposit in a sensitive detector,
  // create a new hit.
   
  G4Track* track = aStep->GetTrack();
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4double length = aStep->GetStepLength();

  if(edep==0.) return false;
 
  TotalhlayerDep += edep;

  // volume information must be extracted from Touchable of "PreStepPoint"
  const G4VTouchable* Touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4int detID = Touchable->GetVolume(0)->GetCopyNo();
	G4int trackID = track->GetTrackID();
  G4int PDG = track->GetDefinition()->GetPDGEncoding();
  G4ThreeVector hitPos = aStep->GetPreStepPoint()->GetPosition();
  G4double hittime = aStep->GetPreStepPoint()->GetGlobalTime();

	//apply quenching effect
	G4double edep_q = edep;
	ingresp->ApplyScintiResponse(&edep_q,track);
    
	//
	IngridHLayerHit* aHit 
		= new IngridHLayerHit(detID,PDG,trackID,edep,edep_q,hitPos,hittime);
    
	IngridHLayerHit* bHit;

	for(int k=0;k<hlayerHitCollection->entries();k++){
		bHit = (*hlayerHitCollection)[k];

		if(bHit->CompareID(*aHit)){
			bHit->AddEdep(edep,edep_q);

			if(bHit->isFaster(*aHit)) { 
				bHit->SetTime(aHit->GetTime()); 
				bHit->SetParticle(aHit->GetParticle()); 
			}
			return true;
		}
	}

	hlayerHitCollection->insert( aHit );

	return true;

}

void IngridHLayerSD::EndOfEvent(G4HCofThisEvent* HCTE)
{
#if DEBUG
  G4cout << "hlayer hits : " << fHIT << "\n"; // number of Hits
#endif
  IngridHLayerHit *cHit;

  G4double edep_tmp;
  G4double time_tmp;
  G4ThreeVector posinmod;
  G4int view;
  G4double pe;

	//
  // apply ingrid response
  for(G4int k=0;k<hlayerHitCollection->entries();k++) {
		cHit = (*hlayerHitCollection)[k];

		//
    edep_tmp = cHit->GetEdepQ();
    time_tmp = cHit->GetTime();
    posinmod = cHit->GetPosInMod();
    view = cHit->GetView();

    //apply fiber attenuation
    ingresp->ApplyFiberResponse(&edep_tmp,&time_tmp,view,posinmod);

    //convert edep -> p.e. &  p.e. statistic & cross-talk & after-pulse
    ingresp->ApplyMPPCResponse(edep_tmp,&pe);

    //fill variable to hitcollection
    cHit->SetPE(pe);
    cHit->SetDelayTime(time_tmp);
  }

}

void IngridHLayerSD::DrawAll()
{
  for(G4int k=0; k < hlayerHitCollection->entries(); k++)
   (*hlayerHitCollection)[k]->Draw(); 
}

void IngridHLayerSD::PrintAll()
{
   for(G4int k=0; k < hlayerHitCollection->entries(); k++)
     (*hlayerHitCollection)[k]->Print(); 
   //hlayerHitCollection-> PrintAllHits();
}

