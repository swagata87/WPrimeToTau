from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['analysis.root','hist_analysis.root']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/crab_Wprime2/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'WPrimeToTaus'
config.Site.storageSite = 'T2_DE_RWTH'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects'

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

## Signal ##
    config.General.requestName = 'WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.Data.inputDataset = '/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    #config.Data.totalUnits = 4
    submit(config)

## Background ##
##
## WW
##
    config.General.requestName = 'WW_TuneCUETP8M1_13TeV-pythia8'
    config.Data.inputDataset = '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## WZ
##
    config.General.requestName = 'WZ_TuneCUETP8M1_13TeV-pythia8'
    config.Data.inputDataset = '/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## ZZ
##
    config.General.requestName = 'ZZ_TuneCUETP8M1_13TeV-pythia8'
    config.Data.inputDataset = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## ST_t-channel_antitop_4f_leptonDecays
##
    config.General.requestName = 'ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.Data.inputDataset = '/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## ST_t-channel_top_4f_leptonDecays
##
    config.General.requestName = 'ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.Data.inputDataset = '/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## ST_tW_antitop_5f_inclusiveDecays
##
    config.General.requestName = 'ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.Data.inputDataset = '/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## ST_tW_top_5f_inclusiveDecays
##
    config.General.requestName = 'ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1'
    config.Data.inputDataset = '/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)

##
## TT
##
    config.General.requestName = 'TT_TuneCUETP8M1_13TeV-powheg-pythia8'
    config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext3-v2/MINIAODSIM'
    config.Data.unitsPerJob = 5
    submit(config)
