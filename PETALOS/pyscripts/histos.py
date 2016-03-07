from ROOT import *
from Util import *

dir_name ="/Users/jjgomezcadenas/Documents/Development/PETALO/histo"
file_name ="LYSO_3mm_xy2.4cm_z5cm_noCher_QE_1_SPTR_0_ASIC_0_DT300.root"

def file_path(dir_name, file_name):
	return dir_name+"/"+file_name

def file_type(dir_name, file_name, file_ext):
	return dir_name+"/"+file_name + "." + file_ext


def read_histo_file(file_name):
	return TFile(file_name)

def read_histo(histo_file,histo_name):
	return histo_file.Get(histo_name)

def plot_histo(histo,histo_name):
	gStyle.SetOptFit(1)
	gStyle.SetOptStat(1110)

	canvas = TCanvas("canvas","multipads",900,700)

	histo.Draw()
	canvas.Print(file_type(dir_name,histo_name,"png")
