import pylab
import numpy

print ' Python no es muy rapido graficando, por favor espere...'

numeros = [0,3,6,9,12,15,18,21,24,27]

for i in numeros:

	data = numpy.loadtxt(open('valores'+str(i)+'.dat', 'r'))
	x = data[:,1]
	y = data[:,2]
	z = data[:,3]

	pylab.plot(x, y, 'k')
	pylab.xlabel('x')
	pylab.ylabel('y')
	pylab.title(str(i)+' x-y')
	pylab.savefig(str(i)+'_x-y.jpg')
	pylab.close()

	pylab.plot(x, z, 'k')
	pylab.xlabel('x')
	pylab.ylabel('z')
	pylab.title(str(i)+' x-z')
	pylab.savefig(str(i)+'_x-z.jpg')
	pylab.close()

	pylab.plot(y, z, 'k')
	pylab.xlabel('y')
	pylab.ylabel('z')
	pylab.title(str(i)+' y-z')
	pylab.savefig(str(i)+'_y-z.jpg')
	pylab.close()
