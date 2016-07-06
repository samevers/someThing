import collections

d = {}
d['a'] = 'B'
d['b'] = 'A'
d['c'] = 'C'
d['d'] = 'B'

for k,v in d.items():
	print k,v

print "---------------------"
d = collections.OrderedDict()
d['a'] = 'B'
d['b'] = 'A'
d['c'] = 'C'
d['d'] = 'B'

for k,v in d.items():
	print k,v


