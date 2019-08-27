import ROOT
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
if options.muon: 
    #f_rB = ROOT.TFile('Muon_Run2017B/results/RunB_hists.root')
    #f_rC = ROOT.TFile('Muon_Run2017C/results/RunC_hists.root')
    #f_rD = ROOT.TFile('Muon_Run2017D/results/RunD_hists.root')
    #f_rE = ROOT.TFile('Muon_Run2017E/results/RunE_hists.root')
    #f_rF = ROOT.TFile('Muon_Run2017F/results/RunF_hists.root')

    f_rB = ROOT.TFile('Muon_Run2017B/results/histograms.root')
    f_rC = ROOT.TFile('Muon_Run2017C/results/histograms.root')
    f_rD = ROOT.TFile('Muon_Run2017D/results/histograms.root')
    f_rE = ROOT.TFile('Muon_Run2017E/results/histograms.root')
    f_rF = ROOT.TFile('Muon_Run2017F/results/histograms.root')
else:
    #f_rB = ROOT.TFile('Electron_Run2017B/results/RunB_hists.root')
    #f_rC = ROOT.TFile('Electron_Run2017C/results/RunC_hists.root')
    #f_rD = ROOT.TFile('Electron_Run2017D/results/RunD_hists.root')
    #f_rE = ROOT.TFile('Electron_Run2017E/results/RunE_hists.root')
    #f_rF = ROOT.TFile('Electron_Run2017F/results/RunF_hists.root')

    f_rB = ROOT.TFile('Electron_Run2017B/results/histograms.root')
    f_rC = ROOT.TFile('Electron_Run2017C/results/histograms.root')
    f_rD = ROOT.TFile('Electron_Run2017D/results/histograms.root')
    f_rE = ROOT.TFile('Electron_Run2017E/results/histograms.root')
    f_rF = ROOT.TFile('Electron_Run2017F/results/histograms.root')

trig_names = []
trig_nf = open(options.trig_names, 'r')
for line in  trig_nf:
    trig_names.append(line.replace('\n', ''))
trig_nf.close()

c_trg = {}
ROOT.gStyle.SetOptStat(0)
for trig in trig_names:
    print(trig)
    trig_h_name = trig + '_pt_nominal'
    h_rB = f_rB.Get(trig_h_name)
    h_rC = f_rC.Get(trig_h_name)
    h_rD = f_rD.Get(trig_h_name)
    h_rE = f_rE.Get(trig_h_name)
    h_rF = f_rF.Get(trig_h_name)

    has_B = True
    has_C = True
    has_D = True
    has_E = True
    has_F = True

    try:
        h_rB.SetMarkerColor(1)
        h_rB.SetMarkerStyle(20)
        h_rB.SetMarkerSize(0.75)
    except AttributeError:
        has_B = False
    try:
        h_rC.SetMarkerColor(2)
        h_rC.SetMarkerStyle(20)
        h_rC.SetMarkerSize(0.75)
    except AttributeError:
        has_C = False
    try:
        h_rD.SetMarkerColor(3)
        h_rD.SetMarkerStyle(20)
        h_rD.SetMarkerSize(0.75)
    except AttributeError:
        has_D = False
    try:
        h_rE.SetMarkerColor(4)
        h_rE.SetMarkerStyle(20)
        h_rE.SetMarkerSize(0.75)
    except AttributeError:
        has_E = False
    try:
        h_rF.SetMarkerColor(5)
        h_rF.SetMarkerStyle(20)
        h_rF.SetMarkerSize(0.75)
    except AttributeError:
        has_F = False

    legend = ROOT.TLegend(0.7, 0.1, 0.9, 0.3)
    legend.AddEntry(h_rB, 'RunB', 'P')
    legend.AddEntry(h_rC, 'RunC', 'P')
    legend.AddEntry(h_rD, 'RunD', 'P')
    legend.AddEntry(h_rE, 'RunE', 'P')
    legend.AddEntry(h_rF, 'RunF', 'P')

    h_rE.GetYaxis().SetTitle("efficiency")
    h_rE.GetXaxis().SetTitle("pT")

    c_trg[trig] = ROOT.TCanvas( trig, trig, 600, 500)
    png_name = options.out_dir + '/' + trig + '.png'
    h_rE.SetMaximum(1)
    h_rE.SetMinimum(0)
    h_rE.Draw()
    if has_B: h_rB.Draw('same')
    if has_C: h_rC.Draw('same')
    if has_D: h_rD.Draw('same')
    if has_F: h_rF.Draw('same')
    legend.Draw('same')
    if options.save: c_trg[trig].SaveAs(png_name)

    c_trg[trig+'_zoom'] = ROOT.TCanvas( trig+'_zoom', trig+'_zoom', 600, 500)
    h_rE.SetMaximum(1)
    h_rE.SetMinimum(0.8)
    #h_rE.GetXaxis().SetLimits(20., 55.)
    h_rE.SetAxisRange(30., 47., 'X')
    #h_rE.GetXaxis().SetLimits(20., 55.)
    png_name = options.out_dir + '/' + trig + '_zoom.png'
    h_rE.Draw()
    if has_B: h_rB.Draw('same')
    if has_C: h_rC.Draw('same')
    if has_D: h_rD.Draw('same')
    if has_F: h_rF.Draw('same')
    legend.Draw('same')
    if options.save: c_trg[trig+'_zoom'].SaveAs(png_name)

raw_input('exit')

# close all
f_rB.Close()
f_rC.Close()
f_rD.Close()
f_rE.Close()
f_rF.Close()
