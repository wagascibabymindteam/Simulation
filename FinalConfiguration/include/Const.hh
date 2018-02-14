#ifndef ___CONSTH
#define ___CONSTH 1

//run mode (option -m)
#define PROTON 2
#define HORIZONTAL 3
#define VERTICAL 4
#define WAGASCI 5
#define LEFTFE 6
#define DOWNFE 7
#define RIGHTFE 8

//max number of pln and ch (bigger is OK)
#define PLNMAX 80
#define CHMAX 100

//Geant4//////////

//world volume(m)
const double CWorldX = 25.0;
const double CWorldY = 20.0;
const double CWorldZ = 20.0;

//halldirt volume(m)
const double CHallDirtRadiusMin =  8.95;//2014/6/11
const double CHallDirtRadiusMax = (CHallDirtRadiusMin+9.0);//2014/6/11
const double CHallDirtHeight    = 10.;
const double CHallDirtSPhi      = 0;
const double CHallDirtDPhi      = 3.1415926535897932384626*2;
const double CHallDirtX         = -3.222;//2014/6/10  //position of center of Dirt
const double CHallDirtY         = 0.;
const double CHallDirtZ         = 1.7;
//upst surface of the floor
const double CFloorup = -5.944;//m
//pillar
const double CPillarX = 0.5;//m
const double CPillarY = 1.5;//m
const double CPillarZ = 2.0;//m
const double CPillarposX = -8.435;//m //20cm far temporary hontoha -8.235
const double CPillarposY = -4.443;//m
const double CPillarposZ = 2.631;//m
const double CPillarposX_rev = -8.035 + 5.0;//m //20cm far temporary hontoha -8.235 + 5.0


//air boxs to put each modules
//air box of 7 ingrids
const double CHorizonX = 5.25;//m        
const double CHorizonY = 1.0;//m
const double CHorizonZ = 68.0;//cm
//box of Proton modules 
const double CPHorizonZ=45.0;//cm
//air box of a ingrid
const double CModuleX=0.75;//m
const double CModuleY=0.75;//m
const double CModuleZ=65.0;//cm
//air box of Proton module
const double CPModuleZ=44.0;//cm
//Positions of ingrid modules
const double CModuleSpace= 1.50;//m     // 120 + 30  distance between the centers of two consecutive modules
const double CModuleStart=-4.50;//m     // -150*3 center of the first module

//position of wagasci,volume of target,distance between MRD and wagasci,number of veto,MRD plane
const double CGap_target_veto = 5.0;//cm
const double CTargetX = 100.0;//cm size of WAGASCI water module
const double CTargetY = 100.0;//cm
const double CTargetZ = 200.0;//cm

//air box of all of WAGASCHI
const double CWagaX = 2.15;//m
const double CWagaY = 1.45;//m
const double CWagaZ = 4.0;//m
const double CWagaposX = -5.722;//m
const double CWagaposY = -4.444;//m
const double CWagaposZ = 1.7+1.0;//m

//air boxs of part of WAGASCHI
//target and veto
const double CWagaboxX = 0.75;//m
const double CWagaboxY = 0.75;//m
const double CWagaboxZ = 1.25;//m
//downstream MRD
const double CWagaboxforX = 2.1;//m
const double CWagaboxforY = 1.3;//m
const double CWagaboxforZ = 1.32;//m
//left side MRD
const double CWagaboxsideX = 0.6;//m
const double CWagaboxsideY = 1.1;//m
const double CWagaboxsideZ = 1.61;//m //WIDTH
//upstream VETO
const double CWagaboxbackX = 2.1;//m
const double CWagaboxbackY = 1.3;//m
const double CWagaboxbackZ = 0.25;//m
//bottom VETO
const double CWagaboxbottomX = 1.1;//m
const double CWagaboxbottomY = 0.17;//m
const double CWagaboxbottomZ = 1.51;//m

//target and veto
const double CWagaboxposX = 0.;//m
const double CWagaboxposY = 0.;//m
const double CWagaboxposZ = -1.;//m
//downstream MRD
const double CWagaboxforposX = 0.;//m
const double CWagaboxforposY = 0.;//m
const double CWagaboxforposZ = 1.845;//m
//left side MRD
const double CWagaboxsideposX = 1.445;//m
const double CWagaboxsideposY = 0.;//m
const double CWagaboxsideposZ = -1.0;//m ??WIDTH
//upstream VETO
const double CWagaboxbackposX = 0.;//m
const double CWagaboxbackposY = 0.;//m
const double CWagaboxbackposZ = -2.845;//m
//bottom MRD
const double CWagaboxbottomposX = 0.;//m
const double CWagaboxbottomposY = -1.275;//m
const double CWagaboxbottomposZ = -1.;//m

//iron volume
//iron for side MRD
const double CIron2X = 1.6;//m
const double CIron2Y = 1.0;//m
const double CIron2Z = 1.50;//cm
//const double CIron2Z = 1.375;//cm
//iron for downstream MRD
const double CIron3X = 2.0;//m
const double CIron3Y = 1.0;//m
const double CIron3Z = 1.50;//cm
//iron for bottom MRD
const double CIron4X = 1.0;//m
const double CIron4Y = 1.50;//cm
const double CIron4Z = 1.5;//m

//scinttilator volume
//horizontal layers
//for side MRD 
const double CHlayer2X = 1.6;//m //WIDTH
const double CHlayer2Y = 2.5;//cm
const double CHlayer2Z = 0.5;//cm
//for downstream MRD and upstream veto
const double CHlayer3X = 2.0;//m
const double CHlayer3Y = 2.5;//cm
const double CHlayer3Z = 0.5;//cm
//don`t use now
const double CHlayer4X = 0.75;//m
const double CHlayer4Y = 2.5;//cm
const double CHlayer4Z = 0.15;//cm
//for downstream veto around wagasci
const double CHlayer5X = 0.625;//m
const double CHlayer5Y = 2.5;//cm
const double CHlayer5Z = 0.5;//cm
//for hlayer in wagasci
const double CHlayer6X = 0.5;//m
const double CHlayer6Y = 1.25;//cm
const double CHlayer6Z = 0.15;//cm
//for side veto around wagasci
const double CHlayer7X = 1.05;//m
const double CHlayer7Y = 2.5;//cm
const double CHlayer7Z = 0.5;//cm
//for bottom veto around wagasci
const double CHlayer8X = 0.625;//m
const double CHlayer8Y = 2.5;//cm
const double CHlayer8Z = 0.5;//cm
//for bottom MRD
const double CHlayer9X = 1.0;//m
const double CHlayer9Y = 0.5;//cm
const double CHlayer9Z = 2.5;//cm

//vertical layers
//for side MRD 
const double CVlayer2X = 2.5;//cm
const double CVlayer2Y = 1.0;//m
const double CVlayer2Z = 0.5;//cm
//for downstream MRD and upstream veto
const double CVlayer3X = 2.5;//cm
const double CVlayer3Y = 1.0;//m
const double CVlayer3Z = 0.5;//cm
//don`t use now
const double CVlayer4X = 2.5;//cm
const double CVlayer4Y = 0.75;//m
const double CVlayer4Z = 0.15;//cm
//for downstream veto around wagasci
const double CVlayer5X = 2.5;//cm
const double CVlayer5Y = 0.55;//m
const double CVlayer5Z = 0.5;//cm
//for hlayer in wagasci
const double CVlayer6X = 1.25;//cm
const double CVlayer6Y = 0.5;//m
const double CVlayer6Z = 0.15;//cm
//for side veto around wagasci
const double CVlayer7X = 2.5;//cm
const double CVlayer7Y = 0.55;//m
const double CVlayer7Z = 0.5;//cm
//for bottom veto around wagasci
const double CVlayer8X = 2.5;//cm
const double CVlayer8Y = 1.125;//m
const double CVlayer8Z = 0.5;//cm
//for bottom MRD
const double CVlayer9X = 2.5;//cm
const double CVlayer9Y = 0.5;//cm
const double CVlayer9Z = 1.5;//m


//B2 lattice added by nchikuma, 2014/3/3*******///////////////////
//for target water   //these three should be linked to parameters in Primarygenerator.cc
const double waterLenX = CTargetX*10;
const double waterLenY = CTargetY*10;
const double waterLenZ = CTargetZ*10;

//Bar for 3D lattice
const double sciSpace =   25;      //the following numbers are determined by "mm"
//const double plnSpace =   32;
const double plnSpace =   60;
//HBar length
const double subHBarX =    5; 
const double subHBarY =    3; 
const double subHBarZ =   15;          //we must take "HbarLenZ<subHBarZ*2"
//double HbarLenX = 1500-subHBarX; //we must take "HbarLenY<subHBarX"
const double HbarLenX = 1000-subHBarX; //we must take "HbarLenY<subHBarX" //2014/6/11
const double HbarLenY =    3;          //we must take "HbarLenZ<sciSpace"
//const double HbarLenZ = 24.5;        //we must take "HbarLenY<(plnSpace-HbarLenZ)/2"
const double HbarLenZ = 25.0;        //we must take "HbarLenY<(plnSpace-HbarLenZ)/2"
//VBar length
const double subVBarX =   subHBarY; 
const double subVBarY =   subHBarX; 
const double subVBarZ =   subHBarZ; 
const double VbarLenX =   HbarLenY;
const double VbarLenY =   HbarLenX;
const double VbarLenZ =   HbarLenZ;
//Bar for plane
const double HplnbarLenX = HbarLenX;
const double HplnbarLenY = HbarLenZ;
const double HplnbarLenZ = HbarLenY;
const double VplnbarLenX = VbarLenZ;
const double VplnbarLenY = VbarLenY;
const double VplnbarLenZ = VbarLenX;
//# of scintillator and plane   //these two should be linked to parameters in IngridH(V)LayerHit.cc
//const int latice_sciNum   = (int)( (HbarLenX+subHBarX)/sciSpace - 1);
const int latice_sciNum   = (int)( (HbarLenX+subHBarX)/(sciSpace*2) - 1);

//const int latice_plnNum     = 61;   //2014/6/11
const int latice_plnNum     = 32;   //Number of scintillator in one of the lattice
//const int plan2D_plnNum     = 40;   //Number of scintillator in one of the lattice
//1 for checking overlapes
const int check = 0;


const double firstdistance_mod5z = 15; //mm distance between water target and scintillator
const double firstdistance_mod5v = 25; //mm distance between water target and scintillator
const double firstdistance_mod5h = 25; //mm distance between water target and scintillator
const double spacedistance_mod5 = 1; //mm distance between scintillator and scintillator
////////////////////////////////////////////////////////////////

const double CVetoGap = 2.0;//cm
const double CMRDGap = 7.7;//cm
const double CUpstGap = 5.0;//cm

const int CVetoNum = 4;
const int CChmax_VetoVupst = 25;
const int CChmax_VetoHupst = 22;
const int CChmax_VetoVdown = 25;
const int CChmax_VetoHdown = 22;
const int CChmax_VetoVright = 42;
const int CChmax_VetoHright = 22;
const int CChmax_VetoVleft = 42;
const int CChmax_VetoHleft = 22;
const int CChmax_VetoVbottom = 25;
const int CChmax_VetoHbottom = 45;
const int CChmax_VetoVup = 25;
const int CChmax_VetoHup = 45;
//
const double CStartVetoupst_z = -113.;//cm
const double CStartVetoupst_v = -60.;//cm
const double CStartVetoupst_h = -52.5;//cm

const double CStartVetodown_z = 105.;//cm
const double CStartVetodown_v = -60.;//cm
const double CStartVetodown_h = -52.5;//cm

const double CStartVetoright_z = -55.;//cm
const double CStartVetoright_v = -102.5;//cm
const double CStartVetoright_h = -52.5;//cm

const double CStartVetoleft_z = 55.;//cm
const double CStartVetoleft_v = -102.5;//cm
const double CStartVetoleft_h = -52.5;//cm

const double CStartVetobottom_z = -57.5;//cm
const double CStartVetobottom_v = -60.0;//cm
const double CStartVetobottom_h = -110.0;//cm

const double CStartVetoup_z = 57.5;//cm
const double CStartVetoup_v = -60.0;//cm
const double CStartVetoup_h = -110.0;//cm


//for primary generator(cm)//////////////////////////////////////

const double B2OFF = 400.;

//for B2 place
//const double B2OFFZ 170.
//const double B2OFFX 572.4
//const double B2OFFY 444.4   
const double B2OFFZ = (CWagaposZ-1.0)*100;
const double B2OFFX = -CWagaposX*100;
const double B2OFFY = -CWagaposY*100;

//const double B2OFFYFLOOR =  594.4//2014/6/13
const double B2OFFYFLOOR = - CFloorup*100; //2014/6/13
const double B2FLOORDEPTH = 1000.0; //2014/6/13

const double B2PillarOFFZ = CPillarposZ*100;
const double B2PillarOFFX = -CPillarposX*100;
const double B2PillarOFFY = -CPillarposY*100; 

const double B2OFFZFE = 178.75; //2014/9/6 distance between center of target and upstream surface of downstream iron
const double B2OFFXFE = 118.75; //2014/7/28 

//////////////////////////////////////////////////////////////////


//positioning of MRDs
const double CStartmod1_iron_z = -( (CWagaboxforposZ*100 - CWagaboxposZ*100)  -B2OFFZFE); //cm
const double CStartmod1_sci_z = -( (CWagaboxforposZ*100 - CWagaboxposZ*100) - (B2OFFZFE-1.1-1.-1.) ); //cm
const double CStartmod1_sci_v = -200; //cm
const double CStartmod1_sci_h = -100; //cm

const double CStartmod2_iron_z = -( (CWagaboxsideposX*100 - CWagaboxposX*100)  -B2OFFXFE); //cm
const double CStartmod2_sci_z = -( (CWagaboxsideposX*100 - CWagaboxposX*100) - (B2OFFXFE-1.1-1.-1.) ); //cm
const double CStartmod2_sci_v = -160; //cm WIDTH!!!!
const double CStartmod2_sci_h = -100; //cm

const double CStartmod3_sci_z = -24.5; //cm
const double CStartmod3_sci_v = -200; //cm
const double CStartmod3_sci_h = -100; //cm

//const double CStartmod9_iron_z = -( (CWagaboxsideposX*100 - CWagaboxposX*100)  -B2OFFXFE); //cm
const double CStartmod9_sci_z = -16.0; //cm
const double CStartmod9_sci_v = -100; //cm
const double CStartmod9_sci_h = -150; //cm


#endif
