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
// Original Author:  Yuan CHAO,27 2-020 (CERN) Mailbox F10500,+41 22 76 74870,+41 22 76 74870
//         Created:  Wed Oct  5 22:39:27 UTC 2011
// $Id$
//
//


// system include files
#include <memory>

#include <TROOT.h>
#include <TSystem.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TRandom.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "DataFormats/Math/interface/angle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" 
// #include "MagneticField/Engine/interface/MagneticField.h"
// #include "DataFormats/TrackReco/interface/Track.h"
// //#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "FWCore/Framework/interface/ESHandle.h"
// #include "DataFormats/Scalers/interface/DcsStatus.h"
// #include "DataFormats/GeometryVector/interface/GlobalPoint.h"

// For JER
//#include "FWCore/Framework/interface/ESHandle.h"
//#include "JetMETCorrections/Modules/interface/JetResolution.h"

// For JEC
// #include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
// #include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
// #include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
// #include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
// #include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

// PileupSummaryInfo
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"


//YH 2012-08-15
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

//
// class declaration
//

#include "TopQuarkAnalysis/MyFCNCkit/interface/MyFCNCkit.h"

//
// constants, enums and typedefs
//

#define W_MASS          80.403
#define Z_MASS          91.1876
#define MUON_MASS       0.105658
#define ELECTRON_MASS   0.0005109989

using namespace edm;
using namespace reco;
using namespace std;
using namespace pat;
using namespace math;
using namespace ROOT;

//
// static data member definitions
//

// #define MAX_LEPTONS     128
// #define MAX_JETS        64
// #define MAX_GENPARTS    512

//
// constructors and destructor
//
MyFCNCkit::MyFCNCkit(const edm::ParameterSet& iConfig){

   edm::Service<TFileService> fs;
   TFileDirectory results = TFileDirectory( fs->mkdir("results") );

   MCflag               = iConfig.getUntrackedParameter<bool>("MCflag",true);
   muonlabel_           = iConfig.getParameter<InputTag>("muonlabel");  //"cleanPatMuons"
   eleclabel_           = iConfig.getParameter<InputTag>("eleclabel");  // "cleanPatElectrons"
   pfjetlabel_          = iConfig.getParameter<InputTag>("pfjetlabel"); // "cleanPatJets"
   metlabel_            = iConfig.getParameter<InputTag>("metlabel");   //"patMETs"
   genlabel_            = iConfig.getParameter<InputTag>("genlabel");   // "genParticles"
   hltlabel_            = iConfig.getParameter<InputTag>("hltlabel");   // "TriggerResults::HLT"
   pathltlabel_         = iConfig.getParameter<InputTag>("pathltlabel"); // patTriggerEvent
   offlinePVlabel_      = iConfig.getParameter<InputTag>("offlinePVlabel"); //offlinePrimaryVertices
   //   offlinePVBSlabel_    = iConfig.getParameter<InputTag>("offlinePVBSlabel"); //offlinePrimaryVerticesWithBS
   offlineBSlabel_      = iConfig.getParameter<InputTag>("offlineBSlabel"); //offlineBeamSpot
//   pixelvtxlabel_       = iConfig.getParameter<InputTag>("pixelvtxlabel"); //pixelVertices
   genevtlabel_         = iConfig.getParameter<InputTag>("genevtlabel"); //generator
   gtdigilabel_         = iConfig.getParameter<InputTag>("gtdigilabel"); //gtDigis
   puInfoLabel_         = iConfig.getParameter<InputTag>("puInfoLabel");
   rhoIsoLabel_         = iConfig.getParameter<InputTag>("rhoIsoInputLabel");

   VertexToken = consumes<reco::VertexCollection>(offlinePVlabel_);
   BeamSpotToken = consumes<reco::BeamSpot>(offlineBSlabel_);
   RhoIsoToken = consumes<double>(rhoIsoLabel_);
   PileupToken = consumes< std::vector< PileupSummaryInfo > >(puInfoLabel_);
   TigResultsToken = consumes<edm::TriggerResults>(hltlabel_);
   gtToken = consumes<L1GlobalTriggerReadoutRecord>(gtdigilabel_);

   GenEventInfoToken = consumes<GenEventInfoProduct>(genevtlabel_);
   GenToken = consumes<reco::GenParticleCollection>(genlabel_);

   JetToken = consumes<std::vector<pat::Jet> >(pfjetlabel_);
   //METToken = consumes<std::vector<reco::PFMET> >(metlabel_);
   METToken = consumes<std::vector<pat::MET> >(metlabel_);
   MuonToken = consumes<std::vector<pat::Muon> >(muonlabel_);
   ElectronToken = consumes<std::vector<pat::Electron> >(eleclabel_);

   m_use_conddb = iConfig.getUntrackedParameter<bool>("useCondDB", false);

   std::cout << "Hello world !\n";
   //now do what ever initialization is needed

}


MyFCNCkit::~MyFCNCkit()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyFCNCkit::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;


/*
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
*/

  GenParts.Size=0;
  Leptons.Size=0;
  Jets.Size=0;
  VtxInfo.Size=0;
  EvtInfo.nBooking=N_TRIGGER_BOOKINGS;


  bool isData = iEvent.isRealData();   // Add by Jacky
  
  edm::Handle<std::vector<pat::Muon> >         MuonHandle;
  edm::Handle<std::vector<pat::Electron> >     ElectronHandle;
  edm::Handle<std::vector<pat::MET> >          METHandle;
  //edm::Handle<std::vector<reco::PFMET> >          METHandle;
  edm::Handle<std::vector<pat::Jet> >          JetHandle;  //PFJets

  edm::Handle<reco::GenParticleCollection>     GenHandle;  
  edm::Handle<reco::VertexCollection>          VertexHandle;
  edm::Handle<reco::VertexCollection>          VertexHandleBS; //Dmitry
  edm::Handle<reco::VertexCollection>          VertexHandlePixel; //Dmitry

  edm::Handle<double> rhoIsoHandle;
  
  iEvent.getByLabel( muonlabel_,   MuonHandle);
  iEvent.getByLabel( eleclabel_,   ElectronHandle);
  iEvent.getByLabel( pfjetlabel_,  JetHandle);  //PFJets
  iEvent.getByLabel( metlabel_,    METHandle);
  
  iEvent.getByLabel( rhoIsoLabel_, rhoIsoHandle); // for Iso PU corr

  // JME::JetResolution resolution;
  // JME::JetResolutionScaleFactor res_sf;

  
  if(!isData) iEvent.getByLabel( genlabel_, GenHandle);

  iEvent.getByLabel( offlinePVlabel_, VertexHandle); 
//   iEvent.getByLabel( offlinePVBSlabel_, VertexHandleBS);   //Offline primary vertices with Beam Spot constraint //Dmitry
//   iEvent.getByLabel( pixelvtxlabel_, VertexHandlePixel);   //Offline primary vertices with Beam Spot constraint //Dmitry     

  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( pathltlabel_, triggerEvent );
  const pat::helper::TriggerMatchHelper matchHelper;
  
  // Prim. vertex
  memset(&VtxInfo,0x00,sizeof(VtxInfo));
  
  const vector<reco::Vertex> Vertices = *VertexHandle;
  double PV_Pt_Max = -100.;
  double Signal_Vz = 0.;
  
  reco::Vertex PrimVtx;
  if( !VertexHandle.failedToGet() && VertexHandle->size() > 0 ) {
    for(vector<reco::Vertex>::const_iterator it_vtx = Vertices.begin();
        it_vtx != Vertices.end(); it_vtx++ ) {
      if (VtxInfo.Size>=MAX_VERTEX) {
        cout << "PV " << VtxInfo.Size << endl;
        fprintf(stderr,"ERROR: number of  Tracks exceeds the size of array.\n");
        break;//exit(0);
      }
      VtxInfo.Type[VtxInfo.Size] = 0; //Vertices WITHOUT the Beam Spot constraint
      VtxInfo.isValid[VtxInfo.Size] = it_vtx->isValid();
      VtxInfo.isFake[VtxInfo.Size] = it_vtx->isFake(); //Uly 2011-05-16
      VtxInfo.Ndof[VtxInfo.Size] = it_vtx->ndof();
      VtxInfo.NormalizedChi2[VtxInfo.Size] = it_vtx->normalizedChi2();
      VtxInfo.vx[VtxInfo.Size] = it_vtx->x();
      VtxInfo.vy[VtxInfo.Size] = it_vtx->y();
      VtxInfo.vz[VtxInfo.Size] = it_vtx->z();
      VtxInfo.Rho[VtxInfo.Size] = it_vtx->position().Rho();
      VtxInfo.Pt_Sum[VtxInfo.Size] = 0.;

      for(reco::Vertex::trackRef_iterator it = it_vtx->tracks_begin();
          it != it_vtx->tracks_end(); it++)
        VtxInfo.Pt_Sum[VtxInfo.Size] += (*it)->pt();
      
      if( VtxInfo.Pt_Sum[VtxInfo.Size] >= PV_Pt_Max ){
        PV_Pt_Max = VtxInfo.Pt_Sum[VtxInfo.Size];
        PrimVtx = *it_vtx;
      }
      
      VtxInfo.Size++;
    }
  }
  //find and store z pozition for track to jet  association
  Signal_Vz=PrimVtx.z();
   
  // //Vertices WITH beam spot constraint
  // const vector<reco::Vertex> VerticesBS = *VertexHandleBS;
  // double PVBS_Pt_Max = -100.;
  // reco::Vertex PrimVtx_BS;
  
  // if( !VertexHandleBS.failedToGet() && VertexHandleBS->size() > 0 ) {
  //    for(vector<reco::Vertex>::const_iterator it_vtx = VerticesBS.begin();
  //          it_vtx != VerticesBS.end(); it_vtx++ ) {
  //       if (VtxInfo.Size>=MAX_VERTEX) {
  //          cout << "PVBS " << VtxInfo.Size << endl;
  //          fprintf(stderr,"ERROR: number of  Vertices exceeds the size of array.\n");
  //          break;//exit(0);
  //       }
  //       VtxInfo.Type[VtxInfo.Size] = 1;  //Vertices WITH the Beam Spot constraint
  //       VtxInfo.isValid[VtxInfo.Size] = it_vtx->isValid();
  //       VtxInfo.isFake[VtxInfo.Size] = it_vtx->isFake(); //Uly 2011-05-16
  //       VtxInfo.Ndof[VtxInfo.Size] = it_vtx->ndof();
  //       VtxInfo.NormalizedChi2[VtxInfo.Size] = it_vtx->normalizedChi2();
  //       VtxInfo.vx[VtxInfo.Size] = it_vtx->x();
  //       VtxInfo.vy[VtxInfo.Size] = it_vtx->y();
  //       VtxInfo.vz[VtxInfo.Size] = it_vtx->z();
  //       VtxInfo.Rho[VtxInfo.Size] = it_vtx->position().Rho();
  //       VtxInfo.Pt_Sum[VtxInfo.Size] = 0.;
  //   for(reco::Vertex::trackRef_iterator it = it_vtx->tracks_begin();
  //       it != it_vtx->tracks_end(); it++)
  //     VtxInfo.Pt_Sum[VtxInfo.Size] += (*it)->pt();
  
  //       if( VtxInfo.Pt_Sum[VtxInfo.Size] >= PVBS_Pt_Max ){
  //     PVBS_Pt_Max = VtxInfo.Pt_Sum[VtxInfo.Size];
  //     PrimVtx_BS = *it_vtx;
  //       }                      
  //       VtxInfo.Size++;
  //    }
  // }

  // Get Beam Spot 
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel( offlineBSlabel_, beamSpotHandle);
  
  if ( beamSpotHandle.isValid() )
    {
      beamSpot = *beamSpotHandle;
      
    } else
    {
      edm::LogInfo("MyAnalyzer")
        << "No beam spot available from EventSetup \n";
    }
  
  
  //Leptons
  
  memset(&Leptons,0x00,sizeof(Leptons));
  //Muons
  for(std::vector<pat::Muon>::const_iterator it_mu = MuonHandle->begin(); 
      it_mu != MuonHandle->end(); it_mu++ ) {
    
    if(Leptons.Size>=MAX_LEPTONS) {
      std::cerr <<"ERROR: number of leptons exceeds the size of array.\n";
      break;//exit(0);
    }
    
    Leptons.Index   [Leptons.Size] = Leptons.Size;
    Leptons.Type    [Leptons.Size] = 13;
    Leptons.Charge  [Leptons.Size] = it_mu->charge();
    Leptons.Pt      [Leptons.Size] = it_mu->pt();
    Leptons.Eta     [Leptons.Size] = it_mu->eta();
    Leptons.Phi     [Leptons.Size] = it_mu->phi();
//      Leptons.TrackIso[Leptons.Size] = it_mu->trackIso();
//      Leptons.EcalIso [Leptons.Size] = it_mu->ecalIso();
//      Leptons.HcalIso [Leptons.Size] = it_mu->hcalIso();
    
    Leptons.Px      [Leptons.Size] = it_mu->px(); //Uly 2011-04-04
    Leptons.Py      [Leptons.Size] = it_mu->py(); //Uly 2011-04-04
    Leptons.Pz      [Leptons.Size] = it_mu->pz(); //Uly 2011-04-04
    Leptons.Energy  [Leptons.Size] = it_mu->energy(); //Uly 2011-04-04

//      const reco::CandidateBaseRef muBaseRef(edm::Ref<std::vector<pat::Muon> >
// 					    (MuonHandle,
// 					     it_mu-MuonHandle->begin()));
//      const pat::TriggerObjectRef trigRef3( matchHelper.triggerMatchObject
// 					   ( muBaseRef,
// 					     "TriggerMatchEGMuForMu",
// 					     iEvent, *triggerEvent ) );
//      if (trigRef3.isAvailable()) { 
//        Leptons.TrgPt    [Leptons.Size] = trigRef3->pt();
//        Leptons.TrgEta   [Leptons.Size] = trigRef3->eta();
//        Leptons.TrgPhi   [Leptons.Size] = trigRef3->phi();
//        Leptons.TrgID    [Leptons.Size] += 100;
//      }

//      const pat::TriggerObjectRef trigRef2( matchHelper.triggerMatchObject
// 					   ( muBaseRef, "TriggerMatchDoubleMu",
// 					     iEvent, *triggerEvent ) );
//      if (trigRef2.isAvailable()) { 
//        Leptons.TrgPt    [Leptons.Size] = trigRef2->pt();
//        Leptons.TrgEta   [Leptons.Size] = trigRef2->eta();
//        Leptons.TrgPhi   [Leptons.Size] = trigRef2->phi();
//        Leptons.TrgID    [Leptons.Size] += 10;
//      }

//      const pat::TriggerObjectRef trigRef1( matchHelper.triggerMatchObject
// 					   ( muBaseRef, "TriggerMatchSingleMu",
// 					     iEvent, *triggerEvent ) );
//      if (trigRef1.isAvailable()) { 
//        Leptons.TrgPt    [Leptons.Size] = trigRef1->pt();
//        Leptons.TrgEta   [Leptons.Size] = trigRef1->eta();
//        Leptons.TrgPhi   [Leptons.Size] = trigRef1->phi();
//        Leptons.TrgID    [Leptons.Size] += 1;
//      }

//     reco::MuonEnergy muEnergy = it_mu->calEnergy();

    Leptons.MuIDGlobalMuonPromptTight[Leptons.Size] = it_mu->muonID("GlobalMuonPromptTight");

     // InnerTrack() is only valid for GlobalMuon and TrackerMuon
     // See Leptons.MuType for it_mu->type() bits
    if ((it_mu->type() & 0x02) || (it_mu->type() & 0x04)){ 
      Leptons.MuInnerTrackDz      [Leptons.Size] = it_mu->innerTrack()->dz(); 
      Leptons.MuInnerTrackD0      [Leptons.Size] = it_mu->innerTrack()->d0(); 
      Leptons.MuInnerTrackDxy_BS  [Leptons.Size] = it_mu->innerTrack()->dxy(beamSpot.position()); 
      Leptons.MuInnerTrackDxy_PV  [Leptons.Size] = it_mu->innerTrack()->dxy(PrimVtx.position()); 
      //       Leptons.MuInnerTrackDxy_PVBS[Leptons.Size] = it_mu->innerTrack()->dxy(PrimVtx_BS.position()); 
      Leptons.MuInnerTrackNHits   [Leptons.Size] = it_mu->innerTrack()->numberOfValidHits(); 
      Leptons.MuNTrackerHits      [Leptons.Size] = it_mu->innerTrack()->hitPattern().numberOfValidTrackerHits(); 
      Leptons.MuNPixelLayers      [Leptons.Size] = it_mu->innerTrack()->hitPattern().numberOfValidPixelHits();
      //       Leptons.MuNLostInnerHits    [Leptons.Size] = it_mu->innerTrack()->hitPattern().numberOfLostHits();
      Leptons.vertexZ             [Leptons.Size] = it_mu->vertex().z(); //Uly 2011-04-04
      Leptons.MuNPixelLayersWMeasurement[Leptons.Size] = it_mu->innerTrack()->hitPattern().pixelLayersWithMeasurement(); //Uly 2011-04-04
    }
    
    if (it_mu->type() & 0x02){
      Leptons.MuGlobalNormalizedChi2 [Leptons.Size] = it_mu->globalTrack()->normalizedChi2();
      Leptons.MuNMuonhits            [Leptons.Size] = it_mu->globalTrack()->hitPattern().numberOfValidMuonHits();
    }
    if ((it_mu->type() & 0x02) || (it_mu->type() & 0x08)){
      //       Leptons.MuNLostOuterHits       [Leptons.Size] = it_mu->outerTrack()->hitPattern().numberOfLostHits();
      Leptons.MunumberOfMatchedStations[Leptons.Size]=it_mu->numberOfMatchedStations();//YH 2012-08-15 
    }
    if ((it_mu->type() & 0x02) || (it_mu->type() & 0x04)){
      Leptons.MuTrackerLayersWithMeasurement[Leptons.Size]=it_mu->track()->hitPattern().trackerLayersWithMeasurement();//YH2012-08-15
    }
    
    
//      Leptons.MuCaloCompat              [Leptons.Size] = it_mu->caloCompatibility();
    Leptons.MuNChambers               [Leptons.Size] = it_mu->numberOfChambers(); 
    Leptons.MuNChambersMatchesSegment [Leptons.Size] = it_mu->numberOfMatches();  // At least 2 Chambers matched with segments

     // Muon type bits:
     // static const unsigned int GlobalMuon     =  1<<1 (0x02);
     // static const unsigned int TrackerMuon    =  1<<2 (0x04);
     // static const unsigned int StandAloneMuon =  1<<3 (0x08);
     // static const unsigned int CaloMuon       =  1<<4 (0x10);
    Leptons.MuType[Leptons.Size] = it_mu->type();
    
    // PF lepton isolation
    Leptons.chargedIso   [Leptons.Size] = it_mu->chargedHadronIso();
    Leptons.neutralIso   [Leptons.Size] = it_mu->neutralHadronIso();
    Leptons.photonIso    [Leptons.Size] = it_mu->photonIso();
    if (it_mu->isPFMuon() && it_mu->isPFIsolationValid()){
      Leptons.ChargedHadronIsoR04  [Leptons.Size] = it_mu->pfIsolationR04().sumChargedHadronPt;
      Leptons.NeutralHadronIsoR04  [Leptons.Size] = it_mu->pfIsolationR04().sumNeutralHadronEt;
      Leptons.PhotonIsoR04         [Leptons.Size] = it_mu->pfIsolationR04().sumPhotonEt;
      Leptons.sumPUPtR04           [Leptons.Size] = it_mu->pfIsolationR04().sumPUPt;
    } 
    
    Leptons.Size++;
    
  }
  
  float AEff03 = 0.0;
  //Electrons
  for(std::vector<pat::Electron>::const_iterator it_el = 
        ElectronHandle->begin(); 
      it_el != ElectronHandle->end(); it_el++ ){
    
    if (Leptons.Size>=MAX_LEPTONS){
      std::cerr << "ERROR: number of leptons exceeds the size of array.\n";
      break;//exit(0);
    }
    
    if(iEvent.isRealData()){
      AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, fabs(it_el->superCluster()->eta()), ElectronEffectiveArea::kEleEAData2012);
    }else{
      AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, fabs(it_el->superCluster()->eta()), ElectronEffectiveArea::kEleEAFall11MC);
    }
    
    //std::cout << "AEff03: " << AEff03 << endl;     
    
    Leptons.Index          [Leptons.Size] = Leptons.Size;
    Leptons.isEcalDriven   [Leptons.Size] = it_el->ecalDrivenSeed();
    Leptons.isTrackerDriven[Leptons.Size] = it_el->trackerDrivenSeed();
    Leptons.Type           [Leptons.Size] = 11;
    Leptons.Charge         [Leptons.Size] = it_el->charge();
//      Leptons.ChargeGsf      [LepInfo.Size] = it_el->gsfTrack()->charge();
//      if( it_el->closestCtfTrackRef().isNonnull() ) 
//        Leptons.ChargeCtf       [LepInfo.Size] = it_el->closestCtfTrackRef()->charge();
//      Leptons.ChargeScPix    [LepInfo.Size] = it_el->scPixCharge();
    Leptons.Pt             [Leptons.Size] = it_el->pt();
    Leptons.Et             [Leptons.Size] = it_el->et(); //Uly 2011-04-04

    Leptons.Eta            [Leptons.Size] = it_el->superCluster()->eta(); //Uly 2011-04-04
    //Leptons.Eta          [Leptons.Size] = it_el->eta();
    Leptons.caloEta        [Leptons.Size] = it_el->caloPosition().eta();
    Leptons.Phi            [Leptons.Size] = it_el->superCluster()->phi(); //Uly 2011-04-04
    
    Leptons.Px         [Leptons.Size] = it_el->px(); //Uly 2011-04-04
    Leptons.Py         [Leptons.Size] = it_el->py(); //Uly 2011-04-04
    Leptons.Pz         [Leptons.Size] = it_el->pz(); //Uly 2011-04-04
    Leptons.Energy     [Leptons.Size] = it_el->energy(); //Uly 2011-04-04
    
    Leptons.ElTrackD0      [Leptons.Size] = it_el->gsfTrack()->d0();
    Leptons.ElTrackDxy_BS  [Leptons.Size] = it_el->gsfTrack()->dxy(beamSpot.position());
    Leptons.ElTrackDxy_PV  [Leptons.Size] = it_el->gsfTrack()->dxy(PrimVtx.position());
     //     Leptons.ElTrackDxy_PVBS[Leptons.Size] = it_el->gsfTrack()->dxy(PrimVtx_BS.position());
    Leptons.vertexZ        [Leptons.Size] = it_el->vertex().z();//Uly 2011-04-04
//      const reco::CandidateBaseRef elBaseRef
//        (edm::Ref< std::vector<pat::Electron> >(ElectronHandle,
// 					       it_el-ElectronHandle->begin()));
//      const pat::TriggerObjectRef trigRef3( matchHelper.triggerMatchObject
// 					   ( elBaseRef,
// 					     "TriggerMatchEGMuForEl",
// 					     iEvent, *triggerEvent ) );
//      if (trigRef3.isAvailable()) { 
//        Leptons.TrgPt    [Leptons.Size] = trigRef3->pt();
//        Leptons.TrgEta   [Leptons.Size] = trigRef3->eta();
//        Leptons.TrgPhi   [Leptons.Size] = trigRef3->phi();
//        Leptons.TrgID    [Leptons.Size] += 100;
//      }
//      const pat::TriggerObjectRef trigRef2( matchHelper.triggerMatchObject( elBaseRef, "TriggerMatchDoubleEl", iEvent, *triggerEvent ) );
//      if (trigRef2.isAvailable()) { 
//        Leptons.TrgPt    [Leptons.Size] = trigRef2->pt();
//        Leptons.TrgEta   [Leptons.Size] = trigRef2->eta();
//        Leptons.TrgPhi   [Leptons.Size] = trigRef2->phi();
//        Leptons.TrgID    [Leptons.Size] += 10;
//      }
//      const pat::TriggerObjectRef trigRef1( matchHelper.triggerMatchObject( elBaseRef, "TriggerMatchSingleEl", iEvent, *triggerEvent ) );
//      if (trigRef1.isAvailable()) { 
//        Leptons.TrgPt    [Leptons.Size] = trigRef1->pt();
//        Leptons.TrgEta   [Leptons.Size] = trigRef1->eta();
//        Leptons.TrgPhi   [Leptons.Size] = trigRef1->phi();
//        Leptons.TrgID    [Leptons.Size] += 1;
//      }
     
    //
    // PAT : ISO
//   Leptons.TrackIso   [Leptons.Size] = it_el->trackIso();
//   Leptons.EcalIso    [Leptons.Size] = it_el->ecalIso();
//   Leptons.HcalIso    [Leptons.Size] = it_el->hcalIso();
    //
    // Use isolations from the GsfElectron instead of PAT
    Leptons.TrackIso     [Leptons.Size] = it_el->dr03TkSumPt();
    Leptons.EcalIso      [Leptons.Size] = it_el->dr03EcalRecHitSumEt();
    Leptons.HcalIso      [Leptons.Size] = it_el->dr03HcalTowerSumEt();
//   Leptons.HcalDepth1Iso[Leptons.Size] = it_el->dr03HcalDepth1TowerSumEt();
//      Leptons.HcalDepth2Iso[Leptons.Size] = it_el->dr03HcalDepth2TowerSumEt();

    // PF lepton isolation
    Leptons.chargedIso   [Leptons.Size] = it_el->chargedHadronIso();
    Leptons.neutralIso   [Leptons.Size] = it_el->neutralHadronIso();
    Leptons.photonIso    [Leptons.Size] = it_el->photonIso();

//     Leptons.chargedIso   [Leptons.Size] = it_el->chargedHadronIso();
//     Leptons.neutralIso   [Leptons.Size] = it_el->neutralHadronIso();
//     Leptons.photonIso    [Leptons.Size] = it_el->photonIso();

//     isodeposit::AbsVetos vetos_ch;
//     isodeposit::AbsVetos vetos_nh;
//     isodeposit::AbsVetos vetos_ph;

//     isodeposit::Direction Dir = isodeposit::Direction(it_el->superCluster()->eta(), it_el->superCluster()->phi());
//
//     if( abs( it_el->superCluster()->eta() ) 1.479 ){
//       vetos_ch.push_back(new ConeVeto( Dir, 0.015 ));
//       vetos_ph.push_back(new ConeVeto( Dir, 0.08 ));
//     }
//
//     Leptons.chargedIso[Leptons.Size] = it_el->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
//     Leptons.neutralIso[Leptons.Size] = it_el->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
//     Leptons.photonIso[Leptons.Size] = it_el->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
//
//     Leptons.puChIso[Leptons.Size] = it_el->isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
//     Leptons.chAllIso[Leptons.Size] = it_el->isoDeposit(pat::PfChargedAllIso)->depositAndCountWithin(0.3, vetos_ch).first;
//
    Leptons.puChIso[Leptons.Size] = it_el->puChargedHadronIso();
    Leptons.AllIso[Leptons.Size] = it_el->particleIso();

    Leptons.AEff03[Leptons.Size] = AEff03;

    //simpleEleId status : (Add by Jacky)
    //0: fails
    //1: passes electron ID only
    //2: passes electron Isolation only
    //3: passes electron ID and Isolation only
    //4: passes conversion rejection
    //5: passes conversion rejection and ID
    //6: passes conversion rejection and Isolation
    //7: passes the whole selection
//      Leptons.simpleEleId95relIso[Leptons.Size] = it_el->electronID("simpleEleId95relIso");
//      Leptons.simpleEleId90relIso[Leptons.Size] = it_el->electronID("simpleEleId90relIso");
//      Leptons.simpleEleId85relIso[Leptons.Size] = it_el->electronID("simpleEleId85relIso");
//      Leptons.simpleEleId80relIso[Leptons.Size] = it_el->electronID("simpleEleId80relIso");
//      Leptons.simpleEleId70relIso[Leptons.Size] = it_el->electronID("simpleEleId70relIso");
//      Leptons.simpleEleId60relIso[Leptons.Size] = it_el->electronID("simpleEleId60relIso");
//      Leptons.simpleEleId95cIso  [Leptons.Size] = it_el->electronID("simpleEleId95cIso");
//      Leptons.simpleEleId90cIso  [Leptons.Size] = it_el->electronID("simpleEleId90cIso");
//      Leptons.simpleEleId85cIso  [Leptons.Size] = it_el->electronID("simpleEleId85cIso");
//      Leptons.simpleEleId80cIso  [Leptons.Size] = it_el->electronID("simpleEleId80cIso");
//      Leptons.simpleEleId70cIso  [Leptons.Size] = it_el->electronID("simpleEleId70cIso");
//      Leptons.simpleEleId60cIso  [Leptons.Size] = it_el->electronID("simpleEleId60cIso");
     
    //
//     EID -- CIC 
//     0 - no cut passed
//     1 - eID cuts passed
//     2 - iso cuts passed
//     4 - conversion rejection
//     8 - ip cut
//     Below three examples to check eId results:
//     eID+Iso+ConversionRejection+IP -> ((eIDmap[electronRef] &15) == 15)
//     Iso only -> ((eIDmap[electronRef] & 2) == 2)
//     eID+ConversionRejection+IP -> ((eIDmap[electronRef] & 13) == 13)
     //
     //CIC without ISO
//       Leptons.eidVeryLoose[Leptons.Size] = it_el->electronID("eidVeryLoose");
//       Leptons.eidLoose[Leptons.Size] = it_el->electronID("eidLoose");
//       Leptons.eidMedium[Leptons.Size] = it_el->electronID("eidMedium");
//       Leptons.eidTight[Leptons.Size] = it_el->electronID("eidTight");
//       Leptons.eidSuperTight[Leptons.Size] = it_el->electronID("eidSuperTight");
//       Leptons.eidHyperTight1[Leptons.Size] = it_el->electronID("eidHyperTight1");
//       Leptons.eidHyperTight2[Leptons.Size] = it_el->electronID("eidHyperTight2");
//       Leptons.eidHyperTight3[Leptons.Size] = it_el->electronID("eidHyperTight3");
//       Leptons.eidHyperTight4[Leptons.Size] = it_el->electronID("eidHyperTight4");

    // CIC with ISO
      // Leptons.eidVeryLooseMC[Leptons.Size] = it_el->userFloat("vidVeto");
      // Leptons.eidLooseMC[Leptons.Size] = it_el->userFloat("vidLoose");
      // Leptons.eidMediumMC[Leptons.Size] = it_el->userFloat("vidMedium");
      // Leptons.eidTightMC[Leptons.Size] = it_el->userFloat("vidTight");
      // Leptons.eidSuperTightMC[Leptons.Size] = it_el->userFloat("vidHEEP");
      Leptons.eidVeryLooseMC[Leptons.Size] = it_el->electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-veto");
      Leptons.eidLooseMC[Leptons.Size] = it_el->electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose");
      Leptons.eidMediumMC[Leptons.Size] = it_el->electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-medium");
      Leptons.eidTightMC[Leptons.Size] = it_el->electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-tight");

    // Leptons.eidVeryLooseMC[Leptons.Size] = it_el->electronID("eidVeryLooseMC");
    // Leptons.eidLooseMC[Leptons.Size] = it_el->electronID("eidLooseMC");
    // Leptons.eidMediumMC[Leptons.Size] = it_el->electronID("eidMediumMC");
    // Leptons.eidTightMC[Leptons.Size] = it_el->electronID("eidTightMC");
    // Leptons.eidSuperTightMC[Leptons.Size] = it_el->electronID("eidSuperTightMC");
    // Leptons.eidHyperTight1MC[Leptons.Size] = it_el->electronID("eidHyperTight1MC");
    // Leptons.eidHyperTight2MC[Leptons.Size] = it_el->electronID("eidHyperTight2MC");
    // Leptons.eidHyperTight3MC[Leptons.Size] = it_el->electronID("eidHyperTight3MC");
    
    // Leptons.eidHyperTight4MC[Leptons.Size] = it_el->electronID("eidHyperTight4MC");

    // Conversion rejection (Version2).               
    ////
//       ConversionFinder convFinder;
//       ConversionInfo convInfo = convFinder.getConversionInfo(*it_el,
// 							     tracks_h,
// 							     evt_bField);

//       Leptons.Eldist             [Leptons.Size] = convInfo.dist();
//       Leptons.Eldcot             [Leptons.Size] = convInfo.dcot();
//       Leptons.Elconvradius       [Leptons.Size] = convInfo.radiusOfConversion();
//       Leptons.ElConvPoint_x      [Leptons.Size] = convInfo.pointOfConversion().x();
//       Leptons.ElConvPoint_y      [Leptons.Size] = convInfo.pointOfConversion().y();
//       Leptons.ElConvPoint_z      [Leptons.Size] = convInfo.pointOfConversion().z();
    ////

    // For CIC (CutBasedElectronID.cc) First check electron categories from CutBasedElectronID.cc
    float dist_ = (it_el->convDist() == -9999.? 9999:it_el->convDist());
    float dcot_ = (it_el->convDcot() == -9999.? 9999:it_el->convDcot());
    Leptons.dcotdist[Leptons.Size] =((0.04 - std::max(fabs(dist_), fabs(dcot_))) > 0?(0.04 - std::max(fabs(dist_), fabs(dcot_))):0);
    Leptons.ElseedEoverP[Leptons.Size] = it_el->eSeedClusterOverP();
    Leptons.ElHcalIso04[Leptons.Size]  = it_el->dr04HcalTowerSumEt();
    // ElTrackDxy_PVBS for ip_gsf
    Leptons.ElEcalIso04[Leptons.Size]  = it_el->dr04EcalRecHitSumEt();
    // iso_sumoet = iso_sum*(40./scEt);

//========================================YH 2012-08-15==================================================

    Leptons.ElepassConversionVeto  [Leptons.Size]  = it_el->passConversionVeto();
    Leptons.ElesuperClusterEta     [Leptons.Size]  = it_el->superCluster()->eta();
    // Leptons.ElemvaTrigV0           [Leptons.Size]  = it_el->electronID("mvaTrigV0");
    // Leptons.ElemvaNTrigV0           [Leptons.Size] = it_el->electronID("mvaNonTrigV0");
    // Leptons.ElemvaTrigV0           [Leptons.Size]  = it_el->electronID("mvaEleID-Spring15-25ns-Trig-V1-wp80");
    // Leptons.ElemvaNTrigV0           [Leptons.Size] = it_el->electronID("mvaEleID-Spring15-25ns-Trig-V1-wp90");
    Leptons.ElemvaTrigV0           [Leptons.Size]  = it_el->electronID("mvaEleID-Spring15-25ns-nonTrig-V1-wp80");
    Leptons.ElemvaNTrigV0           [Leptons.Size] = it_el->electronID("mvaEleID-Spring15-25ns-nonTrig-V1-wp90");
    Leptons.EletrackMomentumAtVtxp [Leptons.Size]  = it_el->trackMomentumAtVtx().R();
    Leptons.EleecalEnergy          [Leptons.Size]  = it_el->ecalEnergy();
    Leptons.EleeSuperClusterOverP  [Leptons.Size]  = it_el->eSuperClusterOverP();
    Leptons.Elefbrem               [Leptons.Size]  = it_el->fbrem();
    Leptons.EleHoverE              [Leptons.Size]  = it_el->hadronicOverEm();
    Leptons.ElesigmaIetaIeta       [Leptons.Size]  = it_el->sigmaIetaIeta();
    Leptons.EledeltaPhiVtx         [Leptons.Size]  = it_el->deltaPhiSuperClusterTrackAtVtx();
    Leptons.EledeltaEtaVtx         [Leptons.Size]  = it_el->deltaEtaSuperClusterTrackAtVtx();
    //      Leptons.EleExpnumberOfHits     [Leptons.Size]  = it_el->gsfTrack()->trackerExpectedHitsInner().numberOfHits();
    
    Leptons.Size++;
  }

   // *********************************************************************************
   // PFJets
   // *********************************************************************************

   memset(&Jets,0x00,sizeof(Jets));

   //Jet ID for PFJet
   edm::ParameterSet PS_pf;
   PS_pf.addParameter<std::string>("version", "FIRSTDATA");
   PS_pf.addParameter<std::string>("quality", "LOOSE");
   PFJetIDSelectionFunctor pfjetIDLOOSE(PS_pf);
   strbitset pfret = pfjetIDLOOSE.getBitTemplate();
   
   // For Jet Uncertainty
   //JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty("START53_V18PR_Uncertainty_AK5PF.txt");
   //JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty("FT_R_53_V6_Uncertainty_AK5PF.txt");
   
   //JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(*(new JetCorrectorParameters("Summer15_25nsV3M3_DATA_UncertaintySources_AK4PFchs.txt", "Total")));
   //   JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty("Summer13_V5_MC_Uncertainty_AK5PF.txt");
  //JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty("Summer13_V5_DATA_Uncertainty_AK5PF.txt");

   //
   //std::string mPayloadName("AK5PF");
   edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
   //iSetup.get<JetCorrectionsRecord>().get(mPayloadName,JetCorParColl);
   iSetup.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
   JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
   JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar);
//

   for(std::vector<pat::Jet>::const_iterator it_jet = JetHandle->begin();
       it_jet != JetHandle->end(); it_jet++ ){ 
     if (Jets.Size>=MAX_JETS) {
       fprintf(stderr,"ERROR: number of jets exceeds the size of array.\n");
       break;//exit(0);
     }

     if (it_jet->pt()<=15.) continue; // IMPORTANT: Only book jet with pt>15 GeV. 

     Jets.Index       [Jets.Size] = Jets.Size;
     Jets.NTracks     [Jets.Size] = it_jet->associatedTracks().size();
     Jets.Eta         [Jets.Size] = it_jet->eta();
     
     Jets.Pt          [Jets.Size] = it_jet->pt();
     Jets.Et          [Jets.Size] = it_jet->et();
     

     jecUnc->setJetEta(it_jet->eta());
     jecUnc->setJetPt(it_jet->pt()); // here you must use the CORRECTED jet pt

//     if(fabs(it_jet->eta())<=3.0)
//       Jets.Unc[Jets.Size] = jecUnc->getUncertainty(true);       
     
     Jets.Phi         [Jets.Size] = it_jet->phi();
     Jets.JetCharge   [Jets.Size] = it_jet->jetCharge();
     Jets.NConstituents[Jets.Size] = it_jet->numberOfDaughters();
     
     Jets.Px          [Jets.Size] = it_jet->px(); //Uly 2011-04-04
     Jets.Py          [Jets.Size] = it_jet->py(); //Uly 2011-04-04
     Jets.Pz          [Jets.Size] = it_jet->pz(); //Uly 2011-04-04
     Jets.Energy      [Jets.Size] = it_jet->energy(); //Uly 2011-04-04

     pfret.set(false);
     bool JetID = pfjetIDLOOSE(*it_jet, pfret);
     Jets.JetIDLOOSE[Jets.Size] = (JetID) ?  1 : 0;

     // fill jet-vertex association

     double tracks_x = 0.;
     double tracks_y = 0.;
     double tracks_x_tot = 0.;
     double tracks_y_tot = 0.;
          
     const reco::TrackRefVector& TrackCol = it_jet->associatedTracks();
     for (reco::TrackRefVector::const_iterator it = TrackCol.begin();
	  it != TrackCol.end (); it++){      
       tracks_x_tot += (*it)->px();
       tracks_y_tot += (*it)->py();     
       if (fabs((*it)->vz()-Signal_Vz) < 0.1){                
	 tracks_x += (*it)->px();
	 tracks_y += (*it)->py();            
       }
     }

      Jets.JVAlpha[Jets.Size] = sqrt(tracks_x*tracks_x+tracks_y*tracks_y)/it_jet->pt();
      if (tracks_x_tot!=0. || tracks_y_tot!=0.) 
      {
         Jets.JVBeta[Jets.Size] = sqrt(tracks_x*tracks_x+tracks_y*tracks_y)/sqrt(tracks_x_tot*tracks_x_tot+tracks_y_tot*tracks_y_tot);
      } else {
         Jets.JVBeta[Jets.Size] = -1.;
      }

      // Jet corrections, B-tagging, and Jet ID information
      // now we just fill everything (regardless of availability)
      Jets.PtCorrRaw   [Jets.Size] = it_jet->correctedJet("Uncorrected"       ).pt();
      Jets.PtCorrL2    [Jets.Size] = it_jet->correctedJet("L2Relative"        ).pt(); // L2(rel) 
      Jets.PtCorrL3    [Jets.Size] = it_jet->correctedJet("L3Absolute"        ).pt(); // L3(abs) 

//L7 correction
//      Jets.PtCorrL7g   [Jets.Size] = it_jet->correctedJet("L7Parton", "gluon" ).pt(); // L7(gluon)
//      Jets.PtCorrL7uds [Jets.Size] = it_jet->correctedJet("L7Parton", "uds"   ).pt(); // L7(uds-jet) 
//      Jets.PtCorrL7c   [Jets.Size] = it_jet->correctedJet("L7Parton", "charm" ).pt(); // L7(c-jet)  
//      Jets.PtCorrL7b   [Jets.Size] = it_jet->correctedJet("L7Parton", "bottom").pt(); // L7(b-jet) 
//
//      Jets.ECorrL7g   [Jets.Size] = it_jet->correctedJet("L7Parton", "gluon" ).energy(); // L7(gluon)
//      Jets.ECorrL7uds [Jets.Size] = it_jet->correctedJet("L7Parton", "uds"   ).energy(); // L7(uds-jet) 
//      Jets.ECorrL7c   [Jets.Size] = it_jet->correctedJet("L7Parton", "charm" ).energy(); // L7(c-jet)  
//      Jets.ECorrL7b   [Jets.Size] = it_jet->correctedJet("L7Parton", "bottom").energy(); // L7(b-jet) 


      // Jets.JetBProbBJetTags        [Jets.Size] = it_jet->bDiscriminator("jetBProbabilityBJetTags");
      // Jets.JetProbBJetTags         [Jets.Size] = it_jet->bDiscriminator("jetProbabilityBJetTags");
      // Jets.TrackCountHiPurBJetTags [Jets.Size] = it_jet->bDiscriminator("trackCountingHighPurBJetTags"); 
      // Jets.TrackCountHiEffBJetTags [Jets.Size] = it_jet->bDiscriminator("trackCountingHighEffBJetTags");
      // //Jets.ImpactParaMVABJetTags   [Jets.Size] = it_jet->bDiscriminator("impactParameterMVABJetTags"); //remove by Chiyi
      // Jets.SimpleSVBJetTags        [Jets.Size] = it_jet->bDiscriminator("simpleSecondaryVertexBJetTags");
      // Jets.SimpleSVBJetTags        [Jets.Size] = it_jet->bDiscriminator("simpleSecondaryVertexBJetTags"); //for 35X sample
      // Jets.SimpleSVHEBJetTags      [Jets.Size] = it_jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags"); //for 36X
      // Jets.SimpleSVHPBJetTags      [Jets.Size] = it_jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags"); //for 36X
      // Jets.CombinedSVBJetTags      [Jets.Size] = it_jet->bDiscriminator("combinedSecondaryVertexBJetTags");
      // Jets.CombinedSVMVABJetTags   [Jets.Size] = it_jet->bDiscriminator("combinedSecondaryVertexMVABJetTags");
      // Jets.SoftElecByIP3dBJetTags  [Jets.Size] = it_jet->bDiscriminator("softElectronByIP3dBJetTags");
      // Jets.SoftElecByPtBJetTags    [Jets.Size] = it_jet->bDiscriminator("softElectronByPtBJetTags");
      // Jets.SoftMuonBJetTags        [Jets.Size] = it_jet->bDiscriminator("softMuonBJetTags");
      // Jets.SoftMuonByIP3dBJetTags  [Jets.Size] = it_jet->bDiscriminator("softMuonByIP3dBJetTags");
      // Jets.SoftMuonByPtBJetTags    [Jets.Size] = it_jet->bDiscriminator("softMuonByPtBJetTags");
      Jets.JetBProbBJetTags        [Jets.Size] = it_jet->bDiscriminator("pfJetBProbabilityBJetTags");
      Jets.JetProbBJetTags         [Jets.Size] = it_jet->bDiscriminator("pfJetProbabilityBJetTags");
      Jets.TrackCountHiPurBJetTags [Jets.Size] = it_jet->bDiscriminator("pfTrackCountingHighPurBJetTags"); 
      Jets.TrackCountHiEffBJetTags [Jets.Size] = it_jet->bDiscriminator("pfTrackCountingHighEffBJetTags");
      Jets.SimpleSVHEBJetTags      [Jets.Size] = it_jet->bDiscriminator("pfSimpleSecondaryVertexHighEffBJetTags");
      Jets.SimpleSVHPBJetTags      [Jets.Size] = it_jet->bDiscriminator("pfSimpleSecondaryVertexHighPurBJetTags");
      Jets.CombinedSVBJetTags      [Jets.Size] = it_jet->bDiscriminator("pfCombinedSecondaryVertexV2BJetTags");
      Jets.CombinedIncSVBJetTags   [Jets.Size] = it_jet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
      Jets.CombinedSVMVABJetTags   [Jets.Size] = it_jet->bDiscriminator("pfCombinedMVABJetTags");
      Jets.CombinedSVSoftLBJetTags [Jets.Size] = it_jet->bDiscriminator("pfCombinedSecondaryVertexSoftLeptonBJetTags");
      Jets.CombinedCvsLJetTags     [Jets.Size] = it_jet->bDiscriminator("pfCombinedCvsLJetTags");
      Jets.CombinedCvsBJetTags     [Jets.Size] = it_jet->bDiscriminator("pfCombinedCvsBJetTags");

      if(!isData){
	const reco::GenJet * genjet = it_jet->genJet();
	if(genjet!=NULL) {
	  Jets.GenJetPt  [Jets.Size] = genjet->pt();
	  Jets.GenJetEta [Jets.Size] = genjet->eta();
	  Jets.GenJetPhi [Jets.Size] = genjet->phi();
	} 

	const reco::GenParticle* parton = it_jet->genParton();
	if(parton!=NULL){
	  Jets.GenPt     [Jets.Size] = parton->pt();
	  Jets.GenEta    [Jets.Size] = parton->eta();
	  Jets.GenPhi    [Jets.Size] = parton->phi();
	  Jets.GenPdgID  [Jets.Size] = parton->pdgId();
	  Jets.GenFlavor [Jets.Size] = it_jet->partonFlavour();
	  
	  //const reco::Candidate* genCand = parton;
	}
      } // no data

      //Jets.CandRef [Jets.Size] = (reco::Candidate*)&(*it_jet);
      Jets.Size++;
   }

   memset(&GenParts,0x00,sizeof(GenParts));
   memset(&EvtInfo,0x00,sizeof(EvtInfo));
      
   EvtInfo.RunNo  = iEvent.id().run();
   EvtInfo.EvtNo  = iEvent.id().event();
   EvtInfo.McFlag = iEvent.isRealData()? 0: 1;  
   EvtInfo.BxNo   = iEvent.bunchCrossing();
   EvtInfo.LumiNo = iEvent.luminosityBlock();

   EvtInfo.Orbit  = iEvent.orbitNumber();

   //EvtInfo.SigmaPU = *(sigmaHandle.product());
   
   EvtInfo.rhoIso = *(rhoIsoHandle.product());

   // MC daughters: 0-1: hard jet from b'bar/t'bar, 2-9: W daughters, 10-13: Z daughters

   vector<const reco::Candidate *> cands;
   vector<const Candidate *>::const_iterator found = cands.begin();
   
   // const reco::Candidate* MCDaughters[14];
   // for(int i=0;i<14;i++) MCDaughters[i] = NULL;
   
   if(!isData){
     GenParts.Size=0;
     for( std::vector<reco::GenParticle>::const_iterator it_gen =
	    GenHandle->begin(); it_gen != GenHandle->end(); it_gen++ ){
       cands.push_back(&*it_gen);
     }

     // PileupSummaryInfo
     Handle<std::vector< PileupSummaryInfo > >  PUInfo;
     iEvent.getByLabel(puInfoLabel_, PUInfo);
     std::vector<PileupSummaryInfo>::const_iterator PVI;
     
     for(PVI = PUInfo->begin(); PVI != PUInfo->end(); ++PVI) {
       EvtInfo.nPU[EvtInfo.nBX] = PVI->getPU_NumInteractions();
       EvtInfo.nTPU[EvtInfo.nBX] = PVI->getTrueNumInteractions();
       EvtInfo.BXPU[EvtInfo.nBX] = PVI->getBunchCrossing();
       //cout << " Pileup Information: bunchXing, nvtx: " 
       //<< PVI->getBunchCrossing() << " " << PVI->getPU_NumInteractions()
       //<< endl;
       EvtInfo.nBX += 1;
     }
     
     for( std::vector<reco::GenParticle>::const_iterator it_gen =
            GenHandle->begin(); it_gen != GenHandle->end() &&
            GenParts.Size < MAX_GENPARTS; it_gen++ ){
// 	  int numberOfDaughters = it_gen->numberOfDaughters();
// 	  int numberOfMothers = it_gen->numberOfMothers();
// 	  int dauId1 = 0,dauId2 = 0,monId = 0;
// 	  const reco::Candidate* dau1 = NULL;
// 	  const reco::Candidate* dau2 = NULL;
	  
       // Particles Mothers and Daighters
       int iMo1 = -1;
       int iMo2 = -1;
       int iDa1 = -1;
       int iDa2 = -1;
       int NMo = it_gen->numberOfMothers();
       int NDa = it_gen->numberOfDaughters();
	 
       // if(it_gen->status() == 3){     //Book GenParts for DC table
         found = find(cands.begin(), cands.end(), it_gen->mother(0));
         if(found != cands.end()) iMo1 = found - cands.begin() ;
         if(iMo1>GenParts.Size) iMo1 = 0;
         
         found = find(cands.begin(), cands.end(), it_gen->mother(1));
         if(found != cands.end()) iMo2 = found - cands.begin() ;
	 
         found = find(cands.begin(), cands.end(), it_gen->daughter(0));
         if(found != cands.end()) iDa1 = found - cands.begin() ;
         
         found = find(cands.begin(), cands.end(), it_gen->daughter(1));
         if(found != cands.end()) iDa2 = found - cands.begin() ;
       // }
       if((it_gen-GenHandle->begin())>=128 && it_gen->status()>=30)
         continue;

       GenParts.Index[GenParts.Size]         = it_gen - GenHandle->begin();
       GenParts.Pt[GenParts.Size]            = it_gen->pt();
       GenParts.Eta[GenParts.Size]           = it_gen->eta();
       GenParts.Phi[GenParts.Size]           = it_gen->phi();
       GenParts.Mass[GenParts.Size]          = it_gen->mass();
       GenParts.PdgID[GenParts.Size]         = it_gen->pdgId();
       GenParts.Status[GenParts.Size]        = it_gen->status();
       GenParts.Mo1[GenParts.Size]           = iMo1; 
       GenParts.Mo2[GenParts.Size]           = iMo2; 
       GenParts.Da1[GenParts.Size]           = iDa1; 
       GenParts.Da2[GenParts.Size]           = iDa2; 
       GenParts.nMo[GenParts.Size]           = NMo;
       GenParts.nDa[GenParts.Size]           = NDa; 
      
       GenParts.Size++;
     }

     //std::cout << "Processing MC... " << GenParts.Size << std::endl;
   }  //not data

   for(std::vector<pat::MET>::const_iterator it_patmet =METHandle->begin();
   //for(std::vector<reco::PFMET>::const_iterator it_patmet =METHandle->begin();
       it_patmet != METHandle->end(); it_patmet++ ){
     
     EvtInfo.MET           = it_patmet->pt();
     EvtInfo.METPhi        = it_patmet->phi();
     // EvtInfo.RawMET        = it_patmet->uncorPt();
     // EvtInfo.RawMETPhi     = it_patmet->uncorPhi();
     
     EvtInfo.METx          = it_patmet->px(); //Uly 2011-04-04
     EvtInfo.METy          = it_patmet->py(); //Uly 2011-04-04
     
     EvtInfo.SumEt           = it_patmet->sumEt();
     EvtInfo.METSig        = it_patmet->mEtSig();
     
     // const reco::GenMET * genmet = it_patmet->genMET();
     // if (genmet!=NULL) {
     //   EvtInfo.GenMET        = genmet->pt();
     //   EvtInfo.GenMETPhi     = genmet->phi();
     // }
   } // MET

   edm::Handle<GenEventInfoProduct> GenEventInfoHandle;  
   bool with_GenEventInfo = iEvent.getByLabel(genevtlabel_,
					      GenEventInfoHandle);

   if(with_GenEventInfo && GenEventInfoHandle->hasPDF()) {
     EvtInfo.PDFid1   = GenEventInfoHandle->pdf()->id.first;
     EvtInfo.PDFid2   = GenEventInfoHandle->pdf()->id.second;
     EvtInfo.PDFx1    = GenEventInfoHandle->pdf()->x.first;
     EvtInfo.PDFx2    = GenEventInfoHandle->pdf()->x.second;
     EvtInfo.PDFscale = GenEventInfoHandle->pdf()->scalePDF;
     EvtInfo.PDFv1    = GenEventInfoHandle->pdf()->xPDF.first;
     EvtInfo.PDFv2    = GenEventInfoHandle->pdf()->xPDF.second;

     EvtInfo.Weight   = GenEventInfoHandle->weight();
   }

   // HLT: Booking trigger bits  
   edm::Handle<TriggerResults> TrgResultsHandle;
   bool with_TriggerResults = iEvent.getByLabel(hltlabel_,TrgResultsHandle);
   if (with_TriggerResults){
     const edm::TriggerNames & TrgNames =
       iEvent.triggerNames(*TrgResultsHandle);
     EvtInfo.TrgCount = 0;
     
     EvtInfo.nBooking=N_TRIGGER_BOOKINGS;
     EvtInfo.nHLT = TrgNames.size();
     for(int i=0; i<N_TRIGGER_BOOKINGS; i++) {
       unsigned int TrgIndex = TrgNames.triggerIndex( TriggerBooking[i] );
       
       if (TrgIndex == TrgNames.size()) {
	 EvtInfo.TrgBook[i] = -4; // The trigger path is not known in this event.
       }else if ( !TrgResultsHandle->wasrun( TrgIndex ) ) {
	 EvtInfo.TrgBook[i] = -3; // The trigger path was not included in this event.
       }else if ( !TrgResultsHandle->accept( TrgIndex ) ) {
	 EvtInfo.TrgBook[i] = -2; // The trigger path was not accepted in this event.
       }else if (  TrgResultsHandle->error ( TrgIndex ) ) {
	 EvtInfo.TrgBook[i] = -1; // The trigger path has an error in this event.
       }else {
	 EvtInfo.TrgBook[i] = +1; // It's triggered.
	 EvtInfo.TrgCount++; 
       }
     }  

     for(unsigned int i=0; i<TrgNames.size();i++){
       EvtInfo.HLTbits[i] = (TrgResultsHandle->accept(i) == true) ? 1:0;
       // Print out Trigger table
       //std::cout << "trigger path= " << TrgNames.triggerName(i) << std::endl;
     }
   }
   
   
   /// **********************************************************
   //   L1 trigger and techincal trigger bits
   // ***********************************************************
   edm::Handle< L1GlobalTriggerReadoutRecord > gtRecord;
   iEvent.getByLabel( gtdigilabel_, gtRecord);
   
   DecisionWord dWord = gtRecord->decisionWord();
   if ( ! dWord.empty() ) { // if board not there this is zero
     // loop over dec. bit to get total rate (no overlap)
     //if(debug) cout << "Trigger Path ";
     for ( int i = 0; i < 128; ++i ) {
       //     if(dWord[i]!=0 && debug)cout << i << " " << dWord[i] << ": ";
       EvtInfo.L1[i]=dWord[i];
     }
     //if(debug) cout << endl;
   }
   TechnicalTriggerWord tw = gtRecord->technicalTriggerWord();
   if ( ! tw.empty() ) {
     // loop over dec. bit to get total rate (no overlap)
     //if(debug) cout << "Tech Trigger Path ";
     for ( int i = 0; i < 64; ++i ) {
       //     if(tw[i]!=0 && debug) cout << i << "  " << tw[i] << ": ";
       EvtInfo.TT[i]=tw[i];
     }
     //if(debug) cout << endl; 
   }  

   myTree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
MyFCNCkit::beginJob(){
  myTree = new TTree("root","My FCNC Top Tree");
  EvtInfo.setBranch(myTree);  
  GenParts.setBranch(myTree);  
  Leptons.setBranch(myTree);
  VtxInfo.setBranch(myTree);
  Jets.setBranch(myTree);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyFCNCkit::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MyFCNCkit::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MyFCNCkit::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MyFCNCkit::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MyFCNCkit::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyFCNCkit::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
