import pylab
import numpy


data = numpy.loadtxt('valores1.dat')

t = data[:,0]
r = data[:,1]
v = data[:,2]
p = data[:,3]

per = 0;
rmin = 0
n=2

while n < len(r):
	if r[n-1] < r[n]:
		rmin=r[n-1]
		per = t[n-1]*2
		break

	n += 1

req = (rmin + r[0])/2

per2 = per /(3600*24)


infile = open ('period_amplitud.txt' , 'w')

infile.write( 'El radio de equilibro es: %f cm' % req)
infile.write( '\n')
infile.write( 'El periodo de oscilacion es:  %f dias' % per2)
infile.write( '\n')

infile.close()
