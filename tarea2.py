import sys, string, os

 sys.argv

i = 0
a = 0
b = 0
lista = []
lista_fi = []
infile = open(argv[1],'r')

#load the full text by lines
text = infile.readlines()

while !text[i+1]:
    letras =list(text[i].split)
    for f in range (letras.itemsize()):
        lista.append(lestras[f])


for a in range (lista.itemsize()):
    for b in range (lista_fi.itemsize()):
        if(lista[a] == lista_fi[b]):
            
        else:
            lista_fi.append(lista[a])

 arc = open('frecuencia','w')
 arc.close()

for h  in range(lista_fi.itemsize()):
     arc = open('frecuencia','w')
     arc.write( print lista_fi[h], lista.count(lista_fi[h]))
       
   

    
    
    
