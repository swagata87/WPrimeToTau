#include <iostream>
#include <algorithm>
#include "TLatex.h"
#include <iomanip>
#include <vector>
#include "TPad.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TSystem.h"
#include "TImage.h"
#include "TKey.h"
#include "TH1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPostScript.h"
#include <TPaveStats.h>
#include "TLegend.h"
#include <TProfile.h>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"

// kfactor source : https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
// Poisson error //
//  mT_Stage1->Sumw2(kFALSE);
//mT_Stage1->SetBinErrorOption(TH1::kPoisson);
//

int Plot_mT_Stage1() {

  double lumi=4.353; //--inv fb--//

  unsigned long long evt_DYJetsToLL_M50=1;
  unsigned long long evt_TT=1;
  unsigned long long evt_WJetsToLNu=1;
  //  TH1::SetDefaultSumw2(); 
  //  gROOT->SetBatch(kTRUE);
  //  TFile *file_DYJetsToLL_M50  = new TFile("../python/crab_projects/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/results/hist.root");
  //double xs_DYJetsToLL_M50=6104000; //--fb--//

  TFile *file_DYJetsToLL_M50  = new TFile("../python/crab_projects/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");             
  double xs_DYJetsToLL_M50=4895000;  //--fb--//                                                                                                                 
  double kfact_DYJetsToLL_M50=1.0;
  //  TFile *file_DYJetsToLL_M5to50  = new TFile("../python/crab_projects/crab_DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");    
  //  double xs_DYJetsToLL_M5to50=;  //--fb--//                                                                                                                    

  TFile *file_TT              = new TFile("../python/crab_projects/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/results/hist.root");
  double xs_TT=730000; //--fb--//
  double kfact_TT= 1.139;

  //TFile *file_WJetsToLNu      = new TFile("../python/crab_projects/crab_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/results/hist.root");
  //double xs_WJetsToLNu=60290000; //--fb--//
  ////  TFile *file_WJetsToLNu      = new TFile("../python/crab_projects/crab_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  ////  double xs_WJetsToLNu= 50690000; //--fb--//

  TFile *file_WJetsToLNu_HT100To200  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT100To200 = 1345000 ; //--fb--//
  double kfact_WJetsToLNu_HT100To200 = 1.21 ; 

  TFile *file_WJetsToLNu_HT200To400  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT200To400 = 359700 ; //--fb--//
  double kfact_WJetsToLNu_HT200To400 = 1.21 ;

  TFile *file_WJetsToLNu_HT400To600  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT400To600 = 48910 ; //--fb--//
  double kfact_WJetsToLNu_HT400To600 = 1.21 ;

  TFile *file_WJetsToLNu_HT600To800  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT600To800 = 12050 ; //--fb--//
  double kfact_WJetsToLNu_HT600To800 = 1.21 ;

  TFile *file_WJetsToLNu_HT800To1200  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT800To1200 = 5501 ; //--fb--//
  double kfact_WJetsToLNu_HT800To1200 = 1.21 ;

  TFile *file_WJetsToLNu_HT1200To2500  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT1200To2500 = 1329 ; //--fb--//
  double kfact_WJetsToLNu_HT1200To2500 = 1.21 ;

  TFile *file_WJetsToLNu_HT2500ToInf  = new TFile("../python/crab_projects/crab_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_WJetsToLNu_HT2500ToInf = 32.16  ; //--fb--//
  double kfact_WJetsToLNu_HT2500ToInf = 1.21 ;

  TFile *file_ST_tchannel_antitop=new TFile("../python/crab_projects/crab_ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tchannel_antitop = 80950; //--fb--//
  double kfact_ST_tchannel_antitop = 1.0;
  //
  TFile *file_ST_tchannel_top=new TFile("../python/crab_projects/crab_ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tchannel_top = 103200; //--fb--//
  double kfact_ST_tchannel_top = 1.0;
  //
  TFile *file_ST_tW_antitop=new TFile("../python/crab_projects/crab_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tW_antitop = 38090; //--fb--//
  double kfact_ST_tW_antitop = 1.0;
  //
  TFile *file_ST_tW_top=new TFile("../python/crab_projects/crab_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/results/hist.root");
  double xs_ST_tW_top = 38090; //--fb--//
  double kfact_ST_tW_top = 1.0; 
  //
  TFile *file_WW=new TFile("../python/crab_projects/crab_WW_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WW = 63210; //--fb--//
  double kfact_WW = 1.0;
  //
  TFile *file_WZ=new TFile("../python/crab_projects/crab_WZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_WZ = 22820; //--fb--//
  double kfact_WZ = 2.06; // 47.13/22.82
  //
  TFile *file_ZZ=new TFile("../python/crab_projects/crab_ZZ_TuneCUETP8M1_13TeV-pythia8/results/hist.root");
  double xs_ZZ = 10320; //--fb--//
  double kfact_ZZ = 1.60 ; //16523/10320
  //
  TFile *file_QCD_HT200to300=new TFile("../python/crab_projects/crab_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT200to300 = 1717000000; //--fb--//
  double kfact_QCD_HT200to300 = 1.0;
  //
  TFile *file_QCD_HT300to500=new TFile("../python/crab_projects/crab_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT300to500 = 351300000; //--fb--//
  double kfact_QCD_HT300to500 = 1.0; 
  //
  TFile *file_QCD_HT500to700=new TFile("../python/crab_projects/crab_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT500to700 = 31630000 ; //--fb--//
  double kfact_QCD_HT500to700 = 1.0;
  //
  TFile *file_QCD_HT700to1000=new TFile("../python/crab_projects/crab_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT700to1000 = 6802000 ; //--fb--//
  double kfact_QCD_HT700to1000 = 1.0;
  //
  TFile *file_QCD_HT1000to1500=new TFile("../python/crab_projects/crab_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT1000to1500 = 1206000 ; //--fb--//
  double kfact_QCD_HT1000to1500 = 1.0 ;
  //
  TFile *file_QCD_HT1500to2000=new TFile("../python/crab_projects/crab_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT1500to2000 = 120400 ; //--fb--//
  double kfact_QCD_HT1500to2000 = 1.0 ;
  //
  TFile *file_QCD_HT2000toInf=new TFile("../python/crab_projects/crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/hist.root");
  double xs_QCD_HT2000toInf = 25250 ; //--fb--//
  double kfact_QCD_HT2000toInf = 1.0 ;
  //
  TFile *file_ZJetsToNuNu_HT100To200 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-100To200_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT100To200 =  280350; //--fb--//
  double kfact_ZJetsToNuNu_HT100To200 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT200To400 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-200To400_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT200To400 = 77670 ; //--fb--//
  double kfact_ZJetsToNuNu_HT200To400 = 1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT400To600 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-400To600_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT400To600 = 10730 ; //--fb--//
  double kfact_ZJetsToNuNu_HT400To600 =  1.23 ;
  //
  TFile *file_ZJetsToNuNu_HT600To800 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-600To800_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT600To800 = 853 ; //--fb--//
  double kfact_ZJetsToNuNu_HT600To800 = 1.0 ;
  //
  TFile *file_ZJetsToNuNu_HT800To1200 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-800To1200_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT800To1200 = 394.2 ; //--fb--//
  double kfact_ZJetsToNuNu_HT800To1200 = 1.0 ; 
  //
  TFile *file_ZJetsToNuNu_HT1200To2500 =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT1200To2500 = 97.4 ; //--fb--//
  double kfact_ZJetsToNuNu_HT1200To2500 = 1.0 ; 
  //
  TFile *file_ZJetsToNuNu_HT2500ToInf =new TFile("../python/crab_projects/crab_ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/results/hist.root");
  double xs_ZJetsToNuNu_HT2500ToInf = 2.308 ; //--fb--//
  double kfact_ZJetsToNuNu_HT2500ToInf = 1.0 ;
 
  /// DATA ///
  TFile *file_Tau_Run2016D = new TFile("../python/crab_projects/crab_Tau_Run2016D_PromptReco_v2/results/hist.root");

  /// Signal ///
  TFile *file_Wprime_M1000 = new TFile("../python/crab_projects/crab_WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_Wprime_M1000= 3060; // --fb-- //


  //-DY-//
  std::cout << "\n**DY" << std::endl;
  TH1D* h1_evt_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/eventCount");
  evt_DYJetsToLL_M50 = h1_evt_DYJetsToLL_M50->GetEntries(); // Integral();
  double wt_DYJetsToLL_M50 = (xs_DYJetsToLL_M50*lumi)/evt_DYJetsToLL_M50 ;
  TH1D* mT_Stage1_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1");
  mT_Stage1_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  mT_Stage1_DYJetsToLL_M50->SetFillColorAlpha(kRed,0.5);
  mT_Stage1_DYJetsToLL_M50->SetLineColor(kBlack);
  mT_Stage1_DYJetsToLL_M50->Rebin(50);  
  //
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_TauScaleUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);  
  // mT_Stage1_TauScaleUp_DYJetsToLL_M50->Rebin(50);
  TH1D* mT_Stage1_TauScaleDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_TauScaleDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_TauScaleDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_JetEnUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_JetEnUp_DYJetsToLL_M50->Rebin(50);  
  TH1D* mT_Stage1_metUncert_JetEnDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_JetEnDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_JetEnDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_JetResUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_JetResUp_DYJetsToLL_M50->Rebin(50);  
  TH1D* mT_Stage1_metUncert_JetResDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_JetResDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_JetResDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_MuonEnUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_MuonEnUp_DYJetsToLL_M50->Rebin(50);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_MuonEnDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_MuonEnDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_ElectronEnUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_ElectronEnUp_DYJetsToLL_M50->Rebin(50);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_ElectronEnDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_ElectronEnDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_TauEnUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50); 
  // mT_Stage1_metUncert_TauEnUp_DYJetsToLL_M50->Rebin(50);
  TH1D* mT_Stage1_metUncert_TauEnDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_TauEnDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_TauEnDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_PhotonEnUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_PhotonEnUp_DYJetsToLL_M50->Rebin(50);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_PhotonEnDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_PhotonEnDown_DYJetsToLL_M50->Rebin(50);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_UnclusteredEnUp_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_UnclusteredEnUp_DYJetsToLL_M50->Rebin(50);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_DYJetsToLL_M50 = (TH1D*)file_DYJetsToLL_M50->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_DYJetsToLL_M50->Scale(wt_DYJetsToLL_M50);
  mT_Stage1_metUncert_UnclusteredEnDown_DYJetsToLL_M50->Scale(kfact_DYJetsToLL_M50);
  // mT_Stage1_metUncert_UnclusteredEnDown_DYJetsToLL_M50->Rebin(50);
  //
  
  //-TT-//
  std::cout << "\n**TTbar" << std::endl;
  TH1D* h1_evt_TT = (TH1D*)file_TT->Get("demo/eventCount");
  evt_TT = h1_evt_TT->GetEntries(); // Integral();
  double wt_TT = (xs_TT*lumi)/evt_TT ;
  TH1D* mT_Stage1_TT  = (TH1D*)file_TT->Get("demo/mT_Stage1");
  mT_Stage1_TT->Scale(wt_TT);
  mT_Stage1_TT->Scale(kfact_TT);
  mT_Stage1_TT->SetFillColor(kBlue-7);
  mT_Stage1_TT->SetLineColor(kBlack);
  mT_Stage1_TT->Rebin(50);
  //
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_TT->Scale(wt_TT);
  mT_Stage1_TauScaleUp_TT->Scale(kfact_TT);
  // mT_Stage1_TauScaleUp_TT->Rebin(50);
  TH1D* mT_Stage1_TauScaleDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_TT->Scale(wt_TT);
  mT_Stage1_TauScaleDown_TT->Scale(kfact_TT);
  // mT_Stage1_TauScaleDown_TT->Rebin(50);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_JetEnUp_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_JetEnUp_TT->Rebin(50);
  TH1D* mT_Stage1_metUncert_JetEnDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_JetEnDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_JetEnDown_TT->Rebin(50);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_JetResUp_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_JetResUp_TT->Rebin(50);
  TH1D* mT_Stage1_metUncert_JetResDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_JetResDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_JetResDown_TT->Rebin(50);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_MuonEnUp_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_MuonEnUp_TT->Rebin(50);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_MuonEnDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_MuonEnDown_TT->Rebin(50);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_ElectronEnUp_TT->Scale(kfact_TT);
  //  mT_Stage1_metUncert_ElectronEnUp_TT->Rebin(50);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_ElectronEnDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_ElectronEnDown_TT->Rebin(50);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_TauEnUp_TT->Scale(kfact_TT); 
  // mT_Stage1_metUncert_TauEnUp_TT->Rebin(50); 
  TH1D* mT_Stage1_metUncert_TauEnDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_TauEnDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_TauEnDown_TT->Rebin(50);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_PhotonEnUp_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_PhotonEnUp_TT->Rebin(50);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_PhotonEnDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_PhotonEnDown_TT->Rebin(50);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_TT->Scale(wt_TT);
  mT_Stage1_metUncert_UnclusteredEnUp_TT->Scale(kfact_TT);
  //  mT_Stage1_metUncert_UnclusteredEnUp_TT->Rebin(50);
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_TT = (TH1D*)file_TT->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_TT->Scale(wt_TT);
  mT_Stage1_metUncert_UnclusteredEnDown_TT->Scale(kfact_TT);
  // mT_Stage1_metUncert_UnclusteredEnDown_TT->Rebin(50);
  //

  //file_ST_tchannel_antitop
  TH1D* h1_evt_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/eventCount");
  unsigned long long evt_ST_tchannel_antitop = h1_evt_ST_tchannel_antitop->GetEntries(); //Integral();
  double wt_ST_tchannel_antitop = (xs_ST_tchannel_antitop*lumi)/evt_ST_tchannel_antitop ;
  TH1D* mT_Stage1_ST_tchannel_antitop  = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1");
  mT_Stage1_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  //
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_TauScaleUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);  
  // mT_Stage1_TauScaleUp_ST_tchannel_antitop->Rebin(50);
  TH1D* mT_Stage1_TauScaleDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_TauScaleDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_TauScaleDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetEnUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_JetEnUp_ST_tchannel_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetEnDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_JetEnDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetResUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_JetResUp_ST_tchannel_antitop->Rebin(50);
  TH1D* mT_Stage1_metUncert_JetResDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetResDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_JetResDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_MuonEnUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_MuonEnUp_ST_tchannel_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_MuonEnDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_MuonEnDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_TauEnUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_TauEnUp_ST_tchannel_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_TauEnDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_TauEnDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  // mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_antitop->Rebin(50);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  //mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_antitop = (TH1D*)file_ST_tchannel_antitop->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_antitop->Scale(wt_ST_tchannel_antitop);
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_antitop->Scale(kfact_ST_tchannel_antitop);
  //mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_antitop->Rebin(50);
  //
 
  //file_ST_tchannel_top
  TH1D* h1_evt_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/eventCount");
  unsigned long long evt_ST_tchannel_top = h1_evt_ST_tchannel_top->GetEntries(); //Integral();
  double wt_ST_tchannel_top = (xs_ST_tchannel_top*lumi)/evt_ST_tchannel_top ;
  TH1D* mT_Stage1_ST_tchannel_top  = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1");
  mT_Stage1_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  //
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_TauScaleUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);  
  // mT_Stage1_TauScaleUp_ST_tchannel_top->Rebin(50);
  TH1D* mT_Stage1_TauScaleDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_TauScaleDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_TauScaleDown_ST_tchannel_top->Rebin(50);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_JetEnUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_JetEnUp_ST_tchannel_top->Rebin(50);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_JetEnDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_JetEnDown_ST_tchannel_top->Rebin(50); 
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_JetResUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);  
  // mT_Stage1_metUncert_JetResUp_ST_tchannel_top->Rebin(50);
  TH1D* mT_Stage1_metUncert_JetResDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_JetResDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_JetResDown_ST_tchannel_top->Rebin(50);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_MuonEnUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top); 
  // mT_Stage1_metUncert_MuonEnUp_ST_tchannel_top->Rebin(50); 
  TH1D* mT_Stage1_metUncert_MuonEnDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_MuonEnDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_MuonEnDown_ST_tchannel_top->Rebin(50);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_top->Rebin(50);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_top->Rebin(50);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_TauEnUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_TauEnUp_ST_tchannel_top->Rebin(50);
  TH1D* mT_Stage1_metUncert_TauEnDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_TauEnDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_TauEnDown_ST_tchannel_top->Rebin(50);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_top->Rebin(50);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_top->Rebin(50);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_top->Rebin(50);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_top = (TH1D*)file_ST_tchannel_top->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_top->Scale(wt_ST_tchannel_top);
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_top->Scale(kfact_ST_tchannel_top);
  // mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_top->Rebin(50);
  //

  //file_ST_tW_antitop
  TH1D* h1_evt_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/eventCount");
  unsigned long long evt_ST_tW_antitop = h1_evt_ST_tW_antitop->GetEntries(); //Integral();
  double wt_ST_tW_antitop = (xs_ST_tW_antitop*lumi)/evt_ST_tW_antitop ;
  TH1D* mT_Stage1_ST_tW_antitop  = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1");
  mT_Stage1_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  //
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_TauScaleUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);  
  //mT_Stage1_TauScaleUp_ST_tW_antitop->Rebin(50);
  TH1D* mT_Stage1_TauScaleDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_TauScaleDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_TauScaleDown_ST_tW_antitop->Rebin(50);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_JetEnUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_JetEnUp_ST_tW_antitop->Rebin(50);
  TH1D* mT_Stage1_metUncert_JetEnDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_JetEnDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_JetEnDown_ST_tW_antitop->Rebin(50);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_JetResUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_JetResUp_ST_tW_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_JetResDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_JetResDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_JetResDown_ST_tW_antitop->Rebin(50);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_MuonEnUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_MuonEnUp_ST_tW_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_MuonEnDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_MuonEnDown_ST_tW_antitop->Rebin(50);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_ElectronEnUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_ElectronEnUp_ST_tW_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_ElectronEnDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_ElectronEnDown_ST_tW_antitop->Rebin(50);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_TauEnUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_TauEnUp_ST_tW_antitop->Rebin(50);
  TH1D* mT_Stage1_metUncert_TauEnDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_TauEnDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_TauEnDown_ST_tW_antitop->Rebin(50);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_PhotonEnUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  //mT_Stage1_metUncert_PhotonEnUp_ST_tW_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_PhotonEnDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  //mT_Stage1_metUncert_PhotonEnDown_ST_tW_antitop->Rebin(50);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_antitop->Rebin(50);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_antitop = (TH1D*)file_ST_tW_antitop->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_antitop->Scale(wt_ST_tW_antitop);
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_antitop->Scale(kfact_ST_tW_antitop);
  // mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_antitop->Rebin(50);
  //
  
  //file_ST_tW_top
  TH1D* h1_evt_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/eventCount");
  unsigned long long evt_ST_tW_top = h1_evt_ST_tW_top->GetEntries(); //Integral();
  double wt_ST_tW_top = (xs_ST_tW_top*lumi)/evt_ST_tW_top ;
  TH1D* mT_Stage1_ST_tW_top  = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1");
  mT_Stage1_ST_tW_top->Scale(wt_ST_tW_top);
  //
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_TauScaleUp_ST_tW_top->Scale(kfact_ST_tW_top);
  // mT_Stage1_TauScaleUp_ST_tW_top->Rebin(50);
  TH1D* mT_Stage1_TauScaleDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_TauScaleDown_ST_tW_top->Scale(kfact_ST_tW_top);
  // mT_Stage1_TauScaleDown_ST_tW_top->Rebin(50);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_JetEnUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_JetEnDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_JetResUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_JetResDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_JetResDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_MuonEnUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_MuonEnDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_ElectronEnUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_ElectronEnDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_TauEnUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_TauEnDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_PhotonEnUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_PhotonEnDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_top->Scale(kfact_ST_tW_top);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_top = (TH1D*)file_ST_tW_top->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_top->Scale(wt_ST_tW_top);
  mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_top->Scale(kfact_ST_tW_top);
  //

  TH1D* total_ST = (TH1D*)mT_Stage1_ST_tchannel_antitop->Clone(); 
  total_ST->Add(mT_Stage1_ST_tchannel_top);
  total_ST->Add(mT_Stage1_ST_tW_antitop);
  total_ST->Add(mT_Stage1_ST_tW_top);
  total_ST->SetFillColorAlpha(kCyan,0.5);
  total_ST->SetLineColor(kBlack);
  total_ST->Rebin(50);

  //file_WJetsToLNu_HT100To200
  TH1D* h1_evt_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT100To200 = h1_evt_WJetsToLNu_HT100To200->GetEntries(); //Integral();                                                                 
  double wt_WJetsToLNu_HT100To200 = (xs_WJetsToLNu_HT100To200*lumi)/evt_WJetsToLNu_HT100To200 ;
  TH1D* mT_Stage1_WJetsToLNu_HT100To200  = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT100To200 = (TH1D*)file_WJetsToLNu_HT100To200->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT100To200->Scale(wt_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT100To200->Scale(kfact_WJetsToLNu_HT100To200);
  //

  //file_WJetsToLNu_HT200To400
  TH1D* h1_evt_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT200To400 = h1_evt_WJetsToLNu_HT200To400->GetEntries(); //Integral();                                                      
  double wt_WJetsToLNu_HT200To400 = (xs_WJetsToLNu_HT200To400*lumi)/evt_WJetsToLNu_HT200To400 ;
  TH1D* mT_Stage1_WJetsToLNu_HT200To400  = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT200To400 = (TH1D*)file_WJetsToLNu_HT200To400->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT200To400->Scale(wt_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT200To400->Scale(kfact_WJetsToLNu_HT200To400);
  //
  //file_WJetsToLNu_HT400To600
  TH1D* h1_evt_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT400To600 = h1_evt_WJetsToLNu_HT400To600->GetEntries(); //Integral();                                                      
  double wt_WJetsToLNu_HT400To600 = (xs_WJetsToLNu_HT400To600*lumi)/evt_WJetsToLNu_HT400To600 ;
  TH1D* mT_Stage1_WJetsToLNu_HT400To600  = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT400To600 = (TH1D*)file_WJetsToLNu_HT400To600->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT400To600->Scale(wt_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT400To600->Scale(kfact_WJetsToLNu_HT400To600);
  //

  //file_WJetsToLNu_HT600To800
  TH1D* h1_evt_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT600To800 = h1_evt_WJetsToLNu_HT600To800->GetEntries(); //Integral();                                                      
  double wt_WJetsToLNu_HT600To800 = (xs_WJetsToLNu_HT600To800*lumi)/evt_WJetsToLNu_HT600To800 ;
  TH1D* mT_Stage1_WJetsToLNu_HT600To800  = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT600To800 = (TH1D*)file_WJetsToLNu_HT600To800->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT600To800->Scale(wt_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT600To800->Scale(kfact_WJetsToLNu_HT600To800);
  //
  //file_WJetsToLNu_HT800To1200
  TH1D* h1_evt_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT800To1200 = h1_evt_WJetsToLNu_HT800To1200->GetEntries(); //Integral();                                                    
  double wt_WJetsToLNu_HT800To1200 = (xs_WJetsToLNu_HT800To1200*lumi)/evt_WJetsToLNu_HT800To1200 ;
  TH1D* mT_Stage1_WJetsToLNu_HT800To1200  = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT800To1200 = (TH1D*)file_WJetsToLNu_HT800To1200->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT800To1200->Scale(wt_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT800To1200->Scale(kfact_WJetsToLNu_HT800To1200);
  //

  //file_WJetsToLNu_HT1200To2500
  TH1D* h1_evt_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT1200To2500 = h1_evt_WJetsToLNu_HT1200To2500->GetEntries(); //Integral();                                                  
  double wt_WJetsToLNu_HT1200To2500 = (xs_WJetsToLNu_HT1200To2500*lumi)/evt_WJetsToLNu_HT1200To2500 ;
  TH1D* mT_Stage1_WJetsToLNu_HT1200To2500  = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT1200To2500 = (TH1D*)file_WJetsToLNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT1200To2500->Scale(wt_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT1200To2500->Scale(kfact_WJetsToLNu_HT1200To2500);
  //

  //file_WJetsToLNu_HT2500ToInf
  TH1D* h1_evt_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/eventCount");
  unsigned long long evt_WJetsToLNu_HT2500ToInf = h1_evt_WJetsToLNu_HT2500ToInf->GetEntries(); //Integral();                                                    
  double wt_WJetsToLNu_HT2500ToInf = (xs_WJetsToLNu_HT2500ToInf*lumi)/evt_WJetsToLNu_HT2500ToInf ;
  TH1D* mT_Stage1_WJetsToLNu_HT2500ToInf  = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1");
  mT_Stage1_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_TauScaleUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_TauScaleDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_TauScaleDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT2500ToInf = (TH1D*)file_WJetsToLNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT2500ToInf->Scale(wt_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT2500ToInf->Scale(kfact_WJetsToLNu_HT2500ToInf);
  //

  TH1D* total_WJets = (TH1D*)mT_Stage1_WJetsToLNu_HT100To200->Clone();
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT200To400);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT400To600);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT600To800);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT800To1200);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT1200To2500);
  total_WJets->Add(mT_Stage1_WJetsToLNu_HT2500ToInf);
  total_WJets->SetFillColorAlpha(kGreen-8,0.5);
  total_WJets->SetLineColor(kBlack);
  total_WJets->Rebin(50);

  //file_WW
  TH1D* h1_evt_WW = (TH1D*)file_WW->Get("demo/eventCount");
  unsigned long long evt_WW = h1_evt_WW->GetEntries(); //Integral();                                                                         
  double wt_WW = (xs_WW*lumi)/evt_WW ;
  TH1D* mT_Stage1_WW  = (TH1D*)file_WW->Get("demo/mT_Stage1");
  mT_Stage1_WW->Scale(wt_WW);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WW->Scale(wt_WW);
  mT_Stage1_TauScaleUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_TauScaleDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WW->Scale(wt_WW);
  mT_Stage1_TauScaleDown_WW->Scale(kfact_WW);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_JetEnUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_JetEnDown_WW->Scale(kfact_WW);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_JetResUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_JetResDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_JetResDown_WW->Scale(kfact_WW);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_MuonEnUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_MuonEnDown_WW->Scale(kfact_WW);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_ElectronEnUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_ElectronEnDown_WW->Scale(kfact_WW);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_TauEnUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_TauEnDown_WW->Scale(kfact_WW);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_PhotonEnUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_PhotonEnDown_WW->Scale(kfact_WW);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WW->Scale(wt_WW);
  mT_Stage1_metUncert_UnclusteredEnUp_WW->Scale(kfact_WW);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WW = (TH1D*)file_WW->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WW->Scale(wt_WW);
  mT_Stage1_metUncert_UnclusteredEnDown_WW->Scale(kfact_WW);
  //

  //file_WZ
  TH1D* h1_evt_WZ = (TH1D*)file_WZ->Get("demo/eventCount");
  unsigned long long evt_WZ = h1_evt_WZ->GetEntries(); //Integral();                                                                         
  double wt_WZ = (xs_WZ*lumi)/evt_WZ ;
  TH1D* mT_Stage1_WZ  = (TH1D*)file_WZ->Get("demo/mT_Stage1");
  mT_Stage1_WZ->Scale(wt_WZ);
  mT_Stage1_WZ->Scale(kfact_WZ);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_WZ->Scale(wt_WZ);
  mT_Stage1_TauScaleUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_TauScaleDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_WZ->Scale(wt_WZ);
  mT_Stage1_TauScaleDown_WZ->Scale(kfact_WZ);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_JetEnUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_JetEnDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_JetEnDown_WZ->Scale(kfact_WZ);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_JetResUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_JetResDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_JetResDown_WZ->Scale(kfact_WZ);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_MuonEnUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_MuonEnDown_WZ->Scale(kfact_WZ);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_ElectronEnUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_ElectronEnDown_WZ->Scale(kfact_WZ);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_TauEnUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_TauEnDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_TauEnDown_WZ->Scale(kfact_WZ);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_PhotonEnUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_PhotonEnDown_WZ->Scale(kfact_WZ);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_UnclusteredEnUp_WZ->Scale(kfact_WZ);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_WZ = (TH1D*)file_WZ->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_WZ->Scale(wt_WZ);
  mT_Stage1_metUncert_UnclusteredEnDown_WZ->Scale(kfact_WZ);
  //

  //file_ZZ
  TH1D* h1_evt_ZZ = (TH1D*)file_ZZ->Get("demo/eventCount");
  unsigned long long evt_ZZ = h1_evt_ZZ->GetEntries(); //Integral();                                                                         
  double wt_ZZ = (xs_ZZ*lumi)/evt_ZZ ;
  TH1D* mT_Stage1_ZZ  = (TH1D*)file_ZZ->Get("demo/mT_Stage1");
  mT_Stage1_ZZ->Scale(wt_ZZ);
  mT_Stage1_ZZ->Scale(kfact_ZZ);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_TauScaleUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_TauScaleDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_TauScaleDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_JetEnUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_JetEnDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_JetResUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_JetResDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_MuonEnUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_MuonEnDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_ElectronEnUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_ElectronEnDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_TauEnUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_TauEnDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_PhotonEnUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_PhotonEnDown_ZZ->Scale(kfact_ZZ);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_UnclusteredEnUp_ZZ->Scale(kfact_ZZ);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZZ = (TH1D*)file_ZZ->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZZ->Scale(wt_ZZ);
  mT_Stage1_metUncert_UnclusteredEnDown_ZZ->Scale(kfact_ZZ);
  //

  TH1D* total_diboson = (TH1D*)mT_Stage1_WW->Clone();
  total_diboson->Add(mT_Stage1_WZ);
  total_diboson->Add(mT_Stage1_ZZ);
  total_diboson->SetFillColorAlpha(kOrange+2,0.5);
  total_diboson->SetLineColor(kBlack);
  total_diboson->Rebin(50);

  //file_QCD_HT200to300
  TH1D* h1_evt_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/eventCount");
  unsigned long long evt_QCD_HT200to300 = h1_evt_QCD_HT200to300->GetEntries(); //Integral();                                                                 
  double wt_QCD_HT200to300 = (xs_QCD_HT200to300*lumi)/evt_QCD_HT200to300 ;
  TH1D* mT_Stage1_QCD_HT200to300  = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT200to300->Scale(wt_QCD_HT200to300);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_TauScaleUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_TauScaleDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_JetEnUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_JetEnDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_JetResUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_JetResDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_TauEnUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_TauEnDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT200to300->Scale(kfact_QCD_HT200to300);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT200to300 = (TH1D*)file_QCD_HT200to300->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT200to300->Scale(wt_QCD_HT200to300);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT200to300->Scale(kfact_QCD_HT200to300);
  //

  //file_QCD_HT300to500
  TH1D* h1_evt_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/eventCount");
  unsigned long long evt_QCD_HT300to500 = h1_evt_QCD_HT300to500->GetEntries(); //Integral();                                                                     
  double wt_QCD_HT300to500 = (xs_QCD_HT300to500*lumi)/evt_QCD_HT300to500 ;
  TH1D* mT_Stage1_QCD_HT300to500  = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT300to500->Scale(wt_QCD_HT300to500);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_TauScaleUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_TauScaleDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_JetEnUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_JetEnDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_JetResUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_JetResDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_TauEnUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_TauEnDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT300to500->Scale(kfact_QCD_HT300to500);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT300to500 = (TH1D*)file_QCD_HT300to500->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT300to500->Scale(wt_QCD_HT300to500);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT300to500->Scale(kfact_QCD_HT300to500);
  //

  //file_QCD_HT500to700
  TH1D* h1_evt_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/eventCount");
  unsigned long long evt_QCD_HT500to700 = h1_evt_QCD_HT500to700->GetEntries(); //Integral();                                                                
  double wt_QCD_HT500to700 = (xs_QCD_HT500to700*lumi)/evt_QCD_HT500to700 ;
  TH1D* mT_Stage1_QCD_HT500to700  = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT500to700->Scale(wt_QCD_HT500to700);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_TauScaleUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_TauScaleDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_JetEnUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_JetEnDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_JetResUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_JetResDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_TauEnUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_TauEnDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT500to700->Scale(kfact_QCD_HT500to700);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT500to700 = (TH1D*)file_QCD_HT500to700->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT500to700->Scale(wt_QCD_HT500to700);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT500to700->Scale(kfact_QCD_HT500to700);
  //

  //file_QCD_HT700to1000
  TH1D* h1_evt_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/eventCount");
  unsigned long long evt_QCD_HT700to1000 = h1_evt_QCD_HT700to1000->GetEntries(); //Integral();                                                                
  double wt_QCD_HT700to1000 = (xs_QCD_HT700to1000*lumi)/evt_QCD_HT700to1000 ;
  TH1D* mT_Stage1_QCD_HT700to1000  = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_TauScaleUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_TauScaleDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_JetEnUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_JetEnDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_JetResUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_JetResDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_TauEnUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_TauEnDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT700to1000 = (TH1D*)file_QCD_HT700to1000->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT700to1000->Scale(wt_QCD_HT700to1000);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT700to1000->Scale(kfact_QCD_HT700to1000);
  //

  //file_QCD_HT1000to1500
  TH1D* h1_evt_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/eventCount");
  unsigned long long evt_QCD_HT1000to1500 = h1_evt_QCD_HT1000to1500->GetEntries(); //Integral();                                                                
  double wt_QCD_HT1000to1500 = (xs_QCD_HT1000to1500*lumi)/evt_QCD_HT1000to1500 ;
  TH1D* mT_Stage1_QCD_HT1000to1500  = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_TauScaleUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_TauScaleDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetEnUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetEnDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetResUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetResDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_TauEnUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_TauEnDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1000to1500 = (TH1D*)file_QCD_HT1000to1500->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1000to1500->Scale(wt_QCD_HT1000to1500);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1000to1500->Scale(kfact_QCD_HT1000to1500);
  //

  //file_QCD_HT1500to2000
  TH1D* h1_evt_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/eventCount");
  unsigned long long evt_QCD_HT1500to2000 = h1_evt_QCD_HT1500to2000->GetEntries(); //Integral();                                                                
  double wt_QCD_HT1500to2000 = (xs_QCD_HT1500to2000*lumi)/evt_QCD_HT1500to2000 ;
  TH1D* mT_Stage1_QCD_HT1500to2000  = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_TauScaleUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_TauScaleDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetEnUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetEnDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetResUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetResDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_TauEnUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_TauEnDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1500to2000 = (TH1D*)file_QCD_HT1500to2000->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1500to2000->Scale(wt_QCD_HT1500to2000);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1500to2000->Scale(kfact_QCD_HT1500to2000);
  //

  //file_QCD_HT2000toInf
  TH1D* h1_evt_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/eventCount");
  unsigned long long evt_QCD_HT2000toInf = h1_evt_QCD_HT2000toInf->GetEntries(); //Integral();                                                                  
  double wt_QCD_HT2000toInf = (xs_QCD_HT2000toInf*lumi)/evt_QCD_HT2000toInf ;
  TH1D* mT_Stage1_QCD_HT2000toInf  = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1");
  mT_Stage1_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
 //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_TauScaleUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_TauScaleDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_TauScaleDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetEnUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_JetEnDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetEnDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetResUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_JetResDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetResDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_MuonEnUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_MuonEnDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_ElectronEnUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_ElectronEnDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_TauEnUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_TauEnDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_TauEnDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_PhotonEnUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_PhotonEnDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT2000toInf = (TH1D*)file_QCD_HT2000toInf->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT2000toInf->Scale(wt_QCD_HT2000toInf);
  mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT2000toInf->Scale(kfact_QCD_HT2000toInf);
  //

  TH1D* total_QCD = (TH1D*)mT_Stage1_QCD_HT200to300->Clone();
  total_QCD->Add(mT_Stage1_QCD_HT300to500);
  total_QCD->Add(mT_Stage1_QCD_HT500to700);
  total_QCD->Add(mT_Stage1_QCD_HT700to1000);
  total_QCD->Add(mT_Stage1_QCD_HT1000to1500);
  total_QCD->Add(mT_Stage1_QCD_HT1500to2000);
  total_QCD->Add(mT_Stage1_QCD_HT2000toInf);
  total_QCD->SetFillColorAlpha(kPink+1,0.5);
  total_QCD->SetLineColor(kBlack);
  total_QCD->Rebin(50);

  //file_ZJetsToNuNu_HT100To200
  TH1D* h1_evt_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT100To200 = h1_evt_ZJetsToNuNu_HT100To200->GetEntries(); //Integral();                                                    
  double wt_ZJetsToNuNu_HT100To200 = (xs_ZJetsToNuNu_HT100To200*lumi)/evt_ZJetsToNuNu_HT100To200 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT100To200  = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT100To200 = (TH1D*)file_ZJetsToNuNu_HT100To200->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT100To200->Scale(wt_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT100To200->Scale(kfact_ZJetsToNuNu_HT100To200);
  //

  //file_ZJetsToNuNu_HT200To400
  TH1D* h1_evt_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT200To400 = h1_evt_ZJetsToNuNu_HT200To400->GetEntries(); //Integral();                                                    
  double wt_ZJetsToNuNu_HT200To400 = (xs_ZJetsToNuNu_HT200To400*lumi)/evt_ZJetsToNuNu_HT200To400 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT200To400  = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT200To400 = (TH1D*)file_ZJetsToNuNu_HT200To400->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT200To400->Scale(wt_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT200To400->Scale(kfact_ZJetsToNuNu_HT200To400);
  //

  //file_ZJetsToNuNu_HT400To600
  TH1D* h1_evt_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT400To600 = h1_evt_ZJetsToNuNu_HT400To600->GetEntries(); //Integral();                                                    
  double wt_ZJetsToNuNu_HT400To600 = (xs_ZJetsToNuNu_HT400To600*lumi)/evt_ZJetsToNuNu_HT400To600 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT400To600  = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT400To600 = (TH1D*)file_ZJetsToNuNu_HT400To600->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT400To600->Scale(wt_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT400To600->Scale(kfact_ZJetsToNuNu_HT400To600);
  //

  //file_ZJetsToNuNu_HT600To800
  TH1D* h1_evt_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT600To800 = h1_evt_ZJetsToNuNu_HT600To800->GetEntries(); //Integral();                                                    
  double wt_ZJetsToNuNu_HT600To800 = (xs_ZJetsToNuNu_HT600To800*lumi)/evt_ZJetsToNuNu_HT600To800 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT600To800  = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT600To800 = (TH1D*)file_ZJetsToNuNu_HT600To800->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT600To800->Scale(wt_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT600To800->Scale(kfact_ZJetsToNuNu_HT600To800);
  //

  //file_ZJetsToNuNu_HT800To1200
  TH1D* h1_evt_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT800To1200 = h1_evt_ZJetsToNuNu_HT800To1200->GetEntries(); //Integral();                                                  
  double wt_ZJetsToNuNu_HT800To1200 = (xs_ZJetsToNuNu_HT800To1200*lumi)/evt_ZJetsToNuNu_HT800To1200 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT800To1200  = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT800To1200 = (TH1D*)file_ZJetsToNuNu_HT800To1200->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT800To1200->Scale(wt_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT800To1200->Scale(kfact_ZJetsToNuNu_HT800To1200);
  //

  //file_ZJetsToNuNu_HT1200To2500
  TH1D* h1_evt_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT1200To2500 = h1_evt_ZJetsToNuNu_HT1200To2500->GetEntries(); //Integral();                                                
  double wt_ZJetsToNuNu_HT1200To2500 = (xs_ZJetsToNuNu_HT1200To2500*lumi)/evt_ZJetsToNuNu_HT1200To2500 ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT1200To2500  = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT1200To2500 = (TH1D*)file_ZJetsToNuNu_HT1200To2500->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT1200To2500->Scale(wt_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT1200To2500->Scale(kfact_ZJetsToNuNu_HT1200To2500);
  //

  //file_ZJetsToNuNu_HT2500ToInf
  TH1D* h1_evt_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/eventCount");
  unsigned long long evt_ZJetsToNuNu_HT2500ToInf = h1_evt_ZJetsToNuNu_HT2500ToInf->GetEntries(); //Integral();                                                  
  double wt_ZJetsToNuNu_HT2500ToInf = (xs_ZJetsToNuNu_HT2500ToInf*lumi)/evt_ZJetsToNuNu_HT2500ToInf ;
  TH1D* mT_Stage1_ZJetsToNuNu_HT2500ToInf  = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1");
  mT_Stage1_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  //-----syst-----//
  //-TauScale
  TH1D* mT_Stage1_TauScaleUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_TauScaleUp");
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_TauScaleUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_TauScaleDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_TauScaleDown");
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_TauScaleDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_JetEn
  TH1D* mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetEnUp");
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetEnDown");
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_JetRes
  TH1D* mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetResUp");
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_JetResDown");
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_MuonEn
  TH1D* mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_MuonEnUp");
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_MuonEnDown");
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_ElectronEn
  TH1D* mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_ElectronEnUp");
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_ElectronEnDown");
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_TauEn
  TH1D* mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_TauEnUp");
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_TauEnDown");
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_PhotonEn
  TH1D* mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_PhotonEnUp");
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_PhotonEnDown");
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //-metUncert_UnclusteredEn
  TH1D* mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_UnclusteredEnUp");
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);  
  TH1D* mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT2500ToInf = (TH1D*)file_ZJetsToNuNu_HT2500ToInf->Get("demo/mT_Stage1_metUncert_UnclusteredEnDown");
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT2500ToInf->Scale(wt_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT2500ToInf->Scale(kfact_ZJetsToNuNu_HT2500ToInf);
  //

  TH1D* total_ZJets = (TH1D*)mT_Stage1_ZJetsToNuNu_HT100To200->Clone();
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT200To400);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT400To600);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT600To800);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT800To1200);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT1200To2500);
  total_ZJets->Add(mT_Stage1_ZJetsToNuNu_HT2500ToInf);
  total_ZJets->SetFillColorAlpha(kYellow-9,0.5);
  total_ZJets->SetLineColor(kBlack);
  total_ZJets->Rebin(50);

  //--Data--//
  TH1D* mT_Stage1_Run2016D  = (TH1D*)file_Tau_Run2016D->Get("demo/mT_Stage1");
  // Poisson error //
  //mT_Stage1_Run2016D->Sumw2(kFALSE);
  //mT_Stage1_Run2016D->SetBinErrorOption(TH1::kPoisson);
  mT_Stage1_Run2016D->SetMarkerStyle(20);
  mT_Stage1_Run2016D->SetMarkerColor(kBlack);
  mT_Stage1_Run2016D->SetLineColor(kBlack);
  mT_Stage1_Run2016D->Rebin(50);

  //--Signal--//
  TH1D* h1_evt_Wprime_M1000 = (TH1D*)file_Wprime_M1000->Get("demo/eventCount");
  unsigned long long evt_Wprime_M1000 = h1_evt_Wprime_M1000->GetEntries(); //Integral();                                                                          
  //std::cout << "evt_Wprime_M1000 = " << evt_Wprime_M1000 << std::endl;
  double wt_Wprime_M1000 = (xs_Wprime_M1000*lumi)/evt_Wprime_M1000 ;
  TH1D* mT_Stage1_Wprime_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/mT_Stage1");
  mT_Stage1_Wprime_M1000->Scale(wt_Wprime_M1000);
  //  mT_Stage1_Wprime_M1000->SetFillColorAlpha(kGreen-7,0.5);
  mT_Stage1_Wprime_M1000->SetLineColor(kMagenta);
  mT_Stage1_Wprime_M1000->SetLineWidth(2);
  mT_Stage1_Wprime_M1000->SetLineStyle(5);
  mT_Stage1_Wprime_M1000->Rebin(50);


  /// SYST TOTAL ///
  //TauScaleUp
  TH1F* mT_Stage1_TauScaleUp_allBkg =  (TH1F*)mT_Stage1_TauScaleUp_DYJetsToLL_M50->Clone();
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_TT);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT100To200);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT200To400);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT400To600);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT600To800);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT800To1200);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ST_tchannel_antitop);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ST_tchannel_top);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ST_tW_antitop);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ST_tW_top);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WW);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_WZ);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZZ);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT200to300);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT300to500);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT500to700);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT700to1000);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT1000to1500);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT1500to2000);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_QCD_HT2000toInf);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_TauScaleUp_allBkg->Add(mT_Stage1_TauScaleUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_TauScaleUp_allBkg->Rebin(50);
  //  mT_Stage1_TauScaleUp_allBkg->Smooth(3);

  //TauScaleDown
  TH1F* mT_Stage1_TauScaleDown_allBkg =  (TH1F*)mT_Stage1_TauScaleDown_DYJetsToLL_M50->Clone();
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_TT);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT100To200);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT200To400);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT400To600);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT600To800);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT800To1200);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ST_tchannel_antitop);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ST_tchannel_top);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ST_tW_antitop);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ST_tW_top);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WW);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_WZ);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZZ);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT200to300);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT300to500);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT500to700);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT700to1000);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT1000to1500);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT1500to2000);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_QCD_HT2000toInf);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_TauScaleDown_allBkg->Add(mT_Stage1_TauScaleDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_TauScaleDown_allBkg->Rebin(50);
  // mT_Stage1_TauScaleDown_allBkg->Smooth(3);

  //metUncert_JetEnUp
  TH1F* mT_Stage1_metUncert_JetEnUp_allBkg =  (TH1F*)mT_Stage1_metUncert_JetEnUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_TT);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ST_tchannel_top);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ST_tW_antitop);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ST_tW_top);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WW);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_WZ);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZZ);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT200to300);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT300to500);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT500to700);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT700to1000);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnUp_allBkg->Add(mT_Stage1_metUncert_JetEnUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnUp_allBkg->Rebin(50);
  // mT_Stage1_metUncert_JetEnUp_allBkg->Smooth(3);

  //metUncert_JetEnDown
  TH1F* mT_Stage1_metUncert_JetEnDown_allBkg =  (TH1F*)mT_Stage1_metUncert_JetEnDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_TT);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ST_tchannel_top);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ST_tW_antitop);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ST_tW_top);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WW);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_WZ);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZZ);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT200to300);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT300to500);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT500to700);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT700to1000);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetEnDown_allBkg->Add(mT_Stage1_metUncert_JetEnDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetEnDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_JetEnDown_allBkg->Smooth(3);

  //metUncert_JetResUp
  TH1F* mT_Stage1_metUncert_JetResUp_allBkg =  (TH1F*)mT_Stage1_metUncert_JetResUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_TT);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ST_tchannel_top);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ST_tW_antitop);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ST_tW_top);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WW);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_WZ);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZZ);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT200to300);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT300to500);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT500to700);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT700to1000);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetResUp_allBkg->Add(mT_Stage1_metUncert_JetResUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResUp_allBkg->Rebin(50);
  //  mT_Stage1_metUncert_JetResUp_allBkg->Smooth(3);

  //metUncert_JetResDown
  TH1F* mT_Stage1_metUncert_JetResDown_allBkg =  (TH1F*)mT_Stage1_metUncert_JetResDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_TT);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ST_tchannel_top);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ST_tW_antitop);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ST_tW_top);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WW);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_WZ);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZZ);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT200to300);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT300to500);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT500to700);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT700to1000);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_JetResDown_allBkg->Add(mT_Stage1_metUncert_JetResDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_JetResDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_JetResDown_allBkg->Smooth(3);

  //metUncert_MuonEnUp
  TH1F* mT_Stage1_metUncert_MuonEnUp_allBkg =  (TH1F*)mT_Stage1_metUncert_MuonEnUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_TT);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ST_tchannel_top);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ST_tW_antitop);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ST_tW_top);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WW);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_WZ);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZZ);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT200to300);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT300to500);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT500to700);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT700to1000);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Add(mT_Stage1_metUncert_MuonEnUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnUp_allBkg->Rebin(50);
  // mT_Stage1_metUncert_MuonEnUp_allBkg->Smooth(3);

  //metUncert_MuonEnDown
  TH1F* mT_Stage1_metUncert_MuonEnDown_allBkg =  (TH1F*)mT_Stage1_metUncert_MuonEnDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_TT);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ST_tchannel_top);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ST_tW_antitop);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ST_tW_top);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WW);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_WZ);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZZ);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT200to300);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT300to500);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT500to700);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT700to1000);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Add(mT_Stage1_metUncert_MuonEnDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_MuonEnDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_MuonEnDown_allBkg->Smooth(3);

  //metUncert_ElectronEnUp
  TH1F* mT_Stage1_metUncert_ElectronEnUp_allBkg =  (TH1F*)mT_Stage1_metUncert_ElectronEnUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_TT);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ST_tchannel_top);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ST_tW_antitop);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ST_tW_top);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WW);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_WZ);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZZ);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT200to300);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT300to500);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT500to700);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT700to1000);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Add(mT_Stage1_metUncert_ElectronEnUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnUp_allBkg->Rebin(50);
  // mT_Stage1_metUncert_ElectronEnUp_allBkg->Smooth(3);

  //metUncert_ElectronEnDown
  TH1F* mT_Stage1_metUncert_ElectronEnDown_allBkg =  (TH1F*)mT_Stage1_metUncert_ElectronEnDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_TT);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ST_tchannel_top);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ST_tW_antitop);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ST_tW_top);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WW);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_WZ);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZZ);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT200to300);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT300to500);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT500to700);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT700to1000);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Add(mT_Stage1_metUncert_ElectronEnDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_ElectronEnDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_ElectronEnDown_allBkg->Smooth(3);

  //metUncert_TauEnUp
  TH1F* mT_Stage1_metUncert_TauEnUp_allBkg =  (TH1F*)mT_Stage1_metUncert_TauEnUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_TT);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ST_tchannel_top);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ST_tW_antitop);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ST_tW_top);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WW);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_WZ);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZZ);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT200to300);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT300to500);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT500to700);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT700to1000);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnUp_allBkg->Add(mT_Stage1_metUncert_TauEnUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnUp_allBkg->Rebin(50);
  // mT_Stage1_metUncert_TauEnUp_allBkg->Smooth(3);

  //metUncert_TauEnDown
  TH1F* mT_Stage1_metUncert_TauEnDown_allBkg =  (TH1F*)mT_Stage1_metUncert_TauEnDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_TT);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ST_tchannel_top);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ST_tW_antitop);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ST_tW_top);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WW);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_WZ);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZZ);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT200to300);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT300to500);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT500to700);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT700to1000);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_TauEnDown_allBkg->Add(mT_Stage1_metUncert_TauEnDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_TauEnDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_TauEnDown_allBkg->Smooth(3);

  //metUncert_PhotonEnUp
  TH1F* mT_Stage1_metUncert_PhotonEnUp_allBkg =  (TH1F*)mT_Stage1_metUncert_PhotonEnUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_TT);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ST_tchannel_top);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ST_tW_antitop);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ST_tW_top);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WW);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_WZ);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZZ);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT200to300);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT300to500);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT500to700);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT700to1000);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Add(mT_Stage1_metUncert_PhotonEnUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnUp_allBkg->Rebin(50);
  // mT_Stage1_metUncert_PhotonEnUp_allBkg->Smooth(3);

  //metUncert_PhotonEnDown
  TH1F* mT_Stage1_metUncert_PhotonEnDown_allBkg =  (TH1F*)mT_Stage1_metUncert_PhotonEnDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_TT);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ST_tchannel_top);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ST_tW_antitop);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ST_tW_top);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WW);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_WZ);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZZ);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT200to300);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT300to500);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT500to700);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT700to1000);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Add(mT_Stage1_metUncert_PhotonEnDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_PhotonEnDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_PhotonEnDown_allBkg->Smooth(3);

  //metUncert_UnclusteredEnUp
  TH1F* mT_Stage1_metUncert_UnclusteredEnUp_allBkg =  (TH1F*)mT_Stage1_metUncert_UnclusteredEnUp_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_TT);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_antitop);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ST_tchannel_top);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_antitop);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ST_tW_top);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WW);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_WZ);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZZ);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT200to300);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT300to500);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT500to700);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT700to1000);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1000to1500);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT1500to2000);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_QCD_HT2000toInf);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnUp_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Rebin(50);
  // mT_Stage1_metUncert_UnclusteredEnUp_allBkg->Smooth(3);

  //metUncert_UnclusteredEnDown
  TH1F* mT_Stage1_metUncert_UnclusteredEnDown_allBkg =  (TH1F*)mT_Stage1_metUncert_UnclusteredEnDown_DYJetsToLL_M50->Clone();
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_TT);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WJetsToLNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_antitop);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ST_tchannel_top);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_antitop);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ST_tW_top);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WW);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_WZ);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZZ);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT200to300);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT300to500);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT500to700);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT700to1000);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1000to1500);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT1500to2000);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_QCD_HT2000toInf);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT100To200);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT200To400);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT400To600);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT600To800);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT800To1200);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT1200To2500);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Add(mT_Stage1_metUncert_UnclusteredEnDown_ZJetsToNuNu_HT2500ToInf);
  mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Rebin(50);
  // mT_Stage1_metUncert_UnclusteredEnDown_allBkg->Smooth(3);

  TH1F* total =  (TH1F*)total_WJets->Clone(); 
  total->Add(mT_Stage1_TT);
  total->Add(mT_Stage1_DYJetsToLL_M50);
  total->Add(total_ST);
  total->Add(total_diboson);
  total->Add(total_QCD);
  total->Add(total_ZJets);

  //  TH1F* total_copy = (TH1F*)total->Clone();
  // total_copy->Smooth(3);
  int nbin=total->GetNbinsX();

  for (int nb=1; nb<nbin+1; nb++) {
    double central=total->GetBinContent(nb);
    if (nb>0) std::cout << "nb=" << nb << " central=" << total->GetBinContent(nb) << std::endl;
    //- Tau Scale
    double TauScaleUp=mT_Stage1_TauScaleUp_allBkg->GetBinContent(nb);
    double delta_TauScaleUp=fabs(TauScaleUp-central) ;
    double TauScaleDown=mT_Stage1_TauScaleDown_allBkg->GetBinContent(nb);
    double delta_TauScaleDown=fabs(TauScaleDown-central) ;
    double delta_TauScale = std::max(delta_TauScaleUp,delta_TauScaleDown);
    if (nb>0) std::cout << "delta_TauScale=" << delta_TauScale << std::endl;
    //- 
    double metUncert_JetEnUp=mT_Stage1_metUncert_JetEnUp_allBkg->GetBinContent(nb);
    double delta_metUncert_JetEnUp=fabs(metUncert_JetEnUp-central) ;
    double metUncert_JetEnDown=mT_Stage1_metUncert_JetEnDown_allBkg->GetBinContent(nb);
    double delta_metUncert_JetEnDown=fabs(metUncert_JetEnDown-central) ;
    double delta_metUncert_JetEn = std::max(delta_metUncert_JetEnUp,delta_metUncert_JetEnDown);
    if (nb>0) std::cout << "delta_metUncert_JetEn=" << delta_metUncert_JetEn << std::endl;
    //-
    double metUncert_JetResUp=mT_Stage1_metUncert_JetResUp_allBkg->GetBinContent(nb);
    double delta_metUncert_JetResUp=fabs(metUncert_JetResUp-central) ;
    double metUncert_JetResDown=mT_Stage1_metUncert_JetResDown_allBkg->GetBinContent(nb);
    double delta_metUncert_JetResDown=fabs(metUncert_JetResDown-central) ;
    double delta_metUncert_JetRes = std::max(delta_metUncert_JetResUp,delta_metUncert_JetResDown);
    if (nb>0) std::cout << "delta_metUncert_JetRes=" << delta_metUncert_JetRes << std::endl;
    //-
    double metUncert_MuonEnUp=mT_Stage1_metUncert_MuonEnUp_allBkg->GetBinContent(nb);
    double delta_metUncert_MuonEnUp=fabs(metUncert_MuonEnUp-central) ;
    double metUncert_MuonEnDown=mT_Stage1_metUncert_MuonEnDown_allBkg->GetBinContent(nb);
    double delta_metUncert_MuonEnDown=fabs(metUncert_MuonEnDown-central) ;
    double delta_metUncert_MuonEn = std::max(delta_metUncert_MuonEnUp,delta_metUncert_MuonEnDown);
    if (nb>0) std::cout << "delta_metUncert_MuonEn=" << delta_metUncert_MuonEn << std::endl;
    //-
    double metUncert_ElectronEnUp=mT_Stage1_metUncert_ElectronEnUp_allBkg->GetBinContent(nb);
    double delta_metUncert_ElectronEnUp=fabs(metUncert_ElectronEnUp-central) ;
    double metUncert_ElectronEnDown=mT_Stage1_metUncert_ElectronEnDown_allBkg->GetBinContent(nb);
    double delta_metUncert_ElectronEnDown=fabs(metUncert_ElectronEnDown-central) ;
    double delta_metUncert_ElectronEn = std::max(delta_metUncert_ElectronEnUp,delta_metUncert_ElectronEnDown);
    if (nb>0) std::cout << "delta_metUncert_ElectronEn=" << delta_metUncert_ElectronEn << std::endl;
    //-
    double metUncert_TauEnUp=mT_Stage1_metUncert_TauEnUp_allBkg->GetBinContent(nb);
    double delta_metUncert_TauEnUp=fabs(metUncert_TauEnUp-central) ;
    double metUncert_TauEnDown=mT_Stage1_metUncert_TauEnDown_allBkg->GetBinContent(nb);
    double delta_metUncert_TauEnDown=fabs(metUncert_TauEnDown-central) ;
    double delta_metUncert_TauEn = std::max(delta_metUncert_TauEnUp,delta_metUncert_TauEnDown);
    if (nb>0) std::cout << "delta_metUncert_TauEn=" << delta_metUncert_TauEn << std::endl;
    //-
    double metUncert_PhotonEnUp=mT_Stage1_metUncert_PhotonEnUp_allBkg->GetBinContent(nb);
    double delta_metUncert_PhotonEnUp=fabs(metUncert_PhotonEnUp-central) ;
    double metUncert_PhotonEnDown=mT_Stage1_metUncert_PhotonEnDown_allBkg->GetBinContent(nb);
    double delta_metUncert_PhotonEnDown=fabs(metUncert_PhotonEnDown-central) ;
    double delta_metUncert_PhotonEn = std::max(delta_metUncert_PhotonEnUp,delta_metUncert_PhotonEnDown);
    if (nb>0) std::cout << "delta_metUncert_PhotonEn=" << delta_metUncert_PhotonEn << std::endl; 
    //-
    double metUncert_UnclusteredEnUp=mT_Stage1_metUncert_UnclusteredEnUp_allBkg->GetBinContent(nb);
    double delta_metUncert_UnclusteredEnUp=fabs(metUncert_UnclusteredEnUp-central) ;
    double metUncert_UnclusteredEnDown=mT_Stage1_metUncert_UnclusteredEnDown_allBkg->GetBinContent(nb);
    double delta_metUncert_UnclusteredEnDown=fabs(metUncert_UnclusteredEnDown-central) ;
    double delta_metUncert_UnclusteredEn = std::max(delta_metUncert_UnclusteredEnUp,delta_metUncert_UnclusteredEnDown);
    if (nb>0)  std::cout << "delta_metUncert_UnclusteredEn=" << delta_metUncert_UnclusteredEn << std::endl; 
    //  
    double delta2 = (delta_TauScale*delta_TauScale)+(delta_metUncert_JetEn*delta_metUncert_JetEn)+(delta_metUncert_JetRes*delta_metUncert_JetRes)+(delta_metUncert_MuonEn*delta_metUncert_MuonEn)+(delta_metUncert_ElectronEn*delta_metUncert_ElectronEn)+(delta_metUncert_TauEn*delta_metUncert_TauEn)+(delta_metUncert_PhotonEn*delta_metUncert_PhotonEn)+(delta_metUncert_UnclusteredEn*delta_metUncert_UnclusteredEn);

    double delta = sqrt(delta2);
    if (central==0.0) delta=0.0;
    if (nb>0) std::cout << "delta=" << delta << std::endl;
    ///    std::cout << "bin-" << nb << " central=" << central  <<  " delta=" << delta << std::endl;

    total->SetBinError(nb,delta);

  }

  total->SetFillStyle(3004);                                                                                                                                     
  total->SetFillColor(kGray+2); 
  total->SetMarkerColor(0);

 
  //--Plotting Styles//
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  //////// Output File /////////
  TFile* outputFile = new TFile("Out_mT_Stage1.root","RECREATE");
  outputFile->cd();

  //--//
  THStack *hs = new THStack("hs","");
  // hs->Add(mT_Stage1_WJetsToLNu);
  hs->Add(total_WJets);
  hs->Add(mT_Stage1_TT);
  hs->Add(mT_Stage1_DYJetsToLL_M50);
  hs->Add(total_ST);
  hs->Add(total_diboson);
  hs->Add(total_QCD);
  hs->Add(total_ZJets);

  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  my_canvas->cd();
  //  hs->Draw();
  gPad->SetLogy();
  hs->Draw("HIST");                                                                                                                                        
  hs->SetMaximum(10000);
  hs->SetMinimum(0.001);
  hs->GetXaxis()->SetLimits(150, 1500);
  hs->GetXaxis()->SetTitle("M_{T}");
  hs->GetYaxis()->SetTitle("Events");

  total->Draw("SAME E2");
 


  mT_Stage1_Run2016D->Draw("SAME E0");
  mT_Stage1_Wprime_M1000->Draw("SAME HIST");
  //  hs->SetOption("HIST L");
  
  TLatex* CMS_text = new TLatex(0.20,0.90,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);
  CMS_text->Draw("same");
  TLatex* CMS_text_2 = new TLatex(0.20,0.85,"Preliminary");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);
  CMS_text_2->Draw("same");    

  TLatex* lumiText = new TLatex(0.95,0.975,"4.35 fb^{-1} (13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     

  TLegend *leg_example = new TLegend(0.75,0.60,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(total_WJets, "Wjets","f");
  leg_example->AddEntry(mT_Stage1_DYJetsToLL_M50, "DY","f");
  leg_example->AddEntry(mT_Stage1_TT, "t#bar{t}","f");
  //leg_example->AddEntry(mT_Stage1_WJetsToLNu, "Wjets","f");
  leg_example->AddEntry(total_ST, "Single Top", "f");
  leg_example->AddEntry(total_diboson, "Diboson", "f");
  leg_example->AddEntry(total_QCD, "QCD", "f");
  leg_example->AddEntry(total_ZJets, "Z#rightarrow#nu#nu", "f");
  leg_example->AddEntry(mT_Stage1_Wprime_M1000, "SSM W' 1 TeV", "l");
  leg_example->AddEntry(mT_Stage1_Run2016D, "Data", "pl" );
  leg_example->Draw("same");
  
  my_canvas->Write();
  my_canvas->Print("mT_Stage1.pdf");


  /*

  TCanvas* my_canvas2 = new TCanvas("canvas2","canvas2");
  my_canvas2->cd();
  gPad->SetLogy();
  total->SetMaximum(1000);
  total->SetMarkerStyle(20);
  total->Draw("E");
  my_canvas2->Write();

  TCanvas* ratio_c = new TCanvas("ratio","ratio_canvas",800,700);
  ratio_c->SetTopMargin(0.); 
  ratio_c->SetBottomMargin(0.); 
  ratio_c->Update();
  ratio_c->Divide(1, 2);
  ratio_c->cd(1);

  gPad->SetPad(.005, .30, .995, .995);
  TPad* pad1 = (TPad*)ratio_c->GetPad(1); 
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.05); 
  
  ratio_c->Update();
  gPad->SetLogy();
  
  hs->Draw("HIST");                                                                                                                                        
  hs->SetMaximum(10000);
  hs->SetMinimum(0.001);
  hs->GetXaxis()->SetLimits(150, 1500);
  hs->GetXaxis()->SetTitle("");
  // total->Draw("SAME E2");
  mT_Stage1_Run2016D->Draw("SAME E1");
  mT_Stage1_Wprime_M1000->Draw("SAME HIST");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  lumiText->Draw("same");
  leg_example->Draw("same");
  ratio_c->cd(2);

  gPad->SetPad(.005, .18, .995, .30); 
  gStyle->SetOptStat(false);
  ratio_c->Update();
  TPad* pad2 = (TPad*)ratio_c->GetPad(2);
  pad2->SetTopMargin(0.05); 
  pad2->SetBottomMargin(0.38); 
  pad2->SetGridx();
  pad2->SetGridy();

  TH1F* data_by_MC = (TH1F*)mT_Stage1_Run2016D->Clone();
  data_by_MC->Divide(total);
  data_by_MC->SetMarkerStyle(20);
  data_by_MC->Draw("E");
  data_by_MC->GetXaxis()->SetLimits(150, 1500);
  data_by_MC->GetXaxis()->SetTitle("M_{T}");
  data_by_MC->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  data_by_MC->GetYaxis()->SetLabelSize(0.16);
  data_by_MC->GetXaxis()->SetLabelSize(0.18);
  data_by_MC->GetYaxis()->SetTitleSize(0.20);
  data_by_MC->GetXaxis()->SetTitleSize(0.22);
  data_by_MC->GetYaxis()->SetTitleOffset(0.20);
  data_by_MC->GetXaxis()->SetTitleOffset(0.65);
  data_by_MC->SetTitle("");
  data_by_MC->SetMaximum(4);
  data_by_MC->SetMinimum(0);
  data_by_MC->GetYaxis()->SetNdivisions(5);
 
  ratio_c->Write();

  */

  return 0;

}
