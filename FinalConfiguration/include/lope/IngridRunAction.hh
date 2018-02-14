#ifndef INGRID_RUN_ACTION_H
#define INGRID_RUN_ACTION_H

#include "TTree.h"
#include "TFile.h"

#include "G4UserRunAction.hh"
#include "INGRIDEVENTSUMMARY.h"

class G4Run;

class IngridRunAction : public G4UserRunAction {
public:
  //IngridRunAction(char* filename,float,float,double);
  IngridRunAction(char* filename);
  virtual ~IngridRunAction();

  virtual void BeginOfRunAction(const G4Run* aRun);
  virtual void EndOfRunAction(const G4Run* aRun);

  inline  TTree* GetTree(){ return tree; }
  inline  IngridEventSummary* GetEvtSum(){ return evt; }
  
	void Clear() { evt->Clear("C"); }

  inline float GetX() {return x;}
  inline float GetY() {return y;}

  float vertex[3];

  Long64_t NotEntry;

	double HitEff() { return hiteff/100.; }	

private:
  float x;
  float y;
  char file[256];
  TFile* f;
  TTree* tree;
  
	IngridEventSummary *evt;

  long seed;

	double hiteff; //%


};

#endif
