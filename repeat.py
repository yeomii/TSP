#!/usr/bin/env python

import sys
from subprocess import Popen


def experiment():
	processes = []
	for i in range(1, 21):
		for size in [200, 496, 662, 1001, 1500]:
			processes.append(Popen(["thorq", "--add", "--name", "multistart_%d_%d"%(size, i), "./ga_multistart", "cycle.in.%d"%size]))
	map(lambda p: p.wait(), processes)

if __name__ == "__main__":
		experiment()
