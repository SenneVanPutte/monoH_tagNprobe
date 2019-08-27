from CRABClient.UserUtilities import config
config = config()

name = 'Muon_Ntuple_2017_monoH_Triggers_v2'
config.General.workArea = 'crab_'+name
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runNtupler_monoH_18.py'
config.JobType.outputFiles = ['TnP_ntuple.root']
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'
config.Data.publication = False
config.Data.totalUnits = -1
config.Data.outLFNDirBase = '/store/user/svanputt/monoHiggs/' + name

config.Site.storageSite = 'T2_BE_IIHE'
config.Site.blacklist = ['T2_BR_SPRACE', 'T2_EE_Estonia']


if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand

   dataset = {
      'Run2018A' : '/SingleMuon/Run2018A-17Sep2018-v2/MINIAOD',
      'Run2018B' : '/SingleMuon/Run2018B-17Sep2018-v1/MINIAOD', 
      'Run2018C' : '/SingleMuon/Run2018C-17Sep2018-v1/MINIAOD', 
      'Run2018D' : '/SingleMuon/Run2018D-PromptReco-v2/MINIAOD', 
      }
   
   
   #nevents = -1 
   lumisPerJob = {
      'Run2018A':        100,
      'Run2018B':        100,
      'Run2018C':        100,
      'Run2018D':        100,
      }
   
   listOfSamples = [
      #'Run2018A',        
      'Run2018B',        
      'Run2018C',        
      #'Run2018D',        
      ]

   listOfSamples.reverse()
   for sample in listOfSamples:
      config.General.requestName = sample+'_v2'
      config.Data.inputDataset = dataset[sample]
      config.Data.unitsPerJob = lumisPerJob[sample]
      config.Data.outputDatasetTag = sample+'_v2'
      crabCommand('submit', config = config)

