import csv,sys,matplotlib.pyplot as plt
p=sys.argv[1] if len(sys.argv)>1 else 'gpu.csv';x=[];y=[]
with open(p) as f:
 for r in csv.DictReader(f):x.append(float(r['x']));y.append(float(r['y']))
plt.scatter(x,y,s=2);plt.axis('equal');plt.title('N-body galaxy snapshot');plt.savefig('galaxy.png',dpi=180);plt.show()
