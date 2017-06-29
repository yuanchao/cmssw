{    
  //Reset ROOT    
  gROOT->Reset();    
    
  //gROOT->LoadMacro("MyTcZAna.C+");    
    
  // Create a chain of files. The parameter to the TChain constructor    
  // is the name of the Tree to be processed in each file of the chain.    
  TChain chain("fcncKit/root");    

  //chain.Add("TTbWcZ_3LPY8.root");   
  //chain.Add("TTbWcZ_3LPY8.root");   
  chain.Add("TTbWcZ_3LPY8_10.root");   
  //chain.Add("TTbWcZ_3LPY8_all.root");   
 
  TFile *hfile = new TFile("sig_TTbWcZ_3LPY8_10.root","RECREATE","Ttbar-fcnc-Signal");    
    
  //MyTcZAna t((TTree *)chain, 1.);    
  //MyG4Ana t;    
//  t.Histogram();    
  //t.Loop();    
  // TTree *tree = new TTree("mvaTree1", "This is a tree");
  // Float_t alpha, beta, gam;

  // //TBranch *branch = tree->Branch("alpha", &alpha, "alpha/F"); 
  // tree->Branch("alpha", &alpha, "alpha/F"); 
  // tree->Branch("beta", &beta, "beta/F"); 
  // tree->Branch("gam", &gam, "gam/F"); 

  // for(int i = 0; i < 1000; i++){
  //   alpha = i;//1+i*1000;
  //   beta = 2+i*1000;
  //   gam = 3+i*1000;

  //   tree->Fill();
  // }

  // tree->Write();

  chain.Process("MyTcZAna.C", "a=b,test;test2");

  hfile->Write();    
  //hfile->Close();    
    
  //t.end();    
}    
