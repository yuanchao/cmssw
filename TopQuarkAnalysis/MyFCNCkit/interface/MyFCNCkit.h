// -*- C++ -*-
//
// Package:    MyFCNCkit
// Class:      MyFCNCkit
// 
/**\class MyFCNCkit MyFCNCkit.cc TopQuarkAnalysis/MyFCNCkit/src/MyFCNCkit.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Chao Yuan,27 2-020 (CERN) Mailbox F10500,+41 22 76 74870,+41 22 76 74870
//         Created:  Wed Oct  5 22:39:27 UTC 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#define MAX_LEPTONS     256
#define MAX_JETS        128
#define MAX_GENPARTS    512
#define MAX_BX          128
#define MAX_VERTEX      256 

//#define N_TRIGGER_BOOKINGS      5929

#include "TopQuarkAnalysis/MyFCNCkit/interface/TriggerBooking.h"


//
// class declaration
//

class EvtInfoClass{
public:
  int   RunNo;
  int   EvtNo;
  int   BxNo;
  int   LumiNo;
  int   Orbit;
  int   McFlag;

  float RhoPU;       
  float SigmaPU;     
  
  int   PDFid1;
  int   PDFid2;
  float PDFx1;
  float PDFx2;
  float PDFscale;
  float PDFv1;
  float PDFv2;
  float MET;
  float METPhi;
  float RawMET;
  float RawMETPhi;
  float SumEt;
  float METSig;
  float eLong;
  float MaxHadTower;
  float MaxEmTower;
  float FracHad;
  float FracEm;
  float GenMET;
  float GenMETPhi;
  float Weight;

  // PU
  int nBX;
  int nPU[MAX_BX];
  int nTPU[MAX_BX];
  int BXPU[MAX_BX];

  float METx;
  float METy;

  float rhoIso;

  int   TrgCount;   // No. of fired booking bits
  char  TrgBook[N_TRIGGER_BOOKINGS];// Trigger bits, reserved up to 120 entries
  int   nHLT;
  int   nBooking;
  bool  HLTbits[N_TRIGGER_BOOKINGS];
  int L1[128]; // L1 trigger bits
  int TT[64];       // Techical trigger bits
  float HighPurityFraction; //Added by Dmitry to help filter out bad events
  int NofTracks; //Added by Dmitry to help filter out bad events

  void setBranch(TTree *root){
    root->Branch("EvtInfo.RunNo"       , &RunNo           , "EvtInfo.RunNo/I"          );
    root->Branch("EvtInfo.EvtNo"       , &EvtNo           , "EvtInfo.EvtNo/I"          );
    root->Branch("EvtInfo.BxNo"        , &BxNo                , "EvtInfo.BxNo/I"       );
    root->Branch("EvtInfo.LumiNo"      , &LumiNo          , "EvtInfo.LumiNo/I"         );
    root->Branch("EvtInfo.Orbit"       , &Orbit           , "EvtInfo.Orbit/I"          );
    root->Branch("EvtInfo.McFlag"      , &McFlag          , "EvtInfo.McFlag/I"         );
    root->Branch("EvtInfo.PDFid1"      , &PDFid1          , "EvtInfo.PDFid1/I"         );
    root->Branch("EvtInfo.PDFid2"      , &PDFid2          , "EvtInfo.PDFid2/I"         );
    root->Branch("EvtInfo.PDFx1"       , &PDFx1           , "EvtInfo.PDFx1/F"          );
    root->Branch("EvtInfo.RhoPU"       , &RhoPU           , "EvtInfo.RhoPU/F"          );
    root->Branch("EvtInfo.SigmaPU"     , &SigmaPU         , "EvtInfo.SigmaPU/F"        );
    root->Branch("EvtInfo.PDFx2"       , &PDFx2           , "EvtInfo.PDFx2/F"          );
    root->Branch("EvtInfo.PDFscale"    , &PDFscale        , "EvtInfo.PDFscale/F"       );
    root->Branch("EvtInfo.PDFv1"       , &PDFv1           , "EvtInfo.PDFv1/F"          );
    root->Branch("EvtInfo.PDFv2"       , &PDFv2           , "EvtInfo.PDFv2/F"          );           
    root->Branch("EvtInfo.MET"         , &MET             , "EvtInfo.MET/F"            );
    root->Branch("EvtInfo.METx"        , &METx            , "EvtInfo.METx/F"            );
    root->Branch("EvtInfo.METy"        , &METy            , "EvtInfo.METy/F"            );
    root->Branch("EvtInfo.METPhi"      , &METPhi          , "EvtInfo.METPhi/F"         );
    root->Branch("EvtInfo.RawMET"      , &RawMET          , "EvtInfo.RawMET/F"         );
    root->Branch("EvtInfo.RawMETPhi"   , &RawMETPhi       , "EvtInfo.RawMETPhi/F"      );
    root->Branch("EvtInfo.SumEt"       , &SumEt           , "EvtInfo.SumEt/F"          );
    root->Branch("EvtInfo.METSig"      , &METSig          , "EvtInfo.METSig/F"         );
    root->Branch("EvtInfo.GenMET"      , &GenMET          , "EvtInfo.GenMET/F"         );
    root->Branch("EvtInfo.GenMETPhi"   , &GenMETPhi       , "EvtInfo.GenMETPhi/F"      );
    root->Branch("EvtInfo.Weight"      , &Weight          , "EvtInfo.Weight/F"      );
    root->Branch("EvtInfo.TrgCount"    , &TrgCount        , "EvtInfo.TrgCount/I"      );
    root->Branch("EvtInfo.nBooking"    , &nBooking             , "EvtInfo.nBooking/I");
    root->Branch("EvtInfo.TrgBook"     , TrgBook         , "EvtInfo.TrgBook[EvtInfo.nBooking]/B");
    root->Branch("EvtInfo.NofTracks"   , &NofTracks       , "EvtInfo.NofTracks/I"      );
    root->Branch("EvtInfo.nHLT"        , &nHLT                 , "EvtInfo.nHLT/I");
    root->Branch("EvtInfo.HLTbits"     , HLTbits               , "EvtInfo.HLTbits[EvtInfo.nHLT]/O");
    root->Branch("EvtInfo.nBX"         , &nBX                  , "EvtInfo.nBX/I");
    root->Branch("EvtInfo.nPU"         , nPU               , "EvtInfo.nPU[EvtInfo.nBX]/I");
    root->Branch("EvtInfo.nTPU"        , nTPU              , "EvtInfo.nTPU[EvtInfo.nBX]/I");
    root->Branch("EvtInfo.BXPU"        , BXPU              , "EvtInfo.BXPU[EvtInfo.nBX]/I");
    root->Branch("EvtInfo.rhoIso"      , &rhoIso           , "EvtInfo.rhoIso/F");
  }
    
};

class LeptonClass{
public:
  int       Size; 
  int       Index[MAX_LEPTONS];
  int       isEcalDriven[MAX_LEPTONS];
  int       isTrackerDriven[MAX_LEPTONS];
  int       Type[MAX_LEPTONS];
  int       Charge[MAX_LEPTONS];

  float Pt[MAX_LEPTONS];
  float Et[MAX_LEPTONS];
  float Eta[MAX_LEPTONS];
  float caloEta[MAX_LEPTONS];
  float Phi[MAX_LEPTONS];
  float TrackIso[MAX_LEPTONS];
  float EcalIso[MAX_LEPTONS];
  float HcalIso[MAX_LEPTONS];
  float HcalDepth1Iso[MAX_LEPTONS];
  float HcalDepth2Iso[MAX_LEPTONS];
  float chargedIso[MAX_LEPTONS];
  float neutralIso[MAX_LEPTONS];
  float photonIso[MAX_LEPTONS];
  float puChIso[MAX_LEPTONS];
  float chAllIso[MAX_LEPTONS];
  float AllIso[MAX_LEPTONS];
  float AEff03[MAX_LEPTONS];
  float ChargedHadronIsoR04[MAX_LEPTONS]; 
  float NeutralHadronIsoR04[MAX_LEPTONS]; 
  float PhotonIsoR04[MAX_LEPTONS];        
  float sumPUPtR04[MAX_LEPTONS];          
  float CaloEnergy[MAX_LEPTONS];
  float e1x5[MAX_LEPTONS];
  float e2x5Max[MAX_LEPTONS];
  float e5x5[MAX_LEPTONS];

  float Px[MAX_LEPTONS]; //Uly 2011-04-04
  float Py[MAX_LEPTONS]; //Uly 2011-04-04
  float Pz[MAX_LEPTONS]; //Uly 2011-04-04
  float Energy[MAX_LEPTONS]; //Uly 2011-04-04
  
  float vertexZ[MAX_LEPTONS]; //Uly 2011-04-04

  float ElTrackD0[MAX_LEPTONS];  
  float ElTrackDxy_BS[MAX_LEPTONS];  
  float ElTrackDxy_PV[MAX_LEPTONS];  
  float ElTrackDxy_PVBS[MAX_LEPTONS]; //yjlei

/*  
  float simpleEleId95relIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId90relIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId85relIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId80relIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId70relIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId60relIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId95cIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId90cIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId85cIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId80cIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId70cIso[MAX_LEPTONS]; // Add by Jacky
  float simpleEleId60cIso[MAX_LEPTONS]; // Add by Jacky
*/
/*
  // CIC without ISO
  int eidVeryLoose[MAX_LEPTONS];
  int eidLoose[MAX_LEPTONS];
  int eidMedium[MAX_LEPTONS];
  int eidTight[MAX_LEPTONS];
  int eidSuperTight[MAX_LEPTONS];
  int eidHyperTight1[MAX_LEPTONS];
  int eidHyperTight2[MAX_LEPTONS];
  int eidHyperTight3[MAX_LEPTONS];
  int eidHyperTight4[MAX_LEPTONS];
*/
  // CIC with ISO

  int eidVeryLooseMC[MAX_LEPTONS];
  int eidLooseMC[MAX_LEPTONS];
  int eidMediumMC[MAX_LEPTONS];
  int eidTightMC[MAX_LEPTONS];
  int eidSuperTightMC[MAX_LEPTONS];
  int eidHyperTight1MC[MAX_LEPTONS];
  int eidHyperTight2MC[MAX_LEPTONS];
  int eidHyperTight3MC[MAX_LEPTONS];
  int eidHyperTight4MC[MAX_LEPTONS];

  
  // For CIC        
  float dcotdist[MAX_LEPTONS];
  float ElseedEoverP[MAX_LEPTONS];
  float ElEcalIso04[MAX_LEPTONS];
  float ElHcalIso04[MAX_LEPTONS];

  float GenPt[MAX_LEPTONS];
  float GenEta[MAX_LEPTONS];
  float GenPhi[MAX_LEPTONS];
  int GenPdgID[MAX_LEPTONS];
  int GenMCTag[MAX_LEPTONS];  // 0: unknown, 1: decay from W, 2: decay from Z, 
  // 3: from b, 4: from c, 5: match to a parton (q or g), 6: match to a photon
  // (+10) from b'
  // (+20) from t'

  float MuInnerTrackDz[MAX_LEPTONS];  
  float MuInnerTrackD0[MAX_LEPTONS];  
  float MuInnerTrackDxy_BS[MAX_LEPTONS];  
  float MuInnerTrackDxy_PV[MAX_LEPTONS];  
  float MuInnerTrackDxy_PVBS[MAX_LEPTONS];  
  int   MuInnerTrackNHits[MAX_LEPTONS];
  int   MuNTrackerHits[MAX_LEPTONS];

  float MuGlobalNormalizedChi2[MAX_LEPTONS]; // Dmitry
  bool  MuIDGlobalMuonPromptTight[MAX_LEPTONS];

  int   MuNChambers[MAX_LEPTONS];
  int   MuNChambersMatchesSegment[MAX_LEPTONS];
  int   MuNPixelLayers[MAX_LEPTONS];
  int   MuNPixelLayersWMeasurement[MAX_LEPTONS]; //Uly 2011-04-04
  int   MuNLostInnerHits[MAX_LEPTONS];
  int   MuNLostOuterHits[MAX_LEPTONS];

  int   MuNMuonhits[MAX_LEPTONS];
  int   MuType[MAX_LEPTONS];
  
  float TrgPt[MAX_LEPTONS];
  float TrgEta[MAX_LEPTONS];
  float TrgPhi[MAX_LEPTONS];
  int TrgID[MAX_LEPTONS];

//YH 2012-08-15
  // Electrons
  bool ElepassConversionVeto[MAX_LEPTONS];
  float ElesuperClusterEta[MAX_LEPTONS];
  float ElemvaTrigV0[MAX_LEPTONS];
  float ElemvaNTrigV0[MAX_LEPTONS];
  float EletrackMomentumAtVtxp[MAX_LEPTONS];
  float EleecalEnergy[MAX_LEPTONS];
  float EleeSuperClusterOverP[MAX_LEPTONS];
  float Elefbrem[MAX_LEPTONS];
  float EleHoverE[MAX_LEPTONS];
  float ElesigmaIetaIeta[MAX_LEPTONS];
  float EledeltaPhiVtx[MAX_LEPTONS];
  float EledeltaEtaVtx[MAX_LEPTONS];
  int EleExpnumberOfHits[MAX_LEPTONS];
  //Muons
  int MuTrackerLayersWithMeasurement[MAX_LEPTONS];
  int MunumberOfMatchedStations[MAX_LEPTONS];

  void setBranch(TTree *root){
    root->Branch("Leptons.Size"               , &Size                     , "Leptons.Size/I");
    root->Branch("Leptons.Index"              , Index                     , "Leptons.Index[Leptons.Size]/I");
    root->Branch("Leptons.isEcalDriven"       , isEcalDriven              , "Leptons.isEcalDriven[Leptons.Size]/I");
    root->Branch("Leptons.isTrackerDriven"    , isTrackerDriven           , "Leptons.isTrackerDriven[Leptons.Size]/I");
    root->Branch("Leptons.Type"               , Type                      , "Leptons.Type[Leptons.Size]/I");
    root->Branch("Leptons.Charge"             , Charge                    , "Leptons.Charge[Leptons.Size]/I");

    root->Branch("Leptons.Pt"                 , Pt                        , "Leptons.Pt[Leptons.Size]/F");
    root->Branch("Leptons.Et"                 , Et                        , "Leptons.Et[Leptons.Size]/F");
    root->Branch("Leptons.Eta"                , Eta                       , "Leptons.Eta[Leptons.Size]/F");
    root->Branch("Leptons.caloEta"            , caloEta                   , "Leptons.caloEta[Leptons.Size]/F");
    root->Branch("Leptons.Phi"                , Phi                       , "Leptons.Phi[Leptons.Size]/F");
    root->Branch("Leptons.TrackIso"           , TrackIso                  , "Leptons.TrackIso[Leptons.Size]/F");
    root->Branch("Leptons.EcalIso"            , EcalIso                   , "Leptons.EcalIso[Leptons.Size]/F");
    root->Branch("Leptons.HcalIso"            , HcalIso                   , "Leptons.HcalIso[Leptons.Size]/F");
    root->Branch("Leptons.HcalDepth1Iso"      , HcalDepth1Iso             , "Leptons.HcalDepth1Iso[Leptons.Size]/F");
    root->Branch("Leptons.HcalDepth2Iso"      , HcalDepth2Iso             , "Leptons.HcalDepth2Iso[Leptons.Size]/F");
    root->Branch("Leptons.CaloEnergy"         , CaloEnergy                , "Leptons.CaloEnergy[Leptons.Size]/F");
    root->Branch("Leptons.e1x5"               , e1x5                      , "Leptons.e1x5[Leptons.Size]/F");
    root->Branch("Leptons.e2x5Max"            , e2x5Max                   , "Leptons.e2x5Max[Leptons.Size]/F");
    root->Branch("Leptons.e5x5"               , e5x5                      , "Leptons.e5x5[Leptons.Size]/F");
    root->Branch("Leptons.chargedIso"         , chargedIso                , "Leptons.chargedIso[Leptons.Size]/F");
    root->Branch("Leptons.neutralIso"         , neutralIso                , "Leptons.neutralIso[Leptons.Size]/F");
    root->Branch("Leptons.photonIso"          , photonIso                 , "Leptons.photonIso[Leptons.Size]/F");
    root->Branch("Leptons.puChIso"            , puChIso                   , "Leptons.puChIso[Leptons.Size]/F");
    root->Branch("Leptons.chAllIso"           , chAllIso                  , "Leptons.chAllIso[Leptons.Size]/F");
    root->Branch("Leptons.AllIso"             , AllIso                    , "Leptons.AllIso[Leptons.Size]/F");
    root->Branch("Leptons.AEff03"             , AEff03                    , "Leptons.AEff03[Leptons.Size]/F");
    root->Branch("Leptons.ChargedHadronIsoR04", ChargedHadronIsoR04       , "Leptons.ChargedHadronIsoR04[Leptons.Size]/F");
    root->Branch("Leptons.NeutralHadronIsoR04", NeutralHadronIsoR04       , "Leptons.NeutralHadronIsoR04[Leptons.Size]/F");
    root->Branch("Leptons.PhotonIsoR04"       , PhotonIsoR04              , "Leptons.PhotonIsoR04[Leptons.Size]/F");
    root->Branch("Leptons.sumPUPtR04"         , sumPUPtR04                , "Leptons.sumPUPtR04[Leptons.Size]/F");

    root->Branch("Leptons.Px"                 , Px                     , "Leptons.Px[Leptons.Size]/F"); //Uly 2011-04-04
    root->Branch("Leptons.Py"                 , Py                     , "Leptons.Py[Leptons.Size]/F"); //Uly 2011-04-04
    root->Branch("Leptons.Pz"                 , Pz                     , "Leptons.Pz[Leptons.Size]/F"); //Uly 2011-04-04

    root->Branch("Leptons.Energy"           , Energy              , "Leptons.Energy[Leptons.Size]/F"); //Uly 2011-04-04
    root->Branch("Leptons.vertexZ"          , vertexZ             , "Leptons.vertexZ[Leptons.Size]/F"); //Uly 2011-04-04

    root->Branch("Leptons.ElTrackD0"    ,   ElTrackD0      , "Leptons.ElTrackD0[Leptons.Size]/F");
    root->Branch("Leptons.ElTrackDxy_BS",   ElTrackDxy_BS  , "Leptons.ElTrackDxy_BS[Leptons.Size]/F");
    root->Branch("Leptons.ElTrackDxy_PV",   ElTrackDxy_PV  , "Leptons.ElTrackDxy_PV[Leptons.Size]/F");
    root->Branch("Leptons.ElTrackDxy_PVBS", ElTrackDxy_PVBS, "Leptons.ElTrackDxy_PVBS[Leptons.Size]/F");

/*
    root->Branch("Leptons.simpleEleId95relIso"    , simpleEleId95relIso , "Leptons.simpleEleId95relIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId90relIso"    , simpleEleId90relIso , "Leptons.simpleEleId90relIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId85relIso"    , simpleEleId85relIso , "Leptons.simpleEleId85relIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId80relIso"    , simpleEleId80relIso , "Leptons.simpleEleId80relIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId70relIso"    , simpleEleId70relIso , "Leptons.simpleEleId70relIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId60relIso"    , simpleEleId60relIso , "Leptons.simpleEleId60relIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId95cIso"    , simpleEleId95cIso , "Leptons.simpleEleId95cIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId90cIso"    , simpleEleId90cIso , "Leptons.simpleEleId90cIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId85cIso"    , simpleEleId85cIso , "Leptons.simpleEleId85cIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId80cIso"    , simpleEleId80cIso , "Leptons.simpleEleId80cIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId70cIso"    , simpleEleId70cIso , "Leptons.simpleEleId70cIso[Leptons.Size]/F");
    root->Branch("Leptons.simpleEleId60cIso"    , simpleEleId60cIso , "Leptons.simpleEleId60cIso[Leptons.Size]/F");
    
    root->Branch("Leptons.eidVeryLoose", eidVeryLoose        , "Leptons.eidVeryLoose[Leptons.Size]/I");
    root->Branch("Leptons.eidLoose", eidLoose                , "Leptons.eidLoose[Leptons.Size]/I");
    root->Branch("Leptons.eidMedium", eidMedium              , "Leptons.eidMedium[Leptons.Size]/I");
    root->Branch("Leptons.eidTight", eidTight                , "Leptons.eidTight[Leptons.Size]/I");
    root->Branch("Leptons.eidSuperTight", eidSuperTight      , "Leptons.eidSuperTight[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight1", eidHyperTight1    , "Leptons.eidHyperTight1[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight2", eidHyperTight2    , "Leptons.eidHyperTight2[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight3", eidHyperTight3    , "Leptons.eidHyperTight3[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight4", eidHyperTight4    , "Leptons.eidHyperTight4[Leptons.Size]/I");
*/    
    root->Branch("Leptons.eidVeryLooseMC", eidVeryLooseMC    , "Leptons.eidVeryLooseMC[Leptons.Size]/I");
    root->Branch("Leptons.eidLooseMC", eidLooseMC            , "Leptons.eidLooseMC[Leptons.Size]/I");
    root->Branch("Leptons.eidMediumMC", eidMediumMC          , "Leptons.eidMediumMC[Leptons.Size]/I");
    root->Branch("Leptons.eidTightMC", eidTightMC            , "Leptons.eidTightMC[Leptons.Size]/I");
    root->Branch("Leptons.eidSuperTightMC", eidSuperTightMC     , "Leptons.eidSuperTightMC[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight1MC", eidHyperTight1MC   , "Leptons.eidHyperTight1MC[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight2MC", eidHyperTight2MC   , "Leptons.eidHyperTight2MC[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight3MC", eidHyperTight3MC   , "Leptons.eidHyperTight3MC[Leptons.Size]/I");
    root->Branch("Leptons.eidHyperTight4MC", eidHyperTight4MC   , "Leptons.eidHyperTight4MC[Leptons.Size]/I");

    root->Branch("Leptons.dcotdist", dcotdist, "Leptons.dcotdist[Leptons.Size]/F");
    root->Branch("Leptons.ElseedEoverP", ElseedEoverP, "Leptons.ElseedEoverP[Leptons.Size]/F");
    root->Branch("Leptons.ElEcalIso04", ElEcalIso04, "Leptons.ElEcalIso04[Leptons.Size]/F");
    root->Branch("Leptons.ElHcalIso04", ElHcalIso04, "Leptons.ElHcalIso04[Leptons.Size]/F");

    root->Branch("Leptons.MuInnerTrackDz"      , MuInnerTrackDz      , "Leptons.MuInnerTrackDz[Leptons.Size]/F");
    root->Branch("Leptons.MuInnerTrackD0"      , MuInnerTrackD0      , "Leptons.MuInnerTrackD0[Leptons.Size]/F");
    root->Branch("Leptons.MuInnerTrackDxy_BS"  , MuInnerTrackDxy_BS  , "Leptons.MuInnerTrackDxy_BS[Leptons.Size]/F");
    root->Branch("Leptons.MuInnerTrackDxy_PV"  , MuInnerTrackDxy_PV  , "Leptons.MuInnerTrackDxy_PV[Leptons.Size]/F");
    root->Branch("Leptons.MuInnerTrackDxy_PVBS", MuInnerTrackDxy_PVBS, "Leptons.MuInnerTrackDxy_PVBS[Leptons.Size]/F");
    root->Branch("Leptons.MuInnerTrackNHits"   , MuInnerTrackNHits   , "Leptons.MuInnerTrackNHits[Leptons.Size]/I");      
    
    root->Branch("Leptons.MuIDGlobalMuonPromptTight", MuIDGlobalMuonPromptTight , "Leptons.MuIDGlobalMuonPromptTight[Leptons.Size]/O");  // Add by Jacky
    root->Branch("Leptons.MuGlobalNormalizedChi2"   , MuGlobalNormalizedChi2   , "Leptons.MuGlobalNormalizedChi2[Leptons.Size]/F"    ); //Dmitry
    root->Branch("Leptons.MuNChambers"              , MuNChambers              , "Leptons.MuNChambers[Leptons.Size]/I"               );
    root->Branch("Leptons.MuNChambersMatchesSegment", MuNChambersMatchesSegment , "Leptons.MuNChambersMatchesSegment[Leptons.Size]/I"                );
    root->Branch("Leptons.MuNPixelLayers"           , MuNPixelLayers            , "Leptons.MuNPixelLayers[Leptons.Size]/I"           );
    root->Branch("Leptons.MuNPixelLayersWMeasurement",MuNPixelLayersWMeasurement, "Leptons.MuNPixelLayersWMeasurement[Leptons.Size]/I"       ); //Uly 2011-04-04
    root->Branch("Leptons.MuNLostInnerHits", MuNLostInnerHits, "Leptons.MuNLostInnerHits[Leptons.Size]/I");
    root->Branch("Leptons.MuNLostOuterHits", MuNLostOuterHits, "Leptons.MuNLostOuterHits[Leptons.Size]/I");
    root->Branch("Leptons.MuNMuonhits"     , MuNMuonhits     , "Leptons.MuNMuonhits[Leptons.Size]/I");
    root->Branch("Leptons.MuType"          , MuType          , "Leptons.MuType[Leptons.Size]/I");

    root->Branch("Leptons.GenPt"     , GenPt    , "Leptons.GenPt[Leptons.Size]/F" );
    root->Branch("Leptons.GenEta"    , GenEta   , "Leptons.GenEta[Leptons.Size]/F");
    root->Branch("Leptons.GenPhi"    , GenPhi   , "Leptons.GenPhi[Leptons.Size]/F");
    root->Branch("Leptons.GenPdgID"  , GenPdgID , "Leptons.GenPdgID[Leptons.Size]/I"   );
    root->Branch("Leptons.GenMCTag"  , GenMCTag , "Leptons.GenMCTag[Leptons.Size]/I"   );
    root->Branch("Leptons.TrgPt"     , TrgPt    , "Leptons.TrgPt[Leptons.Size]/F" );
    root->Branch("Leptons.TrgEta"    , TrgEta   , "Leptons.TrgEta[Leptons.Size]/F");
    root->Branch("Leptons.TrgPhi"    , TrgPhi   , "Leptons.TrgPhi[Leptons.Size]/F");
    root->Branch("Leptons.TrgID"     , TrgID    , "Leptons.TrgID[Leptons.Size]/I" );
   
//YH 2012-08-15
    root->Branch("Leptons.ElepassConversionVeto" ,ElepassConversionVeto , "Leptons.ElepassConversionVeto[Leptons.Size]/O" );
    root->Branch("Leptons.ElesuperClusterEta"    ,ElesuperClusterEta    , "Leptons.ElesuperClusterEta[Leptons.Size]/F" );
    root->Branch("Leptons.ElemvaTrigV0"          ,ElemvaTrigV0          , "Leptons.ElemvaTrigV0[Leptons.Size]/F" );
    root->Branch("Leptons.ElemvaNTrigV0"         ,ElemvaNTrigV0         , "Leptons.ElemvaNTrigV0[Leptons.Size]/F" );
    root->Branch("Leptons.EletrackMomentumAtVtxp",EletrackMomentumAtVtxp, "Leptons.EletrackMomentumAtVtxp[Leptons.Size]/F" );
    root->Branch("Leptons.EleecalEnergy"         ,EleecalEnergy         , "Leptons.EleecalEnergy[Leptons.Size]/F" );
    root->Branch("Leptons.EleeSuperClusterOverP" ,EleeSuperClusterOverP , "Leptons.EleeSuperClusterOverP[Leptons.Size]/F" );
    root->Branch("Leptons.Elefbrem"              ,Elefbrem              , "Leptons.Elefbrem[Leptons.Size]/F" );
    root->Branch("Leptons.EleHoverE"             ,EleHoverE             , "Leptons.EleHoverE[Leptons.Size]/F" );
    root->Branch("Leptons.ElesigmaIetaIeta"      ,ElesigmaIetaIeta      , "Leptons.ElesigmaIetaIeta[Leptons.Size]/F");
    root->Branch("Leptons.EledeltaPhiVtx"        ,EledeltaPhiVtx        , "Leptons.EledeltaPhiVtx[Leptons.Size]/F");
    root->Branch("Leptons.EledeltaEtaVtx"        ,EledeltaEtaVtx        , "Leptons.EledeltaEtaVtx[Leptons.Size]/F");
    root->Branch("Leptons.EleExpnumberOfHits"    ,EleExpnumberOfHits    , "Leptons.EleExpnumberOfHits[Leptons.Size]/I");
    root->Branch("Leptons.MuTrackerLayersWithMeasurement"    ,MuTrackerLayersWithMeasurement   , "Leptons.MuTrackerLayersWithMeasurement[Leptons.Size]/I");
    root->Branch("Leptons.MunumberOfMatchedStations"         ,MunumberOfMatchedStations        , "Leptons.MunumberOfMatchedStations[Leptons.Size]/I");
  }
};


class JetClass{
public:
  int   Size; 
  int   Index[MAX_JETS];
  int   NTracks[MAX_JETS];
  float Et[MAX_JETS];
  float Pt[MAX_JETS];
  float Unc[MAX_JETS];
  float Eta[MAX_JETS];
  float Phi[MAX_JETS];
  int   JetIDLOOSE[MAX_JETS]; //Add by Chiyi
  float JetCharge[MAX_JETS];
  int   NConstituents[MAX_JETS];
  float JVAlpha[MAX_JETS];
  float JVBeta[MAX_JETS];
  float PtCorrRaw[MAX_JETS];  
  float PtCorrL2[MAX_JETS];  
  float PtCorrL3[MAX_JETS];  
  float PtCorrL7g[MAX_JETS];
  float PtCorrL7uds[MAX_JETS];
  float PtCorrL7c[MAX_JETS];  
  float PtCorrL7b[MAX_JETS];  
  float ECorrL7g[MAX_JETS];
  float ECorrL7uds[MAX_JETS];
  float ECorrL7c[MAX_JETS];
  float ECorrL7b[MAX_JETS];
  float JetBProbBJetTags[MAX_JETS];
  float JetProbBJetTags[MAX_JETS];
  float TrackCountHiPurBJetTags[MAX_JETS];  
  float TrackCountHiEffBJetTags[MAX_JETS]; 
  //float ImpactParaMVABJetTags[MAX_JETS]; //NONE //remove by Chiyi
  float SimpleSVHEBJetTags[MAX_JETS];  //for 36X sample //Add by Chiyi
  float SimpleSVHPBJetTags[MAX_JETS];  //for 36X sample //Add by Chiyi
  float CombinedSVBJetTags[MAX_JETS];
  float CombinedIncSVBJetTags[MAX_JETS];
  float CombinedSVMVABJetTags[MAX_JETS];
  float CombinedSVSoftLBJetTags[MAX_JETS];
  float CombinedCvsLJetTags[MAX_JETS];  
  float CombinedCvsBJetTags[MAX_JETS];  
  //float JetLRval[MAX_JETS]; //NONE //remove by Chiyi
  //float JetProb[MAX_JETS]; //NONE //remove by Chiyi
  float GenJetPt[MAX_JETS];
  float GenJetEta[MAX_JETS];
  float GenJetPhi[MAX_JETS];
  float GenPt[MAX_JETS];
  float GenEta[MAX_JETS];
  float GenPhi[MAX_JETS];
  int   GenPdgID[MAX_JETS];
  int   GenFlavor[MAX_JETS];
  int   GenMCTag[MAX_JETS]; // 0: unknown, 1: decay from W, 2: decay from Z, (+10) from b', (+20) from t'
  
  float Px[MAX_JETS]; //Uly 2011-04-04
  float Py[MAX_JETS]; //Uly 2011-04-04
  float Pz[MAX_JETS]; //Uly 2011-04-04
  float Energy[MAX_JETS]; //Uly 2011-04-04

  void setBranch(TTree *root) {
    root->Branch("Jets.Size"        , &Size    , "Jets.Size/I");
    root->Branch("Jets.Index"       , Index    , "Jets.Index[Jets.Size]/I");
    root->Branch("Jets.NTracks"     , NTracks  , "Jets.NTracks[Jets.Size]/I");
    root->Branch("Jets.Et"          , Et  , "Jets.Et[Jets.Size]/F");
    root->Branch("Jets.Pt"          , Pt  , "Jets.Pt[Jets.Size]/F");
    root->Branch("Jets.Unc"         , Unc , "Jets.Unc[Jets.Size]/F");
    root->Branch("Jets.Eta"         , Eta , "Jets.Eta[Jets.Size]/F");
    root->Branch("Jets.Phi"         , Phi , "Jets.Phi[Jets.Size]/F");
    root->Branch("Jets.JetIDLOOSE"  , JetIDLOOSE  , "Jets.JetIDLOOSE[Jets.Size]/I"); //Add by Chiyi
    root->Branch("Jets.JetCharge"   , JetCharge, "Jets.JetCharge[Jets.Size]/F");
    root->Branch("Jets.NConstituents" , NConstituents , "Jets.NConstituents[Jets.Size]/I");
    root->Branch("Jets.JVAlpha"     , JVAlpha  , "Jets.JVAlpha[Jets.Size]/F");
    root->Branch("Jets.JVBeta"      , JVBeta   , "Jets.JVBeta[Jets.Size]/F"); 
    root->Branch("Jets.PtCorrRaw"   , PtCorrRaw, "Jets.PtCorrRaw[Jets.Size]/F");
    root->Branch("Jets.PtCorrL2"    , PtCorrL2 , "Jets.PtCorrL2[Jets.Size]/F");
    root->Branch("Jets.PtCorrL3"    , PtCorrL3 , "Jets.PtCorrL3[Jets.Size]/F");
    root->Branch("Jets.PtCorrL7g"   , PtCorrL7g, "Jets.PtCorrL7g[Jets.Size]/F");
    root->Branch("Jets.PtCorrL7uds" , PtCorrL7uds   , "Jets.PtCorrL7uds[Jets.Size]/F"); 
    root->Branch("Jets.PtCorrL7c"   , PtCorrL7c, "Jets.PtCorrL7c[Jets.Size]/F"); 
    root->Branch("Jets.PtCorrL7b"   , PtCorrL7b, "Jets.PtCorrL7b[Jets.Size]/F");
    root->Branch("Jets.ECorrL7g"   , ECorrL7g, "Jets.ECorrL7g[Jets.Size]/F");
    root->Branch("Jets.ECorrL7uds" , ECorrL7uds   , "Jets.ECorrL7uds[Jets.Size]/F");
    root->Branch("Jets.ECorrL7c"   , ECorrL7c, "Jets.ECorrL7c[Jets.Size]/F");
    root->Branch("Jets.ECorrL7b"   , ECorrL7b, "Jets.ECorrL7b[Jets.Size]/F");
    root->Branch("Jets.JetBProbBJetTags"   , JetBProbBJetTags  , "Jets.JetBProbBJetTags[Jets.Size]/F");
    root->Branch("Jets.JetProbBJetTags"    , JetProbBJetTags   , "Jets.JetProbBJetTags[Jets.Size]/F");
    root->Branch("Jets.TrackCountHiPurBJetTags" ,TrackCountHiPurBJetTags , "Jets.TrackCountHiPurBJetTags[Jets.Size]/F"); 
    root->Branch("Jets.TrackCountHiEffBJetTags" ,TrackCountHiEffBJetTags , "Jets.TrackCountHiEffBJetTags[Jets.Size]/F");
    root->Branch("Jets.SimpleSVHEBJetTags"    ,SimpleSVHEBJetTags   , "Jets.SimpleSVHEBJetTags[Jets.Size]/F"); //for 36X sample //Add by Chiyi
    root->Branch("Jets.SimpleSVHPBJetTags"    ,SimpleSVHPBJetTags   , "Jets.SimpleSVHPBJetTags[Jets.Size]/F"); //for 36X sample //Add by Chiyi
    root->Branch("Jets.CombinedSVBJetTags"    ,CombinedSVBJetTags    , "Jets.CombinedSVBJetTags[Jets.Size]/F");
    root->Branch("Jets.CombinedIncSVBJetTags"    ,CombinedIncSVBJetTags    , "Jets.CombinedIncSVBJetTags[Jets.Size]/F");
    root->Branch("Jets.CombinedSVMVABJetTags" ,CombinedSVMVABJetTags , "Jets.CombinedSVMVABJetTags[Jets.Size]/F");
    root->Branch("Jets.CombinedSVSoftLBJetTags" ,CombinedSVSoftLBJetTags , "Jets.CombinedSVSoftLBJetTags[Jets.Size]/F");
    root->Branch("Jets.CombinedCvsLJetTags"     ,CombinedCvsLJetTags   , "Jets.CombinedCvsLJetTags[Jets.Size]/F");      
    root->Branch("Jets.CombinedCvsBJetTags"     ,CombinedCvsBJetTags   , "Jets.CombinedCvsBJetTags[Jets.Size]/F");      
    
    root->Branch("Jets.GenJetPt"   ,GenJetPt  , "Jets.GenJetPt[Jets.Size]/F");
    root->Branch("Jets.GenJetEta"  ,GenJetEta , "Jets.GenJetEta[Jets.Size]/F");
    root->Branch("Jets.GenJetPhi"  ,GenJetPhi , "Jets.GenJetPhi[Jets.Size]/F");
    root->Branch("Jets.GenPt"      ,GenPt  , "Jets.GenPt[Jets.Size]/F");
    root->Branch("Jets.GenEta"     ,GenEta , "Jets.GenEta[Jets.Size]/F");
    root->Branch("Jets.GenPhi"     ,GenPhi , "Jets.GenPhi[Jets.Size]/F");
    root->Branch("Jets.GenPdgID"   ,GenPdgID  , "Jets.GenPdgID[Jets.Size]/I");
    root->Branch("Jets.GenFlavor"  ,GenFlavor , "Jets.GenFlavor[Jets.Size]/I");
    root->Branch("Jets.GenMCTag"   ,GenMCTag  , "Jets.GenMCTag[Jets.Size]/I");
    
    root->Branch("Jets.Px" ,Px  , "Jets.Px[Jets.Size]/F"); //Uly 2011-04-04
    root->Branch("Jets.Py" ,Py  , "Jets.Py[Jets.Size]/F"); //Uly 2011-04-04
    root->Branch("Jets.Pz" ,Pz  , "Jets.Pz[Jets.Size]/F"); //Uly 2011-04-04
    root->Branch("Jets.Energy",Energy , "Jets.Energy[Jets.Size]/F" ); //Uly 2011-04-04
  }

};

class VtxInfoClass{
public:
  int     Size;
  int     isValid[MAX_VERTEX];
  bool    isFake[MAX_VERTEX]; //Uly 2011-04-04
  int     Type[MAX_VERTEX];   //0 - Offline Primary Vertices, 1 - Offline Primary Vertices with beam spot constraint,
                              //2 - Pixel Vertices
  int     Ndof[MAX_VERTEX];
  float   NormalizedChi2[MAX_VERTEX];
  float   Pt_Sum[MAX_VERTEX];
  float   vx[MAX_VERTEX];
  float   vy[MAX_VERTEX];
  float   vz[MAX_VERTEX];
  float   Rho[MAX_VERTEX];

  void setBranch(TTree *root) {
    root->Branch("VtxInfo.Size"     , &Size      , "VtxInfo.Size/I"        );
    root->Branch("VtxInfo.isValid"  , isValid    , "VtxInfo.isValid[VtxInfo.Size]/I"    );
    root->Branch("VtxInfo.isFake"   , isFake     , "VtxInfo.isFake[VtxInfo.Size]/O"     ); //Uly 2011-04-04
    root->Branch("VtxInfo.Type"     , Type       , "VtxInfo.Type[VtxInfo.Size]/I"       );
    root->Branch("VtxInfo.Ndof"     , Ndof       , "VtxInfo.Ndof[VtxInfo.Size]/I"       );
    root->Branch("VtxInfo.NormalizedChi2" , NormalizedChi2 , "VtxInfo.NormalizedChi2[VtxInfo.Size]/F");
    root->Branch("VtxInfo.Pt_Sum"    , Pt_Sum  , "VtxInfo.Pt_Sum[VtxInfo.Size]/F");
    root->Branch("VtxInfo.vx"        , vx      , "VtxInfo.vx[VtxInfo.Size]/F"    );
    root->Branch("VtxInfo.vy"        , vy      , "VtxInfo.vy[VtxInfo.Size]/F"    );
    root->Branch("VtxInfo.vz"        , vz      , "VtxInfo.vz[VtxInfo.Size]/F"    );
    root->Branch("VtxInfo.Rho"       , Rho     , "VtxInfo.Rho[VtxInfo.Size]/F"   );
  }                                                                             
};

class GenPartsClass{
public:
  int Size;
  int Index[MAX_GENPARTS];
  float Pt[MAX_GENPARTS];
  float Eta[MAX_GENPARTS];
  float Phi[MAX_GENPARTS];
  float Mass[MAX_GENPARTS];
  int PdgID[MAX_GENPARTS];
  int Status[MAX_GENPARTS];
  int nMo[MAX_GENPARTS];
  int nDa[MAX_GENPARTS];
  int Mo1[MAX_GENPARTS];
  int Mo2[MAX_GENPARTS];
  int Da1[MAX_GENPARTS];
  int Da2[MAX_GENPARTS];

  void setBranch(TTree *root) {
    root->Branch("GenParts.Size"    , &Size     ,"GenParts.Size/I"                      );
    root->Branch("GenParts.Index"   , Index     , "GenParts.Index[GenParts.Size]/I"     );
    root->Branch("GenParts.Pt"      , Pt        , "GenParts.Pt[GenParts.Size]/F"        );
    root->Branch("GenParts.Eta"     , Eta       , "GenParts.Eta[GenParts.Size]/F"       );
    root->Branch("GenParts.Phi"     , Phi       , "GenParts.Phi[GenParts.Size]/F"       );
    root->Branch("GenParts.Mass"    , Mass      , "GenParts.Mass[GenParts.Size]/F"      );
    root->Branch("GenParts.PdgID"   , PdgID     , "GenParts.PdgID[GenParts.Size]/I"     );
    root->Branch("GenParts.Status"  , Status    , "GenParts.Status[GenParts.Size]/I"    );
    root->Branch("GenParts.nMo"     , nMo       , "GenParts.nMo[GenParts.Size]/I"       );
    root->Branch("GenParts.nDa"     , nDa       , "GenParts.nDa[GenParts.Size]/I"       );
    root->Branch("GenParts.Mo1"     , Mo1       , "GenParts.Mo1[GenParts.Size]/I"       );
    root->Branch("GenParts.Mo2"     , Mo2       , "GenParts.Mo2[GenParts.Size]/I"       );
    root->Branch("GenParts.Da1"     , Da1       , "GenParts.Da1[GenParts.Size]/I"       );
    root->Branch("GenParts.Da2"     , Da2       , "GenParts.Da2[GenParts.Size]/I"       );
  }
};


class MyFCNCkit : public edm::EDAnalyzer {
public:
  explicit MyFCNCkit(const edm::ParameterSet&);
  ~MyFCNCkit();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------

  TTree *myTree;
  EvtInfoClass EvtInfo;
  GenPartsClass GenParts;
  LeptonClass Leptons;
  JetClass Jets;
  VtxInfoClass VtxInfo;
  
  bool MCflag;
  bool m_use_conddb;
  
  edm::InputTag muonlabel_;
  edm::InputTag eleclabel_;
  edm::InputTag pfjetlabel_;
  edm::InputTag metlabel_;
  edm::InputTag genlabel_;
  edm::InputTag hltlabel_;
  edm::InputTag pathltlabel_;
  edm::InputTag offlinePVlabel_;
  edm::InputTag offlinePVBSlabel_;
  edm::InputTag offlineBSlabel_;
  edm::InputTag genevtlabel_;
  edm::InputTag gtdigilabel_;
  edm::InputTag puInfoLabel_;
  edm::InputTag rhoIsoLabel_;

  edm::EDGetTokenT<reco::VertexCollection> VertexToken;
  edm::EDGetTokenT<reco::BeamSpot> BeamSpotToken;
  edm::EDGetTokenT<double> RhoIsoToken;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > PileupToken;
  edm::EDGetTokenT<edm::TriggerResults> TigResultsToken;
  edm::EDGetTokenT<L1GlobalTriggerReadoutRecord> gtToken;

  edm::EDGetTokenT<GenEventInfoProduct> GenEventInfoToken;
  edm::EDGetTokenT<reco::GenParticleCollection> GenToken;
  // edm::EDGetTokenT<L1GlobalTriggerReadoutRecord>   fGenDigiToken     ;
  // edm::EDGetTokenT<LHEEventProduct>                fLHEToken         ;
  // edm::EDGetTokenT<LHERunInfoProduct>              fLHERunToken      ;

  edm::EDGetTokenT<std::vector<pat::Jet> > JetToken;
  edm::EDGetTokenT<std::vector<pat::MET> > METToken;
  //edm::EDGetTokenT<std::vector<reco::PFMET> > METToken;
  edm::EDGetTokenT<std::vector<pat::Muon> > MuonToken;
  edm::EDGetTokenT<std::vector<pat::Electron> > ElectronToken;

};


//define this as a plug-in
DEFINE_FWK_MODULE(MyFCNCkit);
