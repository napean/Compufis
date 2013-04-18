import pylab
import numpy


data = numpy.loadtxt('valores1.dat')

t = data[:,0]
r = data[:,1]
v = data[:,2]
p = data[:,3]

pylab.plot(t, r, 'k')
pylab.ylabel('Radio (cm)')
pylab.xlabel('Tiempo (s)')
pylab.savefig('radio.png')
pylab.close()

pylab.plot(t, v, 'k')
pylab.ylabel('Velocidad (cm/s)')
pylab.xlabel('Tiempo (s)')
pylab.savefig('velocidad.png')
pylab.close()

pylab.plot(t, p, 'k')
pylab.ylabel('Presion (dinas/cm^2)')
pylab.xlabel('Tiempo (s)')
pylab.savefig('presion.png')
pylab.close()


