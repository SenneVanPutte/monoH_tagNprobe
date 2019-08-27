import ROOT
import time
import optparse
from optparse import OptionParser
from copy import deepcopy

usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('--trig', dest='trig_names', help='Text file containing trigogram names', type='string')
parser.add_option('-o', '--out_dir', dest='out_dir', help='Name of output dir', type='string', default="")
parser.add_option('--left', dest='left', help='Move legend to the left', default=False, action="store_true")
parser.add_option('-s', '--save', dest='save', help='Save images to destination dir', default=False, action="store_true")
parser.add_option('--muon', dest='muon', help='Do muons in stead of electrons', default=False, action="store_true")
(options, args) = parser.parse_args()

#file_out = ROOT.TFile(options.out_file, 'recreate')
year = '2016'
#year = '2017'

runs = ['B', 'C', 'D', 'E', 'F', 'G', 'H']
#runs = ['B', 'C', 'D', 'E', 'F']
files = {}
for run in runs:
    if options.muon:
        files[run] = ROOT.TFile('Muon_Run'+year+run+'/results/histograms.root')
    else:
        files[run] = ROOT.TFile('Electron_Run'+year+run+'/results/histograms.root') 

trig_names = []
trig_nf = open(options.trig_names, 'r')
for line in  trig_nf:
    if not '#' in line: trig_names.append(line.replace('\n', ''))
trig_nf.close()

c_trg = {}
ROOT.gStyle.SetOptStat(0)
for trig in trig_names:
    print(trig)
    trig_h_name = trig + '_pt_nominal'
    histograms = {}
    has_run = {}
    for run in files:
        histograms[run] = files[run].Get(trig_h_name)
        has_run[run] = True
    
    color = 0
    for run in runs:
        color += 1
        try:
            histograms[run].SetMarkerColor(color)
            histograms[run].SetMarkerStyle(20)
            histograms[run].SetMarkerSize(0.75)
        except AttributeError:
            has_run[run] = False

    legend = ROOT.TLegend(0.7, 0.1, 0.9, 0.3)
    for run in runs:
        legend.AddEntry(histograms[run], 'Run'+run, 'P')


    c_trg[trig] = ROOT.TCanvas( trig, trig, 600, 500)
    png_name = options.out_dir + '/' + trig + '.png'
    index = -1
    try:
        histograms[runs[index]].GetYaxis().SetTitle("efficiency")
        histograms[runs[index]].GetXaxis().SetTitle("pT")
        histograms[runs[index]].SetMaximum(1)
        histograms[runs[index]].SetMinimum(0)
        histograms[runs[index]].Draw()
    except:
        pass
    for run in runs:
        if run != runs[index] and has_run[run]: histograms[run].Draw('same')
    legend.Draw('same')
    if options.save:
        print('saving as ' + png_name)
        c_trg[trig].SaveAs(png_name)
    
    time.sleep(2)

    c_trg[trig+'_zoom'] = ROOT.TCanvas( trig+'_zoom', trig+'_zoom', 600, 500)
    histograms[runs[index]].SetMaximum(1)
    histograms[runs[index]].SetMinimum(0.8)
    histograms[runs[index]].SetAxisRange(25., 55., 'X')
    #histograms[runs[-1]].SetAxisRange(45., 70., 'X')
    #histograms[runs[-1]].SetAxisRange(0., 20., 'X')
    #h_rE.GetXaxis().SetLimits(20., 55.)
    #h_rE.GetXaxis().SetLimits(20., 55.)
    png_name = options.out_dir + '/' + trig + '_zoom.png'
    histograms[runs[index]].Draw()
    for run in runs:
        if run != runs[index] and has_run[run]: histograms[run].Draw('same')
    legend.Draw('same')
    if options.save: c_trg[trig+'_zoom'].SaveAs(png_name)

raw_input('exit')

# close all
for run in runs:
    files[run].Close()
