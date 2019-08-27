import ROOT
from copy import deepcopy

def compi_nom_var( in_file, var='pt' ):
    h_ele_leg1 = in_file.Get('Ele23_Ele12_leg1_'+var+'_nominal')
    h_ele_leg2 = in_file.Get('Ele23_Ele12_leg2_'+var+'_nominal')
    h_ele_MHleg = in_file.Get('DoubleEle33_leg_'+var+'_nominal')
    h_ele_orleg1 = in_file.Get('DoubleEle33leg_or_Ele23Ele12leg1_'+var+'_nominal')
    h_ele_orleg2 = in_file.Get('DoubleEle33leg_or_Ele23Ele12leg2_'+var+'_nominal')

    g_ele_leg1 = ROOT.TGraphAsymmErrors(h_ele_leg1)
    g_ele_leg2 = ROOT.TGraphAsymmErrors(h_ele_leg2)
    g_ele_MHleg1 = ROOT.TGraphAsymmErrors(h_ele_MHleg)
    g_ele_orleg1 = ROOT.TGraphAsymmErrors(h_ele_orleg1)
    g_ele_orleg2 = ROOT.TGraphAsymmErrors(h_ele_orleg2)

    g_ele_leg1.SetMarkerColor(1)
    g_ele_leg2.SetMarkerColor(1)
    g_ele_MHleg1.SetMarkerColor(2)
    g_ele_orleg1.SetMarkerColor(3)
    g_ele_orleg2.SetMarkerColor(3)

    g_ele_leg1.SetMarkerStyle(20)
    g_ele_leg2.SetMarkerStyle(20)
    g_ele_MHleg1.SetMarkerStyle(20)
    g_ele_orleg1.SetMarkerStyle(20)
    g_ele_orleg2.SetMarkerStyle(20)

    g_ele_leg1.SetMarkerSize(1)
    g_ele_leg2.SetMarkerSize(1)
    g_ele_MHleg1.SetMarkerSize(1)
    g_ele_orleg1.SetMarkerSize(1)
    g_ele_orleg2.SetMarkerSize(1)

    #legend = ROOT.TLegend(0.62, 0.7, 0.9, 0.9)
    legend = ROOT.TLegend(0.5, 0.1, 0.9, 0.4)
    legend.AddEntry(g_ele_leg1, 'latino')
    legend.AddEntry(g_ele_MHleg1, 'monoHiggs')
    legend.AddEntry(g_ele_orleg1, 'latino or monoHiggs')

    #c_leg1 = ROOT.TCanvas('c_leg1', 'c_leg1', 800, 700)
    #c_leg2 = ROOT.TCanvas('c_leg2', 'c_leg2', 800, 700)

    mg_leg1 = ROOT.TMultiGraph('mg_leg1', 'DoubleEle leg1')
    mg_leg2 = ROOT.TMultiGraph('mg_leg2', 'DoubleEle leg2')

    g_ele_MHleg2 = deepcopy(g_ele_MHleg1)    

    mg_leg1.Add(g_ele_leg1)
    mg_leg1.Add(g_ele_MHleg1)
    mg_leg1.Add(g_ele_orleg1)
    
    #mg_leg2 = ROOT.TMultiGraph()
    mg_leg2.Add(g_ele_leg2)
    mg_leg2.Add(g_ele_MHleg2)
    mg_leg2.Add(g_ele_orleg2)

    mg_leg1.Draw('AP')    
    mg_leg2.Draw('AP')    
    #mg_leg1.GetXaxis().SetTitle(var)   
    #mg_leg2.GetXaxis().SetTitle(var)   
    ROOT.gPad.Update()
    c_leg1 = ROOT.TCanvas('c_leg1', 'c_leg1', 800, 700)
    c_leg2 = ROOT.TCanvas('c_leg2', 'c_leg2', 800, 700)

    c_leg1.cd()
    mg_leg1.Draw('AP')    
    legend.Draw('same')

    ROOT.gPad.Modified()
    mg_leg1.GetXaxis().SetLimits(0,50)
    mg_leg1.GetYaxis().SetLimits(0.8,1)

    #ROOT.gPad.Update()
    c_leg1.Update()

    c_leg2.cd()
    mg_leg2.Draw('AP')    
    legend.Draw('same')




    raw_input('Move along, nothing to see here')

    del mg_leg1
    del mg_leg2
    del c_leg1 
    del c_leg2 

if __name__ == '__main__':
    in_file = ROOT.TFile.Open("histograms.root")
    compi_nom_var(in_file)
    compi_nom_var(in_file, var='eta')
    in_file.Close()
