from Centella.AAlgo import AAlgo
from Centella.physical_constants import *
from Particles import *
from Util import *


"""
This algorithm classifies and filter the interactions passing only events 
where both photons interact in the boxes photoelectrically. 
"""

class CEvent(AAlgo):

	############################################################
	def __init__(self, param=False, level=1, label="", **kargs):

		"""
		CEvent Algorithm
		"""
		#self.m.log(1, 'Constructor()')

		### GENERAL STUFF
		self.name = 'CEvent'
		
		AAlgo.__init__(self, param, level, self.name, 0, label, kargs)

    ### PARAMETERS
    # Box coordinates

  		#print self.vdoubles
  		self.debug = self.ints["Debug"]

		if self.debug == 1:
			wait()
   

	############################################################		
	def initialize(self):

		self.m.log(1, 'Initialize()')
		
		### Defining histos
		# Event energy histogram

		self.m.log(2, "Booking histograms ")

		self.NumberOfParticles_histo_name = bookHisto1(self.label,self.hman,
			"NumberOfParticles","Number Of Particles",20,0.,20.)

		bookHisto1(self.label,self.hman,
			"Edep","Energy deposited (keV)",100,0.,100.)
		
		bookHisto1(self.label,self.hman,
			"Z","Z (cm)",50,0.,50.)

		bookHisto2(self.label,self.hman,
			"XY","XY (cm)",25, -50, 50, 25, -50, 50)
		
		
    ### Counters:
		self.numInputEvents = 0
		self.numOutputEvents = 0
		

		return



	############################################################
	def execute(self, event=""):

		self.m.log(2, 'Execute()')		
	
		self.numInputEvents += 1   

		numberOfParticles = event.GetMCParticles().size()

		self.m.log(3, ' number of particles = %d '%(numberOfParticles))
		self.hman.fill(self.NumberOfParticles_histo_name, numberOfParticles)

		primaryParticles = PrimaryParticles(event)
		self.m.log(3, ' number of primary Particles =%d '%(len(primaryParticles)))
		
		npb0 = 0
		npe = 0
		nco = 0
		interactionType = "none"

		for pparticle in primaryParticles:
			self.m.log(3, '\n+++primary particle+++\n')
			ei,ef = particleEnergy(pparticle)

			self.m.log(3,'name = %s t =%7.2f ns E = %7.2f keV'%(
			particleName(pparticle), particleTime(pparticle)/ns,ei/keV))


			self.particleInfo(self.m,4,pparticle)

			x0,y0,z0 = particleInitialVtx(pparticle)
			px,py,pz = particleInitialMomentum(pparticle)

			self.m.log(3, ' x0 =%7.2f mm, y0 =%7.2f mm, z0 =%7.2f mm '%(
			x0/mm,y0/mm,z0/mm))
		
			self.m.log(3, ' px =%7.2f keV, py =%7.2f keV, z =%7.2f keV '%(
			px/keV,py/keV,pz/keV))


			
		if self.debug == 2: 
			wait()
		
		self.numOutputEvents += 1
			
		return True

		

	############################################################
	def finalize(self):

		self.m.log(1, 'Finalize()')

		self.m.log(1, 'Input  Events: ', self.numInputEvents)
		self.m.log(1, 'Output Events: ', self.numOutputEvents)
		
		return
