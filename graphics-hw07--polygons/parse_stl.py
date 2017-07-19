from pprint import pprint

with open("Suicune.stl", "r") as f:
    lil = f.read().split('\n')
    uzi = [line[(line.find("vertex") + len("vertex") + 1):] for line in lil if "vertex" in line]
    for v in uzi:
        v.replace("-1e-06", "0")
    vert = ""
    for i in xrange(0, len(uzi), 3):
        vert += "\npolygon\n%s %s %s" % (uzi[i], uzi[i+1], uzi[i+2])
    newBars = '''
ident
rotate
y 50
rotate
x 20
scale
20 20 20
move
250 100 0
apply
display
save
suicune.png
'''
    vert += newBars
    with open("suicune_script", "w") as f2:
        f2.write(vert)
    print(vert)
    
