import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.load("WPrimeToTau.MiniAODAnalyzer.METFilters_cff")

## MET filter ## 
#process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
#process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
#process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
##
#process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
#process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
#process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
##

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      # '/store/mc/RunIISpring16MiniAODv2/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/70000/7E9A7536-7A1A-E611-9149-001E67A4055F.root'
#        '/store/mc/RunIIFall15MiniAODv1/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/1AF74AF6-BFA6-E511-96DF-0CC47A1DF7F8.root'
#        '/store/mc/RunIIFall15MiniAODv1/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/26FC919F-C3A6-E511-9A22-0CC47A4D7674.root'
        '/store/mc/RunIISpring16MiniAODv2/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/0A8E0285-A92B-E611-A376-00259081ED0A.root'
# '/store/mc/RunIISpring16MiniAODv2/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/046410F1-7736-E611-8F28-A0000420FE80.root',
#        '/store/mc/RunIISpring16MiniAODv2/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/000C4CF4-CC21-E611-9D0A-0025905C54FE.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/60000/02433DFA-0720-E611-9323-1CB72C1B65D4.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/40000/006F5A7A-7D24-E611-97BB-B083FED43141.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/06A61384-FA1A-E611-8E7E-B083FED3F2E9.root',
#        '/store/mc/RunIISpring16MiniAODv2/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/00000/1EA04C7F-FA1A-E611-A203-1418774124DE.root'
#        '/store/mc/RunIISpring16MiniAODv2/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/70000/008C40ED-811D-E611-95E9-00259029E87C.root'
#        '/store/mc/RunIISpring16MiniAODv2/WW_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/50000/1C2B19A5-471B-E611-916B-008CFA111200.root'
#        '/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v2/70000/00287FF4-0E40-E611-8D06-00266CFE78EC.root'
#      '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/150/00000/64EFFDF2-D719-E611-A0C3-02163E01421D.root',
#      '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/158/00000/D464EE02-D919-E611-8D74-02163E013917.root',
#      '/store/data/Run2016B/Tau/MINIAOD/PromptReco-v2/000/273/290/00000/4C630F9E-191A-E611-AEB5-02163E013716.root'
#        '/store/data/Run2016B/Tau/MINIAOD/01Jul2016-v2/20000/02C0A083-734F-E611-A834-549F35AF44AF.root'
    )
)

process.demo = cms.EDAnalyzer('MiniAODAnalyzer',
       outputFile = cms.string('analysis.root'),
       RunOnData_ = cms.bool(False),
#       RunOnData_ = cms.bool(True),
### generatorName required only for madgraph and powheg. For other cases one can just write "default"
#       generatorName = cms.string("madgraphMLM"),
       generatorName = cms.string("default"),
#       generatorName = cms.string("powheg"),
### correct pdfName required only for madgraph, for other cases one can just write "default"
#       pdfName = cms.string("NNPDF30_lo_as_0130.LHgrid"),   # madgraphMLM                    
       pdfName = cms.string("default"),   # powheg and others                    
       debugLevel_ = cms.int32(0),                       
       vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
       taus = cms.InputTag("slimmedTaus"),
       muons = cms.InputTag("slimmedMuons"),
       electrons = cms.InputTag("slimmedElectrons"),
       mets = cms.InputTag("slimmedMETs"),
       bits = cms.InputTag("TriggerResults","","HLT"),
#       bits_MET = cms.InputTag("TriggerResults","","RECO"),  ##for data
       bits_MET = cms.InputTag("TriggerResults","","PAT"),  ##for MC
       prescales = cms.InputTag("patTrigger"),
       packed = cms.InputTag("packedGenParticles"),
       pruned = cms.InputTag("prunedGenParticles"),
       objects = cms.InputTag("selectedPatTrigger"),
       genEventInfoProductMiniAOD = cms.InputTag('generator'),
       pileupCollection = cms.InputTag("slimmedAddPileupInfo"),
       PileupMCFile = cms.string("MC_pileup.root"),
       PileupDataFile = cms.string("Data_pileup_normalized.root"),
       PileupDataFile_UP = cms.string("Data_pileup_normalized_UP.root"),
       PileupDataFile_DOWN = cms.string("Data_pileup_normalized_DOWN.root"),                       
       BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"), 
       BadPFMuonFilter = cms.InputTag("BadPFMuonFilter"),
       LHEEventTag = cms.InputTag("externalLHEProducer","","LHE"),
#       LHEEventTag = cms.InputTag("source","","LHEFile")
       tag = cms.untracked.string("initrwgt"),
       doPDFuncertainty_ = cms.bool(True),

)

#process.out = cms.OutputModule("PoolOutputModule",
#        fileName = cms.untracked.string('analysis.root')
#)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('hist_analysis.root')
)

#process.run = cms.Path(process.BadPFMuonFilter *process.BadChargedCandidateFilter)

process.p = cms.Path(process.METFiltersSequence*process.demo) 
#process.demo)
#process.p = cms.Path(process.demo)
