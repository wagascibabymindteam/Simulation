#include "IngridBasicReconSummary.h"


//......................................................................

IngridBasicReconSummary::IngridBasicReconSummary():
  nhits(0), ntracks(0)
{ 
  clstime     = -1.e5;
  CTtimecorr  = -1.e5;
  clstimecorr = -1.e5;
  exptime     = -1.e5;
  nhitclster  = -1;
  nactpln     = -1;
  actinarow   = -1;
  layerpe     = -1.e5;
  hitmod      = -1;
  hitcyc      = -1;
  spill_flag  =  false;
  bunch_flag  =  false;
  upstreamtpl = -1;
  upstreamVETO=  false;
  upstreamedge=  false;
  newfid      =  false;
  newfidcosmic=  false;
  vinternal   =  false;
  ontime      =  false;
  vetowtracking   =  false;
  edgewtracking   =  false;
  matchtrk    =  false;
  hastrk      =  false;
  trg_sec     = -1e-5;
  vpe         = -1e-5;
  angle       = -1e-5;
  thetax      = -1e-5;
  thetay      = -1e-5;
  vertexz     = -1;
  vertexxz    = -1;
  vertexyz    = -1;
  trgbit      = -1;
  inarowbit   = -1;
  horn250     =  false;

  vertexx.clear();
  vertexy.clear();


  startxpln = -1;
  startypln = -1;
  startxch  = -1;
  startych  = -1;
  endxpln   = -1;
  endypln   = -1;
  endxch    = -1;
  endych    = -1;
  modfc     = false;
  penIron   = -1;
  muE       = -1e-5;
  nuErec    = -1e-5;

  nhitx     = -1;
  nhity     = -1;
  ntrackhitx= -1;
  ntrackhity= -1;

    retracktest= false;
    //retrackx   = false;
    //retracky   = false;

}
//......................................................................
IngridBasicReconSummary::IngridBasicReconSummary(const IngridBasicReconSummary& basicsum) :
  nhits(0), ntracks(0)
{ 

  clstime     = basicsum. clstime ;
  CTtimecorr  = basicsum. CTtimecorr;
  clstimecorr = basicsum. clstimecorr;
  exptime     = basicsum. exptime;
  nhitclster  = basicsum. nhitclster;
  nactpln     = basicsum. nactpln;
  actinarow   = basicsum. actinarow;
  layerpe     = basicsum. layerpe;
  upstreamVETO= basicsum. upstreamVETO;
  upstreamedge= basicsum. upstreamedge;
  vinternal   = basicsum. vinternal;
  hitmod      = basicsum. hitmod;
  hitcyc      = basicsum. hitcyc;
  spill_flag  = basicsum. spill_flag;
  bunch_flag  = basicsum. bunch_flag;
  upstreamtpl = basicsum. upstreamtpl;
  ontime      = basicsum. ontime;
  vpe         = basicsum. vpe;
  trg_sec     = basicsum. trg_sec ;
  trgbit      = basicsum. trgbit ;
  vetowtracking  = basicsum. vetowtracking ;
  edgewtracking  = basicsum. edgewtracking ;
  matchtrk       = basicsum. matchtrk ;
  hastrk         = basicsum. hastrk ;
  inarowbit      = basicsum. inarowbit ;
  ntracks = 0;
  nhits = 0;
  angle       = basicsum. angle;
  thetax      = basicsum. thetax;
  thetay      = basicsum. thetay;
  vertexz     = basicsum. vertexz;
  vertexxz    = basicsum. vertexxz;
  vertexyz    = basicsum. vertexyz;
  vertexx     = basicsum. vertexx;
  vertexy     = basicsum. vertexy;
  horn250     = basicsum. horn250;


  startxpln   = basicsum. startxpln;
  startypln   = basicsum. startypln;
  startxch    = basicsum. startxch;
  startych    = basicsum. startych;
  endxpln     = basicsum. endxpln;
  endypln     = basicsum. endypln;
  endxch      = basicsum. endxch;
  endych      = basicsum. endych;
  modfc       = basicsum. modfc;
  penIron     = basicsum. penIron;
  muE         = basicsum. muE;
  nuErec      = basicsum. nuErec;

  nhitx       = basicsum. nhitx;
  nhity       = basicsum. nhity;
  ntrackhitx  = basicsum. ntrackhitx;
  ntrackhity  = basicsum. ntrackhity;
  
    retracktest = basicsum. retracktest;
    //retrackx    = basicsum. retrackx;
    //retracky    = basicsum. retracky;
  

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



IngridBasicReconSummary::~IngridBasicReconSummary() 
{

}

//......................................................................


void IngridBasicReconSummary::Clear(Option_t* option)
{
  for (int i=0; i<INGRIDHIT_MAXHITS; ++i)
    fIngridHit[i] = TRef(NULL);
  nhits = 0;

  for (int i=0; i<INGRIDRECON_MAXTRACKS; ++i)
    fTrack[i] = TRef(NULL);
  ntracks = 0;

}

//......................................................................

void IngridBasicReconSummary::Print(Option_t* option) const
{

}
//......................................................................
void IngridBasicReconSummary::AddIngridHit(IngridHitSummary* hit) 
{

    if (nhits < INGRIDHIT_MAXHITS) {
        fIngridHit[nhits] = TRef((IngridHitSummary*) hit);
        ++nhits;
    }

}
//......................................................................


IngridHitSummary* IngridBasicReconSummary::GetIngridHit(int i) const
{ 

  return (IngridHitSummary*)fIngridHit[i].GetObject();
}

//......................................................................

void IngridBasicReconSummary::AddTrack(IngridTrackSummary* trk) 
{

    if (ntracks < INGRIDRECON_MAXTRACKS) {
        fTrack[ntracks] = TRef((IngridTrackSummary*) trk);
        ++ntracks;
    }

}
//......................................................................


IngridTrackSummary* IngridBasicReconSummary::GetTrack(int i) const
{ 

  return (IngridTrackSummary*)fTrack[i].GetObject();
}


//......................................................................





ClassImp(IngridBasicReconSummary)

////////////////////////////////////////////////////////////////////////
