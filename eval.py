#!/usr/bin/env python

import sys, os, re
from math import sqrt

def se(lst):
	m = sum(lst) / len(lst)
	sqsum = sum([i**2 for i in lst]) / len(lst)
	return sqrt(abs(sqsum - m*m))

rec = {'ch': {}, 'un': {}, 're': {}, '32': {}, '64': {}, 'ms': {}}

for f in os.listdir(os.getcwd()):
	if f.startswith("execution_") and f.endswith("stdout"):
		fin = open(f, 'r')
		size = int(f.split('_')[1])
		num = int(f.split('_')[2].split('.')[0])
		key = 'ch'
		if num > 20 and num < 41:
			key = 'un'
		elif num > 40 and num < 61:
			key = 're'
		elif num > 60 and num < 65:
			key = '64'
		elif num > 64:
			key = '32'

		mutation = 0
		time = -1

		for l in fin:
			if l.startswith('m'):
				mutation += 1
		if len(l) > 0 and l[0].isdigit():
			time = float(l) 
		
		if size not in rec[key]:
			rec[key][size] = {'time': [], 'mutation': []}
		if time > 0:
			rec[key][size]['time'].append(time)
			rec[key][size]['mutation'].append(mutation)
	
	if f.startswith("multistart_") and f.endswith("stdout"):
		fin = open(f, 'r')
		size = int(f.split('_')[1])
		num = int(f.split('_')[2].split('.')[0])
		key = 'ms'

		mutation = 0
		time = -1

		for l in fin:
			pass
		if len(l) > 0 and l[0].isdigit():
			time = float(l) 
		if size not in rec[key]:
			rec[key][size] = {'time': [], 'mutation': []}
		if time > 0:
			rec[key][size]['time'].append(time)
			rec[key][size]['mutation'].append(mutation)

fout = open("results", 'w')
for size in [200, 496, 662, 1001, 1500]:
	for key in sorted(rec.keys()):
		if size in rec[key]:
			tlst = rec[key][size]['time']
			mlst = rec[key][size]['mutation']
			fout.write("%s, %d, %f, %f, %f, %d\n" % (key, size, min(tlst), sum(tlst) / len(tlst), se(tlst), len(tlst)))
			fout.write("%s, %d, %f, %f, %d\n" % (key, size, max(mlst), sum(mlst) / len(mlst), len(mlst)))

	fout.write("\n")
fout.close()

