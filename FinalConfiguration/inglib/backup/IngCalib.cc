//##### Standard C++ lib. ######
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;
#include <iomanip.h>
#include <sys/stat.h>
//##### Root Library ###########
#include <TROOT.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TEventList.h>
#include <TBranch.h>
#include <TSystem.h>
//##### INGRID Library #########
#include "INGRIDEVENTSUMMARY.h"
#include "IngridHitSummary.h"
#include "IngridSimHitSummary.h"

float       gain[16][2][15][24];
float        ped[16][2][15][24];
float     logain[16][2][15][24];
float      loped[16][2][15][24];
//###########################################################
//### this is temporary method  #############################
//### (we use text file gain and pedestal file, Jan.2010) ###
//###########################################################
void InitilizeCalibConst(){
  for(int mod=0; mod<16; mod++){
    for(int view=0; view<2; view++){
      for(int pln=0; pln<15; pln++){
	for(int ch=0; ch<24; ch++){
	  gain    [mod][view][pln][ch] =  1e5;
	  logain  [mod][view][pln][ch] =  1e5;
	  ped     [mod][view][pln][ch] = -1e-5;
	  loped   [mod][view][pln][ch] = -1e-5;
	}
      }
    }
  }
}



bool GetCalibConst(string str){
  ifstream calibfile(str.c_str());
  int   mod, view, pln, ch;
  float tgain, tped, tloped;
  int   start_time, end_time, flag;
  calibfile >> flag >> start_time >> end_time;
  //if(!flag)return false;
  while( calibfile 
	 >> mod  >> view   >> pln >> ch
	 >> tped >> tloped >> tgain){
    gain  [mod][view][pln][ch] = tgain;
    logain[mod][view][pln][ch] = 0.1 * tgain;
    ped   [mod][view][pln][ch] = tped;
    loped [mod][view][pln][ch] = tloped;
    
  }
  for(int i=1; i<=6; i++){
    for(int j=0; j<22; j++){
      double temp;
      gain  [i][1][11][j] = gain  [i-1][1][12][j];
      ped   [i][1][11][j] = ped   [i-1][1][12][j];
      logain[i][1][11][j] = logain[i-1][1][12][j];
      loped [i][1][11][j] = loped [i-1][1][12][j];
    }
  }
  for(int i=8; i<=13; i++){
    for(int j=0; j<22; j++){
      gain[i][0][13][j]   = gain[i-1][0][14][j];
      ped [i][0][13][j]   = ped [i-1][0][14][j];
      logain[i][0][13][j] = gain[i-1][0][14][j];
      loped [i][0][13][j] = ped [i-1][0][14][j];
    }
  }
  return true;
}

const static Int_t   cTimeCorrection = 24;//Time correction for difference
                                          //of cable length

int main(int argc,char *argv[]){
  TROOT        root ("GUI","GUI");
  TApplication app  ("App",0,0);
  int run_number;
  int calib_run_number;
  int c=-1;
  int sub_run_number;
  while ((c = getopt(argc, argv, "r:s:c:")) != -1) {
    switch(c){
    case 'r':
      run_number=atoi(optarg);
      calib_run_number=run_number;
      break;
    case 's':
      sub_run_number=atoi(optarg);
      break;
    case 'c':
      calib_run_number=atoi(optarg);
      break;
    }
  }
  char buff[300];
  InitilizeCalibConst(); //### Initialize gain, pedestal, and so on

  //#### check calib. path
  ifstream fcalpath("/home/daq/data/calib_table/calib_path.txt");
  int cal_path_runnum, cal_path_subnum;
  while( fcalpath >> cal_path_runnum >> cal_path_subnum ){
    if( cal_path_runnum == run_number ){
      cout << "there is calib. path of run# " << run_number
           << " : sub run number = " << cal_path_subnum
           << endl;

      goto PATHOK;
    }
  }
  cout << "there is no calib. path of run# " << run_number
       << endl;
  exit(1);

 PATHOK:

  //#### read calibration file 
  sprintf(buff,
	  "/home/daq/data/calib_table/ingrid_%08d_%04d_MPPCcalib.txt",
	  calib_run_number, 
	  cal_path_subnum);
	  
  FileStat_t fs;
  if(gSystem->GetPathInfo(buff,fs)){
    cout<<"Cannot open file "<<buff<<endl;
    exit(1);
  }

  string str = buff;
  GetCalibConst(str);


  //#### Read file before calibration ######
  //########################################
  IngridEventSummary* summary = new IngridEventSummary();
  sprintf(buff,"/home/daq/data/dst/ingrid_%08d_%04d.root",
	  run_number, sub_run_number);
  if(gSystem->GetPathInfo(buff,fs)){
    cout<<"Cannot open file "<<buff<<endl;
    exit(1);
  }
  TFile*            rfile = new TFile(buff,"read");
  TTree*             tree = (TTree*)rfile -> Get("tree");
  TBranch*          EvtBr = tree->GetBranch("fDefaultReco.");
  EvtBr                   ->SetAddress(&summary);
  tree                    ->SetBranchAddress("fDefaultReco.", &summary);
  int                nevt = (int)tree -> GetEntries();
  cout << "Total # of events = " << nevt <<endl;

  //#### Create file after calibration ######
  //#########################################
  sprintf(buff,"/home/daq/data/dst/ingrid_%08d_%04d_calib.root",
	  run_number, sub_run_number);
  TFile*            wfile = new TFile(buff,"recreate");
  TTree*            wtree = new TTree("tree","tree");
  IngridEventSummary* wsummary = new IngridEventSummary(); 
  wtree              -> Branch   ("fDefaultReco.","IngridEventSummary", 
				 &wsummary,  64000,   99);


  for(int ievt = 0; ievt < nevt; ++ievt){
    if(ievt%1000==0)cout<<"Run#"<<run_number<<"\tcalib event:"<<ievt<<endl;
    summary -> Clear();
    wsummary-> Clear();
    tree    -> GetEntry(ievt);
    for(int mod=0; mod<16; mod++){
      for(int cyc=0; cyc<23; cyc++){
        int ninghit = summary -> NIngridModHits(mod, cyc);
        for(int i=0; i<ninghit; i++){

	  IngridHitSummary *inghitsum;
	  inghitsum   = (IngridHitSummary*) (summary -> GetIngridModHit(i, mod, cyc) );
	  
	  int view = inghitsum -> view;
	  int pln  = inghitsum -> pln;
	  int ch   = inghitsum -> ch;


	  //##### Before conversion from ADC to #p.e.,#######
	  //##### we have to do correction of linearity #####
	  //##### of ADC channel.             ###############
	  //##### Now(Jan.2010), we ignore it ###############
	  //#################################################


	  //##### Conversion from ADC to #p.e. ##############
	  //#################################################
	  inghitsum -> pe   = 1.0 * ( inghitsum ->  adc - ped[mod][view][pln][ch] ) / gain[mod][view][pln][ch];

	  //##### Conversion from ADC to #p.e.(Logain)#######
	  //#################################################
	  inghitsum -> lope = 1.0 * ( inghitsum ->  loadc - loped[mod][view][pln][ch] ) / logain[mod][view][pln][ch] ;
	  //##### Conversiont from TDC to time[nsec] ########
	  //#################################################

	  long time = 2.5 * ( inghitsum ->  tdc ) - 10.0 * ( summary -> trgtime ); 
	  //##### If we don't have Pulse Per Second, ########
	  //##### time is larger than one second     ########
	  //#################################################
	  while(time>1000000000){
	    time -= 1000000000;
	  }

	  //##### We have to do  correction because of ##########
	  //##### difference of cable length b/w  ###############
	  //##### Back end board and front end board  ###########
	  //##### but some VETO channels should be careful to do 
	  //#####################################################
	  switch ( mod ) {
	  case  1:
	    if( pln != 11 ) //#### Because pln 11 at mod 1 is pln 12 at mod 0
	    time -= cTimeCorrection;
	    break;
	  case  2:
	    time -= cTimeCorrection;
	    break;
	  case  3:
	    time -= cTimeCorrection;
	    break;	   
	  case  4:
	    if( pln == 11 ) //#### Because pln 11 at mod 4 is pln 12 at mod 3
	    time -= cTimeCorrection;
	    break;	   
	  case 11:
	    if( pln != 13)  //#### Because pln 13 at mod 11 is pln 14 at mod 10
	    time -= cTimeCorrection;
	    break;
	  case 12:
	    if( pln == 13)  //#### Because pln 13 at mod 12 is pln 14 at mod 11
	    time -= cTimeCorrection;
	    break;
	  defalut:
	    break;
	  }
	  inghitsum -> time = time;

	}//Hit Loop
      }//Cyc
    }//Mod
    wsummary = summary;
    wtree -> Fill();
    if(ievt%1000==0)wtree->AutoSave();
  }


  wtree -> Write();
  wfile -> Write();
  wfile -> Close();
  //app.Run();
}
 
