#define tree_cxx
#include "tree.h"
#include "draw.h"
#include "track.h"
#include "mode.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdlib.h>
#define DISPLAY

void ana(){
  tree t; 
  t.Loop();
}

void tree::Loop()
{
  
  if (fChain == 0) return;


  //*****Set draw panel*****
  gStyle->SetTitleBorderSize(0);

  Int_t nactcut=0,npecut=0,nnotra=0,nnomatch=0,nsid=0,nfro=0,nedg=0;
  Int_t vi,nint=0,ntracks,mtracks,mode,nmhit[2][2];
  Float_t xnu,ynu,znux,znuy,znu,nor,nue,cs,Xnu,Ynu,Znu;
  Double_t ct=0;
  char ans[8];
  Float_t noise_rand;
  Int_t noise;
  Int_t mispln[17][2][500][18],mishit[17][2][500],suchit[17][2][500],nmis[2][2][500],nsuc[2][2][500],hitpln[2][2][500],hitch[2][2][500],trahit[2][2];//MC tune
  int plnmis[2][2][500][18];//MC tune
  Float_t hitpe[2][2][500];//MC tune

  TFile* file=new TFile("ana.root", "recreate");
  TTree* tree=new TTree("tree","tree");
  tree->Branch("xnu", &xnu, "xnu/F");
  tree->Branch("ynu", &ynu, "ynu/F");
  tree->Branch("znu", &znu, "znu/F");
  tree->Branch("vi", &vi, "vi/I");
  tree->Branch("ntracks", &ntracks, "ntracks/I");
  tree->Branch("mtracks", &mtracks, "mtracks/I");
  tree->Branch("nint", &nint, "nint/I");
  tree->Branch("mode", &mode, "mode/I");
  tree->Branch("select", &select, "select/I");
  tree->Branch("ct", &ct, "ct/D");
  tree->Branch("nue", &nue, "nue/F");
  tree->Branch("Xnu", &Xnu, "Xnu/F");
  tree->Branch("Ynu", &Ynu, "Ynu/F");
  tree->Branch("Znu", &Znu, "Znu/F");
  tree->Branch("nor", &nor, "nor/F");
  tree->Branch("cs", &cs, "cs/F");
  tree->Branch("ntra", &ntra, "ntra[2][2]/I");
  tree->Branch("mtra", &mtra, "mtra[2][2]/I");
  tree->Branch("star", &star, "star[2][2][50]/I");
  tree->Branch("fini", &fini, "fini[2][2][50]/I");
  tree->Branch("sep", &sep, "sep[2][2][50]/F");
  tree->Branch("kat", &kat, "kat[2][2][50]/F");
  tree->Branch("totpe", &totpe, "totpe[2][2][50]/F");
  tree->Branch("shar", &shar, "shar[2][2][50]/O");
  tree->Branch("nmhit", &nmhit, "nmhit[2][2]/I");
  tree->Branch("nmis", &nmis, "nmis[2][2][500]/I");//MC tune
  tree->Branch("nsuc", &nsuc, "nsuc[2][2][500]/I");//MC tune
  tree->Branch("plnmis", &plnmis, "plnmis[2][2][500][18]/I");//MC tune
  tree->Branch("hitpln", &hitpln, "hitpln[2][2][500]/I");//MC tune
  tree->Branch("hitch", &hitch, "hitch[2][2][500]/I");//MC tune
  tree->Branch("hitpe", &hitpe, "hitpe[2][2][500]/F");//MC tune
  tree->Branch("trahit", &trahit, "trahit[2][2]/I");//MC tune



#ifdef DISPLAY
  TCanvas *c1=new TCanvas("c1","c1",2050*0.8/2/1.5,600*0.94*2/1.5);
  //TCanvas *c1=new TCanvas("c1","c1",820,600);
#endif
  TH1F *h=new TH1F("","Side view",2050*10,0,1875);
  //TH1F *h=new TH1F("","Side view",820*10,0,820);
  h->SetMinimum(0);
  h->SetMaximum(1200);
  h->GetXaxis()->SetLabelSize(0);
  h->GetYaxis()->SetLabelSize(0);
  h->SetStats(0);
  h->SetNdivisions(0);
  TH1F *v=new TH1F("","Top view",2050*10,0,1875);
  //TH1F *v=new TH1F("","Top view",820*10,0,820);
  v->SetMinimum(0);
  v->SetMaximum(1200);
  v->GetXaxis()->SetLabelSize(0);
  v->GetYaxis()->SetLabelSize(0);
  v->SetStats(0);

  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  //*****Start event loop*****
  for(Long64_t jentry=0;jentry<nentries;jentry++) {
  
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    nhit=fDefaultReco_ningridhits;
    ct+=fDefaultReco_fBeamSummary_ct_np[0][4][0];
    nor=fDefaultReco_fSimVertex_norm[0];
    nue=fDefaultReco_fSimVertex_nuE[0];
    mode=fDefaultReco_fNeutInfo_Mode[0];
    cs=fDefaultReco_fSimVertex_totcrsne[0];
    Xnu=fDefaultReco_fSimVertex_xnu[0]*10+600;
    Ynu=fDefaultReco_fSimVertex_ynu[0]*10+600;
    Znu=fDefaultReco_fSimVertex_znu[0]*10+1568;
    
    //*****define time cluster*****
    memset(timecl,0,sizeof(timecl));
    memset(npecychit,0,sizeof(npecychit));
    memset(ncychit,0,sizeof(ncychit));
    memset(hitcyc,true,sizeof(hitcyc));

    for(Long64_t i=0;i<nhit;i++){
      if(fDefaultReco_fIngridHit_pe[i]>2.5
	 //&&fabs(fDefaultReco_fIngridHit_time[i]-(2830+581*(fDefaultReco_fIngridHit_cyc[i]-4))-8)<90
	 &&fDefaultReco_fIngridHit_pln[i]<18
	 &&fDefaultReco_fIngridHit_pln[i]>0
	 //&&fDefaultReco_fIngridHit_cyc[i]==-1
	 //&&fDefaultReco_fIngridHit_cyc[i]<12
	 ){
	timecl[0]+=fDefaultReco_fIngridHit_time[i]*fDefaultReco_fIngridHit_pe[i];
	npecychit[0]+=fDefaultReco_fIngridHit_pe[i];
	ncychit[0]++;
      }
    }

 
    for(Long64_t i=0;i<1;i++){
      if(ncychit[i]>6){
	exptime[i]=timecl[i]/npecychit[i];
      }
      else hitcyc[i]=false;
      select=-4;
    }

    if(!hitcyc[0])continue;

    //*****define active plane*****
    memset(actpln,false,sizeof(actpln));
    memset(numactpln,0,sizeof(numactpln));
    memset(peactpln,0,sizeof(peactpln));
    for(Long64_t i=0;i<nhit;i++){
      if(fDefaultReco_fIngridHit_pe[i]>2.5
	 &&fDefaultReco_fIngridHit_pln[i]<18
	 &&fDefaultReco_fIngridHit_pln[i]>0
	 //&&fDefaultReco_fIngridHit_cyc[i]==-1
	 //&&fDefaultReco_fIngridHit_cyc[i]<12
	 //&&hitcyc[fDefaultReco_fIngridHit_cyc[i]+1]
	 ){
	//if(fabs(fDefaultReco_fIngridHit_time[i]-exptime[fDefaultReco_fIngridHit_cyc[i]-4])>30)continue;
	actpln[fDefaultReco_fIngridHit_cyc[i]+1][fDefaultReco_fIngridHit_view[i]][fDefaultReco_fIngridHit_pln[i]]=true;
	/*
	if(fDefaultReco_fIngridHit_view[i]==1
	   &&fDefaultReco_fIngridHit_pln[i]==9
	   &&fDefaultReco_fIngridHit_ch[i]==21
	   )continue;
	*/

	if(fDefaultReco_fIngridHit_ch[i]>7
	   &&fDefaultReco_fIngridHit_ch[i]<24
	   )
	peactpln[fDefaultReco_fIngridHit_cyc[i]+1]+=1.96*fDefaultReco_fIngridHit_pe[i];
	else peactpln[fDefaultReco_fIngridHit_cyc[i]+1]+=fDefaultReco_fIngridHit_pe[i];
	numactpln[fDefaultReco_fIngridHit_cyc[i]+1][fDefaultReco_fIngridHit_view[i]]++;
      }
    }

    //*****# of active plane > 2*****
    for(Long64_t icyc=0;icyc<1;icyc++){
      if(numactpln[icyc][0]<3||&numactpln[icyc][1]<3){
	hitcyc[icyc]=false;
	select=-3;
	nactcut++;
      }
    }





    //*****pe / actice plane > 6.5*****
    for(Long64_t icyc=0;icyc<1;icyc++){
      if(!hitcyc[icyc])continue;
      if(peactpln[icyc]/(numactpln[icyc][0]+numactpln[icyc][1])<6.5){
	hitcyc[icyc]=false;
	select=-2;
	npecut++;
      }
    }



    //*****start cycle loop*****
    for(Long64_t icyc=0;icyc<1;icyc++){
      if(!hitcyc[icyc])continue;
      
      //*****Read hit infomation*****
      memset(hit,0,sizeof(hit));
      memset(hitnum,-1,sizeof(hitnum));
      for(Long64_t i=0;i<nhit;i++){
	//if(fDefaultReco_fIngridHit_cyc[i]!=icyc)continue;
	//if(fabs(fDefaultReco_fIngridHit_time[i]-exptime[icyc-4])>30)continue;
	//if(fabs(fDefaultReco_fIngridHit_time[i]-(2830+581*(icyc-4)))>50)continue;
	if(fDefaultReco_fIngridHit_pe[i]<2.5)continue;
	mod=fDefaultReco_fIngridHit_mod[i];
	if(mod!=16&&mod!=3)continue;
	view=fDefaultReco_fIngridHit_view[i];
	pe[mod][view][hit[mod][view]]=fDefaultReco_fIngridHit_pe[i];
	pln[mod][view][hit[mod][view]]=fDefaultReco_fIngridHit_pln[i];
	ch[mod][view][hit[mod][view]]=fDefaultReco_fIngridHit_ch[i];
	timing[mod][view][hit[mod][view]]=fDefaultReco_fIngridHit_time[i];
	pdg[mod][view][hit[mod][view]]=0;//fDefaultReco_fIngridSimHit_pdg[i];//add
	if(view==1&&pln[mod][view][hit[mod][view]]==9&&ch[mod][view][hit[mod][view]]==21)continue;
	if(mod==16&&pln[mod][view][hit[mod][view]]>0&&pln[mod][view][hit[mod][view]]<18&&ch[mod][view][hit[mod][view]]>7&&ch[mod][view][hit[mod][view]]<24)pe[mod][view][hit[mod][view]]=pe[mod][view][hit[mod][view]]*1.96;//0.81;

	if(pln[mod][view][hit[mod][view]]<npln(mod))hitnum[mod][view][pln[mod][view][hit[mod][view]]][ch[mod][view][hit[mod][view]]]=hit[mod][view];
	hit[mod][view]++;
      }


      //****mppc noise*****
      noise_rand=(float)rand()/RAND_MAX;
      if(noise_rand<0.1955)noise=0;
      else if(noise_rand<0.5146)noise=1;
      else if(noise_rand<0.7751)noise=2;
      else if(noise_rand<0.9167)noise=3;
      else if(noise_rand<0.9745)noise=4;
      else if(noise_rand<0.9933)noise=5;
      else noise=6;
      for(Long64_t i=0;i<noise;i++){
	mod=16;
	view=rand()%2;
	pe[mod][view][hit[mod][view]]=3;
	pln[mod][view][hit[mod][view]]=rand()%18;
	ch[mod][view][hit[mod][view]]=rand()%32;
	if(pln[mod][view][hit[mod][view]]==0&&ch[mod][view][hit[mod][view]]>23){
	  i--;
	  continue;
	}
	if(hitnum[mod][view][pln[mod][view][hit[mod][view]]][ch[mod][view][hit[mod][view]]]>=0)continue;
	hitnum[mod][view][pln[mod][view][hit[mod][view]]][ch[mod][view][hit[mod][view]]]=hit[mod][view];
	timing[mod][view][hit[mod][view]]=0;
	pdg[mod][view][hit[mod][view]]=0;
	hit[mod][view]++;
      }



      //*****Start track search*****
      for(int MOD=0;MOD<17;MOD++){
	//	if(MOD>6&&MOD<16)continue;
	if(MOD!=16&&MOD!=3)continue;
      for(int VIEW=0;VIEW<2;VIEW++){

	//*****Define clusters*****
	memset(ncl[MOD][VIEW],0,sizeof(ncl[MOD][VIEW]));
	memset(numcl[MOD][VIEW],0,sizeof(numcl[MOD][VIEW]));
	memset(clhit[MOD][VIEW],0,sizeof(clhit[MOD][VIEW]));
	for(PLN=0;PLN<npln(MOD);PLN++){
	  CH=0;
	  while(1){
	    if(hitnum[MOD][VIEW][PLN][CH]>=0){
	      clchi[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]]=CH;
	      clhit[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]][numcl[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]]]=hitnum[MOD][VIEW][PLN][CH];
	      while(1){
		numcl[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]]++;
		if(CH==nch(MOD)-1)break;
		if(hitnum[MOD][VIEW][PLN][CH+1]<0)break;
		CH++;
		clhit[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]][numcl[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]]]=hitnum[MOD][VIEW][PLN][CH];
	      }
	      clchf[MOD][VIEW][PLN][ncl[MOD][VIEW][PLN]]=CH;
	      ncl[MOD][VIEW][PLN]++;
	    }//if
	    if(CH==nch(MOD)-1)break;
	    CH++;
	  }//while
	}//for PLN
	

	//*****Fill pe and center of clusters*****
	memset(clpe[MOD][VIEW],0,sizeof(clpe[MOD][VIEW]));
	memset(clcenter[MOD][VIEW],0,sizeof(clcenter[MOD][VIEW]));
	for(PLN=0;PLN<npln(MOD);PLN++){
	  for(CL=0;CL<ncl[MOD][VIEW][PLN];CL++){
	    for(CLHIT=0;CLHIT<numcl[MOD][VIEW][PLN][CL];CLHIT++){
	      clpe[MOD][VIEW][PLN][CL]+=pe[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]];
	      clcenter[MOD][VIEW][PLN][CL]+=pe[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]*yposi(MOD,PLN,clchi[MOD][VIEW][PLN][CL]+CLHIT);
	    }
	    clcenter[MOD][VIEW][PLN][CL]=clcenter[MOD][VIEW][PLN][CL]/clpe[MOD][VIEW][PLN][CL];
	  }
	}
	

	//*****Define cells*****
	memset(ncell[MOD][VIEW],0,sizeof(ncell[MOD][VIEW]));
	for(PLN=0;PLN<npln(MOD)-1;PLN++){
	  for(CL=0;CL<ncl[MOD][VIEW][PLN];CL++){
	    for(DIST=0;DIST<2;DIST++){
	      if(PLN==npln(MOD)-2&&DIST==1)continue;
	      for(CL2=0;CL2<ncl[MOD][VIEW][PLN+DIST+1];CL2++){
		if(DIST==1&&fabs(clcenter[MOD][VIEW][PLN][CL]-clcenter[MOD][VIEW][PLN+2][CL2])>92)continue;
		cellu[MOD][VIEW][PLN][ncell[MOD][VIEW][PLN][DIST]][DIST]=CL;
		celld[MOD][VIEW][PLN][ncell[MOD][VIEW][PLN][DIST]][DIST]=CL2;
		ncell[MOD][VIEW][PLN][DIST]++;
	      }
	    }
	  }
	}

	

	//*****Define neiborhoods*****
	memset(nnei[MOD][VIEW],0,sizeof(nnei[MOD][VIEW]));
	for(PLN=0;PLN<npln(MOD)-2;PLN++){
	  for(DIST=0;DIST<2;DIST++){
	    if(PLN==0&&DIST==1)continue;
	    for(CELL=0;CELL<ncell[MOD][VIEW][PLN-DIST][DIST];CELL++){
	      for(DIST2=0;DIST2<2;DIST2++){
		if(PLN==npln(MOD)-3&&DIST2==1)continue;
		if(DIST==1&&DIST2==1)continue;
		for(CELL2=0;CELL2<ncell[MOD][VIEW][PLN+1][DIST2];CELL2++){
		  if(celld[MOD][VIEW][PLN-DIST][CELL][DIST]==cellu[MOD][VIEW][PLN+1][CELL2][DIST2]){
		    neib=false;
		    for(CLHIT=0;CLHIT<numcl[MOD][VIEW][PLN-DIST][cellu[MOD][VIEW][PLN-DIST][CELL][DIST]];CLHIT++){
		      for(CLHIT2=0;CLHIT2<numcl[MOD][VIEW][PLN+1][celld[MOD][VIEW][PLN-DIST][CELL][DIST]];CLHIT2++){
			for(CLHIT3=0;CLHIT3<numcl[MOD][VIEW][PLN+2+DIST2][celld[MOD][VIEW][PLN+1][CELL2][DIST2]];CLHIT3++){

			 
			  x[0]=xposi(MOD,VIEW,PLN-DIST);
			  x[1]=xposi(MOD,VIEW,PLN+1);
			  x[2]=xposi(MOD,VIEW,PLN+2+DIST2);
			  y[0]=yposi(MOD,PLN-DIST,clchi[MOD][VIEW][PLN-DIST][cellu[MOD][VIEW][PLN-DIST][CELL][DIST]]+CLHIT);
			  y[1]=yposi(MOD,PLN+1,clchi[MOD][VIEW][PLN+1][celld[MOD][VIEW][PLN-DIST][CELL][DIST]]+CLHIT2);
			  y[2]=yposi(MOD,PLN+2+DIST2,clchi[MOD][VIEW][PLN+2+DIST2][celld[MOD][VIEW][PLN+1][CELL2][DIST2]]+CLHIT3);
			  TGraph *graph=new TGraph(3,x,y);
			  TF1 *f=new TF1("f","[0]+[1]*x");

			  f->SetParameters(y[0]-x[0]*(y[2]-y[0])/(x[2]-x[0]),(y[2]-y[0])/(x[2]-x[0]));
			  


			  graph->Fit("f","Q");
			  chi2=f->GetChisquare();
			  graph->Delete();
			    f->Delete();
			    if(DIST==0&&DIST2==0)ulimit=500;
			    else ulimit==280;
			    if(chi2<ulimit){
			      neiu[MOD][VIEW][PLN][nnei[MOD][VIEW][PLN][DIST][DIST2]][DIST][DIST2]=CELL;
			      neid[MOD][VIEW][PLN][nnei[MOD][VIEW][PLN][DIST][DIST2]][DIST][DIST2]=CELL2;
			      nnei[MOD][VIEW][PLN][DIST][DIST2]++;
			      neib=true;
			      //break;
			    }
			}
			//if(neib)break;
		      }
		      //if(neib)break;
		    }
		  }
		}
	      }
	    }
	  }
	}

	
	//*****Define value of cells*****
	memset(value[MOD][VIEW],0,sizeof(value[MOD][VIEW]));
	memset(nvalue[MOD][VIEW],0,sizeof(nvalue[MOD][VIEW]));
	for(int jndex=0;jndex<18;jndex++){
	  for(PLN=0;PLN<npln(MOD)-2;PLN++){
	    for(DIST=0;DIST<2;DIST++){
	      for(DIST2=0;DIST2<2;DIST2++){
		if(PLN==0&&DIST==1)continue;
		if(PLN==npln(MOD)-3&&DIST2==1)continue;
		if(DIST==1&&DIST2==1)continue;
		
		for(NEI=0;NEI<nnei[MOD][VIEW][PLN][DIST][DIST2];NEI++){
		  if(value[MOD][VIEW][PLN-DIST][neiu[MOD][VIEW][PLN][NEI][DIST][DIST2]][DIST]==value[MOD][VIEW][PLN+1][neid[MOD][VIEW][PLN][NEI][DIST][DIST2]][DIST2]){
		    nvalue[MOD][VIEW][PLN+1][neid[MOD][VIEW][PLN][NEI][DIST][DIST2]][DIST2]=value[MOD][VIEW][PLN+1][neid[MOD][VIEW][PLN][NEI][DIST][DIST2]][DIST2]+1;
		  }
		}
	      } 
	    }
	  }
	  for(PLN=0;PLN<npln(MOD)-1;PLN++){	   
	    for(DIST=0;DIST<2;DIST++){
	      if(PLN==npln(MOD)-2&&DIST==1)continue;
	      for(CELL=0;CELL<ncell[MOD][VIEW][PLN][DIST];CELL++){
		value[MOD][VIEW][PLN][CELL][DIST]=nvalue[MOD][VIEW][PLN][CELL][DIST];
	      }
	    }
	  }
	}




	//*****Define tracks*****
	ntrack[MOD][VIEW]=0;
	memset(ntracell[MOD][VIEW],0,sizeof(ntracell[MOD][VIEW]));
	memset(mishit[MOD][VIEW],0,sizeof(mishit[MOD][VIEW]));//MC tune
	for(PLN=1;PLN<npln(MOD)-1;PLN++){
	  for(DIST=0;DIST<2;DIST++){
	    if(PLN==npln(MOD)-2&&DIST==1)continue;
	    for(CELL=0;CELL<ncell[MOD][VIEW][PLN][DIST];CELL++){
	      if(value[MOD][VIEW][PLN][CELL][DIST]>0){
		if(PLN+DIST==npln(MOD)-2){upst=true;}
		else{
		  upst=true;
		  for(DIST2=0;DIST2<2;DIST2++){
		    if(DIST==1&&DIST2==1)continue;
		    for(NEI=0;NEI<nnei[MOD][VIEW][PLN+DIST][DIST][DIST2];NEI++){
		      //if(cellu[PLN][CELL]==cellu[PLN][neiu[PLN][NEI]])upst=false;
		      if(CELL==neiu[MOD][VIEW][PLN+DIST][NEI][DIST][DIST2])upst=false;
		    }
		  }
		}
		if(upst){
		  track_pln[MOD][VIEW][ntrack[MOD][VIEW]][0]=PLN;
		  track_cell[MOD][VIEW][ntrack[MOD][VIEW]][0]=CELL;
		  track_dist[MOD][VIEW][ntrack[MOD][VIEW]][0]=DIST;
		  if(DIST==1){mispln[MOD][VIEW][ntrack[MOD][VIEW]][0]=PLN+1;mishit[MOD][VIEW][ntrack[MOD][VIEW]]++;}//MC tune
		  ntracell[MOD][VIEW][ntrack[MOD][VIEW]]=1;
		  PLN2=PLN-1;
		  while(PLN2>=0){
		    dwst=true;
		    DIST3=track_dist[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]-1];
		    for(DIST2=0;DIST2<2;DIST2++){
		      if(DIST3==1&&DIST2==1)continue;
		      if(DIST2==1&&PLN2==0)continue;
		      for(NEI=0;NEI<nnei[MOD][VIEW][PLN2][DIST2][DIST3];NEI++){
			if(neid[MOD][VIEW][PLN2][NEI][DIST2][DIST3]==track_cell[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]-1]&&
			   value[MOD][VIEW][PLN2-DIST2][neiu[MOD][VIEW][PLN2][NEI][DIST2][DIST3]][DIST2]+1==value[MOD][VIEW][PLN2+1][neid[MOD][VIEW][PLN2][NEI][DIST2][DIST3]][DIST3]){
			  if(!dwst){

			    x[0]=xposi(MOD,VIEW,PLN2-DIST2);
			    x[1]=xposi(MOD,VIEW,PLN2+1);
			    x[2]=xposi(MOD,VIEW,PLN2+2+DIST3);
			    
			    y[0]=clcenter[MOD][VIEW][PLN2-DIST2][cellu[MOD][VIEW][PLN2-DIST2][track_cell[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]][DIST2]];
			    y[1]=clcenter[MOD][VIEW][PLN2+1][celld[MOD][VIEW][PLN2-DIST2][track_cell[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]][DIST2]];
			    y[2]=clcenter[MOD][VIEW][PLN2+2+DIST3][celld[MOD][VIEW][PLN2+1][track_cell[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]-1]][DIST3]];
			    
			    
			    TGraph *graph=new TGraph(3,x,y);
			    TF1 *f=new TF1("f","[0]+[1]*x");
			    f->SetParameters(y[0]-x[0]*(y[2]-y[0])/(x[2]-x[0]),(y[2]-y[0])/(x[2]-x[0]));
			    
			    graph->Fit("f","Q");
			    chi2=f->GetChisquare();
			    graph->Delete();
			    f->Delete();
			    
			    y[0]=clcenter[MOD][VIEW][PLN2-DIST2][cellu[MOD][VIEW][PLN2-DIST2][neiu[MOD][VIEW][PLN2][NEI][DIST2][DIST3]][DIST2]];
			    
			    TGraph *graph=new TGraph(3,x,y);
			    TF1 *f=new TF1("f","[0]+[1]*x");
			    f->SetParameters(y[0]-x[0]*(y[2]-y[0])/(x[2]-x[0]),(y[2]-y[0])/(x[2]-x[0]));
			    
			    graph->Fit("f","Q");
			    tmp=f->GetChisquare();
			    graph->Delete();
			    f->Delete();


			    if(tmp>chi2)continue;
			  
			  }
			
			  track_cell[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]=neiu[MOD][VIEW][PLN2][NEI][DIST2][DIST3];
			  track_pln[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]=PLN2-DIST2;
			  track_dist[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]=DIST2;

			  dwst=false;
			}
			//if(!dwst)break;
		      }//NEI
		      if(!dwst)break;
		    }
		    if(dwst)break;
		    if(track_dist[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]==1){mispln[MOD][VIEW][ntrack[MOD][VIEW]][mishit[MOD][VIEW][ntrack[MOD][VIEW]]]=track_pln[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]+1;mishit[MOD][VIEW][ntrack[MOD][VIEW]]++;}//MC tune
		    PLN2=PLN2-track_dist[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]]-1;

		    ntracell[MOD][VIEW][ntrack[MOD][VIEW]]++;
		    
		  }

		  //mishit[MOD][VIEW][ntrack[MOD][VIEW]]=(track_pln[MOD][VIEW][ntrack[MOD][VIEW]][0]-track_pln[MOD][VIEW][ntrack[MOD][VIEW]][ntracell[MOD][VIEW][ntrack[MOD][VIEW]]-1]+1)-(ntracell[MOD][VIEW][ntrack[MOD][VIEW]]);//MC tune
		  suchit[MOD][VIEW][ntrack[MOD][VIEW]]=ntracell[MOD][VIEW][ntrack[MOD][VIEW]]-1;//MC tune
		  ntrack[MOD][VIEW]++;

		}
	      }
	    }
	  }
	}




	//*****Set track points*****
	memset(trape[MOD][VIEW],0,sizeof(trape[MOD][VIEW]));
	for(TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  plane[MOD][VIEW][TRA][0]=track_pln[MOD][VIEW][TRA][0]+track_dist[MOD][VIEW][TRA][0]+1;
	  clus[MOD][VIEW][TRA][0]=celld[MOD][VIEW][track_pln[MOD][VIEW][TRA][0]][track_cell[MOD][VIEW][TRA][0]][track_dist[MOD][VIEW][TRA][0]];
	  X[MOD][VIEW][TRA][0]=xposi(MOD,VIEW,plane[MOD][VIEW][TRA][0]);
	  Y[MOD][VIEW][TRA][0]=clcenter[MOD][VIEW][plane[MOD][VIEW][TRA][0]][clus[MOD][VIEW][TRA][0]];
	  trape[MOD][VIEW][TRA]+=clpe[MOD][VIEW][plane[MOD][VIEW][TRA][0]][clus[MOD][VIEW][TRA][0]];
	  
	  for(TRACELL=0;TRACELL<ntracell[MOD][VIEW][TRA];TRACELL++){
	  
	    plane[MOD][VIEW][TRA][TRACELL+1]=track_pln[MOD][VIEW][TRA][TRACELL];
	    clus[MOD][VIEW][TRA][TRACELL+1]=cellu[MOD][VIEW][track_pln[MOD][VIEW][TRA][TRACELL]][track_cell[MOD][VIEW][TRA][TRACELL]][track_dist[MOD][VIEW][TRA][TRACELL]];
	    X[MOD][VIEW][TRA][TRACELL+1]=xposi(MOD,VIEW,plane[MOD][VIEW][TRA][TRACELL+1]);
	    Y[MOD][VIEW][TRA][TRACELL+1]=clcenter[MOD][VIEW][plane[MOD][VIEW][TRA][TRACELL+1]][clus[MOD][VIEW][TRA][TRACELL+1]];
	    trape[MOD][VIEW][TRA]+=clpe[MOD][VIEW][plane[MOD][VIEW][TRA][TRACELL+1]][clus[MOD][VIEW][TRA][TRACELL+1]];


	  }
	  ntracl[MOD][VIEW][TRA]=ntracell[MOD][VIEW][TRA]+1;
	}
	



	
	//*****Fit tracks*****
	for(TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  TGraph *g=new TGraph(ntracell[MOD][VIEW][TRA]+1,X[MOD][VIEW][TRA],Y[MOD][VIEW][TRA]);
	  TF1 *f=new TF1("f","[0]+[1]*x");
	  f->SetParameters(Y[MOD][VIEW][TRA][0]-X[MOD][VIEW][TRA][0]*(Y[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]]-Y[MOD][VIEW][TRA][0])/(X[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]]-X[MOD][VIEW][TRA][0]),(Y[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]]-Y[MOD][VIEW][TRA][0])/(X[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]]-X[MOD][VIEW][TRA][0]));
	  g->Fit("f","Q");
	  TF1 *func=g->GetFunction("f");
	  par[MOD][VIEW][TRA][0]=func->GetParameter(0);
	  par[MOD][VIEW][TRA][1]=func->GetParameter(1);

	  g->Delete();
	  f->Delete();
	}




	//*****Track rank*****
	memset(trank[MOD][VIEW],0,sizeof(trank[MOD][VIEW]));
	memset(rank[MOD][VIEW],0,sizeof(rank[MOD][VIEW]));
	memset(ncltra[MOD][VIEW],0,sizeof(ncltra[MOD][VIEW]));
	ntrack2[MOD][VIEW]=0;
	for(TRACL=18;TRACL>0;TRACL--){
	  for(TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	    if(ntracl[MOD][VIEW][TRA]==TRACL){
	      trank[MOD][VIEW][TRACL][ncltra[MOD][VIEW][TRACL]]=TRA;
	      ncltra[MOD][VIEW][TRACL]++;
	    }
	  }

	  for(CL=0;CL<ncltra[MOD][VIEW][TRACL];CL++){
	    for(CL2=CL+1;CL2<ncltra[MOD][VIEW][TRACL];CL2++){
	      if(trape[MOD][VIEW][trank[MOD][VIEW][TRACL][CL]]<trape[MOD][VIEW][trank[MOD][VIEW][TRACL][CL2]]){
		dummy=trank[MOD][VIEW][TRACL][CL];
		trank[MOD][VIEW][TRACL][CL]=trank[MOD][VIEW][TRACL][CL2];
	      trank[MOD][VIEW][TRACL][CL2]=dummy;
	      }
	    }
	    rank[MOD][VIEW][ntrack2[MOD][VIEW]]=trank[MOD][VIEW][TRACL][CL];
	    ntrack2[MOD][VIEW]++;
	  }
	}


   
	//*****True track selection*****
	memset(ttrack[MOD][VIEW],true,sizeof(ttrack[MOD][VIEW]));
	memset(hitcl[MOD][VIEW],false,sizeof(hitcl[MOD][VIEW]));
	memset(ntracl2[MOD][VIEW],0,sizeof(ntracl2[MOD][VIEW]));
	memset(ovcl[MOD][VIEW],false,sizeof(ovcl[MOD][VIEW]));//add
	ntrack2[MOD][VIEW]=0;
	for(TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  TRA2=rank[MOD][VIEW][TRA];
	  for(TRACL=0;TRACL<ntracl[MOD][VIEW][TRA2];TRACL++){
	    if(!hitcl[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL]][clus[MOD][VIEW][TRA2][TRACL]]
	       &&clpe[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL]][clus[MOD][VIEW][TRA2][TRACL]]>6.0){
	      ntracl2[MOD][VIEW][TRA2]++;
	    }
	  }


	  if(ntracl2[MOD][VIEW][TRA2]==2){
	  for(TRACL2=0;TRACL2<ntracl[MOD][VIEW][TRA2];TRACL2++){
	    if(!hitcl[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL2]][clus[MOD][VIEW][TRA2][TRACL2]]
	       &&clpe[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL2]][clus[MOD][VIEW][TRA2][TRACL2]]>6.0)break;
	  }
	  TRACL2++;
	    if(hitcl[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL2]][clus[MOD][VIEW][TRA2][TRACL2]]
	       &&clpe[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL2]][clus[MOD][VIEW][TRA2][TRACL2]]>6.0)ntracl2[MOD][VIEW][TRA2]=1;
	  
	  }
	  


	  if(ntracl2[MOD][VIEW][TRA2]>1){
	    for(TRACL=0;TRACL<ntracl[MOD][VIEW][TRA2];TRACL++){
	      if(hitcl[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL]][clus[MOD][VIEW][TRA2][TRACL]]==true)ovcl[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL]][clus[MOD][VIEW][TRA2][TRACL]]=true;//add
	      
	      hitcl[MOD][VIEW][plane[MOD][VIEW][TRA2][TRACL]][clus[MOD][VIEW][TRA2][TRACL]]=true;
	    }
	    ntrack2[MOD][VIEW]++;
	  }
	  else ttrack[MOD][VIEW][TRA2]=false;
	}



      }

      }


      //***# of not reconstructed hits***
      memset(nmhit,0,sizeof(nmhit));
      memset(trahit,0,sizeof(trahit));//MC tune
      for(int MOD=0;MOD<17;MOD++){
	//if(MOD>6&&MOD<16)continue;
	if(MOD!=16&&MOD!=3)continue;
	if(MOD==3)TMP=1;
	else if(MOD==16)TMP=0;
	for(int VIEW=0;VIEW<2;VIEW++){
	  for(int PLN=0;PLN<18;PLN++){
	    for(int CL=0;CL<ncl[MOD][VIEW][PLN];CL++){
	
	      if(!hitcl[MOD][VIEW][PLN][CL])nmhit[TMP][VIEW]+=clchf[MOD][VIEW][PLN][CL]-clchi[MOD][VIEW][PLN][CL]+1;


	      else{
		if(clchf[MOD][VIEW][PLN][CL]==clchi[MOD][VIEW][PLN][CL]){
		  int CH=clchf[MOD][VIEW][PLN][CL];
		  hitpe[TMP][VIEW][trahit[TMP][VIEW]]=pe[MOD][VIEW][hitnum[MOD][VIEW][PLN][CH]];
		  hitpln[TMP][VIEW][trahit[TMP][VIEW]]=PLN;
		  hitch[TMP][VIEW][trahit[TMP][VIEW]]=CH;
		  trahit[TMP][VIEW]++;
		}
	      }//MC tune
	      
	    }
	  }
	}
      }



      for(int MOD=16;MOD<17;MOD++){
      for(TRA=0;TRA<ntrack[MOD][0];TRA++){
	if(ttrack[MOD][0][TRA]==false)continue;

	for(TRA2=0;TRA2<ntrack[MOD][1];TRA2++){
	  if(ttrack[MOD][1][TRA2]==false)continue;

	  if(2*plane[MOD][0][TRA][0]-1>2*plane[MOD][1][TRA2][0])shita=2*plane[MOD][1][TRA2][0];
	  else shita=2*plane[MOD][0][TRA][0]-1;

	  if(2*plane[MOD][0][TRA][ntracl[MOD][0][TRA]-1]-1<2*plane[MOD][1][TRA2][ntracl[MOD][1][TRA2]-1])ue=2*plane[MOD][1][TRA2][ntracl[MOD][1][TRA2]-1];
	  else ue=2*plane[MOD][0][TRA][ntracl[MOD][0][TRA]-1]-1;

	  if(shita-ue>=3)goto MATCH;

	}
      }
      }
      select=-1;
      goto RES;

  
    MATCH:


      //*****upstream veto & edge channel cut*****
      select=4;
      for(int MOD=16;MOD<17;MOD++){
      for(int VIEW=0;VIEW<2;VIEW++){
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(ttrack[MOD][VIEW][TRA]==false)continue;
       	  if(plane[MOD][VIEW][TRA][ntracl[MOD][VIEW][TRA]-1]==0){select=1;goto RES;}
	  for(int TRACL=ntracl[MOD][VIEW][TRA]-2;TRACL<ntracl[MOD][VIEW][TRA];TRACL++){
	    for(CLHIT=0;CLHIT<numcl[MOD][VIEW][plane[MOD][VIEW][TRA][TRACL]][clus[MOD][VIEW][TRA][TRACL]];CLHIT++){
	      if(ch[MOD][VIEW][clhit[MOD][VIEW][plane[MOD][VIEW][TRA][TRACL]][clus[MOD][VIEW][TRA][TRACL]][CLHIT]]==0){select=2;goto RSIDE;}
	      else if(ch[MOD][VIEW][clhit[MOD][VIEW][plane[MOD][VIEW][TRA][TRACL]][clus[MOD][VIEW][TRA][TRACL]][CLHIT]]==31){select=2;goto RSIDE;}
	    }
	  }
	}
      }
      }



    RSIDE:
      //*****side veto*****
      for(int MOD=16;MOD<17;MOD++){
      for(int VIEW=0;VIEW<2;VIEW++){
	for(HIT=0;HIT<hit[MOD][VIEW];HIT++){
	  if(pln[MOD][VIEW][HIT]>17){
	    for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	      if(ttrack[MOD][VIEW][TRA]==false)continue;
	      if(par[MOD][VIEW][TRA][1]>0){
		if(vposiy(MOD,pln[MOD][VIEW][HIT])==1255)continue;
		if(X[MOD][VIEW][TRA][ntracl[MOD][VIEW][TRA]-1]-(0-par[MOD][VIEW][TRA][0])/par[MOD][VIEW][TRA][1]>46*2)continue;
	      }
	      else if(par[MOD][VIEW][TRA][1]<0){
		if(vposiy(MOD,pln[MOD][VIEW][HIT])==-55)continue;
		if(X[MOD][VIEW][TRA][ntracl[MOD][VIEW][TRA]-1]-(1200-par[MOD][VIEW][TRA][0])/par[MOD][VIEW][TRA][1]>46*2)continue;
	      }
	      
	      dis=fabs(par[MOD][VIEW][TRA][1]*vposix(MOD,ch[MOD][VIEW][HIT])-vposiy(MOD,pln[MOD][VIEW][HIT])+par[MOD][VIEW][TRA][0])/sqrt((par[MOD][VIEW][TRA][1])**2+1);
	      if(dis<80){select=3;goto RES;}
	    }
	  }
	}
      }
      }
    RES:



      //*****cut low upstream hit****
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(ttrack[MOD][VIEW][TRA]&&clpe[MOD][VIEW][plane[MOD][VIEW][TRA][ntracl[MOD][VIEW][TRA]-1]][clus[MOD][VIEW][TRA][ntracl[MOD][VIEW][TRA]-1]]<4.5){
	    if(ntracl[MOD][VIEW][TRA]==3){ttrack[MOD][VIEW][TRA]=false;ntrack2[MOD][VIEW]--;continue;}
	    ntracl[MOD][VIEW][TRA]--;
	    ntracell[MOD][VIEW][TRA]--;
	  }
	}
      }
      }



      //*****track upstream point matching******
      memset(ttrack2,false,sizeof(ttrack2));
      memset(ntrack3,0,sizeof(ntrack3));
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	if(ntrack2[MOD][VIEW]<2)continue;
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(!ttrack[MOD][VIEW][TRA])continue;
	  for(int TRA2=TRA+1;TRA2<ntrack[MOD][VIEW];TRA2++){
	    if(!ttrack[MOD][VIEW][TRA2])continue;	   
	    if((X[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]]-X[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]])**2+(Y[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]]-Y[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]])**2<100**2){

	      if(!ttrack2[MOD][VIEW][TRA]){
		ttrack2[MOD][VIEW][TRA]=true;
		ntrack3[MOD][VIEW]++;
	      }
	      if(!ttrack2[MOD][VIEW][TRA2]){
		ttrack2[MOD][VIEW][TRA2]=true;
		ntrack3[MOD][VIEW]++;
	      }

	    }

	  }
	}
      }
      }
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	if(ntrack3[MOD][VIEW]==0&&ntrack2[MOD][VIEW]>0)ntrack3[MOD][VIEW]=1;
      }
      }



      //*****track length****
      memset(length,0,sizeof(length));
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(ttrack[MOD][VIEW][TRA]&&ntracell[MOD][VIEW][TRA]>length[MOD][VIEW]){
	    length[MOD][VIEW]=plane[MOD][VIEW][TRA][0]-plane[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]];
	    ang[MOD][VIEW]=180/3.14*atan(par[MOD][VIEW][TRA][1]);
	  }
	}
      }
      }




      //*****true track info****
      memset(fini,0,sizeof(fini));
      memset(star,0,sizeof(star));
      memset(sep,0,sizeof(sep));
      memset(kat,0,sizeof(kat));
      memset(shar,0,sizeof(shar));
      memset(totpe,0,sizeof(totpe));
      memset(ntra,0,sizeof(ntra));
      memset(mtra,0,sizeof(mtra));
      memset(nmis,0,sizeof(nmis));//MC tune
      memset(nsuc,0,sizeof(nsuc));//MC tune
      memset(plnmis,0,sizeof(plnmis));//MC tune
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
	if(MOD==3)TMP=1;
	else if(MOD==16)TMP=0;
      for(int VIEW=0;VIEW<2;VIEW++){
	TRA2=0;
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(ttrack[MOD][VIEW][TRA]){
	    fini[TMP][VIEW][TRA2]=plane[MOD][VIEW][TRA][0];
	    star[TMP][VIEW][TRA2]=plane[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]];
	    sep[TMP][VIEW][TRA2]=par[MOD][VIEW][TRA][0];
	    kat[TMP][VIEW][TRA2]=par[MOD][VIEW][TRA][1];
	    shar[TMP][VIEW][TRA2]=ttrack2[MOD][VIEW][TRA];
	    totpe[TMP][VIEW][TRA2]=trape[MOD][VIEW][TRA];
	    nmis[TMP][VIEW][TRA2]=mishit[MOD][VIEW][TRA];//MC tune
	    nsuc[TMP][VIEW][TRA2]=suchit[MOD][VIEW][TRA];//MC tune
	    for(int HIT=0;HIT<nmis[TMP][VIEW][TRA2];HIT++)plnmis[TMP][VIEW][TRA2][HIT]=mispln[MOD][VIEW][TRA][HIT];//MC tune
	    ntra[TMP][VIEW]++;
	    if(ttrack2[MOD][VIEW][TRA])mtra[TMP][VIEW]++;
	    TRA2++;
	  }
	}
      }
      }





      //*****cluster energy deposit*****
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	memset(cluspe[MOD][VIEW],0,sizeof(cluspe[MOD][VIEW]));
	memset(clpdg[MOD][VIEW],0,sizeof(clpdg[MOD][VIEW]));
	for(PLN=0;PLN<npln(MOD);PLN++){
	  for(CL=0;CL<ncl[MOD][VIEW][PLN];CL++){
	    for(CLHIT=0;CLHIT<numcl[MOD][VIEW][PLN][CL];CLHIT++){
	      if(ch[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]<8||ch[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]>23)
		cluspe[MOD][VIEW][PLN][CL]+=pe[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]];
	      else
		cluspe[MOD][VIEW][PLN][CL]+=pe[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]/1.3;
	      

	      //add
	      if(/*pdg[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]==11||*/pdg[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]==-11)clpdg[MOD][VIEW][PLN][CL][0]++;

	      else if(pdg[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]==13)clpdg[MOD][VIEW][PLN][CL][1]++;
	      else if(pdg[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]==211||pdg[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]==-211)clpdg[MOD][VIEW][PLN][CL][2]++;
	      else if(pdg[MOD][VIEW][clhit[MOD][VIEW][PLN][CL][CLHIT]]==2212)clpdg[MOD][VIEW][PLN][CL][3]++;

	    }
	  }
	}
      }
      }


      //****track energy deposit****
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){      
	memset(trackpe[MOD][VIEW],0,sizeof(trackpe[MOD][VIEW]));
	memset(trackpdg[MOD][VIEW],0,sizeof(trackpdg[MOD][VIEW]));
	memset(len[MOD][VIEW],0,sizeof(len[MOD][VIEW]));
	for(TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  for(TRACELL=0;TRACELL<ntracell[MOD][VIEW][TRA]+1;TRACELL++){
	    if(!ovcl[MOD][VIEW][plane[MOD][VIEW][TRA][TRACELL]][clus[MOD][VIEW][TRA][TRACELL]]){
	      trackpe[MOD][VIEW][TRA]+=cluspe[MOD][VIEW][plane[MOD][VIEW][TRA][TRACELL]][clus[MOD][VIEW][TRA][TRACELL]];
	      len[MOD][VIEW][TRA]++;
	      for(TMP=0;TMP<4;TMP++)
		trackpdg[MOD][VIEW][TRA][TMP]+=clpdg[MOD][VIEW][plane[MOD][VIEW][TRA][TRACELL]][clus[MOD][VIEW][TRA][TRACELL]][TMP];
	    }
	  }
	}
      }
      }


      /*
      //****track pid****
      memset(trapdg,0,sizeof(trapdg));
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){	  
	  for(TMP=1;TMP<4;TMP++){
	    if(trackpdg[MOD][VIEW][TRA][trapdg[MOD][VIEW][TRA]]<trackpdg[MOD][VIEW][TRA][TMP])trapdg[MOD][VIEW][TRA]=TMP;
	  }
	}
      }
      }

      //*****track angle+length+dE/dx*****
      memset(hosei,0,sizeof(hosei));
      memset(dedx,0,sizeof(dedx));
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(!ttrack[MOD][VIEW][TRA])continue;
	  hosei[MOD][VIEW][TRA]=1/sqrt(par[MOD][VIEW][TRA][1]**2+1);
	  dedx[MOD][VIEW][TRA]=trackpe[MOD][VIEW][TRA]/len[MOD][VIEW][TRA]*hosei[MOD][VIEW][TRA];
	}
      }
      }
      */

      xnu=800,ynu=800,znux=800,znuy=800,vi=0;
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
	for(int VIEW=0;VIEW<2;VIEW++){
	  for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	    TRA2=rank[MOD][VIEW][TRA];
	    if(ttrack[MOD][VIEW][TRA2]){
	      if(VIEW==0){
		if(znuy>X[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]]){
		  znuy=X[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]];
		  ynu=Y[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]];
		}
	      }
	      else{
		if(znux>X[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]]){
		  znux=X[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]];
		  xnu=Y[MOD][VIEW][TRA2][ntracell[MOD][VIEW][TRA2]];
		}
	      }
	    }
	  }
	}
      }


        if(ntrack2[1]<ntrack2[0])ntracks=ntrack2[0];
	else ntracks=ntrack2[1];
	if(ntrack3[1]<ntrack3[0])mtracks=ntrack3[0];
	else mtracks=ntrack3[1];
	if(znux<znuy){znu=znux;vi=0;}
	else{znu=znuy;vi=1;}


	
      if(ntrack2[0]==0||ntrack2[1]==0){
	select=0;
	//cout<<"not tracked"<<endl;
	nnotra++;	
	//continue;
      }
      else if(select==-1){
	//cout<<"not matched"<<endl;
	nnomatch++;	
	//continue;
      }
      else if(select==1){
	//cout<<"front veto"<<endl;
	nfro++;	
	//continue;
      }
      else if(select==2){
	//cout<<"edge channel"<<endl;
	nedg++;
	//continue;
      }
      else if(select==3){
	//cout<<"side veto"<<endl;
	nsid++;	
	//continue;
      }
      else{
	//cout<<"neutrino"<<endl;
	nint++;
	//continue;
      }

      /*
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){
	//if(VIEW==0)cout<<"yoko"<<endl;
	//else cout<<"tate"<<endl;
	for(int TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(ttrack[MOD][VIEW][TRA])
	  cout<<trapdg[MOD][VIEW][TRA]<<":"<<dedx[MOD][VIEW][TRA]<<endl;
	}
      }
      }
      */



      if(jentry%100==0)cout<<jentry<<"entries"<<endl;
      tree->Fill();
      if(jentry%200==0)tree->Write();


#ifdef DISPLAY
      //*****Draw module*****
      c1->Divide(1,2);
      c1->cd(1);
      h->Draw();
      drawx();
      c1->cd(2);
      v->Draw();
      drawy();
      
      for(int MOD=0;MOD<17;MOD++){if(MOD!=3&&MOD!=16)continue;
      for(int VIEW=0;VIEW<2;VIEW++){	

	//*****Start drawing*****
	c1->cd(VIEW+1);

	//*****Draw hits*****
	for(Long64_t i=0;i<hit[MOD][VIEW];i++){

	  
	  if(MOD==16){
	  if(VIEW==0){
	    if(pln[MOD][VIEW][i]<18)xhit(pln[MOD][VIEW][i],ch[MOD][VIEW][i],(double)pe[MOD][VIEW][i]);
	    else vhit(pln[MOD][VIEW][i]-18,ch[MOD][VIEW][i],(double)pe[MOD][VIEW][i]);
	  }
	  else{
	    if(pln[MOD][VIEW][i]<18)yhit(pln[MOD][VIEW][i],ch[MOD][VIEW][i],(double)pe[MOD][VIEW][i]);
	    else vhit(pln[MOD][VIEW][i]-21,ch[MOD][VIEW][i],(double)pe[MOD][VIEW][i]);
	  }
	  }
	  else if(MOD==3){
	    if(VIEW==0){
	      if(pln[MOD][VIEW][i]<11)xihit(pln[MOD][VIEW][i],ch[MOD][VIEW][i],(double)pe[MOD][VIEW][i]);
	    }
	    else{
	      if(pln[MOD][VIEW][i]<11)yihit(pln[MOD][VIEW][i],ch[MOD][VIEW][i],(double)pe[MOD][VIEW][i]);
	    }
	  }

	}
	
	
	//*****Draw clusters*****
	for(PLN=0;PLN<npln(MOD);PLN++){
	  for(CL=0;CL<ncl[MOD][VIEW][PLN];CL++){
	    cluster(MOD,VIEW,PLN,clchi[MOD][VIEW][PLN][CL],clchf[MOD][VIEW][PLN][CL]);
	  }
	}

	
	//*****Draw cells*****
	for(PLN=0;PLN<npln(MOD)-1;PLN++){
	  for(DIST=0;DIST<2;DIST++){
	    if(PLN==npln(MOD)-2&&DIST==1)continue;
	    for(CELL=0;CELL<ncell[MOD][VIEW][PLN][DIST];CELL++){
	      //cline(MOD,VIEW,PLN,clcenter[MOD][VIEW][PLN][cellu[MOD][VIEW][PLN][CELL][DIST]],clcenter[MOD][VIEW][PLN+1+DIST][celld[MOD][VIEW][PLN][CELL][DIST]],value[MOD][VIEW][PLN][CELL][DIST],DIST);
	    }
	  }
	}

	//*****Draw tracks*****
	for(TRA=0;TRA<ntrack[MOD][VIEW];TRA++){
	  if(ttrack[MOD][VIEW][TRA])
	    tline(MOD,X[MOD][VIEW][TRA][ntracell[MOD][VIEW][TRA]],X[MOD][VIEW][TRA][0],par[MOD][VIEW][TRA][0],par[MOD][VIEW][TRA][1]);
	}

	
      }
      }

      cout<<jentry<<"th event"<<endl;
      cout<<icyc<<"th cycle"<<endl;
      cout<<ntrack3[16][0]<<" track(s) from Side view"<<endl;
      cout<<ntrack3[16][1]<<" track(s) from Top view"<<endl;
      Mode(mode);

      c1->Update();
      printf("Type \'n\' to go to the next event.\n");
      printf("Type \'q\' to quit.\n");


      
      while( gets(ans)){
	if( *ans == 'n') break;
	else if( *ans == 'q') break;
    }
      if( *ans == 'q') break;
      
      c1->Clear();
#endif
    }
    if( *ans == 'q') break;
  }




  tree->Write();
  file->Close();


  cout<<"actpln"<<nactcut<<endl;
  cout<<"pecut"<<npecut<<endl;
  cout<<"notrack"<<nnotra<<endl;
  cout<<"nomatch"<<nnomatch<<endl;
  cout<<"front"<<nfro<<endl;
  cout<<"edge"<<nedg<<endl;
  cout<<"side"<<nsid<<endl;
  cout<<"end"<<endl;
  
}
