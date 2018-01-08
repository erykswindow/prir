#!/usr/bin/python

import sys
import csv
import matplotlib.pyplot as plt

i = 0;

with open(sys.argv[1], 'rb') as csvfile:
	reader = csv.reader(csvfile, delimiter=",")
	N = []
	threads = []
	subthreads = []
	error = []
	time = []
	for row in reader:
		N.append(long(row[0]) * long(row[0]))
		threads.append(int(row[1]))
		error.append(float(row[2]))
		time.append(float(row[3]))


Ns = []
for i in range(0, len(N)):
	if N[i] not in Ns:
		Ns.append(N[i])

ttn = zip(threads, time, error, N)

valuesDict = {}
errorsDict = {}
for n in Ns:
	valuesDict[n] = []
	errorsDict[n] = []

for thread, time, error, n in ttn:
	valuesDict[n].append((thread, time))
	errorsDict[n].append((thread, error))


timeChartName = './results/%s/time.png' % sys.argv[2]
errorChartName = './results/%s/error.png' % sys.argv[2]

figureThread = plt.figure()

for n in Ns:
	threads = [x for x, y in valuesDict[n]]
	times = [y for x, y in valuesDict[n]]
	label = 'N = %d' % (n)
	plt.plot(threads, times, '-x', label=label)


plt.ylabel('Czas obliczen [s]')
plt.xlabel('Liczba watkow [j]')
plt.legend()

figureThread.savefig(timeChartName)

figureError = plt.figure()
for n in Ns:
	threads = [x for x, y in errorsDict[n]]
	errors = [y for x, y in errorsDict[n]]
	label = 'N = %d' % (n)
	plt.plot(threads, errors, '-o', label=label)


plt.ylabel('Blad [j]')
plt.xlabel('Liczba watkow [j]')
plt.legend()

figureError.savefig(errorChartName)
