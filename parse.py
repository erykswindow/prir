#!/usr/bin/python

import sys
import csv
import matplotlib.pyplot as plt

N = []
threads = []
subthreads = []
error = []
time = []

def remove_repeats(x):
	result = []
	for i in range(0, len(N)):
		if x[i] not in result:
			result.append(x[i])
	return result

def plot(name, input, input_keys,  marker, xLabel, yLabel, ):
	figure = plt.figure()
	plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
	for key in input_keys:
		xs = [x for x, y in input[key]]
		ys = [y for x, y in input[key]]
		label = 'N = %.1e' % (key)
		plt.plot(xs, ys, marker, label=label)

	plt.ylabel(yLabel)
	plt.xlabel(xLabel)
	plt.legend()
	figure.savefig(name)

def empty_array_dictionary(keys):
	returnValue  = {}
	for key in keys:
		returnValue[key] = []
	return returnValue


with open(sys.argv[1], 'rb') as csvfile:
	reader = csv.reader(csvfile, delimiter=",")

	for row in reader:
		N.append(long(row[0]) * long(row[0]))
		threads.append(int(row[1]))
		error.append(float(row[2]))
		time.append(float(row[3]))

	csvfile.close()

Ns = remove_repeats(N)
Ts = remove_repeats(threads)
valuesDict = empty_array_dictionary(Ns)
errorsDict = empty_array_dictionary(Ns)

ttn = zip(threads, time, error, N)

for thread, time, error, n in ttn:
	valuesDict[n].append((thread, time))
	errorsDict[n].append((thread, error))

timeChartName = './results/%s/time.png' % sys.argv[2]
errorChartName = './results/%s/error.png' % sys.argv[2]

plot(timeChartName, valuesDict, Ns,  '-x', 'Liczba watkow [j]', 'Czas obliczen [s]')
plot(errorChartName, errorsDict, Ns, '-o', 'Liczba watkow [j]', 'Blad[j]')

timesDict = {}
errorDict = {}

for thread, time, error, n in ttn:
	key = (n, thread)
	timesDict[key] = time
	errorDict[key] = error

errorTableName = './results/%s/error.csv' % sys.argv[2]
timeTableName = './results/%s/time.csv' % sys.argv[2]

with open(timeTableName, 'w+') as tFile, open(errorTableName, 'w+') as eFile:

	tFile.write('N/threads;')
	eFile.write('N/threads;')

	for i in range(0, len(Ts)):
		value = '%d' % Ts[i]
		tFile.write(value)
		eFile.write(value)
		if i + 1 == len(Ts):
			tFile.write('\n')
			eFile.write('\n')
		else:
			tFile.write(';')
			eFile.write(';')
			
	for i in range(0, len(Ns)):
		value = '%.1e;' % Ns[i]
		tFile.write(value)
		eFile.write(value)
		for j in range(0, len(Ts)):
			n = Ns[i]
			t = Ts[j]
			key = (n,t)
			tFile.write('%e' % timesDict[key])
			eFile.write('%e' % errorDict[key])
			if j + 1 == len(Ts):
				tFile.write('\n')
				eFile.write('\n')
			else:
				tFile.write(';')
				eFile.write(';')

	tFile.close()
	eFile.close()
		
