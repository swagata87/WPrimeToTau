// -*- C++ -*-
//
// Package:    WPrimeToTau/MiniAODAnalyzer
// Class:      MiniAODAnalyzer
//
/**\class MiniAODAnalyzer MiniAODAnalyzer.cc WPrimeToTau/MiniAODAnalyzer/plugins/MiniAODAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Swagata Mukherjee
//         Created:  Tue, 05 Jul 2016 09:41:37 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include <string>
#include "TH1.h"
#include "TLorentzVector.h"

// new includes
#include <unordered_map>
#include <unordered_set>
#include "helper.hh"
#include "TString.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class MiniAODAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit MiniAODAnalyzer(const edm::ParameterSet&);
  ~MiniAODAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  bool PassTauID(const pat::Tau &tau);
  bool PassTauID_NonIsolated(const pat::Tau &tau);
  bool PassTauAcceptance(TLorentzVector tau);

  bool FindTauIDEfficiency(const edm::Event&,TLorentzVector gen_p4);
  bool PassFinalCuts(int nGoodTau_, double met_val_, double met_phi_, double tau_pt_, double ptau_phi_);


  //new additions
  virtual void Create_Trees();
  virtual void Fill_Tree(TLorentzVector sel_lepton, const pat::MET sel_met);
  virtual void Fill_QCD_Tree(bool iso);

  std::unordered_map< std::string,float > mLeptonTree;
  std::unordered_map< std::string,float > mQCDTree;
  edm::Service<TFileService> fs;
  Helper* helper =new Helper(fs);

  // ----------member data ---------------------------
  edm::LumiReWeighting LumiWeights_;
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::TauCollection> tauToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_MET_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  // edm::EDGetTokenT<edm::ValueMap<bool> > eleLooseIdMapToken_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
  edm::EDGetTokenT<GenEventInfoProduct> genEventInfoProductTagToken_;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puCollection_;

  //------//
  TFile*  rootFile_;
  std::string outputFile_; // output file
  std::string pileupMC_ ;
  std::string pileupData_ ;
  TTree* mytree;
  TH1I *h1_EventCount;
  TH1I *h1_EventCount2;
  TH1D *h1_TauPt_Gen;
  TH1I *h1_nGoodTau_Reco;
  TH1I *h1_nGenTau;
  TH1D *h1_TauPt_reco;
  TH1D *h1_TauEta_reco;
  TH1D *h1_TauPt_goodreco;
  TH1D *h1_TauEta_goodreco;
  TH1D *h1_TauPt_Stage1;
  TH1D *h1_TauPt_RegA_Stage1;
  TH1D *h1_TauPt_RegC_Stage1;
  TH1D *h1_TauPt_GenMatchedTau_RegC_Stage1;
  TH1D *h1_TauPt_RegD_Stage1;
  TH1D *h1_TauPt_GenMatchedTau_RegD_Stage1;
  TH1D *h1_MT_Stage1;
  TH1D *h1_MT_RegA_Stage1;
  TH1D *h1_MT_RegC_Stage1;
  TH1D *h1_MT_GenMatchedTau_RegC_Stage1;
  TH1D *h1_MT_RegD_Stage1;
  TH1D *h1_MT_GenMatchedTau_RegD_Stage1;
  TH1D *h1_MT_Stage1_metUncert_JetEnUp;
  TH1D *h1_MT_Stage1_metUncert_JetEnDown;
  TH1D *h1_MT_Stage1_metUncert_JetResUp;
  TH1D *h1_MT_Stage1_metUncert_JetResDown;
  TH1D *h1_MT_Stage1_metUncert_MuonEnUp;
  TH1D *h1_MT_Stage1_metUncert_MuonEnDown;
  TH1D *h1_MT_Stage1_metUncert_ElectronEnUp;
  TH1D *h1_MT_Stage1_metUncert_ElectronEnDown;
  TH1D *h1_MT_Stage1_metUncert_TauEnUp;
  TH1D *h1_MT_Stage1_metUncert_TauEnDown;
  TH1D *h1_MT_Stage1_metUncert_PhotonEnUp;
  TH1D *h1_MT_Stage1_metUncert_PhotonEnDown;
  TH1D *h1_MT_Stage1_metUncert_UnclusteredEnUp;
  TH1D *h1_MT_Stage1_metUncert_UnclusteredEnDown;
  TH1D *h1_MT_Stage1_TauScaleUp;
  TH1D *h1_MT_Stage1_TauScaleDown;
  TH1D *h1_recoVtx_NoPUWt;
  TH1D *h1_recoVtx_WithPUWt;

  bool RunOnData;
  int Run;
  double final_weight=1;
  int Event;
  double dphi_tau_met;
  //  int num_PU_vertices;

};

//
// constructors and destructor
//
MiniAODAnalyzer::MiniAODAnalyzer(const edm::ParameterSet& iConfig):
  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  tauToken_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("taus"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("mets"))),
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerBits_MET_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits_MET"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  //  eleLooseIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),
  prunedGenToken_(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed"))),
  genEventInfoProductTagToken_(consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("genEventInfoProductMiniAOD"))),
  puCollection_(consumes<std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("pileupCollection"))),
  outputFile_(iConfig.getParameter<std::string>("outputFile")),
  RunOnData(iConfig.getParameter<bool>("RunOnData_"))
{
   //now do what ever initialization is needed
  //usesResource("TFileService");
  pileupMC_ = iConfig.getParameter<std::string>("PileupMCFile") ;
  pileupData_ = iConfig.getParameter<std::string>("PileupDataFile") ;
  rootFile_   = TFile::Open(outputFile_.c_str(),"RECREATE"); // open output file to store histograms
  TFileDirectory histoDir = fs->mkdir("histoDir");


/*
 * this is a bit messy atm, if we are fine with a histoDir
 * remove this part
 *
  h1_EventCount = fs->make<TH1I>("eventCount", "EventCount", 10, 0, 10);
  h1_nGenTau = fs->make<TH1I>("nGenTau", "nGenTau", 5, -0.5, 4.5);
  h1_nGoodTau_Reco = fs->make<TH1I>("nGoodTauReco", "nGoodTauReco", 5, -0.5, 4.5);
  h1_TauPt_Gen = fs->make<TH1D>("tauPt_Gen", "TauPt_Gen", 100, 0, 1000);
  h1_TauPt_reco = fs->make<TH1D>("tauPt_reco", "TauPt_reco", 50, 0, 1000);
  h1_TauPt_goodreco = fs->make<TH1D>("tauPt_goodreco", "TauPt_goodreco", 50, 0, 1000);
  h1_TauEta_reco = fs->make<TH1D>("tauEta_reco", "TauEta_reco", 48, -2.4, 2.4);
  h1_TauEta_goodreco = fs->make<TH1D>("tauEta_goodreco", "TauEta_goodreco", 48, -2.4, 2.4);
  h1_TauPt_Stage1 = fs->make<TH1D>("tauPt_Stage1", "TauPt_Stage1", 100, 0, 1000);
  h1_TauPt_RegA_Stage1 = fs->make<TH1D>("tauPt_RegA_Stage1", "TauPt_RegA_Stage1", 100, 0, 1000);
  h1_TauPt_RegC_Stage1 = fs->make<TH1D>("tauPt_RegC_Stage1", "TauPt_RegC_Stage1", 100, 0, 1000);
  h1_TauPt_GenMatchedTau_RegC_Stage1 = fs->make<TH1D>("tauPt_GenMatchedTau_RegC_Stage1", "TauPt_GenMatchedTau_RegC_Stage1", 100, 0, 1000);
  h1_TauPt_RegD_Stage1 = fs->make<TH1D>("tauPt_RegD_Stage1", "TauPt_RegD_Stage1", 100, 0, 1000);
  h1_TauPt_GenMatchedTau_RegD_Stage1 = fs->make<TH1D>("tauPt_GenMatchedTau_RegD_Stage1", "TauPt_GenMatchedTau_RegD_Stage1", 100, 0, 1000);
  h1_MT_Stage1 = fs->make<TH1D>("mT_Stage1", "MT_Stage1", 2000, 0, 2000);
  h1_MT_RegA_Stage1 = fs->make<TH1D>("mT_RegA_Stage1", "MT_RegA_Stage1", 2000, 0, 2000);
  h1_MT_RegC_Stage1 = fs->make<TH1D>("mT_RegC_Stage1", "MT_RegC_Stage1", 2000, 0, 2000);
  h1_MT_GenMatchedTau_RegC_Stage1 = fs->make<TH1D>("mT_GenMatchedTau_RegC_Stage1", "MT_GenMatchedTau_RegC_Stage1", 2000, 0, 2000);
  h1_MT_RegD_Stage1 = fs->make<TH1D>("mT_RegD_Stage1", "MT_RegD_Stage1", 2000, 0, 2000);
  h1_MT_GenMatchedTau_RegD_Stage1 = fs->make<TH1D>("mT_GenMatchedTau_RegD_Stage1", "MT_GenMatchedTau_RegD_Stage1", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnUp = fs->make<TH1D>("mT_Stage1_metUncert_JetEnUp", "MT_Stage1_metUncert_JetEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnDown = fs->make<TH1D>("mT_Stage1_metUncert_JetEnDown", "MT_Stage1_metUncert_JetEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResUp = fs->make<TH1D>("mT_Stage1_metUncert_JetResUp", "MT_Stage1_metUncert_JetResUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResDown = fs->make<TH1D>("mT_Stage1_metUncert_JetResDown", "MT_Stage1_metUncert_JetResDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnUp = fs->make<TH1D>("mT_Stage1_metUncert_MuonEnUp", "MT_Stage1_metUncert_MuonEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnDown = fs->make<TH1D>("mT_Stage1_metUncert_MuonEnDown", "MT_Stage1_metUncert_MuonEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnUp = fs->make<TH1D>("mT_Stage1_metUncert_ElectronEnUp", "MT_Stage1_metUncert_ElectronEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnDown = fs->make<TH1D>("mT_Stage1_metUncert_ElectronEnDown", "MT_Stage1_metUncert_ElectronEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnUp = fs->make<TH1D>("mT_Stage1_metUncert_TauEnUp", "MT_Stage1_metUncert_TauEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnDown = fs->make<TH1D>("mT_Stage1_metUncert_TauEnDown", "MT_Stage1_metUncert_TauEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnUp = fs->make<TH1D>("mT_Stage1_metUncert_PhotonEnUp", "MT_Stage1_metUncert_PhotonEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnDown = fs->make<TH1D>("mT_Stage1_metUncert_PhotonEnDown", "MT_Stage1_metUncert_PhotonEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnUp = fs->make<TH1D>("mT_Stage1_metUncert_UnclusteredEnUp", "MT_Stage1_metUncert_UnclusteredEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnDown = fs->make<TH1D>("mT_Stage1_metUncert_UnclusteredEnDown", "MT_Stage1_metUncert_UnclusteredEnDown", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleUp = fs->make<TH1D>("mT_Stage1_TauScaleUp", "MT_Stage1_TauScaleUp", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleDown = fs->make<TH1D>("mT_Stage1_TauScaleDown", "MT_Stage1_TauScaleDown", 2000, 0, 2000);
  h1_recoVtx_NoPUWt = fs->make<TH1D>("recoVtx_NoPUWt", "RecoVtx_NoPUWt", 100, 0, 100);
  h1_recoVtx_WithPUWt = fs->make<TH1D>("recoVtx_WithPUWt", "RecoVtx_WithPUWt", 100, 0, 100);*/
  h1_EventCount = histoDir.make<TH1I>("eventCount", "EventCount", 10, 0, 10);
  h1_nGenTau = histoDir.make<TH1I>("nGenTau", "nGenTau", 5, -0.5, 4.5);
  h1_nGoodTau_Reco = histoDir.make<TH1I>("nGoodTauReco", "nGoodTauReco", 5, -0.5, 4.5);
  h1_TauPt_Gen = histoDir.make<TH1D>("tauPt_Gen", "TauPt_Gen", 100, 0, 1000);
  h1_TauPt_reco = histoDir.make<TH1D>("tauPt_reco", "TauPt_reco", 50, 0, 1000);
  h1_TauPt_goodreco = histoDir.make<TH1D>("tauPt_goodreco", "TauPt_goodreco", 50, 0, 1000);
  h1_TauEta_reco = histoDir.make<TH1D>("tauEta_reco", "TauEta_reco", 48, -2.4, 2.4);
  h1_TauEta_goodreco = histoDir.make<TH1D>("tauEta_goodreco", "TauEta_goodreco", 48, -2.4, 2.4);
  h1_TauPt_Stage1 = histoDir.make<TH1D>("tauPt_Stage1", "TauPt_Stage1", 100, 0, 1000);
  h1_TauPt_RegA_Stage1 = histoDir.make<TH1D>("tauPt_RegA_Stage1", "TauPt_RegA_Stage1", 100, 0, 1000);
  h1_TauPt_RegC_Stage1 = histoDir.make<TH1D>("tauPt_RegC_Stage1", "TauPt_RegC_Stage1", 100, 0, 1000);
  h1_TauPt_GenMatchedTau_RegC_Stage1 = histoDir.make<TH1D>("tauPt_GenMatchedTau_RegC_Stage1", "TauPt_GenMatchedTau_RegC_Stage1", 100, 0, 1000);
  h1_TauPt_RegD_Stage1 = histoDir.make<TH1D>("tauPt_RegD_Stage1", "TauPt_RegD_Stage1", 100, 0, 1000);
  h1_TauPt_GenMatchedTau_RegD_Stage1 = histoDir.make<TH1D>("tauPt_GenMatchedTau_RegD_Stage1", "TauPt_GenMatchedTau_RegD_Stage1", 100, 0, 1000);
  h1_MT_Stage1 = histoDir.make<TH1D>("mT_Stage1", "MT_Stage1", 2000, 0, 2000);
  h1_MT_RegA_Stage1 = histoDir.make<TH1D>("mT_RegA_Stage1", "MT_RegA_Stage1", 2000, 0, 2000);
  h1_MT_RegC_Stage1 = histoDir.make<TH1D>("mT_RegC_Stage1", "MT_RegC_Stage1", 2000, 0, 2000);
  h1_MT_GenMatchedTau_RegC_Stage1 = histoDir.make<TH1D>("mT_GenMatchedTau_RegC_Stage1", "MT_GenMatchedTau_RegC_Stage1", 2000, 0, 2000);
  h1_MT_RegD_Stage1 = histoDir.make<TH1D>("mT_RegD_Stage1", "MT_RegD_Stage1", 2000, 0, 2000);
  h1_MT_GenMatchedTau_RegD_Stage1 = histoDir.make<TH1D>("mT_GenMatchedTau_RegD_Stage1", "MT_GenMatchedTau_RegD_Stage1", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_JetEnUp", "MT_Stage1_metUncert_JetEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_JetEnDown", "MT_Stage1_metUncert_JetEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResUp = histoDir.make<TH1D>("mT_Stage1_metUncert_JetResUp", "MT_Stage1_metUncert_JetResUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResDown = histoDir.make<TH1D>("mT_Stage1_metUncert_JetResDown", "MT_Stage1_metUncert_JetResDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_MuonEnUp", "MT_Stage1_metUncert_MuonEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_MuonEnDown", "MT_Stage1_metUncert_MuonEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnUp", "MT_Stage1_metUncert_ElectronEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnDown", "MT_Stage1_metUncert_ElectronEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_TauEnUp", "MT_Stage1_metUncert_TauEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_TauEnDown", "MT_Stage1_metUncert_TauEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnUp", "MT_Stage1_metUncert_PhotonEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnDown", "MT_Stage1_metUncert_PhotonEnDown", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnUp", "MT_Stage1_metUncert_UnclusteredEnUp", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnDown", "MT_Stage1_metUncert_UnclusteredEnDown", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleUp = histoDir.make<TH1D>("mT_Stage1_TauScaleUp", "MT_Stage1_TauScaleUp", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleDown = histoDir.make<TH1D>("mT_Stage1_TauScaleDown", "MT_Stage1_TauScaleDown", 2000, 0, 2000);
  h1_recoVtx_NoPUWt = histoDir.make<TH1D>("recoVtx_NoPUWt", "RecoVtx_NoPUWt", 100, 0, 100);
  h1_recoVtx_WithPUWt = histoDir.make<TH1D>("recoVtx_WithPUWt", "RecoVtx_WithPUWt", 100, 0, 100);

  if (!RunOnData) {
    LumiWeights_ = edm::LumiReWeighting(pileupMC_, pileupData_, "pileup", "pileup");
  }
}


MiniAODAnalyzer::~MiniAODAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  delete rootFile_;

}

//
// member functions
//

// ------------ method called for each event  ------------
void
MiniAODAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace pat;

  h1_EventCount->Fill(1);

  //---Clear---//
  Run=0;
  Event=0;
  //------//
  Run   = iEvent.id().run();
  Event = iEvent.id().event();
  //std::cout << "\n --EVENT-- " << Event << std::endl;

  //-- probValue --//
  //-- https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py --//
  //----------//
  //--PileUp--//
  //----------//
  int MC_TrueNumInteractions=-1;
  double Lumi_Wt=1;

  if (!RunOnData) {
    Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByToken(puCollection_, PupInfo);
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    int Tnpv = -1;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      int BX = PVI->getBunchCrossing();
      // std::cout << " --PVI-- " << " BX=" << BX << std::endl;
      if(BX == 0) {
    Tnpv = PVI->getTrueNumInteractions();
    //  std::cout << "Tnpv=" << Tnpv << std::endl;
    continue;
      }
    }
    MC_TrueNumInteractions = Tnpv;

    Lumi_Wt = LumiWeights_.weight( MC_TrueNumInteractions );
  }
  //  std::cout << "RunOnData=" << RunOnData << " MC_TrueNumInteractions=" << MC_TrueNumInteractions << " Lumi_Wt=" << Lumi_Wt << std::endl;

  ///-- MC event weight --///
  double mc_event_weight=1;
  if (!RunOnData) {
    Handle<GenEventInfoProduct> genEvtInfo;
    iEvent.getByToken(genEventInfoProductTagToken_, genEvtInfo );
    mc_event_weight = genEvtInfo->weight();
  }
  //  std::cout << "RunOnData=" << RunOnData << " mc_event_weight=" << mc_event_weight << std::endl;

  //----------------//
  //--Final Weight--//
  //----------------//
  if (!RunOnData) {
    final_weight=Lumi_Wt*mc_event_weight;
  }
  else {
    final_weight=1;
  }
  //  std::cout << "RunOnData=" << RunOnData << " final_weight=" << final_weight << std::endl;

  ///----///
  int nGenTau=0;
  TLorentzVector tauGen_p4[10];
  const Candidate * MyTau;
  // const Candidate * MyTauSel=0;
  double TauPt_Gen=0;
  if (!RunOnData) {
    //--GenParticles--//
    Handle<edm::View<reco::GenParticle> > pruned;
    std::cout << pruned <<
    iEvent.getByToken(prunedGenToken_,pruned);

    Handle<edm::View<pat::PackedGenParticle> > packed;
    iEvent.getByToken(packedGenToken_,packed);

    for(size_t i=0; i<pruned->size();i++){
      if(   (abs((*pruned)[i].pdgId())==15) && ( ((*pruned)[i].status()==2) )) {
    MyTau = &(*pruned)[i];
    if ( (MyTau->pt()>20.0)  &&  (fabs(MyTau->eta())<2.3)  )  {
      // MyTauSel=MyTau;
      TauPt_Gen=MyTau->pt();
      h1_TauPt_Gen->Fill(TauPt_Gen);
      tauGen_p4[nGenTau].SetPxPyPzE(MyTau->px(),MyTau->py(),MyTau->pz(),MyTau->energy());
      nGenTau++;
      // std::cout << " pt " << TauPt_Gen << " nMother=" << MyTau->numberOfMothers() << " mother pdgID = " << MyTau->mother(0)->pdgId() << " mother status = " << MyTau->mother(0)->status()  << std::endl;
      //  const Candidate * MotherOfMyTau=MyTau->mother(0);
    }
      }
    }
  }
  ////  std::cout << "nGenTau=" << nGenTau << std::endl;
  //   if ((!RunOnData) && (nGenTau>1))   std::cout << "\n#### #### #### ######### nGenTau=" << nGenTau << std::endl;
  h1_nGenTau->Fill(nGenTau);
   if (nGenTau==1) FindTauIDEfficiency(iEvent,tauGen_p4[0]);


   //---Trigger---//
   edm::Handle<edm::TriggerResults> triggerBits;
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

   iEvent.getByToken(triggerBits_, triggerBits);
   iEvent.getByToken(triggerObjects_, triggerObjects);
   iEvent.getByToken(triggerPrescales_, triggerPrescales);

   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

   bool passTauTrig=0;

   //   std::cout << "=== TRIGGER PATHS === " << std::endl;
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
     //    std::cout << "Trigger " << names.triggerName(i) <<
     // ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
     // ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)")
     //        << std::endl;
     if ( (names.triggerName(i)).find("HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90") != std::string::npos ) {
       passTauTrig=triggerBits->accept(i) ;
     }
   }
   if (!RunOnData) passTauTrig=1;
   // std::cout << "RunOnData=" << RunOnData <<  " ## passTauTrig=" << passTauTrig << std::endl;

   //---Trigger MET---//
   edm::Handle<edm::TriggerResults> triggerBits_MET;
   iEvent.getByToken(triggerBits_MET_, triggerBits_MET);
   const edm::TriggerNames &names_MET = iEvent.triggerNames(*triggerBits_MET);

   bool passHBHENoiseFilter=0;
   bool passHBHENoiseIsoFilter=0;
   bool passEcalDeadCellTriggerPrimitiveFilter=0;
   bool passgoodVertices=0;
   bool passeeBadScFilter=0;
   bool passglobalTightHalo2016Filter=0;

   //   std::cout << " === TRIGGER PATHS (MET) === " << std::endl;
   for (unsigned int i = 0, n = triggerBits_MET->size(); i < n; ++i) {
     //std::cout << "Trigger " << names_MET.triggerName(i) <<
     //  ": " << (triggerBits_MET->accept(i) ? "PASS" : "fail (or not run)")
     //        << std::endl;
        if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseFilter") != std::string::npos ) {
      passHBHENoiseFilter=triggerBits_MET->accept(i) ;
        }
        if ( (names_MET.triggerName(i)).find("Flag_HBHENoiseIsoFilter") != std::string::npos ) {
      passHBHENoiseIsoFilter=triggerBits_MET->accept(i) ;
        }
    if ( (names_MET.triggerName(i)).find("Flag_EcalDeadCellTriggerPrimitiveFilter") != std::string::npos ) {
      passEcalDeadCellTriggerPrimitiveFilter=triggerBits_MET->accept(i) ;
        }
    if ( (names_MET.triggerName(i)).find("Flag_goodVertices") != std::string::npos ) {
      passgoodVertices=triggerBits_MET->accept(i) ;
        }
    if ( (names_MET.triggerName(i)).find("Flag_eeBadScFilter") != std::string::npos ) {
      passeeBadScFilter=triggerBits_MET->accept(i) ;
        }
    if ( (names_MET.triggerName(i)).find("Flag_globalTightHalo2016Filter") != std::string::npos ) {
      passglobalTightHalo2016Filter=triggerBits_MET->accept(i) ;
        }
   }

   /*
   if (!RunOnData) {
     passHBHENoiseFilter=1;
     passHBHENoiseIsoFilter=1;
     passEcalDeadCellTriggerPrimitiveFilter=1;
     passgoodVertices=1;
     passeeBadScFilter=1;
     passglobalTightHalo2016Filter=1;
   }
   */
   //   if (!RunOnData) passTauTrig=1;
   //std::cout << "RunOnData=" << RunOnData <<  " ## passHBHENoiseFilter=" << passHBHENoiseFilter
   // <<  " ## passHBHENoiseIsoFilter=" << passHBHENoiseIsoFilter
   //        << " ## passEcalDeadCellTriggerPrimitiveFilter=" << passEcalDeadCellTriggerPrimitiveFilter
   //        << " ## passgoodVertices=" << passgoodVertices
   //        << " ## passeeBadScFilter=" << passeeBadScFilter
   //        << " ## passglobalTightHalo2016Filter=" << passglobalTightHalo2016Filter << std::endl;


   edm::Handle<reco::VertexCollection> vertices;
   iEvent.getByToken(vtxToken_, vertices);
   if (vertices->empty()) return; // skip the event if no PV found
   // std::cout << "Number of vertices " << vertices->size() << std::endl;
   const reco::Vertex &PV = vertices->front();
   reco::VertexCollection vtxs = *vertices;

   int nvtx=0;
   int recoVtx = vertices->size();

   if( vertices.isValid() ){
     for( reco::VertexCollection::const_iterator vtx = vtxs.begin(); vtx!=vtxs.end(); ++vtx ) {
       bool isGood = ( (vtx->ndof() >= 4.0) &&
               (abs(vtx->z()) <= 24.0) &&
               (abs(vtx->position().Rho()) <= 2.0)
               );
       //       std::cout << "vtx->ndof()=" << vtx->ndof() << " ## vtx->z()=" << vtx->z() << " ## vtx->position().Rho()=" << vtx->position().Rho() << std::endl;
       //       std::cout << "Vertex is good? " << isGood << std::endl;
       if( !isGood ) continue;
       nvtx++;
     }
   }
   //   std::cout << "Number of good vertices " << nvtx << std::endl;


   edm::Handle<pat::METCollection> mets;
   iEvent.getByToken(metToken_, mets);
   const pat::MET &met = mets->front();
   double met_val=met.pt();
   double met_phi=met.phi();
   //-------------------------//
   //**--MET UNCERTAINTIES--**//
   //-------------------------//
   //--JetEnergy Up--//
   double met_val_JetEnUp=met.shiftedPt(pat::MET::JetEnUp);
   double met_phi_JetEnUp=met.shiftedPhi(pat::MET::JetEnUp);
   //--JetEnergy Down--//
   double met_val_JetEnDown=met.shiftedPt(pat::MET::JetEnDown);
   double met_phi_JetEnDown=met.shiftedPhi(pat::MET::JetEnDown);
   //--JetRes Up--//
   double met_val_JetResUp=met.shiftedPt(pat::MET::JetResUp);
   double met_phi_JetResUp=met.shiftedPhi(pat::MET::JetResUp);
   //--JetRes Down--//
   double met_val_JetResDown=met.shiftedPt(pat::MET::JetResDown);
   double met_phi_JetResDown=met.shiftedPhi(pat::MET::JetResDown);
   //--MuonEnergy Up--//
   double met_val_MuonEnUp=met.shiftedPt(pat::MET::MuonEnUp);
   double met_phi_MuonEnUp=met.shiftedPhi(pat::MET::MuonEnUp);
   //--MuonEnergy Down--//
   double met_val_MuonEnDown=met.shiftedPt(pat::MET::MuonEnDown);
   double met_phi_MuonEnDown=met.shiftedPhi(pat::MET::MuonEnDown);
   //--ElectronEnergy Up--//
   double met_val_ElectronEnUp=met.shiftedPt(pat::MET::ElectronEnUp);
   double met_phi_ElectronEnUp=met.shiftedPhi(pat::MET::ElectronEnUp);
   //--ElectronEnergy Down--//
   double met_val_ElectronEnDown=met.shiftedPt(pat::MET::ElectronEnDown);
   double met_phi_ElectronEnDown=met.shiftedPhi(pat::MET::ElectronEnDown);
   //--TauEnergy Up--//
   double met_val_TauEnUp=met.shiftedPt(pat::MET::TauEnUp);
   double met_phi_TauEnUp=met.shiftedPhi(pat::MET::TauEnUp);
   //--TauEnergy Down--//
   double met_val_TauEnDown=met.shiftedPt(pat::MET::TauEnDown);
   double met_phi_TauEnDown=met.shiftedPhi(pat::MET::TauEnDown);
   //--PhotonEnergy Up--//
   double met_val_PhotonEnUp=met.shiftedPt(pat::MET::PhotonEnUp);
   double met_phi_PhotonEnUp=met.shiftedPhi(pat::MET::PhotonEnUp);
   //--PhotonEnergy Down--//
   double met_val_PhotonEnDown=met.shiftedPt(pat::MET::PhotonEnDown);
   double met_phi_PhotonEnDown=met.shiftedPhi(pat::MET::PhotonEnDown);
   //--UnclusteredEnergy Up--//
   double met_val_UnclusteredEnUp=met.shiftedPt(pat::MET::UnclusteredEnUp);
   double met_phi_UnclusteredEnUp=met.shiftedPhi(pat::MET::UnclusteredEnUp);
   //--UnclusteredEnergy Down--//
   double met_val_UnclusteredEnDown=met.shiftedPt(pat::MET::UnclusteredEnDown);
   double met_phi_UnclusteredEnDown=met.shiftedPhi(pat::MET::UnclusteredEnDown);

   //h1_MT_Stage1_metUncert_UnclusteredEnUp
   //   std::cout << "**MET** phi=" << met.phi() << " phi(JES up=)" << met.shiftedPhi(pat::MET::JetEnUp) << " phi(JES down=)=" << met.shiftedPhi(pat::MET::JetEnDown) << std::endl;
   //   printf("MET: pt %5.1f, phi %+4.2f, sumEt (%.1f). genMET %.1f. MET with JES up/down: %.1f/%.1f\n",
   //     met.pt(), met.phi(), met.sumEt(),
   //     met.genMET()->pt(),
   //     met.shiftedPt(pat::MET::JetEnUp), met.shiftedPt(pat::MET::JetEnDown));
   // std::cout << "MET=" << met_val << std::endl;

   int nTightMu=0;
   edm::Handle<pat::MuonCollection> muons;
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
     //https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon
     if ( (mu.pt()>20.0) &&  (abs(mu.eta())<2.4) && (mu.isTightMuon(PV)) &&  ((mu.isolationR03().sumPt/mu.pt())<0.10) ) nTightMu++ ;
     //std::cout << "mu.pt()=" << mu.pt() << " abs(mu.eta())=" << abs(mu.eta()) << " mu.isolationR03().sumPt/mu.pt()=" << mu.isolationR03().sumPt/mu.pt() << std::endl;
     //       printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
     //     mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
   }
   //  std::cout << "nTightMu=" << nTightMu << std::endl;

   int nLooseEle=0;
   //   int nLooseEle_HighPt=0;
   edm::Handle<pat::ElectronCollection> electrons;
   iEvent.getByToken(electronToken_, electrons);
   //   std::cout << "nEle = " << electrons->size() << std::endl;
   for (const pat::Electron &el : *electrons) {
     //std::cout <<      el.electronIDs().size() << std::endl;
     //std::cout <<      el.electronIDs().front().first << std::endl;
     if (el.pt() < 5) continue;
     //https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
     if ( (el.pt()>20) &&  ( abs(el.eta())<2.5 )  && (el.electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose")>6) ) nLooseEle++;

     //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f  ",
     //      el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta()  );
   }
   //  std::cout << "nLooseEle=" << nLooseEle << std::endl;

   edm::Handle<pat::TauCollection> taus;
   int nGoodTau=0;
   double tau_pt[10]={0};
   double tau_phi[10]={0};

   int nGoodNonIsoTau=0;
   double tau_pt_nonIso[10]={0};
   double tau_phi_nonIso[10]={0};

   int nGoodTau_ScaleUp=0;
   double tau_pt_ScaleUp[10]={0};
   double tau_phi_ScaleUp[10]={0};

   int nGoodTau_ScaleDown=0;
   double tau_pt_ScaleDown[10]={0};
   double tau_phi_ScaleDown[10]={0};

   double tauScaleShift=0.03;
   TLorentzVector tau_NoShift(0,0,0,0);
   TLorentzVector tau_ScaleUp(0,0,0,0);
   TLorentzVector tau_ScaleDown(0,0,0,0);
   TLorentzVector tau_nonIso(0,0,0,0);

   //  double tau_px=0;
   //double tau_py=0;
   //double tau_pz=0;
   //double tau_E=0;
   //TLorentzVector tauGoodReco_p4;

   iEvent.getByToken(tauToken_, taus);

   for (const pat::Tau &tau : *taus) {

     if (PassTauID_NonIsolated(tau)==true) {
       tau_nonIso.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
       if (PassTauAcceptance(tau_nonIso)==true) {
     tau_pt_nonIso[nGoodNonIsoTau]=tau_nonIso.Pt();
     tau_phi_nonIso[nGoodNonIsoTau]=tau_nonIso.Phi();
     nGoodNonIsoTau++;
       }
     }

     if ( (PassTauID(tau)==true) ) {

       tau_NoShift.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
       tau_ScaleUp.SetPxPyPzE((1+tauScaleShift)*(tau.px()),(1+tauScaleShift)*(tau.py()),(1+tauScaleShift)*(tau.pz()),(1+tauScaleShift)*(tau.energy()));
       tau_ScaleDown.SetPxPyPzE((1-tauScaleShift)*(tau.px()),(1-tauScaleShift)*(tau.py()),(1-tauScaleShift)*(tau.pz()),(1-tauScaleShift)*(tau.energy()));

       if (PassTauAcceptance(tau_NoShift)==true) {
     // std::cout << "Tau selected" << std::endl;
     tau_pt[nGoodTau]=tau_NoShift.Pt();
     tau_phi[nGoodTau]=tau_NoShift.Phi();
     nGoodTau++;
       }

       //-Syst Up-//
       if (PassTauAcceptance(tau_ScaleUp)==true) {
     // std::cout << "Tau selected" << std::endl;
     tau_pt_ScaleUp[nGoodTau_ScaleUp]=tau_ScaleUp.Pt();
     tau_phi_ScaleUp[nGoodTau_ScaleUp]=tau_ScaleUp.Phi();
     nGoodTau_ScaleUp++;
       }

       //-Syst Down-//
       if (PassTauAcceptance(tau_ScaleDown)==true) {
     // std::cout << "Tau selected" << std::endl;
     tau_pt_ScaleDown[nGoodTau_ScaleDown]=tau_ScaleDown.Pt();
     tau_phi_ScaleDown[nGoodTau_ScaleDown]=tau_ScaleDown.Phi();
     nGoodTau_ScaleDown++;
       }
     }
   }

   h1_nGoodTau_Reco->Fill(nGoodTau,final_weight);
   //std::cout << "nGoodTau=" << nGoodTau << ",nGoodTau_ScaleUp=" << nGoodTau_ScaleUp << ",nGoodTau_ScaleDown=" << nGoodTau_ScaleDown << std::endl;

   //---------------//
   //---Selection---//
   //---------------//

   if (passTauTrig && passHBHENoiseFilter && passHBHENoiseIsoFilter && passEcalDeadCellTriggerPrimitiveFilter && passgoodVertices && passeeBadScFilter && passglobalTightHalo2016Filter) {
     if ( (nvtx>0) && (nTightMu==0) && (nLooseEle==0) ) {
       //** Stage1 = final stage (all cuts applied) **//
       if ( (PassFinalCuts(nGoodTau, met_val,met_phi,tau_pt[0],tau_phi[0]) == true) ) {
     h1_recoVtx_NoPUWt->Fill(recoVtx,mc_event_weight);
     h1_recoVtx_WithPUWt->Fill(recoVtx,final_weight);
     h1_TauPt_Stage1->Fill(tau_pt[0],final_weight);
     //std::cout << "*Standard* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT=  sqrt(2*tau_pt[0]*met_val*(1- cos(dphi_tau_met)));
     h1_MT_Stage1->Fill(MT,final_weight);
       }
       //--Systematics--//
       if ( (PassFinalCuts(nGoodTau, met_val_JetEnUp,met_phi_JetEnUp,tau_pt[0],tau_phi[0] ) == true) ) {
     //std::cout << "*metUncert_JetEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_JetEnUp = sqrt(2*tau_pt[0]*met_val_JetEnUp*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_JetEnUp->Fill(MT_metUncert_JetEnUp,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_JetEnDown,met_phi_JetEnDown,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_JetEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_JetEnDown = sqrt(2*tau_pt[0]*met_val_JetEnDown*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_JetEnDown->Fill(MT_metUncert_JetEnDown,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_JetResUp,met_phi_JetResUp,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_JetResUp* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_JetResUp = sqrt(2*tau_pt[0]*met_val_JetResUp*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_JetResUp->Fill(MT_metUncert_JetResUp,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_JetResDown,met_phi_JetResDown,tau_pt[0],tau_phi[0]) == true) ) {
     // std::cout << "*metUncert_JetResDown* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_JetResDown = sqrt(2*tau_pt[0]*met_val_JetResDown*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_JetResDown->Fill(MT_metUncert_JetResDown,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_MuonEnUp,met_phi_MuonEnUp,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_MuonEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_MuonEnUp = sqrt(2*tau_pt[0]*met_val_MuonEnUp*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_MuonEnUp->Fill(MT_metUncert_MuonEnUp,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_MuonEnDown,met_phi_MuonEnDown,tau_pt[0],tau_phi[0]) == true) ) {
     // std::cout << "*metUncert_MuonEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_MuonEnDown = sqrt(2*tau_pt[0]*met_val_MuonEnDown*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_MuonEnDown->Fill(MT_metUncert_MuonEnDown,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_ElectronEnUp,met_phi_ElectronEnUp,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_ElectronEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
    double MT_metUncert_ElectronEnUp = sqrt(2*tau_pt[0]*met_val_ElectronEnUp*(1- cos(dphi_tau_met)));
    h1_MT_Stage1_metUncert_ElectronEnUp->Fill(MT_metUncert_ElectronEnUp,final_weight);
      }
      ///
       if ( (PassFinalCuts(nGoodTau, met_val_ElectronEnDown,met_phi_ElectronEnDown,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_ElectronEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_ElectronEnDown = sqrt(2*tau_pt[0]*met_val_ElectronEnDown*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_ElectronEnDown->Fill(MT_metUncert_ElectronEnDown,final_weight);
      }
      ///
       if ( (PassFinalCuts(nGoodTau, met_val_TauEnUp,met_phi_TauEnUp,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_TauEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
    double MT_metUncert_TauEnUp = sqrt(2*tau_pt[0]*met_val_TauEnUp*(1- cos(dphi_tau_met)));
    h1_MT_Stage1_metUncert_TauEnUp->Fill(MT_metUncert_TauEnUp,final_weight);
      }
      ///
       if ( (PassFinalCuts(nGoodTau, met_val_TauEnDown,met_phi_TauEnDown,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_TauEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
    double MT_metUncert_TauEnDown = sqrt(2*tau_pt[0]*met_val_TauEnDown*(1- cos(dphi_tau_met)));
    h1_MT_Stage1_metUncert_TauEnDown->Fill(MT_metUncert_TauEnDown,final_weight);
      }
      ///
       if ( (PassFinalCuts(nGoodTau, met_val_PhotonEnUp,met_phi_PhotonEnUp,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_PhotonEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
    double MT_metUncert_PhotonEnUp = sqrt(2*tau_pt[0]*met_val_PhotonEnUp*(1- cos(dphi_tau_met)));
    h1_MT_Stage1_metUncert_PhotonEnUp->Fill(MT_metUncert_PhotonEnUp,final_weight);
      }
      ///
       if ( (PassFinalCuts(nGoodTau, met_val_PhotonEnDown,met_phi_PhotonEnDown,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_PhotonEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
    double MT_metUncert_PhotonEnDown = sqrt(2*tau_pt[0]*met_val_PhotonEnDown*(1- cos(dphi_tau_met)));
    h1_MT_Stage1_metUncert_PhotonEnDown->Fill(MT_metUncert_PhotonEnDown,final_weight);
      }
      ///
       if ( (PassFinalCuts(nGoodTau, met_val_UnclusteredEnUp,met_phi_UnclusteredEnUp,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_UnclusteredEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
    double MT_metUncert_UnclusteredEnUp = sqrt(2*tau_pt[0]*met_val_UnclusteredEnUp*(1- cos(dphi_tau_met)));
    h1_MT_Stage1_metUncert_UnclusteredEnUp->Fill(MT_metUncert_UnclusteredEnUp,final_weight);
      }
       ///
       if ( (PassFinalCuts(nGoodTau, met_val_UnclusteredEnDown,met_phi_UnclusteredEnDown,tau_pt[0],tau_phi[0]) == true) ) {
     //std::cout << "*metUncert_UnclusteredEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_metUncert_UnclusteredEnDown = sqrt(2*tau_pt[0]*met_val_UnclusteredEnDown*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_metUncert_UnclusteredEnDown->Fill(MT_metUncert_UnclusteredEnDown,final_weight);
       }
       ///--Tau Scale--///
       if ( (PassFinalCuts(nGoodTau_ScaleUp, met_val, met_phi, tau_pt_ScaleUp[0], tau_phi_ScaleUp[0]) == true) ) {
     //std::cout << "*Tau Scale Up* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_TauScaleUp = sqrt(2*tau_pt_ScaleUp[0]*met_val*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_TauScaleUp->Fill(MT_TauScaleUp,final_weight);
       }
       ///
       if ( (PassFinalCuts(nGoodTau_ScaleDown, met_val, met_phi, tau_pt_ScaleDown[0], tau_phi_ScaleDown[0]) == true) ) {
     //std::cout << "*Tau Scale Down* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT_TauScaleDown = sqrt(2*tau_pt_ScaleDown[0]*met_val*(1- cos(dphi_tau_met)));
     h1_MT_Stage1_TauScaleDown->Fill(MT_TauScaleDown,final_weight);
       }
       ///
     }
   }

   //--------------//
   //-- Region A --// Only one non-isolated tau //
   //--------------//
   if (passTauTrig && passHBHENoiseFilter && passHBHENoiseIsoFilter && passEcalDeadCellTriggerPrimitiveFilter && passgoodVertices && passeeBadScFilter && passglobalTightHalo2016Filter) {
     if ( (nvtx>0) && (nTightMu==0) && (nLooseEle==0) ) {
       //** Stage1 = final stage (all cuts applied) **//
       if ( (PassFinalCuts(nGoodNonIsoTau,met_val,met_phi,tau_pt_nonIso[0],tau_phi_nonIso[0]) == true) ) {
         h1_TauPt_RegA_Stage1->Fill(tau_pt_nonIso[0],final_weight);
         //std::cout << "*Standard* dphi_tau_met=" << dphi_tau_met << std::endl;
         double MT_RegA =  sqrt(2*tau_pt_nonIso[0]*met_val*(1- cos(dphi_tau_met)));
         h1_MT_RegA_Stage1->Fill(MT_RegA,final_weight);

       }
     }
   }



   //--------------//
   //-- Region C --// One non-isolated tau + one isolated e/mu
   //--------------//
   if (passTauTrig && passHBHENoiseFilter && passHBHENoiseIsoFilter && passEcalDeadCellTriggerPrimitiveFilter && passgoodVertices && passeeBadScFilter && passglobalTightHalo2016Filter) {
     if ( (nvtx>0)  &&  ((nTightMu+nLooseEle)==1)  ) {
       if ( (PassFinalCuts(nGoodNonIsoTau,met_val,met_phi,tau_pt_nonIso[0],tau_phi_nonIso[0]) == true) ) {
         h1_TauPt_RegC_Stage1->Fill(tau_pt_nonIso[0],final_weight);
         double MT_RegC =  sqrt(2*tau_pt_nonIso[0]*met_val*(1- cos(dphi_tau_met)));
         h1_MT_RegC_Stage1->Fill(MT_RegC,final_weight);

     if (!RunOnData) {
       double DR_min_C=999;
       ///   std::cout << "\n nGenTau=" << nGenTau << std::endl;
       for (int i=0; i<nGenTau; i++) {
         double deltaR_tau_gen_reco_C = tauGen_p4[i].DeltaR(tau_nonIso);
         if (DR_min_C>deltaR_tau_gen_reco_C) DR_min_C=deltaR_tau_gen_reco_C;
       }
       if (DR_min_C<0.4) {
         // Genmatched tau
         h1_TauPt_GenMatchedTau_RegC_Stage1->Fill(tau_pt_nonIso[0],final_weight);
         h1_MT_GenMatchedTau_RegC_Stage1->Fill(MT_RegC,final_weight);

       }
     }
       }
     }
   }

   //--------------//
   //-- Region D --// One isolated tau + one isolated e/mu
   //--------------//
   if (passTauTrig && passHBHENoiseFilter && passHBHENoiseIsoFilter && passEcalDeadCellTriggerPrimitiveFilter && passgoodVertices && passeeBadScFilter && passglobalTightHalo2016Filter) {
     if ( (nvtx>0)  &&  ((nTightMu+nLooseEle)==1)  ) {
       if ( (PassFinalCuts(nGoodTau,met_val,met_phi,tau_pt[0],tau_phi[0]) == true) ) {
         h1_TauPt_RegD_Stage1->Fill(tau_pt[0],final_weight);
         //std::cout << "*Standard* dphi_tau_met=" << dphi_tau_met << std::endl;
         double MT_RegD =  sqrt(2*tau_pt[0]*met_val*(1- cos(dphi_tau_met)));
         h1_MT_RegD_Stage1->Fill(MT_RegD,final_weight);
         if (!RunOnData) {
       double DR_min=999;
       for (int i=0; i<nGenTau; i++) {
         double deltaR_tau_gen_reco = tauGen_p4[i].DeltaR(tau_NoShift);
         if (DR_min>deltaR_tau_gen_reco) DR_min=deltaR_tau_gen_reco;
       }
       if (DR_min<0.4) {
         // Genmatched tau
         h1_TauPt_GenMatchedTau_RegD_Stage1->Fill(tau_pt[0],final_weight);
         h1_MT_GenMatchedTau_RegD_Stage1->Fill(MT_RegD,final_weight);
       }
     }
       }
     }
   }





   mytree->Fill();
   Fill_QCD_Tree(true);

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}

bool MiniAODAnalyzer::PassFinalCuts(int nGoodTau_, double met_val_,double met_phi_,double tau_pt_,double tau_phi_) {
  bool passed=false;
  if (nGoodTau_==1) {
    if ( met_val_>120 ) {
      dphi_tau_met = deltaPhi(tau_phi_,met_phi_);
      double pToverEtMiss=tau_pt_/met_val_ ;
      if (pToverEtMiss>0.7 && pToverEtMiss<1.3) {
    // std::cout << "pToverEtMiss=" << pToverEtMiss << std::endl;
    if (dphi_tau_met>2.4) {
      // std::cout << "dphi_tau_met=" << dphi_tau_met << std::endl;
      passed=true;
    }
      }
    }
  }
  return passed;
}

bool MiniAODAnalyzer::FindTauIDEfficiency(const edm::Event& iEvent, TLorentzVector gen_p4) {

  edm::Handle<pat::TauCollection> taus;
  iEvent.getByToken(tauToken_, taus);
  TLorentzVector tauReco_p4;
  TLorentzVector tauGoodReco_p4;

  for (const pat::Tau &tau : *taus) {
    if ( (tau.pt()>20) && (fabs(tau.eta())<2.3) ) {
      tauReco_p4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
      double deltaR_tau_gen_reco = gen_p4.DeltaR(tauReco_p4);
      if (deltaR_tau_gen_reco<0.4) {
    h1_TauPt_reco->Fill(tau.pt(),final_weight);
    h1_TauEta_reco->Fill(tau.eta(),final_weight);
    if (PassTauID(tau)==true) {
      h1_TauPt_goodreco->Fill(tau.pt(),final_weight);
      h1_TauEta_goodreco->Fill(tau.eta(),final_weight);
    }
      }
    }
  }
  return true;
}

bool MiniAODAnalyzer::PassTauID(const pat::Tau &tau)
{

  bool passTauID_=true;

  //----Tau ID----//
  if ( tau.tauID("decayModeFindingNewDMs") < 0.5 ) passTauID_=false;
  if ( tau.tauID("byMediumIsolationMVArun2v1DBnewDMwLT") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstElectronLooseMVA6") < 0.5 ) passTauID_=false;
  if ( tau.tauID("againstMuonLoose3") < 0.5 ) passTauID_=false;

   return passTauID_;
}

bool MiniAODAnalyzer::PassTauID_NonIsolated(const pat::Tau &tau)
{
  bool passTauID_NonIso_=true;

  //----Tau ID----//
  if ( tau.tauID("decayModeFindingNewDMs") < 0.5 ) passTauID_NonIso_=false;
  if ( tau.tauID("byMediumIsolationMVArun2v1DBnewDMwLT") > 0.5 ) passTauID_NonIso_=false;
  if ( tau.tauID("againstElectronLooseMVA6") < 0.5 ) passTauID_NonIso_=false;
  if ( tau.tauID("againstMuonLoose3") < 0.5 ) passTauID_NonIso_=false;

   return passTauID_NonIso_;
}

bool MiniAODAnalyzer::PassTauAcceptance(TLorentzVector tau)
{
  bool passTauAcc_=true;
  //  std::cout << "Inside PassTauAcceptance -> TAU pt=" << tau.Pt() << " energy=" << tau.Energy() << std::endl;
  //----pT----//
  if ( tau.Pt() < 80 ) passTauAcc_=false;

  //----Eta----//
  if ( fabs(tau.PseudoRapidity()) > 2.1 ) passTauAcc_=false;

  return passTauAcc_;
}

// ------------ method called once each job just before starting event loop  ------------
void
MiniAODAnalyzer::beginJob()
{
  rootFile_->cd();
  mytree  = new TTree("tree","tr");

  //----
  mytree->Branch("event_runNo",  &Run,   "event_runNo/I");
  mytree->Branch("event_evtNo",  &Event, "event_evtNo/I");
  //mytree->Branch("num_PU_vertices",&num_PU_vertices,"num_PU_vertices/I");
  Create_Trees();

  helper->CreateHistoUnchangedName("h_counters", 10, 0, 11, "N_{events}");
}

// ------------ method called once each job just after ending the event loop  ------------
void
MiniAODAnalyzer::endJob()
{

  /*
   * this part can be removed, if we want to
   * "mytree" as to be reintroduced in the TFileService then
   * via mytree = fs->make<TTree>("tree", "tr");
  */
  rootFile_->cd();
  rootFile_->mkdir("mukherjee");
  rootFile_->cd("mukherjee");
  mytree->Write();
  rootFile_->cd("..");
  rootFile_->mkdir("materok");// used for testing purposes
  rootFile_->cd("materok");
  helper->WriteAll("h_");
  helper->WriteTree("qcdtree");

  rootFile_->Close();

  //TFileDirectory subDir = fs->mkdir( "mySubDirectory" ); //testing
  //subDir.cd();
  //helper.WriteTree("qcdtree");
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MiniAODAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

/*
 *   Intoduce a map of trees, instead of a tree
 *   Has the advantage of not initialising the tree 3 times,
 *   modeled after the exisiting TAPAS code in HistClass.hh and WPrime's specialAna
*/
    //create a function that creates a Tree on a map (argument 1) with a given name (argument 2)

void MiniAODAnalyzer::Create_Trees(){
  //these are the variables used in the tree of the old analysis

  //Kinematics
  mLeptonTree["mt"]=0;
  mLeptonTree["delta_phi"]=0;
  mLeptonTree["pt"]=0;
  mLeptonTree["met"]=0;
  mLeptonTree["lepton_phi"]=0;
  mLeptonTree["lepton_eta"]=0;
  mLeptonTree["met_phi"]=0;
  mLeptonTree["jet1_et"]=0;
  mLeptonTree["jet1_phi"]=0;
  mLeptonTree["jet1_eta"]=0;

  mLeptonTree["bjet1"]=0;
  mLeptonTree["highEtEleTrig"]=0;
  mLeptonTree["kfak"]=0;



  //PDF
  mLeptonTree["id1"]=999;
  mLeptonTree["id2"]=999;
  mLeptonTree["x1"]=999;
  mLeptonTree["x2"]=999;
  mLeptonTree["qscale"]=-1;

  //general
  mLeptonTree["ThisWeight"]=0;
  mLeptonTree["lepton_type"]=0;

  helper->Tree_Creater( &mLeptonTree, "slimtree");

  mQCDTree["lepton_n"]=0;
  mQCDTree["pt"]=0;
  mQCDTree["mt"]=0;
  mQCDTree["eta"]=0;
  mQCDTree["met"]=0;
  mQCDTree["iso"]=0;
  mQCDTree["nvert"]=0;
  mQCDTree["mtpos"]=0;
  mQCDTree["mtneg"]=0;
  mQCDTree["delta_phi"]=0;
  mQCDTree["ThisWeight"]=0;
  mQCDTree["QCDWeight"]=0;
  mQCDTree["lepton_type"]=0;
  mQCDTree["decay_mode"]=0;
  mQCDTree["metTriggerd"]=0;

/*        if(m_do_complicated_tau_stuff){
            for(auto idisc : d_mydisc){
                mQCDTree[idisc]=0;
            }
        }
*/
  helper->Tree_Creater( &mQCDTree, "qcdtree");
}


void MiniAODAnalyzer::Fill_Tree(TLorentzVector sel_lepton, const pat::MET sel_met){

    mLeptonTree["bjet1"]=0;
    mLeptonTree["mt"]=MT(sel_lepton,sel_met);
    mLeptonTree["delta_phi"]=deltaPhi(part1.Phi(),part2.phi());
    mLeptonTree["pt"]=sel_lepton->Pt();
    mLeptonTree["met"]=sel_met->pt();
    mLeptonTree["lepton_phi"]=sel_lepton->Phi();
    /*mLeptonTree["lepton_eta"]=sel_lepton->Eta();
    mLeptonTree["met_phi"]=sel_met->getPhi();
    mLeptonTree["kfak"]=k_fak_stored;
    if(JetList->size()>0){
        pxl::Particle* jet = (pxl::Particle*) JetList->at(0);
        mLeptonTree["jet1_et"]=jet->getPt();
        mLeptonTree["jet1_phi"]=jet->getPhi();
        mLeptonTree["jet1_eta"]=jet->getEta();
        if(jet->getUserRecord("pfCombinedInclusiveSecondaryVertexV2BJetTags").toDouble()>0.814 && mLeptonTree["bjet1"]==0)
            mLeptonTree["bjet1"]=jet->getPt();
    }else{
        mLeptonTree["jet1_et"]=-1;
        mLeptonTree["jet1_phi"]=99;
        mLeptonTree["jet1_eta"]=99;

    }
    //PDF
    if( not runOnData ){
        mLeptonTree["id1"]=m_GenEvtView->getUserRecord("f1");
        mLeptonTree["id2"]=m_GenEvtView->getUserRecord("f2");
        mLeptonTree["x1"]=m_GenEvtView->getUserRecord("x1");
        mLeptonTree["x2"]=m_GenEvtView->getUserRecord("x2");
        mLeptonTree["qscale"]=m_GenEvtView->getUserRecord("Q");
    }
    //general
    mLeptonTree["ThisWeight"]=weight;
    //mLeptonTree["lepton_type"]=sel_lepton->getUserRecord("id");
    mLeptonTree["lepton_type"]=sel_lepton->getPdgNumber();
    if(abs(sel_lepton->getPdgNumber())==11){
        mLeptonTree["highEtEleTrig"]=highEtTriggStored;
    }else{
        mLeptonTree["highEtEleTrig"]=0;
    }*/
    //helper.Tree_Filler("slimtree");
}

void MiniAODAnalyzer::Fill_QCD_Tree(bool iso){

    // testing stuff
    if(iso){
        mQCDTree["lepton_n"]=3;
    }
    else{
        mQCDTree["lepton_n"]=2;
    }
    helper->Tree_Filler("qcdtree");


    /*

    if(iso){
        mQCDTree["lepton_n"]=0;
        mQCDTree["iso"]=iso;
        mQCDTree["ThisWeight"]=weight;
        mQCDTree["QCDWeight"]=qcd_weight;
        mQCDTree["met"]=sel_met->getPt();
        mQCDTree["pt"]=sel_lepton->getPt();
        mQCDTree["mt"]=MT(sel_lepton,sel_met);
        mQCDTree["eta"]=sel_lepton->getEta();
        mQCDTree["delta_phi"]=DeltaPhi(sel_lepton,sel_met);
        mQCDTree["nvert"]=m_RecEvtView->getUserRecord("NumVertices");
        if (sel_lepton->getCharge() > 0){
            mQCDTree["mtpos"]=MT(sel_lepton,sel_met);
        }
        if (sel_lepton->getCharge() < 0){
            mQCDTree["mtneg"]=MT(sel_lepton,sel_met);
        }
        if(abs(sel_lepton->getPdgNumber())==15){
            mQCDTree["metTriggerd"]=sel_lepton->getUserRecord("metTriggered").toBool();
        }
        else{
            mQCDTree["metTriggerd"]=0;
        }
        if(sel_lepton->hasUserRecord("decayMode")){
            mQCDTree["decay_mode"]=sel_lepton->getUserRecord("decayMode").toDouble();
        }else{
            mQCDTree["decay_mode"]=-1;
        }
        if(abs(sel_lepton->getPdgNumber())==15 && m_do_complicated_tau_stuff){
            for(auto idisc : d_mydisc){
                mQCDTree[idisc]=sel_lepton->getUserRecord(idisc).toDouble();
            }

        }
        MiniAODAnalyzer::Tree_Filler("qcdtree");
    }else{
        int i=0;
        for(auto thisQCDlepton : QCDLeptonList){
            mQCDTree["lepton_n"]=i;
            i++;
            mQCDTree["iso"]=iso;
            mQCDTree["ThisWeight"]=weight;
            mQCDTree["QCDWeight"]=qcd_weight;
            mQCDTree["met"]=sel_met->getPt();
            mQCDTree["mt"]=MT(thisQCDlepton,sel_met);
            mQCDTree["pt"]=thisQCDlepton->getPt();
            mQCDTree["eta"]=thisQCDlepton->getEta();
            mQCDTree["delta_phi"]=DeltaPhi(thisQCDlepton,sel_met);
            mQCDTree["nvert"]=m_RecEvtView->getUserRecord("NumVertices");
            if (thisQCDlepton->getCharge() > 0){
                mQCDTree["mtpos"]=MT(thisQCDlepton,sel_met);
            }
            if (thisQCDlepton->getCharge() < 0){
                mQCDTree["mtneg"]=MT(thisQCDlepton,sel_met);
            }
            mQCDTree["lepton_type"]=thisQCDlepton->getPdgNumber();
            if(abs(thisQCDlepton->getPdgNumber())==15){
                if(thisQCDlepton->hasUserRecord("metTriggered")){
                    mQCDTree["metTriggerd"]=thisQCDlepton->getUserRecord("metTriggered").toBool();
                }else{
                    if(QCDLeptonList[0]->hasUserRecord("metTriggered")){
                        mQCDTree["metTriggerd"]=QCDLeptonList[0]->getUserRecord("metTriggered").toBool();
                    }else{
                        mQCDTree["metTriggerd"]=1.;
                    }
                }
            }else{
                mQCDTree["metTriggerd"]=0;
            }
            if(thisQCDlepton->hasUserRecord("decayMode")){
                mQCDTree["decay_mode"]=thisQCDlepton->getUserRecord("decayMode").toDouble();
            }else{
                mQCDTree["decay_mode"]=-1;
            }
            if(abs(thisQCDlepton->getPdgNumber())==15 && m_do_complicated_tau_stuff){
                for(auto idisc : d_mydisc){
                    mQCDTree[idisc]=thisQCDlepton->getUserRecord(idisc).toDouble();
                }
            }
            helper.Tree_Filler("qcdtree");
        }
    }
*/}


//double specialAna::MT(pxl::Particle* lepton, pxl::Particle* met) {
    //double mm = 2 * lepton->getPt() * met->getPt() * ( 1. - cos(lepton->getPhi() - met->getPhi()) );
    //return sqrt(mm);
//}
/*
 * get gen variables from LHE header of miniAOD
 * gen mass of  w, save in variable,
 * so you can go as often through the event as you like,
 * without losing time
 * ht: gen level
 * ht: reco level
 *
 * */






//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODAnalyzer);
