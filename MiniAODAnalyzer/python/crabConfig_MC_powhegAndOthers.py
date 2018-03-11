from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['hist_analysis.root']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root', 'k_faktors_ele.root', 'k_faktors_mu.root', 'k_faktors_tau.root','METFilters_cff.py', 'qcdFakeOutput15pt_eta.root']
#config.JobType.maxMemoryMB = 3000
#config.JobType.numCores = 2

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


## Signal SSM ##

#    config.General.requestName = 'WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_600_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_600_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-600_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_1200_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_1200_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-1200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_1400_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_1400_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-1400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_1600_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_1600_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-1600_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_1800_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_1800_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-1800_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_2200_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_2200_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-2200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_2400_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_2400_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-2400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_2600_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_2600_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-2600_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_2800_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_2800_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-2800_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)


#    config.General.requestName = 'WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_3200_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_3200_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-3200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_3400_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_3400_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-3400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_3600_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_3600_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-3600_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_3800_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_3800_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-3800_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)


    config.General.requestName = 'WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WprimeToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 1
    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_4200_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_4200_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-4200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_4400_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_4400_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-4400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_4600_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_4600_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-4600_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_4800_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_4800_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-4800_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)


#    config.General.requestName = 'WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_5200_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_5200_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-5200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_5400_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_5400_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-5400_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_5600_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_5600_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-5600_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)

#    config.General.requestName = 'WprimeToTauNu_M_5800_TuneCUETP8M1_13TeV_pythia8_tauola'
#    config.JobType.pyCfgParams = ['sourceFileStringInput=WprimeToTauNu_M_5800_TuneCUETP8M1_13TeV_pythia8_tauola']
#    config.Data.inputDataset = '/WprimeToTauNu_M-5800_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
#    config.Data.unitsPerJob = 1
#    submit(config)


## Background ##
##
## WW
##
    config.General.requestName = 'WW_TuneCUETP8M1_13TeV-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WW_TuneCUETP8M1_13TeV-pythia8']
    config.Data.inputDataset = '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WW_TuneCUETP8M1_13TeV-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WW_TuneCUETP8M1_13TeV-pythia8']
    config.Data.inputDataset = '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## WZ
##
    config.General.requestName = 'WZ_TuneCUETP8M1_13TeV-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WZ_TuneCUETP8M1_13TeV-pythia8']
    config.Data.inputDataset = '/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WZ_TuneCUETP8M1_13TeV-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WZ_TuneCUETP8M1_13TeV-pythia8']
    config.Data.inputDataset = 'WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ZZ
##
    config.General.requestName = 'ZZ_TuneCUETP8M1_13TeV-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZZ_TuneCUETP8M1_13TeV-pythia8']
    config.Data.inputDataset = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'ZZ_TuneCUETP8M1_13TeV-pythia8_ext1'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ZZ_TuneCUETP8M1_13TeV-pythia8']
    config.Data.inputDataset = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_t-channel_antitop_4f
##
    config.General.requestName = 'ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin']
    config.Data.inputDataset = '/ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_t-channel_top_4f
##
    config.General.requestName = 'ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin']
    config.Data.inputDataset = '/ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_tW_antitop_5f_inclusiveDecays
##
    config.General.requestName = 'ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4']
    config.Data.inputDataset = '/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## ST_tW_top_5f_inclusiveDecays
##
    config.General.requestName = 'ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4'
    config.JobType.pyCfgParams = ['sourceFileStringInput=ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4']
    config.Data.inputDataset = '/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

##
## TT
##
    config.General.requestName = 'TT_TuneCUETP8M2T4_13TeV-powheg-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=TT_TuneCUETP8M2T4_13TeV-powheg-pythia8']
    config.Data.inputDataset = '/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8']
    config.Data.inputDataset = '/TT_Mtt-700to1000_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8'
    config.JobType.pyCfgParams = ['sourceFileStringInput=TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8']
    config.Data.inputDataset = '/TT_Mtt-1000toInf_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

###
## W mass binned sample ##
###

    config.General.requestName = 'WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-100_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-200_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-500_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-1000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-2000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-3000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-4000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-5000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

    config.General.requestName = 'WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola'
    config.JobType.pyCfgParams = ['sourceFileStringInput=WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola']
    config.Data.inputDataset = '/WToTauNu_M-6000_TuneCUETP8M1_13TeV-pythia8-tauola/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    config.Data.unitsPerJob = 2
    submit(config)

