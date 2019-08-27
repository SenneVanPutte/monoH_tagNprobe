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
    print(run)
    wdir = result_map+'/Run'+run+'/ptVeta/'
    ext = '_efficiency.txt'

    for ele_tr in ele_trig:
       print(ele_tr)
       tf_path = wdir+ele_tr+'_pt_eta_'
       os.system('python make_sys_txt.py --nom '+tf_path+'nominal'+ext+' --z_up '+tf_path+'Zmass_up'+ext+' --z_dn '+tf_path+'Zmass_down'+ext+' --pt_up '+tf_path+'TagPt_up'+ext+' --pt_dn '+tf_path+'TagPt_down'+ext+' -o '+tf_path+'nominal_withSys'+ext)
    for mu_tr in mu_trig: 
       print(mu_tr)
       tf_path = wdir+mu_tr+'_pt_eta_'
       os.system('python make_sys_txt.py --nom '+tf_path+'nominal'+ext+' --z_up '+tf_path+'Zmass_up'+ext+' --z_dn '+tf_path+'Zmass_down'+ext+' --pt_up '+tf_path+'TagPt_up'+ext+' --pt_dn '+tf_path+'TagPt_down'+ext+' -o '+tf_path+'nominal_withSys'+ext)

