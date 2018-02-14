void Mode(int num);

void Mode(int num){

      if(num<11)cout<<"CCQE"<<endl;
      else if(num<17)cout<<"CC1PI"<<endl;
      else if(num<21)cout<<"CC1GAMMA"<<endl;
      else if(num<22)cout<<"CCMultiPI"<<endl;
      else if(num<23)cout<<"CC1ETA"<<endl;
      else if(num<26)cout<<"CC1K"<<endl;
      else if(num<31)cout<<"CCDIS"<<endl;
      else if(num<38)cout<<"NC1PI"<<endl;
      else if(num<41)cout<<"N1GAMMA"<<endl;
      else if(num<42)cout<<"NCMultiPI"<<endl;
      else if(num<44)cout<<"NC1ETA"<<endl;
      else if(num<46)cout<<"NC1K"<<endl;
      else if(num<51)cout<<"NCDIS"<<endl;
      else cout<<"NCE"<<endl;

}
