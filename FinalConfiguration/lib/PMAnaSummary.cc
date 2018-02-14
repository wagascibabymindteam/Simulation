#include "PMAnaSummary.h"

//......................................................................

PMAnaSummary::PMAnaSummary():
  nhits(0), ntracks(0)
{ 
  Ntrack      = -1; 
  Ningtrack   = -1; 
  clstime     = -1.e5;  
  clstimecorr = -1.e5;
  exptime     = -1.e5;
  hitcyc      = -1;
  ontime      =  false;
  vetowtracking=  false;
  edgewtracking=  false;
  openangle = -1.e5;
  crossangle = -1.e5;

  x.clear();
  y.clear();
  z.clear();
  zx.clear();
  zy.clear();
  startxpln.clear();
  startypln.clear();
  startxch.clear();
  startych.clear();
  endxpln.clear();
  endypln.clear();
  endxch.clear();
  endych.clear();
  thetax.clear();
  thetay.clear();
  angle.clear();
  v_startmod.clear();//for B2
  h_startmod.clear();//for B2
  ing_startmod.clear();
  ing_endmod.clear();
  ing_startpln.clear();
  ing_endpln.clear();
  //ing_trk.clear();
  ing_trk2.clear();
  //pm_stop.clear();
  pm_stop2.clear();
  //ing_stop.clear();
  ing_stop2.clear();
  sci_range.clear();
  iron_range.clear();
  iron_pene.clear();
  //veto.clear();
  veto2.clear();
  //edge.clear();
  edge2.clear();
  pdg.clear();
  mucl.clear();
  trkpe.clear();
//forB2 visualize//////////////
  intcptx.clear();
  intcpty.clear();
  slopex.clear();
  slopey.clear();
/////////////////////////////

//for B2 analysis///////////
  truemomentum.clear();
  trueangle.clear();
  trackid.clear();
  time1.clear();
  time2.clear();
  timen1.clear();
  timen2.clear();
  timene1.clear();
  timene2.clear();
////////////////////////////

}

//......................................................................
PMAnaSummary::PMAnaSummary(const PMAnaSummary& basicsum) :
  nhits(0), ntracks(0)
{
  Ntrack      = basicsum. Ntrack ;
  Ningtrack   = basicsum. Ningtrack ;
  clstime     = basicsum. clstime ;
  clstimecorr = basicsum. clstimecorr;
  exptime     = basicsum. exptime;
  hitcyc      = basicsum. hitcyc;
  ontime      = basicsum. ontime;
  vetowtracking  = basicsum. vetowtracking ;
  edgewtracking  = basicsum. edgewtracking ;
  openangle  = basicsum. openangle ;
  crossangle  = basicsum. crossangle ;

  x = basicsum. x;
  y = basicsum. y;
  z = basicsum. z;
  zx= basicsum. zx;
  zy= basicsum. zy;
  startxpln = basicsum. startxpln;
  startypln = basicsum. startypln;
  startxch = basicsum. startxch;
  startych = basicsum. startych;
  endxpln = basicsum. endxpln;
  endypln = basicsum. endypln;
  endxch = basicsum. endxch;
  endych = basicsum. endych;
  thetax = basicsum. thetax;
  thetay = basicsum. thetay;
  angle = basicsum. angle;
  v_startmod = basicsum. v_startmod;//for B2
  h_startmod = basicsum. h_startmod;//for B2
  ing_startmod = basicsum. ing_startmod;
  ing_endmod = basicsum. ing_endmod;
  ing_startpln = basicsum. ing_startpln;
  ing_endpln = basicsum. ing_endpln;
  //ing_trk = basicsum. ing_trk;
  ing_trk2 = basicsum. ing_trk2;
  //pm_stop = basicsum. pm_stop;
  pm_stop2 = basicsum. pm_stop2;
  //ing_stop = basicsum. ing_stop;
  ing_stop2 = basicsum. ing_stop2;
  sci_range = basicsum. sci_range;
  iron_range = basicsum. iron_range;
  iron_pene = basicsum. iron_pene;
  //veto = basicsum. veto;
  veto2 = basicsum. veto2;
  //edge = basicsum. edge;
  edge2 = basicsum. edge2;
  pdg = basicsum. pdg;
  mucl = basicsum. mucl;
  trkpe = basicsum. trkpe;

//forB2 visualize//////////////
  intcptx = basicsum. intcptx;
  intcpty = basicsum. intcpty;
  slopex = basicsum.slopex;
  slopey = basicsum.slopey;
/////////////////////////////

//for B2 analysis///////////
  truemomentum = basicsum.truemomentum;
  trueangle = basicsum.trueangle;
  trackid = basicsum.trackid;
  time1 = basicsum.time1;
  time2 = basicsum.time2;
  timen1 = basicsum.timen1;
  timen2 = basicsum.timen2;
  timene1 = basicsum.timene1;
  timene2 = basicsum.timene2;
///////////////////////////

  ntracks = 0;
  nhits = 0;
  

  for (int i=0; i<INGRIDHIT_MAXHITS; ++i) {
    fIngridHit[i] = TRef(NULL);
  }
  for (int i=0; i < basicsum.nhits; ++i) 
    AddIngridHit(basicsum.GetIngridHit(i));

  for (int i=0; i<INGRIDRECON_MAXTRACKS; ++i) {
    fTrack[i] = TRef(NULL);
  }
  for (int i=0; i < basicsum.ntracks; ++i) 
    AddTrack(basicsum.GetTrack(i));

}

//......................................................................



PMAnaSummary::~PMAnaSummary() 
{

}

//......................................................................


void PMAnaSummary::Clear(Option_t* option)
{
  for (int i=0; i<INGRIDHIT_MAXHITS; ++i)
    fIngridHit[i] = TRef(NULL);
  nhits = 0;
  
  for (int i=0; i<INGRIDRECON_MAXTRACKS; ++i)
    fTrack[i] = TRef(NULL);
  ntracks = 0;
}

//......................................................................

void PMAnaSummary::Print()
{

}
//......................................................................
void PMAnaSummary::AddIngridHit(IngridHitSummary* hit) 
{
  if (nhits < INGRIDHIT_MAXHITS) {
    fIngridHit[nhits] = TRef((IngridHitSummary*) hit);
    ++nhits;
  }
}
//......................................................................


IngridHitSummary* PMAnaSummary::GetIngridHit(int i) const
{ 
  return (IngridHitSummary*)fIngridHit[i].GetObject();
}

//......................................................................

void PMAnaSummary::AddTrack(IngridTrackSummary* trk) 
{
  if (ntracks < INGRIDRECON_MAXTRACKS) {
    fTrack[ntracks] = TRef((IngridTrackSummary*) trk);
    ++ntracks;
  }
}
//......................................................................


IngridTrackSummary* PMAnaSummary::GetTrack(int i) const
{ 

  return (IngridTrackSummary*)fTrack[i].GetObject();
}

//......................................................................


ClassImp(PMAnaSummary)

////////////////////////////////////////////////////////////////////////
