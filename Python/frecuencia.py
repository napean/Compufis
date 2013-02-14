import sys, string, os , numpy

sys.argv

i = 0
a = 0
b = 0
num = 0.0
veces = 0.0
frecuencia = 1.0
infile = open(sys.argv[1],'r')

titulo=sys.argv[1]

#load the full text by lines
texto = infile.readlines()

text = [x.lower() for x in texto]

for i in range(len(text)):
    if i==0:
        letras=list(text[i])
    else:
        letras.extend(text[i])

    

num = len(letras)

lista_fi =list(set(letras))



lista_fi.remove('.')
lista_fi.remove('!')
lista_fi.remove('?')
lista_fi.remove('(')
lista_fi.remove(')')
lista_fi.remove('#')
lista_fi.remove(';')
lista_fi.remove(':')
lista_fi.remove('$')
lista_fi.remove('%')
lista_fi.remove(' ')
lista_fi.remove(',')
lista_fi.remove('-')
lista_fi.remove('_')
lista_fi.remove(']')
lista_fi.remove('[')
lista_fi.remove('@')
lista_fi.remove('/')
lista_fi.remove('"')


nombrearchivo = "frecuencia_" + titulo 

arc = open(nombrearchivo,'w')



listfrecuencia = []


for h in range(len(lista_fi)):
    listfrecuencia.extend(lista_fi[h]) 

for u in range(len(lista_fi)):   
        veces = letras.count(lista_fi[u])
        frecuencia = (veces*1.0)/(num*1.0)
        listfrecuencia[u]=frecuencia


indiceord = numpy.argsort(listfrecuencia)

for index in indiceord:
    arc.write('%s %f\n'%(lista_fi[index],listfrecuencia[index]))
    


    
