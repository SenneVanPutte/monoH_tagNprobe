import ROOT
import optparse
from optparse import OptionParser
from copy import deepcopy

usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('--hist', dest='hist_names', help='Text file containing histogram names', type='string')
parser.add_option('--root', dest='root_names', help='Text file containing rootfile names', type='string')
parser.add_option('-o', '--out', dest='out_file', help='Name of outpu rootfile', type='string')
parser.add_option('--left', dest='left', help='Move legend to the left', default=False, action="store_true")
(options, args) = parser.parse_args()

file_out = ROOT.TFile(options.out_file, 'recreate')

root_files = []
open_root_files = {}
root_fnf = open(options.root_names, 'r')
for line in root_fnf:
    if '.root' in line:
        name = line.replace('\n', '')
        root_files.append(name)
        open_root_files[name] = ROOT.TFile.Open(name) 
root_fnf.close()

hist_names = []
hist_nf = open(options.hist_names, 'r')
for line in  hist_nf:
    hist_names.append(line.replace('\n', ''))
hist_nf.close()

for trigger_hist in hist_names:
    print(trigger_hist)
    if 'pt_eta' in trigger_hist: 
        tag = 'ptVeta'
        trg_name = trigger_hist.replace('_pt_eta', '')
    else:
        splitted = trigger_hist.split('_')
        tag = splitted[-1]
        trg_name = trigger_hist.replace('_'+tag, '')
    for root_f in root_files:
       type_name = root_f.replace('efficiency_', '').replace('.root', '')
       name = trg_name + '_' + tag + '_' + type_name
       #print(name)
       h_tot = open_root_files[root_f].Get(trigger_hist+'_total') 
       h_pas = open_root_files[root_f].Get(trigger_hist+'_pass')
       h_eff = h_pas.Clone(name) 
       h_eff.Divide(h_tot)
        
       file_out.cd()
       h_eff.Write()

# close all
for fil in open_root_files:
    open_root_files[fil].Close()
file_out.Close()
