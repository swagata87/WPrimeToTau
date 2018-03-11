from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
#config.JobType.outputFiles = ['analysis.root','hist_analysis.root']
config.JobType.outputFiles = ['hist_analysis.root']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root', 'k_faktors_ele.root', 'k_faktors_mu.root', 'k_faktors_tau.root','METFilters_cff.py','qcdFakeOutput15pt_eta.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/crab_2017_Nov14/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'WPrimeToTaus_2017_Nov14'
config.Site.storageSite = 'T2_DE_RWTH'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_2017_Nov14'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

## Background ##
##

## NUGIM ##

#    config.General.requestName = 'WprimeToTauNUGIM_M800_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M800_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M800_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M600_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M600_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M600_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M4500_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M4500_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M4500_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M400_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M400_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M400_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M4000_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M4000_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M4000_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3800_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3800_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3800_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3600_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3600_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3600_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#   config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3400_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3400_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3400_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3200_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3200_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3200_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3000_gL1p9-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3000_gL1p9-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3000_gL1p9-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3000_gL1p7-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3000_gL1p7-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3000_gL1p7-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3000_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3000_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3000_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3000_gL1p3-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3000_gL1p3-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3000_gL1p3-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M3000_gL1p1-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M3000_gL1p1-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M3000_gL1p1-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2800_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2800_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2800_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2600_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2600_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2600_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2400_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2400_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2400_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2200_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2200_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2200_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2000_gL1p9-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2000_gL1p9-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2000_gL1p9-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2000_gL1p7-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2000_gL1p7-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2000_gL1p7-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2000_gL1p3-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2000_gL1p3-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2000_gL1p3-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M2000_gL1p1-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M2000_gL1p1-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M2000_gL1p1-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M1800_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M1800_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M1800_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M1600_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M1600_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M1600_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNUGIM_M1000_gL1p5-madgraph'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNUGIM_M1000_gL1p5-madgraph']
#    config.Data.inputDataset = '/WprimeToTauNUGIM_M1000_gL1p5-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)



## ZJets
##
    config.General.requestName = 'ZJetsToNuNu_HT-100To200_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-100To200_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 1
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-100To200_13TeV-madgraph_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-100To200_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 1
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-200To400_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-200To400_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-200To400_13TeV-madgraph_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-200To400_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-400To600_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-400To600_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-400To600_13TeV-madgraph_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-400To600_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-600To800_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-600To800_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-600To800_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-800To1200_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-800To1200_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-1200To2500_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-1200To2500_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-1200To2500_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph']
    config.Data.inputDataset = '/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## QCD
##
    config.General.requestName = 'QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

#
## Wjets HT binned sample ##
##
    config.General.requestName = 'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext2'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    
    config.General.requestName = 'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext2'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
##
## WJets flat sample ##
##
    config.General.requestName = 'WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext2'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
## DY ##
    config.General.requestName = 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
    config.General.requestName = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext2'
    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
    config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)
    
##ZtoMuMu
#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_120_200'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_120_200']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_120_200/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_1400_2300'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_1400_2300']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_1400_2300/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_200_400'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_200_400']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_200_400/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_2300_3500'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_2300_3500']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_2300_3500/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_3500_4500'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_3500_4500']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_3500_4500/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_400_800'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_400_800']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_400_800/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_4500_6000'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_4500_6000']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_4500_6000/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_50_120'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_50_120']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_50_120/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_6000_Inf'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_6000_Inf']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_6000_Inf/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'ZToMuMu_NNPDF30_13TeV-powheg_M_800_1400'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=ZToMuMu_NNPDF30_13TeV-powheg_M_800_1400']
#    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_800_1400/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)

#    config.General.requestName = 'DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
#    config.General.requestName = 'DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8']
#    config.Data.inputDataset = '/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 2
#    submit(config)
    
##
## aMC@NLO
##

#    #config.General.requestName = 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
#    #config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    #config.Data.unitsPerJob = 5
    ##config.Data.totalUnits = 8
#    #submit(config)

#    #config.General.requestName = 'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
#    #config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    #config.Data.unitsPerJob = 5
    ##config.Data.totalUnits = 8
#    #submit(config)

#    #config.General.requestName = 'WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'
#    #config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
#    #config.Data.unitsPerJob = 5
    ##configData.totalUnits = 8
#    #submit(config)
