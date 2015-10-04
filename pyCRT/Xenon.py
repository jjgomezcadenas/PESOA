"""
Xenon
Properties of Xenon
"""

from Util import *
import sys

#Photon   ,Coherent,Incoher.,Photoel.,Nuclear ,Electron,Tot. w/ ,
#Energy   ,Scatter.,Scatter.,Absorb. ,Pr. Prd.,Pr. Prd.,Coherent,

Xe={
1.000E-03:[8.458E+00,4.417E-03,9.403E+03,0.000E+00,0.000E+00,9.412E+03],
1.072E-03:[8.393E+00,4.969E-03,8.133E+03,0.000E+00,0.000E+00,8.141E+03],
1.149E-03:[8.325E+00,5.582E-03,7.032E+03,0.000E+00,0.000E+00,7.040E+03],
1.149E-03:[8.325E+00,5.582E-03,7.334E+03,0.000E+00,0.000E+00,7.343E+03],
1.500E-03:[8.000E+00,8.522E-03,4.077E+03,0.000E+00,0.000E+00,4.085E+03],
2.000E-03:[7.481E+00,1.285E-02,2.080E+03,0.000E+00,0.000E+00,2.088E+03],
3.000E-03:[6.481E+00,2.123E-02,7.715E+02,0.000E+00,0.000E+00,7.780E+02],
4.000E-03:[5.637E+00,2.874E-02,3.730E+02,0.000E+00,0.000E+00,3.787E+02],
4.782E-03:[5.087E+00,3.383E-02,2.357E+02,0.000E+00,0.000E+00,2.408E+02],
4.782E-03:[5.087E+00,3.383E-02,6.890E+02,0.000E+00,0.000E+00,6.941E+02],
5.000E-03:[4.945E+00,3.515E-02,6.344E+02,0.000E+00,0.000E+00,6.393E+02],
5.104E-03:[4.880E+00,3.577E-02,5.995E+02,0.000E+00,0.000E+00,6.044E+02],
5.104E-03:[4.880E+00,3.577E-02,8.133E+02,0.000E+00,0.000E+00,8.182E+02],
5.275E-03:[4.775E+00,3.677E-02,7.515E+02,0.000E+00,0.000E+00,7.563E+02],
5.453E-03:[4.669E+00,3.777E-02,6.945E+02,0.000E+00,0.000E+00,6.992E+02],
5.453E-03:[4.669E+00,3.777E-02,8.018E+02,0.000E+00,0.000E+00,8.065E+02],
6.000E-03:[4.368E+00,4.071E-02,6.330E+02,0.000E+00,0.000E+00,6.374E+02],
8.000E-03:[3.464E+00,5.027E-02,2.998E+02,0.000E+00,0.000E+00,3.033E+02],
1.000E-02:[2.815E+00,5.848E-02,1.662E+02,0.000E+00,0.000E+00,1.691E+02],
1.500E-02:[1.852E+00,7.440E-02,5.550E+01,0.000E+00,0.000E+00,5.743E+01],
2.000E-02:[1.322E+00,8.486E-02,2.510E+01,0.000E+00,0.000E+00,2.651E+01],
3.000E-02:[7.545E-01,9.729E-02,8.078E+00,0.000E+00,0.000E+00,8.929E+00],
3.456E-02:[6.119E-01,1.008E-01,5.417E+00,0.000E+00,0.000E+00,6.130E+00],
3.456E-02:[6.119E-01,1.008E-01,3.244E+01,0.000E+00,0.000E+00,3.316E+01],
4.000E-02:[4.913E-01,1.038E-01,2.211E+01,0.000E+00,0.000E+00,2.270E+01],
5.000E-02:[3.492E-01,1.073E-01,1.227E+01,0.000E+00,0.000E+00,1.273E+01],
6.000E-02:[2.610E-01,1.091E-01,7.454E+00,0.000E+00,0.000E+00,7.824E+00],
8.000E-02:[1.608E-01,1.096E-01,3.363E+00,0.000E+00,0.000E+00,3.633E+00],
1.000E-01:[1.089E-01,1.081E-01,1.793E+00,0.000E+00,0.000E+00,2.010E+00],
1.500E-01:[5.298E-02,1.019E-01,5.651E-01,0.000E+00,0.000E+00,7.200E-01],
2.000E-01:[3.136E-02,9.555E-02,2.490E-01,0.000E+00,0.000E+00,3.759E-01],
3.000E-01:[1.464E-02,8.495E-02,8.009E-02,0.000E+00,0.000E+00,1.797E-01],
4.000E-01:[8.435E-03,7.688E-02,3.699E-02,0.000E+00,0.000E+00,1.223E-01],
5.000E-01:[5.472E-03,7.064E-02,2.088E-02,0.000E+00,0.000E+00,9.699E-02],
6.000E-01:[3.837E-03,6.559E-02,1.338E-02,0.000E+00,0.000E+00,8.281E-02],
8.000E-01:[2.181E-03,5.784E-02,6.940E-03,0.000E+00,0.000E+00,6.696E-02],
1.000E+00:[1.404E-03,5.211E-02,4.335E-03,0.000E+00,0.000E+00,5.785E-02],
1.022E+00:[1.345E-03,5.156E-02,4.126E-03,0.000E+00,0.000E+00,5.703E-02],
1.250E+00:[9.022E-04,4.665E-02,2.782E-03,1.914E-04,0.000E+00,5.052E-02],
1.500E+00:[6.279E-04,4.244E-02,1.991E-03,8.853E-04,0.000E+00,4.594E-02],
2.000E+00:[3.540E-04,3.625E-02,1.211E-03,2.971E-03,0.000E+00,4.078E-02],
2.044E+00:[3.390E-04,3.580E-02,1.169E-03,3.173E-03,0.000E+00,4.048E-02],
3.000E+00:[1.576E-04,2.854E-02,6.422E-04,7.458E-03,9.981E-06,3.681E-02],
4.000E+00:[8.871E-05,2.381E-02,4.250E-04,1.141E-02,4.070E-05,3.577E-02],
5.000E+00:[5.679E-05,2.057E-02,3.142E-04,1.481E-02,8.100E-05,3.583E-02],
6.000E+00:[3.944E-05,1.818E-02,2.478E-04,1.774E-02,1.243E-04,3.634E-02],
7.000E+00:[2.898E-05,1.634E-02,2.040E-04,2.035E-02,1.674E-04,3.709E-02],
8.000E+00:[2.219E-05,1.488E-02,1.731E-04,2.269E-02,2.091E-04,3.797E-02],
9.000E+00:[1.754E-05,1.367E-02,1.501E-04,2.482E-02,2.489E-04,3.891E-02],
1.000E+01:[1.420E-05,1.267E-02,1.324E-04,2.677E-02,2.868E-04,3.987E-02],
}


def selectE(E):
  """
  Select the key closest to the energy E
  """
  dE=999999.
  EE = -999999.

  #print "selectE: E = ", E/MeV
  for key in Xe.keys():
    diff=abs(E - key)
    if diff < dE:
      dE=diff
      EE=key 

  #print "EE =",EE
  return EE

def ScatterCoherent(E):
  """
  cross section due to coherent scattering
  """
  return Xe[selectE(E/MeV)][0]*cm2/g

def ScatterIncoherent(E):
  """
  cross section  due to incoherent scattering
  """
  return Xe[selectE(E/MeV)][1]*cm2/g

def Photoelectric(E):
  """
  cross section  due to photoelectric
  """
  return Xe[selectE(E/MeV)][2]*cm2/g

def PairNuclearFied(E):
  """
  cross section  due to pairs in nuclear field
  """
  return Xe[selectE(E/MeV)][3]*cm2/g
  
def PairElectronField(E):
  """
  cross section  due to pairs in electron field
  """
  return Xe[selectE(E/MeV)][4]*cm2/g
  
def TotalInteraction(E):
  """
   Total cross section 
    """ 
  return Xe[selectE(E/MeV)][5]*cm2/g  

def TransmittedBeam(E,Z,rho):
  """
  Transmitted beam of energy z through a thickness Z
  rho is the density
  """
  mu_over_rho =TotalInteraction(E)

  # print "mu_over_rho = %7.4g (cm2/g)"%(mu_over_rho/(cm2/g))
  # print "rho = %7.4g (g/cm3)"%(self.rho/(g/cm3))
  # print "z = %7.4g (cm)"%(Z/cm)
  # print "mu_over_rho*rho*z = %7.4g"%(mu_over_rho*self.rho*Z)
  # print "exp(-mu_over_rho*rho*z) = %7.4g"%(exp(-mu_over_rho*self.rho*Z))
  return exp(-mu_over_rho*Z*rho)

def InteractionFraction(E,Z,rho):
  """
  Fraction of gammas of energy E interacting in thickness E
  """
  return 1. - TransmittedBeam(E, Z,rho)
    
    
