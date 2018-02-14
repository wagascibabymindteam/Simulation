#!/bin/sh
MYROOTLIB=$ROOTSYS/lib/root
MYROOTINC=$ROOTSYS/include/root/

cp -f ./INGRIDEVENTSUMMARY.so        $MYROOTLIB/libINGRIDEVENTSUMMARY.so
cp -f ./IngridHitSummary.so        $MYROOTLIB/libIngridHitSummary.so
cp -f ./IngridSimHitSummary.so     $MYROOTLIB/libIngridSimHitSummary.so
cp -f ./IngridSimVertexSummary.so     $MYROOTLIB/libIngridSimVertexSummary.so
cp -f ./IngridSimParticleSummary.so     $MYROOTLIB/libIngridSimParticleSummary.so
cp -f ./BeamInfoSummary.so     $MYROOTLIB/libBeamInfoSummary.so
cp -f ./IngridBasicReconSummary.so     $MYROOTLIB/libIngridBasicReconSummary.so
cp -f ./Ingrid1stReducSummary.so     $MYROOTLIB/libIngrid1stReducSummary.so
cp -f ./IngridTrackSummary.so	$MYROOTLIB/libIngridTrackSummary.so
cp -f ./IngridBasicReconSummary.so	$MYROOTLIB/libIngridBasicReconSummary.so
cp -f ./NeutInfoSummary.so	$MYROOTLIB/libNeutInfoSummary.so

cp -f ./INGRIDEVENTSUMMARY.h        $MYROOTINC/INGRIDEVENTSUMMARY.h
cp -f ./IngridHitSummary.h        $MYROOTINC/IngridHitSummary.h
cp -f ./IngridSimHitSummary.h     $MYROOTINC/IngridSimHitSummary.h
cp -f ./IngridSimVertexSummary.h     $MYROOTINC/IngridSimVertexSummary.h
cp -f ./IngridSimParticleSummary.h     $MYROOTINC/IngridSimParticleSummary.h
cp -f ./BeamInfoSummary.h     $MYROOTINC/BeamInfoSummary.h
cp -f ./IngridBasicReconSummary.h     $MYROOTINC/IngridBasicReconSummary.h
cp -f ./Ingrid1stReducSummary.h     $MYROOTINC/Ingrid1stReducSummary.h
cp -f ./IngridTrackSummary.h     $MYROOTINC/IngridTrackSummary.h
cp -f ./IngridBasicReconSummary.h     $MYROOTINC/IngridBasicReconSummary.h
cp -f ./NeutInfoSummary.h     $MYROOTINC/NeutInfoSummary.h
