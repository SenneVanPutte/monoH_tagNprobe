import os
#year='2017'
year='2016'

#runs=['B', 'C', 'D', 'E', 'F']
runs=['B', 'C', 'D', 'E', 'F', 'G', 'H']

#ele_trig=['DoubleEle33_leg', 'DoubleEle27_leg', 'DoubleEle25_leg', 'Ele27_Ele37_leg1', 'Ele27_Ele37_leg2']
ele_trig=['DoubleEle33_GsfTrkIdVL_leg', 'DoubleEle33_GsfTrkIdVL_MW_leg', 'Mu27_Ele37_emu_legEle']

#mu_trig=['Mu50', 'Mu37_TkMu27_leg1', 'Mu37_TkMu27_leg2', 'Mu27_Ele37_legMu', 'Mu37_Ele27_legMu']
mu_trig=['Mu50', 'Mu30_TkMu11_leg1', 'Mu30_TkMu11_leg2', 'Mu33_Ele33_emu_legMu', 'Mu27_Ele37_legMu']

prefix = ''
#prefix = '_17v5'

result_map = year+'_trigger_results'+prefix
os.system('mkdir '+result_map)
for run in runs:
    # mkdirs
    print(run)
    os.system('mkdir '+result_map+'/Run'+run)
    os.system('mkdir '+result_map+'/Run'+run+'/pt')
    os.system('mkdir '+result_map+'/Run'+run+'/eta')
    os.system('mkdir '+result_map+'/Run'+run+'/ptVeta')

    for ele_tr in ele_trig:
       print('    ' + ele_tr)
       os.system('cp Electron_Run'+year+run+'/results/'+ele_tr+'_pt/* '+result_map+'/Run'+run+'/pt/.') 
       os.system('cp Electron_Run'+year+run+'/results/'+ele_tr+'_eta/* '+result_map+'/Run'+run+'/eta/.') 
       os.system('cp Electron_Run'+year+run+'/results/'+ele_tr+'_pt_eta/* '+result_map+'/Run'+run+'/ptVeta/.')
    for mu_tr in mu_trig: 
       print('    ' + mu_tr)
       os.system('cp Muon_Run'+year+run+'/results/'+mu_tr+'_pt/* '+result_map+'/Run'+run+'/pt/.') 
       os.system('cp Muon_Run'+year+run+'/results/'+mu_tr+'_eta/* '+result_map+'/Run'+run+'/eta/.') 
       os.system('cp Muon_Run'+year+run+'/results/'+mu_tr+'_pt_eta/* '+result_map+'/Run'+run+'/ptVeta/.')

