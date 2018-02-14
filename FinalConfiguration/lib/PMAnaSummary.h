#ifndef PMANASUMMARY_H
#define PMANASUMMARY_H
#include <iostream>
#include "TObject.h"
#include "TClonesArray.h"

#include "TRefArray.h"
#include "TRef.h"
#include "vector"
using namespace std;

#include "IngridHitSummary.h"
#include "IngridTrackSummary.h"


#define INGRIDHIT_MAXHITS 1000  //## Temporary
#define INGRIDRECON_MAXTRACKS 10 //## Temporary

//......................................................................
class PMAnaSummary : public TObject{
 public:

  int       Ntrack;
  int       Ningtrack;
  float     clstime;      // time of cluster defined by most high p.e.
  float     clstimecorr;  // time after correction by measurement time of CT
  float     exptime;      // diff. from expected time
  int       hitcyc;       //
  bool      ontime;       //
  bool      vetowtracking; // Upstream VETO
  bool      edgewtracking; // Fiducial CUT
  float     openangle;
  float     crossangle;

  vector<Float_t>  x;
  vector<Float_t>  y;
  vector<Float_t>  z;
  vector<Float_t>  zx;
  vector<Float_t>  zy;

  vector<Int_t>    startxpln;
  vector<Int_t>    startypln;
  vector<Float_t>    startxch;
  vector<Float_t>    startych;
  vector<Int_t>    endxpln;
  vector<Int_t>    endypln;
  vector<Float_t>    endxch;
  vector<Float_t>    endych;
  vector<Float_t>  thetax;
  vector<Float_t>  thetay;
  vector<Float_t>  angle;
  vector<Int_t>    v_startmod;//added by koga 2014/4/4
  vector<Int_t>    h_startmod;//added by koga 2014/4/4
  vector<Int_t>    ing_startmod;
  vector<Int_t>    ing_endmod;
  vector<Int_t>    ing_startpln;
  vector<Int_t>    ing_endpln;
  //vector<Bool_t>   ing_trk;
  //vector<Bool_t>   pm_stop;
  //vector<Bool_t>   ing_stop;
  vector<Int_t>   ing_trk2;    //added by koga 2014/2/8
  vector<Int_t>   pm_stop2;    //added by koga 2014/2/8
  vector<Int_t>   ing_stop2;   //added by koga 2014/2/8
  vector<Float_t>  sci_range;
  vector<Float_t>  iron_range;
  vector<Int_t>    iron_pene;
  //vector<Bool_t>   veto; // Upstream VETO
  //vector<Bool_t>   edge; // Fiducial CUT
  vector<Int_t>   veto2; // Upstream VETO //added by koga 2014/2/8
  vector<Int_t>   edge2; // Fiducial CUT  //added by koga 2014/2/8
  vector<Int_t>    pdg;
  vector<Float_t>  mucl;
  vector<Float_t>  trkpe;

  //forB2 visualization //////////////////////////////
  vector<Float_t> intcptx;
  vector<Float_t> intcpty;
  vector<Float_t> slopex;
  vector<Float_t> slopey; 
  ///////////////////////////////////////////////////

  //for B2 analysis/////////////////////////////////
  vector<Float_t> truemomentum; 
  vector<Float_t> trueangle; 
  vector<Int_t> trackid; //2014/2/2
  vector<Float_t> time1; 
  vector<Float_t> time2; 
  vector<Int_t> timen1; 
  vector<Int_t> timen2; 
  vector<Float_t> timene1; 
  vector<Float_t> timene2; 
  ///////////////////////////////////////////////////


  //###########################################
  //###########################################
  PMAnaSummary();
  PMAnaSummary(const PMAnaSummary& basicsum);
  virtual ~PMAnaSummary();
  void Clear   (Option_t* option="");
  void Print();
  void AddIngridHit(IngridHitSummary* hit);
  IngridHitSummary* GetIngridHit(int i) const;
  void AddTrack(IngridTrackSummary* trk);
  IngridTrackSummary* GetTrack(int i) const;
  int nhits;
  
 private:
  
  TRef fIngridHit[INGRIDHIT_MAXHITS];
  TRef fTrack[INGRIDRECON_MAXTRACKS];
 public:
  int ntracks;
  int Nhits(){return nhits;}
  int Ntracks(){return ntracks;}
  ClassDef(PMAnaSummary, 10) // Ingrid Hit Summary //change1to2to3 forB2 //change 3 to 4 for B2 2014/2/2 //change 4 to 5 for B2 2014/2/8 //change 6 to 7 for B2 2014/4/4//change 7 to 9 2014/7/26 change 9 to 10 2014/8/17
    };

#endif // PMANASUMMARY_H
////////////////////////////////////////////////////////////////////////
