#define dist 240  

void xhit(int x,int y,double r);
void yhit(int x,int y,double r);
void vhit(int x,int y,double r);
void xihit(int x,int y;double r);
void yihit(int x,int y;double r);
void vihit(int x,int y;double r);
void sci_ing(double x,double y,double x1,double y1);
void sci_par(double x,double y,double x1,double y1);
void sci_sci(double x,double y,double x1,double y1);
void sci_veto(double x,double y,double x1,double y1);
void iron(double x,double y,double x1,double y1);
void drawx(void);
void drawy(void);



void xhit(int x,int y,double r){
  double X,Y,R;
  if(x==0)X=5;
  else X=46*x+9;
  if(x==0)Y=y*50+25;
  else{
  if(y<8)Y=y*50+25;
  else if(y<24)Y=412.5+(y-8)*25;
  else Y=(y-8)*50+25;
  }
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  TArc *arc=new TArc(X,Y,R);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");

}


void yhit(int x,int y,double r){
  double X,Y,R;
  if(x==0)X=28;
  else X=46*x+32;
  if(x==0)Y=y*50+25;
  else{
  if(y<8)Y=y*50+25;
  else if(y<24)Y=412.5+(y-8)*25;
  else Y=(y-8)*50+25;
  }
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  TArc *arc=new TArc(X,Y,R);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}


void vhit(int x,int y,double r){
  double X,Y,R;
  if(x==0)Y=-55;
  else Y=1255;
  X=9.5+y*50;
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  TArc *arc=new TArc(X,Y,R);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}



void xihit(int x,int y,double r){
  double X,Y,R;
  X=105*x+791+dist;
  Y=y*50+25;
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  TArc *arc=new TArc(X,Y,R);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");

}



void yihit(int x,int y,double r){
  double X,Y,R;
  X=105*x+801+dist;
  Y=y*50+25;
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  TArc *arc=new TArc(X,Y,R);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}


void vihit(int x,int y,double r){
  double X,Y,R;
  if(x==0)Y=-55-20;
  else Y=1255+20;
  X=9.5+y*50+1020;
  if(r<2)R=0;
  else R=sqrt(r-2)*3;
  TArc *arc=new TArc(X,Y,R);
  arc->SetFillColor(kRed);
  arc->SetLineColor(kRed);
  arc->Draw("SAME");
}


void sci_ing(double x,double y,double x1,double y1){
  TBox *b1=new TBox(x,y,x1,y1);
  b1->SetLineColor(kGreen);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}
void sci_par(double x,double y,double x1,double y1){
  TBox *b1=new TBox(x,y,x1,y1);
  b1->SetLineColor(kYellow);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}
void sci_sci(double x,double y,double x1,double y1){
  TBox *b1=new TBox(x,y,x1,y1);
  b1->SetLineColor(kGreen+2);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}
void sci_veto(double x,double y,double x1,double y1){
  TBox *b1=new TBox(x,y,x1,y1);
  b1->SetLineColor(kBlue);
  b1->SetLineWidth(2);
  b1->SetFillStyle(0);
  b1->Draw("SAME");
}


void iron(double x,double y,double x1,double y1){
  TBox *b1=new TBox(x,y,x1,y1);
  b1->SetFillColor(17);
  b1->SetLineWidth(2);
  b1->SetFillStyle(1);
  b1->Draw("SAME");
}




void drawx(void){
  
  int k,j,i;

  for(j=0;j<24;j++)sci_ing(0,j*50,10,j*50+50);
  sci_par(23,0,33,1200);
  for(k=0;k<17;k++){
    for(j=0;j<8;j++)sci_ing(50+46*k,j*50,60+46*k,j*50+50);
    for(j=16;j<24;j++)sci_ing(50+46*k,j*50,60+46*k,j*50+50);
    for(j=0;j<16;j++)sci_sci(48.5+46*k,400+j*25,61.5+46*k,j*25+425);
  sci_par(73+46*k,0,83+46*k,1200);
  }
  for(j=0;j<17;j++)sci_veto(-15.5+50*j,-60,34.5+50*j,-50);
  for(j=0;j<17;j++)sci_veto(-15.5+50*j,1250,34.5+50*j,1260);



  for(k=0;k<11;k++){
    for(j=0;j<24;j++)sci_ing(105*k+786+dist,j*50,105*k+796+dist,j*50+50);
  }
  for(k=0;k<9;k++)iron(105*k+816+dist,0,105*k+881+dist,1200);

  for(j=0;j<22;j++)sci_veto(-15.5+50*j+1020,-60-20,34.5+50*j+1020,-50-20);
  for(j=0;j<22;j++)sci_veto(-15.5+50*j+1020,1250+20,34.5+50*j+1020,1260+20);


  
}


void drawy(void){
  
  int k,j,i;
  for(j=0;j<24;j++)sci_ing(23,j*50,33,j*50+50);
  sci_par(0,0,10,1200);

  for(k=0;k<17;k++){
    for(j=0;j<8;j++)sci_ing(73+46*k,j*50,83+46*k,j*50+50);
    for(j=16;j<24;j++)sci_ing(73+46*k,j*50,83+46*k,j*50+50);
    for(j=0;j<16;j++)sci_sci(71.5+46*k,400+j*25,84.5+46*k,j*25+425);
  sci_par(50+46*k,0,60+46*k,1200);
  }
  for(j=0;j<17;j++)sci_veto(-15.5+50*j,-60,34.5+50*j,-50);
  for(j=0;j<17;j++)sci_veto(-15.5+50*j,1250,34.5+50*j,1260);
 


  for(k=0;k<11;k++){
    for(j=0;j<24;j++)sci_ing(105*k+796+dist,j*50,105*k+806+dist,j*50+50);
  }
  for(k=0;k<9;k++)iron(105*k+816+dist,0,105*k+881+dist,1200);

  for(j=0;j<22;j++)sci_veto(-15.5+50*j+1020,-60-20,34.5+50*j+1020,-50-20);
  for(j=0;j<22;j++)sci_veto(-15.5+50*j+1020,1250+20,34.5+50*j+1020,1260+20);


 
}
