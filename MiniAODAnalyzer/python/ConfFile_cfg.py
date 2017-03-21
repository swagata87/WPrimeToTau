import FWCore.ParameterSet.Config as cms

import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("Demo")
options = VarParsing.VarParsing('analysis')
options.register ('sourceFileStringInput',
                  'default', # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "Name of the sample")
options.parseArguments()

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag

#  as a rule, find the "auto" global tag in $CMSSW_RELEASE_BASE/src/Configuration/AlCa/python/autoCond.py
#  This auto global tag will look up the "proper" global tag
#  that is typically found in the DAS under the Configs for given dataset
#  (although it can be "overridden" by requirements of a given release)

#80X_mcRun2_asymptotic_2016_TrancheIV_v6
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')     # MC

#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v6', '')     # MC

#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')  # OBSOLETE?? DATA

#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016SeptRepro_v7', '')  # reminiaod DATA B-G

#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v16', '')  # reminiaod DATA H

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.load("WPrimeToTau.MiniAODAnalyzer.METFilters_cff")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#    ignoreTotal = cms.untracked.int32(1),
#    moduleMemorySummary = cms.untracked.bool(True),
#)

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = [
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff'
  # 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff'
    ]
#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
##2015##
#'/store/mc/RunIIFall15MiniAODv2/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/60000/D8E02B5E-49B9-E511-BBF6-D8D385AE84C4.root'
## Moriond 17 samples ##
#'/store/mc/RunIISummer16MiniAODv2/WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/0E082AEC-4FBE-E611-A1E6-FA163EF4D564.root'
'/store/mc/RunIISummer16MiniAODv2/WprimeToTauNUGIM_M600_gL1p5-madgraph/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/4C54A632-C0C9-E611-8A77-008CFA0A5844.root'
#'/store/mc/RunIISummer16MiniAODv2/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/80000/000DDA5C-82D3-E611-A60D-A4BF0100DD3E.root'
#'/store/mc/RunIISummer16MiniAODv2/WprimeToTauNu_M-1200_TuneCUETP8M1_13TeV-pythia8-tauola/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/70000/006926C1-1EB7-E611-93A8-ECB1D79E5C40.root'
#'/store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/100000/04FAFBA6-3AD2-E611-99C0-90B11C1453E1.root'
#'/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/0693E0E7-97BE-E611-B32F-0CC47A78A3D8.root'
#'/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/0806AB92-99BE-E611-9ECD-0025905A6138.root'
#'/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/165F54A0-A3BE-E611-B3F7-0025905A606A.root'
#'/store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/3CCF34DF-9DBE-E611-9512-0025905B858E.root'
##
#        '/store/data/Run2016G/Tau/MINIAOD/23Sep2016-v1/110000/8267B1F2-B89E-E611-BE7F-0CC47A4D76C0.root'
#        '/store/data/Run2016F/Tau/MINIAOD/03Feb2017-v1/110000/029DABBB-A2EB-E611-938D-A0000420FE80.root'
    )
#    eventsToProcess = cms.untracked.VEventRange('1:40000-1:86000'),
)

process.demo = cms.EDAnalyzer('MiniAODAnalyzer',
       doFakeHist_ = cms.bool(True),
       doTrees_ = cms.bool(True),
       useReweighting = cms.bool(True),
       RunOnData_ = cms.bool(False),
#       RunOnData_ = cms.bool(True),
### generatorName required only for madgraph and powheg. For other cases one can just write "default"
#       generatorName = cms.string("madgraphMLM"),
       generatorName = cms.string("default"),
#       generatorName = cms.string("powheg"),
### correct pdfName required only for madgraph, for other cases one can just write "default"
#       pdfName = cms.string("NNPDF30_lo_as_0130.LHgrid"),   # madgraphMLM
#       pdfName = cms.string("NNPDF23_lo_as_0130_qed.LHgrid"), # NUGIM madgraph
       pdfName = cms.string("default"),   # powheg and others
       debugLevel_ = cms.int32(0),
       vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
       taus = cms.InputTag("slimmedTaus"),
       muons = cms.InputTag("slimmedMuons"),
       electrons = cms.InputTag("slimmedElectrons"),
       jets = cms.InputTag("slimmedJets"),
       met = cms.InputTag("slimmedMETs"),
       met_reminiaod = cms.InputTag("slimmedMETsMuEGClean"),
       bits = cms.InputTag("TriggerResults","","HLT"),
#       bits_MET = cms.InputTag("TriggerResults","","RECO"), ## OBSOLETE ##use only for old data
       bits_MET = cms.InputTag("TriggerResults","","PAT"),  ##for MC and reminiAOD DATA
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
       KFactorE = cms.string("k_faktors_ele.root"),
       KFactorMu = cms.string("k_faktors_mu.root"),
       KFactorTau = cms.string("k_faktors_tau.root"),
       QCDWeightTau = cms.string("qcdFakeOutput15pt_eta.root"),
       #sourceFileString = cms.string(process.source_().dumpConfig().split('\n')[2].split("/")[4]),
       sourceFileString = cms.string(options.sourceFileStringInput),                       
       BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
       BadPFMuonFilter = cms.InputTag("BadPFMuonFilter"),
       eleIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1"),
    #  eleIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
#       LHEEventTag = cms.InputTag("externalLHEProducer","","LHE"),
       LHEEventTag = cms.InputTag("source","","LHEFile"),
       tag = cms.untracked.string("initrwgt"),
       doPDFuncertainty_ = cms.bool(False),

)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('hist_analysis.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

#process.run = cms.Path(process.BadPFMuonFilter *process.BadChargedCandidateFilter)

process.p = cms.Path(process.METFiltersSequence*process.egmGsfElectronIDSequence*process.demo)
#process.demo)
#process.p = cms.Path(process.demo)
