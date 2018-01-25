#!/usr/bin/python

import sys
import csv
import matplotlib.pyplot as plt

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

def writeCSV(name, row_column_name, rows, columns, valuesDict):
	with open(name, 'w+') as file:
		writer = csv.writer(file)

		writer.writerow([row_column_name] + columns)

		for row in rows:
			rowTitle = '%.1e;' % row
			values = ['%e' % valuesDict[(row,column)] for column in columns]
			writer.writerow([rowTitle] + values)

		file.close()



N = []
threads = []
subthreads = []
error = []
time = []

filename = sys.argv[1]
with open(filename, 'rb') as csvfile:
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

timesDict = {}
errorDict = {}

ttn = zip(threads, time, error, N)

for thread, time, error, n in ttn:
	key = (n, thread)
	timesDict[key] = time
	errorDict[key] = error
	valuesDict[n].append((thread, time))
	errorsDict[n].append((thread, error))

folderName = sys.argv[2]
timeChartName = './results/%s/time.png' % folderName
errorChartName = './results/%s/error.png' % folderName
timeTableName = './results/%s/time.csv' % folderName
errorTableName = './results/%s/error.csv' % folderName

plot(timeChartName, valuesDict, Ns,  '-x', 'Liczba watkow [j]', 'Czas obliczen [s]')
plot(errorChartName, errorsDict, Ns, '-o', 'Liczba watkow [j]', 'Blad[j]')
writeCSV(errorTableName, 'N/threads', Ns, Ts, errorDict)
writeCSV(timeTableName, 'N/threads', Ns, Ts, timesDict)