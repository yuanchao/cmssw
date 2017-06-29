#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "THStack.h"
#include "TLegend.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "TH1F.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
#include "TArrow.h"
#include "TRef.h"
#include "TApplication.h"
#include "TError.h"
#include "TMath.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TLine.h"

#include <vector>

// /* processed events
//#define TcZ 664441 // 591864 // 601931
#define TcZ 591864 // 601931
#define ttjets 999999
#define t_s 998400
#define t_t 19681068
#define t_tw 1000000
#define tb_s 999999
#define tb_t 999999
#define tb_tw 999999

#define ttwqq 831847
#define ttwln 250307
#define ttzqq 747000
#define ttzll 128800
#define wz2l2q 11996330
#define wz3ln 12560069  // 5.48837e+06  // 3801447

#define zjets 999999999999
#define zz2l2n 999999
#define zz2l2q 9999999
#define zz4l 9999999
#define ww 9999999
#define tthiggs 999999
#define wjets 9999999999999

// Integrated Lumi.

// 160404-163869 	214.54 /pb   May 10   214.54
// 165071-166500 	328.79 /pb   PRv4
// 166501-167913 	587.43 /pb            1130.76
// 170249-172619 	284.55 /pb   PRv5
// 172620-173692 	653.97 /pb   PRv6     2069.28
// 175832-176023 	122.13 /pb
// 176024-177053 	613.12 /pb
// 177054-178078 	622.51 /pb
// 178079-178677 	276.00 /pb

//#define INT_LUM 214.54
//#define INT_LUM 916.22
//#define INT_LUM 284.55
//#define INT_LUM 653.97
//#define INT_LUM 626.24
//#define INT_LUM 1130.76
//#define INT_LUM 1058.66
//#define INT_LUM 2069.28
//#define INT_LUM 1000.

//#define INT_LUM 201.76
//#define INT_LUM 930.21
//#define INT_LUM 313.04
//#define INT_LUM 658.89
//#define INT_LUM 1131.97
//#define INT_LUM 2103.90
//#define INT_LUM 2510.90
//#define INT_LUM 19468.


//#define INT_LUM 5318 //Run2012 AB
//#define INT_LUM 19788 //Run2012 ABCD

//new Pre-cut normalized
//#define INT_LUM 1.80433813536287053e+04//MET
//#define INT_LUM 1.78636979328051020e+04//hist_wmn_mt_3b
//#define INT_LUM 1.87488901498339837e+04//hist_wen_mt_3b


#define INT_LUM 18279.6772126550495//Signal resion - Higgs
//#define INT_LUM 18240.0826437974501//Signal resion - CSV 
//#define INT_LUM 19309.1501746216527//Control resion - Higgs
//#define INT_LUM 1.93088333541226821e+04//Control resion - CSV

//#define INT_LUM 18296.7592298147065//Signal region - for uH channel

vector<TH1*>nPFJets;
vector<TH1*>mTopCZ;
vector<TH1*>mTopBW;
vector<TH1*>htSig;
vector<TH1*>htOther;

vector<TH1*>massZee;
vector<TH1*>massZmm;
vector<TH1*>ptZee;
vector<TH1*>ptZmm;
vector<TH1*>METee;
vector<TH1*>METee3b;
vector<TH1*>METmm;
vector<TH1*>METeel;
vector<TH1*>METmml;
vector<TH1*>WeMTee;
vector<TH1*>WeMTmm;
vector<TH1*>WmMTee;
vector<TH1*>WmMTmm;

vector<TH1*>VtxNo;
vector<TH1*>VtxNDoF;
vector<TH1*>VtxVz;
vector<TH1*>VtxVrho;

vector<TH1*>ElecPt;
vector<TH1*>ElecEta;
vector<TH1*>ElecPhi;
vector<TH1*>ElecMVA;

vector<TH1*>MuonPt;
vector<TH1*>MuonEta;
vector<TH1*>MuonPhi;
 
vector<TH1*>JetNo;
vector<TH1*>BJetNo;
vector<TH1*>JetPt;
vector<TH1*>JetEta;
vector<TH1*>JetPhi;

vector<TH1*>HiggsMass;
vector<TH1*>HiggsMassBack;
vector<TH1*>HiggspT;
vector<TH1*>HiggspTBack;
vector<TH1*>HiggsMassGem;

vector<TH1*>TopMassZq;
vector<TH1*>TopMassWb; 
vector<TH1*>ToppTHad;
vector<TH1*>ToppTLep; 
vector<TH1*>ToppT; 
vector<TH1*>HiggspTAFC;
vector<TH1*>HiggsMassAFC;
vector<TH1*>HiggsMassAFCE;
vector<TH1*>HiggsMassAFCM;
vector<TH1*>TopMassHadAFC;
vector<TH1*>TopMassLepAFC; 
vector<TH1*>ToppTHadAFC;
vector<TH1*>ToppTLepAFC; 
vector<TH1*>ToppTAFC; 
//vector<TH1*>TopMassGem;

vector<TH1*>Final_Mtop_bw;
vector<TH1*>Final_Mtop_cz;
vector<TH1*>Final_MZ_ee;
vector<TH1*>Final_MZ_mm;
vector<TH1*>Final_MtW_en;
vector<TH1*>Final_MtW_mn;
vector<TH1*>Final_HT;
vector<TH1*>Final_ST;
vector<TH1*>Final_cTag_lc1;
vector<TH1*>Final_cTag_lc2;
vector<TH1*>Final_cTag_bc1;
vector<TH1*>Final_cTag_bc2;
vector<TH1*>Final_nbJet;
vector<TH1*>Final_ncbJet;

//const int nFiles=20; //matrix weight but number is 0 to 16
const int nFiles=17; //matrix weight but number is 0 to 16
//const int nFiles=22; //matrix weight but number is 0 to 16

std::string Labels[nFiles+3]=
  {

                                  "t#rightarrowZq (B=0.05%)",       // T2ZQ
                                  "t#bar{t}",            // ttjets
//                                  "TTJetsWtoBC",            // ttjets in W decay to BC
                                  "t#bar{t}H",            // tthiggs
                                  "t#bar{t}W / t#bar{t}Z",  // ttwjets
                                  "t#bar{t}W",           // ttwjets
                                  "t#bar{t}Z",            // ttzjets
                                  "t#bar{t}Z",            // ttzjets
                                  "Z/#gamma*/W+Jets",        // zjets
                                  "Drell Yan",        // zjets10to50
                                  "W+Jets",        // wjets
                                  "W+Jets",        // wbbjets
                                  "VV",     // ww
                                  "VV",      // wz2l2q
                                  "VV",      // wz3ln
                                  "VV",     // zz2l2n
                                  "VV",      // zz2l2q
                                  "VV",        // zz4l
                                  "Single top",       // t_s
                                  //"Single top",    // tb_s
                                  "Single top",       // t_t
                                  //"Single top",    // tb_t
                                  "Single top"//,      // t_tw
                                  //"Single top",   // tb_tw
                                  //               "Data"   // tb_tw
};

std::string histFiles[nFiles+3]=
  {
//                              "plot_BG_MC/hist_ttjetsWtoBC_1.root",     // ttjets
    "sig_TTbWcZ_3LPY8_K_Zct.root",  // T2CZ
    "sig_TTbWcZ_3LPY8_10.root",     // ttjets
    "sig_TTbWcZ_3LPY8_10.root",     // tthiggs
    "ttwqq_TTbWcZ_3LPY8.root", // ttwqq
    "ttwln_TTbWcZ_3LPY8.root", // ttwln
    "ttzqq_TTbWcZ_3LPY8.root",   // ttzqq
    "ttzll_TTbWcZ_3LPY8.root",   // ttzll
    "sig_TTbWcZ_3LPY8_10.root",   // zjets
    //    "sig_TTbWcZ_3LPY8_10.root",   // zjets10to50
    "sig_TTbWcZ_3LPY8_10.root",   // wjets
    "sig_TTbWcZ_3LPY8_10.root",   // wbbjets
    "sig_TTbWcZ_3LPY8_10.root",     // ww
    "sig_TTbWcZ_3LPY8_10.root",   // wz2l2q
    "wz_TTbWcZ_3LPY8.root",   // wz3ln
    "sig_TTbWcZ_3LPY8_10.root",   // zz2l2n
    "sig_TTbWcZ_3LPY8_10.root",   // zz2l2q
    "sig_TTbWcZ_3LPY8_10.root",   // zz4l
    "st-s_TTbWcZ_3LPY8.root", // t_s
    "st-t_TTbWcZ_3LPY8.root", // t_t
    "st-tW_TTbWcZ_3LPY8.root",   // t_tw
 	
    "dataTTbWcZ_2016C.root"
    //"sig_TTbWcZ_3LPY8_10.root"
};

double hist_scale[nFiles+3] = 
  {
    2*0.0005*831.76*0.10099*0.324 *INT_LUM/TcZ,       // T2HC  0.10099 Z->ll; 0.324 W->lepton and tau; FCNC 0.1%
    0.            *INT_LUM/ttjets,     // ttjets
    0.          *INT_LUM/tthiggs,     // tthiggs   
    0.4062          *INT_LUM/ttwqq,    // ttwjets 0.2148
    0.2043          *INT_LUM/ttwln,    // ttwjets 0.2148
    0.5297           *INT_LUM/ttzqq,    // ttzjets 0.172
    0.2529           *INT_LUM/ttzll,    // ttzjets 0.172
    0.000          *INT_LUM/zjets,      // zjets
    //    0.000           *INT_LUM/zjets10to50,      // zjets10to50 //13124
    0.000         *INT_LUM/wjets,      // wjets 37509 
    //0.000           *INT_LUM/wbbjets,      // wjets
    //000.           *INT_LUM/ww,         // ww2l2n
    0*5.595          *INT_LUM/wz2l2q,     // wz2l2q
    5.26            *INT_LUM/wz3ln,      // wz3ln
    0*0.564          *INT_LUM/zz2l2n,     // zz2l2n
    0*3.22           *INT_LUM/zz2l2q,     // zz2l2q
    0*1.212           *INT_LUM/zz4l,       // zz4l
    3.36            *INT_LUM/t_s,        // t_s
    44.33           *INT_LUM/t_t,        // t_t
    35.85           *INT_LUM/t_tw,       // t_tw
};

double histMax[30];// = {30, };

//int histColor[nFiles] = {kRed+1, kRed-7, kGreen-3, kAzure-2, kGreen-9,
int histColor[nFiles+3] = 
  {
    kWhite,     // T2CZ
    kRed+1,     // ttjets
    //                                kRed+1,     // ttjetsWtoBC
    kRed-5,     // tthiggs
    kAzure-7,   // ttwqq
    kAzure-7,   // ttwln
    kAzure-7,   // ttzqq
    kAzure-7,   // ttzll
    kAzure-2,   // zjets
    kAzure-2,   // wjets
    kAzure+8,     // ww
    kAzure+8,     // ww
    kAzure+8,   // wz2l2q
    kAzure+8,   // wz3ln
    kAzure+8,   // zz2l2n
    kAzure+8,   // zz2l2q
    kAzure+8,   // zz4l
    kMagenta, // t_s
    kMagenta, // t_t
    kMagenta,   // t_tw
    kBlack    // data
};

TFile* inFile[nFiles+2];
  

void plot_hist(TCanvas *c1, vector<TH1*> &hists, //vector<TH1*> &hdata,
	       std::string histName, int nfiles, std::string xlabel="test",int x1=-1000,int x2=1000,int y=500){

//   TPad *pad1 = new TPad("pad1","pad1",0,0.27,1,1);//addpa
//   TPad *pad2 = new TPad("pad2","pad2",0,0.05,1,0.27);//addpa
//   TPad *pad1 = new TPad("pad1","pad1",0,0.11,1,1);//addpa
//   TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.);//addpa
 
  //TCanvas *c1 = new TCanvas("c1","",600,600); 
  c1->cd();
  //c1->SetBottomMargin(0.002);
  c1->SetLeftMargin(0.17);
  c1->SetRightMargin(0.05);
  c1->SetTopMargin(0.06);
  c1->SetBottomMargin(0.13);

//  pad1->SetTopMargin(0.05);
//  pad1->SetBottomMargin(0.13);
  
//   pad1->Draw();//addpa
//   pad1->cd();//addpa
//   TLegend* leg = new TLegend(0.60,0.70,0.85,0.93);
//   leg->SetTextSize(0.03);
//   leg->SetFillColor(0);

//   TLatex *t1a = new TLatex(0.40,0.85,"CMS Preliminary");
//   t1a->SetTextFont(42);
//   t1a->SetTextSize(0.05);
//   t1a->SetTextAlign(22);
//   t1a->SetNDC(kTRUE); 
  std::string ylabel="Events";
  std::string ydlabel="Ratio";
  const int size = nfiles;
  TH1* plots[size+3];
  Float_t tgx[500], tgy[500], tgex[500], tgey[500];
  Float_t tgxe[500], tgye[500], tgexe[500], tgeye[500];

  TH1* sigHist;
  //THStack* bkgHist=new THStack("bkg", histName.c_str());
  TH1* bkgHist;
  THStack* allHist=new THStack("all", histName.c_str());
  TH1F* deno;//addpa
  TH1F* deno2;//addpa

  //cout << "   to make plots... " << hists.size() << endl;

  TLegend* leg = new TLegend(0.65,0.45,0.92,0.9);
  //TLegend* leg = new TLegend(0.4,0.32,0.65,0.9);
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  //leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetLineStyle(0);
  leg->SetTextFont(42);
  leg->SetFillStyle(1);
  //leg->AddEntry(hdata, hdata->GetTitle(), "lp");

  //for(int i = 0; i < nfiles; i++){
  for(int i = nfiles-1; i >= 0; i--){
   // if(i==7 || i==8 || i==9) continue;

    std::string histname = hists[i]->GetName();
   // histname = hists[i]->GetName();
    char name[100];
    sprintf(name,"%s_%d.png",histname.c_str(),i);
    
    plots[i] = (TH1*)hists[i]->Clone(histname.c_str());
//    plots[i]->SetXTitle(xlabel.c_str());
//     plots[i]->GetXaxis()->SetLabelSize(0.10);
//     plots[i]->GetYaxis()->SetLabelSize(0.045);
//     plots[i]->GetYaxis()->SetLabelOffset(0.005);
    plots[i]->GetXaxis()->SetLabelSize(0.06);
    plots[i]->GetYaxis()->SetLabelSize(0.05);
    plots[i]->GetYaxis()->SetLabelOffset(0.005);

    //if(xlabel.find("[") < xlabel.Length())
    char label[100];
    char labeld[100];
    sprintf(label, "%s", ylabel.c_str());
    sprintf(labeld, "%s", ydlabel.c_str());
    if(xlabel.find("[") < 80){
      sprintf(label, "%s / %d %s", ylabel.c_str(),
              (int)plots[i]->GetBinWidth(1), xlabel.c_str()+xlabel.find("[")+1);
      label[strlen(label)-1]=0;
    }
    //ylabel=ylabel+" / "+plots[i].GetBinWidth(1);//+std::string(plots[i].GetBinWidth(1));//+xlabel.c_str()+xlabel.find("[");
    plots[i]->SetYTitle(label);//ylabel.c_str());
    plots[i]->GetYaxis()->SetTitleOffset(1.32);
    plots[i]->GetYaxis()->SetTitleSize(0.065);
    plots[i]->GetXaxis()->SetLabelSize(0.05);
    plots[i]->GetXaxis()->SetTitleSize(0.06);
    plots[i]->SetXTitle(xlabel.c_str());
    //plots[i]->GetXaxis()->SetTitleSize(0.18);

    //plots[i]->GetYaxis()->SetRangeUser(0,1.2*plots[i]->GetMaximum()); // linear scale
    //plots[i]->GetYaxis()->SetRangeUser(0,1.2*log(plots[i]->GetMaximum()));  // log scale

    // add overflow bin
    // plots[i]->SetBinContent(plots[i]->GetNbinsX(),
    //                         plots[i]->GetBinContent(plots[i]->GetNbinsX())+
    //                         plots[i]->GetBinContent(plots[i]->GetNbinsX()+1));

    plots[i]->Scale(hist_scale[i]);

    plots[i]->SetFillColor(histColor[i]);

    if(plots[i]->GetNbinsX() > 10) plots[i]->Rebin(2);
      plots[i]->GetYaxis()->SetRangeUser(0,20000);
      //plots[i]->GetYaxis()->SetLimits(0,20000);

//set line color


       if(i == 0) plots[i]->SetLineColor(kBlack);
       else plots[i]->SetLineColor(histColor[i]);
/*
       if(//omit line color
        i == 1 ||
        i == 2 ||
        i == 3 ||
        i == 5 ||
        i == 7 ||
        i == 9 ||
        i == 10||
        i == 11||
        i == 12||
        i == 13||
        i == 15||
        i == 16||
        i == 17||
        i == 18||
        i == 19||
        i == 20
      )
      plots[i]->SetLineColor(histColor[i]); 
*/




//      plots[i]->Draw("");
//      c1->SaveAs(name);     

    if(i==0){
       sigHist=(TH1*)plots[i]->Clone();
       //allHist=(TH1*)plots[i]->Clone();
    }else if(i==nfiles-1){
       //bkgHist->SetHistogram(plots[i]);
       //bkgHist->Add(plots[i]);
       
       allHist->SetHistogram(plots[i]);
       allHist->Add(plots[i]);
       bkgHist=(TH1*)plots[i]->Clone();
       
       deno=(TH1F*)plots[i]->Clone("divider");//addpa
    }else{
       bkgHist->Add(plots[i]);
       allHist->Add(plots[i]);
       deno->Add(plots[i]);//addpa
    }		    
  }

//  hists[nfiles+1]->SetMarkerStyle(20);  //fate2.root
//  hists[nfiles+1]->SetMarkerSize(1.0);

//  leg->AddEntry(hists[nfiles+1], "Data", "lp");



//RRR
  //allHist->Add(sigHist);
  //set maximum height of plot
  allHist->SetMaximum(allHist->GetMaximum()*1.25);
  //allHist->SetMaximum(3000);
  
  allHist->UseCurrentStyle();

  if(allHist->GetXaxis()->GetXmax()==150){
    allHist->GetXaxis()->SetRangeUser(30, 150);
  }
  allHist->Draw();
  //cout << "draw all" << endl;

  sigHist->UseCurrentStyle();
  sigHist->SetLineWidth(3);
  //sigHist->SetLineColor(7);
  //sigHist->SetLineColor(kBlack);
  sigHist->SetLineColor(kRed+3);
  //sigHist->Scale(20);
  //sigHist->SetEntries(7700);
  //sigHist->SetMaximum(2000);
  //signal_plot
  sigHist->Draw("same");


  bkgHist->UseCurrentStyle();
  bkgHist->SetLineColor(kBlack);
  bkgHist->SetFillColor(0);
  bkgHist->SetLineWidth(2);
  //cout<<"Background "<<bkgHist->Integral()<< endl;//don't plot data
  bkgHist->DrawCopy("same");

  bkgHist->Sumw2();
  //cout << "background done\n";
 /* CSV error check
  TH1 *pf[10][10];
  Float_t Total[70], Square[10][70], X[70];

  for(int a = 0 ; a < 60 ; a++){
    X[a] = -0.09 +  a*0.02;
  }

  TFile *normal = new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_normal.root");
  TFile *JESup =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_JESup.root");
  TFile *JESdown =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_JESdown.root");
  TFile *Purup =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_purityup.root");
  TFile *Purdown =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_puritydown.root");
  TFile *Stats1up =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_stats1up.root");
  TFile *Stats1down =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_stats1down.root");
  TFile *Stats2up =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_stats2up.root");
  TFile *Stats2down =new TFile("plot_BG_MC/CSVerror_temp_ttjet/hist_ttjets_1_stats2down.root");



  for(int ip = 1 ; ip <= 8 ; ip++){
    for(int jb=1; jb <= 60 ; jb++) Total[jb]=0;

    for(int ib=1; ib <= 60 ; ib++){
      for(int sys = 1 ; sys <= 8 ; sys++){
        Total[ib] += (pf[sys][ip]->GetBinContent(ib))*(pf[sys][ip]->GetBinContent(ib));
      }//sys loop
      Square[ip][ib]=sqrt(Total[ib])-pf[0][ip]->GetBinContent(ib);
    }//bin loop
  }//plot loop

 */
  /*
  for(int ib=1; ib <= bkgHist->GetNbinsX()+1; ib++){
    //eeerror
    tgx[ib-1]=bkgHist->GetXaxis()->GetBinCenter(ib);
    tgy[ib-1]=bkgHist->GetBinContent(ib);
    tgex[ib-1]=bkgHist->GetBinWidth(ib)/2;
    //tgey[ib-1]=bkgHist->GetBinContent(ib)*0.;
    //tgey[ib-1]=sqrt(bkgHist->GetBinContent(ib));
    tgey[ib-1]=sqrt(bkgHist->GetBinContent(ib)) + (bkgHist->GetBinContent(ib))*0.075;//ttbar cross section
    //tgey[ib-1]=sqrt(bkgHist->GetBinContent(ib)) + (bkgHist->GetBinContent(ib))*0.23716;//signal
    //tgey[ib-1]=sqrt(bkgHist->GetBinContent(ib)) + (bkgHist->GetBinContent(ib))*0.34;//Normal signal
  }

  TGraphErrors *gr = new TGraphErrors(bkgHist->GetNbinsX(),
				      tgx, tgy, tgex, tgey);
  gr->UseCurrentStyle();
  //gr->SetLineColor(kBlack);
  gr->SetLineColor(0);
  gr->SetFillColor(kBlack);
  //gr->SetFillStyle(3744);
  gr->SetFillStyle(3013);
  gr->Draw("e2same");
  */
  /*
  plots[nfiles] = (TH1*)hists[nfiles]->Clone(histname.c_str());
  plots[nfiles+1] = (TH1*)hists[nfiles+1]->Clone(histname.c_str());

  //plots[nfiles]->Sumw2();
  plots[nfiles+1]->Add(plots[nfiles]);

//   plots[nfiles+1]->SetBinContent(plots[nfiles+1]->GetNbinsX(),
// 				 plots[nfiles+1]->GetBinContent(plots[nfiles+1]->GetNbinsX())+
// 				 plots[nfiles+1]->GetBinContent(plots[nfiles+1]->GetNbinsX()+1));

  plots[nfiles+1]->SetLineColor(kBlack);
  plots[nfiles+1]->SetMarkerStyle(20);
  plots[nfiles+1]->SetMarkerSize(0.9);
  plots[nfiles+1]->Rebin(2);
  
  deno2=(TH1F*)plots[nfiles+1]->Clone("divider2");//addpa
  
  plots[nfiles+1]->Sumw2();
  
  //plots[nfiles]->Draw("same");
  cout<<"Data "<<plots[nfiles+1]->Integral()<< endl;//don't plot data
  plots[nfiles+1]->Draw("same");//don't plot data
  //plots[nfiles+1]->Draw();

  //allHist->SetFillColor(50);
  
  //sigHist->SetFillColor(38);

  //allHist->Draw("same");
  
  leg->AddEntry(plots[nfiles+1], "Data", "Ep");
  leg->AddEntry(sigHist, Labels[0].c_str(), "l");
  */
  leg->AddEntry(sigHist, Labels[0].c_str(), "l");
  for(int i = 1; i < nfiles; i++){
    if(i == 0 || i == 1 || i == 2 || i==3 || i==7 || i==15 || i==17)
      leg->AddEntry(plots[i], Labels[i].c_str(), "f");
  }
  //leg->AddEntry(sigHist, Labels[0].c_str(), "l");
  //leg->AddEntry(plots[nfiles+1], "Data", "Ep");
  //leg->AddEntry(gr, "BG uncertainty", "f");

     if(plots[0]->GetXaxis()->GetXmax() < 10 && 
        plots[0]->GetXaxis()->GetXmax() > 2 ){
         leg->SetX1(0.35);
         leg->SetX2(0.60);
         leg->SetY1(0.22);
         leg->SetY2(0.80);
       }

  leg->Draw();
  //cout << "legend done\n";
  /*
  // Hack for ROOT 5.32's bug on TLegend
  double xmin = allHist->GetXaxis()->GetXmin();
  double xmax = allHist->GetXaxis()->GetXmax();
  double ymin = allHist->GetMinimum();
  double ymax = allHist->GetMaximum()*1.25;
  
  if(allHist->GetXaxis()->GetXmax()==150){
    xmin+=9.7;
    xmax+=9.7;
  }
  TLine *ltl = new TLine((xmax-xmin)*leg->GetX1()+xmin+2.1,
                         ymax*1.02,//(ymax-ymin)*leg->GetY1(), //+ymin+20.,
                         (xmax-xmin)*leg->GetX1()+xmin+2.1,
                         ymax*0.95);//(ymax-ymin)*leg->GetY2()+ymin+20.);
  //cout << "Legend box: " << xmin << " " << xmax << endl;
  //cout << "Legend box: " << ymin << " " << ymax << endl;
  ltl->SetLineColor(kBlack);//addpa
  ltl->SetLineWidth(1);//addpa
  ltl->SetLineStyle(1);//addpa
  ltl->Draw();
  // Draw vertical error bar manually
  cout << "line done\n";
*/
//  text1 = new TLatex(3.570061,23.08044,"CMS Preliminary");
//  text1->SetNDC();
//  text1->SetTextAlign(13);
//  text1->SetX(0.184);
//  text1->SetY(0.928);
//  text1->SetTextFont(42);
//  text1->SetTextSizePixels(24);
//  text1->Draw();
//
//  text2 = new TLatex(3.570061,23.08044,"#sqrt{s} = 8 TeV; #int L dt=19.8 fb^{-1}");
//  text2->SetNDC();
//  text2->SetTextAlign(13);
//  text2->SetX(0.184);
//  text2->SetY(0.83);
//  text2->SetTextFont(42);
//  text2->SetTextSizePixels(24);
//  text2->Draw();
/*
  //text1 = new TLatex(5.570061,23.08044,"CMS Preliminary");
  text1 = new TLatex(5.570061,23.08044,"#scale[1.1]{CMS}");
  text1->SetNDC();
  text1->SetTextAlign(13);
  //text1->SetX(0.084);
  //text1->SetX(0.184);
  text1->SetX(0.214);
  //text1->SetY(0.928);
  //text1->SetY(0.99);
  text1->SetY(0.89);
  text1->SetTextFont(62);
  //text1->SetTextSize(0.07);
  text1->SetTextSizePixels(124);
  text1->Draw();
*/
  /*
  text4 = new TLatex(5.570061,23.08044,"");
  //text4 = new TLatex(5.570061,23.08044,"#geq 4 jets; #geq 3 b-jets");
  //text4 = new TLatex(5.570061,23.08044,"#geq 4 jets; = 2 b-jets");
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.214);
  text4->SetY(0.89);
  text4->SetTextFont(42);
  //text4->SetTextSize(0.07);
  text4->SetTextSizePixels(124);
  text4->Draw();
  */
  /*
  //text2 = new TLatex(5.570061,23.08044,"#sqrt{s} = 8 TeV;#intL dt=19.8 fb^{-1}");
  //text2 = new TLatex(5.570061,23.08044,"#sqrt{s} = 8 TeV;     #scale[0.9]{L} =19.8 fb^{-1}");
  text2 = new TLatex(5.570061,23.08044,"19.7 fb^{-1} (8 TeV)");
  text2->SetNDC();
  text2->SetTextAlign(13);
  //text2->SetX(0.484);
  text2->SetX(0.634);
  //text2->SetY(0.83);
  text2->SetY(1.0);
  text2->SetTextFont(42);
  //text2->SetTextSize(0.07);
  text2->SetTextSizePixels(124);
  text2->Draw();
  */
//   text3 = new TLatex(5.570061,23.08044,"                     #scale[0.45]{#int}");
//   text3->SetNDC();
//   text3->SetTextAlign(13);
//   //text3->SetX(0.484);
//   text3->SetX(0.384);
//   text3->SetY(0.980);
//   text3->SetTextFont(42);
//   text3->SetTextSize(0.07);
//   text3->SetTextSizePixels(124);
//   text3->Draw();

  //plots[nfiles+1]->Draw("same");

//   bkgHist->SetFillColor(38);
//   bkgHist->Draw("same");
//
//Lower pad
/*
  TLine *tl = new TLine(plots[nfiles+1]->GetXaxis()->GetXmin(),1,plots[nfiles+1]->GetXaxis()->GetXmax(),1);//addpa
  tl->SetLineColor(kRed);//addpa
  tl->SetLineWidth(2);//addpa
  tl->SetLineStyle(2);//addpa
  
  deno->Sumw2();//addpa
*/
  c1->cd();//addpa
  
//   pad2->SetLeftMargin(0.11);
//   pad2->SetRightMargin(0.05);
//   pad2->SetTopMargin(0.05);
//   pad2->SetBottomMargin(0.39);
//   //pad2->Draw();//addpa
//   pad2->cd();//addpa
/*
  char ks_char[128];
  double ks = deno2->KolmogorovTest(deno);
//  double ks = deno2->Chi2Test(deno);
  sprintf(ks_char,"#scale[0.7]{Kolmogorov-Smirnov}: %1.3g ",ks);
*/
  /*
  text3 = new TLatex(0.3,0.7,ks_char);
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.184);
  text3->SetY(0.928);
  text3->SetTextFont(42);
  text3->SetTextSizePixels(24);
  text3->SetTextSize(0.2);
  */
//   deno2->Divide(deno);//addpa
//   deno2->SetXTitle(xlabel.c_str());
//   deno2->GetXaxis()->SetTitleSize(0.18);
//   deno2->SetMaximum(2.0);//addpa
//   deno2->SetMinimum(0);//addpa
//   deno2->SetTitleOffset(0.3,"Y");//addpa
//   deno2->SetTitleSize(0.18,"Y");//addpa
//   deno2->SetYTitle(labeld);//ydlabel.c_str());
//   deno2->GetYaxis()->SetNdivisions(2,0);//addpa
//   deno2->SetLabelSize(0.15,"Y");//addpa
//   deno2->SetLabelOffset(0.02,"Y");//addpa
//   deno2->SetLabelSize(0.17,"X");//addpa
//   deno2->SetLabelOffset(0.03,"X");//addpa
//   deno2->DrawClone();//addpa
  
  //make kstest
  // text3->Draw("same");

//  for(int ibe=1; ibe <= deno2->GetNbinsX()+1; ibe++){
//    tgxe[ibe-1]=deno2->GetXaxis()->GetBinCenter(ibe);
//    tgye[ibe-1]=deno2->GetBinContent(ibe);
//    tgexe[ibe-1]=deno2->GetBinWidth(ibe)/2;
//    tgeye[ibe-1]=sqrt(deno2->GetBinContent(ibe)) + (deno2->GetBinContent(ibe))*0.236;
//  }
//
//  TGraphErrors *gre = new TGraphErrors(deno2->GetNbinsX(),
//				      tgxe, tgye, tgexe, tgeye);
//  gre->UseCurrentStyle();
//  gre->SetFillColor(kBlack);
//  gre->SetFillStyle(3744);
//  gre->Draw("e2same");
  
//   tl->Draw("same");//addpa
//   c1->cd();//addpa


    

//   if(x1!=-1000 && x2!=1000 && y!=500){
//    myline= new TLine(x1,0,x1,y);
//    myline2= new TLine(x2,0,x2,y);
//    myline->SetLineStyle(2);
//    myline2->SetLineStyle(2);
//    myline->SetLineWidth(3);
//    myline2->SetLineWidth(3);
//    myline->SetLineColor(kBlue-4);
//    myline2->SetLineColor(kBlue-4);
//    myline->Draw("same");
//    myline2->Draw("same");
//     } 
}

//void setTDRStyle();

void mkplots_perf(){
  //Reset ROOT
  gROOT->Reset();
  gStyle->SetOptFit();

  gROOT->LoadMacro("setTDRStyle.C");
  //gROOT->ProcessLine(".x setTDRStyle.C");
  //setTDRStyle();

 //gStyle->SetOptStat(1);
 // gStyle->SetPadLeftMargin(0.16);
 // gStyle->SetPadRightMargin(0.02);
 //gStyle->SetPadBottomMargin(1.1);
 gStyle->SetTitleXOffset(0.9);
 gStyle->SetTitleYOffset(1.25);

 gStyle->SetHatchesSpacing(1.0);
 gStyle->SetOptTitle(0);

 double m_over=0., m_max=0.;

 TH1* hist;

 //TFile *f_hist_mc = TFile::Open("hist_top_cz1.root");
 cout << "reading histograms...\n";

 for(int if1=0; if1 < 5; if1++){ //nFiles; if1++){
   //if(if1==7 || if1==8 || if1==9) continue;

   cout << "loading... \n";
   inFile[if1] = TFile::Open(histFiles[if1].c_str());
   cout << histFiles[if1].c_str() << endl;
   gDirectory->cd("");

   /*   // Vertex plots
   hist = (TH1*) gDirectory->Get("hist_vtx_no_AS");
   VtxNo.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_vtx_ndof_AS");
   VtxNDoF.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_met_pt_AS");
   METee.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_met_pt_3b");
   METee3b.push_back(hist);

   // Leptons
   hist = (TH1*) gDirectory->Get("hist_e_pt_AS");
   ElecPt.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_e_eta_AS");
   ElecEta.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_e_phi_AS");
   ElecPhi.push_back(hist);

//   hist = (TH1*) gDirectory->Get("hist_e_mva");
//   ElecMVA.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_m_pt_AS");
   MuonPt.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_m_eta_AS");
   MuonEta.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_m_phi_AS");
   MuonPhi.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_no after selection");
   JetNo.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_bjet_no after selection");
   BJetNo.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_pt_AS");
   JetPt.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_eta_AS");
   JetEta.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_phi_AS");
   JetPhi.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_higgs_m_had");
   HiggsMass.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_higgs_m_had_Back");
   HiggsMassBack.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_higgs_pt_had");
   HiggspT.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_higgs_pt_had_Back");
   HiggspTBack.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_top_m_had"); 
   TopMassHad.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_top_m_lep");
   TopMassLep.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_top_pt_had"); 
   ToppTHad.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_top_pt_lep"); 
   ToppTLep.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_higgs_m_had_afc");
   HiggsMassAFC.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_higgs_m_had_afc_e");
   HiggsMassAFCE.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_higgs_m_had_afc_m");
   HiggsMassAFCM.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_higgs_pt_had_afc");
   HiggspTAFC.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_top_m_had_afc"); 
   TopMassHadAFC.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_top_m_lep_afc");
   TopMassLepAFC.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_top_pt_had_afc"); 
   ToppTHadAFC.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_top_pt_lep_afc"); 
   ToppTLepAFC.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_top_pt_afc"); 
   ToppTAFC.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_ERc");
   CjetEnergy.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_AS");
   CSVvalue.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_AS_corr");
   CSVvalueCorr.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_4Jets_1");
   CSVleading.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_4Jets_2");
   CSV2nd.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_4Jets_3");
   CSV3rd.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_4Jets_4");
   CSV4th.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_1");
   CSVJet1.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_2");
   CSVJet2.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_3");
   CSVJet3.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_1_afc");
   CSVJet1afc.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_2_afc");
   CSVJet2afc.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_value_3_afc");
   CSVJet3afc.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_2");
   CSVJetTotal.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_2_corr");
   CSVJetTotalafc.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_4");
   CSVJetTotal4.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_4_corr");
   CSVJetTotal4afc.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_6");
   CSVJetTotal6.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_jet_btag_6_corr");
   CSVJetTotal6afc.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_jet_btag_s");
   CSVJetTotalS.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_corr");
   CSVJetTotalSafc.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_bjet");
   CSVJetTotalSBJet.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_corr_bjet");
   CSVJetTotalSafcBJet.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_2");
   CSVJetTotalS2.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_2_corr");
   CSVJetTotalS2afc.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_ann");
   ANNValue.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_MLPBNN");
   MLPBNNValue.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_MLPBFGS");
   MLPBFGSValue.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_MLP");
   MLPValue.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_top_pt"); 
   ToppT.push_back(hist); 

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_pur_up");
   CSVJetPurup.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_pur_down");
   CSVJetPurdown.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_sta1_up");
   CSVJetSta1up.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_sta1_down");
   CSVJetSta1down.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_sta2_up");
   CSVJetSta2up.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_sta2_down");
   CSVJetSta2down.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_total_up");
   CSVJetTotalup.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_s_total_down");
   CSVJetTotaldown.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_nob");
   CSVNobtagged.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_jet_btag_nob_corr");
   CSVNobtaggedCorr.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_wen_mt");
   EUM.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_wmn_mt");
   MUM.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_wen_mt_2b");
   EUM2.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_wmn_mt_2b");
   MUM2.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_wen_mt_3b");
   EUM3.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_wmn_mt_3b");
   MUM3.push_back(hist);
   
   hist1 = (TH1*) gDirectory->Get("hist_wen_mt_3b");
   hist2 = (TH1*) gDirectory->Get("hist_wmn_mt_3b");
   hist = (TH1*) hist1->Clone();
   hist->Add(hist2);
   LUM3.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_bdt_TB");
   BDTValue.push_back(hist);

//BDT input varaibles
   hist = (TH1*) gDirectory->Get("hist_higgs_m_had_gen");
   BDTint0.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_top_m_had_gen");
   BDTint1.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_top_m_lep_gen");
   BDTint2.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_ERc_gen");
   BDTint3.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_top_dphi_gen");
   BDTint4.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_top_LepbJet_dphi_gen");
   BDTint5.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_top_HCJet_dphi_gen");
   BDTint6.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_higgs_BJetspair_dphi_gen");
   BDTint7.push_back(hist);
   */
   hist = (TH1*) gDirectory->Get("hist_fit_m_bw");
   Final_Mtop_bw.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_m_cz");
   Final_Mtop_cz.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_m_zee");
   Final_MZ_ee.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_m_zmm");
   Final_MZ_mm.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_mt_wen");
   Final_MtW_en.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_mt_wmn");
   Final_MtW_mn.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_ht");
   Final_HT.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_st");
   Final_ST.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_ctag_lc1");
   Final_cTag_lc1.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_ctag_lc2");
   Final_cTag_lc2.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_ctag_bc1");
   Final_cTag_bc1.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_ctag_bc2");
   Final_cTag_bc2.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_nbjet");
   Final_nbJet.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_fit_ncbjet");
   Final_ncbJet.push_back(hist);

 }

  TCanvas *c1 = new TCanvas("c1","T2ZQ",10,10,600,600);
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_Mtop_bw, "Invariant Mass of top(bW)", nFiles, "Top(bW) Mass");
  c1->SaveAs("mkplot_perf/hist_fit_m_bw.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_bw.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_Mtop_cz, "Invariant Mass of top(cZ)", nFiles, "Top(cZ) Mass");
  c1->SaveAs("mkplot_perf/hist_fit_m_cz.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_MZ_ee, "Invariant Mass of Z(ee)", nFiles, "Z(ee) Mass");
  c1->SaveAs("mkplot_perf/hist_fit_m_zee.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_MZ_mm, "Invariant Mass of Z(#mu#mu)", nFiles, "Z(#mu#mu) Mass");
  c1->SaveAs("mkplot_perf/hist_fit_m_zmm.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_MtW_en, "Invariant TMass of W(e#nu)", nFiles, "W(e#nu) TMass");
  c1->SaveAs("mkplot_perf/hist_fit_mt_wen.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_MtW_mn, "Invariant TMass of W(#mu#nu)", nFiles, "W(#mu#nu) TMass");
  c1->SaveAs("mkplot_perf/hist_fit_mt_wmn.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_HT, "Transverse Momentum Sum HT", nFiles, "HT");
  c1->SaveAs("mkplot_perf/hist_fit_ht.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_ST, "Transverse Momentum Sum ST", nFiles, "ST");
  c1->SaveAs("mkplot_perf/hist_fit_st.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_cTag_lc1, "C vs. Light for Jet 1", nFiles, "MVA Output");
  c1->SaveAs("mkplot_perf/hist_fit_ctag_lc1.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_cTag_lc2, "C vs. Light for Jet 2", nFiles, "MVA Output");
  c1->SaveAs("mkplot_perf/hist_fit_ctag_lc2.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_cTag_bc1, "C vs. B for Jet 1", nFiles, "MVA Output");
  c1->SaveAs("mkplot_perf/hist_fit_ctag_bc1.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_cTag_bc2, "C vs. B for Jet 2", nFiles, "MVA Output");
  c1->SaveAs("mkplot_perf/hist_fit_ctag_bc2.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_nbJet, "No. of b-tagged Jets", nFiles, "b-Jets #");
  c1->SaveAs("mkplot_perf/hist_fit_nbjet.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);


  plot_hist(c1, Final_ncbJet, "No. of clean b-tagged Jets", nFiles, "cb-Jets #");
  c1->SaveAs("mkplot_perf/hist_fit_ncbjet.png");
  //c1->SaveAs("mkplot_perf/hist_fit_m_cz.pdf");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

// plot_hist(c1, VtxNo, "No. of Vertex", nFiles, "Number of Vertex");
// c1->SaveAs("mkplot_perf/hist_vtx_no_AS.png");
// c1->SaveAs("mkplot_perf/hist_vtx_no_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, VtxNDoF, "Vertex no. of DoF", nFiles, "Number of DoF");
// c1->SaveAs("mkplot_perf/hist_vtx_ndof_AS.png");
// c1->SaveAs("mkplot_perf/hist_vtx_ndof_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, METee, "Miss ET of W", nFiles, "Miss ET [GeV]");
// c1->SaveAs("mkplot_perf/hist_met_pt_AS.png");
// c1->SaveAs("mkplot_perf/hist_met_pt_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);

//// plot_hist(c1, EUM, "the reconstructed e+nu transverse mass of the W boson candidate", nFiles, "transverse mass [GeV]");
//// c1->SaveAs("mkplot_perf/hist_wen_mt.eps");
//// c1->SaveAs("mkplot_perf/hist_wen_mt.png");
//// c1->SaveAs("mkplot_perf/hist_wen_mt.pdf");
////
//// plot_hist(c1, MUM, "the reconstructed muon+nu transverse mass of the W boson candidate", nFiles, "transverse mass [GeV]");
//// c1->SaveAs("mkplot_perf/hist_wmn_mt.eps");
//// c1->SaveAs("mkplot_perf/hist_wmn_mt.png");
//// c1->SaveAs("mkplot_perf/hist_wmn_mt.pdf");
////
//// plot_hist(c1, EUM2, "the reconstructed e+nu transverse mass of the W boson candidate", nFiles, "transverse mass [GeV]");
//// c1->SaveAs("mkplot_perf/hist_wen_mt_2b.eps");
//// c1->SaveAs("mkplot_perf/hist_wen_mt_2b.png");
//// c1->SaveAs("mkplot_perf/hist_wen_mt_2b.pdf");
////
//// plot_hist(c1, MUM2, "the reconstructed muon+nu transverse mass of the W boson candidate", nFiles, "transverse mass [GeV]");
//// c1->SaveAs("mkplot_perf/hist_wmn_mt_2b.eps");
//// c1->SaveAs("mkplot_perf/hist_wmn_mt_2b.png");
//// c1->SaveAs("mkplot_perf/hist_wmn_mt_2b.pdf");
//
/*
  TCanvas *c1 = new TCanvas("c1","T2ZQ",10,10,600,600);
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

 plot_hist(c1, METee3b, "Miss ET of W in signal region", nFiles, "E_{T}^{miss} [GeV]");
 c1->SaveAs("mkplot_perf.final33/hist_met_pt_3b.png");
 c1->SaveAs("mkplot_perf.final33/hist_met_pt_3b.pdf");
 c1->SaveAs("mkplot_perf.final33/hist_met_pt_3b.C");
  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, MUM3, "the reconstructed muon+nu transverse mass of the W boson candidate in signal region", nFiles, "M_{T} W(#mu#nu) [GeV]");
  c1->SaveAs("mkplot_perf.final33/hist_wmn_mt_3b.png");
  c1->SaveAs("mkplot_perf.final33/hist_wmn_mt_3b.pdf");
   TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
   c1->cd();
   c1->cd()->SetRightMargin(0.08);
 //
  plot_hist(c1, EUM3, "the reconstructed e+nu transverse mass of the W boson candidate in signal region", nFiles, "M_{T} W(e#nu) [GeV]");
  c1->SaveAs("mkplot_perf.final33/hist_wen_mt_3b.png");
  c1->SaveAs("mkplot_perf.final33/hist_wen_mt_3b.pdf");
   TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
   c1->cd();
   c1->cd()->SetRightMargin(0.08);
 //
 plot_hist(c1, LUM3, "the reconstructed muon+nu transverse mass of the W boson candidate in signal region", nFiles, "M_{T} [GeV]");
 c1->SaveAs("mkplot_perf.final33/hist_wln_mt_3b.png");
 c1->SaveAs("mkplot_perf.final33/hist_wln_mt_3b.pdf");
  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
  c1->cd();
  c1->cd()->SetRightMargin(0.08);
*/
//
//
// plot_hist(c1, ElecPt, "Electron Pt distribution", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_e_pt_AS.png");
// c1->SaveAs("mkplot_perf/hist_e_pt_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, ElecEta, "Electron Eta distribution", nFiles, "Pseudo Rapidity #eta");
// c1->SaveAs("mkplot_perf/hist_e_eta_AS.png");
// c1->SaveAs("mkplot_perf/hist_e_eta_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, ElecPhi, "Electron Phi distribution", nFiles, "Azimuthal Angle #phi");
// c1->SaveAs("mkplot_perf/hist_e_phi_AS.png");
// c1->SaveAs("mkplot_perf/hist_e_phi_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
//// plot_hist(c1, ElecMVA, "Electron MVA distribution", nFiles, "Azimuthal #mva");
//// c1->SaveAs("mkplot_perf/hist_e_mva.png");
//
// plot_hist(c1, MuonPt, "Muon Pt distribution", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_m_pt_AS.png");
// c1->SaveAs("mkplot_perf/hist_m_pt_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, MuonEta, "Muon Eta distribution", nFiles, "Pseudo Rapidity #eta");
// c1->SaveAs("mkplot_perf/hist_m_eta_AS.png");
// c1->SaveAs("mkplot_perf/hist_m_eta_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, MuonPhi, "Muon Phi distribution", nFiles, "Azimuthal Angle #phi");
// c1->SaveAs("mkplot_perf/hist_m_phi_AS.png");
// c1->SaveAs("mkplot_perf/hist_m_phi_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, JetNo, "Jet No. distribution", nFiles, "Number of Jets");
// c1->SaveAs("mkplot_perf/hist_jet_no.png");
// c1->SaveAs("mkplot_perf/hist_jet_no.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);

// plot_hist(c1, BJetNo, "B-tagged Jet No. distribution", nFiles, "Number of BJets");
// c1->SaveAs("mkplot_perf/hist_bjet_no.png");
// c1->SaveAs("mkplot_perf/hist_bjet_no.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, JetPt, "Jet Pt distribution", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_jet_pt_AS.png");
// c1->SaveAs("mkplot_perf/hist_jet_pt_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, JetEta, "Jet Eta distribution", nFiles, "Pseudo Rapidity #eta");
// c1->SaveAs("mkplot_perf/hist_jet_eta_AS.png");
// c1->SaveAs("mkplot_perf/hist_jet_eta_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, JetPhi, "Jet Phi distribution", nFiles, "Azimuthal Angle #phi");
// c1->SaveAs("mkplot_perf/hist_jet_phi_AS.png");
// c1->SaveAs("mkplot_perf/hist_jet_phi_AS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, CSVJetTotal, "CSV value all Jet in only 4 jets", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_2.png");
// c1->SaveAs("mkplot_perf/hist_jet_btag_2.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, CSVJetTotalafc, "CSV value all Jet in only 4 jets after correction", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_2_corr.png");
// c1->SaveAs("mkplot_perf/hist_jet_btag_2_corr.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, CSVJetTotalS, "CSV value all Jet in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s.png");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, CSVJetTotalSafc, "CSV value all Jet in signal region after correction", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_corr.png");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_corr.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, CSVJetTotalSBJet, "CSV value all BJet in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_bjet.png");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_bjet.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);

// plot_hist(c1, CSVJetTotalSafcBJet, "CSV value all BJet in signal region after correction", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_corr_bjet.png");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_corr_bjet.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);

//// plot_hist(c1, CSVJetTotal4, "CSV value all Jet in control region", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_4.png");
//// plot_hist(c1, CSVJetTotal4afc, "CSV value all Jet in control region after correction", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_4_corr.png");
////
//// plot_hist(c1, CSVJetTotal6, "CSV value all Jet in 6 jets region", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_6.png");
//// plot_hist(c1, CSVJetTotal6afc, "CSV value all Jet in 6 jets region after correction", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_6_corr.png");
////
//// plot_hist(c1, CSVJetTotalS2, "CSV value all Jet in signal only 3b region", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_s_2.png");
//// plot_hist(c1, CSVJetTotalS2afc, "CSV value all Jet in signal only 3b region after correction", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_s_2_corr.png");
// 
//// plot_hist(c1, CSVleading, "CSV value leading", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_4Jets_1.png");
//// plot_hist(c1, CSV2nd, "CSV value 2nd", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_4Jets_2.png");
//// plot_hist(c1, CSV3rd, "CSV value 3rd", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_4Jets_3.png");
//// plot_hist(c1, CSV4th, "CSV value 4th", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_4Jets_4.png");
//// plot_hist(c1, CSVJet1, "CSV value Jet1", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_1.png");
//// plot_hist(c1, CSVJet2, "CSV value Jet2", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_2.png");
//// plot_hist(c1, CSVJet3, "CSV value Jet3", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_value_3.png");
////
 // plot_hist(c1, CSVJet1afc, "CSV value Jet1 after correction", nFiles, "B-tagging value");
 // c1->SaveAs("mkplot_perf/hist_jet_btag_value_1_afc.png");
 // c1->SaveAs("mkplot_perf/hist_jet_btag_value_1_afc.pdf");
 //  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
 //  c1->cd();
 //  c1->cd()->SetRightMargin(0.08);
 // plot_hist(c1, CSVJet2afc, "CSV value Jet2 after correction", nFiles, "B-tagging value");
 // c1->SaveAs("mkplot_perf/hist_jet_btag_value_2_afc.png");
 // c1->SaveAs("mkplot_perf/hist_jet_btag_value_2_afc.pdf");
 //  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
 //  c1->cd();
 //  c1->cd()->SetRightMargin(0.08);
 // plot_hist(c1, CSVJet3afc, "CSV value Jet3 after correction", nFiles, "B-tagging value");
 // c1->SaveAs("mkplot_perf/hist_jet_btag_value_3_afc.png");
 // c1->SaveAs("mkplot_perf/hist_jet_btag_value_3_afc.pdf");
 //  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
 //  c1->cd();
 //  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, HiggsMassAFCE, "Higgs_Mass_all after correction electron channel", nFiles, "Invariant mass [GeV]");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had_afc_e.png");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had_afc_e.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, HiggsMassAFCM, "Higgs_Mass_all after correction muon channel", nFiles, "Invariant mass [GeV]");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had_afc_m.png");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had_afc_m.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
//  plot_hist(c1, HiggsMassAFC, "Higgs_Mass_all after correction", nFiles, "Invariant mass [GeV]");
//  c1->SaveAs("mkplot_perf/hist_higgs_m_had_afc_3b.png");
//  c1->SaveAs("mkplot_perf/hist_higgs_m_had_afc_3b.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, HiggsMass, "Higgs_Mass_all", nFiles, "Invariant mass [GeV]");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had.png");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, HiggsMassBack, "Higgs_Mass_all Back", nFiles, "Invariant mass [GeV]");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had_Back.png");
// c1->SaveAs("mkplot_perf/hist_higgs_m_had_Back.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, HiggspT, "Higgs_pT_all", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_higgs_pt_had.png");
// c1->SaveAs("mkplot_perf/hist_higgs_pt_had.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, HiggspTBack, "Higgs_pT_all Back", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_higgs_pt_had_Back.png");
// c1->SaveAs("mkplot_perf/hist_higgs_pt_had_Back.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, TopMassHad, "Top_Mass_Had", nFiles, "Invariant mass [GeV]"); 
// c1->SaveAs("mkplot_perf/hist_top_m_had.png"); 
// c1->SaveAs("mkplot_perf/hist_top_m_had.pdf"); 
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, TopMassLep, "Top_Mass_Lep", nFiles, "Invariant mass [GeV]");
// c1->SaveAs("mkplot_perf/hist_top_m_lep.png");
// c1->SaveAs("mkplot_perf/hist_top_m_lep.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, ToppTHad, "Top_pT_Had", nFiles, "p_{T} [GeV/c]"); 
// c1->SaveAs("mkplot_perf/hist_top_pt_had.png"); 
// c1->SaveAs("mkplot_perf/hist_top_pt_had.pdf"); 
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, ToppTLep, "Top_pT_Lep", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_top_pt_lep.png");
// c1->SaveAs("mkplot_perf/hist_top_pt_lep.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
//
//// plot_hist(c1, HiggspTAFC, "Higgs_pT_all after correction", nFiles, "p_{T} [GeV/c]");
//// c1->SaveAs("mkplot_perf/hist_higgs_pt_had_afc.png");
////
//// plot_hist(c1, TopMassHadAFC, "Top_Mass_Had after correction", nFiles, "Invariant mass [GeV]"); 
//// c1->SaveAs("mkplot_perf/hist_top_m_had_afc.png"); 
////
//// plot_hist(c1, TopMassLepAFC, "Top_Mass_Lep after correction", nFiles, "Invariant mass [GeV]");
//// c1->SaveAs("mkplot_perf/hist_top_m_lep_afc.png");
////
//// plot_hist(c1, ToppTHadAFC, "Top_pT_Had after correction", nFiles, "p_{T} [GeV/c]"); 
//// c1->SaveAs("mkplot_perf/hist_top_pt_had_afc.png"); 
////
//// plot_hist(c1, ToppTLepAFC, "Top_pT_Lep after correction", nFiles, "p_{T} [GeV/c]");
//// c1->SaveAs("mkplot_perf/hist_top_pt_lep_afc.png");
//
// plot_hist(c1, ToppT, "Top pT", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_top_pt.png");
// c1->SaveAs("mkplot_perf/hist_top_pt.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, ToppTAFC, "Top pT after correction", nFiles, "p_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_top_pt_afc.png");
// c1->SaveAs("mkplot_perf/hist_top_pt_afc.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, CjetEnergy, "Cjet energy", nFiles, "E_{T} [GeV/c]");
// c1->SaveAs("mkplot_perf/hist_ERc.png");
// c1->SaveAs("mkplot_perf/hist_ERc.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
// 
//// plot_hist(c1, CSVvalue, "All jets CSV value", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_AS.png");
//// plot_hist(c1, CSVvalueCorr, "All jets CSV value after correction", nFiles, "B-tagging value");
//// c1->SaveAs("mkplot_perf/hist_jet_btag_AS_corr.png");
//
//
// plot_hist(c1, ANNValue, "ANN output", nFiles, "ANN output value");
// c1->SaveAs("mkplot_perf/hist_ann.png");
// c1->SaveAs("mkplot_perf/hist_ann.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, MLPValue, "MLP output", nFiles, "MLP output value");
// c1->SaveAs("mkplot_perf/hist_MLP.png");
// c1->SaveAs("mkplot_perf/hist_MLP.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, MLPBNNValue, "MLPBNN output", nFiles, "MLPBNN output value");
// c1->SaveAs("mkplot_perf/hist_MLPBNN.png");
// c1->SaveAs("mkplot_perf/hist_MLPBNN.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, MLPBFGSValue, "MLPBFGS output", nFiles, "MLPBFGS output value");
// c1->SaveAs("mkplot_perf/hist_MLPBFGS.png");
// c1->SaveAs("mkplot_perf/hist_MLPBFGS.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTValue, "BDT output", nFiles, "BDT output value");
// c1->SaveAs("mkplot_perf/hist_bdt_TB.png");
// c1->SaveAs("mkplot_perf/hist_bdt_TB.pdf");
//
//
// plot_hist(c1, BDTint0, "Higgs mass for BDT", nFiles, "Higgs mass for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint0.png");
// c1->SaveAs("mkplot_perf/hist_BDTint0.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
//
// plot_hist(c1, BDTint1, "Top_had mass for BDT", nFiles, "Top_had mass for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint1.png");
// c1->SaveAs("mkplot_perf/hist_BDTint1.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTint2, "Top_lep mass for BDT", nFiles, "Top_lep mass for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint2.png");
// c1->SaveAs("mkplot_perf/hist_BDTint2.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTint3, "ERc for BDT", nFiles, "ERc for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint3.png");
// c1->SaveAs("mkplot_perf/hist_BDTint3.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTint4, "Dphi of ttbar for BDT", nFiles, "Dphi of ttbar for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint4.png");
// c1->SaveAs("mkplot_perf/hist_BDTint4.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTint5, "Dphi of lepton_bjet for BDT", nFiles, "Dphi of lepton_bjet for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint5.png");
// c1->SaveAs("mkplot_perf/hist_BDTint5.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTint6, "Dphi of Higgs_cjet for BDT", nFiles, "Dphi of Higgs_cjet for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint6.png");
// c1->SaveAs("mkplot_perf/hist_BDTint6.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);
//
// plot_hist(c1, BDTint7, "Dphi of bbpair for BDT", nFiles, "Dphi of bbpair for BDT");
// c1->SaveAs("mkplot_perf/hist_BDTint7.png");
// c1->SaveAs("mkplot_perf/hist_BDTint7.pdf");
//  TCanvas *c1 = new TCanvas("c1","T2HC",10,10,600,600);
//  c1->cd();
//  c1->cd()->SetRightMargin(0.08);


// //Luca and Jacob
// plot_hist(c1, CSVJetSta1up, "CSV value all Jet sta1 up in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta1_up.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta1_up.png");
//
// plot_hist(c1, CSVJetSta1down, "CSV value all Jet sta1 down in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta1_down.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta1_down.png");
//
// plot_hist(c1, CSVJetSta2up, "CSV value all Jet sta2 up in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta2_up.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta2_up.png");
//
// plot_hist(c1, CSVJetSta2down, "CSV value all Jet sta2 down in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta2_down.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_sta2_down.png");
//
// plot_hist(c1, CSVJetPurup, "CSV value all Jet pur up in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_pur_up.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_pur_up.png");
//
// plot_hist(c1, CSVJetPurdown, "CSV value all Jet pur down in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_pur_down.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_pur_down.png");
//
// plot_hist(c1, CSVJetTotalup, "CSV value all Jet Total up in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_total_up.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_total_up.png");
//
// plot_hist(c1, CSVJetTotaldown, "CSV value all Jet Total down in signal region", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_total_down.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_s_total_down.png");
//
// plot_hist(c1, CSVNobtagged, "CSV value all Jet 4jets No btagged", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_nob.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_nob.png");
// 
// plot_hist(c1, CSVNobtaggedCorr, "CSV value all Jet 4jets No btagged after correction", nFiles, "B-tagging value");
// c1->SaveAs("mkplot_perf/hist_jet_btag_nob_corr.eps");
// c1->SaveAs("mkplot_perf/hist_jet_btag_nob_corr.png");

}
