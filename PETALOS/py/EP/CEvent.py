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

		self.hNumberOfParticles = bookHisto1(self.label,self.hman,
			"NumberOfParticles","Number Of Particles",10,0.,10.)

		self.hTi = bookHisto1(self.label,self.hman,
			"Ti","Kinetic Energy (keV)",100,0.,100.)
		
		self.hZ = bookHisto1(self.label,self.hman,
			"Z","Z (mm)",50,0.,50.)

		self.hXY = bookHisto2(self.label,self.hman,
			"XY","XY (mm)",25, -50, 50, 25, -50, 50)
		
		
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
		self.hman.fill(self.hNumberOfParticles, numberOfParticles)

		primaryParticles = PrimaryParticles(event)
		self.m.log(3, ' number of primary Particles =%d '%(len(primaryParticles)))
		
		if self.debug == 2:
			wait()

		for pparticle in primaryParticles:
			self.m.log(3, '\n+++primary particle+++\n')
			ei,ef = particleEnergy(pparticle)

			self.m.log(3,'name = %s t =%7.2f ns E = %7.2f keV'%(
			particleName(pparticle), particleTime(pparticle)/ns,ei/keV))


			particleInfo(self.m,4,pparticle)

			x0,y0,z0 = particleInitialVtx(pparticle)
			ti,tf = particleKineticEnergy(pparticle)
			

			self.m.log(3, ' x0 =%7.2f mm, y0 =%7.2f mm, z0 =%7.2f mm '%(
			x0/mm,y0/mm,z0/mm))
		
			self.m.log(3, ' ti =%7.2f keV, tf =%7.2f keV '%(
			ti/keV,tf/keV))

			self.hman.fill(self.hXY, x0/mm,y0/mm)
			self.hman.fill(self.hZ, z0/mm)
			self.hman.fill(self.hTi, ti/KeV)

			
			if self.debug == 3: 
				wait()
		
		self.numOutputEvents += 1
			
		return True

		

	############################################################
	def finalize(self):

		self.m.log(1, 'Finalize()')

		self.m.log(1, 'Input  Events: ', self.numInputEvents)
		self.m.log(1, 'Output Events: ', self.numOutputEvents)
		
		return
