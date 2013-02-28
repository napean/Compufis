#!/usr/bin/ python
#encoding: UTF-8
import sys, codecs , numpy

#opens file with the right encoding and read everything
filein = codecs.open(sys.argv[1], "r", "utf8")
fullin = filein.read()
fulltext = fullin.lower() #make everything lower case
filein.close()

#this is the list of different characters
all_characters = list(set(fulltext))

# a list of charachters to remove from the all_characters list
to_remove = [' ', ',', '_', '.','(', ')', '#','"','[',']','\n', '\r', u'\x0c',u'\u011d', u'\u2014', u'\u016d', u'\u0109', u'\u2123']

for undesired in to_remove:
    try:
        all_characters.remove(undesired) #if undesired is not in the list, remove fails
    except:
        pass

#count the number of times in the text
frequencies = []
for valid in all_characters:
    n_times = 1.0 * fulltext.count(valid)
    frequencies.append(n_times)

#make a final list of frequencies and charachters
n_total = sum(frequencies)
final_list = []
for frequencies, letter in zip(frequencies, all_characters):
    final_list.append((frequencies/n_total, letter))

#sort it
final_list.sort()
final_list.reverse()

#write it to a file
fileout = codecs.open("frecuencias"+sys.argv[1], "w", "utf8")
for item in final_list:
    fileout.write("%s %f\n"%(item[1], item[0]))

fileout.close()


out = open ("frecuencias"+sys.argv[1], 'r')
coso = out.readlines()

listfrecuencia2 =  []
lista_fi2 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19]


for i in range (20):

 lala = coso[i].split()
 listfrecuencia2.append((numpy.log(float(lala[1]))))


xx =numpy.array(lista_fi2)
xx2= numpy.array(listfrecuencia2)

p = numpy.polyfit(xx, xx2, 1)


fileout = codecs.open("k"+sys.argv[1], "w", "utf8")
fileout.write("%f\n"%( p[0]))


print p[0]
