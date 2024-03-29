#define TagAndProbe_cxx
#include "TagAndProbe.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TagAndProbe::Loop(TString output)
{
//   In a ROOT session, you can do:
//      root> .L TagAndProbe.C
//      root> TagAndProbe t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
  bool RunSystematic=true;
   vector<TString> systematicVar =  {"nominal"};
   
   if (RunSystematic)
   {
	systematicVar.push_back("TagPt_up");
	systematicVar.push_back("TagPt_down");
	systematicVar.push_back("Zmass_up");
	systematicVar.push_back("Zmass_down");
   }

for(int i=0; i<systematicVar.size();i++)
{

   double ptTag = 35; 
   double zMassL = 60; 
   double zMassR = 120;

   if(systematicVar.at(i).Contains("TagPt_up")) ptTag = 40;
   if(systematicVar.at(i).Contains("TagPt_down")) ptTag = 30;
   if(systematicVar.at(i).Contains("Zmass_up")) {zMassL = 50; zMassR = 130;}
   if(systematicVar.at(i).Contains("Zmass_down")) {zMassL = 70; zMassR = 110;}
 
   cout<<systematicVar.at(i).Data()<<endl;
   cout<<" ptTag : "<<ptTag<<" , zMassL : "<<zMassL<<" , zMassR : "<<zMassR<<endl;
   output = "";
   output +="efficiency_";
   output += systematicVar.at(i);
   output +=".root";

   TFile *file = new TFile(output.Data(),"RECREATE");
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<< "total events : "<<nentries<<endl;
   double eta_bins[11] = {-2.5,-2.1,-1.6,-1.4,-0.8,0,0.8,1.4,1.6,2.1,2.5};
   double pt_bins_Ele35[18] = {0,10,20,30,32,33,34,35,36,37,38,40,45,50,60,100,200};
   double pt_bins_Ele23_Ele12_leg1[18] = {0,10,20,21,22,23,24,25,26,30,35,40,45,50,60,100,200};
   double pt_bins_Ele23_Ele12_leg2[18] = {0,10,11,12,13,14,15,20,25,30,35,40,45,50,60,100,200};

   // MonoHiggs
   double pt_bins_DoubleEle33[18] = {0,10,20,30,32,33,34,35,36,37,38,40,45,50,60,100,200};
   double pt_bins_DoubleEle27[18] = {0,10,20,24,25,26,27,28,29,30,32,35,40,50,60,100,200};
   double pt_bins_DoubleEle25[18] = {0,10,20,22,23,24,25,26,27,28,30,35,40,50,60,100,200};
   double pt_bins_Ele27_Ele37_leg2[18] = {0,10,20,24,25,26,27,28,29,30,32,35,40,50,60,100,200};
   double pt_bins_Ele27_Ele37_leg1[18] = {0,10,20,30,34,35,36,37,38,39,40,42,45,50,60,100,200};


// HLT Ele35
   TH1F *h_Ele35_pt_total = new TH1F("Ele35_pt_total","Ele35_pt",16,pt_bins_Ele35);
   TH1F *h_Ele35_eta_total = new TH1F("Ele35_eta_total","Ele35_eta",10,eta_bins);
   TH2F *h_Ele35_pt_eta_total = new TH2F("Ele35_pt_eta_total","Ele35_pt_eta",10,eta_bins,16,pt_bins_Ele35);
   TH1F *h_Ele35_pt_pass = new TH1F("Ele35_pt_pass","Ele35_pt",16,pt_bins_Ele35);
   TH1F *h_Ele35_eta_pass = new TH1F("Ele35_eta_pass","Ele35_eta",10,eta_bins);
   TH2F *h_Ele35_pt_eta_pass = new TH2F("Ele35_pt_eta_pass","Ele35_pt_eta",10,eta_bins,16,pt_bins_Ele35);

   h_Ele35_pt_total->Sumw2();
   h_Ele35_eta_total->Sumw2();
   h_Ele35_pt_eta_total->Sumw2();
   h_Ele35_pt_pass->Sumw2();
   h_Ele35_eta_pass->Sumw2();
   h_Ele35_pt_eta_pass->Sumw2();

// HLT Ele23_Ele12 Ele23 leg
   TH1F *h_Ele23_Ele12_leg1_pt_total = new TH1F("Ele23_Ele12_leg1_pt_total","Ele23_Ele12_leg1_pt",16,pt_bins_Ele23_Ele12_leg1);
   TH1F *h_Ele23_Ele12_leg1_eta_total = new TH1F("Ele23_Ele12_leg1_eta_total","Ele23_Ele12_leg1_eta",10,eta_bins);
   TH2F *h_Ele23_Ele12_leg1_pt_eta_total = new TH2F("Ele23_Ele12_leg1_pt_eta_total","Ele23_Ele12_leg1_pt_eta",10,eta_bins,16,pt_bins_Ele23_Ele12_leg1);
   TH1F *h_Ele23_Ele12_leg1_pt_pass = new TH1F("Ele23_Ele12_leg1_pt_pass","Ele23_Ele12_leg1_pt",16,pt_bins_Ele23_Ele12_leg1);
   TH1F *h_Ele23_Ele12_leg1_eta_pass = new TH1F("Ele23_Ele12_leg1_eta_pass","Ele23_Ele12_leg1_eta",10,eta_bins);
   TH2F *h_Ele23_Ele12_leg1_pt_eta_pass = new TH2F("Ele23_Ele12_leg1_pt_eta_pass","Ele23_Ele12_leg1_pt_eta",10,eta_bins,16,pt_bins_Ele23_Ele12_leg1);
      
   h_Ele23_Ele12_leg1_pt_total->Sumw2();
   h_Ele23_Ele12_leg1_eta_total->Sumw2();
   h_Ele23_Ele12_leg1_pt_eta_total->Sumw2();
   h_Ele23_Ele12_leg1_pt_pass->Sumw2();
   h_Ele23_Ele12_leg1_eta_pass->Sumw2();
   h_Ele23_Ele12_leg1_pt_eta_pass->Sumw2();

// HLT Ele23_Ele12 Ele12 leg
   TH1F *h_Ele23_Ele12_leg2_pt_total = new TH1F("Ele23_Ele12_leg2_pt_total","Ele23_Ele12_leg2_pt",16,pt_bins_Ele23_Ele12_leg2);
   TH1F *h_Ele23_Ele12_leg2_eta_total = new TH1F("Ele23_Ele12_leg2_eta_total","Ele23_Ele12_leg2_eta",10,eta_bins);
   TH2F *h_Ele23_Ele12_leg2_pt_eta_total = new TH2F("Ele23_Ele12_leg2_pt_eta_total","Ele23_Ele12_leg2_pt_eta",10,eta_bins,16,pt_bins_Ele23_Ele12_leg2);
   TH1F *h_Ele23_Ele12_leg2_pt_pass = new TH1F("Ele23_Ele12_leg2_pt_pass","Ele23_Ele12_leg2_pt",16,pt_bins_Ele23_Ele12_leg2);
   TH1F *h_Ele23_Ele12_leg2_eta_pass = new TH1F("Ele23_Ele12_leg2_eta_pass","Ele23_Ele12_leg2_eta",10,eta_bins);
   TH2F *h_Ele23_Ele12_leg2_pt_eta_pass = new TH2F("Ele23_Ele12_leg2_pt_eta_pass","Ele23_Ele12_leg2_pt_eta",10,eta_bins,16,pt_bins_Ele23_Ele12_leg2);

   h_Ele23_Ele12_leg2_pt_total->Sumw2();
   h_Ele23_Ele12_leg2_eta_total->Sumw2();
   h_Ele23_Ele12_leg2_pt_eta_total->Sumw2();
   h_Ele23_Ele12_leg2_pt_pass->Sumw2();
   h_Ele23_Ele12_leg2_eta_pass->Sumw2();
   h_Ele23_Ele12_leg2_pt_eta_pass->Sumw2();

// MonoHiggs
   TH1F *h_DoubleEle33_pt_total = new TH1F("DoubleEle33_pt_total","DoubleEle33_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_eta_total = new TH1F("DoubleEle33_eta_total","DoubleEle33_eta",10,eta_bins);
   TH2F *h_DoubleEle33_pt_eta_total = new TH2F("DoubleEle33_pt_eta_total","DoubleEle33_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_pt_pass = new TH1F("DoubleEle33_pt_pass","DoubleEle33_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_eta_pass = new TH1F("DoubleEle33_eta_pass","DoubleEle33_eta",10,eta_bins);
   TH2F *h_DoubleEle33_pt_eta_pass = new TH2F("DoubleEle33_pt_eta_pass","DoubleEle33_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);

   h_DoubleEle33_pt_total->Sumw2();
   h_DoubleEle33_eta_total->Sumw2();
   h_DoubleEle33_pt_eta_total->Sumw2();
   h_DoubleEle33_pt_pass->Sumw2();
   h_DoubleEle33_eta_pass->Sumw2();
   h_DoubleEle33_pt_eta_pass->Sumw2();

   TH1F *h_DoubleEle33_leg_pt_total = new TH1F("DoubleEle33_leg_pt_total","DoubleEle33_leg_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_leg_eta_total = new TH1F("DoubleEle33_leg_eta_total","DoubleEle33_leg_eta",10,eta_bins);
   TH2F *h_DoubleEle33_leg_pt_eta_total = new TH2F("DoubleEle33_leg_pt_eta_total","DoubleEle33_leg_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_leg_pt_pass = new TH1F("DoubleEle33_leg_pt_pass","DoubleEle33_leg_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_leg_eta_pass = new TH1F("DoubleEle33_leg_eta_pass","DoubleEle33_leg_eta",10,eta_bins);
   TH2F *h_DoubleEle33_leg_pt_eta_pass = new TH2F("DoubleEle33_leg_pt_eta_pass","DoubleEle33_leg_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);

   h_DoubleEle33_leg_pt_total->Sumw2();
   h_DoubleEle33_leg_eta_total->Sumw2();
   h_DoubleEle33_leg_pt_eta_total->Sumw2();
   h_DoubleEle33_leg_pt_pass->Sumw2();
   h_DoubleEle33_leg_eta_pass->Sumw2();
   h_DoubleEle33_leg_pt_eta_pass->Sumw2();

   TH1F *h_DoubleEle27_leg_pt_total = new TH1F("DoubleEle27_leg_pt_total","DoubleEle27_leg_pt",16,pt_bins_DoubleEle27);
   TH1F *h_DoubleEle27_leg_eta_total = new TH1F("DoubleEle27_leg_eta_total","DoubleEle27_leg_eta",10,eta_bins);
   TH2F *h_DoubleEle27_leg_pt_eta_total = new TH2F("DoubleEle27_leg_pt_eta_total","DoubleEle27_leg_pt_eta",10,eta_bins,16,pt_bins_DoubleEle27);
   TH1F *h_DoubleEle27_leg_pt_pass = new TH1F("DoubleEle27_leg_pt_pass","DoubleEle27_leg_pt",16,pt_bins_DoubleEle27);
   TH1F *h_DoubleEle27_leg_eta_pass = new TH1F("DoubleEle27_leg_eta_pass","DoubleEle27_leg_eta",10,eta_bins);
   TH2F *h_DoubleEle27_leg_pt_eta_pass = new TH2F("DoubleEle27_leg_pt_eta_pass","DoubleEle27_leg_pt_eta",10,eta_bins,16,pt_bins_DoubleEle27);

   h_DoubleEle27_leg_pt_total->Sumw2();
   h_DoubleEle27_leg_eta_total->Sumw2();
   h_DoubleEle27_leg_pt_eta_total->Sumw2();
   h_DoubleEle27_leg_pt_pass->Sumw2();
   h_DoubleEle27_leg_eta_pass->Sumw2();
   h_DoubleEle27_leg_pt_eta_pass->Sumw2();

   TH1F *h_DoubleEle25_leg_pt_total = new TH1F("DoubleEle25_leg_pt_total","DoubleEle25_leg_pt",16,pt_bins_DoubleEle25);
   TH1F *h_DoubleEle25_leg_eta_total = new TH1F("DoubleEle25_leg_eta_total","DoubleEle25_leg_eta",10,eta_bins);
   TH2F *h_DoubleEle25_leg_pt_eta_total = new TH2F("DoubleEle25_leg_pt_eta_total","DoubleEle25_leg_pt_eta",10,eta_bins,16,pt_bins_DoubleEle25);
   TH1F *h_DoubleEle25_leg_pt_pass = new TH1F("DoubleEle25_leg_pt_pass","DoubleEle25_leg_pt",16,pt_bins_DoubleEle25);
   TH1F *h_DoubleEle25_leg_eta_pass = new TH1F("DoubleEle25_leg_eta_pass","DoubleEle25_leg_eta",10,eta_bins);
   TH2F *h_DoubleEle25_leg_pt_eta_pass = new TH2F("DoubleEle25_leg_pt_eta_pass","DoubleEle25_leg_pt_eta",10,eta_bins,16,pt_bins_DoubleEle25);

   h_DoubleEle25_leg_pt_total->Sumw2();
   h_DoubleEle25_leg_eta_total->Sumw2();
   h_DoubleEle25_leg_pt_eta_total->Sumw2();
   h_DoubleEle25_leg_pt_pass->Sumw2();
   h_DoubleEle25_leg_eta_pass->Sumw2();
   h_DoubleEle25_leg_pt_eta_pass->Sumw2();
   
   TH1F *h_Ele27_Ele37_leg1_pt_total = new TH1F("Ele27_Ele37_leg1_pt_total","Ele27_Ele37_leg1_pt",16,pt_bins_Ele27_Ele37_leg1);
   TH1F *h_Ele27_Ele37_leg1_eta_total = new TH1F("Ele27_Ele37_leg1_eta_total","Ele27_Ele37_leg1_eta",10,eta_bins);
   TH2F *h_Ele27_Ele37_leg1_pt_eta_total = new TH2F("Ele27_Ele37_leg1_pt_eta_total","Ele27_Ele37_leg1_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg1);
   TH1F *h_Ele27_Ele37_leg1_pt_pass = new TH1F("Ele27_Ele37_leg1_pt_pass","Ele27_Ele37_leg1_pt",16,pt_bins_Ele27_Ele37_leg1);
   TH1F *h_Ele27_Ele37_leg1_eta_pass = new TH1F("Ele27_Ele37_leg1_eta_pass","Ele27_Ele37_leg1_eta",10,eta_bins);
   TH2F *h_Ele27_Ele37_leg1_pt_eta_pass = new TH2F("Ele27_Ele37_leg1_pt_eta_pass","Ele27_Ele37_leg1_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg1);

   h_Ele27_Ele37_leg1_pt_total->Sumw2();
   h_Ele27_Ele37_leg1_eta_total->Sumw2();
   h_Ele27_Ele37_leg1_pt_eta_total->Sumw2();
   h_Ele27_Ele37_leg1_pt_pass->Sumw2();
   h_Ele27_Ele37_leg1_eta_pass->Sumw2();
   h_Ele27_Ele37_leg1_pt_eta_pass->Sumw2();

   TH1F *h_Ele27_Ele37_leg2_pt_total = new TH1F("Ele27_Ele37_leg2_pt_total","Ele27_Ele37_leg2_pt",16,pt_bins_Ele27_Ele37_leg2);
   TH1F *h_Ele27_Ele37_leg2_eta_total = new TH1F("Ele27_Ele37_leg2_eta_total","Ele27_Ele37_leg2_eta",10,eta_bins);
   TH2F *h_Ele27_Ele37_leg2_pt_eta_total = new TH2F("Ele27_Ele37_leg2_pt_eta_total","Ele27_Ele37_leg2_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg2);
   TH1F *h_Ele27_Ele37_leg2_pt_pass = new TH1F("Ele27_Ele37_leg2_pt_pass","Ele27_Ele37_leg2_pt",16,pt_bins_Ele27_Ele37_leg2);
   TH1F *h_Ele27_Ele37_leg2_eta_pass = new TH1F("Ele27_Ele37_leg2_eta_pass","Ele27_Ele37_leg2_eta",10,eta_bins);
   TH2F *h_Ele27_Ele37_leg2_pt_eta_pass = new TH2F("Ele27_Ele37_leg2_pt_eta_pass","Ele27_Ele37_leg2_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg2);

   h_Ele27_Ele37_leg2_pt_total->Sumw2();
   h_Ele27_Ele37_leg2_eta_total->Sumw2();
   h_Ele27_Ele37_leg2_pt_eta_total->Sumw2();
   h_Ele27_Ele37_leg2_pt_pass->Sumw2();
   h_Ele27_Ele37_leg2_eta_pass->Sumw2();
   h_Ele27_Ele37_leg2_pt_eta_pass->Sumw2();

   TH1F *h_Mu27_Ele37_legEle_pt_total = new TH1F("Mu27_Ele37_legEle_pt_total","Mu27_Ele37_legEle_pt",16,pt_bins_Ele27_Ele37_leg1);
   TH1F *h_Mu27_Ele37_legEle_eta_total = new TH1F("Mu27_Ele37_legEle_eta_total","Mu27_Ele37_legEle_eta",10,eta_bins);
   TH2F *h_Mu27_Ele37_legEle_pt_eta_total = new TH2F("Mu27_Ele37_legEle_pt_eta_total","Mu27_Ele37_legEle_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg1);
   TH1F *h_Mu27_Ele37_legEle_pt_pass = new TH1F("Mu27_Ele37_legEle_pt_pass","Mu27_Ele37_legEle_pt",16,pt_bins_Ele27_Ele37_leg1);
   TH1F *h_Mu27_Ele37_legEle_eta_pass = new TH1F("Mu27_Ele37_legEle_eta_pass","Mu27_Ele37_legEle_eta",10,eta_bins);
   TH2F *h_Mu27_Ele37_legEle_pt_eta_pass = new TH2F("Mu27_Ele37_legEle_pt_eta_pass","Mu27_Ele37_legEle_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg1);

   h_Mu27_Ele37_legEle_pt_total->Sumw2();
   h_Mu27_Ele37_legEle_eta_total->Sumw2();
   h_Mu27_Ele37_legEle_pt_eta_total->Sumw2();
   h_Mu27_Ele37_legEle_pt_pass->Sumw2();
   h_Mu27_Ele37_legEle_eta_pass->Sumw2();
   h_Mu27_Ele37_legEle_pt_eta_pass->Sumw2();

   TH1F *h_Mu37_Ele27_legEle_pt_total = new TH1F("Mu37_Ele27_legEle_pt_total","Mu37_Ele27_legEle_pt",16,pt_bins_Ele27_Ele37_leg2);
   TH1F *h_Mu37_Ele27_legEle_eta_total = new TH1F("Mu37_Ele27_legEle_eta_total","Mu37_Ele27_legEle_eta",10,eta_bins);
   TH2F *h_Mu37_Ele27_legEle_pt_eta_total = new TH2F("Mu37_Ele27_legEle_pt_eta_total","Mu37_Ele27_legEle_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg2);
   TH1F *h_Mu37_Ele27_legEle_pt_pass = new TH1F("Mu37_Ele27_legEle_pt_pass","Mu37_Ele27_legEle_pt",16,pt_bins_Ele27_Ele37_leg2);
   TH1F *h_Mu37_Ele27_legEle_eta_pass = new TH1F("Mu37_Ele27_legEle_eta_pass","Mu37_Ele27_legEle_eta",10,eta_bins);
   TH2F *h_Mu37_Ele27_legEle_pt_eta_pass = new TH2F("Mu37_Ele27_legEle_pt_eta_pass","Mu37_Ele27_legEle_pt_eta",10,eta_bins,16,pt_bins_Ele27_Ele37_leg2);

   h_Mu37_Ele27_legEle_pt_total->Sumw2();
   h_Mu37_Ele27_legEle_eta_total->Sumw2();
   h_Mu37_Ele27_legEle_pt_eta_total->Sumw2();
   h_Mu37_Ele27_legEle_pt_pass->Sumw2();
   h_Mu37_Ele27_legEle_eta_pass->Sumw2();
   h_Mu37_Ele27_legEle_pt_eta_pass->Sumw2();

/*
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg1_pt_total = new TH1F("DoubleEle33leg_or_Ele23Ele12leg1_pt_total","DoubleEle33leg_or_Ele23Ele12leg1_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg1_eta_total = new TH1F("DoubleEle33leg_or_Ele23Ele12leg1_eta_total","DoubleEle33leg_or_Ele23Ele12leg1_eta",10,eta_bins);
   TH2F *h_DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_total = new TH2F("DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_total","DoubleEle33leg_or_Ele23Ele12leg1_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg1_pt_pass = new TH1F("DoubleEle33leg_or_Ele23Ele12leg1_pt_pass","DoubleEle33leg_or_Ele23Ele12leg1_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg1_eta_pass = new TH1F("DoubleEle33leg_or_Ele23Ele12leg1_eta_pass","DoubleEle33leg_or_Ele23Ele12leg1_eta",10,eta_bins);
   TH2F *h_DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_pass = new TH2F("DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_pass","DoubleEle33leg_or_Ele23Ele12leg1_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);

   h_DoubleEle33leg_or_Ele23Ele12leg1_pt_total->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg1_eta_total->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_total->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg1_pt_pass->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg1_eta_pass->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_pass->Sumw2();

   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg2_pt_total = new TH1F("DoubleEle33leg_or_Ele23Ele12leg2_pt_total","DoubleEle33leg_or_Ele23Ele12leg2_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg2_eta_total = new TH1F("DoubleEle33leg_or_Ele23Ele12leg2_eta_total","DoubleEle33leg_or_Ele23Ele12leg2_eta",10,eta_bins);
   TH2F *h_DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_total = new TH2F("DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_total","DoubleEle33leg_or_Ele23Ele12leg2_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg2_pt_pass = new TH1F("DoubleEle33leg_or_Ele23Ele12leg2_pt_pass","DoubleEle33leg_or_Ele23Ele12leg2_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33leg_or_Ele23Ele12leg2_eta_pass = new TH1F("DoubleEle33leg_or_Ele23Ele12leg2_eta_pass","DoubleEle33leg_or_Ele23Ele12leg2_eta",10,eta_bins);
   TH2F *h_DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_pass = new TH2F("DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_pass","DoubleEle33leg_or_Ele23Ele12leg2_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);

   h_DoubleEle33leg_or_Ele23Ele12leg2_pt_total->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg2_eta_total->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_total->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg2_pt_pass->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg2_eta_pass->Sumw2();
   h_DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_pass->Sumw2();

   TH1F *h_DoubleEle33_or_Ele23Ele12leg1_pt_total = new TH1F("DoubleEle33_or_Ele23Ele12leg1_pt_total","DoubleEle33_or_Ele23Ele12leg1_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_or_Ele23Ele12leg1_eta_total = new TH1F("DoubleEle33_or_Ele23Ele12leg1_eta_total","DoubleEle33_or_Ele23Ele12leg1_eta",10,eta_bins);
   TH2F *h_DoubleEle33_or_Ele23Ele12leg1_pt_eta_total = new TH2F("DoubleEle33_or_Ele23Ele12leg1_pt_eta_total","DoubleEle33_or_Ele23Ele12leg1_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_or_Ele23Ele12leg1_pt_pass = new TH1F("DoubleEle33_or_Ele23Ele12leg1_pt_pass","DoubleEle33_or_Ele23Ele12leg1_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_or_Ele23Ele12leg1_eta_pass = new TH1F("DoubleEle33_or_Ele23Ele12leg1_eta_pass","DoubleEle33_or_Ele23Ele12leg1_eta",10,eta_bins);
   TH2F *h_DoubleEle33_or_Ele23Ele12leg1_pt_eta_pass = new TH2F("DoubleEle33_or_Ele23Ele12leg1_pt_eta_pass","DoubleEle33_or_Ele23Ele12leg1_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);

   h_DoubleEle33_or_Ele23Ele12leg1_pt_total->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg1_eta_total->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg1_pt_eta_total->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg1_pt_pass->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg1_eta_pass->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg1_pt_eta_pass->Sumw2();

   TH1F *h_DoubleEle33_or_Ele23Ele12leg2_pt_total = new TH1F("DoubleEle33_or_Ele23Ele12leg2_pt_total","DoubleEle33_or_Ele23Ele12leg2_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_or_Ele23Ele12leg2_eta_total = new TH1F("DoubleEle33_or_Ele23Ele12leg2_eta_total","DoubleEle33_or_Ele23Ele12leg2_eta",10,eta_bins);
   TH2F *h_DoubleEle33_or_Ele23Ele12leg2_pt_eta_total = new TH2F("DoubleEle33_or_Ele23Ele12leg2_pt_eta_total","DoubleEle33_or_Ele23Ele12leg2_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_or_Ele23Ele12leg2_pt_pass = new TH1F("DoubleEle33_or_Ele23Ele12leg2_pt_pass","DoubleEle33_or_Ele23Ele12leg2_pt",16,pt_bins_DoubleEle33);
   TH1F *h_DoubleEle33_or_Ele23Ele12leg2_eta_pass = new TH1F("DoubleEle33_or_Ele23Ele12leg2_eta_pass","DoubleEle33_or_Ele23Ele12leg2_eta",10,eta_bins);
   TH2F *h_DoubleEle33_or_Ele23Ele12leg2_pt_eta_pass = new TH2F("DoubleEle33_or_Ele23Ele12leg2_pt_eta_pass","DoubleEle33_or_Ele23Ele12leg2_pt_eta",10,eta_bins,16,pt_bins_DoubleEle33);

   h_DoubleEle33_or_Ele23Ele12leg2_pt_total->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg2_eta_total->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg2_pt_eta_total->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg2_pt_pass->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg2_eta_pass->Sumw2();
   h_DoubleEle33_or_Ele23Ele12leg2_pt_eta_pass->Sumw2();
*/
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //for (Long64_t jentry=0; jentry<10;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000000 == 0)cout<<"number of events processed : "<<jentry<<endl;
      if(nEle!=2) continue;
      int first  = rand()%2;
      int second = (first+1)%2;      
      if(ele_charge->at(first) * ele_charge->at(second)>0)continue;
      bool tag_EleId = passEleIdTight->at(first);
      bool tag_EleKin = ele_pt->at(first)>ptTag && fabs(ele_etaSC->at(first))<2.5;
      bool tag_TriggerMatch = passFilterEle35->at(first);

      // MonoHiggs
      // bool tag_TriggerMatch_monoH = passFilterEle35->at(first) || passFilter_monoHSingleEle->at(first);

      if(!(tag_EleId && tag_EleKin && tag_TriggerMatch))continue;

      //bool probe_EleId = HWW_Electron_Def(second, ele_etaSC->at(second));
      bool probe_EleId = HWW_Electron_17v5(second, ele_etaSC->at(second));
      bool probe_EleKin = fabs(ele_etaSC->at(second))<2.5;

      if(!(probe_EleId && probe_EleKin)) continue;

      TLorentzVector tag_eleLV, probe_eleLV, Z_candLV;
      tag_eleLV.SetPtEtaPhiE(ele_pt->at(first), ele_etaSC->at(first), ele_phiSC->at(first), ele_energy->at(first));
      probe_eleLV.SetPtEtaPhiE(ele_pt->at(second), ele_etaSC->at(second), ele_phiSC->at(second), ele_energy->at(second));
      Z_candLV = tag_eleLV + probe_eleLV;

      if (Z_candLV.M()<zMassL || Z_candLV.M() > zMassR) continue;

      h_Ele35_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Ele35_eta_total->Fill(ele_etaSC->at(second)); 
      h_Ele35_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
     
      h_Ele23_Ele12_leg1_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>25)h_Ele23_Ele12_leg1_eta_total->Fill(ele_etaSC->at(second)); 
      h_Ele23_Ele12_leg1_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_Ele23_Ele12_leg2_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>15)h_Ele23_Ele12_leg2_eta_total->Fill(ele_etaSC->at(second)); 
      h_Ele23_Ele12_leg2_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      if (passFilterEle35->at(second)){
      h_Ele35_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Ele35_eta_pass->Fill(ele_etaSC->at(second)); 
      h_Ele35_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 
      if (passFilterEle23_12_leg1->at(second)){
      h_Ele23_Ele12_leg1_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>25)h_Ele23_Ele12_leg1_eta_pass->Fill(ele_etaSC->at(second)); 
      h_Ele23_Ele12_leg1_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 
      if (passFilterEle23_12_leg2->at(second)){
      h_Ele23_Ele12_leg2_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>15)h_Ele23_Ele12_leg2_eta_pass->Fill(ele_etaSC->at(second)); 
       h_Ele23_Ele12_leg2_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      // MonoHiggs
      h_DoubleEle33_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      
      h_DoubleEle33_leg_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_leg_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_leg_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_DoubleEle27_leg_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle27_leg_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle27_leg_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_DoubleEle25_leg_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle25_leg_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle25_leg_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_Ele27_Ele37_leg1_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Ele27_Ele37_leg1_eta_total->Fill(ele_etaSC->at(second)); 
      h_Ele27_Ele37_leg1_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_Ele27_Ele37_leg2_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Ele27_Ele37_leg2_eta_total->Fill(ele_etaSC->at(second)); 
      h_Ele27_Ele37_leg2_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_Mu27_Ele37_legEle_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Mu27_Ele37_legEle_eta_total->Fill(ele_etaSC->at(second)); 
      h_Mu27_Ele37_legEle_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_Mu37_Ele27_legEle_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Mu37_Ele27_legEle_eta_total->Fill(ele_etaSC->at(second)); 
      h_Mu37_Ele27_legEle_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

/*
      h_DoubleEle33leg_or_Ele23Ele12leg1_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33leg_or_Ele23Ele12leg1_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_DoubleEle33leg_or_Ele23Ele12leg2_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33leg_or_Ele23Ele12leg2_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_DoubleEle33_or_Ele23Ele12leg1_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_or_Ele23Ele12leg1_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_or_Ele23Ele12leg1_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 

      h_DoubleEle33_or_Ele23Ele12leg2_pt_total->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_or_Ele23Ele12leg2_eta_total->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_or_Ele23Ele12leg2_pt_eta_total->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
*/
      if (passFilterDoubleEle33->at(second)){
      h_DoubleEle33_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterDoubleEle33_leg->at(second)){
      h_DoubleEle33_leg_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_leg_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_leg_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterDoubleEle27_leg->at(second)){
      h_DoubleEle27_leg_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle27_leg_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle27_leg_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterDoubleEle25_leg->at(second)){
      h_DoubleEle25_leg_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle25_leg_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle25_leg_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterEle27_37_leg1->at(second)){
      h_Ele27_Ele37_leg1_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Ele27_Ele37_leg1_eta_pass->Fill(ele_etaSC->at(second)); 
      h_Ele27_Ele37_leg1_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterEle27_37_leg2->at(second)){
      h_Ele27_Ele37_leg2_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Ele27_Ele37_leg2_eta_pass->Fill(ele_etaSC->at(second)); 
      h_Ele27_Ele37_leg2_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterMu27_Ele37_legEle->at(second)){
      h_Mu27_Ele37_legEle_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Mu27_Ele37_legEle_eta_pass->Fill(ele_etaSC->at(second)); 
      h_Mu27_Ele37_legEle_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterMu37_Ele27_legEle->at(second)){
      h_Mu37_Ele27_legEle_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_Mu37_Ele27_legEle_eta_pass->Fill(ele_etaSC->at(second)); 
      h_Mu37_Ele27_legEle_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

/*
      if (passFilterDoubleEle33_leg->at(second) || passFilterEle23_12_leg1->at(second)){
      h_DoubleEle33leg_or_Ele23Ele12leg1_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33leg_or_Ele23Ele12leg1_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33leg_or_Ele23Ele12leg1_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterDoubleEle33_leg->at(second) || passFilterEle23_12_leg2->at(second)){
      h_DoubleEle33leg_or_Ele23Ele12leg2_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33leg_or_Ele23Ele12leg2_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33leg_or_Ele23Ele12leg2_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterDoubleEle33->at(second) || passFilterEle23_12_leg1->at(second)){
      h_DoubleEle33_or_Ele23Ele12leg1_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_or_Ele23Ele12leg1_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_or_Ele23Ele12leg1_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 

      if (passFilterDoubleEle33->at(second) || passFilterEle23_12_leg2->at(second)){
      h_DoubleEle33_or_Ele23Ele12leg2_pt_pass->Fill(ele_pt->at(second)); 
      if(ele_pt->at(second)>40)h_DoubleEle33_or_Ele23Ele12leg2_eta_pass->Fill(ele_etaSC->at(second)); 
      h_DoubleEle33_or_Ele23Ele12leg2_pt_eta_pass->Fill(ele_etaSC->at(second),ele_pt->at(second)); 
      } 
*/
      // if (Cut(ientry) < 0) continue;
    }
file->Write(); 
  }
 
}
bool TagAndProbe::HWW_Electron_17v5(int i, double eta)
{
    double sieie = ele_full5x5_sigmaIetaIeta->at(i);
    double eInvMinusPInv = ele_ooEmooP->at(i);
    bool pass_mvaFall17Iso_WP90 = passMVAIsoWP90->at(i);
    bool convVeto = ele_passConversionVeto->at(i);
    double relIso = ele_relCombIsoWithEA->at(i);
    if (!convVeto) return false;
    if(fabs(eta) >= 2.5) return false;
    if(relIso >= 0.06) return false;
    if(fabs(eta) <= 1.479){
        if (ele_d0->at(i)>=0.05) return false;
        if (ele_dz->at(i)>=0.1) return false;
    }
    else{
        if (sieie >= 0.03) return false;
        if (eInvMinusPInv >= 0.014) return false;
        if (ele_d0->at(i)>=0.1) return false;
        if (ele_dz->at(i)>=0.2) return false;
    }
    return true;
}


bool TagAndProbe::HWW_Electron_Def(int i, double eta)
{

double sieie = ele_full5x5_sigmaIetaIeta->at(i);
double dEtaSC = ele_dEtaSeed->at(i);
double hoe = ele_hOverE->at(i);
double eInvMinusPInv = ele_ooEmooP->at(i);
double dr03TkSumPt_overPt = ele_dr03TkSumPt->at(i);
double dr03EcalRecHitSumEt_overPt = ele_dr03EcalRecHitSumEt->at(i);
double dr03HcalDepth1TowerSumEt_overPt = ele_dr03HcalDepth1TowerSumEt->at(i);
double lostHits = ele_expectedMissingInnerHits->at(i);
bool convVeto = ele_passConversionVeto->at(i);
double relIso = ele_relCombIsoWithEA->at(i);

if(fabs(eta) < 1.479){
if (sieie >= 0.011) return false;
//if (fabs(dEtaSC) >= 0.004) return false;
if (hoe >= 0.06) return false;
if (fabs(eInvMinusPInv) >= 0.013) return false;
if (dr03TkSumPt_overPt/ele_pt->at(i) >= 0.08) return false;
if (dr03EcalRecHitSumEt_overPt/ele_pt->at(i) >= 0.15) return false;
if (dr03HcalDepth1TowerSumEt_overPt/ele_pt->at(i) >= 0.12) return false;
if (lostHits >= 1) return false;
if (!convVeto) return false;
if (relIso >= 0.06) return false;
if (!passMVAIsoWP90) return false;
if (ele_d0->at(i)>=0.05) return false;
if (ele_dz->at(i)>=0.1) return false;
}

else{
if (sieie >= 0.03) return false;
//if (fabs(dEtaSC) >= 0.006) return false;
if (hoe >= 0.07) return false;
if (fabs(eInvMinusPInv) >= 0.013) return false;
if (dr03TkSumPt_overPt/ele_pt->at(i) >= 0.08) return false;
if (dr03EcalRecHitSumEt_overPt/ele_pt->at(i) >= 0.13) return false;
if (dr03HcalDepth1TowerSumEt_overPt/ele_pt->at(i) >= 0.08) return false;
if (lostHits >= 1) return false;
if (!convVeto) return false;
if (relIso >= 0.12) return false;
if (!passMVAIsoWP90) return false;
if (ele_d0->at(i)>=0.1) return false;
if (ele_dz->at(i)>=0.2) return false;
}

return true;

}

bool TagAndProbe::HWW_Electron_NewDef(int i, double eta)
{

double sieie = ele_full5x5_sigmaIetaIeta->at(i);
double dEtaSC = ele_dEtaSeed->at(i);
double dPhiIn = ele_dPhiIn->at(i);
double hoe = ele_hOverE->at(i);
double eInvMinusPInv = ele_ooEmooP->at(i);
double dr03TkSumPt_overPt = ele_dr03TkSumPt->at(i);
double dr03EcalRecHitSumEt_overPt = ele_dr03EcalRecHitSumEt->at(i);
double dr03HcalDepth1TowerSumEt_overPt = ele_dr03HcalDepth1TowerSumEt->at(i);
double lostHits = ele_expectedMissingInnerHits->at(i);
bool convVeto = ele_passConversionVeto->at(i);
double relIso = ele_relCombIsoWithEA->at(i);

if(fabs(eta) < 1.479){    // Barrel
double hoe_compareWith = 0.05 +(1.12/ele_energySC->at(i)) + (0.0368*(rho/ele_energySC->at(i)));
if (sieie >= 0.0128) return false;
if (fabs(dEtaSC) >= 0.00523) return false;
if (fabs(dPhiIn) >= 0.159) return false;
if (hoe >= hoe_compareWith) return false;
if (fabs(eInvMinusPInv) >= 0.193) return false;
if (!(lostHits <= 2)) return false;
if (!convVeto) return false;
if (relIso >= 0.168) return false;
if (!passMVAIsoWP90) return false;
if (ele_d0->at(i)>=0.05) return false;
if (ele_dz->at(i)>=0.1) return false;
}

else{
double hoe_compareWith = 0.05 +(0.5/ele_energySC->at(i)) + (0.201*(rho/ele_energySC->at(i)));
if (sieie >= 0.03) return false;
if (fabs(dEtaSC) >= 0.00984) return false;
if (fabs(dPhiIn) >= 0.157) return false;
if (hoe >= hoe_compareWith) return false;
if (fabs(eInvMinusPInv) >= 0.014) return false;
if (!(lostHits <= 3)) return false;
if (!convVeto) return false;
if (relIso >= 0.185) return false;
if (!passMVAIsoWP90) return false;
if (ele_d0->at(i)>=0.1) return false;
if (ele_dz->at(i)>=0.2) return false;
}

return true;

}
