#define MyTcZAna_cxx
// The class definition in MyTcZAna.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("MyTcZAna.C")
// root> T->Process("MyTcZAna.C","some options")
// root> T->Process("MyTcZAna.C+")
//

#include "MyTcZAna.h"
#include <TH2.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TLorentzVector.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "TriggerBooking.h"
#define N_TRIGGER_BOOKINGS      5790

#define MASS_Z0 91.1870
#define MASS_W 80.33000

#define VTX_NDOF_CUT 4
#define VTX_SUMPT_CUT 0.
#define VTX_ABSZ_CUT 24.
#define VTX_RHO_CUT 2.

#define ELE_PT_CUT  30  //20.before 30.group 
#define ELE_PT_CUT_Veto  10
#define ELE_ETA_CUT 2.5 //2.5.group
#define ELE_ETA_CUT_Veto 2.5 //2.5.group
#define ElTrackDxy 0.04 //Transverse IP of the elecrtron
#define ELE_MVA_CUT 0.9 //MVA : electron.electronID("mvaTrigV0"); > 0.5(or 0.9)
#define ELE_MVA_CUT_Veto_Lcut 0
#define ELE_MVA_CUT_Veto_Tcut 1
#define ELE_Track_CUT 0 // mHits
#define ELE_ISO_LB 0.15 //relIso (r=0.3) with Rho corrections
#define ELE_ISO_LCUT_Veto 0.15

#define MU_PT_CUT   26  //20.before 26.group 
#define MU_PT_CUT_Veto   10  //20.before 26.group 
#define MU_ETA_CUT  2.1 //2.4
#define MU_ETA_CUT_Veto  2.5 //2.4
#define MU_ISO_LCUT 0.15
#define MU_ISO_LCUT_Veto 0.2
#define MU_Tracker_CUT 5
#define MU_GlobeTracker_CUT 0
#define MU_InnerTrack_CUT 0
#define MU_MatchedStations_CUT 1
#define MU_VertexZ_CUT 0.5

#define LEP_ISO_LB 0.1 
#define LEP_ISO_LCUT 0.2
#define LEP_ISO_TCUT 0.2

#define Z_MASS_LCUT 30.   // 78
#define Z_MASS_HCUT 150.   // 102

#define TZ_MASS_LCUT 80.
#define TZ_MASS_HCUT 100.

#define ZZ_MASS_LCUT 30.
#define ZZ_MASS_HCUT 150.

#define W_MT_LCUT 0.   //  65
#define W_MT_HCUT 525.   //  290

#define MET_CUT 30.

#define JET_PT_CUT 30. 
#define JET_PT_CUT_1 55.
#define JET_PT_CUT_2 45.
#define JET_PT_CUT_3 35.
#define JET_PT_CUT_4up 30.
#define JET_ETA_CUT 2.4
#define JET_BTAG_CUT 0.679 //CSVL 0.244 ;CSVM 0.679  ;CSVT 0.898
#define JET_CBTAG_CUT 0. //c-tag c vs. b
#define JET_NUMBER_CUT 4  //jet number least at 4
#define JET_BJETNO_CUT 3 //bjet number cut

#define HT_S_LCUT 250.
#define HT_S_HCUT 1860.

#define NoRhoCorr 0

#define JES_UNC 0.0
// #define JES_UNC 1.0
// #define JES_UNC -1.0

 #define JER_UNC 0.0
// #define JER_UNC 1.0
// #define JER_UNC -1.0
 
 #define JEM_UNC 0.0
// #define JEM_UNC 1.0
// #define JEM_UNC -1.0

 #define SFM_UNC 0.0
// #define SFM_UNC 1.0
// #define SFM_UNC -1.0

 #define SFE_UNC 0.0
// #define SFE_UNC 1.0
// #define SFE_UNC -1.0

 #define SFM_UNC_I 0.0
// #define SFM_UNC_I 1.0
// #define SFM_UNC_I -1.0

 #define SFE_UNC_I 0.0
// #define SFE_UNC_I 1.0
// #define SFE_UNC_I -1.0

 #define ToppT_UNC 0.0
// #define ToppT_UNC 1.0
// #define ToppT_UNC -1.0

 #define TTbb_UNC 0.0
// #define TTbb_UNC 1.0
// #define TTbb_UNC -1.0

 #define TTcc_UNC 0.0
// #define TTcc_UNC 1.0
// #define TTcc_UNC -1.0
 
 #define METue_UNC 0.0
// #define METue_UNC 1.0
// #define METue_UNC -1.0

void MyTcZAna::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

  //..Histogram definitions
   cout << "MyTcZAna... begin!\n";
   cout << "   options: " << option << endl;


   Event_Weight=1.0;
   Event_Weight_Tot=0;
   Event_Tot=0;

}

void MyTcZAna::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // Definition of histograms
   hist_evt_cut = new TH1D("hist_evt_cut","Event selection cuts", 25, 0, 25);
   hist_evt_cut_e = new TH1D("hist_evt_cut_e","Event selection cuts", 25, 0, 25);
   hist_evt_cut_m = new TH1D("hist_evt_cut_m","Event selection cuts", 25, 0, 25);
   hist_ele_cut = new TH1D("hist_ele_cut","Eletron selection cuts", 20, 0, 20);
   hist_mu_cut = new TH1D("hist_mu_cut","Muon selection cuts", 20, 0, 20);
   hist_jet_cut = new TH1D("hist_jet_cut","Jet selection cuts", 25, 0, 25);


   hist_vtx_no = new TH1D("hist_vtx_no","No. of vtx",50,0,50);
   // hist_vtx_no_AS = new TH1D("hist_vtx_no_AS","No. of vtx",50,0,50);
   // hist_vtx_no_AS_nPU = new TH1D("hist_vtx_no_AS without PU","No. of vtx",50,0,50);
   hist_vtx_ndof = new TH1D("hist_vtx_ndof","No. of vtx DoF",100, 0, 350);
   // hist_vtx_ndof_AS = new TH1D("hist_vtx_ndof_AS","No. of vtx DoF",100, 0, 350);
   hist_vtx_nx2 = new TH1D("hist_vtx_nx2","Norm. #chi^2",100, 0, 5);
   hist_vtx_ptsum = new TH1D("hist_vtx_ptsum","p_{T} sum of vtx", 100, 0,1000);
   hist_vtx_z = new TH1D("hist_vtx_z","Vtx z position",100, -30, 30);
   hist_vtx_rho = new TH1D("hist_vtx_rho","Vtx rho position",100, -1, 1);
   hist_vtx_cut = new TH1D("hist_vtx_cut","Vtx selection cuts",10, 0, 10);

   hist_npu = new TH1D("hist_npu","# of pile-ups",80, 0, 80);
   hist_npu_raw = new TH1D("hist_npu_raw","# of pile-ups",80, 0, 80);

   hist_e_AEff = new TH1D("hist_e_AEff","e AEff",100,0,1);
   hist_m_AEff = new TH1D("hist_m_AEff","m AEff",100,0,1);
   hist_e_rho_AEff = new TH1D("hist_e_rho_AEff","e rho_AEff",400,0,20);
   hist_m_rho_AEff = new TH1D("hist_m_rho_AEff","m rho_AEff",400,0,20);
   hist_rho = new TH1D("hist_rho","rho",400,0,100);

   hist_e_pt = new TH1D("hist_e_pt","e p_{T}",100,0,200);
   hist_e_pt_AS = new TH1D("hist_e_pt_AS","e p_{T}",50,0,200);
   hist_e_eta = new TH1D("hist_e_eta","e #eta",100,-3.0,3.0);
   hist_e_eta_AS = new TH1D("hist_e_eta_AS","e #eta",50,-3.0,3.0);
   hist_e_phi = new TH1D("hist_e_phi","e #phi",100,-3.14,3.14);
   hist_e_phi_AS = new TH1D("hist_e_phi_AS","e #phi",50,-3.14,3.14);
   hist_e_iso = new TH1D("hist_e_iso","e Rel. Iso.",100,0.,0.25);
   hist_e_mva = new TH1D("hist_e_mva","e MVA",110,0.,1.1);
   hist_e_mva_no = new TH1D("hist_e_mva_no","NO. Ele MVA value is 0 or 1",10,0,10);

   hist_m_pt = new TH1D("hist_m_pt","#mu p_{T}",100,0,200);
   hist_m_pt_AS = new TH1D("hist_m_pt_AS","#mu p_{T}",50,0,200);
   hist_m_eta = new TH1D("hist_m_eta","#mu #eta",100,-3.0,3.0);
   hist_m_eta_AS = new TH1D("hist_m_eta_AS","#mu #eta",50,-3.0,3.0);
   hist_m_phi = new TH1D("hist_m_phi","#mu #phi",100,-3.14,3.14);
   hist_m_phi_AS = new TH1D("hist_m_phi_AS","#mu #phi",50,-3.14,3.14);
   hist_m_iso = new TH1D("hist_m_iso","#mu Rel. Iso.",100,0.,0.25);
   hist_m_mva = new TH1D("hist_m_mva","#mu MVA",110,0.,1.1);

   hist_ge_pt = new TH1D("hist_ge_pt","GEN matched e p_{T}",100,0,200);
   hist_ge_eta = new TH1D("hist_ge_eta","GEN matched e #eta",100,-3.0,3.0);
   hist_ge_phi = new TH1D("hist_ge_phi","GEN matched e #phi",100,-3.14,3.14);

   hist_gm_pt = new TH1D("hist_gm_pt","GEN matched #mu p_{T}",100,0,200);
   hist_gm_eta = new TH1D("hist_gm_eta","GEN matched #mu #eta",100,-3.0,3.0);
   hist_gm_phi = new TH1D("hist_gm_phi","GEN matched #mu #phi",100,-3.14,3.14);

   hist_gel_pt = new TH1D("hist_gel_pt","GEN matched e p_{T}",100,0,200);
   hist_gel_eta = new TH1D("hist_gel_eta","GEN matched e #eta",100,-3.0,3.0);
   hist_gel_phi = new TH1D("hist_gel_phi","GEN matched e #phi",100,-3.14,3.14);

   hist_gml_pt = new TH1D("hist_gml_pt","GEN matched #mu p_{T}",100,0,200);
   hist_gml_eta = new TH1D("hist_gml_eta","GEN matched #mu #eta",100,-3.0,3.0);
   hist_gml_phi = new TH1D("hist_gml_phi","GEN matched #mu #phi",100,-3.14,3.14);
   hist_get_pt = new TH1D("hist_get_pt","GEN matched e p_{T}",100,0,200);
   hist_get_eta = new TH1D("hist_get_eta","GEN matched e #eta",100,-3.0,3.0);
   hist_get_phi = new TH1D("hist_get_phi","GEN matched e #phi",100,-3.14,3.14);

   hist_gmt_pt = new TH1D("hist_gmt_pt","GEN matched #mu p_{T}",100,0,200);
   hist_gmt_eta = new TH1D("hist_gmt_eta","GEN matched #mu #eta",100,-3.0,3.0);
   hist_gmt_phi = new TH1D("hist_gmt_phi","GEN matched #mu #phi",100,-3.14,3.14);

   hist_te_pt = new TH1D("hist_te_pt","tight e p_{T}",100,0,200);
   hist_te_eta = new TH1D("hist_te_eta","tight e #eta",100,-3.0,3.0);
   hist_te_phi = new TH1D("hist_te_phi","tight e #phi",100,-3.14,3.14);

   hist_tm_pt = new TH1D("hist_tm_pt","tight #mu p_{T}",100,0,200);
   hist_tm_eta = new TH1D("hist_tm_eta","tight #mu #eta",100,-3.0,3.0);
   hist_tm_phi = new TH1D("hist_tm_phi","tight #mu #phi",100,-3.14,3.14);

   hist_wen_m = new TH1D("hist_wen_m","invariant mass of W(e #nu)",50,0,250);
   hist_wmn_m = new TH1D("hist_wmn_m","invariant mass of W(#mu #nu)",50,0,250);
   hist_wen_m_2b = new TH1D("hist_wen_m_2b","invariant mass of W(e #nu)",50,0,250);
   hist_wmn_m_2b = new TH1D("hist_wmn_m_2b","invariant mass of W(#mu #nu)",50,0,250);
   hist_wen_m_3b = new TH1D("hist_wen_m_3b","invariant mass of W(e #nu)",50,0,250);
   hist_wmn_m_3b = new TH1D("hist_wmn_m_3b","invariant mass of W(#mu #nu)",50,0,250);
   hist_wen_mt = new TH1D("hist_wen_mt","transverse mass of W(e #nu)",50,0,250);
   hist_wmn_mt = new TH1D("hist_wmn_mt","transverse mass of W(#mu #nu)",50,0,250);
   hist_wen_mt_2b = new TH1D("hist_wen_mt_2b","transverse mass of W(e #nu)",50,0,250);
   hist_wmn_mt_2b = new TH1D("hist_wmn_mt_2b","transverse mass of W(#mu #nu)",50,0,250);
   hist_wen_mt_3b = new TH1D("hist_wen_mt_3b","transverse mass of W(e #nu)",50,0,250);
   hist_wmn_mt_3b = new TH1D("hist_wmn_mt_3b","transverse mass of W(#mu #nu)",50,0,250);
   hist_wen_gmt = new TH1D("hist_wen_gmt","trans. mass of gen W(e #nu)",50,0,250);
   hist_wmn_gmt = new TH1D("hist_wmn_gmt","trans. mass of gen W(#mu #nu)",50,0,250);
/*
   hist_w_wmt_h = new TH1D("hist_wen_wmt_h","transverse mass of W high pt",50,0,200);
   hist_w_wmt_l = new TH1D("hist_wmn_wmt_l","transverse mass of W low pt",50,0,200);
   hist_w_n = new TH1D("hist_w_n","No. of W candidates (e/#mu)",5,0,5);
   hist_wen_mt_met = new TH2D("hist_wen_mt_met","Mt of W(e #nu) vs. MET",50,0,150,50,0,100);
   hist_wmn_mt_met = new TH2D("hist_wmn_mt_met","Mt of W(#mu #nu) vs. MET",50,0,150,50,0,100);
*/
   hist_wen_pt = new TH1D("hist_wen_pt","p_{T} of W(e #nu)",50,0,250);
   hist_wmn_pt = new TH1D("hist_wmn_pt","p_{T} of W(#mu #nu)",50,0,250);
/*
   hist_wen_lpt = new TH1D("hist_wen_lpt","p_{T} of W(e)",100,0,200);
   hist_wmn_lpt = new TH1D("hist_wmn_lpt","p_{T} of W(#mu)",100,0,200);
   hist_wen_ldz = new TH1D("hist_wen_ldz","#Delta z of W(e)",100,-0.5,0.5);
   hist_wmn_ldz = new TH1D("hist_wmn_ldz","#Delta z of W(#mu)",100,-0.5,0.5);
*/
   hist_wen_no = new TH1D("hist_wen_no", "No. of W candidates (e)",5,0,5.);
   hist_wmn_no = new TH1D("hist_wmn_no", "No. of W candidates (#mu)",5,0,5.);
/*
   hist_wen_iso = new TH1D("hist_wen_iso","Trk iso. of W(e)",100,0,5.);
   hist_wmn_iso = new TH1D("hist_wmn_iso","Trk iso. of W(#mu)",100,0,5.);
*/
   hist_wen_mt_ee = new TH1D("hist_wen_mt_ee","transverse mass of W(e #nu)",50,0,250);
   hist_wen_mt_mm = new TH1D("hist_wen_mt_mm","transverse mass of W(e #nu)",50,0,250);
   hist_wmn_mt_ee = new TH1D("hist_wmn_mt_ee","transverse mass of W(#mu #nu)",50,0,250);
   hist_wmn_mt_mm = new TH1D("hist_wmn_mt_mm","transverse mass of W(#mu #nu)",50,0,250);

/*
   hist_wqq_m = new TH1D("hist_wqq_m","invariant mass of W(qq)",50,0,250);
   hist_wqq_mt = new TH1D("hist_wqq_mt","transverse mass of W(qq)",50,0,250);
   hist_wqq_pt = new TH1D("hist_wqq_pt","p_{T} of W(qq)",50,0,250);
   hist_wqq_gm = new TH1D("hist_wqq_gm","inv. mass of GEN W(qq)",50,0,250);
   hist_wqq_gmt = new TH1D("hist_wqq_gmt","trans. mass of GEN W(qq)",50,0,250);
   hist_wqq_gpt = new TH1D("hist_wqq_gpt","p_{T} of GEN W(qq)",50,0,250);
*/
   /*
   hist_wen_ltrk_ze = new TH1D("hist_w_ltrk_ze","Trk iso. of W Z(ee)",20,0,20.);
   hist_wmn_ltrk_zm = new TH1D("hist_w_ltrk_zm","Trk iso. of W Z(#mu#mu)",20,0,20.);
   hist_w_lecal_ze = new TH1D("hist_w_lecal_ze","ECal iso. of W Z(ee)",20,0,20.);
   hist_w_lecal_zm = new TH1D("hist_w_lecal_zm","ECal iso. of W Z(#mu#mu)",20,0,20.);
   hist_w_tiso_pt_e = new TH2D("hist_w_tiso_pt_e","iso. vs. pt of W(e)",20,0,10.,50,0,150);
   hist_w_tiso_pt_m = new TH2D("hist_w_tiso_pt_m","iso. vs. pt of W(#mu)",20,0,10.,50,0,150);
   hist_w_eiso_pt_e = new TH2D("hist_w_eiso_pt_e","iso. vs. pt of W(e)",20,0,10.,50,0,150);
   hist_w_eiso_pt_m = new TH2D("hist_w_eiso_pt_m","iso. vs. pt of W(#mu)",20,0,10.,50,0,150);
   hist_w_hiso_pt_e = new TH2D("hist_w_hiso_pt_e","iso. vs. pt of W(e)",20,0,10.,50,0,150);
   hist_w_hiso_pt_m = new TH2D("hist_w_hiso_pt_m","iso. vs. pt of W(#mu)",20,0,10.,50,0,150);
   */

   hist_zee_no = new TH1D("hist_zee_no","# of Z(ee)",10,0,10);
   hist_zmm_no = new TH1D("hist_zmm_no","# of Z(#mu#mu)",10,0,10);

   hist_zee_pt = new TH1D("hist_zee_pt","pt of Z(ee)",50,0,150);
   hist_zmm_pt = new TH1D("hist_zmm_pt","pt of Z(#mu#mu)",50,0,150);

   hist_zee_m = new TH1D("hist_zee_m","mass of Z(ee)",60,30,150);
   hist_zmm_m = new TH1D("hist_zmm_m","mass of Z(#mu#mu)",60,30,150);

   hist_e_no = new TH1D("hist_e_no", "No. of electons",10,0,10);
   hist_e_notest = new TH1D("hist_e_notest", "No. of electons test",10,0,10);
   hist_m_no = new TH1D("hist_m_no", "No. of muons",10,0,10);
   hist_lep_no = new TH1D("hist_lep_no", "No. of leptons",10,0,10);
   hist_wz_no = new TH1D("hist_wz_no", "No. of W+Z",5,0,5);

   hist_jet_pt = new TH1D("hist_jet_pt", "p_{T} of jet",50,0,150);
   hist_jet_pt_AS = new TH1D("hist_jet_pt_AS", "p_{T} of jet",50,0,150);
   hist_jet_eta = new TH1D("hist_jet_eta", "#eta of jet",100,-3.,3.);
   hist_jet_eta_AS = new TH1D("hist_jet_eta_AS", "#eta of jet",100,-3.,3.);
   hist_jet_phi = new TH1D("hist_jet_phi", "#phi of jet",100,-3.5,3.5);
   hist_jet_phi_AS = new TH1D("hist_jet_phi_AS", "#phi of jet",100,-3.5,3.5);
   hist_jet_btag = new TH1D("hist_jet_btag", "btag of jet",100,-2,2);
   hist_jet_btag_nob = new TH1D("hist_jet_btag_nob", "btag of jet (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_corr = new TH1D("hist_jet_btag_nob_corr", "btag of jet (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_b = new TH1D("hist_jet_btag_nob_b", "btag of b-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_b_corr = new TH1D("hist_jet_btag_nob_b_corr", "btag of of b-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_l = new TH1D("hist_jet_btag_nob_l", "btag of of light-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_l_corr = new TH1D("hist_jet_btag_nob_l_corr", "btag of of light-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_6 = new TH1D("hist_jet_btag_6", "btag of jet (ttjets) > 6jets + 3 btagged region",60,-0.1,1.1);
   hist_jet_btag_6_corr = new TH1D("hist_jet_btag_6_corr", "btag of jet (ttjets) > 6jets + 3 btagged region after correction",60,-0.1,1.1);
   hist_jet_btag_6_b = new TH1D("hist_jet_btag_6_b", "btag of b-jet flavor (ttjets) > 6jets + 3 btagged region ",60,-0.1,1.1);
   hist_jet_btag_6_b_corr = new TH1D("hist_jet_btag_6_b_corr", "btag of of b-jet flavor (ttjets) > 6jets + 3 btagged region after correction",60,-0.1,1.1);
   hist_jet_btag_6_l = new TH1D("hist_jet_btag_6_l", "btag of of light-jet flavor (ttjets) > 6jets + 3 btagged region",60,-0.1,1.1);
   hist_jet_btag_6_l_corr = new TH1D("hist_jet_btag_6_l_corr", "btag of of light-jet flavor (ttjets) > 6jets + 3 btagged region after correction",60,-0.1,1.1);
   hist_jet_btag_4 = new TH1D("hist_jet_btag_4", "btag of jet (ttjets) control region",60,-0.1,1.1);
   hist_jet_btag_4_corr = new TH1D("hist_jet_btag_4_corr", "btag of jet (ttjets) control region after correction",60,-0.1,1.1);
   hist_jet_btag_4_b = new TH1D("hist_jet_btag_4_b", "btag of b-jet flavor (ttjets) control region ",60,-0.1,1.1);
   hist_jet_btag_4_b_corr = new TH1D("hist_jet_btag_4_b_corr", "btag of of b-jet flavor (ttjets) control region after correction",60,-0.1,1.1);
   hist_jet_btag_4_l = new TH1D("hist_jet_btag_4_l", "btag of of light-jet flavor (ttjets) control region",60,-0.1,1.1);
   hist_jet_btag_4_l_corr = new TH1D("hist_jet_btag_4_l_corr", "btag of of light-jet flavor (ttjets) control region after correction",60,-0.1,1.1);

   hist_jet_btag_2_ttb = new TH1D("hist_jet_btag_2_ttb", "btag of jet (tt+b) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_2_ttb_corr = new TH1D("hist_jet_btag_2_ttb_corr", "btag of jet (tt+b) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_2_ttc = new TH1D("hist_jet_btag_2_ttc", "btag of jet (tt+c) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_2_ttc_corr = new TH1D("hist_jet_btag_2_ttc_corr", "btag of jet (tt+c) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_2_ttlf = new TH1D("hist_jet_btag_2_ttlf", "btag of jet (tt+lf) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_2_ttlf_corr = new TH1D("hist_jet_btag_2_ttlf_corr", "btag of jet (tt+lf) signal only 3b region after correction",60,-0.1,1.1);

   hist_jet_btag_2 = new TH1D("hist_jet_btag_2", "btag of jet (ttjets) 4jet(2b)",60,-0.1,1.1);
   hist_jet_btag_2_corr = new TH1D("hist_jet_btag_2_corr", "btag of jet (ttjets) 4jet(2b) after correction",60,-0.1,1.1);
   hist_jet_btag_2_b = new TH1D("hist_jet_btag_2_b", "btag of b-jet flavor (ttjets)4jet(2b) ",60,-0.1,1.1);
   hist_jet_btag_2_b_corr = new TH1D("hist_jet_btag_2_b_corr", "btag of of b-jet flavor (ttjets) 4jet(2b) after correction",60,-0.1,1.1);
   hist_jet_btag_2_c = new TH1D("hist_jet_btag_2_c", "btag of charm flavor (ttjets)4jet(2b) ",60,-0.1,1.1);
   hist_jet_btag_2_c_corr = new TH1D("hist_jet_btag_2_c_corr", "btag of of charm flavor (ttjets) 4jet(2b) after correction",60,-0.1,1.1);
   hist_jet_btag_2_l = new TH1D("hist_jet_btag_2_l", "btag of of light-jet flavor (ttjets) 4jet(2b)",60,-0.1,1.1);
   hist_jet_btag_2_l_corr = new TH1D("hist_jet_btag_2_l_corr", "btag of of light-jet flavor (ttjets) 4jet(2b) after correction",60,-0.1,1.1);

   hist_jet_btag_s_2 = new TH1D("hist_jet_btag_s_2", "btag of jet (ttjets) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_s_2_corr = new TH1D("hist_jet_btag_s_2_corr", "btag of jet (ttjets) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_s_2_b = new TH1D("hist_jet_btag_s_2_b", "btag of b-jet flavor (ttjets) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_s_2_b_corr = new TH1D("hist_jet_btag_s_2_b_corr", "btag of of b-jet flavor (ttjets) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_s_2_l = new TH1D("hist_jet_btag_s_2_l", "btag of of light-jet flavor (ttjets) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_s_2_l_corr = new TH1D("hist_jet_btag_s_2_l_corr", "btag of of light-jet flavor (ttjets) signal only 3b region after correction",60,-0.1,1.1);

   hist_jet_btag_s_ttb = new TH1D("hist_jet_btag_s_ttb", "btag of jet (tt+b) signal region",60,-0.1,1.1);
   hist_jet_btag_s_ttb_corr = new TH1D("hist_jet_btag_s_ttb_corr", "btag of jet (tt+b) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_ttc = new TH1D("hist_jet_btag_s_ttc", "btag of jet (tt+c) signal region",60,-0.1,1.1);
   hist_jet_btag_s_ttc_corr = new TH1D("hist_jet_btag_s_ttc_corr", "btag of jet (tt+c) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_ttlf = new TH1D("hist_jet_btag_s_ttlf", "btag of jet (tt+lf) signal region",60,-0.1,1.1);
   hist_jet_btag_s_ttlf_corr = new TH1D("hist_jet_btag_s_ttlf_corr", "btag of jet (tt+lf) signal region after correction",60,-0.1,1.1);

   hist_jet_btag_s = new TH1D("hist_jet_btag_s", "btag of jet (ttjets) signal region",60,-0.1,1.1);
   hist_jet_btag_s_bjet = new TH1D("hist_jet_btag_s_bjet", "btag of b tagged jet (ttjets) signal region",60,-0.1,1.1);
   hist_jet_btag_s_total_up = new TH1D("hist_jet_btag_s_total_up", "btag of jet (ttjets) total up signal region",60,-0.1,1.1);
   hist_jet_btag_s_total_down = new TH1D("hist_jet_btag_s_total_down", "btag of jet (ttjets) total down signal region",60,-0.1,1.1);
   hist_jet_btag_s_jes_up = new TH1D("hist_jet_btag_s_jes_up", "btag of jet (ttjets) JES up signal region",60,-0.1,1.1);
   hist_jet_btag_s_jes_down = new TH1D("hist_jet_btag_s_jes_down", "btag of jet (ttjets) JES down signal region",60,-0.1,1.1);
   hist_jet_btag_s_pur_up = new TH1D("hist_jet_btag_s_pur_up", "btag of jet (ttjets) purity up signal region",60,-0.1,1.1);
   hist_jet_btag_s_pur_down = new TH1D("hist_jet_btag_s_pur_down", "btag of jet (ttjets) purity down signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta1_up = new TH1D("hist_jet_btag_s_sta1_up", "btag of jet (ttjets) sta1 up signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta1_down = new TH1D("hist_jet_btag_s_sta1_down", "btag of jet (ttjets) sta1 down signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta2_up = new TH1D("hist_jet_btag_s_sta2_up", "btag of jet (ttjets) sta2 up signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta2_down = new TH1D("hist_jet_btag_s_sta2_down", "btag of jet (ttjets) sta2 down signal region",60,-0.1,1.1);
   hist_jet_btag_s_corr = new TH1D("hist_jet_btag_s_corr", "btag of jet (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_corr_bjet = new TH1D("hist_jet_btag_s_corr_bjet", "btag of btagged jet (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_b = new TH1D("hist_jet_btag_s_b", "btag of b-jet flavor (ttjets) signal regio",60,-0.1,1.1);
   hist_jet_btag_s_b_corr = new TH1D("hist_jet_btag_s_b_corr", "btag of of b-jet flavor (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_c = new TH1D("hist_jet_btag_s_c", "btag of charm flavor (ttjets) signal regio",60,-0.1,1.1);
   hist_jet_btag_s_c_corr = new TH1D("hist_jet_btag_s_c_corr", "btag of of charm flavor (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_l = new TH1D("hist_jet_btag_s_l", "btag of of light-jet flavor (ttjets) signal region",60,-0.1,1.1);
   hist_jet_btag_s_l_Luca = new TH1D("hist_jet_btag_s_l_Luca", "ttjets light-jet flavor in signal region No b-tagging",60,-0.1,1.1);
   hist_jet_btag_s_l_corr = new TH1D("hist_jet_btag_s_l_corr", "btag of of light-jet flavor (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_AS = new TH1D("hist_jet_btag_AS", "btag of jet after 4 jets",60,-0.1,1.1);
   hist_jet_btag_AS_corr = new TH1D("hist_jet_btag_AS_corr", "btag of jet after correction",60,-0.1,1.1);
   hist_jet_btag_Func = new TH1D("hist_jet_btag_Func", "Correction Function of (lep)b",2200,0,1.1);
   hist_jet_btag_pdgid0 = new TH1D("hist_jet_btag_pdgid0", "btag of jet with pdgID is 0",60,-0.1,1.1);
   hist_jet_SF_pdgid0 = new TH1D("hist_jet_SF_pdgid0", "Scale factor of jet with pdgID is 0",60,0,6);
   hist_gjet_pt = new TH1D("hist_gjet_pt", "p_{T} of gjet",100,0,150);
   hist_gjet_eta = new TH1D("hist_gjet_eta", "#eta of gjet",100,-3.,3.);
   hist_gjet_phi = new TH1D("hist_gjet_phi", "#phi of gjet",100,-3.5,3.5);
   hist_gjetc_pt = new TH1D("hist_gjetc_pt", "p_{T} of gjetc",100,0,150);
   hist_gjetc_eta = new TH1D("hist_gjetc_eta", "#eta of gjetc",100,-3.,3.);
   hist_gjetc_phi = new TH1D("hist_gjetc_phi", "#phi of gjetc",100,-3.5,3.5);
/*
   hist_jet_disc = new TH1D("hist_jet_disc", "Disc of jet",100,-15,15);
   hist_jet_fish = new TH1D("hist_jet_fish", "Jet cleaning fisher",100,0,1.);
st_higgs_BJetpair_DR_gm*/
   hist_bjet_no_cut = new TH1D("hist_bjet_no_cut", "No. of bjets after event selection",10,0,10);
   hist_bjet_no = new TH1D("hist_bjet_no", "No. of bjets",10,0,10);
   hist_jet_no = new TH1D("hist_jet_no", "No. of jets",10,0,10);
   hist_bjet_no_AS = new TH1D("hist_bjet_no after selection", "No. of bjets",10,0,10);
   hist_jet_no_AS = new TH1D("hist_jet_no after selection", "No. of jets",10,0,10);
   hist_jet_no_c = new TH1D("hist_jet_no_c", "No. of jets Cleaned",10,0,10);

   hist_met_sumEt = new TH1D("hist_met_sumEt", "Sum E_{T} of MET",50,0,1000);
   hist_met_sumEt_xy = new TH1D("hist_met_sumEt_xy", "Sum E_{T} of MET",50,0,1000);
   hist_met_UE = new TH1D("hist_met_UE", "Unclustered Energy of MET",50,0,1000);
   hist_met_pt = new TH1D("hist_met_pt", "p_{T} of MET",100,0,150);
   hist_met_pt_AS = new TH1D("hist_met_pt_AS", "p_{T} of MET",100,0,150);
   hist_met_pt_2b = new TH1D("hist_met_pt_2b", "p_{T} of MET",100,0,150);
   hist_met_pt_3b = new TH1D("hist_met_pt_3b", "p_{T} of MET",100,0,150);
   hist_met_phi = new TH1D("hist_met_phi", "#phi of MET",100,-3.5,3.5);

   hist_top_m_bw = new TH1D("hist_top_m_bw","inv mass of t(bW) all",50,50,350);
   hist_top_m_cz = new TH1D("hist_top_m_cz","inv mass of t(cZ) all",50,50,350);

   hist_top_comb = new TH1D("hist_top_comb","# of combinations",10,0,10);
   hist_top_corr = new TH1D("hist_top_corr","pick correct comb.", 5,0, 5);
   hist_top_corr0 = new TH1D("hist_top_corr0","pick correct comb. Org", 5,0, 5);

   hist_ERb = new TH1D("hist_ERb","energy of b at top rest frame",50,0,200);
   hist_ERc = new TH1D("hist_ERc","energy of c at top rest frame",50,0,200);

   hist_fit_m_bw = new TH1D("hist_fit_m_bw","inv mass of t(bW)",50,50,350);
   hist_fit_m_cz = new TH1D("hist_fit_m_cz","inv mass of t(cZ)",50,50,350);
   hist_fit_m_zee = new TH1D("hist_fit_m_zee","inv mass of Z(ee)",60,30,150);
   hist_fit_m_zmm = new TH1D("hist_fit_m_zmm","inv mass of Z(#mu#mu)",60,30,150);
   hist_fit_m_wen = new TH1D("hist_fit_m_wen","inv mass of W(e#nu)",50,0,250);
   hist_fit_m_wmn = new TH1D("hist_fit_m_wmn","inv mass of W(#mu#nu)",50,0,250);
   hist_fit_mt_wen = new TH1D("hist_fit_mt_wen","trans. mass of W(e#nu)",50,0,250);
   hist_fit_mt_wmn = new TH1D("hist_fit_mt_wmn","trans mass of W(#mu#nu)",50,0,250);
   hist_fit_ht = new TH1D("hist_fit_ht","Daughter p_{T} sum",50,0,1500);
   hist_fit_st = new TH1D("hist_fit_st","Total p_{T} sum",50,0,1500);

   hist_fit_ctag_lc1 = new TH1D("hist_fit_ctag_lc1","c-tag l-c 1",50,-2.,2.);
   hist_fit_ctag_lc2 = new TH1D("hist_fit_ctag_lc2","c-tag l-c 2",50,-2.,2.);
   hist_fit_ctag_bc1 = new TH1D("hist_fit_ctag_bc1","c-tag b-c 1",50,-2.,2.);
   hist_fit_ctag_bc2 = new TH1D("hist_fit_ctag_bc2","c-tag b-c 2",50,-2.,2.);

   hist_fit_nbjet = new TH1D("hist_fit_nbjet", "No. of bjets",10,0,10);
   hist_fit_ncbjet = new TH1D("hist_fit_ncbjet", "No. of clean bjets",10,0,10);

   mvaTree = new TTree("mvaTree", "Tree for MVA studies");

   mvaTree->Branch("TopInfo_Pt_bw", &TopInfo_Pt_bw, "TopInfo_Pt_bw/F");
   mvaTree->Branch("TopInfo_M_bw", &TopInfo_M_bw, "TopInfo_M_bw/F");
   mvaTree->Branch("TopInfo_Mt_bw", &TopInfo_Mt_bw, "TopInfo_Mt_bw/F");
   mvaTree->Branch("TopInfo_Pt_cz", &TopInfo_Pt_cz, "TopInfo_Pt_cz/F");
   mvaTree->Branch("TopInfo_M_cz", &TopInfo_M_cz, "TopInfo_M_cz/F");
   mvaTree->Branch("TopInfo_Mt_cz", &TopInfo_Mt_cz, "TopInfo_Mt_cz/F");
   mvaTree->Branch("TopInfo_MCTruth", &TopInfo_MCTruth, "TopInfo_MCTruth/I");

   mvaTree->Branch("CJetBoost_E", &CJetBoost_E, "CJetBoost_E/F");
   mvaTree->Branch("BJetBoost_E", &BJetBoost_E, "BJetBoost_E/F");
   mvaTree->Branch("WInfo_Pt", &WInfo_Pt, "WInfo_Pt/F");
   mvaTree->Branch("WInfo_Mt", &WInfo_Mt, "WInfo_Mt/F");
   mvaTree->Branch("ZInfo_Pt", &ZInfo_Pt, "ZInfo_Pt/F");
   mvaTree->Branch("ZInfo_M", &ZInfo_M, "ZInfo_M/F");
   
   mvaTree->Branch("TopTop_dphi", &TopTop_dphi, "TopTop_dphi/F");
   mvaTree->Branch("Z_cjet_dphi", &Z_cjet_dphi, "Z_cjet_dphi/F");
   mvaTree->Branch("Z_bjet_dphi", &Z_bjet_dphi, "Z_bjet_dphi/F");
   mvaTree->Branch("W_cjet_dphi", &W_cjet_dphi, "W_cjet_dphi/F");
   mvaTree->Branch("W_bjet_dphi", &W_bjet_dphi, "W_bjet_dphi/F");
   mvaTree->Branch("ZLLpair_dphi", &ZLLpair_dphi, "ZLLpair_dphi/F");
   mvaTree->Branch("WLZL1_dphi", &WLZL1_dphi, "WLZL1_dphi/F");
   mvaTree->Branch("WLZL2_dphi", &WLZL2_dphi, "WLZL2_dphi/F");
   mvaTree->Branch("WLep_bjet_dphi", &WLep_bjet_dphi, "WLep_bjet_dphi/F");
   mvaTree->Branch("ZLep1_bjet_dphi", &ZLep1_bjet_dphi, "ZLep1_bjet_dphi/F");
   mvaTree->Branch("ZLep2_bjet_dphi", &ZLep2_bjet_dphi, "ZLep2_bjet_dphi/F");
   mvaTree->Branch("WLep_cjet_dphi", &WLep_cjet_dphi, "WLep_cjet_dphi/F");
   mvaTree->Branch("ZLep1_cjet_dphi", &ZLep1_cjet_dphi, "ZLep1_cjet_dphi/F");
   mvaTree->Branch("ZLep2_cjet_dphi", &ZLep2_cjet_dphi, "ZLep2_cjet_dphi/F");
   
   mvaTree->Branch("TopTop_dtheta", &TopTop_dtheta, "TopTop_dtheta/F");
   mvaTree->Branch("Z_cjet_dtheta", &Z_cjet_dtheta, "Z_cjet_dtheta/F");
   mvaTree->Branch("Z_bjet_dtheta", &Z_bjet_dtheta, "Z_bjet_dtheta/F");
   mvaTree->Branch("W_cjet_dtheta", &W_cjet_dtheta, "W_cjet_dtheta/F");
   mvaTree->Branch("W_bjet_dtheta", &W_bjet_dtheta, "W_bjet_dtheta/F");
   mvaTree->Branch("ZLLpair_dtheta", &ZLLpair_dtheta, "ZLLpair_dtheta/F");
   mvaTree->Branch("WLZL1_dtheta", &WLZL1_dtheta, "WLZL1_dtheta/F");
   mvaTree->Branch("WLZL2_dtheta", &WLZL2_dtheta, "WLZL2_dtheta/F");
   mvaTree->Branch("WLep_bjet_dtheta", &WLep_bjet_dtheta, "WLep_bjet_dtheta/F");
   mvaTree->Branch("ZLep1_bjet_dtheta", &ZLep1_bjet_dtheta, "ZLep1_bjet_dtheta/F");
   mvaTree->Branch("ZLep2_bjet_dtheta", &ZLep2_bjet_dtheta, "ZLep2_bjet_dtheta/F");
   mvaTree->Branch("WLep_cjet_dtheta", &WLep_cjet_dtheta, "WLep_cjet_dtheta/F");
   mvaTree->Branch("ZLep1_cjet_dtheta", &ZLep1_cjet_dtheta, "ZLep1_cjet_dtheta/F");
   mvaTree->Branch("ZLep2_cjet_dtheta", &ZLep2_cjet_dtheta, "ZLep2_cjet_dtheta/F");

   mvaTree->Branch("BJet_btag", &BJet_btag, "BJet_btag/F");
   mvaTree->Branch("BJet_ctag", &BJet_ctag, "BJet_ctag/F");
   mvaTree->Branch("CJet_btag", &CJet_btag, "CJet_btag/F");
   mvaTree->Branch("CJet_ctag", &CJet_ctag, "CJet_ctag/F");
   
   mvaTree->Branch("mvaOCPE", &mvaOCPE, "mvaOCPE/F");
   
   fOutput->Add(mvaTree);

   readerOCPE = new TMVA::Reader( "!Color:!Silent" );

//   readerOCPE->AddVariable( "CJetBoost_E", &CJetBoost_E );
//   readerOCPE->AddVariable( "BJetBoost_E", &BJetBoost_E );
   readerOCPE->AddVariable( "TopTop_dphi", &TopTop_dphi );
   readerOCPE->AddVariable( "Z_cjet_dphi", &Z_cjet_dphi );
//   readerOCPE->AddVariable( "Z_bjet_dphi", &Z_bjet_dphi );
//   readerOCPE->AddVariable( "W_cjet_dphi", &W_cjet_dphi );
//   readerOCPE->AddVariable( "W_bjet_dphi", &W_bjet_dphi );
   readerOCPE->AddVariable( "ZLLpair_dphi", &ZLLpair_dphi );
   readerOCPE->AddVariable( "WLZL1_dphi", &WLZL1_dphi );
//   readerOCPE->AddVariable( "WLZL2_dphi", &WLZL2_dphi );
   readerOCPE->AddVariable( "WLep_bjet_dphi", &WLep_bjet_dphi );
//   readerOCPE->AddVariable( "ZLep1_bjet_dphi", &ZLep1_bjet_dphi );
//   readerOCPE->AddVariable( "ZLep2_bjet_dphi", &ZLep2_bjet_dphi );
//   readerOCPE->AddVariable( "WLep_cjet_dphi", &WLep_cjet_dphi );
//   readerOCPE->AddVariable( "ZLep1_cjet_dphi", &ZLep1_cjet_dphi );
//   readerOCPE->AddVariable( "ZLep2_cjet_dphi", &ZLep2_cjet_dphi );

//   readerOCPE->AddVariable( "BJet_btag", &BJet_btag );
//   readerOCPE->AddVariable( "BJet_ctag", &BJet_btag );
//   readerOCPE->AddVariable( "CJet_btag", &BJet_btag );
//   readerOCPE->AddVariable( "CJet_ctag", &BJet_btag );

   readerOCPE->AddSpectator( "TopInfo_M_bw", &TopInfo_M_bw );
   readerOCPE->AddSpectator( "TopInfo_M_cz", &TopInfo_M_cz );

   //readerOCPE->SetWeightExpression( "Event_Weight" );
   readerOCPE->BookMVA( "myOCPE", "TMVAClassification_Likelihood.weights.xml" );
   //readerOCPE->BookMVA( "myOCPE", "TMVAClassification_MLPBNN.weights.xml" );
}

Bool_t MyTcZAna::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MyTcZAna::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fChain->GetTree()->GetEntry(entry);
   //cout << entry << endl;
   //cout << EvtInfo_EvtNo << endl;
   //Event_Weight_Tot += Event_Weight;

   m_gen_zee_idx=-1;
   m_gen_wuu_idx=-1;
   m_gen_top1_idx=-1;
   m_gen_top2_idx=-1;
   m_gen_lep1_idx=-1;
   m_gen_lep2_idx=-1;
   m_gen_lep3_idx=-1;
   m_gen_lep4_idx=-1;
   m_gen_jet1_idx=-1;
   m_gen_jet2_idx=-1;

   m_ht = m_st = 0.;

   if(EvtInfo_McFlag > 0){ // MC events
     if(GenParts_Size > 512) cout << "!!!\n\n";
     
     for(int git=0; git < GenParts_Size && git < MAX_GENS; git++){
       GenParts_P4[git].SetPtEtaPhiM(GenParts_Pt[git], GenParts_Eta[git],
                                     GenParts_Phi[git], GenParts_Mass[git]);
       
       if(m_gen_zee_idx==-1 &&
          //GenParts_PdgID[git]==23 && GenParts_Status[git]==3){
          GenParts_PdgID[git]==23 && GenParts_Status[git]<30){
         m_gen_zee_idx=git;
         //continue;
         //std::cout << "Found Z!!\n" << std::endl;
       }
       
       if(m_gen_wuu_idx==-1 &&
          //abs(GenParts_PdgID[git])==24 && GenParts_Status[git]==3){
          fabs(GenParts_PdgID[git])==24 && GenParts_Status[git]<30){
         m_gen_wuu_idx=git;
         //continue;
         //std::cout << "Found W!!\n" << std::endl;
       }
       
       if(m_gen_jet1_idx==-1 &&  // b-jet
          fabs(GenParts_PdgID[git])==5 && GenParts_Status[git]<30){
         m_gen_jet1_idx=git;
         //continue;
       }
       
       if(m_gen_jet2_idx==-1 && m_gen_zee_idx!=-1 && m_gen_zee_idx!=-1 &&
          (fabs(GenParts_PdgID[git])==2 || fabs(GenParts_PdgID[git])==4) &&
          GenParts_Status[git]<30){
         m_gen_jet2_idx=git;  // light jet
         //continue;
       }
       
       if(m_gen_top1_idx==-1 && 
          fabs(GenParts_PdgID[git]) == 6 &&
          fabs(GenParts_PdgID[git+1]) == 6){
         m_gen_top1_idx = git;
         m_gen_top2_idx = git+1;
       }
       
       // this doesn't work for PY8
       if(m_gen_zee_idx!=-1 && m_gen_top2_idx!=-1 &&
          GenParts_Index[m_gen_top2_idx]==
          (GenParts_Mo1[m_gen_zee_idx]-1)){
         m_gen_top1_idx=m_gen_top1_idx+1;
         m_gen_top2_idx=m_gen_top2_idx-1;  // swap them
       }
       
       //std::cout << Event_Weight_Tot << "\n";
       // if(git==0){
         
       // }

       //if(Event_Weight_Tot < 10 && GenParts_Status[git]==3){
       if(Event_Weight_Tot < 10 && 
          (//(git > 5 && git < 150) ||
           (GenParts_Status[git] >= 3 && (GenParts_Status[git] < 30 )))){
            //|| git > 100)){
         if(git == 0) cout << endl;
         cout << "MC evt. " << EvtInfo_EvtNo << " #" << git << " "
              << GenParts_Index[git] << " pdgID: "
              << GenParts_PdgID[git] << " Mo: " << GenParts_Mo1[git]
              << ","
              << GenParts_Mo2[git] << " Da: " << GenParts_Da1[git]
              << ","
             << GenParts_Da2[git] << " Status: " << GenParts_Status[git];


         
         if(m_gen_top1_idx == git)
           cout << " *\n";
         else if(m_gen_top2_idx == git)
           cout << " &\n";
         else if(m_gen_wuu_idx == git)
           cout << " W\n";
         else if(m_gen_zee_idx == git)
           cout << " Z\n";
         else if(m_gen_jet1_idx == git)
           cout << " b\n";
         else if(m_gen_jet2_idx == git && fabs(GenParts_PdgID[git])==2)
           cout << " u\n";
         else if(m_gen_jet2_idx == git && fabs(GenParts_PdgID[git])==4)
           cout << " c\n";
         else
           cout << endl;
       }
     } // GEN loop
   } // MC if

   hist_evt_cut->Fill(0., Event_Weight);
   // if(Channel_flag_e ==1) hist_evt_cut_e->Fill(0., Event_Weight);
   // if(Channel_flag_m ==1) hist_evt_cut_m->Fill(0., Event_Weight);
   hist_evt_cut_e->Fill(0., Event_Weight);
   hist_evt_cut_m->Fill(0., Event_Weight);
   
   Event_Weight_Tot += Event_Weight;
   Event_Tot ++;

   if(Event_Tot%10000 ==0 && Event_Tot>0) cout << "." << std::flush;
   
   if(
      //Single Electron
      (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v8] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v9] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v10] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v11] == 1 ) hist_evt_cut_e->Fill(1., Event_Weight); 
   if(  
      //Single Moun
      (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v11] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v12] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v13] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v14] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v15] == 1  ) hist_evt_cut_m->Fill(1., Event_Weight);
   
   
   //    /* HLT 
   // if(
   //    //Single Electron
   //    (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v8] != 1 &&
   //    (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v9] != 1 &&
   //    (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v10] != 1 && 
   //    (int)EvtInfo_TrgBook[HLT_Ele27_WP80_v11] != 1 && 
   //    //Single Moun
   //    (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v11] != 1 && 
   //    (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v12] != 1 &&
   //    (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v13] != 1 &&
   //    (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v14] != 1 &&
   //    (int)EvtInfo_TrgBook[HLT_IsoMu24_eta2p1_v15] != 1  
   //    ) return(false); 
   // */   
   hist_evt_cut->Fill(1., Event_Weight);

   // Primary Vertex Selections
   //     int i_prim_vtx=-1;
   m_vtx_no=0;
   //double vtx_sumpt=0.;

   //hist_vtx_cut->Fill(0., Event_Weight);      
   for(int iv=0; iv < VtxInfo_Size; iv++){
     VtxInfo_Good[iv] = 0;
     hist_vtx_cut->Fill(0., Event_Weight); 
     
     // 0: Vertices WITHOUT the Beam Spot constraint
     // 1: Vertices WITH the Beam Spot constraint
     if(VtxInfo_Type[iv] >= 0){//Type
       hist_vtx_cut->Fill(1, Event_Weight);
       
       if(VtxInfo_isValid[iv] > 0){
         hist_vtx_cut->Fill(2, Event_Weight);
         hist_vtx_ndof->Fill(VtxInfo_Ndof[iv], Event_Weight);
         hist_vtx_nx2->Fill(VtxInfo_NormalizedChi2[iv], Event_Weight);
         
         if(VtxInfo_Ndof[iv] > VTX_NDOF_CUT){//at least 4 degrees of freedom
           hist_vtx_cut->Fill(3, Event_Weight);
           hist_vtx_ptsum->Fill(VtxInfo_Pt_Sum[iv], Event_Weight);
           hist_vtx_z->Fill(VtxInfo_vz[iv], Event_Weight);
           hist_vtx_rho->Fill(VtxInfo_Rho[iv], Event_Weight);
           
           if(VtxInfo_Pt_Sum[iv] >= VTX_SUMPT_CUT){
             hist_vtx_cut->Fill(4, Event_Weight);
             
             //vtx_sumpt=VtxInfo_Pt_Sum[iv];
             
             if(fabs(VtxInfo_vz[iv]) < VTX_ABSZ_CUT){
               //an impact parameter with respect to the beanspot in z,dz
               hist_vtx_cut->Fill(5, Event_Weight);
               
               if(fabs(VtxInfo_Rho[iv]) < VTX_RHO_CUT){
                 hist_vtx_cut->Fill(6, Event_Weight);
                 //		    i_prim_vtx=iv;
                 VtxInfo_Good[iv] = 1;
                 m_vtx_no++;
               }
             }
           }
         }
       }
     }
   }//END Vertex Loop

   hist_vtx_no->Fill(m_vtx_no, Event_Weight);
   if(m_vtx_no == 0) return(false);

   hist_evt_cut->Fill(2., Event_Weight);
   hist_evt_cut_e->Fill(2., Event_Weight);
   hist_evt_cut_m->Fill(2., Event_Weight);

   m_e_notest=0;
   m_e_no=0; m_te_no=0;
   m_m_no=0; m_tm_no=0;

   for(int il1=0; il1 < Leptons_Size; il1++){
     Leptons_Good[il1]=0;
     Leptons_Index[il1]=il1;
     
     Leptons_P4[il1].SetPxPyPzE(Leptons_Px[il1], Leptons_Py[il1],
                                Leptons_Pz[il1], Leptons_Energy[il1]);
     
     // checking MC GEN matching
     // Leptons_GenMatch[il1]=-1;
     // if((m_gen_lep1_idx != -1 && abs(GenParts_PdgID[m_gen_lep1_idx])>10 &&
     //     GenParts_P4[m_gen_lep1_idx].DeltaR(Leptons_P4[il1]) < 0.5)){
     //   Leptons_GenMatch[il1]=m_gen_lep1_idx;
     // }
     //if(Event_Weight_Tot < 10.){ std::cout << "Lepton " << il1 << std::endl;}

     ReconElec(il1);
     ReconMuon(il1);
     m_st += Leptons_P4[il1].Pt();

   }//END lepton Loop
   
   hist_lep_no->Fill(m_e_no+m_m_no, Event_Weight);
   hist_e_no->Fill(m_e_no, Event_Weight);
   hist_m_no->Fill(m_m_no, Event_Weight);

   if((m_e_no+m_m_no)!=3){
     return(false);
   }

   ReconZ();

   Jets_No=0;
   m_bjet_no=0;
   
   ReconJet();
   ReconBJet();

   m_te_no=0; m_tm_no=0;
   Wuu_No=0;
   ReconW();

   m_st += EvtInfo_MET;
   
   if(EvtInfo_MET < MET_CUT) return(false);
   
   hist_evt_cut->Fill(4, Event_Weight);
   //if((m_e_no == 1) && (m_m_no == 0)) 
   if((m_e_no > 0) && (m_e_no+m_m_no == 3)){
     hist_evt_cut_e->Fill(4, Event_Weight);
     //else if((m_e_no == 0) && (m_m_no == 1)) 
   }else if((m_m_no > 0) && (m_e_no+m_m_no == 3)){
     hist_evt_cut_m->Fill(4, Event_Weight);
   }
   
   hist_jet_no->Fill(Jets_No, Event_Weight);
   hist_bjet_no->Fill(m_bjet_no, Event_Weight);
   
   mvaTree = dynamic_cast<TTree *>(fOutput->FindObject(Form("mvaTree")));

   TopInfo_MCTruth = 0;
   ReconTop();

   return kTRUE;
}

void MyTcZAna::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void MyTcZAna::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  mvaTree = dynamic_cast<TTree *>(fOutput->FindObject(Form("mvaTree")));
  if(mvaTree){
    // for(int i=0; i< 1000;i++){
    //   mvaTree->Fill();
    // }
    mvaTree->Write();
  }

  // std::cout << "\nSelecting done!\nTotal " << Event_Weight_Tot
  //           << " events processed.\n";
  std::cout << "\n\nVoila! C'est fini.\n";

   cout << "\nVertex_selection:\n";
   for(int i=0; i < 7; i++){
     cout << vtx_cut_label[i] << "   \t\t" << setprecision(9)
          << hist_vtx_cut->GetBinContent(i+1) << endl;
   }

   cout << "\nElectron_selection:\n";
   for(int i=0; i < 8; i++){
     cout << ele_cut_label[i] << "   \t\t" << setprecision(9)
          << hist_ele_cut->GetBinContent(i+1) << endl;
   }

   cout << "\nMuon_selection:\n";
   for(int i=0; i < 15; i++){
     cout << mu_cut_label[i] << "   \t\t" << setprecision(9)
          << hist_mu_cut->GetBinContent(i+1) << endl;
   }

   cout << "\nJet_selection:\n";
   for(int i=0; i < 7; i++){
     cout << jet_cut_label[i] << " : \t\t" << setprecision(9)
          << hist_jet_cut->GetBinContent(i+1) << endl;
   }

   cout << "\nEvent_selection  \t all \t eee \t eem \t emm \t mmm \n";
   for(int i=0; i < 14; i++){
     cout << evt_cut_label[i] << "   \t\t" << setprecision(9)
          << hist_evt_cut->GetBinContent(i+1) << " \t "
          // << hist_evt_cut_eee->GetBinContent(i+1) << " \t "
          // << hist_evt_cut_eem->GetBinContent(i+1) << " \t "
          // << hist_evt_cut_emm->GetBinContent(i+1) << " \t "
          // << hist_evt_cut_mmm->GetBinContent(i+1)
          << endl;
   }

   cout << "Total event weight: " << Event_Weight_Tot << endl;

}

void MyTcZAna::ReconElec(int il1){

  if(fabs(Leptons_Type[il1])==11){
    //m_e_notest++;
    hist_ele_cut->Fill(0., Event_Weight);

    // check the ele MVA is 0 and 1
    if(Leptons_ElemvaTrigV0[il1] == 0 || Leptons_ElemvaTrigV0[il1] ==1){
      hist_e_mva_no->Fill(7.,Event_Weight);
    }

//     if(Leptons_GenMatch[il1]!=-1 && fabs(GenParts_PdgID[Leptons_GenMatch[il1]])==11){
//       hist_ge_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
//       hist_ge_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
//       hist_ge_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);

//       hist_ele_cut->Fill(1, Event_Weight);
//     }

//Electron real cut         
    if(Leptons_Pt[il1] > ELE_PT_CUT){ // PT > 30
      hist_ele_cut->Fill(2, Event_Weight);
      
      // eta < 2.5 & Excluding EB-EE transition region
      if(fabs(Leptons_Eta[il1]) < ELE_ETA_CUT && 
         (fabs(Leptons_Eta[il1])<1.4442 || fabs(Leptons_Eta[il1])>1.566) ){

        hist_ele_cut->Fill(3, Event_Weight);

        if( Leptons_ElepassConversionVeto[il1] == 1){
          hist_ele_cut->Fill(4, Event_Weight);

          // Dxy not checked, Dxy < 0.05;0.10 cm, Dz < 0.10;0.20 cm
          // included in cutBasedID already
          //if(1||Leptons_ElTrackDxy_PV[il1] <ElTrackDxy){ //Dxy < 0.02
          //if(true){
          if(Leptons_eidVeryLooseMC[il1] > 0){
            hist_ele_cut->Fill(5, Event_Weight);
            
            // hist_e_iso->Fill(((Leptons_chargedIso[il1]+Leptons_neutralIso[il1]+Leptons_photonIso[il1])/Leptons_Et[il1]),Event_Weight);
            // Leptons_Good[il1]=-3;

            // if((Leptons_chargedIso[il1]+Leptons_neutralIso[il1]+
            //     Leptons_photonIso[il1])/Leptons_Et[il1] < ELE_ISO_LB &&
            //    Leptons_ElemvaTrigV0[il1]>ELE_MVA_CUT ){ 
            //relIso < 0.15 ; MVA > 0.9 recommended
            if(Leptons_eidMediumMC[il1] > 0){

              hist_ele_cut->Fill(6, Event_Weight);
              Leptons_Good[il1]=1;

              // if( Leptons_EleExpnumberOfHits[il1] <= ELE_Track_CUT){ 
              //   //mHits <= 0 
              if(Leptons_eidTightMC[il1] > 0){

                hist_ele_cut->Fill(7, Event_Weight);

                hist_e_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
                hist_e_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
                hist_e_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);

                m_e_no++;
                Leptons_Good[il1]=2;
  
              }//eid tight
            }//eid medium
          }//eid veto
        }//conv_veto
      }//eta < 2.5
    }//pt > 30
  } // end if il1 electron
}// ReconEle end


void MyTcZAna::ReconMuon(int il1){

  if(fabs(Leptons_Type[il1])==13){
    hist_mu_cut->Fill(0., Event_Weight);

    // if(Leptons_GenMatch[il1]!=-1 &&
    //     abs(GenParts_PdgID[Leptons_GenMatch[il1]])==13){
    //   hist_gm_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
    //   hist_gm_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
    //   hist_gm_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
    //   hist_mu_cut->Fill(1, Event_Weight);
    // }

//Muon real cut
    if((Leptons_MuType[il1] & 0x02) !=0 || // Global Muon
       (Leptons_MuType[il1] & 0x04) !=0 ){ // Tracker Muon  ==> Loose Muon
      hist_mu_cut->Fill(1, Event_Weight);
      
      if((Leptons_MuType[il1] & 0x04) !=0 ){ // Tracker Muon
        hist_mu_cut->Fill(2, Event_Weight);
      } 
        
      if(Leptons_Pt[il1] > MU_PT_CUT){ // PT > 20
        hist_mu_cut->Fill(3, Event_Weight);
          
        if(fabs(Leptons_Eta[il1]) < MU_ETA_CUT){ // eta < 2.4
          hist_mu_cut->Fill(4, Event_Weight);
            
          //(mu->pfIsolationR04().sumChargedHadronPt + max(0., mu->pfIsolationR04().sumNeutralHadronEt + mu->pfIsolationR04().sumPhotonEt - 0.5*mu->pfIsolationR04().sumPUPt))/mu->pt()
          double pf_neutral = max(0., Leptons_NeutralHadronIsoR04[il1] +
                                  Leptons_PhotonIsoR04[il1] -
                                  0.5*Leptons_sumPUPtR04[il1]);

          double pf_iso = (Leptons_ChargedHadronIsoR04[il1] + pf_neutral) /
            Leptons_Pt[il1];
            
          hist_m_iso->Fill( pf_iso, Event_Weight);

          //Leptons_Good[il1]=-3;

          if(pf_iso < MU_ISO_LCUT){ // Tight 0.15
            hist_mu_cut->Fill(5, Event_Weight);

            // Tight Muon            
            if(Leptons_MuInnerTrackDxy_PVBS[il1] <0.2){ // dxy
              //0.2 Transverse IP of the muon wrt primary vertex (cm)
              hist_mu_cut->Fill(7, Event_Weight);
              
              if(Leptons_MuGlobalNormalizedChi2[il1] < 10){//10 normChi2
                hist_mu_cut->Fill(8, Event_Weight);

                if(Leptons_MuNPixelLayers[il1] > MU_InnerTrack_CUT ){
                  // 0 muon.innerTrack()->hitPattern().numberOfValidPixelHits()
                  hist_mu_cut->Fill(9, Event_Weight);
                  
                  if(fabs(Leptons_MunumberOfMatchedStations[il1]) > 1){
                    //2 numberOfMatchedStations(), same wuth cut 14 loose cut
                    hist_mu_cut->Fill(10, Event_Weight);
                    
                    Leptons_Good[il1]=1;
                  
                    if(Leptons_MuTrackerLayersWithMeasurement[il1] > MU_Tracker_CUT){ 
                      // 5 track()->hitPattern().trackerLayersWithMeasurement()
                      hist_mu_cut->Fill(12, Event_Weight);
                      
                      if(Leptons_MuNMuonhits[il1] > MU_GlobeTracker_CUT){
                        // 0 recoMu.globalTrack()->hitPattern().numberOfValidMuonHits()
                        hist_mu_cut->Fill(13, Event_Weight);
                        
                        if(Leptons_MunumberOfMatchedStations[il1] > MU_MatchedStations_CUT){// 1 numberOfMatchedStations()
                          hist_mu_cut->Fill(14, Event_Weight);
                          
                          if(fabs(Leptons_vertexZ[il1]-VtxInfo_vz[0]) < MU_VertexZ_CUT){// 0.5 fabs( muon.vertex().z() - PV.z())
                            hist_mu_cut->Fill(15, Event_Weight);
                            
                            hist_m_pt->Fill(Leptons_Pt[il1], Event_Weight);
                            hist_m_eta->Fill(Leptons_Eta[il1], Event_Weight);
                            hist_m_phi->Fill(Leptons_Phi[il1], Event_Weight);
                            
                            m_m_no++;
                            Leptons_Good[il1]=2;
                          
                            //Leptons_Mu_P4[il1] = Leptons_P4[il1]; 
                          }//VertexZ < 0.5
                        }//MatchedStation > 1
                      }//GlobeTracker > 0                         
                    }// Tracker < 5 
                  }//iso < 0.12
                  //                    }//MuNChambersMatchesSegment >=2
                }//MuNPixelLayers > 0
              }//Chi2 < 10
            }//Dxy_PVBS <0.2
            //            }//TrackNHits > 10
          }//Eta < 2.1
        }//pt > 26
      }//MuType1
    }//MuType2
    
  }// end if il1 Muon
}// ReconMu end

void MyTcZAna::ReconZ(){
  // Z selections
  //int Z2ee_No=0, Z2mm_No=0;
  Zee_No=0;
  for(int il1=0; il1 < Leptons_Size; il1++){

// 	cout <<GenParts_PdgID[m_gen_lep1_idx] <<endl;
// 	cout <<GenParts_PdgID[m_gen_lep1_idx] <<endl;

// 	  cout << " " << il1 << ": (" << Leptons_P4[il1].Pt() << ", "
// 	       << Leptons_P4[il1].Eta() << ", "
// 	       << Leptons_P4[il1].Phi() << ") dR: "
// 	       << GenParts_P4[m_gen_lep1_idx].DeltaR(Leptons_P4[il1])
// 	       << ", "
// 	       << GenParts_P4[m_gen_lep2_idx].DeltaR(Leptons_P4[il1])
// 	       << ", "
// 	       << GenParts_P4[m_gen_lep3_idx].DeltaR(Leptons_P4[il1])
// 	    // << DeltaPhi(GenParts_Phi[m_gen_lep1_idx], Leptons_P4[il1].Phi())
// 	       << endl;

	//if(Leptons_LeptonType[il1]==11 ){
//Is good Electron
	if(Leptons_Type[il1]==11 && Leptons_Good[il1]>=1){
	//if(Leptons_Type[il1]==11 && abs(Leptons_Good[il1])>=1){ // loose
	  //m_e_no++;

//Check to see if the electron is faked by a muon
	  int muon_veto = 0;
	  for(int il=0; il < Leptons_Size; il++){
	    if(Leptons_Type[il]==13 && Leptons_Good[il]==2 &&
	       Leptons_Pt[il] > MU_PT_CUT &&
	       fabs((Leptons_P4[il]).DeltaR(Leptons_P4[il1])) < 0.1){
	      muon_veto=1;
	      break;
	    }
	  }
	  if(muon_veto != 0){
	    Leptons_Good[il1]=-1;
	    continue;
	  }

	  if(Leptons_GenMatch[il1]!=-1){
	    hist_gel_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
	    hist_gel_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
	    hist_gel_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
        
	    //hist_ele_cut->Fill(5, Event_Weight);
	  }
      
// 	  if(GenParts_P4[m_gen_top1_idx].DeltaR(Leptons_P4[il1]) > 0.5 &&
// 	     GenParts_P4[m_gen_top1_idx].DeltaR(Leptons_P4[il1]) > 0.5 )
// 	    continue;
	  
	  for(int il2=il1; il2 < Leptons_Size; il2++){
	    if(Leptons_Good[il1]==2 &&
	       Leptons_Type[il2]==11 && Leptons_Good[il2]==2 &&
	       Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
          
	      int muon_veto2 = 0;
	      for(int il=0; il < Leptons_Size; il++){
                if(Leptons_Type[il]==13 && Leptons_Good[il]>=1 &&
                   fabs((Leptons_P4[il]).DeltaR(Leptons_P4[il2])) < 0.1){
                  muon_veto2=1;
                  break;
                }
	      }
	      if(muon_veto2==1){
                Leptons_Good[il2]=-1;
                continue;
	      }
	      
	      Zee_P4[Zee_No]=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
	      if(Zee_P4[Zee_No].M() > Z_MASS_LCUT &&
                 Zee_P4[Zee_No].M() < Z_MASS_HCUT ){
            
                hist_zee_m->Fill(Zee_P4[Zee_No].M(), Event_Weight);
                hist_zee_pt->Fill(Zee_P4[Zee_No].Pt(), Event_Weight);
            
                Zee_lid1[Zee_No]=Leptons_Index[il1];
                Zee_lid2[Zee_No]=Leptons_Index[il2];
            
                if(Zee_P4[Zee_No].M() > TZ_MASS_LCUT &&
                   Zee_P4[Zee_No].M() < TZ_MASS_HCUT &&
                   fabs(Leptons_P4[il1].DeltaR(Leptons_P4[il2])) > 0.05 ){
                  //m_tz_no++;
                  m_tz_no_e++;
                }

                //cout << "Zee mass: " << Zee.mass() << endl;
                Zee_No++;
                m_z_no_e++;
	      }
	    }

	    // if(Leptons_Good[il1]==2 &&
	    //    Leptons_Type[il2]==11 && Leptons_Good[il2]==2 &&
	    //    Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
          
	    //   TLorentzVector  Zee_TT_P4=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
	    //   hist_zee_tt_m->Fill(Zee_TT_P4.M(), Event_Weight);
	    //   hist_zee_tt_pt->Fill(Zee_TT_P4.Pt(), Event_Weight);
	    // }else if(Leptons_Good[il1]==2 &&
        //          Leptons_Type[il2]==11 && Leptons_Good[il2]==-2 &&
        //          Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
          
	    //   TLorentzVector  Zee_TF_P4=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
	    //   hist_zee_tf_m->Fill(Zee_TF_P4.M(), Event_Weight);
	    //   hist_zee_tf_pt->Fill(Zee_TF_P4.Pt(), Event_Weight);
	    // }
        
	    // if(Leptons_Good[il1]==2 &&
        //    Leptons_Type[il2]==11 &&
        //    (Leptons_Good[il2]==-3 || Leptons_Good[il2]==1) &&
        //    Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
          
	    //   TLorentzVector  Zee_TE_P4=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
	    //   hist_zee_te_m->Fill(Zee_TE_P4.M(), Event_Weight);
	    //   hist_zee_te_pt->Fill(Zee_TE_P4.Pt(), Event_Weight);
	    // }
        
	  }
	}

	// now look for muons
	if(Leptons_Type[il1]==13 && Leptons_Good[il1]>=1){
	//if(Leptons_Type[il1]==13 && abs(Leptons_Good[il1])>=1){ // loose
	  //m_m_no++;

	  if(Leptons_GenMatch[il1]!=-1){
	    hist_gml_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
	    hist_gml_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
	    hist_gml_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
	    
	    hist_mu_cut->Fill(17, Event_Weight);
	  }

	  for(int il2=il1+1; il2 < Leptons_Size; il2++){
	    if(Leptons_Good[il1]==2 &&
	       Leptons_Type[il2]==13 && Leptons_Good[il2]==2 &&
	       Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
          
	      Zee_P4[Zee_No]=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
	      if(Zee_P4[Zee_No].M() > Z_MASS_LCUT &&
               Zee_P4[Zee_No].M() < Z_MASS_HCUT ){
            
                hist_zmm_m->Fill(Zee_P4[Zee_No].M(), Event_Weight);
                hist_zmm_pt->Fill(Zee_P4[Zee_No].Pt(), Event_Weight);
            
                Zee_lid1[Zee_No]=Leptons_Index[il1];
                Zee_lid2[Zee_No]=Leptons_Index[il2];
            
                //              cout << "Zee mass: " << Zee.mass() << endl;
                if(Zee_P4[Zee_No].M() > TZ_MASS_LCUT &&
                   Zee_P4[Zee_No].M() < TZ_MASS_HCUT &&
                   fabs(Leptons_P4[il1].DeltaR(Leptons_P4[il2])) > 0.05 ){
                  //m_tz_no++;
                  m_tz_no_m++;
                }
            
                Zee_No++;
                m_z_no_m++;
            
	      }
	    } // Leptons2 IF

	    // if(Leptons_Good[il1]==2 &&
		//      Leptons_Type[il2]==11 &&
		//      (Leptons_Good[il2]==-3 || Leptons_Good[il2]==1) &&
		//      Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
   
	    //   TLorentzVector  Zee_TE_P4=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
	    //   hist_zmm_te_m->Fill(Zee_TE_P4.M(), Event_Weight);
	    //   hist_zmm_te_pt->Fill(Zee_TE_P4.Pt(), Event_Weight);
	    // }

	  } // Leptons2 loop
	} // Leptons1 IF
  } // Leptons loop

  hist_zee_no->Fill(m_z_no_e, Event_Weight);
  hist_zmm_no->Fill(m_z_no_m, Event_Weight);

}

void MyTcZAna::ReconW(){
  // W selections
  //int Wen_No=0, Wmn_No=0;
  Wuu_No=0;
  m_w_no_e=m_w_no_m=0;
  hist_met_pt->Fill(EvtInfo_MET, Event_Weight);
  hist_met_phi->Fill(EvtInfo_METPhi, Event_Weight);

  int m_lep_idx=-1;

  TLorentzVector nu;

  nu.SetPxPyPzE(EvtInfo_MET*cos(EvtInfo_METPhi),
		EvtInfo_MET*sin(EvtInfo_METPhi), 0.,
		EvtInfo_MET);

  // loop over leptons for W
  int m_te_no=0; int m_tm_no=0;
  for(int il1=0; il1 < Leptons_Size; il1++){
	
    if(Leptons_Type[il1]==11 && Leptons_Good[il1] == 2 ){ //&& //#$%^
       //if(Leptons_Type[il1]==11 && abs(Leptons_Good[il1]) == 2 && // loose
       //Leptons_Index[il1]!=Zee_lid1[0] && Leptons_Index[il1]!=Zee_lid2[0]){
      //Not 0th Z's lepton
      //m_lep_idx=il1;
      m_te_no++;
      
      hist_te_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
      hist_te_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
      hist_te_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
      
      if(Leptons_GenMatch[il1]!=-1){
        hist_get_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
        hist_get_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
        hist_get_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
        
        //hist_ele_cut->Fill(7, Event_Weight);
      }
    }
    if(Leptons_Type[il1]==13 && Leptons_Good[il1] == 2 ){ //&& //#$%^
       //if(Leptons_Type[il1]==13 && abs(Leptons_Good[il1]) == 2 && // loose
       //Leptons_Index[il1]!=Zee_lid1[0] && Leptons_Index[il1]!=Zee_lid2[0]){
      //m_lep_idx=il1;
      m_tm_no++;
      //cout << "m!\n";
      hist_tm_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
      hist_tm_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
      hist_tm_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
      
      if(Leptons_GenMatch[il1]!=-1){
        hist_gmt_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
        hist_gmt_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
        hist_gmt_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
        
        //hist_mu_cut->Fill(15, Event_Weight);
      }
    }
  }

  //if((m_te_no+m_tm_no)==1) cout <<"!@!"<<std::flush;

  //if((m_te_no+m_tm_no)==1){//Means the lepton is not e and m at the same time

// 	  int muon_veto = 0;
// 	  for(int il=0; il < Leptons_Size; il++){
// 	    if(Leptons_LeptonType[il]==13 && Leptons_Good[il]==2 &&
// 	       Leptons_Pt[il] > MU_PT_CUT &&
// 	       fabs((Leptons_P4[il]).DeltaR(Leptons_P4[il1])) < 0.1){
// 	      muon_veto=1;
// 	      break;
// 	    }
// 	  }
// 	  if(muon_veto != 0){
// 	    //Leptons_Good[il1]=-1;
// 	    continue;
// 	  }
  for(int il1=0; il1 < Leptons_Size; il1++){

    if(Leptons_Good[il1] != 2) continue;

    TLorentzVector lep;
	  
// 	  lep.SetPxPyPzE(Leptons_P4[il1].Px(), Leptons_P4[il1].Py(), 0.,
// 			 sqrt(Leptons_P4[il1].Pt()*Leptons_P4[il1].Pt()+
// 			      Leptons_P4[il1].M()*Leptons_P4[il1].M()));
    
    lep.SetPxPyPzE(Leptons_P4[il1].Px(), Leptons_P4[il1].Py(),
                   Leptons_P4[il1].Pz(), Leptons_P4[il1].E());
    
    double pz=0, b4ac=0, b=0;
    b=lep.Px()*nu.Px()+lep.Py()*nu.Py()+MASS_W*MASS_W/2;
    b4ac=b*b-nu.E()*nu.E()*(lep.E()*lep.E()-lep.Pz()*lep.Pz());
    
    if(b4ac>0){
      if((lep.Pz()*b) * (lep.E()*sqrt(b4ac)) >= 0){
        pz=(lep.Pz()*b - lep.E()*sqrt(b4ac)) /
          (lep.E()*lep.E()-lep.Pz()*lep.Pz());
      }else{
        pz=(lep.Pz()*b + lep.E()*sqrt(b4ac)) /
          (lep.E()*lep.E()-lep.Pz()*lep.Pz());
      }
    }else{
      pz=(lep.Pz()*b) / (lep.E()*lep.E()-lep.Pz()*lep.Pz());
    }
    
    nu.SetPxPyPzE(EvtInfo_MET*cos(EvtInfo_METPhi),
                  EvtInfo_MET*sin(EvtInfo_METPhi), pz,
                  EvtInfo_MET);
    
    Wuu_P4[Wuu_No]=(nu+lep);
  
    Wuu_Mt[Wuu_No] = sqrt(2 * Leptons_P4[il1].Pt() * EvtInfo_MET *
                          ( 1 - cos(EvtInfo_METPhi-Leptons_P4[il1].Phi())));

    if(Leptons_Type[il1] == 11){
      //This W is from e and nu_e

      hist_wen_m->Fill(Wuu_P4[Wuu_No].M(), Event_Weight);
      hist_wen_mt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      hist_wen_pt->Fill(Wuu_P4[Wuu_No].Pt(), Event_Weight);
      
      // if(m_z_no_e > 0){//means take it as e nu_e,ee event
      //   hist_wen_mt_ee->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      // }
      // if(m_z_no_m > 0){//means take it as e nu_e,mumu event
      //   hist_wen_mt_mm->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      // }
      
      //Check Gen Match
      // if(m_gen_lep3_idx != -1 &&
      //    Leptons_P4[m_lep_idx].DeltaR(GenParts_P4[m_gen_lep3_idx]) < 0.3){
      //   hist_wen_gmt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      // }
      if(m_gen_wuu_idx >= 0 && 
         fabs(Wuu_P4[Wuu_No].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.35){
        hist_wen_gmt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      }
      
      //if(m_veto != 1 && Wuu_P4[Wuu_No].Mt() > W_MT_LCUT &&
      if(Wuu_Mt[Wuu_No] > W_MT_LCUT && Wuu_Mt[Wuu_No] < W_MT_HCUT){
        
        Wuu_lid[Wuu_No]=Leptons_Index[il1];
        
        // 	    //              cout << "Wuu mass: " << Wuu.mass() << endl;
        m_w_no_e++;
        Wuu_No++;
      }
    }
    if(Leptons_Type[il1] == 13){//The lepton of W is muon
      hist_wmn_m->Fill(Wuu_P4[Wuu_No].M(), Event_Weight);
      hist_wmn_mt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      hist_wmn_pt->Fill(Wuu_P4[Wuu_No].Pt(), Event_Weight);
      
      // if(m_z_no_e > 0){//The lepton of Z is electron
      //   hist_wmn_mt_ee->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      // }
      // if(m_z_no_m > 0){//The lepton of Z is muon
      //   hist_wmn_mt_mm->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      // }

      //Check GEN Match
      // if(m_gen_lep3_idx != -1 &&
      //    Leptons_P4[il1].DeltaR(GenParts_P4[m_gen_lep3_idx]) < 0.3){
      //   hist_wmn_gmt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      // }
      if(m_gen_wuu_idx >= 0 && 
         fabs(Wuu_P4[Wuu_No].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.35){
        hist_wmn_gmt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      }
      
      //if(m_veto != 1 && Wuu_P4[Wuu_No].Mt() > W_MT_LCUT &&
      if(Wuu_Mt[Wuu_No] > W_MT_LCUT && Wuu_Mt[Wuu_No] < W_MT_HCUT){
        
        Wuu_lid[Wuu_No]=Leptons_Index[il1];
        
        // 	    //              cout << "Wuu mass: " << Wuu.mass() << endl;
        m_w_no_m++;
        Wuu_No++;
      }
    }
  }
  hist_wen_no->Fill(m_w_no_e, Event_Weight);
  hist_wmn_no->Fill(m_w_no_m, Event_Weight);
}

void MyTcZAna::ReconJet(){
  Jets_No = 0;
  // Looping over jets
  if(Jets_Size > 64) cout << "Jet Size > 64!!!!!!\n\n";
  for(int ij1=0; ij1 < Jets_Size && ij1 < 64; ij1++){
    hist_jet_cut->Fill(0., Event_Weight);
    Jets_Good[ij1]=0;
    //Jets_Pt_CSV[ij1] = Jets_Pt[ij1];  
    
    //Jet energy resolution Measurement 
    if(EvtInfo_McFlag != 0) {
      double JEta = fabs(Jets_Eta[ij1]); 
      // if(JetEta[0]<=JEta && JEta < JetEta[1]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[0]*(Jets_Pt[ij1]-Jets_GenPt[ij1])); 
      // if(JetEta[1]<=JEta && JEta < JetEta[2]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[1]*(Jets_Pt[ij1]-Jets_GenPt[ij1])); 
      // if(JetEta[2]<=JEta && JEta < JetEta[3]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[2]*(Jets_Pt[ij1]-Jets_GenPt[ij1])); 
      // if(JetEta[3]<=JEta && JEta < JetEta[4]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[3]*(Jets_Pt[ij1]-Jets_GenPt[ij1])); 
      // if(JetEta[4]<=JEta && JEta < JetEta[5]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[4]*(Jets_Pt[ij1]-Jets_GenPt[ij1]));
      // if(JetEta[5]<=JEta && JEta < JetEta[6]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[5]*(Jets_Pt[ij1]-Jets_GenPt[ij1]));
      // if(JetEta[6]<=JEta && JEta < JetEta[7]) Jets_Pt[ij1] = max(0.0, Jets_GenPt[ij1] + SF_JM[6]*(Jets_Pt[ij1]-Jets_GenPt[ij1]));

    }
      
    Jets_P4[ij1].SetPtEtaPhiE(Jets_Pt[ij1], Jets_Eta[ij1],
                              Jets_Phi[ij1], Jets_Energy[ij1]);
    
    Jets_GenMatch[ij1]=-1;
    
    // /*  
    // if(EvtInfo_McFlag > 0){ // MC events
    //   flag_matched_Jet = 0;
    //   Matched_Jet_pdgid = 0;
    //   for(int gg7=0; gg7 < GenParts_Size && gg7 < 30; gg7++){
    //     int f_Gen = fabs(GenParts_PdgID[gg7]);
    //     int St_Gen = fabs(GenParts_Status[gg7]);
    //     if(f_Gen != 1 && f_Gen != 2 && f_Gen != 3 && f_Gen != 4 && f_Gen != 5 && f_Gen != 21) continue;
        
    //     GenParts_P4[gg7].SetPtEtaPhiM(GenParts_Pt[gg7], GenParts_Eta[gg7],
    //                                   GenParts_Phi[gg7], GenParts_Mass[gg7]);
    //     if(St_Gen ==3 && (Jets_P4[ij1].DeltaR(GenParts_P4[gg7])) < 0.5){
    //       Matched_Jet_pdgid = GenParts_PdgID[gg7];
    //       if(abs(GenParts_PdgID[GenParts_Mo1[gg7]])==24) flag_matched_Jet++;
    //     } 
    //     if(St_Gen ==2 && (Jets_P4[ij1].DeltaR(GenParts_P4[gg7])) < 0.5 ){
    //       Matched_Jet_pdgid = GenParts_PdgID[gg7];
    //     } 
        
    //   }//Genjet loop
      
    //   Jets_MatchingGenP4[ij1]    = Jets_P4[ij1];   
    //   Jets_MatchingGenPdgID[ij1] = Matched_Jet_pdgid; 
      
    // }// MC flag
    // */
    
    //Not cut
    if(Jets_GenJetPt[ij1]>0){
      hist_gjet_pt->Fill(Jets_Pt[ij1], Event_Weight);
      hist_gjet_eta->Fill(Jets_Eta[ij1], Event_Weight);
      hist_gjet_phi->Fill(Jets_Phi[ij1], Event_Weight);
      
      hist_jet_cut->Fill(1, Event_Weight);
    }
    
    if(Jets_P4[ij1].Pt() > JET_PT_CUT){
      hist_jet_cut->Fill(2, Event_Weight);
      
      if(fabs(Jets_Eta[ij1]) < JET_ETA_CUT){
        hist_jet_cut->Fill(3, Event_Weight);
        
        if(Jets_JetIDLOOSE[ij1] > 0){
          hist_jet_cut->Fill(4, Event_Weight);
          
          Jets_Good[ij1]=1;
          Jets_No++;
          hist_jet_cut->Fill(5, Event_Weight);
          
          hist_jet_pt->Fill(Jets_P4[ij1].Pt(), Event_Weight);
          hist_jet_eta->Fill(Jets_Eta[ij1], Event_Weight);
          hist_jet_phi->Fill(Jets_Phi[ij1], Event_Weight);
          hist_jet_btag->Fill(Jets_CombinedSVBJetTags[ij1], Event_Weight);
          
          m_st += Jets_P4[ij1].Pt();
        }//cut IDloose
      }//cut eta
    }//cut pt
    
  }//loop jet size
  
}//for Jet recon
  

void MyTcZAna::ReconBJet(){
  m_bjet_no = 0;
  m_cbjet_no = 0;

  for(int ij1=0; ij1 < Jets_Size && ij1 < 64; ij1++){
    if(Jets_Good[ij1]<1) continue;
    
    // if(Jets_CombinedSVBJetTags[ij1] >= 0) hist_jet_btag_AS_corr->Fill(Jets_CombinedSVBJetTags[ij1], Event_Weight);
    
  //b-tagging jets 
    if(Jets_CombinedSVBJetTags[ij1] > JET_BTAG_CUT){
      hist_jet_cut->Fill(6, Event_Weight);
      Jets_Good[ij1]=2;  // loose WP

      m_bjet_no++;

      if(Jets_CombinedCvsBJetTags[ij1] < JET_CBTAG_CUT) m_cbjet_no++;

      // if(Jets_GenJetPt[ij1]>0){
      //   hist_gjetc_pt->Fill(Jets_Pt[ij1], Event_Weight);
      //   hist_gjetc_eta->Fill(Jets_Eta[ij1], Event_Weight);
      //   hist_gjetc_phi->Fill(Jets_Phi[ij1], Event_Weight);
      //   hist_jet_cut->Fill(8, Event_Weight);
      // }//MC Truth

    }//medium bjet
  }//loop jet size
}//Recon B-jet End


void MyTcZAna::ReconTop(){

  // int Chi2_flag = 0;
  // int LepTopJidx = -1;
  // int HadTop_HiggsJidx1 = -1;
  // int HadTop_HiggsJidx2 = -1;
  // int HadTop_CJidx = -1;
  double ERc_cjet_gm = 0.0;
  double ERc_cjet_choose = 0.0;
  double ERc_bjet_choose = 0.0;
  // double Xsquare = 0.1;
  // double XsquareMin = -7777777;
  // double XsquareMax = 7777777;
  // double CSV_Leading_4Jets_1 = 0;
  // double CSV_Leading_4Jets_2 = 0;
  // double CSV_Leading_4Jets_3 = 0;
  // double CSV_Leading_4Jets_4 = 0;
  // double Flag_4Jets = 0;

  int m_wuu_idx = -1;
  int m_zee_idx = -1;
  int m_jet1_idx = -1; // b
  int m_jet2_idx = -1; // u,c
  int m_lep1_idx = -1; // Z l1
  int m_lep2_idx = -1; // Z l2
  int m_lep3_idx = -1; // W l

  int GM = 0;
  int flag_CSV = 0;
  double TopDR_gm = 0.0;
  double Topdphi_gm = 0.0;
  double BJetsDR_gm = 0.0;
  double BJetsdphi_gm = 0.0;
  double ZcJetDR_gm = 0.0;  
  double ZcJetdphi_gm = 0.0;
  double WbJetDR_gm = 0.0;
  double WbJetdphi_gm = 0.0; 
  double LepbJetdphi_gm = 0.0; 
    
  double TopDR = 0.0;
  double Topdphi = 0.0;
  double LepDR = 0.0;
  double Lepdphi = 0.0;
  double ZcJetDR = 0.0;  
  double ZbJetdphi = 0.0;
  double ZcJetdphi = 0.0;
  double WbJetDR = 0.0;
  double WbJetdphi = 0.0;
  double WcJetdphi = 0.0;
  double LepbJetdphi = 0.0;

  double TopMax = 99999; 
  double TopMassFlag = 0;
  // double Mass1 = 0.1;
  // double Mass2 = 0.1;
  // double Mass3 = 0.1;
  // int bbpair_flag_1 = 99;
  // int bbpair_flag_2 = 99;
  int blep_flag = 99;
  int cjet_flag = 99;
  int woring_flag = 0;

  int m_top_comb = 0;

  double SF_leptop = 1;
  double SF_hadtop = 1; 
  double WeightToppT = 1; 
  double CSVweight = 1; 

  mvaOCPE=mvaOCPEt=mvaOCPEmax=-9999.;
  mvaOCPE0=mvaOCPE0t=mvaOCPE0max=-9999.;
  
// ***********  BDT Train ************* //
/*
     if(SignalMC_flag != 0){//blep_flag should be b-jet from W side; bbpair_flag is from higgs

      Higgs_P4[0] = Jets_P4[Had_Top_Jet3_idx]+Jets_P4[Had_Top_Jet4_idx];
      Top_P4[0] = Jets_P4[Had_Top_Jet2_idx]+Higgs_P4[0];
      Top_P4[1] = Jets_P4[Lep_Top_Jet1_idx] + Wuu_P4[0];// Wuu_P4 is no matched


      HCJetDR_gm = Higgs_P4[0].DeltaR(Jets_P4[Had_Top_Jet2_idx]);
      BJetsDR_gm = Jets_P4[Had_Top_Jet3_idx].DeltaR(Jets_P4[Had_Top_Jet4_idx]);
      WbJetDR_gm = Jets_P4[Lep_Top_Jet1_idx].DeltaR(Wuu_P4[0]);
      TopDR_gm   = Top_P4[0].DeltaR(Top_P4[1]);

      HCJetdphi_gm = Higgs_P4[0].DeltaPhi(Jets_P4[Had_Top_Jet2_idx]);
      BJetsdphi_gm = Jets_P4[Had_Top_Jet3_idx].DeltaPhi(Jets_P4[Had_Top_Jet4_idx]);
      WbJetdphi_gm = Jets_P4[Lep_Top_Jet1_idx].DeltaPhi(Wuu_P4[0]);
      LepbJetdphi_gm = Jets_P4[Lep_Top_Jet1_idx].DeltaPhi(Leptons_P4_te[0]);
      Topdphi_gm   = Top_P4[0].DeltaPhi(Top_P4[1]);

      //Boost to top Coordinate
      Jets_P4[36] = Jets_P4[Had_Top_Jet2_idx];
      ERc_topCoor[0] = Top_P4[0].BoostVector();
      ERc_topCoor[1] = -ERc_topCoor[0];  
      Jets_P4[36].Boost(ERc_topCoor[1]);  
      ERc_cjet_gm = Jets_P4[36].E();
   
  JetInfo_BTAG1=Jets_CombinedSVBJetTags[Lep_Top_Jet1_idx];
  JetInfo_BTAG2=Jets_CombinedSVBJetTags[Had_Top_Jet4_idx];
  JetInfo_BTAG3=Jets_CombinedSVBJetTags[Had_Top_Jet3_idx];
  JetInfo_BTAG4=Jets_CombinedSVBJetTags[Had_Top_Jet2_idx];
  
  if(0 > JetInfo_BTAG1 || 0 > JetInfo_BTAG2 || 0 > JetInfo_BTAG3 || 0 > JetInfo_BTAG4 ) continue;
//  if(woring_flag > 2) continue;
//  if(TopInfo_M_had > 300 || TopInfo_M_lep > 300 || HInfo_M > 250 || CJetBoostInfo_E > 150) continue;

  if(TopInfo_M_had < 85 || TopInfo_M_had > 210 || 
     TopInfo_M_lep < 100 || TopInfo_M_lep > 240 || 
     CJetBoostInfo_E < 20 || CJetBoostInfo_E > 55) continue;
  mvaTree2->Fill();// For BDT-1 Training Sample signal non-matched events only
  woring_flag++;

    }//for MC flag  */// Train BDT-1 

// ****** Signal Training park BDT-1 END ********




// ***********  RealRun ************* //
//    /*FOR Signal matching method
  for(int iw=0; iw < Wuu_No ; iw++) { // W
    
    for(int iz=0; iz < Zee_No; iz++){ // Z
      if(Zee_lid1[iz] == Wuu_lid[iw] || 
         Zee_lid2[iz] == Wuu_lid[iw]) continue;  // no lepton overlap
      
      for(int ij1=0; ij1 < Jets_Size ; ij1++) { //b for bW
        if(Jets_Good[ij1] < 2) continue;  // b-tagging

        if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[Wuu_lid[iw]])) < 0.35) continue;
        if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[Zee_lid1[iz]])) < 0.35) continue;
        if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[Zee_lid2[iz]])) < 0.35) continue;
    
        for(int ij2=0; ij2 < Jets_Size ; ij2++) { //u for qZ
          if(Jets_Good[ij2] < 1) continue;  // good jet
          if(ij2 == ij1) continue;  // no jet overlap

          if(fabs(Jets_P4[ij2].DeltaR(Leptons_P4[Wuu_lid[iw]])) <0.35) continue;
          if(fabs(Jets_P4[ij2].DeltaR(Leptons_P4[Zee_lid1[iz]]))<0.35) continue;
          if(fabs(Jets_P4[ij2].DeltaR(Leptons_P4[Zee_lid2[iz]]))<0.35) continue;
      
          // Higgs_P4[0] = Jets_P4[ij2] + Jets_P4[ij3];//bbpair
          Top_P4[0] = Wuu_P4[iw] + Jets_P4[ij1]; // tree top side
          Top_P4[1] = Zee_P4[iz] + Jets_P4[ij2]; // fcnc top side

          //cout << "W lepton type: " << Leptons_Type[Wuu_lid[iw]] << endl;
          //cout << "Z lepton type: " << Leptons_Type[Zee_lid1[iz]] << endl;
          ZcJetDR   = Zee_P4[iz].DeltaR(Jets_P4[ij2]); //c Z DR
          LepDR     = Leptons_P4[Zee_lid1[iz]].DeltaR(
                                 Leptons_P4[Zee_lid2[iz]]);// 2 lep DR
          WbJetDR   = Jets_P4[ij1].DeltaR(Wuu_P4[iw]);//W b DR
          TopDR     = Top_P4[0].DeltaR(Top_P4[1]); //two top DR
              
          ZbJetdphi = Zee_P4[iz].DeltaPhi(Jets_P4[ij1]); //b Z Dphi
          ZcJetdphi = Zee_P4[iz].DeltaPhi(Jets_P4[ij2]); //c Z Dphi
          Lepdphi   = Leptons_P4[Zee_lid1[iz]].DeltaPhi(
                                   Leptons_P4[Zee_lid2[iz]]);// 2 lep Dphi
          WbJetdphi = Wuu_P4[iw].DeltaPhi(Jets_P4[ij1]); // W b Dphi
          WcJetdphi = Wuu_P4[iw].DeltaPhi(Jets_P4[ij2]); // W b Dphi
          LepbJetdphi = Jets_P4[ij1].DeltaPhi(Leptons_P4[Wuu_lid[iw]]);
                                                        //W_l b Dphi
          Topdphi   = Top_P4[0].DeltaPhi(Top_P4[1]);//two top Dphi
              
          // Boost
          Jets_P4[127] = Jets_P4[ij2];
          //ERc_topCoor[3] = Top_P4[0].BoostVector();
          //ERc_topCoor[4] = -ERc_topCoor[3];
          Jets_P4[127].Boost(-Top_P4[1].BoostVector());
          ERc_cjet_choose = Jets_P4[127].E();

          Jets_P4[126] = Jets_P4[ij1];
          Jets_P4[126].Boost(-Top_P4[0].BoostVector());
          ERc_bjet_choose = Jets_P4[126].E();
          
          // mvaTree 
          TopInfo_Pt_bw = Top_P4[0].Pt();
          TopInfo_M_bw = Top_P4[0].M();
          TopInfo_Mt_bw = Top_P4[0].Mt();
          TopInfo_Pt_cz = Top_P4[1].Pt();
          TopInfo_M_cz = Top_P4[1].M();
          TopInfo_Mt_cz = Top_P4[1].Mt();
          WInfo_Pt = Wuu_P4[0].Pt();
          WInfo_Mt = Wuu_Mt[0];
          ZInfo_Pt = Zee_P4[0].Pt();
          ZInfo_M  = Zee_P4[0].M();
          CJetBoost_E = ERc_cjet_choose;
          BJetBoost_E = ERc_bjet_choose;

          TopTop_dphi = fabs(Topdphi);
          W_bjet_dphi = fabs(WbJetdphi);
          W_cjet_dphi = fabs(WcJetdphi);
          WLep_bjet_dphi = fabs(LepbJetdphi);
          WLep_bjet_dphi = fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Wuu_lid[iw]]));
          WLep_cjet_dphi = fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Wuu_lid[iw]]));
          Z_bjet_dphi = fabs(ZbJetdphi);
          Z_cjet_dphi = fabs(ZcJetdphi);
          ZLLpair_dphi = fabs(Lepdphi);
          ZLep1_bjet_dphi =fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Zee_lid1[iz]]));
          ZLep2_bjet_dphi =fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Zee_lid2[iz]]));
          ZLep1_cjet_dphi =fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Zee_lid1[iz]]));
          ZLep2_cjet_dphi =fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Zee_lid2[iz]]));
          WLZL1_dphi = fabs(Leptons_P4[Wuu_lid[iw]].DeltaPhi(
                                                 Leptons_P4[Zee_lid1[iz]]));
          WLZL2_dphi = fabs(Leptons_P4[Wuu_lid[iw]].DeltaPhi(
                                                 Leptons_P4[Zee_lid2[iz]]));

          TopTop_DR = TopDR;
          W_bjet_DR = WbJetDR;
          Z_cjet_DR = ZcJetDR;
          ZLLpair_DR = LepDR;
          // JetInfo_BJetNumber = m_bjet_no;
          // JetInfo_JetNumber = Jet_No;

          //Jet info.

          BJet_btag = Jets_CombinedSVBJetTags[ij1];
          BJet_ctag = Jets_CombinedCvsBJetTags[ij1];
          //BJet_ltag = Jets_CombinedCvsLJetTags[ij1];
          CJet_btag = Jets_CombinedSVBJetTags[ij2];
          CJet_ctag = Jets_CombinedCvsBJetTags[ij2];
          //CJet_ltag = Jets_CombinedCvsLJetTags[ij2];
            
          //  if(TopInfo_M_had > 300 || TopInfo_M_lep > 300 || 
          //HInfo_M > 250 || CJetBoostInfo_E > 150) continue;//Basic mass cut
          // if(TopInfo_M_bw < 85 || TopInfo_M_bw > 210 || 
          //    TopInfo_M_cz < 100 || TopInfo_M_cz > 240 || 
             // CJetBoost_E < 20 || CJetBoost_E > 55) continue;
          if(TopInfo_M_bw < 50 || TopInfo_M_bw > 350 || 
             TopInfo_M_cz < 50 || TopInfo_M_cz > 350 || 
             CJetBoost_E < 0 || CJetBoost_E > 300) continue;
            
          //hist_zee_m->Fill(ZInfo_M, Event_Weight);
          hist_top_m_bw->Fill(TopInfo_M_bw, Event_Weight);
          hist_top_m_cz->Fill(TopInfo_M_cz, Event_Weight);
          //hist_top_m_lep_gen->Fill(TopInfo_M_lep, Event_Weight);
          hist_ERb->Fill(BJetBoost_E, Event_Weight);
          hist_ERc->Fill(CJetBoost_E, Event_Weight);

          m_top_comb++;

          if(EvtInfo_McFlag > 0){ // MC events

            if(m_gen_top1_idx > 0 && m_gen_top2_idx > 0 &&
               m_gen_zee_idx > 0 && m_gen_wuu_idx > 0){
              // MC traced
              
              if((fabs(Top_P4[0].DeltaR(GenParts_P4[m_gen_top1_idx])) < 0.35 &&
                  fabs(Top_P4[1].DeltaR(GenParts_P4[m_gen_top2_idx])) < 0.35) ||
                 (fabs(Top_P4[0].DeltaR(GenParts_P4[m_gen_top2_idx])) < 0.35 &&
                  fabs(Top_P4[1].DeltaR(GenParts_P4[m_gen_top1_idx])) < 0.35)){
              if(fabs(Zee_P4[iz].DeltaR(GenParts_P4[m_gen_zee_idx])) < 0.35 &&
                   fabs(Wuu_P4[iw].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.35){

                  if(m_gen_jet1_idx > 0 && ij1 < 125 &&
                     m_gen_jet2_idx > 0 && ij2 < 125 &&
                     GenParts_P4[m_gen_jet1_idx].Pt() > 0.1 &&
                     GenParts_P4[m_gen_jet2_idx].Pt() > 0.1 &&
                     fabs(Jets_P4[ij1].DeltaR(
                                         GenParts_P4[m_gen_jet1_idx]))<0.5 &&
                     fabs(Jets_P4[ij2].DeltaR(
                                         GenParts_P4[m_gen_jet2_idx]))<0.5 &&
                     fabs(Jets_P4[ij1].Rho() / 
                          GenParts_P4[m_gen_jet1_idx].Rho()) > 0.5 &&
                     fabs(Jets_P4[ij1].Rho() / 
                          GenParts_P4[m_gen_jet1_idx].Rho()) < 2.0 &&
                     fabs(Jets_P4[ij2].Rho() / 
                          GenParts_P4[m_gen_jet2_idx].Rho()) > 0.5 &&
                     fabs(Jets_P4[ij2].Rho() / 
                          GenParts_P4[m_gen_jet2_idx].Rho()) < 2.0 ){
                    TopInfo_MCTruth += 1;
                    mvaOCPEt = readerOCPE->EvaluateMVA("myOCPE");
                    mvaOCPE0t = fabs(TopTop_dphi);
                  }
                }
              }
            }
          // hist_top_dphi_gen->Fill(Tophad_Toplep_dphi, Event_Weight);
          // hist_top_LepbJet_dphi_gen->Fill(Lep_bjet_dphi, Event_Weight);
          // hist_top_HCJet_dphi_gen->Fill(H_cjet_dphi, Event_Weight);
          // hist_higgs_BJetspair_dphi_gen->Fill(BBpair_dphi, Event_Weight);
          }
          //mvaTree->Fill(); //Here mvaTree is for choosing the best combination 
          //mvaTree2->Fill();//Here mvaTree2 is for choosing the best combination 
          mvaOCPE = readerOCPE->EvaluateMVA("myOCPE");
          mvaOCPE0 = fabs(TopTop_dphi);
          //mvaOCPE0 = mvaOCPE;

          if(mvaOCPE > mvaOCPEmax){
            mvaOCPEmax = mvaOCPE;
            m_wuu_idx = iw;
            m_zee_idx = iz;
            m_jet1_idx = ij1;
            m_jet2_idx = ij2;
          }

          if(mvaOCPE0 > mvaOCPE0max){
            mvaOCPE0max = mvaOCPE0;
            //mvaOCPE0t = mvaOCPE; //readerOCPE->EvaluateMVA("myOCPE");
          }

          if(mvaTree){
            mvaTree->Fill();
            //cout << "Fill... \n";
          }

          //BDT
          //  Xsquare = fabs(Topdphi);
          
          //  Xsquare =  (Topdphi - 3.14)*(Topdphi - 3.14)/(0.5*0.5) +
          //             (TopInfo_M_lep - 170)*(TopInfo_M_lep - 170)/(26.44*26.44) +
          //             (TopInfo_M_had - 155)*(TopInfo_M_had - 155)/(32.5*32.5) + 
          //             (HInfo_M - 110)*(HInfo_M - 110)/(18.8*18.8);
          
        }
      }
    }
  }//4 objects loop
    
  hist_top_comb->Fill(m_top_comb, Event_Weight);

  if(m_top_comb > 0 ){
    if(EvtInfo_McFlag > 0 && mvaOCPEt != -9999. &&
       m_gen_top1_idx > 0 && m_gen_top2_idx > 0 &&
       m_gen_zee_idx > 0 && m_gen_wuu_idx > 0 &&
       m_gen_jet1_idx > 0 && m_gen_jet2_idx > 0){
      if(mvaOCPEt == mvaOCPEmax){
        hist_top_corr->Fill(1., Event_Weight);
      }else{
        hist_top_corr->Fill(0., Event_Weight);
      }

      if(mvaOCPE0t == mvaOCPE0max){
        hist_top_corr0->Fill(1., Event_Weight);
      }else{
        hist_top_corr0->Fill(0., Event_Weight);
      }
    }

    if( m_wuu_idx >= 0 && m_zee_idx >= 0 && m_jet1_idx >= 0 && m_jet2_idx >= 0){
      Top_P4[126] = Wuu_P4[m_wuu_idx] + Jets_P4[m_jet1_idx]; // tree top side
      Top_P4[127] = Zee_P4[m_zee_idx] + Jets_P4[m_jet2_idx]; // fcnc top side
      
      hist_fit_m_bw->Fill(Top_P4[126].M(), Event_Weight);
      hist_fit_m_cz->Fill(Top_P4[127].M(), Event_Weight);
      
      hist_fit_ctag_lc1->Fill(Jets_CombinedCvsLJetTags[m_jet1_idx], Event_Weight);
      hist_fit_ctag_lc2->Fill(Jets_CombinedCvsLJetTags[m_jet2_idx], Event_Weight);
      hist_fit_ctag_bc1->Fill(Jets_CombinedCvsBJetTags[m_jet1_idx], Event_Weight);
      hist_fit_ctag_bc2->Fill(Jets_CombinedCvsBJetTags[m_jet2_idx], Event_Weight);

      hist_fit_nbjet->Fill(m_bjet_no, Event_Weight);
      hist_fit_ncbjet->Fill(m_cbjet_no, Event_Weight);

      //hist_fit_m_zee->Fill(Zee_P4[m_zee_idx].M(), Event_Weight);
      if(fabs(Leptons_Type[Zee_lid1[m_zee_idx]]) == 11){
        hist_fit_m_zee->Fill(Zee_P4[m_zee_idx].M(), Event_Weight);
      }else{
        hist_fit_m_zmm->Fill(Zee_P4[m_zee_idx].M(), Event_Weight);
      }
      
      //hist_fit_m_wen->Fill(Wuu_P4[m_wuu_idx].M(), Event_Weight);
      if(fabs(Leptons_Type[Wuu_lid[m_wuu_idx]]) == 11){
        hist_fit_m_wen->Fill(Wuu_P4[m_wuu_idx].M(), Event_Weight);
        hist_fit_mt_wen->Fill(Wuu_Mt[m_wuu_idx], Event_Weight);
      }else{
        hist_fit_m_wmn->Fill(Wuu_P4[m_wuu_idx].M(), Event_Weight);
        hist_fit_mt_wmn->Fill(Wuu_Mt[m_wuu_idx], Event_Weight);
      }
      
      m_ht = Leptons_P4[Zee_lid1[m_zee_idx]].Pt() +
        Leptons_P4[Zee_lid2[m_zee_idx]].Pt() +
        Leptons_P4[Wuu_lid[m_wuu_idx]].Pt() +
        Jets_P4[m_jet1_idx].Pt() + Jets_P4[m_jet2_idx].Pt() + EvtInfo_MET;
    }
    
    hist_fit_ht->Fill(m_ht, Event_Weight);
    hist_fit_st->Fill(m_st, Event_Weight);
  }
            /*
            if(Chi2_flag == 1) {
              
              Higgs_P4[8] = Jets_P4[HadTop_CJidx] + Jets_P4[HadTop_HiggsJidx2];//bc
              Higgs_P4[9] = Jets_P4[HadTop_HiggsJidx1] + Jets_P4[HadTop_CJidx];//bc
              Higgs_P4[10] = Jets_P4[HadTop_HiggsJidx1] + Jets_P4[HadTop_HiggsJidx2];//bb

              Higgs_P4[5] = Jets_P4[HadTop_HiggsJidx1] + Jets_P4[HadTop_HiggsJidx2];
              Top_P4[5] = Higgs_P4[5] + Jets_P4[HadTop_CJidx];
              Top_P4[6] = Jets_P4[LepTopJidx] + Wuu_P4[0];//// decision top mass(Lep) cut(decide bje110

              HCJetDR   = Higgs_P4[5].DeltaR(Jets_P4[HadTop_CJidx]);//c higgs DR
              BJetsDR   = Jets_P4[HadTop_HiggsJidx1].DeltaR(Jets_P4[HadTop_HiggsJidx2]);//bbpair DR
              HCJetdphi = Higgs_P4[5].DeltaPhi(Jets_P4[HadTop_CJidx]);//c higgs Dphi
              BJetsdphi = Jets_P4[HadTop_HiggsJidx1].DeltaPhi(Jets_P4[HadTop_HiggsJidx2]);//leading bbpair Dphi
              WbJetdphi = Jets_P4[LepTopJidx].DeltaPhi(Wuu_P4[0]);//W third_b Dphi
              WbJetDR   = Jets_P4[LepTopJidx].DeltaR(Wuu_P4[0]);//W third_b DR
              Topdphi   = Top_P4[5].DeltaPhi(Top_P4[6]);//two top Dphi
              TopDR     = Top_P4[5].DeltaR(Top_P4[6]);//two top DR
              LepbJetdphi = Jets_P4[LepTopJidx].DeltaPhi(Leptons_P4_te[0]);//W third_b Dphi

              // Boost
              Jets_P4[41] = Jets_P4[HadTop_CJidx];
              ERc_topCoor[8] = Top_P4[5].BoostVector();
              ERc_topCoor[9] = -ERc_topCoor[8];
              Jets_P4[41].Boost(ERc_topCoor[9]);
              ERc_cjet_choose = Jets_P4[41].E();
              */

   

            // ** mvaTree **
            // TopInfo_Pt_had = Top_P4[5].Pt();
            // TopInfo_M_had = Top_P4[5].M();
            // TopInfo_Mt_had = Top_P4[5].Mt();
            // TopInfo_Pt_lep = Top_P4[6].Pt();
            // TopInfo_M_lep = Top_P4[6].M();
            // TopInfo_Mt_lep = Top_P4[6].Mt();
            /*
            WInfo_Pt = Wuu_P4[0].Pt();
            WInfo_Mt = Wuu_Mt[0];
            HInfo_Pt = Higgs_P4[5].Pt();
            HInfo_M  = Higgs_P4[5].M();
            CJetBoostInfo_E = ERc_cjet_choose;

            Tophad_Toplep_dphi = fabs(Topdphi);
            W_bjet_dphi = fabs(WbJetdphi);
            Lep_bjet_dphi = fabs(LepbJetdphi);
            H_cjet_dphi = fabs(HCJetdphi);
            BBpair_dphi = fabs(BJetsdphi);
            Tophad_Toplep_DR = TopDR;
            W_bjet_DR = WbJetDR;
            H_cjet_DR = HCJetDR;
            BBpair_DR = BJetsDR;
            JetInfo_BJetNumber = m_bjet_no;
            JetInfo_JetNumber = Jet_No;

            //B_Jets info.
            Jet_b_Info_Pt_Lep = Jets_P4[LepTopJidx].Pt();
            Jet_b_Info_Pt_Had1 = Jets_P4[HadTop_HiggsJidx2].Pt();
            Jet_b_Info_Pt_Had2 = Jets_P4[HadTop_HiggsJidx1].Pt();
            
            //Jet info.
            JetInfo_BTAG1 = Jets_CombinedSVBJetTags[LepTopJidx];//b(lep)
            JetInfo_BTAG2 = Jets_CombinedSVBJetTags[HadTop_HiggsJidx1];//bb pair
            JetInfo_BTAG3 = Jets_CombinedSVBJetTags[HadTop_HiggsJidx2];
            JetInfo_BTAG4 = Jets_CombinedSVBJetTags[HadTop_CJidx];//c(had)
            JetInfo_M1 = Jets_P4[LepTopJidx].M();
            JetInfo_M2 = Jets_P4[HadTop_HiggsJidx1].M();
            JetInfo_M3 = Jets_P4[HadTop_HiggsJidx2].M();
            JetInfo_M4 = Jets_P4[HadTop_CJidx].M();
            */
            /*
              if(0 <= JetInfo_BTAG1 && 0 <= JetInfo_BTAG2 && 0 <= JetInfo_BTAG3 && 0 <= JetInfo_BTAG4 ){
              
              //top pT reweighting
              hist_top_pt->Fill(TopInfo_Pt_had, Event_Weight);
              hist_top_pt->Fill(TopInfo_Pt_lep, Event_Weight);
              if(EvtInfo_McFlag > 0){
              SF_leptop = exp(0.156 - 0.00137*TopInfo_Pt_lep);//Twiki page
              SF_hadtop = exp(0.156 - 0.00137*TopInfo_Pt_had);
              WeightToppT = sqrt(SF_leptop*SF_hadtop);
              if(ToppT_UNC== 1) WeightToppT = WeightToppT*WeightToppT;
              if(ToppT_UNC== -1) WeightToppT = 1;
              Event_Weight = Event_Weight * WeightToppT;
              }
              hist_top_pt_afc->Fill(TopInfo_Pt_had, Event_Weight);
              hist_top_pt_afc->Fill(TopInfo_Pt_lep, Event_Weight);
              
              // CSV correction reweighting
              //   if(EvtInfo_McFlag > 0)  Event_Weight = Event_Weight * csvWgtTotal[CSVerrorType];

              hist_higgs_m_had_Back->Fill(Higgs_P4[8].M(), Event_Weight);//Higgs mass of all combination 
              hist_higgs_m_had_Back->Fill(Higgs_P4[9].M(), Event_Weight);
              hist_higgs_m_had_Back->Fill(Higgs_P4[10].M(), Event_Weight);
              hist_higgs_pt_had_Back->Fill(Higgs_P4[8].Pt(), Event_Weight);
              hist_higgs_pt_had_Back->Fill(Higgs_P4[9].Pt(), Event_Weight);
              hist_higgs_pt_had_Back->Fill(Higgs_P4[10].Pt(), Event_Weight);
              hist_jet_btag_value_1_Func->Fill(JetInfo_BTAG2, Event_Weight);//for the CSVcorrection()
              hist_jet_btag_value_2_Func->Fill(JetInfo_BTAG3, Event_Weight);
              hist_jet_btag_value_3_Func->Fill(JetInfo_BTAG4, Event_Weight);
              
              hist_higgs_m_had->Fill(HInfo_M, Event_Weight);
              hist_higgs_pt_had->Fill(HInfo_Pt, Event_Weight);
              hist_top_m_had->Fill(TopInfo_M_had, Event_Weight);
              hist_top_mt_had->Fill(TopInfo_Mt_had, Event_Weight);
              hist_top_pt_had->Fill(TopInfo_Pt_had, Event_Weight);
              hist_top_m_lep->Fill(TopInfo_M_lep, Event_Weight);
              hist_top_mt_lep->Fill(TopInfo_Mt_lep, Event_Weight);
              hist_top_pt_lep->Fill(TopInfo_Pt_lep, Event_Weight);
              hist_ERc->Fill(CJetBoostInfo_E, Event_Weight);
              hist_higgs_BJetspair_dphi->Fill(BJetsdphi, Event_Weight);
              hist_jet_btag_value_4Jets_1->Fill(CSV_Value_Leading_4Jets_1, Event_Weight);
              hist_jet_btag_value_4Jets_2->Fill(CSV_Value_Leading_4Jets_2, Event_Weight);
              hist_jet_btag_value_4Jets_3->Fill(CSV_Value_Leading_4Jets_3, Event_Weight);
              hist_jet_btag_value_4Jets_4->Fill(CSV_Value_Leading_4Jets_4, Event_Weight);
              hist_jet_no_c->Fill(JetInfo_JetNumber, Event_Weight);
              

              hist_jet_btag_value_lep->Fill(JetInfo_BTAG1, Event_Weight);
              hist_jet_btag_value_1->Fill(JetInfo_BTAG2, Event_Weight);
              hist_jet_btag_value_2->Fill(JetInfo_BTAG3, Event_Weight);
              hist_jet_btag_value_3->Fill(JetInfo_BTAG4, Event_Weight);
              
              //CSV distribution in signal region
              for(int ijs = 0; ijs< Jets_Size; ijs++){
              if(Jets_Good[ijs] < 1) continue;
              hist_jet_btag_s->Fill(Jets_CombinedSVBJetTags[ijs],Event_Weight);
              if(Jets_Good[ijs] != 2) continue;
              hist_jet_btag_s_bjet->Fill(Jets_CombinedSVBJetTags[ijs],Event_Weight);
              }
              
              if(EvtInfo_McFlag > 0){
              
              double SF_pdgid0 = 0; double SF_pdgid0_T = 0;
              int SF_pdgid0_NO = 0; int flag_pdgid0_NO = 0;
              for(int ij = 0; ij< Jets_Size; ij++){
              if(Jets_Good[ij] < 1) continue;
              hist_pdgid->Fill(Jets_GenPdgID[ij],1);
              hist_pdgid_match->Fill(Jets_MatchingGenPdgID[ij], 1);
              hist_flavor->Fill(Jets_GenFlavor[ij],1);
              
              if(Jets_GenPdgID[ij]==0){
              hist_jet_btag_pdgid0->Fill(Jets_CombinedSVBJetTags[ij],1);
              SF_pdgid0_NO++;
              SF_pdgid0 = SF_pdgid0 + csvWgt[CSVerrorType][ij];
              flag_pdgid0_NO=1;
              }
              }
              if (flag_pdgid0_NO == 1){
              SF_pdgid0_T = SF_pdgid0/SF_pdgid0_NO;
              hist_jet_SF_pdgid0->Fill(SF_pdgid0_T,1);
              }
              
              for(int cc = 0 ; cc < 9 ; cc++){
              EvtWei[cc] = Event_Weight * csvWgtTotal[cc];
              EvtWeiTotal[cc] += EvtWei[cc];
              }
              
              CSVweight = csvWgt[CSVerrorType][HadTop_HiggsJidx1]*csvWgt[CSVerrorType][HadTop_HiggsJidx2]*csvWgt[CSVerrorType][HadTop_CJidx];
              
              EvtInfo_EvtWeiTri = Event_Weight;
              Event_Weight = Event_Weight * csvWgtTotal[CSVerrorType];//all Good jet weight include CSV correction
              }

              //pt distribution
              hist_higgs_pt_had_afc->Fill(HInfo_Pt, Event_Weight);
              hist_top_pt_lep_afc->Fill(TopInfo_Pt_lep, Event_Weight);
              hist_top_pt_had_afc->Fill(TopInfo_Pt_had, Event_Weight);

              //Missin energy and transverse mass   
              if(m_te_no==1){
              hist_wen_m_3b->Fill(Wuu_P4[0].M(), Event_Weight);
              hist_wen_mt_3b->Fill(Wuu_Mt[0], Event_Weight);
              hist_higgs_m_had_afc_e->Fill(HInfo_M, Event_Weight);
              //      TotalEvents_E = TotalEvents_E + Event_Weight;
              }
              if(m_tm_no==1){
              hist_wmn_m_3b->Fill(Wuu_P4[0].M(), Event_Weight);
              hist_wmn_mt_3b->Fill(Wuu_Mt[0], Event_Weight);
              hist_higgs_m_had_afc_m->Fill(HInfo_M, Event_Weight);
              //      TotalEvents_M = TotalEvents_M + Event_Weight;
              }
              hist_met_pt_3b->Fill(EvtInfo_MET, Event_Weight); 

              EvtInfo_CSVWei = csvWgtTotal[CSVerrorType];
              EvtInfo_EvtWei = Event_Weight;
              
              //  if( 0.4 < JetInfo_BTAG4 && 0.7 > JetInfo_BTAG4 ) {
              
              mvaTree->Fill();
              
              //  }//0.7 test

              //ANN
              mvaValue_ann = reader->EvaluateMVA( "myANN" );
              hist_ann->Fill(mvaValue_ann,Event_Weight);       
              hist_ann_test->Fill(mvaValue_ann,Event_Weight);       
              BDT_value = mvaValue_ann;
              
              //Missin energy and transverse mass   
              if(m_te_no==1){
              BDT_value_e = mvaValue_ann;
              }
              if(m_tm_no==1){
              BDT_value_m = mvaValue_ann;
              }


              hist_evt_cut->Fill(7, Event_Weight);
              if((m_e_no == 1) && (m_m_no == 0)) 
              hist_evt_cut_e->Fill(7, Event_Weight);
              else if((m_e_no == 0) && (m_m_no == 1)) 
              hist_evt_cut_m->Fill(7, Event_Weight);
              
              // ** check gen-matching **
              if(EvtInfo_McFlag > 0){
              if(m_gen_evt_type == _bWch_lepJet) {
              if( (Jets_P4[HadTop_CJidx].DeltaR(GenParts_P4[m_gen_jet2_idx]) < 0.5) ) flagTMVAGA = 1;//c had side
              
              if( Jets_P4[LepTopJidx].DeltaR(GenParts_P4[m_gen_jet1_idx]) < 0.5 ) flagChi2 = 1;//b lep side
              
              if( ((Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5) || 
              (Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5) )&&
              ((Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5) || 
              (Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5) )
              ) flagTMVABDT = 1;//bbpair had side
              }//is Signal?
              }//is MC?
              // ** END **

              if(EvtInfo_McFlag > 0){
              fout << EvtInfo_PDFid1 << "   " << EvtInfo_PDFid2 << "   "
              << EvtInfo_PDFx1 << "   " << EvtInfo_PDFx2 << "   "
              << EvtInfo_PDFscale   
              << "   " << EvtInfo_PDFv1 << "   " << EvtInfo_PDFv2 << "  " 
              << Event_Weight << "  "<< mvaValue_ann << std::endl;
            */              
  //}
  //  } //mvaTree Cut (all CSV>0)
  //    }//Chi2_flag
  // */

      /*
        if(EvtInfo_McFlag > 0){
        //Signal check
        if(m_gen_evt_type == _bWch_lepJet) {
        if(Jets_P4[HadTop_CJidx].DeltaR(GenParts_P4[m_gen_jet2_idx])<0.5) flagChi2 = 1;  
        if( ((Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5) && (Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5)) ||
        ((Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5) && (Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5))
        ) flagTMVABDT = 1;
        if( 
        ((Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet2_idx]) < 0.5) || 
        (Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5) || 
        (Jets_P4[HadTop_HiggsJidx1].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5)) 
        &&
        ((Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet2_idx]) < 0.5) || 
        (Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5) || 
        (Jets_P4[HadTop_HiggsJidx2].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5)) 
        &&
        ((Jets_P4[HadTop_CJidx].DeltaR(GenParts_P4[m_gen_jet2_idx]) < 0.5) || 
        (Jets_P4[HadTop_CJidx].DeltaR(GenParts_P4[m_gen_jet3_idx]) < 0.5) || 
        (Jets_P4[HadTop_CJidx].DeltaR(GenParts_P4[m_gen_jet4_idx]) < 0.5)) 
        ) flagTMVAGA = 1;
        }
        
        }//MC flag
      */

      // Higgs_P4[5] = Jets_P4[HadTop_HiggsJidx1] + Jets_P4[HadTop_HiggsJidx2];
      // Top_P4[5] = Jets_P4[HadTop_CJidx]+Higgs_P4[5];
      /*
      // Boost
      Jets_P4[40] =Jets_P4[HadTop_CJidx];
      ERc_topCoor[3] = Top_P4[5].BoostVector();
      ERc_topCoor[4] = -ERc_topCoor[3];
      Jets_P4[40].Boost(ERc_topCoor[4]);
      ERc_cjet_choose = Jets_P4[40].E();
      
      TopInfo_M_had = Top_P4[5].M();
      HInfo_M  = Higgs_P4[5].M();
      CJetBoostInfo_E = ERc_cjet_choose;
      
      H_cjet_dphi = Higgs_P4[5].DeltaPhi(Jets_P4[HadTop_CJidx]);
      BBpair_dphi = Jets_P4[HadTop_HiggsJidx1].DeltaPhi(Jets_P4[HadTop_HiggsJidx2]);
      
      //Jet info.
      JetInfo_BTAG2 = Jets_CombinedSVBJetTags[HadTop_HiggsJidx1];//bb pair
      JetInfo_BTAG3 = Jets_CombinedSVBJetTags[HadTop_HiggsJidx2];
      JetInfo_BTAG4 = Jets_CombinedSVBJetTags[HadTop_CJidx];//c(had)
      */
      //mvaTree->Fill();
 
}//for ReconTop7()

