from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['hist_analysis.root','SelectedDataEvents.txt']
config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root', 'k_faktors_ele.root', 'k_faktors_mu.root', 'k_faktors_tau.root','METFilters_cff.py', 'qcdFakeOutput15pt_eta.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'Cert_294927-305636_13TeV_PromptReco_Collisions17_JSON.txt'
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
    config.General.workArea = 'crab_projects_2017_Nov17'

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

##### 2017 MINIAOD #####
    config.General.requestName = 'Tau_Run2017A'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_2017A']
    config.Data.inputDataset = '/Tau/Run2017A-PromptReco-v3/MINIAOD'
    config.Data.unitsPerJob = 23
    submit(config)

    config.General.requestName = 'Tau_Run2017B'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_2017B']
    config.Data.inputDataset = '/Tau/Run2017B-PromptReco-v1/MINIAOD'
    config.Data.unitsPerJob = 23
    submit(config)

    config.General.requestName = 'Tau_Run2017C'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_2017C']
    config.Data.inputDataset = '/Tau/Run2017C-PromptReco-v3/MINIAOD'
    config.Data.unitsPerJob = 23
    submit(config)

    config.General.requestName = 'Tau_Run2017D'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_2017D']
    config.Data.inputDataset = '/Tau/Run2017D-PromptReco-v1/MINIAOD'
    config.Data.unitsPerJob = 23
    submit(config)

    config.General.requestName = 'Tau_Run2017E'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_2017E']
    config.Data.inputDataset = '/Tau/Run2017E-PromptReco-v1/MINIAOD'
    config.Data.unitsPerJob = 23
    submit(config)

    config.General.requestName = 'Tau_Run2017F'
    config.JobType.pyCfgParams = ['sourceFileStringInput=Tau_2017F']
    config.Data.inputDataset = '/Tau/Run2017F-PromptReco-v1/MINIAOD'
    config.Data.unitsPerJob = 23
    submit(config)

