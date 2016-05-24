"""
Utilities
"""
#from __future__ import print_function
from math import *
import sys, os
from PhysicalConstants import *
from system_of_units import *

import matplotlib.pyplot as plt
import numpy as np

ps = picosecond
nm = nanometer 
mol = mole
micron = micrometer

def wait():
	raw_input("Press a key...")


def drange(start, stop, step):
	"""
	a range of doubles
	"""
	r = start
	while r < stop:
		yield r
		r += step

def lin(x,x0,y0,x1,y1):
	"""
	lineal extrapolation
	"""
	
	return y0 + (x-x0)*(y1-y0)/(x1-x0)

def inRange(x,xmin,xmax):
	if x >= xmin and x <= xmax:
		return True
	else:
		return False

def bookHisto1(lbl,hman,hdes,htitle,nx,xmin,xmax):

	hname = lbl + '.'+ hdes
	hman.h1(hname, hdes, nx, xmin, xmax)
	hman.fetch(hname).GetXaxis().SetTitle(htitle)
	return hname

def bookHisto2(lbl,hman,hdes,htitle,nx,xmin,xmax,ny,ymin,ymax):

	hname = lbl + '.'+ hdes
	hman.h2(hname, hdes, nx, xmin, xmax, ny, ymin, ymax)	
	hman.fetch(hname).GetXaxis().SetTitle(htitle)
	return hname

