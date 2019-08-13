from CRABClient.UserUtilities import config
config = config()

name = 'Muon_Ntuple_2016_monoH_Triggers_v8'
config.General.workArea = 'crab_'+name
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runNtupler_monoH_16.py'
config.JobType.outputFiles = ['TnP_ntuple.root']

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.txt'
config.Data.publication = False
config.Data.totalUnits = -1
config.Data.outLFNDirBase = '/store/user/svanputt/monoHiggs/' + name

config.Site.storageSite = 'T2_BE_IIHE'
config.Site.blacklist = ['T2_BR_SPRACE', 'T2_EE_Estonia']


if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand

   dataset = {
      'Run2016B' : '/SingleMuon/Run2016B-17Jul2018_ver2-v1/MINIAOD',
      'Run2016C' : '/SingleMuon/Run2016C-17Jul2018-v1/MINIAOD', 
      'Run2016D' : '/SingleMuon/Run2016D-17Jul2018-v1/MINIAOD', 
      'Run2016E' : '/SingleMuon/Run2016E-17Jul2018-v1/MINIAOD', 
      'Run2016F' : '/SingleMuon/Run2016F-17Jul2018-v1/MINIAOD', 
      'Run2016G' : '/SingleMuon/Run2016G-17Jul2018-v1/MINIAOD', 
      'Run2016H' : '/SingleMuon/Run2016H-17Jul2018-v1/MINIAOD', 
      }


   #nevents = -1 
   lumisPerJob = {
      'Run2016B':        100,
      'Run2016C':        100,
      'Run2016D':        100,
      'Run2016E':        100,
      'Run2016F':        100,
      'Run2016G':        100,
      'Run2016H':        100,
      }

   listOfSamples = [
      'Run2016B',        
      'Run2016C',        
      'Run2016D',        
      'Run2016E',        
      'Run2016F',        
      'Run2016G',        
      'Run2016H',        
      ]

   listOfSamples.reverse()
   for sample in listOfSamples:
      config.General.requestName = sample+'_v8'
      config.Data.inputDataset = dataset[sample]
      config.Data.unitsPerJob = lumisPerJob[sample]
      config.Data.outputDatasetTag = sample+'_v8'
      crabCommand('submit', config = config)

