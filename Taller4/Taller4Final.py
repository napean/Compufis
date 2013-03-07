import os
import numpy
import sys
#import matplotlib.pyplot as plt
import scipy
from scipy.optimize import curve_fit
from scipy.linalg import eigh
from numpy import linalg as LA


table = []
theta = []
var_gravity = []
avg_grav = []
pca = []
data = open('data.dat', 'w')
valF = open('valF.dat', 'w')
residuoF = open('residuoF.dat', 'w')
angulog = open('angulog.dat' ,'w')
# corre un loop en el directorio hw4_data
for filename in os.listdir('hw4_data/' ):

        datos = []
        tiempo = []
        x = []
        y = []
        nomarch = (filename.replace('.dat','')).split('_')

        path = os.path.expanduser('hw4_data/' + filename)
       
	coso = open(path, 'r').readlines()
	
	datos = numpy.loadtxt(path)

      
        # crea los arrays con los datos de los archivos
	tiempo=datos[:,0]
	x=datos[:,1]
        y=datos[:,2]

        # encuentra las ecuacion de x y haciendo un fit
        ecx = numpy.polyfit(numpy.array(tiempo), numpy.array(x), 1.0)
        ecy = numpy.polyfit(numpy.array(tiempo), numpy.array(y), 2.0)

        # agrega a la lista una tupla con la informacion del archivo
        table.append((int(nomarch[1]),float(nomarch[3]),float(ecx[0]),float(ecy[1]),(-2.0*float(ecy[0]))))

		
		

        # Organiza los datos en orden creciente respecto al angulo
	table.sort(key=lambda tup: tup[1])
	
	# crea un archivo con los datos necesarios
	for row in table:
		for ht in row:
			data.write( '%f ' % (ht))
		data.write('\n')

print 'se importaron los datos de los arvhivos a data.dat'


F=[]
gmd = []
angulo = []
gmedia = []
cont = 0
cont2 = 0

for row in table:	       
	if row[1] not in angulo: 
	       angulo.append(row[1])
	

for ang in angulo:
	cont = 0.0	
	for line in table:
		if (line[1] == ang):
			cont += line[4]

       	cont /= 6.0
       	gmedia.append(cont)

"""
# grafica gmedia vs theta y lo guarda en el archivo 'gmedia_vs_theta.png'
plt.plot(angulo, gmedia, '.')
plt.xlabel('theta (degrees)')
plt.ylabel('gmedia (m/s^2)')
plt.title('gmedia vs Theta')
plt.savefig('gmedia_vs_theta')
plt.grid(True)
plt.show()
"""

# obtiene la matriz de covarianzas
#1. Obtener el vector de los valores de la gravedad en cada exp.
#2. Obtener el vector de los valores de la velocidad en x en cada exp.
#3. Obtener el vector de los valores de la velocidad en y en cada exp.
gravedad = []
vSubx = []
vSuby = []

for row in table:
    gravedad.append(row[4])
    vSubx.append(row[2])
    vSuby.append(row[3])

M=numpy.vstack(((gravedad,vSubx),vSuby))
Mcov = numpy.cov(M)
print ("Matriz de Covarianzas: ")
print numpy.cov(M)
evals, evecs = LA.eig(Mcov)
print ("Autovalores: ", evals)
print ("Autovectores: ")
print evecs

# obtiene la matriz de covarianzas
#1. Obtener el vector de los valores de la gravedad en cada exp.
#2. Obtener el vector de los valores de la velocidad en x en cada exp.
#3. Obtener el vector de los valores de la velocidad en y en cada exp.
gravedad = []
vSubx = []
vSuby = []

for row in table:
    gravedad.append(row[4])
    vSubx.append(row[2])
    vSuby.append(row[3])

M=numpy.vstack(((gravedad,vSubx),vSuby))
Mcov = numpy.cov(M)
print ("Matriz de Covarianzas: ")
print numpy.cov(M)
evals, evecs = LA.eig(Mcov)
print ("Autovalores: ", evals)
print ("Autovectores: ")
print evecs

for g in gmedia:
	F.append(1 -((g)/(9.81)))  

for i in range(len(angulo)):
	
	angulog.write('%f ' % (angulo[i]))
	angulog.write( '%f ' % (gmedia[i]))
       	angulog.write('\n')


for i in range(len(F)):
	
	valF.write('%f ' % (angulo[i]))
	valF.write( '%f ' % (F[i]))
       	valF.write('\n')

	


# hace un fit de los datos
def fit(x, a, b):
     return a*numpy.sin(numpy.deg2rad(x)) + b       	


param = (scipy.optimize.curve_fit(fit, numpy.array(angulo), numpy.array(F)))[0]

for i in range(len(F)):
	
	residuoF.write('%f ' % (angulo[i]))
	residuoF.write( '%f ' % ( fit(angulo[i],param[0],param[1])-F[i]))
       	residuoF.write('\n')

"""
plt.plot(angulo, fit(angulo,param[0],param[1]), '.')
plt.plot(angulo, F, '.')
plt.xlabel('angulo (grados)')
plt.ylabel('Variacion Gravitacional (adimensional)')
plt.title('Variacion Gravitacional vs angulo')
plt.grid(True)
plt.show()

# grafica residuo vs angulo y lo guarda en el archivo 'Residuo_vs_angulo.png'
<<<<<<< HEAD
plt.plot(angulos, fit(angulo,param[0],param[1])-F, '.')
=======
plt.plot(angulos, fit(angulo,parameters[0],parameters[1])-F, '.')
>>>>>>> 4b45f064eca2d6de2edd64d7477b1d59b12a8a26
plt.xlabel('angulo (grados)')
plt.ylabel('residuo (adimensiona)')
plt.title('Residuo vs angulo')
plt.savefig('Residuo_vs_angulo.png')
plt.grid(True)
plt.show()

"""

	      



			    


		
	



