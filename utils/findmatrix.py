#!/usr/local/bin/python

tc1 = (((1, 0), (0, 1)),
       ((0, 1), (-1, 1)),
       ((-1, 1), (-1, 0)))

tc2 = map(lambda x: (x[1], x[0]), tc1)

tc = tc2

r = -1, 0, 1
for a in r:
    for b in r:
        for c in r:
            for d in r:
                for (x, y), t in tc:
                    # nx = a * x + b * y
                    # ny = c * x + d * y
                    tt = a * x + b * y, c * x + d * y
                    if t != tt:
                        break
                else:
                    print a, b, c, d
