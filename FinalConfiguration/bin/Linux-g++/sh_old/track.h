#define NMOD 17
#define DISTANCE 240

int PLN,PLN2,CH,CL,CL2,CLHIT,CLHIT2,CLHIT3,CELL,CELL2,NEI,TRA,TRA2,TRACELL,TRACL,TRACL2,HIT,DIST,DIST2,DIST3,dummy,TMP;
int hitnum[NMOD][2][18][32];
bool hitcl[NMOD][2][18][16];
int clchi[NMOD][2][18][16],clchf[NMOD][2][18][16],ncl[NMOD][2][18],clcenter[NMOD][2][18][16],numcl[NMOD][2][18][16],clhit[NMOD][2][18][16][10],clpe[NMOD][2][18][16];
int cellu[NMOD][2][17][500][2],celld[NMOD][2][17][500][2],ncell[NMOD][2][17][2],value[NMOD][2][17][500][2],nvalue[NMOD][2][17][500][2];
int neiu[NMOD][2][16][500][2][2],neid[NMOD][2][16][500][2][2],nnei[NMOD][2][16][2][2];
int track_cell[NMOD][2][500][17],track_pln[NMOD][2][500][17],track_dist[NMOD][2][500][17],ntracell[NMOD][2][500],ntracl[NMOD][2][500],ntracl2[NMOD][2][500],ntrack[NMOD][2],ntrack2[NMOD][2],ntrack3[NMOD][2],trank[NMOD][2][19][50],ncltra[NMOD][2][19],rank[NMOD][2][500];
bool ttrack[NMOD][2][500],ttrack2[NMOD][2][500];
bool neib;
int plane[NMOD][2][500][18],clus[NMOD][2][500][18];
float ang[NMOD][2];
float hosei[NMOD][2][500],dedx[NMOD][2][500],cluspe[NMOD][2][18][16],trackpe[NMOD][2][500];//add
int pdg[NMOD][2][1000],clpdg[NMOD][2][18][16][4],trackpdg[NMOD][2][500][4],trapdg[NMOD][2][500],len[NMOD][2][500];//add
bool ovcl[NMOD][2][18][16];//add
float dis;
float X[NMOD][2][500][18],Y[NMOD][2][500][18];
float x[3];
float y[3];
float chi2,tmp;
float par[NMOD][2][500][2];
float trape[NMOD][2][500];
float ulimit;
bool upst,dwst;
int select;
int nhit,view,mod,hit[NMOD][2],pe[NMOD][2][1000],pln[NMOD][2][1000],ch[NMOD][2][1000],timing[NMOD][2][1000];

int ue,shita;
bool actpln[8][2][18];
float peactpln[8];
int numactpln[8][2];
bool hitcyc[8];
int length[NMOD][2];
int ncychit[8];
int exptime[8];
float timecl[8];
float npecychit[8];

int star[2][2][50],fini[2][2][50];
float sep[2][2][50],kat[2][2][50],totpe[2][2][50];
bool shar[2][2][50];
int ntra[2][2],mtra[2][2];


void cluster(int mod,int view,int pln,int chi,int chf);
void cline(int mod,int view,int pln,float up,float down,int value,int dist);
void tline(int mod,int xup,int xdown,float seppen,float katamuki);
int xposi(int mod,int view,int pln);
float yposi(int mod,int pln,int ch);
float vposix(int mod,int ch);
int vposiy(int mod,int pln);
int npln(int mod);
int nch(int mod);

int xposi(int mod,int view,int pln){
  int X;

  if(mod==16){
  if(view==0){
    if(pln==0)X=5;
    else X=46*pln+9;
  }
  else{
    if(pln==0)X=28;
    else X=46*pln+32;
  }
  }
  else if(mod==3){
    X=105*pln+791+DISTANCE;
  }

  return X;
}


float yposi(int mod,int pln,int ch){
  float Y;

  if(mod==16){
  if(pln==0){
    Y=ch*50+25;
  }
  else{
    if(ch<8)Y=ch*50+25;
    else if(ch<24)Y=412.5+(ch-8)*25;
    else Y=(ch-8)*50+25;
  }
  }

  else if(mod==3){
    Y=ch*50+25;
  }

  return Y;
}


float vposix(int mod,int ch){
  float X;
  X=9.5+50*ch;
  return X;
}


int vposiy(int mod,int pln){
  int Y;
  if(pln==18||pln==21)Y=-55;
  else Y=1255;
  return Y;
}


void cluster(int mod,int view,int pln,int chi,int chf){
  TBox *b1=new TBox(xposi(mod,view,pln)-20,yposi(mod,pln,chi)-20,xposi(mod,view,pln)+20,yposi(mod,pln,chf)+20);
  b1->SetLineColor(kBlue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}


void cline(int mod,int view,int pln,float up,float down,int value,int dist){
  TLine *l1=new TLine(xposi(mod,view,pln),up, xposi(mod,view,pln+1+dist), down);
  l1->SetLineWidth(sqrt(sqrt(value)*8));
  l1->SetLineColor(28);
  l1->Draw("SAME");
}


void tline(int mod,int xup,int xdown,float seppen,float katamuki){
  TLine *l1=new TLine(xup,seppen+xup*katamuki, xdown, seppen+xdown*katamuki);
  l1->SetLineWidth(5);
  l1->Draw("SAME");
}

int npln(int mod){
  int pln;
  if(mod==16)pln=18;
  else pln=11;

  return pln;
}

int nch(int mod){
  int ch;
  if(mod==16)ch=32;
  else ch=24;
  return ch;
}
