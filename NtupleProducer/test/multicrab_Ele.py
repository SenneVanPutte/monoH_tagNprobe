from CRABClient.UserUtilities import config

name = 'Electron_Ntuple_2017_monoH_Triggers_v2'

config = config()
config.General.workArea = 'crab_'+name
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runNtupler_monoH.py'
config.JobType.outputFiles = ['TnP_ntuple.root']

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.publication = False
config.Data.totalUnits = -1
#config.Data.totalUnits = 5
config.Data.outLFNDirBase = '/store/user/svanputt/monoHiggs/' + name

config.Site.storageSite = 'T2_BE_IIHE'
config.Site.blacklist = ['T2_BR_SPRACE', 'T2_EE_Estonia']


if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand


   dataset = {
      'Run2017B' : '/SingleElectron/Run2017B-31Mar2018-v1/MINIAOD',
      'Run2017C' : '/SingleElectron/Run2017C-31Mar2018-v1/MINIAOD', 
      'Run2017D' : '/SingleElectron/Run2017D-31Mar2018-v1/MINIAOD', 
      'Run2017E' : '/SingleElectron/Run2017E-31Mar2018-v1/MINIAOD', 
      'Run2017F' : '/SingleElectron/Run2017F-31Mar2018-v1/MINIAOD', 
      }


   #nevents = -1 
   lumisPerJob = {
      'Run2017B':        100,
      'Run2017C':        100,
      'Run2017D':        100,
      'Run2017E':        100,
      'Run2017F':        100,
      }

   listOfSamples = [
      'Run2017B',        
      'Run2017C',        
      'Run2017D',        
      'Run2017E',        
      'Run2017F',        
      ]


   listOfSamples.reverse()
   for sample in listOfSamples:
      config.General.requestName = sample+'_v1'
      config.Data.inputDataset = dataset[sample]
      config.Data.unitsPerJob = lumisPerJob[sample]
      config.Data.outputDatasetTag = sample+'_v1'
      crabCommand('submit', config = config)

