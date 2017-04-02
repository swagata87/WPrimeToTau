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

int PlotSignal() {

  double lumi=35.865 ;  // B->5.882  // C->2.646   D->4.353 ;  // E->4.049 ; F->3.16 ;  G->7.554;  H->5.942  //--inv fb--//

  /// Signal ///
  TFile *file_Wprime_M1000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  double xs_Wprime_M1000= 3060; // --fb-- //

  TFile *file_Wprime_M1200 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_1200_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  double xs_Wprime_M1200= 1370; // --fb-- //

  TFile *file_Wprime_M1400 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M_1400_TuneCUETP8M1_13TeV_pythia8_tauola/results/hist.root");
  double xs_Wprime_M1400= 793; // --fb-- //


  //  TFile *file_Wprime_M2000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  //  double xs_Wprime_M2000= 122.0; // --fb-- //

  //  TFile *file_Wprime_M3000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  //  double xs_Wprime_M3000= 11.6; // --fb-- //

  //  TFile *file_Wprime_M4000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  // double xs_Wprime_M4000= 2.04; // --fb-- //

  // TFile *file_Wprime_M5000 = new TFile("../python/crab_projects_March3/crab_WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/results/hist.root");
  //  double xs_Wprime_M5000=0.408; // --fb-- //

  std::cout << "will do signal " << std::endl;

  //--Signal--//
  TH1D* h1_evt_Wprime_M1000 = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1000 = h1_evt_Wprime_M1000->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M1000 = (xs_Wprime_M1000*lumi)/evt_Wprime_M1000 ;
  TH1D* mT_Stage1_Wprime_M1000  = (TH1D*)file_Wprime_M1000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1000 : " << ( mT_Stage1_Wprime_M1000->GetEntries() / evt_Wprime_M1000 ) << std::endl;
  mT_Stage1_Wprime_M1000->Scale(wt_Wprime_M1000);
  mT_Stage1_Wprime_M1000->SetLineColor(kMagenta);
  mT_Stage1_Wprime_M1000->SetLineWidth(3);
  mT_Stage1_Wprime_M1000->Rebin(100);

  TH1D* h1_evt_Wprime_M1200 = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1200 = h1_evt_Wprime_M1200->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M1200 = (xs_Wprime_M1200*lumi)/evt_Wprime_M1200 ;
  TH1D* mT_Stage1_Wprime_M1200  = (TH1D*)file_Wprime_M1200->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1200 : " << ( mT_Stage1_Wprime_M1200->GetEntries() / evt_Wprime_M1200 ) << std::endl;
  mT_Stage1_Wprime_M1200->Scale(wt_Wprime_M1200);
  mT_Stage1_Wprime_M1200->SetLineColor(kMagenta+2);
  mT_Stage1_Wprime_M1200->SetLineWidth(3);
  mT_Stage1_Wprime_M1200->Rebin(100);

  TH1D* h1_evt_Wprime_M1400 = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M1400 = h1_evt_Wprime_M1400->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M1400 = (xs_Wprime_M1400*lumi)/evt_Wprime_M1400 ;
  TH1D* mT_Stage1_Wprime_M1400  = (TH1D*)file_Wprime_M1400->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M1400 : " << ( mT_Stage1_Wprime_M1400->GetEntries() / evt_Wprime_M1400 ) << std::endl;
  mT_Stage1_Wprime_M1400->Scale(wt_Wprime_M1400);
  mT_Stage1_Wprime_M1400->SetLineColor(kMagenta+4);
  mT_Stage1_Wprime_M1400->SetLineWidth(3);
  mT_Stage1_Wprime_M1400->Rebin(100);

  /*
  TH1D* h1_evt_Wprime_M2000 = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M2000 = h1_evt_Wprime_M2000->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M2000 = (xs_Wprime_M2000*lumi)/evt_Wprime_M2000 ;
  TH1D* mT_Stage1_Wprime_M2000  = (TH1D*)file_Wprime_M2000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M2000 : " << ( mT_Stage1_Wprime_M2000->GetEntries() / evt_Wprime_M2000 ) << std::endl;
  mT_Stage1_Wprime_M2000->Scale(wt_Wprime_M2000);
  mT_Stage1_Wprime_M2000->SetLineColor(kGreen);
  mT_Stage1_Wprime_M2000->SetLineWidth(3);
  mT_Stage1_Wprime_M2000->Rebin(100);
  */
  /*
  TH1D* h1_evt_Wprime_M3000 = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M3000 = h1_evt_Wprime_M3000->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M3000 = (xs_Wprime_M3000*lumi)/evt_Wprime_M3000 ;
  TH1D* mT_Stage1_Wprime_M3000  = (TH1D*)file_Wprime_M3000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M3000 : " << ( mT_Stage1_Wprime_M3000->GetEntries() / evt_Wprime_M3000 ) << std::endl;
  mT_Stage1_Wprime_M3000->Scale(wt_Wprime_M3000);
  mT_Stage1_Wprime_M3000->SetLineColor(kBlue);
  mT_Stage1_Wprime_M3000->SetLineWidth(3);
  mT_Stage1_Wprime_M3000->Rebin(100);

  TH1D* h1_evt_Wprime_M4000 = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M4000 = h1_evt_Wprime_M4000->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M4000 = (xs_Wprime_M4000*lumi)/evt_Wprime_M4000 ;
  TH1D* mT_Stage1_Wprime_M4000  = (TH1D*)file_Wprime_M4000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M4000 : " << ( mT_Stage1_Wprime_M4000->GetEntries() / evt_Wprime_M4000 ) << std::endl;
  mT_Stage1_Wprime_M4000->Scale(wt_Wprime_M4000);
  mT_Stage1_Wprime_M4000->SetLineColor(kRed);
  mT_Stage1_Wprime_M4000->SetLineWidth(3);
  mT_Stage1_Wprime_M4000->Rebin(100);

  TH1D* h1_evt_Wprime_M5000 = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/eventCount");
  unsigned long long evt_Wprime_M5000 = h1_evt_Wprime_M5000->GetEntries(); //Integral();                                                                          
  double wt_Wprime_M5000 = (xs_Wprime_M5000*lumi)/evt_Wprime_M5000 ;
  TH1D* mT_Stage1_Wprime_M5000  = (TH1D*)file_Wprime_M5000->Get("demo/histoDir/mT_Stage1");
  std::cout << "Sig Eff W' M5000 : " << ( mT_Stage1_Wprime_M5000->GetEntries() / evt_Wprime_M5000 ) << std::endl;
  mT_Stage1_Wprime_M5000->Scale(wt_Wprime_M5000);
  mT_Stage1_Wprime_M5000->SetLineColor(kOrange);
  mT_Stage1_Wprime_M5000->SetLineWidth(3);
  mT_Stage1_Wprime_M5000->Rebin(100);
  */
  //--Plotting Styles//
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.12);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  //////// Output File /////////
  TFile* outputFile = new TFile("SignalMT.root","RECREATE");
  outputFile->cd();

  //--//
  TCanvas* my_canvas = new TCanvas("canvas","canvas",800,600);
  my_canvas->cd();

  gPad->SetLogy();
 
  mT_Stage1_Wprime_M1000->SetMaximum(100000);
  mT_Stage1_Wprime_M1000->SetMinimum(1);
  mT_Stage1_Wprime_M1000->GetXaxis()->SetLimits(0, 6000);
  mT_Stage1_Wprime_M1000->GetXaxis()->SetTitle("M_{T} [GeV]");
  mT_Stage1_Wprime_M1000->GetYaxis()->SetTitle("Events");
  

  mT_Stage1_Wprime_M1000->Draw("HIST");
  mT_Stage1_Wprime_M1200->Draw("SAME HIST");
  mT_Stage1_Wprime_M1400->Draw("SAME HIST");
  
  //  mT_Stage1_Wprime_M2000->Draw("SAME HIST");
  //  mT_Stage1_Wprime_M3000->Draw("SAME HIST");
  //  mT_Stage1_Wprime_M4000->Draw("SAME HIST");
  //  mT_Stage1_Wprime_M5000->Draw("SAME HIST");
  
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

  TLatex* lumiText = new TLatex(0.92,0.975,"35.9 fb^{-1}");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     

  TLegend *leg_example = new TLegend(0.75,0.60,0.94,0.94);
  leg_example->SetFillColor(0);
  leg_example->SetTextFont(42);
  leg_example->SetBorderSize(0);
  leg_example->AddEntry(mT_Stage1_Wprime_M1000, "SSM W' 1.0 TeV", "l");
  //  leg_example->AddEntry(mT_Stage1_Wprime_M2000, "SSM W' 2 TeV", "l");
  leg_example->AddEntry(mT_Stage1_Wprime_M1200, "SSM W' 1.2 TeV", "l");
  leg_example->AddEntry(mT_Stage1_Wprime_M1400, "SSM W' 1.4 TeV", "l");
  // leg_example->AddEntry(mT_Stage1_Wprime_M3000, "SSM W' 3 TeV", "l");
  // leg_example->AddEntry(mT_Stage1_Wprime_M4000, "SSM W' 4 TeV", "l");
  // leg_example->AddEntry(mT_Stage1_Wprime_M5000, "SSM W' 5 TeV", "l");
  leg_example->Draw("same");
  
  my_canvas->Write();
  my_canvas->Print("mT_Signal2.png");
  my_canvas->Print("mT_Signal2.pdf");


 
  return 0;

}
