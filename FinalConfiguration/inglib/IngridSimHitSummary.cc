#include "IngridSimHitSummary.h"

//......................................................................

IngridSimHitSummary::IngridSimHitSummary() 
{ 
  
    edeposit = -1.e5;
    trackid  = -1;
    pdg      = -1;

}

//......................................................................

IngridSimHitSummary::~IngridSimHitSummary() 
{ 
}

//......................................................................

void IngridSimHitSummary::Clear(Option_t* option)
{
}

//......................................................................

void IngridSimHitSummary::Print(Option_t* option) const
{
  
}

//......................................................................

ClassImp(IngridSimHitSummary)

////////////////////////////////////////////////////////////////////////
