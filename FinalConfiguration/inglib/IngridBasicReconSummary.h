#ifndef INGRIDBASICRECONSUMMARY_H
#define INGRIDBASICRECONSUMMARY_H
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
class IngridBasicReconSummary : public TObject{
public:

    float     clstime;      // time of cluster defined by most high p.e. channel's time
    float     CTtimecorr;   // i'th beam bunch timing at CT - 581*i 
    float     clstimecorr;  // time after correction by measurement time of CT
                            // ; clstime - ( CTtime - expectecdCTtime )
    float     exptime;      // difference from expected beam time
                            // ; ( clstimecorr - TDCoffset )%GapTimebwBunch - expected(200nsec)
    int       nhitclster;   // # of hits in clster
    int       nactpln;      //
    int       actinarow;      //
    float     layerpe;      //
    bool      upstreamVETO; //
    bool      upstreamedge; //

    bool      newfid;       // 2010/5/12 new fiducial volume
                            // x, x, (4 ~ 19), (2 ~ 21), (1 ~ 22)...
    bool      newfidcosmic; // x, x, (4 ~ 19), (2 ~ 21), (1 ~ 22)...(1 ~ 22), (2 ~ 21), (4 ~ 19), x, x

    bool      vinternal;    //
    int       hitmod;       //
    int       hitcyc;       //
    bool      spill_flag;   //
    bool      bunch_flag;   //
    bool      ontime;       //
    int       trgbit;
    int       inarowbit;

    bool      vetowtracking; //
    bool      edgewtracking; //
    bool      matchtrk; //
    bool      hastrk; //

    bool      modfc;         // module FC(Fully Contained) event
    int       penIron;       // # of penetrated iron
    float     muE;           // energy of muon
    float     nuErec;        // reconstructed energy of neutrino

    int       nhitx;         // Number of Hit at X view (view == FromY)
    int       nhity;         // Number of Hit at Y view (view == FromX)
    int       ntrackhitx;    // Number of Hit at X view which are associated with reconstrack track
    int       ntrackhity;    // Number of Hit at Y view which are associated with reconstrack track

    int       retracktest;

    int       trg_sec;
    int       upstreamtpl;  //
    int       vertexz;              // most upstream TPL #
    int       vertexxz;              // most upstream TPL #
    int       vertexyz;              // most upstream TPL #
    float     angle;
    
    float     thetax;
    float     thetay;
    vector<int>       vertexx;      // X Ch# at upstream TPL
    vector<int>       vertexy;      // Y Ch# at upstream TPL
    bool      horn250;      // all horns 250kA
    float     vpe;

    int       startxpln;
    int       startypln;
    int       startxch;
    int       startych;
    int       endxpln;
    int       endypln;
    int       endxch;
    int       endych;


    //###########################################
    //###########################################


    IngridBasicReconSummary();
    IngridBasicReconSummary(const IngridBasicReconSummary& basicsum);
    virtual ~IngridBasicReconSummary();
    void Clear   (Option_t* option="");
    void Print(Option_t*) const;
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
    ClassDef(IngridBasicReconSummary, 28) // Ingrid Hit Summary
};

#endif // INGRIDHITSUMMARY_H
////////////////////////////////////////////////////////////////////////
