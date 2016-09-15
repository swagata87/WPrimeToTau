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
#include "FWCore/Framework/interface/global/EDFilter.h"
#include "FWCore/Framework/interface/EDProducer.h"
//#include "PhysicsTools/HepMCCandAlgos/interface/PDFWeightsHelper.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
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
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include <string>
#include "TH1.h"
#include "TLorentzVector.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

// cant set lorentzvetor branch without this
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif
#ifdef __CINT__
#pragma link C++ class std::vector<float>+;
#endif

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

//class MiniAODAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
class MiniAODAnalyzer : public edm::EDAnalyzer {
public:
  explicit MiniAODAnalyzer(const edm::ParameterSet&);
  ~MiniAODAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  virtual void beginRun( edm::Run const &iRun, edm::EventSetup const &iSetup ) override;
  bool PassTauID(const pat::Tau &tau);
  bool PassTauID_NonIsolated(const pat::Tau &tau);
  bool PassTauAcceptance(TLorentzVector tau);
  bool FindTauIDEfficiency(const edm::Event&,TLorentzVector gen_p4);
  bool PassFinalCuts(int nGoodTau_, double met_val_, double met_phi_, double tau_pt_, double tau_phi_);
  bool PassFinalCuts(TLorentzVector part1, const pat::MET part2, pat::MET::METUncertainty metUncert);
  bool PassFinalCuts(TLorentzVector part1, const pat::MET part2);
  bool PassFinalCuts(int nGoodTau_,TLorentzVector part1, const pat::MET part2);


  std::vector<int> pdf_indices;
  std::vector<double> inpdfweights;

  //new additions
  virtual void Create_Trees();
  virtual void Fill_Tree(TLorentzVector sel_lepton, const pat::MET sel_met,double weight, std::string systematic);
  virtual void Fill_QCD_Tree(bool iso,TLorentzVector sel_lepton, const pat::MET sel_met, double weight);

  std::unordered_map< std::string,float > mLeptonTree;
  std::unordered_map< std::string,float > mReweightTree;
  std::unordered_map< std::string,float > mQCDTree;
  std::unordered_map< std::string,float > mFakeTree;
  std::unordered_map< std::string,std::vector<float> > mFakeVectorTree;
  //std::unordered_map< std::string,float > mFakeVectorTree;
  edm::Service<TFileService> fs;
  Helper* helper =new Helper(fs);


  //MT addition
  double calcMT(TLorentzVector part1, TLorentzVector part2);
  double calcMT(TLorentzVector part1, const pat::MET part2);
  double calcMT(TLorentzVector part1, const pat::MET part2, pat::MET::METUncertainty metUncert);
  double calcMT(const pat::Electron part1, const pat::MET part2);
  double calcMT(const pat::Muon part1, const pat::MET part2);
  double calcMT(const pat::Tau part1, const pat::MET part2);

  std::unordered_map< std::string,pat::MET::METUncertainty > mSyst;
  std::unordered_map< std::string,TH1D* > mSystHist;
  std::unordered_map< std::string,std::string > mSystName;
  virtual void SetSystMap();

  //deltaR calculation
  double DeltaR(auto part ,auto tau);
  double DeltaR(pat::Electron part ,pat::Tau tau);
  double DeltaR(pat::Muon part,pat::Tau tau);

  //deltaPhi calculation
  double DeltaPhi(pat::Electron part1, pat::MET part2);
  double DeltaPhi(pat::Muon part1, pat::MET part2);
  double DeltaPhi(pat::Tau part1, pat::MET part2);

  //kfactor
  double applyWKfactor(int mode,edm::Handle<edm::View<reco::GenParticle>> genPart);
  std::string KFactorE_;
  std::string KFactorMu_;
  std::string KFactorTau_;
  TFile* m_kfactorFile_ele;
  TFile* m_kfactorFile_muo;
  TFile* m_kfactorFile_tau;
  TH1D* m_kfactorHist_ele[3];
  TH1D* m_kfactorHist_muo[3];
  TH1D* m_kfactorHist_tau[3];
  std::string sourceFileString;
  double WtoInt;
  double WJetsInt;
  int getWdecay(edm::Handle<edm::View<reco::GenParticle>> genPart);
  double getWmass(edm::Handle<edm::View<reco::GenParticle>> genPart);
  double wmass_stored;
  double k_fak_stored;

  //discriminators
  std::vector<std::string> d_mydisc;
  //QCD stuff
  void QCDAnalyse();
  //void QCDAnalyseTau(edm::Handle<std::vector<pat::Muon> >*list, edm::Handle<std::vector<pat::Tau> >*tauList);
  //void QCDAnalyseTau(std::vector<pat::Electron> EleList,std::vector<pat::Muon> MuonList, std::vector<pat::Tau> tauList,const pat::MET sel_met,double weight,edm::Handle<edm::View<reco::GenParticle>> genPart);
  //void QCDAnalyseTau(std::vector<pat::Electron> EleList,std::vector<pat::Muon> MuonList, std::vector<pat::Tau> tauList,const pat::MET sel_met,double weight);
  ///test
  edm::Handle<pat::MuonCollection> muons;
  edm::Handle<pat::ElectronCollection> electrons;
  edm::Handle<pat::TauCollection> taus;
  edm::Handle<edm::View<reco::GenParticle> > pruned; ///might not work for data
  //reco::GenParticle* GetTruthMatch(std::string name, pat::Tau lepton);
  reco::GenParticle* GetTruthMatch(std::string name, auto lepton);
  reco::GenParticle* GetTruthMatchAllFlavor(auto lepton);
  std::map< pat::Tau*,reco::GenParticle* > tauGenMatchMapAllFlav;
  std::map< pat::Tau*,reco::GenParticle* > tauGenMatchMap;
  //pat::Electron GetTruthElectron(int part_temp_id, auto lepton);
  //pat::Muon GetTruthMuon(int part_temp_id, auto lepton);
  //pat::Tau GetTruthTau(int part_temp_id, auto lepton);
  ///rest qcd stuff
  //void QCDAnalyseTau(const pat::MET sel_met,double weight);
  void QCDAnalyseTau(const pat::MET sel_met,double weight,edm::Handle<edm::View<reco::GenParticle>> genPart);
  int vetoNumberEle(double ptTreshold,double vetoConeSize);
  int vetoNumberMuon(double ptTreshold,double vetoConeSize);
  int vetoNumberTau(double ptTreshold);
  std::vector<int> EleIDPassed;
  std::vector<int> MuonIDPassed;
  std::vector<float> FakeCandPt;
  std::vector<float> FakeCandPhi;
  std::vector<float> FakeCandEta;
  std::vector<float> FakeCandMt;
  std::vector<float> FakeCandDeltaPhi;
  std::vector<float> FakeCandMET;
  std::vector<float> FakeCandMETPhi;
  std::vector<float> FakeCandIso;
  std::vector<float> FakeCandNoIso;
  std::vector<float> FakeCandVetoNum;
  std::vector<float> FakeCandDecayMode;
  std::vector<float> FakeCandLeptonType;
  std::vector<float> FakeCandLeptonMt;
  std::vector<float> FakeCandLeptonDeltaPhi;
  std::vector<float> FakeCandLeptonPt;
  std::vector<float> FakeCandLeptonEta;
  std::vector<float> FakeCandLeptonPhi;
  std::vector<float> FakeCandLeptonTrigger;

  std::vector<TLorentzVector> FakeCandLorentz;
  //trigger for ele + muon
  bool passEleTrig;
  bool passMuonTrig;

  //reweighting stuff
  bool useReweighting;
  void setShiftedTree(TLorentzVector sel_lepton, const pat::MET sel_met,double weight, pat::MET::METUncertainty metUncert);
  void setShiftedTree(TLorentzVector sel_lepton, const pat::MET sel_met, double weight);

  // ----------member data ---------------------------
  edm::LumiReWeighting LumiWeights_;
  edm::LumiReWeighting LumiWeights_UP_;
  edm::LumiReWeighting LumiWeights_DOWN_;
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
  edm::EDGetTokenT<bool> BadChCandFilterToken_;
  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;
  edm::EDGetTokenT<LHEEventProduct> LHEEventToken_;
  edm::EDGetTokenT<LHERunInfoProduct> LHERunInfoToken_;


  //------//
  TFile*  rootFile_;
  std::string outputFile_; // output file
  std::string pdfName_;
  //  std::string lheString = "source" ; //  "externalLHEProducer" ;
  std::string lheString =  "externalLHEProducer" ;
  std::string pileupMC_ ;
  std::string pileupData_ ;
  std::string pileupData_UP_ ;
  std::string pileupData_DOWN_ ;
  std::string pdfid_1;
  std::string pdfid_2;
  std::string tag_;

  bool RunOnData;
  bool doPDFuncertainty;
  std::string generatorName_;
  int debugLevel;
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
  TH1D *h1_MT_Stage1_pileupUncertUp;
  TH1D *h1_MT_Stage1_pileupUncertDown;
  TH1D *h1_MT_Stage1_pdfUncertUp;
  TH1D *h1_MT_Stage1_pdfUncertDown;
  TH1D *h1_MT_Stage1_kFactorUp;
  TH1D *h1_MT_Stage1_kFactorDown;

  ///crosscheck
  TH1D *h1_MT_Stage1_metUncert_JetEnUp_new;
  TH1D *h1_MT_Stage1_metUncert_JetEnDown_new;
  TH1D *h1_MT_Stage1_metUncert_JetResUp_new;
  TH1D *h1_MT_Stage1_metUncert_JetResDown_new;
  TH1D *h1_MT_Stage1_metUncert_MuonEnUp_new;
  TH1D *h1_MT_Stage1_metUncert_MuonEnDown_new;
  TH1D *h1_MT_Stage1_metUncert_ElectronEnUp_new;
  TH1D *h1_MT_Stage1_metUncert_ElectronEnDown_new;
  TH1D *h1_MT_Stage1_metUncert_TauEnUp_new;
  TH1D *h1_MT_Stage1_metUncert_TauEnDown_new;
  TH1D *h1_MT_Stage1_metUncert_PhotonEnUp_new;
  TH1D *h1_MT_Stage1_metUncert_PhotonEnDown_new;
  TH1D *h1_MT_Stage1_metUncert_UnclusteredEnUp_new;
  TH1D *h1_MT_Stage1_metUncert_UnclusteredEnDown_new;
  TH1D *h1_MT_Stage1_TauScaleUp_new;
  TH1D *h1_MT_Stage1_TauScaleDown_new;
  TH1D *h1_MT_Stage1_metUncert_JetEnUp_diff;
  TH1D *h1_MT_Stage1_metUncert_JetEnDown_diff;
  TH1D *h1_MT_Stage1_metUncert_JetResUp_diff;
  TH1D *h1_MT_Stage1_metUncert_JetResDown_diff;
  TH1D *h1_MT_Stage1_metUncert_MuonEnUp_diff;
  TH1D *h1_MT_Stage1_metUncert_MuonEnDown_diff;
  TH1D *h1_MT_Stage1_metUncert_ElectronEnUp_diff;
  TH1D *h1_MT_Stage1_metUncert_ElectronEnDown_diff;
  TH1D *h1_MT_Stage1_metUncert_TauEnUp_diff;
  TH1D *h1_MT_Stage1_metUncert_TauEnDown_diff;
  TH1D *h1_MT_Stage1_metUncert_PhotonEnUp_diff;
  TH1D *h1_MT_Stage1_metUncert_PhotonEnDown_diff;
  TH1D *h1_MT_Stage1_metUncert_UnclusteredEnUp_diff;
  TH1D *h1_MT_Stage1_metUncert_UnclusteredEnDown_diff;
  TH1D *h1_MT_Stage1_TauScaleUp_diff;
  TH1D *h1_MT_Stage1_TauScaleDown_diff;
  ///crosscheck end

  TH1D *h1_recoVtx_NoPUWt;
  TH1D *h1_recoVtx_WithPUWt;
  //
  //-- These 100 histograms needed for PDF uncertainty --//
  TH1F *h1_MT_Stage1_pdfWt[100];
  char *histname_MT = new char[60];
  int nbinMT=2000;
  int xlowMT=0;
  int xupMT=2000;
  //
  int Run;
  double final_weight=1;
  double final_weight_PUweight_UP=1;
  double final_weight_PUweight_DOWN=1;
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
  BadChCandFilterToken_(consumes<bool>(iConfig.getParameter<edm::InputTag>("BadChargedCandidateFilter"))),
  BadPFMuonFilterToken_(consumes<bool>(iConfig.getParameter<edm::InputTag>("BadPFMuonFilter"))),
  LHEEventToken_( consumes<LHEEventProduct>( iConfig.getParameter<edm::InputTag>( "LHEEventTag" ))),
  //  LHERunInfoToken_( consumes<LHERunInfoProduct,edm::InRun> ( iConfig.getParameter<edm::InputTag>( "LHEEventTag" ))),
  LHERunInfoToken_( consumes<LHERunInfoProduct,edm::InRun> (edm::InputTag("externalLHEProducer"))),
  //  LHERunInfoToken_( consumes<LHERunInfoProduct,edm::InRun> (edm::InputTag("source"))),
  outputFile_(iConfig.getParameter<std::string>("outputFile")),
  pdfName_(iConfig.getParameter<std::string>("pdfName")),
  tag_(iConfig.getUntrackedParameter<std::string>( "tag", "initrwgt" )),
  RunOnData(iConfig.getParameter<bool>("RunOnData_")),
  doPDFuncertainty(iConfig.getParameter<bool>("doPDFuncertainty_")),
  generatorName_(iConfig.getParameter<std::string>("generatorName")),
  debugLevel(iConfig.getParameter<int>("debugLevel_"))
{
   //now do what ever initialization is needed
  //usesResource("TFileService");
  pileupMC_ = iConfig.getParameter<std::string>("PileupMCFile") ;
  pileupData_ = iConfig.getParameter<std::string>("PileupDataFile") ;
  pileupData_UP_ = iConfig.getParameter<std::string>("PileupDataFile_UP") ;
  pileupData_DOWN_ = iConfig.getParameter<std::string>("PileupDataFile_DOWN") ;
  KFactorE_ = iConfig.getParameter<std::string>("KFactorE") ;
  KFactorMu_ = iConfig.getParameter<std::string>("KFactorMu") ;
  KFactorTau_ = iConfig.getParameter<std::string>("KFactorTau") ;
  sourceFileString=iConfig.getParameter<std::string>("sourceFileString");
  useReweighting=iConfig.getParameter<bool>("useReweighting");
  rootFile_   = TFile::Open(outputFile_.c_str(),"RECREATE"); // open output file to store histograms
  TFileDirectory histoDir = fs->mkdir("histoDir");
  TFileDirectory crossDir = fs->mkdir("crossDir");

  /////  if (isPowheg) lheString = "source" ;
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
  h1_MT_Stage1 = histoDir.make<TH1D>("mT_Stage1", "MT_Stage1", nbinMT, xlowMT, xupMT);
  h1_MT_RegA_Stage1 = histoDir.make<TH1D>("mT_RegA_Stage1", "MT_RegA_Stage1", nbinMT, xlowMT, xupMT);
  h1_MT_RegC_Stage1 = histoDir.make<TH1D>("mT_RegC_Stage1", "MT_RegC_Stage1", nbinMT, xlowMT, xupMT);
  h1_MT_GenMatchedTau_RegC_Stage1 = histoDir.make<TH1D>("mT_GenMatchedTau_RegC_Stage1", "MT_GenMatchedTau_RegC_Stage1", nbinMT, xlowMT, xupMT);
  h1_MT_RegD_Stage1 = histoDir.make<TH1D>("mT_RegD_Stage1", "MT_RegD_Stage1", nbinMT, xlowMT, xupMT);
  h1_MT_GenMatchedTau_RegD_Stage1 = histoDir.make<TH1D>("mT_GenMatchedTau_RegD_Stage1", "MT_GenMatchedTau_RegD_Stage1", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_JetEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_JetEnUp", "MT_Stage1_metUncert_JetEnUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_JetEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_JetEnDown", "MT_Stage1_metUncert_JetEnDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_JetResUp = histoDir.make<TH1D>("mT_Stage1_metUncert_JetResUp", "MT_Stage1_metUncert_JetResUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_JetResDown = histoDir.make<TH1D>("mT_Stage1_metUncert_JetResDown", "MT_Stage1_metUncert_JetResDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_MuonEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_MuonEnUp", "MT_Stage1_metUncert_MuonEnUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_MuonEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_MuonEnDown", "MT_Stage1_metUncert_MuonEnDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_ElectronEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnUp", "MT_Stage1_metUncert_ElectronEnUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_ElectronEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnDown", "MT_Stage1_metUncert_ElectronEnDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_TauEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_TauEnUp", "MT_Stage1_metUncert_TauEnUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_TauEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_TauEnDown", "MT_Stage1_metUncert_TauEnDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_PhotonEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnUp", "MT_Stage1_metUncert_PhotonEnUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_PhotonEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnDown", "MT_Stage1_metUncert_PhotonEnDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_UnclusteredEnUp = histoDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnUp", "MT_Stage1_metUncert_UnclusteredEnUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_metUncert_UnclusteredEnDown = histoDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnDown", "MT_Stage1_metUncert_UnclusteredEnDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_TauScaleUp = histoDir.make<TH1D>("mT_Stage1_TauScaleUp", "MT_Stage1_TauScaleUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_TauScaleDown = histoDir.make<TH1D>("mT_Stage1_TauScaleDown", "MT_Stage1_TauScaleDown", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_pileupUncertUp = histoDir.make<TH1D>("mT_Stage1_pileupUncertUp", "MT_Stage1_pileupUncertUp", nbinMT, xlowMT, xupMT);
  h1_MT_Stage1_pileupUncertDown =histoDir.make<TH1D>("mT_Stage1_pileupUncertDown", "MT_Stage1_pileupUncertDown", nbinMT, xlowMT, xupMT);
  if ( doPDFuncertainty ) {
    h1_MT_Stage1_pdfUncertUp = histoDir.make<TH1D>("mT_Stage1_pdfUncertUp", "MT_Stage1_pdfUncertUp", nbinMT, xlowMT, xupMT);
    h1_MT_Stage1_pdfUncertDown =histoDir.make<TH1D>("mT_Stage1_pdfUncertDown", "MT_Stage1_pdfUncertDown", nbinMT, xlowMT, xupMT);
  }
  ///crosscheck
  h1_MT_Stage1_metUncert_JetEnUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_JetEnUp_new", "MT_Stage1_metUncert_JetEnUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_JetEnDown_new", "MT_Stage1_metUncert_JetEnDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_JetResUp_new", "MT_Stage1_metUncert_JetResUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_JetResDown_new", "MT_Stage1_metUncert_JetResDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_MuonEnUp_new", "MT_Stage1_metUncert_MuonEnUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_MuonEnDown_new", "MT_Stage1_metUncert_MuonEnDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnUp_new", "MT_Stage1_metUncert_ElectronEnUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnDown_new", "MT_Stage1_metUncert_ElectronEnDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_TauEnUp_new", "MT_Stage1_metUncert_TauEnUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_TauEnDown_new", "MT_Stage1_metUncert_TauEnDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnUp_new", "MT_Stage1_metUncert_PhotonEnUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnDown_new", "MT_Stage1_metUncert_PhotonEnDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnUp_new = crossDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnUp_new", "MT_Stage1_metUncert_UnclusteredEnUp_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnDown_new = crossDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnDown_new", "MT_Stage1_metUncert_UnclusteredEnDown_new", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleUp_new = crossDir.make<TH1D>("mT_Stage1_TauScaleUp_new", "MT_Stage1_TauScaleUp_new", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleDown_new = crossDir.make<TH1D>("mT_Stage1_TauScaleDown_new", "MT_Stage1_TauScaleDown_new", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_JetEnUp_diff", "MT_Stage1_metUncert_JetEnUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetEnDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_JetEnDown_diff", "MT_Stage1_metUncert_JetEnDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_JetResUp_diff", "MT_Stage1_metUncert_JetResUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_JetResDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_JetResDown_diff", "MT_Stage1_metUncert_JetResDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_MuonEnUp_diff", "MT_Stage1_metUncert_MuonEnUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_MuonEnDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_MuonEnDown_diff", "MT_Stage1_metUncert_MuonEnDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnUp_diff", "MT_Stage1_metUncert_ElectronEnUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_ElectronEnDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_ElectronEnDown_diff", "MT_Stage1_metUncert_ElectronEnDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_TauEnUp_diff", "MT_Stage1_metUncert_TauEnUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_TauEnDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_TauEnDown_diff", "MT_Stage1_metUncert_TauEnDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnUp_diff", "MT_Stage1_metUncert_PhotonEnUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_PhotonEnDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_PhotonEnDown_diff", "MT_Stage1_metUncert_PhotonEnDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnUp_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnUp_diff", "MT_Stage1_metUncert_UnclusteredEnUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_metUncert_UnclusteredEnDown_diff = crossDir.make<TH1D>("mT_Stage1_metUncert_UnclusteredEnDown_diff", "MT_Stage1_metUncert_UnclusteredEnDown_diff", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleUp_diff = crossDir.make<TH1D>("mT_Stage1_TauScaleUp_diff", "MT_Stage1_TauScaleUp_diff", 2000, 0, 2000);
  h1_MT_Stage1_TauScaleDown_diff = crossDir.make<TH1D>("mT_Stage1_TauScaleDown_diff", "MT_Stage1_TauScaleDown_diff", 2000, 0, 2000);
  ///crosscheck
    ///qcd histos
  int nstages=8;
  helper->CreateHisto(nstages,"Tau_fake_pt",  5000, 0, 5000, "p_{T} [GeV]");
  helper->CreateHisto(nstages,"Tau_nofake_pt",  5000, 0, 5000, "p_{T} [GeV]");
  helper->CreateHisto("Tau_fake_pt_decay", 500, 0, 5000, 20, 0, 20, "p_{T} [GeV]", "decay mode");
  helper->CreateHisto("Tau_nofake_pt_decay", 500, 0, 5000, 20, 0, 20, "p_{T} [GeV]", "decay mode");
  helper->CreateHisto("Tau_fake_pt_eta", 500, 0, 5000, 20, -5, 5, "p_{T} [GeV]", "eta");
  helper->CreateHisto("Tau_nofake_pt_eta", 500, 0, 5000, 20, -5, 5, "p_{T} [GeV]", "eta");
  helper->CreateHisto("Tau_fake_pt_met", 500, 0, 5000, 500, 0, 5000, "p_{T} [GeV]", "MET");
  helper->CreateHisto("Tau_nofake_pt_met", 500, 0, 5000, 500, 0, 5000, "p_{T} [GeV]", "MET");
  helper->CreateHisto(nstages,"Tau_fake_pt_true",  5000, 0, 5000, "p_{T} [GeV]");
  helper->CreateHisto(nstages,"Tau_nofake_pt_true",  5000, 0, 5000, "p_{T} [GeV]");
  helper->CreateHisto("Tau_fake_pt_decay_true", 500, 0, 5000, 20, 0, 20, "p_{T} [GeV]", "decay mode");
  helper->CreateHisto("Tau_nofake_pt_decay_true", 500, 0, 5000, 20, 0, 20, "p_{T} [GeV]", "decay mode");
  helper->CreateHisto("Tau_fake_pt_eta_true", 500, 0, 5000, 20, -5, 5, "p_{T} [GeV]", "eta");
  helper->CreateHisto("Tau_nofake_pt_eta_true", 500, 0, 5000, 20, -5, 5, "p_{T} [GeV]", "eta");
  helper->CreateHisto("Tau_fake_pt_met_true", 500, 0, 5000, 500, 0, 5000, "p_{T} [GeV]", "MET");
  helper->CreateHisto("Tau_nofake_pt_met_true", 500, 0, 5000, 500, 0, 5000, "p_{T} [GeV]", "MET");
  if(not RunOnData){
      for(std::string gen : {"lightquark","gluon","bquark","lightlepton","unmatched"}){
          helper->CreateHisto(nstages,Form("Tau_fake_pt_%s",gen.c_str()),  5000, 0, 5000, "p_{T} [GeV]");
          helper->CreateHisto(nstages,Form("Tau_nofake_pt_%s",gen.c_str()),  5000, 0, 5000, "p_{T} [GeV]");
      }
  }

  ///k-factor
  m_kfactorFile_ele= new TFile(KFactorE_.c_str(),"READ");
  m_kfactorHist_ele[0] = (TH1D*) m_kfactorFile_ele->Get("k_fac_p");
  m_kfactorHist_ele[1] = (TH1D*) m_kfactorFile_ele->Get("k_fac_m");
  m_kfactorHist_ele[2] = (TH1D*) m_kfactorFile_ele->Get("k_fac_mean");

  m_kfactorFile_muo= new TFile(KFactorMu_.c_str(),"READ");
  m_kfactorHist_muo[0] = (TH1D*) m_kfactorFile_muo->Get("k_fac_p");
  m_kfactorHist_muo[1] = (TH1D*) m_kfactorFile_muo->Get("k_fac_m");
  m_kfactorHist_muo[2] = (TH1D*) m_kfactorFile_muo->Get("k_fac_mean");

  m_kfactorFile_tau= new TFile(KFactorTau_.c_str(),"READ");
  m_kfactorHist_tau[0] = (TH1D*) m_kfactorFile_tau->Get("k_fac_p");
  m_kfactorHist_tau[1] = (TH1D*) m_kfactorFile_tau->Get("k_fac_m");
  m_kfactorHist_tau[2] = (TH1D*) m_kfactorFile_tau->Get("k_fac_mean");

  // discriminators
  d_mydisc= {
        "byLooseCombinedIsolationDeltaBetaCorr3Hits",
        "byMediumCombinedIsolationDeltaBetaCorr3Hits",
        "byPhotonPtSumOutsideSignalCone",
        "byTightCombinedIsolationDeltaBetaCorr3Hits",
    };

  h1_recoVtx_NoPUWt = histoDir.make<TH1D>("recoVtx_NoPUWt", "RecoVtx_NoPUWt", 100, 0, 100);
  h1_recoVtx_WithPUWt = histoDir.make<TH1D>("recoVtx_WithPUWt", "RecoVtx_WithPUWt", 100, 0, 100);

  //
  if ( doPDFuncertainty ) {
    //  std::cout << "Will initialize 100 MT histograms for different pdf weights " << std::endl;
    for (int i=0; i<100; i++) {
      //std::cout << "Initialize hist " << i << std::endl;
      sprintf(histname_MT,"mT_Stage1_pdfWt_%d",i);
      h1_MT_Stage1_pdfWt[i] = new TH1F(histname_MT,"",nbinMT, xlowMT, xupMT);
    }
  }
  if (!RunOnData) {
    LumiWeights_ = edm::LumiReWeighting(pileupMC_, pileupData_, "pileup", "pileup");
    LumiWeights_UP_ = edm::LumiReWeighting(pileupMC_, pileupData_UP_, "pileup", "pileup");
    LumiWeights_DOWN_ = edm::LumiReWeighting(pileupMC_, pileupData_DOWN_, "pileup", "pileup");
  }
}


MiniAODAnalyzer::~MiniAODAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  delete rootFile_;

  if ( doPDFuncertainty ) {
    for (unsigned int i=0; i<100; i++) {
      delete h1_MT_Stage1_pdfWt[i];
    }
  }
}

//
// member functions
//

void MiniAODAnalyzer::beginRun( edm::Run const &iRun, edm::EventSetup const &iSetup ) {
  //std::cout << "Inside beginRun()" << std::endl;
  pdf_indices.clear();

  if (!RunOnData ) {
    if ( doPDFuncertainty) {

      //std::cout << "RunOnData=" << RunOnData << std::endl;
      edm::Handle<LHERunInfoProduct> run;
      typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;
      iRun.getByLabel( lheString , run );
      if ( run.isValid()) {
    std::cout << "Take pdf weights from CMSSW" << std::endl;
    LHERunInfoProduct myLHERunInfoProduct = *(run.product());
        std::vector<std::string> weight_lines;
    for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++){
      // if (debugLevel<1) std::cout << "TAG " << iter->tag() << std::endl;
      std::vector<std::string> lines = iter->lines();
      if( ( iter->tag() ).compare( tag_ ) == 0 ) {
        weight_lines = iter->lines();
        //  std::cout << iter->lines() << std::endl;
      }
      if (debugLevel>3) {
        for (unsigned int iLine = 0; iLine<lines.size(); iLine++) {
          std::cout   << "LINE " << lines.at(iLine);
        }
      }
    }
    int pdfidx = 0;
    pdfidx = run->heprup().PDFSUP.first;
    if (generatorName_=="powheg" && pdfidx==-1) pdfidx=260000;
    //std::cout << "This sample was generated with the following PDFs : "   << pdfidx <<   std::endl;
    pdfid_1 = boost::lexical_cast<std::string>(pdfidx + 1);
    pdfid_2 = boost::lexical_cast<std::string>(pdfidx + 100);
    //      std::cout << "PDF min and max id for MC replicas: " << pdfid_1 << "   " << pdfid_2 << std::endl;
    //std::cout << "size=" << weight_lines.size() << std::endl;
    std::stringstream ss;
    std::copy(weight_lines.begin(), weight_lines.end(),std::ostream_iterator<std::string>(ss,""));
    //cout << ss.str()<<endl;
    boost::property_tree::ptree pt;
    read_xml( ss , pt);

    // --- Name of the weightgroup
    //  string scalevar = "scale_variation";
    std::string pdfvar="";
    if (generatorName_=="powheg") {
      pdfvar = "PDF_variation";
    }
    else if (generatorName_=="madgraphMLM") {
      pdfvar = pdfName_;
    }

    if( (generatorName_=="madgraphMLM") && (pdfidx==263000) && (pdfvar != "NNPDF30_lo_as_0130.LHgrid") )
      throw cms::Exception("WrongPDFname")
        << "Wrong pdf name provided. ID=" << pdfidx << " NAME=" << pdfvar   ;

    if( (generatorName_=="madgraphMLM") && (pdfidx != 263000) && (pdfvar == "NNPDF30_lo_as_0130.LHgrid") )
      throw cms::Exception("WrongPDFname")
        << "Wrong pdf name provided. ID=" << pdfidx << " NAME=" << pdfvar   ;
    //      std::cout << "generatorName_=" << generatorName_ << " pdfvar=" << pdfvar << std::endl;

    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, pt.get_child("") ) {
      //std::cout << "v.first=" << v.first  << std::endl;

      if (v.first == "weightgroup"){
        boost::property_tree::ptree subtree = (boost::property_tree::ptree) v.second ;

        boost::optional<std::string> weightgroupname1 = v.second.get_optional<std::string>("<xmlattr>.name");
        boost::optional<std::string> weightgroupname2 = v.second.get_optional<std::string>("<xmlattr>.type");
        //std::cout << "weightgroupname1=" << weightgroupname1 << " weightgroupname2=" << weightgroupname2 << std::endl;
        if ( (weightgroupname1 && weightgroupname1.get() == pdfvar)  || (weightgroupname2 && weightgroupname2.get() == pdfvar)) {
          BOOST_FOREACH(boost::property_tree::ptree::value_type &vs,subtree) {
        //    std::cout << "vs.first=" << vs.first << " vs.second="  << vs.second << std::endl;
        if (vs.first == "weight") {
          //std::cout << vs.first <<  "   " << vs.second.get<std::string>("<xmlattr>.id")  << "  " << vs.second.data()<< std::endl;
          std::string strwid  = vs.second.get<std::string>("<xmlattr>.id");
          std::string strw    = vs.second.data();
          int id = stoi(strwid);
          std::vector<std::string> strs;
          if (generatorName_=="madgraphMLM") boost::split(strs, strw, boost::is_any_of(" "));
          if (generatorName_=="powheg") boost::split(strs, strw, boost::is_any_of("="));
          int pdf_wt_index  = 999;
          if (generatorName_=="powheg") {
            pdf_wt_index = stoi(strs.back());
          }
          else if (generatorName_=="madgraphMLM") {
            pdf_wt_index = pdfidx+ (stoi(strs.back())) +1 ;
          }
          //        std::cout << "id=" << id  << "  pdf_wt_index = " << pdf_wt_index << std::endl;
          if ( (pdf_wt_index >= stoi(pdfid_1) ) && (pdf_wt_index <= stoi(pdfid_2)) ){
            pdf_indices.push_back( id );
          }
        }
          }
        }
      }
    }
      }
      else {
    if (debugLevel>3)   std::cout << "PDF weights not saved in CMSSW. Do post-facto reweighting" << std::endl;
      }
    }
  }
}

// ------------ method called for each event  ------------
void MiniAODAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
  ////std::cout << "\n --EVENT-- " << Event << std::endl;


  //-- kfactor --//
  wmass_stored=0;
  //-- probValue --//
  //-- https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py --//
  //----------//
  //--PileUp--//
  //----------//
  int MC_TrueNumInteractions=-1;
  double Lumi_Wt=1;
  double Lumi_Wt_UP=1;
  double Lumi_Wt_DOWN=1;

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
    Lumi_Wt_UP = LumiWeights_UP_.weight( MC_TrueNumInteractions );
    Lumi_Wt_DOWN = LumiWeights_DOWN_.weight( MC_TrueNumInteractions );
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

  if ( doPDFuncertainty) {
    ///--PDF weight--///
    edm::Handle<LHEEventProduct> EvtHandle ;
    if  ( !(RunOnData) ) {
      iEvent.getByToken( LHEEventToken_ , EvtHandle ) ;
      if  ( (EvtHandle.isValid()) ) {
    std::cout << "Take pdf weights from CMSSW" << std::endl;
    inpdfweights.clear();

    //  if  ( !(RunOnData) && (EvtHandle.isValid()) ) {
    // std::cout << "\n\n wt for this evt :" <<  EvtHandle->originalXWGTUP() << " vect_size=" << EvtHandle->weights().size()  << std::endl ; // PDF weight of this event !
    //  std::string whichWeightId = "20";
    for (unsigned int i=0; i<EvtHandle->weights().size(); i++) {
      int id_i = stoi( EvtHandle->weights()[i].id );
      for( unsigned int j = 0; j<pdf_indices.size(); j++ ) {
        int id_j = pdf_indices[j];
        if( id_i == id_j ){
          float pdf_weight = (EvtHandle->weights()[i].wgt)/(EvtHandle->originalXWGTUP());
          //   std::cout << "pdf_weight=" << pdf_weight  << std::endl;
          inpdfweights.push_back( pdf_weight );
        }
      }

      // for (unsigned int i=0; i<101; i++) {
      //  std::cout << "id=" << EvtHandle->weights()[i].id  <<  " wt=" << EvtHandle->weights()[i].wgt/EvtHandle->originalXWGTUP() << std::endl;
      //if (EvtHandle->weights()[i].id == whichWeightId) std::cout << "id="  << EvtHandle->weights()[i].id << " wt=" << EvtHandle->weights()[i].wgt  << std::endl;
      // if (EvtHandle->weights()[i].id == "YYY") theWeight *= EvtHandle->weights()[i].wgt/EvtHandle->originalXWGTUP();
    }
      }
      else {
    if (debugLevel) std::cout << "PDF weights not saved in CMSSW. Do post-facto reweighting" << std::endl;
      }
    }
  }
  //----------------//
  //--Final Weight--//
  //----------------//
  if (!RunOnData) {
    final_weight               =Lumi_Wt*mc_event_weight;
    final_weight_PUweight_UP   =Lumi_Wt_UP*mc_event_weight;
    final_weight_PUweight_DOWN =Lumi_Wt_DOWN*mc_event_weight;

  }
  else {
    final_weight=1;
    final_weight_PUweight_UP=1;
    final_weight_PUweight_DOWN=1;
  }
  //  std::cout << "RunOnData=" << RunOnData << " final_weight=" << final_weight << std::endl;

  ///----///
  int nGenTau=0;
  TLorentzVector tauGen_p4[10];
  const Candidate * MyTau;
  // const Candidate * MyTauSel=0;
  double TauPt_Gen=0;

  k_fak_stored=1;
  if (!RunOnData) {
    //--GenParticles--//
    //Handle<edm::View<reco::GenParticle> > pruned;
    //std::cout << pruned <<
    iEvent.getByToken(prunedGenToken_,pruned);

    Handle<edm::View<pat::PackedGenParticle> > packed;
    iEvent.getByToken(packedGenToken_,packed);


    ///-- W k-factor --///
    k_fak_stored=applyWKfactor(1,pruned);
    //std::cout << k_fak_stored << std::endl;
    final_weight=final_weight*k_fak_stored;



    for(size_t i=0; i<pruned->size();i++){
        if(   (abs((*pruned)[i].pdgId())==15) && ( ((*pruned)[i].status()==2) )) {
            MyTau = &(*pruned)[i];
            if ( (MyTau->pt()>20.0)  &&  (fabs(MyTau->eta())<2.3)  )  {
                // MyTauSel=MyTau;
                TauPt_Gen=MyTau->pt();
                h1_TauPt_Gen->Fill(TauPt_Gen);
                tauGen_p4[nGenTau].SetPxPyPzE(MyTau->px(),MyTau->py(),MyTau->pz(),MyTau->energy());
                nGenTau++;
                //std::cout << " pt " << TauPt_Gen << " nMother=" << MyTau->numberOfMothers() << " mother pdgID = " << MyTau->mother(0)->pdgId() << " mother status = " << MyTau->mother(0)->status()  << std::endl;
                //const Candidate * MotherOfMyTau=MyTau->mother(0);
            }
        }
      }

      //if(   (abs((*pruned)[i].pdgId())==16) && ( ((*pruned)[i].status()==2)) && (sel_tau==true)) {
          //MyNu= &(*pruned)[i]; //used for calculating the W mass
          //MyNu->px(); // to get rid of not use warning
      //}

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
     if ( (names.triggerName(i)).find("HLT_Mu45_eta2p1_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_Mu50_eta2p1_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_Mu50_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_IsoMu24_eta2p1_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_IsoMu24_eta2p1_IterTrk02_v") != std::string::npos
     ) {
       passMuonTrig=triggerBits->accept(i) ;
     }
     if ( (names.triggerName(i)).find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_Ele105_CaloIdVT_GsfTrkIdT_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_Ele27_eta2p1_WP75_Gsf_v") != std::string::npos or
          (names.triggerName(i)).find("HLT_Ele27_eta2p1_WPLoose_Gsf_v") != std::string::npos
     ) {
       passEleTrig=triggerBits->accept(i) ;
     }
   }
   if (!RunOnData) passTauTrig=1;
   // std::cout << "RunOnData=" << RunOnData <<  " ## passTauTrig=" << passTauTrig << std::endl;

   //---Trigger MET---//
   edm::Handle<edm::TriggerResults> triggerBits_MET;
   iEvent.getByToken(triggerBits_MET_, triggerBits_MET);
   const edm::TriggerNames &names_MET = iEvent.triggerNames(*triggerBits_MET);

   bool passAllMETFilters=0;
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
   //  std::cout << "RunOnData=" << RunOnData <<  " ## passHBHENoiseFilter=" << passHBHENoiseFilter
   //        <<  " ## passHBHENoiseIsoFilter=" << passHBHENoiseIsoFilter
   //        << " ## passEcalDeadCellTriggerPrimitiveFilter=" << passEcalDeadCellTriggerPrimitiveFilter
   //        << " ## passgoodVertices=" << passgoodVertices
   //        << " ## passeeBadScFilter=" << passeeBadScFilter
   //        << " ## passglobalTightHalo2016Filter=" << passglobalTightHalo2016Filter << std::endl;


   //---MET FILTERS THAT ARE UNAVAILABLE IN MINIAOD AS FLAG---//
   edm::Handle<bool> ifilterbadChCand;
   iEvent.getByToken(BadChCandFilterToken_, ifilterbadChCand);
   bool  filterbadChCandidate = *ifilterbadChCand;
   //   if (filterbadChCandidate<1)   std::cout << "filterbadChCandidate=" << filterbadChCandidate << std::endl;

   edm::Handle<bool> ifilterbadPFMuon;
   iEvent.getByToken(BadPFMuonFilterToken_, ifilterbadPFMuon);
   bool filterbadPFMuon = *ifilterbadPFMuon;
   //  if (filterbadPFMuon<1)   std::cout << "filterbadPFMuon=" << filterbadPFMuon << std::endl;

   //Pass All MET Filters? //
   passAllMETFilters =  passHBHENoiseFilter * passHBHENoiseIsoFilter * passEcalDeadCellTriggerPrimitiveFilter * passgoodVertices * passeeBadScFilter * passglobalTightHalo2016Filter * filterbadChCandidate * filterbadPFMuon ;

   //   std::cout << "passAllMETFilters=" << passAllMETFilters << std::endl;

   ///-- VERTEX --///
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
   //edm::Handle<pat::MuonCollection> muons;  ///in header now
   iEvent.getByToken(muonToken_, muons);
   for (const pat::Muon &mu : *muons) {
     //https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon
     if ( (mu.pt()>20.0) &&  (abs(mu.eta())<2.4) && (mu.isTightMuon(PV)) &&  ((mu.isolationR03().sumPt/mu.pt())<0.10) ) {
         nTightMu++;
         MuonIDPassed.push_back(1);}
     else {MuonIDPassed.push_back(0);}
     //std::cout << "mu.pt()=" << mu.pt() << " abs(mu.eta())=" << abs(mu.eta()) << " mu.isolationR03().sumPt/mu.pt()=" << mu.isolationR03().sumPt/mu.pt() << std::endl;
     //       printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
     //     mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
   }
   //  std::cout << "nTightMu=" << nTightMu << std::endl;

   int nLooseEle=0;
   //   int nLooseEle_HighPt=0;
   //edm::Handle<pat::ElectronCollection> electrons;///in header now
   iEvent.getByToken(electronToken_, electrons);
   //   std::cout << "nEle = " << electrons->size() << std::endl;
   for (const pat::Electron &el : *electrons) {
     //std::cout <<      el.electronIDs().size() << std::endl;
     //std::cout <<      el.electronIDs().front().first << std::endl;
     if (el.pt() < 5) continue;
     //https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
     //std::cout << "ele pt " << el.pt() << " ele eta" << abs(el.eta()) << " ele id " << el.electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose") << std::endl;
     if ( (el.pt()>20) &&  ( abs(el.eta())<2.5 )  && (el.electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-loose")>6) ){
     //if ( (el.pt()>20) &&  ( abs(el.eta())<2.5 )  && (el.electronID("cutBasedElectronID-Summer16-80X-V1-loose")>6) ){
         nLooseEle++;
         EleIDPassed.push_back(1);}
     else {EleIDPassed.push_back(0);}
     //printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f  ",
     //      el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta()  );
   }
     //std::cout << "nLooseEle=" << nLooseEle << std::endl;

   //edm::Handle<pat::TauCollection> taus;///in header now
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

   if (passTauTrig && passAllMETFilters ) {
     if ( (nvtx>0) && (nTightMu==0) && (nLooseEle==0) ) {
       //** Stage1 = final stage (all cuts applied) **//
       if ( (PassFinalCuts(nGoodTau, met_val,met_phi,tau_pt[0],tau_phi[0]) == true) ) {
     h1_recoVtx_NoPUWt->Fill(recoVtx,mc_event_weight);
     h1_recoVtx_WithPUWt->Fill(recoVtx,final_weight);
     h1_TauPt_Stage1->Fill(tau_pt[0],final_weight);
     //std::cout << "*Standard* dphi_tau_met=" << dphi_tau_met << std::endl;
     double MT=  sqrt(2*tau_pt[0]*met_val*(1- cos(dphi_tau_met)));
     h1_MT_Stage1->Fill(MT,final_weight);
     //--PU Systematics--//
     h1_MT_Stage1_pileupUncertUp->Fill(MT,final_weight_PUweight_UP);
     h1_MT_Stage1_pileupUncertDown->Fill(MT,final_weight_PUweight_DOWN);

     if ( doPDFuncertainty) {
       //--PDF Systematics--//
       // std::cout << "Evt selected. Size of inpdfweights = " << inpdfweights.size() << std::endl;
       int imem=0;
       for (std::vector<double>::iterator it = inpdfweights.begin() ; it != inpdfweights.end(); ++it) {
         //std::cout << "weight = " << *it << std::endl;
         double final_wt_with_pdf = (*it)*final_weight;
         h1_MT_Stage1_pdfWt[imem]->Fill(MT,final_wt_with_pdf);
       //      std::cout << "final_wt_with_pdf " << final_wt_with_pdf << std::endl ;
         imem++;
       }
     }
       }
       //--Systematics--//
       if ( (PassFinalCuts(nGoodTau, met_val_JetEnUp,met_phi_JetEnUp,tau_pt[0],tau_phi[0] ) == true) ) {
             //std::cout << "*metUncert_JetEnUp* dphi_tau_met=" << dphi_tau_met << std::endl;
             double MT_metUncert_JetEnUp = sqrt(2*tau_pt[0]*met_val_JetEnUp*(1- cos(dphi_tau_met)));  // always use the same dphi? or shifted dphi?
             //double MT_metUncert_JetEnUp_test = calcMT(tau_NoShift,met,pat::MET::JetEnUp);
             //if (MT_metUncert_JetEnUp-MT_metUncert_JetEnUp_test != 0){
                 //std::cout << MT_metUncert_JetEnUp << " " << MT_metUncert_JetEnUp_test << " " << MT_metUncert_JetEnUp-MT_metUncert_JetEnUp_test << std::endl;
             //}
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

       ///testing new way to get systematics
       //std::cout << nGoodTau << std::endl;
       if (nGoodTau==1)  {
            for (int i=1;i<=14;i++){
                if ( (PassFinalCuts(tau_NoShift,met,mSyst[std::to_string(i)] ) == true) ) {
                 //std::cout << "*metUncert_JetEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
                 mSystHist[std::to_string(i)]->Fill(calcMT(tau_NoShift,met,mSyst[std::to_string(i)]),final_weight);
                 setShiftedTree(tau_NoShift, met, final_weight, mSyst[std::to_string(i)]);
               }
            }
            for (int i=15;i<=16;i++){
                double kFactorShift=1.;
                if (i==15){ kFactorShift=1.05;}
                else if (i==16){ kFactorShift=0.95;}
                if ( (PassFinalCuts(tau_NoShift,met) == true) ) {
                 //std::cout << "*metUncert_JetEnDown* dphi_tau_met=" << dphi_tau_met << std::endl;
                 mSystHist[std::to_string(i)]->Fill(calcMT(tau_NoShift,met),final_weight*kFactorShift);
                 setShiftedTree(tau_NoShift, met, final_weight*kFactorShift);
               }
            }
               ///--Tau Scale--///
           }
           if (nGoodTau_ScaleUp==1){
               if ( (PassFinalCuts(tau_ScaleUp,met ) == true ) ) {
             //std::cout << "*Tau Scale Up* dphi_tau_met=" << dphi_tau_met << std::endl;
             h1_MT_Stage1_TauScaleUp_new->Fill(calcMT(tau_ScaleUp,met),final_weight);
               }
           }
               ///
           if (nGoodTau_ScaleDown==1){
               if ( (PassFinalCuts(tau_ScaleDown,met ) == true) ) {
             //std::cout << "*Tau Scale Down* dphi_tau_met=" << dphi_tau_met << std::endl;
             h1_MT_Stage1_TauScaleDown_new->Fill(calcMT(tau_ScaleDown,met),final_weight);
          }
       }
    }


     }

   //--------------//
   //-- Region A --// Only one non-isolated tau //
   //--------------//
   if (passTauTrig && passAllMETFilters ) {
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
   if (passTauTrig && passAllMETFilters ) {
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
   if (passTauTrig && passAllMETFilters ) {
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
   //QCDAnalyse();
   //if (not RunOnData)
   QCDAnalyseTau(met,final_weight,pruned);
   //QCDAnalyseTau(met,final_weight);

    //if(tau_NoShift.Pt()>80 && calcMT(tau_NoShift,met)>50){
       Fill_QCD_Tree(true,tau_NoShift,met,final_weight);
       Fill_Tree(tau_NoShift,met,final_weight,"");
       helper->Tree_Filler("reweighttree");
    //}


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
    if (fabs(dphi_tau_met)>2.4) {
      // std::cout << "dphi_tau_met=" << dphi_tau_met << std::endl;
      passed=true;
    }
      }
    }
  }
  return passed;
}

bool MiniAODAnalyzer::PassFinalCuts(TLorentzVector part1, const pat::MET part2, pat::MET::METUncertainty metUncert) {
    ///--- please make sure you asked explicitly for 1 good tau!! ---///
    return PassFinalCuts(1,part2.shiftedPt(metUncert),part2.shiftedPhi(metUncert),part1.Pt(),part1.Phi());
}
bool MiniAODAnalyzer::PassFinalCuts(TLorentzVector part1, const pat::MET part2) {
    return PassFinalCuts(1,part2.pt(),part2.phi(),part1.Pt(),part1.Phi());
}
bool MiniAODAnalyzer::PassFinalCuts(int nGoodTau_,TLorentzVector part1, const pat::MET part2) {
    return PassFinalCuts(nGoodTau_,part2.pt(),part2.phi(),part1.Pt(),part1.Phi());
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
  SetSystMap();
  Create_Trees();
  SetSystMap();

  helper->CreateHistoUnchangedName("h_counters", 10, 0, 11, "N_{events}");
}

// ------------ method called once each job just after ending the event loop  ------------
void
MiniAODAnalyzer::endJob()
{

  //  std::cout << "In endJob()" << std::endl;
   if ( doPDFuncertainty) {
    for (int nb=0; nb<nbinMT; nb++) {
      double array[100] = {0.} ;
      double temp=0.0;
      double temp2=9.0e+100;
      for (int nh=0; nh<100; nh++) {
    double binCon = h1_MT_Stage1_pdfWt[nh]->GetBinContent(nb);
    array[nh]=binCon;
      }

      for(int nh2=0;nh2<100;nh2++) {
    if (array[nh2]>temp)  temp=array[nh2];
    if (array[nh2]<temp2) temp2=array[nh2];
      }

      //      double nominal=h1_MT_Stage1->GetBinContent(nb);
      //      std::cout << "Nominal= "<< nominal <<  " up= " << temp << " down=" << temp2 << std::endl;
      h1_MT_Stage1_pdfUncertUp->SetBinContent(nb,temp);
      h1_MT_Stage1_pdfUncertDown->SetBinContent(nb,temp2);

    }
  }

  /*    ///-- nominal +/- RMS did not work. down always 0 --///
  if ( doPDFuncertainty) {
    for (int nb=0; nb<nbinMT; nb++) {
      double val=0.0;
      for (int nh=0; nh<100; nh++) {
    double binCon = h1_MT_Stage1_pdfWt[nh]->GetBinContent(nb);
    val=val + (binCon*binCon) ;
      }
      double rms= sqrt((val/100));
      double nominal=h1_MT_Stage1->GetBinContent(nb);
      double up= (nominal+rms);
      double down = (nominal-rms);
      //    std::cout << "nbin=" << nb << " nominal=" << nominal  << " rms=" << rms << " up/down=" << up << " / " << down << std::endl;
      if (down<0.0) down=0.0;
      h1_MT_Stage1_pdfUncertUp->SetBinContent(nb,up);
      h1_MT_Stage1_pdfUncertDown->SetBinContent(nb,down);
    }
  }
*/
  /*
   * this part can be removed, if we want to
   * "mytree" as to be reintroduced in the TFileService then
   * via mytree = fs->make<TTree>("tree", "tr");
  */
  ///remove second root file
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


  ///crosscheck
  h1_MT_Stage1_metUncert_JetEnUp_diff->Add(h1_MT_Stage1_metUncert_JetEnUp_new,1);
  h1_MT_Stage1_metUncert_JetEnUp_diff->Add(h1_MT_Stage1_metUncert_JetEnUp,-1);
  h1_MT_Stage1_metUncert_JetEnDown_diff->Add(h1_MT_Stage1_metUncert_JetEnDown_new,1);
  h1_MT_Stage1_metUncert_JetEnDown_diff->Add(h1_MT_Stage1_metUncert_JetEnDown,-1);
  h1_MT_Stage1_metUncert_JetResUp_diff->Add(h1_MT_Stage1_metUncert_JetResUp_new,1);
  h1_MT_Stage1_metUncert_JetResUp_diff->Add(h1_MT_Stage1_metUncert_JetResUp,-1);
  h1_MT_Stage1_metUncert_JetResDown_diff->Add(h1_MT_Stage1_metUncert_JetResDown_new,1);
  h1_MT_Stage1_metUncert_JetResDown_diff->Add(h1_MT_Stage1_metUncert_JetResDown,-1);
  h1_MT_Stage1_metUncert_MuonEnUp_diff->Add(h1_MT_Stage1_metUncert_MuonEnUp_new,1);
  h1_MT_Stage1_metUncert_MuonEnUp_diff->Add(h1_MT_Stage1_metUncert_MuonEnUp,-1);
  h1_MT_Stage1_metUncert_MuonEnDown_diff->Add(h1_MT_Stage1_metUncert_MuonEnDown_new,1);
  h1_MT_Stage1_metUncert_MuonEnDown_diff->Add(h1_MT_Stage1_metUncert_MuonEnDown,-1);
  h1_MT_Stage1_metUncert_ElectronEnUp_diff->Add(h1_MT_Stage1_metUncert_ElectronEnUp_new,1);
  h1_MT_Stage1_metUncert_ElectronEnUp_diff->Add(h1_MT_Stage1_metUncert_ElectronEnUp,-1);
  h1_MT_Stage1_metUncert_ElectronEnDown_diff->Add(h1_MT_Stage1_metUncert_ElectronEnDown_new,1);
  h1_MT_Stage1_metUncert_ElectronEnDown_diff->Add(h1_MT_Stage1_metUncert_ElectronEnDown,-1);
  h1_MT_Stage1_metUncert_TauEnUp_diff->Add(h1_MT_Stage1_metUncert_TauEnUp_new,1);
  h1_MT_Stage1_metUncert_TauEnUp_diff->Add(h1_MT_Stage1_metUncert_TauEnUp,-1);
  h1_MT_Stage1_metUncert_TauEnDown_diff->Add(h1_MT_Stage1_metUncert_TauEnDown_new,1);
  h1_MT_Stage1_metUncert_TauEnDown_diff->Add(h1_MT_Stage1_metUncert_TauEnDown,-1);
  h1_MT_Stage1_metUncert_PhotonEnUp_diff->Add(h1_MT_Stage1_metUncert_PhotonEnUp_new,1);
  h1_MT_Stage1_metUncert_PhotonEnUp_diff->Add(h1_MT_Stage1_metUncert_PhotonEnUp,-1);
  h1_MT_Stage1_metUncert_PhotonEnDown_diff->Add(h1_MT_Stage1_metUncert_PhotonEnDown_new,1);
  h1_MT_Stage1_metUncert_PhotonEnDown_diff->Add(h1_MT_Stage1_metUncert_PhotonEnDown,-1);
  h1_MT_Stage1_metUncert_UnclusteredEnUp_diff->Add(h1_MT_Stage1_metUncert_UnclusteredEnUp_new,1);
  h1_MT_Stage1_metUncert_UnclusteredEnUp_diff->Add(h1_MT_Stage1_metUncert_UnclusteredEnUp,-1);
  h1_MT_Stage1_metUncert_UnclusteredEnDown_diff->Add(h1_MT_Stage1_metUncert_UnclusteredEnDown_new,1);
  h1_MT_Stage1_metUncert_UnclusteredEnDown_diff->Add(h1_MT_Stage1_metUncert_UnclusteredEnDown,-1);
  h1_MT_Stage1_TauScaleUp_diff->Add(h1_MT_Stage1_TauScaleUp_new,1);
  h1_MT_Stage1_TauScaleUp_diff->Add(h1_MT_Stage1_TauScaleUp,-1);
  h1_MT_Stage1_TauScaleDown_diff->Add(h1_MT_Stage1_TauScaleDown_new,1);
  h1_MT_Stage1_TauScaleDown_diff->Add(h1_MT_Stage1_TauScaleDown,-1);

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

  if(useReweighting==true){
      mReweightTree["gen_mt"]=-1;
      for (int i=0; i<=16;i++){
          mReweightTree["gen_mt_"+mSystName[std::to_string(i)]]=-1;
          mReweightTree["mt_"+mSystName[std::to_string(i)]]=-1;
          mReweightTree["delta_phi_"+mSystName[std::to_string(i)]]=-1;
          mReweightTree["ThisWeight_"+mSystName[std::to_string(i)]]=-1;
          mReweightTree["met_"+mSystName[std::to_string(i)]]=-1;
      }
    }


  helper->Tree_Creater( &mReweightTree, "reweighttree");

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



  mFakeTree["mt"]=0;
  mFakeTree["delta_phi"]=0;
  mFakeTree["pt"]=0;
  mFakeTree["met"]=0;
  mFakeTree["phi"]=0;
  mFakeTree["eta"]=0;
  mFakeTree["met_phi"]=0;

  mFakeTree["decay_mode"]=0;
  mFakeTree["iso"]=0;
  mFakeTree["tau_n"]=0;
  mFakeTree["truth_match"]=0;

  mFakeTree["lepton_type"]=0;
  mFakeTree["lepton_mt"]=0;
  mFakeTree["lepton_delta_phi"]=0;
  mFakeTree["lepton_pt"]=0;
  mFakeTree["lepton_eta"]=0;
  mFakeTree["lepton_phi"]=0;
  mFakeTree["lepton_trigger"]=0;


  //general
  mFakeTree["ThisWeight"]=0;
  helper->Tree_Creater( &mFakeTree, "fakeTree");


  //mFakeVectorTree["test"]=0;
  //std::vector<float> vec(20);
    ///needs to be fixed
/*
  std::vector<std::string> str= {"FakeCandPt",
  //std::vector<char *> str= {"FakeCandPt",
  "FakeCandPhi","FakeCandEta","FakeCandMET",
  "FakeCandMETPhi","FakeCandDeltaPhi","FakeCandIso",
  "FakeCandNoIso","FakeCandVetoNum"};
  std::vector<std::vector<float>> vecOfVec= {FakeCandPt,
  FakeCandPhi,FakeCandEta,FakeCandMET,
  FakeCandMETPhi,FakeCandDeltaPhi,FakeCandIso,
  FakeCandNoIso,FakeCandVetoNum};*/

  //for (auto arg:str) mFakeVectorTree[arg]=vec;
  //mFakeVectorTree["FakeCandPt"]=vec;
  //mFakeVectorTree["FakeCandPhi"]=0;
  //mFakeVectorTree["FakeCandEta"]=0;
  //mFakeVectorTree["FakeCandMET"]=0;
  //mFakeVectorTree["FakeCandMETPhi"]=0;
  //mFakeVectorTree["FakeCandDeltaPhi"]=0;
  //mFakeVectorTree["FakeCandIso"]=0;
  //mFakeVectorTree["FakeCandNoIso"]=0;
  //mFakeVectorTree["FakeCandVetoNum"]=0;
  helper->Tree_Creater( &mFakeVectorTree, "fakeVectorTree");
    ///needs to be fixed
  //for (size_t i=0;i<str.size();i++) helper->SetFakeBranches("fakeVectorTree",str[i].c_str(),&(vecOfVec[i]));
  //for (size_t i=0;i<str.size();i++) helper->SetFakeBranches("fakeVectorTree","FakeCandPt",&vecOfVec[i]);
  //for (size_t i=0;i<str.size();i++) helper->SetFakeBranches("fakeVectorTree","FakeCandPt",&FakeCandPt);

  helper->SetFakeBranches("fakeVectorTree","FakeCandPt",&FakeCandPt);
  helper->SetFakeBranches("fakeVectorTree","FakeCandPhi",&FakeCandPhi);
  helper->SetFakeBranches("fakeVectorTree","FakeCandEta",&FakeCandEta);
  helper->SetFakeBranches("fakeVectorTree","FakeCandDeltaPhi",&FakeCandDeltaPhi);
  helper->SetFakeBranches("fakeVectorTree","FakeCandMET",&FakeCandMET);
  helper->SetFakeBranches("fakeVectorTree","FakeCandMETPhi",&FakeCandMETPhi);
  helper->SetFakeBranches("fakeVectorTree","FakeCandIso",&FakeCandIso);
  helper->SetFakeBranches("fakeVectorTree","FakeCandNoIso",&FakeCandNoIso);
  helper->SetFakeBranches("fakeVectorTree","FakeCandVetoNum",&FakeCandVetoNum);
  helper->SetFakeBranches("fakeVectorTree","FakeCandDecayMode",&FakeCandDecayMode);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonType",&FakeCandLeptonType);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonMt",&FakeCandLeptonMt);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonDeltaPhi",&FakeCandLeptonDeltaPhi);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonPt",&FakeCandLeptonPt);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonEta",&FakeCandLeptonEta);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonPhi",&FakeCandLeptonPhi);
  helper->SetFakeBranches("fakeVectorTree","FakeCandLeptonTrigger",&FakeCandLeptonTrigger);

  //helper->SetFakeBranches("fakeVectorTree","FakeCandLorentz",&FakeCandLorentz);
}


void MiniAODAnalyzer::setShiftedTree(TLorentzVector sel_lepton, const pat::MET sel_met, double weight, pat::MET::METUncertainty metUncert){

    if(useReweighting==true){
        for (int i=1;i<=14;i++){
            if ( (PassFinalCuts(sel_lepton,sel_met,mSyst[std::to_string(i)] ) == true) ) {
                /// currently the tau is not given, maybe loop over all taus and find the match?
                /*TLorentzVector tempP4 (0,0,0,0);
                reco::GenParticle* genMatch=GetTruthMatch("Tau",tau);
                tempP4.SetPxPyPzE(genMatch->px(),genMatch->py(),genMatch->pz(),genMatch->energy());
                mReweightTree["gen_mt_"+mSystName[std::to_string(i)]]=calcMT(tempP4,sel_met,mSyst[std::to_string(i)]);//gen, has to be fixed*/
                mReweightTree["gen_mt_"+mSystName[std::to_string(i)]]=calcMT(sel_lepton,sel_met,mSyst[std::to_string(i)]);//gen, has to be fixed
                mReweightTree["mt_"+mSystName[std::to_string(i)]]=calcMT(sel_lepton,sel_met,mSyst[std::to_string(i)]);
                mReweightTree["met_"+mSystName[std::to_string(i)]]=sel_met.shiftedPhi(metUncert);
                mReweightTree["delta_phi_"+mSystName[std::to_string(i)]]=deltaPhi(sel_lepton.Phi(),sel_met.shiftedPhi(metUncert));
                mReweightTree["ThisWeight_"+mSystName[std::to_string(i)]]=weight;
            }
        }
        //for (int i=15;i<=16;i++){
            //if ( (PassFinalCuts(sel_lepton,sel_met,mSyst[std::to_string(i)] ) == true) ) {
                //mLeptonTree["gen_mt_"+mSystName[std::to_string(i)]]=calcMT(sel_lepton,sel_met);//gen, has to be fixed
                //mLeptonTree["mt_"+mSystName[std::to_string(i)]]=calcMT(sel_lepton,sel_met,mSyst[std::to_string(i)]);
                //mLeptonTree["met_"+mSystName[std::to_string(i)]]=sel_met.shiftedPhi(metUncert);
                //mLeptonTree["delta_phi_"+mSystName[std::to_string(i)]]=deltaPhi(sel_lepton.Phi(),sel_met.shiftedPhi(metUncert));
                //mLeptonTree["ThisWeight_"+mSystName[std::to_string(i)]]=weight;
            //}
        //}

    }
    //else{
        //mLeptonTree["gen_mt"]=calcMT(sel_lepton,sel_met);//gen
    //}

}
void MiniAODAnalyzer::setShiftedTree(TLorentzVector sel_lepton, const pat::MET sel_met, double weight){

    if(useReweighting==true){
        for (int i=15;i<=16;i++){
            //std::cout << i << std::endl;
            if ( (PassFinalCuts(sel_lepton,sel_met,mSyst[std::to_string(i)] ) == true) ) {
                /*TLorentzVector tempP4 (0,0,0,0);
                reco::GenParticle* genMatch=GetTruthMatch("Tau",tau);
                tempP4.SetPxPyPzE(genMatch->px(),genMatch->py(),genMatch->pz(),genMatch->energy());
                mReweightTree["gen_mt_"+mSystName[std::to_string(i)]]=calcMT(tempP4,sel_met);*/
                mReweightTree["gen_mt_"+mSystName[std::to_string(i)]]=calcMT(sel_lepton,sel_met);
                mReweightTree["mt_"+mSystName[std::to_string(i)]]=calcMT(sel_lepton,sel_met);
                mReweightTree["met_"+mSystName[std::to_string(i)]]=sel_met.phi();
                mReweightTree["delta_phi_"+mSystName[std::to_string(i)]]=deltaPhi(sel_lepton.Phi(),sel_met.phi());
                mReweightTree["ThisWeight_"+mSystName[std::to_string(i)]]=weight;
            }
        }
    }

}
void MiniAODAnalyzer::Fill_Tree(TLorentzVector sel_lepton, const pat::MET sel_met, double weight, std::string systematic){

    mLeptonTree["bjet1"]=0;
    mLeptonTree["mt"]=calcMT(sel_lepton,sel_met);
    mLeptonTree["delta_phi"]=deltaPhi(sel_lepton.Phi(),sel_met.phi());
    mLeptonTree["pt"]=sel_lepton.Pt();
    mLeptonTree["met"]=sel_met.pt();
    mLeptonTree["lepton_phi"]=sel_lepton.Phi();
    mLeptonTree["lepton_eta"]=sel_lepton.Eta();
    mLeptonTree["met_phi"]=sel_met.phi();
    mLeptonTree["kfak"]=k_fak_stored;
    //good for crosschecks
    /*
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
    }*/
    //PDF
    //needed for reweighting
    if( not RunOnData ){
        mLeptonTree["id1"]=0;
        mLeptonTree["id2"]=0;
        mLeptonTree["x1"]=0;
        mLeptonTree["x2"]=0;
        mLeptonTree["qscale"]=0;
        //mLeptonTree["id1"]=m_GenEvtView->getUserRecord("f1");
        //mLeptonTree["id2"]=m_GenEvtView->getUserRecord("f2");
        //mLeptonTree["x1"]=m_GenEvtView->getUserRecord("x1");
        //mLeptonTree["x2"]=m_GenEvtView->getUserRecord("x2");
        //mLeptonTree["qscale"]=m_GenEvtView->getUserRecord("Q");
    }
    //general*/
    mLeptonTree["ThisWeight"]=weight;

    //needed when using different leptons
    /*//mLeptonTree["lepton_type"]=sel_lepton->getUserRecord("id");
    mLeptonTree["lepton_type"]=sel_lepton->getPdgNumber();
    if(abs(sel_lepton->getPdgNumber())==11){
        mLeptonTree["highEtEleTrig"]=highEtTriggStored;
    }else{
        mLeptonTree["highEtEleTrig"]=0;
    }*/
    helper->Tree_Filler("slimtree");
}

void MiniAODAnalyzer::Fill_QCD_Tree(bool iso,TLorentzVector sel_lepton, const pat::MET sel_met, double weight){

    // testing stuff
    //if(iso){
        //mQCDTree["lepton_n"]=3;
    //}
    //else{
        //mQCDTree["lepton_n"]=2;
    //}
    //helper->Tree_Filler("qcdtree");


    if(iso){
        mQCDTree["lepton_n"]=0;
        mQCDTree["iso"]=iso;
        mQCDTree["ThisWeight"]=weight;
        //mQCDTree["QCDWeight"]=qcd_weight;
        mQCDTree["met"]=sel_met.pt();
        mQCDTree["pt"]=sel_lepton.Pt();
        mQCDTree["mt"]=calcMT(sel_lepton,sel_met);
        mQCDTree["eta"]=sel_lepton.Eta();
        mQCDTree["delta_phi"]=deltaPhi(sel_lepton.Phi(),sel_met.phi());
        //mQCDTree["nvert"]=m_RecEvtView->getUserRecord("NumVertices");  // if there was a dependence on the nvertices, build dependend fakerate
        //if (sel_lepton.charge() > 0){
            //mQCDTree["mtpos"]=calcMT(sel_lepton,sel_met);
        //}
        //if (sel_lepton.charge() < 0){
            //mQCDTree["mtneg"]=calcMT(sel_lepton,sel_met);
        //}
        //if(abs(sel_lepton->getPdgNumber())==15){
            //mQCDTree["metTriggerd"]=sel_lepton->getUserRecord("metTriggered").toBool();
        //}
        //else{
            //mQCDTree["metTriggerd"]=0;
        //}
        //if(sel_lepton->hasUserRecord("decayMode")){
            //mQCDTree["decay_mode"]=sel_lepton->getUserRecord("decayMode").toDouble();
        //}else{
            //mQCDTree["decay_mode"]=-1;
        //}
        //if(abs(sel_lepton->getPdgNumber())==15 && m_do_complicated_tau_stuff){
            //for(auto idisc : d_mydisc){
                //mQCDTree[idisc]=sel_lepton->getUserRecord(idisc).toDouble();
            //}
        //}
        helper->Tree_Filler("qcdtree");
    }/*else{
        int i=0;
        for(auto thisQCDlepton : QCDLeptonList){
            mQCDTree["lepton_n"]=i;
            i++;
            mQCDTree["iso"]=iso;
            mQCDTree["ThisWeight"]=weight;
            mQCDTree["QCDWeight"]=qcd_weight;
            mQCDTree["met"]=sel_met.pt();
            mQCDTree["pt"]=thisQCDlepton.Pt();
            mQCDTree["mt"]=calcMT(thisQCDlepton,sel_met);
            mQCDTree["eta"]=thisQCDlepton->Eta();
            mQCDTree["delta_phi"]=deltaPhi(thisQCDlepton.Phi(),sel_met.phi());
            mQCDTree["nvert"]=m_RecEvtView->getUserRecord("NumVertices");
            if (thisQCDlepton->getCharge() > 0){
                mQCDTree["mtpos"]=calcMT(thisQCDlepton,sel_met);
            }
            if (thisQCDlepton->getCharge() < 0){
                mQCDTree["mtneg"]=MT(thisQCDlepton,sel_met);
            }
            mQCDTree["lepton_type"]=thisQCDlepton.pdgId();
            if(abs(thisQCDlepton.pdgId())==15){
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
            helper->Tree_Filler("qcdtree");
        }
    }*/
}


double MiniAODAnalyzer::calcMT(TLorentzVector part1, TLorentzVector part2) {
    double mm = 2 * part1.Pt() * part2.Pt() * ( 1. - cos(deltaPhi(part1.Phi(),part2.Phi()) ));
    return sqrt(mm);
}
double MiniAODAnalyzer::calcMT(TLorentzVector part1, const pat::MET part2) {
    TLorentzVector tempPart2P4 (0,0,0,0);
    tempPart2P4.SetPxPyPzE(part2.px(),part2.py(),part2.pz(),part2.energy());
    return calcMT(part1,tempPart2P4);
}

double MiniAODAnalyzer::calcMT(TLorentzVector part1, const pat::MET part2, pat::MET::METUncertainty metUncert) {
    double mm = 2 * part1.Pt() * part2.shiftedPt(metUncert) * ( 1. - cos(deltaPhi(part1.Phi(),part2.shiftedPhi(metUncert)) ));
    return sqrt(mm);
}
double MiniAODAnalyzer::calcMT(const pat::Electron part1, const pat::MET part2) {

    TLorentzVector tempPart1P4 (0,0,0,0);
    tempPart1P4.SetPxPyPzE(part1.px(),part1.py(),part1.pz(),part1.energy());
    TLorentzVector tempPart2P4 (0,0,0,0);
    tempPart2P4.SetPxPyPzE(part2.px(),part2.py(),part2.pz(),part2.energy());
    return calcMT(tempPart1P4,tempPart2P4);
}
double MiniAODAnalyzer::calcMT(const pat::Muon part1, const pat::MET part2) {

    TLorentzVector tempPart1P4 (0,0,0,0);
    tempPart1P4.SetPxPyPzE(part1.px(),part1.py(),part1.pz(),part1.energy());
    TLorentzVector tempPart2P4 (0,0,0,0);
    tempPart2P4.SetPxPyPzE(part2.px(),part2.py(),part2.pz(),part2.energy());
    return calcMT(tempPart1P4,tempPart2P4);
}
double MiniAODAnalyzer::calcMT(const pat::Tau part1, const pat::MET part2) {

    TLorentzVector tempPart1P4 (0,0,0,0);
    tempPart1P4.SetPxPyPzE(part1.px(),part1.py(),part1.pz(),part1.energy());
    TLorentzVector tempPart2P4 (0,0,0,0);
    tempPart2P4.SetPxPyPzE(part2.px(),part2.py(),part2.pz(),part2.energy());
    return calcMT(tempPart1P4,tempPart2P4);
}

double MiniAODAnalyzer::DeltaR(auto part,auto tau){

    TLorentzVector tempPartP4 (0,0,0,0);
    tempPartP4.SetPxPyPzE(part.px(),part.py(),part.pz(),part.energy());
    TLorentzVector tempTauP4 (0,0,0,0);
    tempTauP4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
    return tempTauP4.DeltaR(tempPartP4);
}
double MiniAODAnalyzer::DeltaR(pat::Muon part,pat::Tau tau){

    TLorentzVector tempPartP4 (0,0,0,0);
    tempPartP4.SetPxPyPzE(part.px(),part.py(),part.pz(),part.energy());
    TLorentzVector tempTauP4 (0,0,0,0);
    tempTauP4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
    return tempTauP4.DeltaR(tempPartP4);
}
double MiniAODAnalyzer::DeltaR(pat::Electron part,pat::Tau tau){

    TLorentzVector tempPartP4 (0,0,0,0);
    tempPartP4.SetPxPyPzE(part.px(),part.py(),part.pz(),part.energy());
    TLorentzVector tempTauP4 (0,0,0,0);
    tempTauP4.SetPxPyPzE(tau.px(),tau.py(),tau.pz(),tau.energy());
    return tempTauP4.DeltaR(tempPartP4);
}
double MiniAODAnalyzer::DeltaPhi(pat::Electron part1, pat::MET part2){
    return deltaPhi(part1.phi(),part2.phi());
}
double MiniAODAnalyzer::DeltaPhi(pat::Muon part1, pat::MET part2){
    return deltaPhi(part1.phi(),part2.phi());
}
double MiniAODAnalyzer::DeltaPhi(pat::Tau part1, pat::MET part2){
    return deltaPhi(part1.phi(),part2.phi());
}

void MiniAODAnalyzer::SetSystMap(){

     //set syst names to use in setShifted
  mSystName["0"]="";
  mSyst["1"]=pat::MET::JetEnUp;
  mSystHist["1"]=h1_MT_Stage1_metUncert_JetEnUp_new;
  mSystName["1"]="JetEnUp";
  mSyst["2"]=pat::MET::JetEnDown;
  mSystHist["2"]=h1_MT_Stage1_metUncert_JetEnDown_new;
  mSystName["2"]="JetEnDown";
  mSyst["3"]=pat::MET::JetResUp;
  mSystHist["3"]=h1_MT_Stage1_metUncert_JetResUp_new;
  mSystName["3"]="JetResUp";
  mSyst["4"]=pat::MET::JetResDown;
  mSystHist["4"]=h1_MT_Stage1_metUncert_JetResDown_new;
  mSystName["4"]="JetResDown";
  mSyst["5"]=pat::MET::MuonEnUp;
  mSystHist["5"]=h1_MT_Stage1_metUncert_MuonEnUp_new;
  mSystName["5"]="MuonEnUp";
  mSyst["6"]=pat::MET::MuonEnDown;
  mSystHist["6"]=h1_MT_Stage1_metUncert_MuonEnDown_new;
  mSystName["6"]="MuonEnDown";
  mSyst["7"]=pat::MET::ElectronEnUp;
  mSystHist["7"]=h1_MT_Stage1_metUncert_ElectronEnUp_new;
  mSystName["7"]="EleEnUp";
  mSyst["8"]=pat::MET::ElectronEnDown;
  mSystHist["8"]=h1_MT_Stage1_metUncert_ElectronEnDown_new;
  mSystName["8"]="EleEnDown";
  mSyst["9"]=pat::MET::TauEnUp;
  mSystHist["9"]=h1_MT_Stage1_metUncert_TauEnUp_new;
  mSystName["9"]="TauEnUp";
  mSyst["10"]=pat::MET::TauEnDown;
  mSystHist["10"]=h1_MT_Stage1_metUncert_TauEnDown_new;
  mSystName["10"]="TauEnDown";
  mSyst["11"]=pat::MET::PhotonEnUp;
  mSystHist["11"]=h1_MT_Stage1_metUncert_PhotonEnUp_new;
  mSystName["11"]="PhotonEnUp";
  mSyst["12"]=pat::MET::PhotonEnDown;
  mSystHist["12"]=h1_MT_Stage1_metUncert_PhotonEnDown_new;
  mSystName["12"]="PhotonEnDown";
  mSyst["13"]=pat::MET::UnclusteredEnUp;
  mSystHist["13"]=h1_MT_Stage1_metUncert_UnclusteredEnUp_new;
  mSystName["13"]="UnclusteredEnUp";
  mSyst["14"]=pat::MET::UnclusteredEnDown;
  mSystHist["14"]=h1_MT_Stage1_metUncert_UnclusteredEnDown_new;
  mSystName["14"]="UnclusteredEnDown";
  //mSyst["15"]=0;
  mSystHist["15"]=h1_MT_Stage1_kFactorUp;
  mSystName["15"]="kFactorUp";
  //mSyst["16"]=0;
  mSystHist["16"]=h1_MT_Stage1_kFactorDown;
  mSystName["16"]="kFactorDown";
    }

/*
 * get gen variables from LHE header of miniAOD
 * gen mass of  w, save in variable,
 * so you can go as often through the event as you like,
 * without losing time
 * ht: gen level
 * ht: reco level
 *
 * */


double MiniAODAnalyzer::applyWKfactor(int mode, edm::Handle<edm::View<reco::GenParticle>> genPart){

    WtoInt=sourceFileString.find("Wto");
    WJetsInt=sourceFileString.find("WJets");
    //std::cout << std::endl<< sourceFileString << " "<< WtoInt
    //<< " " << WJetsInt    <<  " " << std::string::npos << std::endl;
    //std::cout << sourceFileString.find("Wto") << std::endl;
    bool applyKfactor=false;
    if (WtoInt!=std::string::npos or WJetsInt!=std::string::npos){
        applyKfactor=true;
    }
    //std::cout << applyKfactor << std::endl;

    ///--- mode 1 (multiplicative) is legacy and should not be used ---///
    if( not (mode==1 || mode==0) ){
        throw std::runtime_error("specialAna.cc: The k-faktor must be additive (mode=0) or multiplicative (mode=1) yours is "+std::to_string(mode));
    }

    if (applyKfactor==true){
        double mass=getWmass(genPart);
        int leptonID=getWdecay(genPart);
        double k_faktor=1.;
        if(mass>0){
            if(leptonID==11){
                k_faktor=m_kfactorHist_ele[mode]->GetBinContent(m_kfactorHist_ele[mode]->FindBin(mass));
            }else if(leptonID==13){
                k_faktor=m_kfactorHist_muo[mode]->GetBinContent(m_kfactorHist_muo[mode]->FindBin(mass));
            }else if(leptonID==15){
                k_faktor=m_kfactorHist_tau[mode]->GetBinContent(m_kfactorHist_tau[mode]->FindBin(mass));
            }
        }
        if (k_faktor<0){
            k_faktor=1.;
        }
        //weight*=k_faktor;
        return k_faktor;
    }
    else{
        return 1;
    }
}


int MiniAODAnalyzer::getWdecay(edm::Handle<edm::View<reco::GenParticle>> genPart){
    int temp_id=0;
    for(size_t i=0; i<genPart->size();i++){
        if (abs((*genPart)[i].pdgId())==15 or abs((*genPart)[i].pdgId())==13 or abs((*genPart)[i].pdgId())==11){
            temp_id=abs((*genPart)[i].pdgId());
            break;
        }
    }
    return temp_id;
}


double MiniAODAnalyzer::getWmass(edm::Handle<edm::View<reco::GenParticle>> genPart){
    //std::cout << "wmass_stored is " << wmass_stored << std::endl;
    if(wmass_stored!=0){
        return wmass_stored;
    }
    double temp_W_mass=0;
    bool First=false;
    bool second=false;
    int temp_i=0;

    for(size_t i=0; i<genPart->size();i++){
        if(abs((*genPart)[i].pdgId())==24 && First==false){
            //std::cout << "ID is " << (*genPart)[i].pdgId() << std::endl;
            //std::cout << "W mass from W is " << (*genPart)[i].mass() << std::endl;
            First=true;
            temp_W_mass=(*genPart)[i].mass();
            break;
        }
        if (second==false){
            if (abs((*genPart)[i].pdgId())==15 or abs((*genPart)[i].pdgId())==13 or abs((*genPart)[i].pdgId())==11){
                temp_i=i;
                second=true;
                break;
            }
        }
    }
    if (second==true){
        for(size_t i=0; i<genPart->size();i++){
            int sign=(*genPart)[temp_i].pdgId()/abs((*genPart)[temp_i].pdgId());
            if ( (*genPart)[i].pdgId()==(-1*((*genPart)[temp_i].pdgId()+sign))){
                temp_W_mass=((*genPart)[i].p4()+(*genPart)[temp_i].p4()).mass();
                break;
            }
        }
    }
    wmass_stored=temp_W_mass;
    return wmass_stored;
}

/*
void MiniAODAnalyzer::QCDAnalyse() {
    //inverted isolation
    if(sel_lepton!=0 or m_do_complicated_tau_stuff){
        return;
    }
    int qcd_id=0;
    bool passed=false;
    bool passedPtMet=false;
    bool passedDeltaPhi=false;

    double m_leptonVetoPt=20;
    int numVetoMuo=vetoNumber(MuonList,m_leptonVetoPt);
    int numVetoTau=vetoNumberTau(TauList,m_leptonVetoPt);
    int numVetoEle=vetoNumber(EleList,m_leptonVetoPt);


    if( numVetoEle==0 && TauList->size()>=1 && numVetoMuo==0 ){
        int passedID=0;
        map<string,int> passedID_disc;
        for(std::vector<std::string>::iterator disc_it = d_mydisc.begin(); disc_it != d_mydisc.end(); disc_it++){
            passedID_disc[(*disc_it)]=0;
        }
        for( std::vector< pxl::Particle* >::iterator it = TauList->begin(); it != TauList->end(); ++it ) {

            if(m_do_complicated_tau_stuff){
                for(std::vector<std::string>::iterator disc_it = d_mydisc.begin(); disc_it != d_mydisc.end(); disc_it++){
                    if(not ((*it)->getUserRecord( (*disc_it) ).toDouble()>0.5)){
                        passedID_disc[(*disc_it)]++;
                        (*it)->setPdgNumber(15);
                        QCDLeptonList.push_back(*it);
                    }
                }
            }else{
                //if( Check_Tau_ID_no_iso(*it) ){
                    //passedID++;
                    //(*it)->setPdgNumber(15);
                    //QCDLeptonList.push_back(*it);
                //}
            }
        }
        if(passedID>=1){
            qcd_lepton=QCDLeptonList.at(0);
            m_pt_min_cut=m_pt_min_cut_tau;
            m_delta_phi_cut=m_delta_phi_cut_tau;
            m_pt_met_min_cut=m_pt_met_min_cut_tau;
            m_pt_met_max_cut=m_pt_met_max_cut_tau;

            m_pt_met_min_cut_funk_root=m_pt_met_min_cut_funk_root_tau;
            m_pt_met_max_cut_funk_root=m_pt_met_max_cut_funk_root_tau;
            m_delta_phi_cut_funk_root=m_delta_phi_cut_funk_root_tau;
            qcd_id=15;
        }
    }

    if( EleList->size()>=1 && numVetoTau==0 && numVetoMuo==0 ){
        int passedID=0;
        for( std::vector< pxl::Particle* >::iterator it = EleList->begin(); it != EleList->end(); ++it ) {

            if( (*it)->hasUserRecord("loosIDnoISO")){
                if ( (*it)->getUserRecord("loosIDnoISO").toBool() or (*it)->getUserRecord("loosIDandISO").toBool() ){
                    passedID++;
                    (*it)->setPdgNumber(11);
                    QCDLeptonList.push_back(*it);
                }
            }
            //we can not do the fr if we tag the electrons!!
            //else if (EleList->size()==1){
                //passedID++;
                //tmpEle=( pxl::Particle* ) EleList->at(0);
                //break;
            //}
        }
        //cout<<passedID<<endl;
        if(passedID>=1){
            qcd_lepton=QCDLeptonList.at(0);
            m_pt_min_cut=m_pt_min_cut_ele;
            m_delta_phi_cut=m_delta_phi_cut_ele;
            m_pt_met_min_cut=m_pt_met_min_cut_ele;
            m_pt_met_max_cut=m_pt_met_max_cut_ele;

            m_pt_met_min_cut_funk_root=m_pt_met_min_cut_funk_root_ele;
            m_pt_met_max_cut_funk_root=m_pt_met_max_cut_funk_root_ele;
            m_delta_phi_cut_funk_root=m_delta_phi_cut_funk_root_ele;
            qcd_id=11;
        }
    }
    if( numVetoEle==0 && numVetoTau==0 && MuonList->size()>=1 ){
        int passedID=0;
        for( std::vector< pxl::Particle* >::iterator it = MuonList->begin(); it != MuonList->end(); ++it ) {
            if( (*it)->hasUserRecord("ISOfailed")){
                if (  (*it)->getUserRecord("ISOfailed").toBool() ){
                    passedID++;
                    (*it)->setPdgNumber(13);
                    QCDLeptonList.push_back(*it);
                }
            }
            //we can not do the fr if we tag the muons!!
            //else if (MuonList->size()==1){
                //passedID++;
                //tmpMuo=( pxl::Particle* ) MuonList->at(0);
                //break;
            //}
        }
        if(passedID>=1){
            qcd_lepton=QCDLeptonList.at(0);
            m_pt_min_cut=m_pt_min_cut_muo;
            m_delta_phi_cut=m_delta_phi_cut_muo;
            m_pt_met_min_cut=m_pt_met_min_cut_muo;
            m_pt_met_max_cut=m_pt_met_max_cut_muo;

            m_pt_met_min_cut_funk_root=m_pt_met_min_cut_funk_root_muo;
            m_pt_met_max_cut_funk_root=m_pt_met_max_cut_funk_root_muo;
            m_delta_phi_cut_funk_root=m_delta_phi_cut_funk_root_muo;
            qcd_id=13;
        }
    }

    if(sel_met && qcd_lepton && qcd_lepton->getPt()>m_pt_min_cut){
        if(qcd_id==11){
            qcd_weight = max(0.,qcd_weight_ele_pt->GetBinContent(qcd_weight_ele_pt->FindBin(qcd_lepton->getPt())));
            for(unsigned int i=1;  i<QCDLeptonList.size();i++){
                qcd_weight*=(1-max(0.,qcd_weight_ele_pt->GetBinContent(qcd_weight_ele_pt->FindBin(QCDLeptonList[i]->getPt()))));
            }
            //for(unsigned int j=0;  j<QCDLeptonList.size();j++){
                //qcd_weight = max(0.,qcd_weight_ele_pt->GetBinContent(qcd_weight_ele_pt->FindBin(QCDLeptonList[j]->getPt())));
                //for(unsigned int i=0;  i<QCDLeptonList.size();i++){
                    //if(i==j){
                        //continue;
                    //}
                    //qcd_weight*=(1-max(0.,qcd_weight_ele_pt->GetBinContent(qcd_weight_ele_pt->FindBin(QCDLeptonList[i]->getPt()))));
                //}
            //}
        }

        if(qcd_id==13){
            qcd_weight = max(0.,qcd_weight_muo_pt->GetBinContent(qcd_weight_muo_pt->FindBin(qcd_lepton->getPt())));
        }
        if(qcd_id==15){
            qcd_weight = max(0.,qcd_weight_tau_pt->GetBinContent(qcd_weight_tau_pt->FindBin(qcd_lepton->getUserRecord("decayMode"))));
        }
        double mt=MT(qcd_lepton,sel_met);
        m_pt_met_min_cut=   m_pt_met_min_cut_funk_root.Eval(mt);
        m_pt_met_max_cut=   m_pt_met_max_cut_funk_root.Eval(mt);
        m_delta_phi_cut=    m_delta_phi_cut_funk_root.Eval(mt);

        if(qcd_lepton->getPt()/sel_met->getPt()>m_pt_met_min_cut && qcd_lepton->getPt()/sel_met->getPt()<m_pt_met_max_cut){
            passedPtMet=true;
        }
        if(DeltaPhi(qcd_lepton->getPhi(),sel_met->getPhi())>m_delta_phi_cut){
            passedDeltaPhi=true;
        }
        if (passedDeltaPhi && passedPtMet){
            passed=true;
        }
    }
    if(qcd_lepton){
        qcd_lepton->setUserRecord("passedPtMet",passedPtMet);
        qcd_lepton->setUserRecord("passedDeltaPhi",passedDeltaPhi);
        qcd_lepton->setUserRecord("passed",passed);
        qcd_lepton->setPdgNumber(qcd_id);
    }

}
*/
int MiniAODAnalyzer::vetoNumberEle(double ptTreshold,double vetoConeSize){
    //make veto numbers
    //we don't need std::vectors, do we?
    int numVeto=0;
    int posi=0;
    for( auto part: *electrons) {
        if( part.pt()>ptTreshold && (EleIDPassed[posi]==1) ){
            bool veto_tau=false; //if particle is used as tau
            int i=0;
            for( auto tau : *taus ){
                if( PassTauID(tau) && DeltaR(part,tau)<vetoConeSize){
                    veto_tau=true;
                }
                i++;
            }
            if(not veto_tau){
                numVeto++;
            }
        }else if(part.pt()<ptTreshold) {
        ///    Lists are Pt sorted
            break;
        }
        posi++;
    }
    return numVeto;
}
int MiniAODAnalyzer::vetoNumberMuon(double ptTreshold,double vetoConeSize){
    //make veto numbers
    //we don't need std::vectors, do we?
    int numVeto=0;
    int posi=0;
    for( auto part: *muons) {
        if( part.pt()>ptTreshold && (MuonIDPassed[posi]==1) ){
            bool veto_tau=false; //if particle is used as tau
            int i=0;
            for( auto tau : *taus ){
                if( PassTauID(tau) && DeltaR(part,tau)<vetoConeSize){
                    veto_tau=true;
                }
                i++;
            }
            if(not veto_tau){
                numVeto++;
            }
        }else if(part.pt()<ptTreshold) {
        ///    Lists are Pt sorted
            break;
        }
        posi++;
    }
    return numVeto;

}


int MiniAODAnalyzer::vetoNumberTau(double ptTreshold){
    //make veto numbers
    //we don't need std::vectors, do we?
    int numVeto=0;
    bool passedID=false;
    for (auto tau: *taus){
        passedID=false;
        passedID=PassTauID(tau);
        if( tau.pt()>ptTreshold && passedID ){
            numVeto++;
        }else if(tau.pt()<ptTreshold) {
            ///Lists are Pt sorted
            break;
        }
    }
    return numVeto;
}

void MiniAODAnalyzer::QCDAnalyseTau( const pat::MET sel_met,double weight,edm::Handle<edm::View<reco::GenParticle>> genPart) {
//void MiniAODAnalyzer::QCDAnalyseTau( const pat::MET sel_met) {

    double ptTauTreshold=80;
    double m_leptonVetoPt=20;
    double vetoConeSize=0.3;
    //int numVetoMuo=vetoNumberMuon(MuonList, m_leptonVetoPt,TauList,vetoConeSize);
    int numVetoMuo=vetoNumberMuon(m_leptonVetoPt,vetoConeSize);
    int numVetoTau=vetoNumberTau(ptTauTreshold);
    int numVetoEle=vetoNumberEle(m_leptonVetoPt,vetoConeSize);

    //std::cout << numVetoEle << " Muo Vetos " << numVetoMuo << " taus size "<<taus->size()<< std::endl;
    if( ( (numVetoEle==1) xor (numVetoMuo==1 )) && taus->size()>=1){
        pat::Electron eleCandi;
        pat::Muon muoCandi;
        int i=0;
        bool eleBool=false;
        for( auto part: *electrons) {
            if( part.pt()>m_leptonVetoPt && EleIDPassed[i]==1 ){
                eleCandi=(part);
                eleBool=true;
                break;
            }
            i++;
        }
        if (eleBool) std::cout << "electron passed " << std::endl;
        i=0;
        bool muonBool=false;
        //for( auto part: MuonList) {
        for( auto part: *muons) {
            if( part.pt()>m_leptonVetoPt && MuonIDPassed[i]==1 ){
                muoCandi=(part);
                muonBool=true;
                break;
            }
            i++;
        }
        if(eleBool==false and muonBool==false){
            return;
        }
        /// make it shorter
        FakeCandPt.clear();
        FakeCandPhi.clear();
        FakeCandEta.clear();
        FakeCandMET.clear();
        FakeCandMETPhi.clear();
        FakeCandDeltaPhi.clear();
        FakeCandIso.clear();
        FakeCandNoIso.clear();
        FakeCandVetoNum.clear();
        FakeCandLorentz.clear();
        FakeCandDecayMode.clear();
        FakeCandLeptonType.clear();
        FakeCandLeptonMt.clear();
        FakeCandLeptonDeltaPhi.clear();
        FakeCandLeptonPt.clear();
        FakeCandLeptonEta.clear();
        FakeCandLeptonPhi.clear();
        FakeCandLeptonTrigger.clear();
        for( auto tau: *taus ) {
            if(muonBool && DeltaR(muoCandi,tau)<vetoConeSize){
                continue;
            }
            if(eleBool &&  DeltaR(eleCandi,tau)<vetoConeSize){
                continue;
            }

            if( not PassTauID_NonIsolated(tau)  and not PassTauID(tau)){
                continue;
            }
            bool m_do_complicated_tau_stuff=false;
            if(!m_do_complicated_tau_stuff){
                //cout<<"ele   "<<eleTrig<<"   "<<eleCandi<<endl;
                //cout<<"muon   "<<muoTrig<<"   "<<muoCandi<<endl;
                //cout<<"------------------------- "<<endl;


                mFakeTree["mt"]=calcMT(tau,sel_met);
                FakeCandMt.push_back(calcMT(tau,sel_met));
                mFakeTree["delta_phi"]=DeltaPhi(tau,sel_met);
                FakeCandDeltaPhi.push_back(DeltaPhi(tau,sel_met));
                mFakeTree["pt"]=tau.pt();
                FakeCandPt.push_back(tau.pt());
                mFakeTree["met"]=sel_met.pt();
                FakeCandMET.push_back(sel_met.pt());
                mFakeTree["phi"]=tau.phi();
                FakeCandPhi.push_back(tau.phi());
                mFakeTree["eta"]=tau.eta();
                FakeCandEta.push_back(tau.eta());
                mFakeTree["met_phi"]=sel_met.phi();
                FakeCandMETPhi.push_back(sel_met.phi());
                mFakeTree["iso"]=PassTauID(tau);
                FakeCandIso.push_back(PassTauID(tau));
                mFakeTree["noiso"]=PassTauID(tau);
                FakeCandNoIso.push_back(PassTauID(tau));
                mFakeTree["tau_n"]=numVetoTau;
                FakeCandVetoNum.push_back(numVetoTau);
                mFakeTree["decay_mode"]=tau.decayMode();
                FakeCandDecayMode.push_back(tau.decayMode());



/*                mFakeTree["truth_match"]=(not runOnData and Get_Truth_match("Tau",*it)) ;
                if((*it)->hasUserRecord("decayMode")){
                    mFakeTree["decay_mode"]=(*it)->getUserRecord("decayMode").toDouble();
                }else{
                    mFakeTree["decay_mode"]=-1;
                }
                */if(muonBool){
                    mFakeTree["lepton_type"]=13;
                    FakeCandLeptonType.push_back(13);
                    mFakeTree["lepton_mt"]=calcMT(muoCandi,sel_met);
                    FakeCandLeptonMt.push_back(calcMT(muoCandi,sel_met));
                    mFakeTree["lepton_delta_phi"]=DeltaPhi(muoCandi,sel_met);
                    FakeCandLeptonDeltaPhi.push_back(DeltaPhi(muoCandi,sel_met));
                    mFakeTree["lepton_pt"]=muoCandi.pt();
                    FakeCandLeptonPt.push_back(muoCandi.pt());
                    mFakeTree["lepton_eta"]=muoCandi.eta();
                    FakeCandLeptonEta.push_back(muoCandi.eta());
                    mFakeTree["lepton_phi"]=muoCandi.phi();
                    FakeCandLeptonPhi.push_back(muoCandi.phi());
                    mFakeTree["lepton_trigger"]=passMuonTrig;
                    FakeCandLeptonTrigger.push_back(passMuonTrig);
                }
                if (eleBool){
                    mFakeTree["lepton_type"]=11;
                    FakeCandLeptonType.push_back(11);
                    mFakeTree["lepton_mt"]=calcMT(eleCandi,sel_met);
                    FakeCandLeptonMt.push_back(calcMT(eleCandi,sel_met));
                    mFakeTree["lepton_delta_phi"]=DeltaPhi(eleCandi,sel_met);
                    FakeCandLeptonDeltaPhi.push_back(DeltaPhi(eleCandi,sel_met));
                    mFakeTree["lepton_pt"]=eleCandi.pt();
                    FakeCandLeptonPt.push_back(eleCandi.pt());
                    mFakeTree["lepton_eta"]=eleCandi.eta();
                    FakeCandLeptonEta.push_back(eleCandi.eta());
                    mFakeTree["lepton_phi"]=eleCandi.phi();
                    FakeCandLeptonPhi.push_back(eleCandi.phi());
                    mFakeTree["lepton_trigger"]=passEleTrig;
                    FakeCandLeptonTrigger.push_back(passEleTrig);
                }

                //general
                mFakeTree["ThisWeight"]=weight;


                helper->Tree_Filler("fakeTree");
                if(PassTauID_NonIsolated(tau)){
                    helper->Fill(0,"Tau_fake_pt",tau.pt(),weight);
                    if(muonBool)
                        helper->Fill(1,"Tau_fake_pt",muoCandi.pt(),weight);
                    if(eleBool)
                        helper->Fill(2,"Tau_fake_pt",eleCandi.pt(),weight);
                    helper->Fill( "Tau_fake_pt_eta",tau.pt(),tau.eta(),weight );
                    helper->Fill( "Tau_fake_pt_met",tau.pt(),sel_met.pt(),weight );
                    helper->Fill( "Tau_fake_pt_decay",tau.pt(),tau.decayMode(),weight );
                   //if(not RunOnData and GetTruthMatch("Tau",tau) ){
                   if(not RunOnData  ){
                       GetTruthMatch("Tau",tau);
                        if(muonBool)
                            helper->Fill(1,"Tau_fake_pt_true",muoCandi.pt(),weight);
                            helper->Fill(3,"Tau_fake_pt_true",tau.pt(),weight);
                        if(eleBool)
                            helper->Fill(2,"Tau_fake_pt_true",eleCandi.pt(),weight);
                            helper->Fill(4,"Tau_fake_pt_true",tau.pt(),weight);
                        helper->Fill(0,"Tau_fake_pt_true",tau.pt(),weight);
                        helper->Fill( "Tau_fake_pt_eta_true",tau.pt(),tau.eta(),weight );
                        helper->Fill( "Tau_fake_pt_met_true",tau.pt(),sel_met.pt(),weight );
                        helper->Fill( "Tau_fake_pt_decay_true",tau.pt(),tau.decayMode(),weight );
                    }else if(not RunOnData ){
                        reco::GenParticle* genMatch= GetTruthMatchAllFlavor(tau);
                        if(genMatch){
                            //lightquarks
                            if(abs(genMatch->pdgId())<5){
                                helper->Fill(0,"Tau_fake_pt_lightquark",tau.pt(),weight);
                                //HistClass::Fill( "Tau_fake_pt_eta_lightquark",tau.pt(),tau.eta(),weight );
                                //HistClass::Fill( "Tau_fake_pt_met_lightquark",tau.pt(),sel_met.pt(),weight );
                            //b quarks
                            }else if(abs(genMatch->pdgId())==5){
                                helper->Fill(0,"Tau_fake_pt_bquark",tau.pt(),weight);
                                //HistClass::Fill( "Tau_fake_pt_eta_bquark",tau.pt(),tau.eta(),weight );
                                //HistClass::Fill( "Tau_fake_pt_met_bquark",tau.pt(),sel_met.pt(),weight );
                            }else if(abs(genMatch->pdgId())==9 or abs(genMatch->pdgId())==21){
                                helper->Fill(0,"Tau_fake_pt_gluon",tau.pt(),weight);
                                //HistClass::Fill( "Tau_fake_pt_eta_gluon",tau.pt(),tau.eta(),weight );
                                //HistClass::Fill( "Tau_fake_pt_met_gluon",tau.pt(),sel_met.pt(),weight );
                            }else if(abs(genMatch->pdgId())==11 or abs(genMatch->pdgId())==13){
                                 helper->Fill(0,"Tau_fake_pt_lightlepton",tau.pt(),weight);
                                //HistClass::Fill( "Tau_fake_pt_eta_gluon",tau.pt(),tau.eta(),weight );
                                //HistClass::Fill( "Tau_fake_pt_met_gluon",tau.pt(),sel_met.pt(),weight );
                            }else{
                                helper->Fill(0,"Tau_fake_pt_unmatched",tau.pt(),weight);
                                std::cout<<"unassociated match: "<<genMatch->pdgId()<<std::endl;
                            }

                        }


                    }
                }
                else if(PassTauID(tau)){
                    helper->Fill(0,"Tau_nofake_pt",tau.pt(),weight);
                    if(muonBool)
                        helper->Fill(1,"Tau_nofake_pt",muoCandi.pt(),weight);
                        helper->Fill(3,"Tau_nofake_pt",tau.pt(),weight);
                    if(eleBool)
                        helper->Fill(2,"Tau_nofake_pt",eleCandi.pt(),weight);
                        helper->Fill(4,"Tau_nofake_pt",tau.pt(),weight);
                    helper->Fill( "Tau_nofake_pt_eta",tau.pt(),tau.eta(), weight );
                    helper->Fill( "Tau_fake_pt_met",tau.pt(),sel_met.pt(),weight );
                    if(tau.decayMode())
                        helper->Fill( "Tau_nofake_pt_decay",tau.pt(),tau.decayMode(), weight );
                    if(not RunOnData and GetTruthMatch("Tau",tau) ){
                        helper->Fill(0,"Tau_nofake_pt_true",tau.pt(),weight);
                        helper->Fill( "Tau_nofake_pt_eta_true",tau.pt(),tau.eta(), weight );
                        helper->Fill( "Tau_fake_pt_met_true",tau.pt(),sel_met.pt(),weight );
                        if(tau.decayMode())
                            helper->Fill( "Tau_nofake_pt_decay_true",tau.pt(),tau.decayMode(), weight );
                    }else if(not RunOnData ){
                        reco::GenParticle* genMatch= GetTruthMatchAllFlavor(tau);
                        if(genMatch){
                            //lightquarks
                            if(abs(genMatch->pdgId())<5){
                                helper->Fill(0,"Tau_nofake_pt_lightquark",tau.pt(),weight);
                                //helper->Fill( "Tau_nofake_pt_eta_lightquark",tau.pt(),tau.eta(),weight );
                                //helper->Fill( "Tau_nofake_pt_met_lightquark",tau.pt(),sel_met.pt(),weight );
                            //b quarks
                            }else if(abs(genMatch->pdgId())==5){
                                helper->Fill(0,"Tau_nofake_pt_bquark",tau.pt(),weight);
                                //helper->Fill( "Tau_nofake_pt_eta_bquark",tau.pt(),tau.eta(),weight );
                                //helper->Fill( "Tau_nofake_pt_met_bquark",tau.pt(),sel_met.pt(),weight );
                            }else if(abs(genMatch->pdgId())==9 or abs(genMatch->pdgId())==21){
                                helper->Fill(0,"Tau_nofake_pt_gluon",tau.pt(),weight);
                                //helper->Fill( "Tau_nofake_pt_eta_gluon",tau.pt(),tau.eta(),weight );
                                //helper->Fill( "Tau_nofake_pt_met_gluon",tau.pt(),sel_met.pt(),weight );
                            }else if(abs(genMatch->pdgId())==11 or abs(genMatch->pdgId())==13){
                                 helper->Fill(0,"Tau_nofake_pt_lightlepton",tau.pt(),weight);
                                //helper->Fill( "Tau_nofake_pt_eta_gluon",tau.pt(),tau.eta(),weight );
                                //helper->Fill( "Tau_nofake_pt_met_gluon",tau.pt(),sel_met.pt(),weight );
                            }else{
                                helper->Fill(0,"Tau_nofake_pt_unmatched",tau.pt(),weight);
                                std::cout<<"unassociated match: "<<genMatch->pdgId()<<std::endl;
                            }

                        }


                    }

                }
            }/*else{//do complicated tau stuff
                for(std::vector<std::string>::iterator disc_it = d_mydisc.begin(); disc_it != d_mydisc.end(); disc_it++){
                    //if(PassTauID_NonIsolated(tau,*disc_it)){
                    if(PassTauID_NonIsolated(tau)){
                        helper->Fill(0,Form("Tau_fake_pt_%s",(*disc_it).c_str()),tau.pt(),weight);
                        helper->Fill( Form("Tau_fake_pt_eta_%s",(*disc_it).c_str()),tau.pt(),tau.eta(),weight );
                        helper->Fill( Form("Tau_fake_pt_met_%s",(*disc_it).c_str()),tau.pt(),sel_met.pt(),weight );
                        if(tau.decayMode())
                            helper->Fill( Form("Tau_fake_pt_decay_%s",(*disc_it).c_str()),tau.pt(),tau.decayMode().toDouble(),weight );
                        if(not RunOnData and GetTruthMatch("Tau",tau) ){
                            helper->Fill(0,Form("Tau_fake_pt_%s_true",(*disc_it).c_str()),tau.pt(),weight);
                            helper->Fill( Form("Tau_fake_pt_eta_%s_true",(*disc_it).c_str()),tau.pt(),tau.eta(),weight );
                            helper->Fill( Form("Tau_fake_pt_met_%s_true",(*disc_it).c_str()),tau.pt(),sel_met.pt(),weight );
                            if(tau.decayMode())
                                helper->Fill( Form("Tau_fake_pt_decay_%s_true",(*disc_it).c_str()),tau.pt(),tau.decayMode().toDouble(),weight );
                        }
                    }
                    //else if(PassTauID(tau,*disc_it)){
                    else if(PassTauID(tau)){
                        helper->Fill(0,Form("Tau_nofake_pt_%s",(*disc_it).c_str()),tau.pt(),weight);
                        helper->Fill( Form("Tau_nofake_pt_eta_%s",(*disc_it).c_str()),tau.pt(),tau.eta(), weight );
                        helper->Fill( Form("Tau_fake_pt_met_%s",(*disc_it).c_str()),tau.pt(),sel_met.pt(),weight );
                        if(tau-decayMode())
                            helper->Fill( Form("Tau_nofake_pt_decay_%s",(*disc_it).c_str()),tau.pt(),tau.decayMode(), weight );
                        if(not RunOnData and Get_Truth_match("Tau",tau) ){
                            helper->Fill(0,Form("Tau_nofake_pt_%s_true",(*disc_it).c_str()),tau.pt(),weight);
                            helper->Fill( Form("Tau_nofake_pt_eta_%s_true",(*disc_it).c_str()),tau.pt(),tau.eta(), weight );
                            helper->Fill( Form("Tau_fake_pt_met_%s_true",(*disc_it).c_str()),tau.pt(),sel_met.pt(),weight );
                            if(tau.decayMode())
                                helper->Fill( Form("Tau_nofake_pt_decay_%s_true",(*disc_it).c_str()),tau.pt(),tau.decayMode(), weight );

                        }
                    }
                }
            }*/
        }

        //std::cout << FakeCandDeltaPhi.size() << " " << FakeCandPt.size() << std::endl;
        /*
        mFakeVectorTree["FakeCandPt"]=FakeCandPt;
        mFakeVectorTree["FakeCandPhi"]=FakeCandPhi;
        mFakeVectorTree["FakeCandEta"]=FakeCandEta;
        mFakeVectorTree["FakeCandMET"]=FakeCandMET;
        mFakeVectorTree["FakeCandMETPhi"]=FakeCandMETPhi;
        mFakeVectorTree["FakeCandDeltaPhi"]=FakeCandDeltaPhi;
        mFakeVectorTree["FakeCandIso"]=FakeCandIso;
        mFakeVectorTree["FakeCandNoIso"]=FakeCandNoIso;
        mFakeVectorTree["FakeCandVetoNum"]=FakeCandVetoNum;*/

        //std::cout << FakeCandEta[-1] << std::endl;
        helper->Tree_Filler("fakeVectorTree");
    }
}

//reco::GenParticle MiniAODAnalyzer::GetTruthMatch(std::string name, auto lepton) {
reco::GenParticle* MiniAODAnalyzer::GetTruthMatch(std::string name, auto lepton) {
    if (tauGenMatchMap.end()  !=tauGenMatchMap.find(&lepton)){
        return tauGenMatchMap[&lepton];
    }
    int part_temp_id = 0;
    if (name == "Tau") {
        part_temp_id = 15;
    } else if (name ==  "Muon") {
        part_temp_id = 13;
    } else if (name == "Ele") {
        part_temp_id = 11;
    }
    double temp_delta_r = 2;
    reco::GenParticle gen_match;
    for (auto part_i: *pruned){
        int part_temp_truth_id = 0;
            part_temp_truth_id = TMath::Abs(part_i.pdgId());
        if (part_temp_id != part_temp_truth_id) continue;
        double test_delta_r = DeltaR(lepton,part_i);
        if (test_delta_r < temp_delta_r) {
            temp_delta_r = test_delta_r;
            gen_match = part_i;
        }
    }
    tauGenMatchMap[&lepton]=&gen_match;
    return tauGenMatchMap[&lepton];
}
reco::GenParticle* MiniAODAnalyzer::GetTruthMatchAllFlavor(auto lepton) {
    if (tauGenMatchMapAllFlav.end()  !=tauGenMatchMapAllFlav.find(&lepton)){
        return tauGenMatchMapAllFlav[&lepton];
    }
    double temp_delta_r = 0.5;
    reco::GenParticle gen_match;
    for (auto part_i: *pruned){
        double test_delta_r = DeltaR(lepton,part_i);
        if (test_delta_r < temp_delta_r && fabs(lepton.pt()-part_i.pt())/part_i.pt()<0.5 && abs(part_i.pdgId())<22 && abs(part_i.pdgId())!=12 && abs(part_i.pdgId())!=14 && abs(part_i.pdgId())!=16) {
            temp_delta_r = test_delta_r;
            gen_match = part_i;
        }
    }
    tauGenMatchMapAllFlav[&lepton]=&gen_match;
    return tauGenMatchMap[&lepton];
}

/*
pxl::Particle* specialAna::Get_Truth_match_all_flavor(pxl::Particle* lepton) {
    if (gen_match_map_all_flav.end()  !=gen_match_map_all_flav.find(lepton)){
        return gen_match_map_all_flav[lepton];
    }
    double temp_delta_r = 0.5;
    pxl::Particle* gen_match = 0;
    for (std::vector< pxl::Particle* >::const_iterator part_it = S3ListGen->begin(); part_it != S3ListGen->end(); ++part_it) {
        pxl::Particle *part_i = *part_it;
        double test_delta_r = lepton->getVector().deltaR(part_i->getVector());
        if (test_delta_r < temp_delta_r && fabs(lepton->getPt()-part_i->getPt())/part_i->getPt()<0.5 && abs(part_i->getPdgNumber())<23 && abs(part_i->getPdgNumber())!=12 && abs(part_i->getPdgNumber())!=14 && abs(part_i->getPdgNumber())!=16 && abs(part_i->getPdgNumber())!=22 ) {
            temp_delta_r = test_delta_r;
            gen_match = part_i;
        }
    }
    gen_match_map_all_flav[lepton]=gen_match;
    return gen_match;
}*/


//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODAnalyzer);



