//
// File generated by rootcint at Fri Aug 12 05:13:56 2011

// Do NOT change. Changes will be lost next time file is generated
//

#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "BeamInfoSummaryDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void BeamInfoSummary_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void *new_BeamInfoSummary(void *p = 0);
   static void *newArray_BeamInfoSummary(Long_t size, void *p);
   static void delete_BeamInfoSummary(void *p);
   static void deleteArray_BeamInfoSummary(void *p);
   static void destruct_BeamInfoSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BeamInfoSummary*)
   {
      ::BeamInfoSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BeamInfoSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("BeamInfoSummary", ::BeamInfoSummary::Class_Version(), "BeamInfoSummary.h", 18,
                  typeid(::BeamInfoSummary), DefineBehavior(ptr, ptr),
                  &::BeamInfoSummary::Dictionary, isa_proxy, 0,
                  sizeof(::BeamInfoSummary) );
      instance.SetNew(&new_BeamInfoSummary);
      instance.SetNewArray(&newArray_BeamInfoSummary);
      instance.SetDelete(&delete_BeamInfoSummary);
      instance.SetDeleteArray(&deleteArray_BeamInfoSummary);
      instance.SetDestructor(&destruct_BeamInfoSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BeamInfoSummary*)
   {
      return GenerateInitInstanceLocal((::BeamInfoSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BeamInfoSummary*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *BeamInfoSummary::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *BeamInfoSummary::Class_Name()
{
   return "BeamInfoSummary";
}

//______________________________________________________________________________
const char *BeamInfoSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BeamInfoSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BeamInfoSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BeamInfoSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void BeamInfoSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BeamInfoSummary*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *BeamInfoSummary::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BeamInfoSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void BeamInfoSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class BeamInfoSummary.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> nurun;
      R__b >> spill_flag;
      R__b >> good_spill_flag;
      R__b >> trg_sec;
      R__b >> spillnum;
      R__b >> nd280spillnum;
      R__b >> run_type;
      R__b.ReadStaticArray((double*)target_eff);
      R__b.ReadStaticArray((double*)beam_time);
      R__b.ReadStaticArray((double*)ct_np);
      R__b.ReadStaticArray((double*)mumon);
      R__b.ReadStaticArray((double*)hct);
      R__b.ReadStaticArray((double*)otr);
      R__b >> wohorn;
      R__b >> horn1;
      R__b >> whorn;
      R__b >> cutwotr;
      R__b >> horn250;
      R__b.CheckByteCount(R__s, R__c, BeamInfoSummary::IsA());
   } else {
      R__c = R__b.WriteVersion(BeamInfoSummary::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << nurun;
      R__b << spill_flag;
      R__b << good_spill_flag;
      R__b << trg_sec;
      R__b << spillnum;
      R__b << nd280spillnum;
      R__b << run_type;
      R__b.WriteArray(target_eff, 3);
      R__b.WriteArray((double*)beam_time, 45);
      R__b.WriteArray((double*)ct_np, 45);
      R__b.WriteArray(mumon, 12);
      R__b.WriteArray((double*)hct, 15);
      R__b.WriteArray(otr, 13);
      R__b << wohorn;
      R__b << horn1;
      R__b << whorn;
      R__b << cutwotr;
      R__b << horn250;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

//______________________________________________________________________________
void BeamInfoSummary::ShowMembers(TMemberInspector &R__insp, char *R__parent)
{
      // Inspect the data members of an object of class BeamInfoSummary.
      TClass *R__cl = ::BeamInfoSummary::IsA();
      Int_t R__ncp = strlen(R__parent);
      if (R__ncp || R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__parent, "nurun", &nurun);
      R__insp.Inspect(R__cl, R__parent, "spill_flag", &spill_flag);
      R__insp.Inspect(R__cl, R__parent, "good_spill_flag", &good_spill_flag);
      R__insp.Inspect(R__cl, R__parent, "trg_sec", &trg_sec);
      R__insp.Inspect(R__cl, R__parent, "spillnum", &spillnum);
      R__insp.Inspect(R__cl, R__parent, "nd280spillnum", &nd280spillnum);
      R__insp.Inspect(R__cl, R__parent, "run_type", &run_type);
      R__insp.Inspect(R__cl, R__parent, "target_eff[3]", target_eff);
      R__insp.Inspect(R__cl, R__parent, "beam_time[5][9]", beam_time);
      R__insp.Inspect(R__cl, R__parent, "ct_np[5][9]", ct_np);
      R__insp.Inspect(R__cl, R__parent, "mumon[12]", mumon);
      R__insp.Inspect(R__cl, R__parent, "hct[3][5]", hct);
      R__insp.Inspect(R__cl, R__parent, "otr[13]", otr);
      R__insp.Inspect(R__cl, R__parent, "wohorn", &wohorn);
      R__insp.Inspect(R__cl, R__parent, "horn1", &horn1);
      R__insp.Inspect(R__cl, R__parent, "whorn", &whorn);
      R__insp.Inspect(R__cl, R__parent, "cutwotr", &cutwotr);
      R__insp.Inspect(R__cl, R__parent, "horn250", &horn250);
      TObject::ShowMembers(R__insp, R__parent);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BeamInfoSummary(void *p) {
      return  p ? new(p) ::BeamInfoSummary : new ::BeamInfoSummary;
   }
   static void *newArray_BeamInfoSummary(Long_t nElements, void *p) {
      return p ? new(p) ::BeamInfoSummary[nElements] : new ::BeamInfoSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_BeamInfoSummary(void *p) {
      delete ((::BeamInfoSummary*)p);
   }
   static void deleteArray_BeamInfoSummary(void *p) {
      delete [] ((::BeamInfoSummary*)p);
   }
   static void destruct_BeamInfoSummary(void *p) {
      typedef ::BeamInfoSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BeamInfoSummary

/********************************************************
* BeamInfoSummaryDict.cc
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && (__GNUC__ > 3) && (__GNUC_MINOR__ > 1)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableBeamInfoSummaryDict();

extern "C" void G__set_cpp_environmentBeamInfoSummaryDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("BeamInfoSummary.h");
  G__cpp_reset_tagtableBeamInfoSummaryDict();
}
#include <new>
extern "C" int G__cpp_dllrevBeamInfoSummaryDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* BeamInfoSummary */
static int G__BeamInfoSummaryDict_173_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BeamInfoSummary* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new BeamInfoSummary[n];
     } else {
       p = new((void*) gvp) BeamInfoSummary[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new BeamInfoSummary;
     } else {
       p = new((void*) gvp) BeamInfoSummary;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BeamInfoSummary* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new BeamInfoSummary(*(BeamInfoSummary*) libp->para[0].ref);
   } else {
     p = new((void*) gvp) BeamInfoSummary(*(BeamInfoSummary*) libp->para[0].ref);
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) BeamInfoSummary::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) BeamInfoSummary::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) BeamInfoSummary::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      BeamInfoSummary::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BeamInfoSummary*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) BeamInfoSummary::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) BeamInfoSummary::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) BeamInfoSummary::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BeamInfoSummaryDict_173_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) BeamInfoSummary::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef BeamInfoSummary G__TBeamInfoSummary;
static int G__BeamInfoSummaryDict_173_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (BeamInfoSummary*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((BeamInfoSummary*) (soff+(sizeof(BeamInfoSummary)*i)))->~G__TBeamInfoSummary();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (BeamInfoSummary*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((BeamInfoSummary*) (soff))->~G__TBeamInfoSummary();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__BeamInfoSummaryDict_173_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BeamInfoSummary* dest = (BeamInfoSummary*) G__getstructoffset();
   *dest = *(BeamInfoSummary*) libp->para[0].ref;
   const BeamInfoSummary& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* BeamInfoSummary */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncBeamInfoSummaryDict {
 public:
  G__Sizep2memfuncBeamInfoSummaryDict(): p(&G__Sizep2memfuncBeamInfoSummaryDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncBeamInfoSummaryDict::*p)();
};

size_t G__get_sizep2memfuncBeamInfoSummaryDict()
{
  G__Sizep2memfuncBeamInfoSummaryDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceBeamInfoSummaryDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary))) {
     BeamInfoSummary *G__Lderived;
     G__Lderived=(BeamInfoSummary*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary),G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableBeamInfoSummaryDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<TSchemaHelper>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* BeamInfoSummary */
static void G__setup_memvarBeamInfoSummary(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary));
   { BeamInfoSummary *p; p=(BeamInfoSummary*)0x1000; if (p) { }
   G__memvar_setup((void*)((long)(&p->nurun)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"nurun=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->spill_flag)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"spill_flag=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->good_spill_flag)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"good_spill_flag=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->trg_sec)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"trg_sec=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->spillnum)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"spillnum=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->nd280spillnum)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"nd280spillnum=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->run_type)-(long)(p)),105,0,0,-1,G__defined_typename("Int_t"),-1,1,"run_type=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->target_eff)-(long)(p)),100,0,0,-1,G__defined_typename("Double_t"),-1,1,"target_eff[3]=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->beam_time)-(long)(p)),100,0,0,-1,G__defined_typename("Double_t"),-1,1,"beam_time[5][9]=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->ct_np)-(long)(p)),100,0,0,-1,G__defined_typename("Double_t"),-1,1,"ct_np[5][9]=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->mumon)-(long)(p)),100,0,0,-1,G__defined_typename("Double_t"),-1,1,"mumon[12]=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->hct)-(long)(p)),100,0,0,-1,G__defined_typename("Double_t"),-1,1,"hct[3][5]=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->otr)-(long)(p)),100,0,0,-1,G__defined_typename("Double_t"),-1,1,"otr[13]=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->wohorn)-(long)(p)),103,0,0,-1,-1,-1,1,"wohorn=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->horn1)-(long)(p)),103,0,0,-1,-1,-1,1,"horn1=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->whorn)-(long)(p)),103,0,0,-1,-1,-1,1,"whorn=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->cutwotr)-(long)(p)),103,0,0,-1,-1,-1,1,"cutwotr=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->horn250)-(long)(p)),103,0,0,-1,-1,-1,1,"horn250=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarBeamInfoSummaryDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncBeamInfoSummary(void) {
   /* BeamInfoSummary */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary));
   G__memfunc_setup("BeamInfoSummary",1519,G__BeamInfoSummaryDict_173_0_1, 105, G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("BeamInfoSummary",1519,G__BeamInfoSummaryDict_173_0_2, 105, G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary), -1, 0, 1, 1, 1, 0, "u 'BeamInfoSummary' - 11 - info", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "C - 'Option_t' 10 '\"\"' option", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Print",525,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 8, "C - 'Option_t' 10 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Class",502,G__BeamInfoSummaryDict_173_0_5, 85, G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) (TClass* (*)())(&BeamInfoSummary::Class), 0);
   G__memfunc_setup("Class_Name",982,G__BeamInfoSummaryDict_173_0_6, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) (const char* (*)())(&BeamInfoSummary::Class_Name), 0);
   G__memfunc_setup("Class_Version",1339,G__BeamInfoSummaryDict_173_0_7, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) (Version_t (*)())(&BeamInfoSummary::Class_Version), 0);
   G__memfunc_setup("Dictionary",1046,G__BeamInfoSummaryDict_173_0_8, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) (void (*)())(&BeamInfoSummary::Dictionary), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 2, 1, 1, 0, 
"u 'TMemberInspector' - 1 - insp C - - 0 - parent", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__BeamInfoSummaryDict_173_0_12, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__BeamInfoSummaryDict_173_0_13, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) (const char* (*)())(&BeamInfoSummary::DeclFileName), 0);
   G__memfunc_setup("ImplFileLine",1178,G__BeamInfoSummaryDict_173_0_14, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) (int (*)())(&BeamInfoSummary::ImplFileLine), 0);
   G__memfunc_setup("ImplFileName",1171,G__BeamInfoSummaryDict_173_0_15, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) (const char* (*)())(&BeamInfoSummary::ImplFileName), 0);
   G__memfunc_setup("DeclFileLine",1152,G__BeamInfoSummaryDict_173_0_16, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) (int (*)())(&BeamInfoSummary::DeclFileLine), 0);
   // automatic destructor
   G__memfunc_setup("~BeamInfoSummary", 1645, G__BeamInfoSummaryDict_173_0_17, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__BeamInfoSummaryDict_173_0_18, (int) ('u'), G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary), -1, 1, 1, 1, 1, 0, "u 'BeamInfoSummary' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncBeamInfoSummaryDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalBeamInfoSummaryDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcBeamInfoSummaryDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__BeamInfoSummaryDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__BeamInfoSummaryDictLN_BeamInfoSummary = { "BeamInfoSummary" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableBeamInfoSummaryDict() {
  G__BeamInfoSummaryDictLN_TClass.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_TBuffer.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_TMemberInspector.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_TObject.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__BeamInfoSummaryDictLN_BeamInfoSummary.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableBeamInfoSummaryDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BeamInfoSummaryDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__tagtable_setup(G__get_linked_tagnum(&G__BeamInfoSummaryDictLN_BeamInfoSummary),sizeof(BeamInfoSummary),-1,30464,"Beam Info Summary",G__setup_memvarBeamInfoSummary,G__setup_memfuncBeamInfoSummary);
}
extern "C" void G__cpp_setupBeamInfoSummaryDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupBeamInfoSummaryDict()");
  G__set_cpp_environmentBeamInfoSummaryDict();
  G__cpp_setup_tagtableBeamInfoSummaryDict();

  G__cpp_setup_inheritanceBeamInfoSummaryDict();

  G__cpp_setup_typetableBeamInfoSummaryDict();

  G__cpp_setup_memvarBeamInfoSummaryDict();

  G__cpp_setup_memfuncBeamInfoSummaryDict();
  G__cpp_setup_globalBeamInfoSummaryDict();
  G__cpp_setup_funcBeamInfoSummaryDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncBeamInfoSummaryDict();
  return;
}
class G__cpp_setup_initBeamInfoSummaryDict {
  public:
    G__cpp_setup_initBeamInfoSummaryDict() { G__add_setup_func("BeamInfoSummaryDict",(G__incsetup)(&G__cpp_setupBeamInfoSummaryDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initBeamInfoSummaryDict() { G__remove_setup_func("BeamInfoSummaryDict"); }
};
G__cpp_setup_initBeamInfoSummaryDict G__cpp_setup_initializerBeamInfoSummaryDict;

