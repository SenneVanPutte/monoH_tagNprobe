import optparse
from optparse import OptionParser
import math
import ROOT

usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('--nom', dest='nominal_file', help='Text file containing nominal values', type='string')
parser.add_option('--z_up', dest='z_up_file', help='Text file containing Z up variation values', type='string')
parser.add_option('--z_dn', dest='z_dn_file', help='Text file containing Z down variation values', type='string')
parser.add_option('--pt_up', dest='pt_up_file', help='Text file containing pt up variation values', type='string')
parser.add_option('--pt_dn', dest='pt_dn_file', help='Text file containing pt down variation values', type='string')
parser.add_option('-o', dest='o_file', help='Name of output file', type='string')
(options, args) = parser.parse_args()

def get_list(name):
    temp_f = open(name, 'r')
    temp_l = [line.rstrip().split() for line in temp_f if '#' not in line]
    temp_f.close()
    return temp_l

nom_l = get_list(options.nominal_file)
zup_l = get_list(options.z_up_file)
zdn_l = get_list(options.z_dn_file)
ptup_l = get_list(options.pt_up_file)
ptdn_l = get_list(options.pt_dn_file)

#new_l = []

h_zup  = ROOT.TH1F('h_zup',  'Z_up - nom',  100, -0.02, 0.02)
h_zdn  = ROOT.TH1F('h_zdn',  'Z_dn - nom',  100, -0.02, 0.02)
h_ptup = ROOT.TH1F('h_ptup', 'pT_up - nom', 100, -0.02, 0.02)
h_ptdn = ROOT.TH1F('h_ptdn', 'pT_dn - nom', 100, -0.02, 0.02)

h_zdiff  = ROOT.TH1F('h_zdiff',  'Z_up - Z_dn',   100, -0.02, 0.02)
h_ptdiff = ROOT.TH1F('h_ptdiff', 'pT_up - pT_dn', 100, -0.02, 0.02)

if __name__ == '__main__':
    out_f = open(options.o_file, 'w')
    for it,nom in enumerate(nom_l):
        
        zup = zup_l[it] 
        zdn = zdn_l[it] 
        ptup = ptup_l[it] 
        ptdn = ptdn_l[it] 
        new = nom
        
        zup_f = float(zup[4])
        zdn_f = float(zdn[4])
        ptup_f = float(ptup[4])
        ptdn_f = float(ptdn[4])
        nom_f = float(nom[4])
        statup_f = float(nom[5])
        statdn_f = float(nom[6])

        up_var = math.sqrt( (max(0,zup_f - nom_f))**2 + (max(0,zdn_f - nom_f))**2 + (max(0,ptup_f - nom_f))**2 + (max(0,ptdn_f - nom_f))**2 + statup_f**2)
        dn_var = math.sqrt( (min(0,zup_f - nom_f))**2 + (min(0,zdn_f - nom_f))**2 + (min(0,ptup_f - nom_f))**2 + (min(0,ptdn_f - nom_f))**2 + statdn_f**2)

        new[5] = str(round(up_var, 3))
        new[6] = str(round(dn_var, 3))

        #print('nominal='+nom[4]+', Z_up='+zup[4]+', Z_dn='+zdn[4]+', pT_up='+ptup[4]+', pT_dn='+ptdn[4])
        prt_str = str(new[0])+'\t'+str(new[1])+'\t'+str(new[2])+'\t'+str(new[3])+'\t\t'+str(new[4])+'\t'+str(new[5])+'\t'+str(new[6])+'\n'
        out_f.write(prt_str)

    out_f.close()

'''
        h_zup.Fill(zup_f - nom_f)
        h_zdn.Fill(zdn_f - nom_f)
        h_ptup.Fill(ptup_f - nom_f)
        h_ptdn.Fill(ptdn_f - nom_f)

        h_zdiff.Fill(zup_f - zdn_f)
        h_ptdiff.Fill(ptup_f - ptdn_f)

        if not (zup[0] == nom[0] and zdn[0] == nom[0] and ptdn[0] == nom[0] and ptup[0] == nom[0]): print("weird 0 it " + str(it)) 
        if not (zup[1] == nom[1] and zdn[1] == nom[1] and ptdn[1] == nom[1] and ptup[1] == nom[1]): print("weird 1 it " + str(it)) 
        if not (zup[2] == nom[2] and zdn[2] == nom[2] and ptdn[2] == nom[2] and ptup[2] == nom[2]): print("weird 2 it " + str(it)) 
        if not (zup[3] == nom[3] and zdn[3] == nom[3] and ptdn[3] == nom[3] and ptup[3] == nom[3]): print("weird 3 it " + str(it)) 
        zup_rel = float(zup[4]) - float(nom[4]) + float(zup[5])
        if zup_rel < 0: print( str(zup_rel) + " Z up: " + zup[4] + ", nom: " + nom[4] + ", Z up up stat:" + zup[5])
        zdn_rel = float(nom[4]) - float(zdn[4]) + float(zdn[6])
        if zdn_rel < 0: print(str(zdn_rel) + "Z dn: " + zdn[4] + ", nom: " + nom[4] + ", Z dn dn stat:" + zup[6])
        ptup_rel = max(0, float(ptup[4]) - float(nom[4]) + float(ptup[5]))
        if ptup_rel < 0: print(str(ptup_rel) + "pt up: " + ptup[4] + ", nom: " + nom[4] + ", pt up up stat:" + ptup[5])
        ptdn_rel =  float(nom[4]) - float(ptdn[4]) + float(ptdn[6])
        if ptdn_rel < 0: print(str(ptdn_rel) + "pt dn: " + ptdn[4] + ", nom: " + nom[4] + ", pt dn dn stat:" + ptup[6])
        if zup_rel < 0 or zdn_rel < 0 or ptup_rel < 0 or ptdn_rel < 0:
            print(it)
            exit()

        new[5] = float(nom[5]) + zup_rel + ptup_rel
        new[6] = float(nom[6]) + zdn_rel + ptdn_rel
        #new_l[it] = new
        prt_str = str(new[0])+'\t'+str(new[1])+'\t'+str(new[2])+'\t'+str(new[3])+'\t\t'+str(new[4])+'\t'+str(new[5])+'\t'+str(new[6])+'\n'
        out_f.write(prt_str)

    out_f.close()

h_zup.Draw()
raw_input('continue')
h_zdn.Draw()
raw_input('continue')
h_ptup.Draw()
raw_input('continue')
h_ptdn.Draw()
raw_input('continue')
h_zdiff.Draw()
raw_input('continue')
h_ptdiff.Draw()
raw_input('continue')
'''
