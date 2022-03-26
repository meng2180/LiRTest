import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

Jac_pp=np.loadtxt('Jac_pp.txt') 
Jac_sc=np.loadtxt('Jac_sc.txt') 
Jac_part=np.loadtxt('Jac_part.txt') 
Jac_pv=np.loadtxt('Jac_pv.txt') 

plt.rcParams['axes.unicode_minus'] = False
 

data=[Jac_pp,Jac_sc,Jac_part,Jac_pv]

print(np.mean(Jac_pv))

bplot1=plt.boxplot(x = data, 
 
            patch_artist=True, 
 
            boxprops = {'color':'black','facecolor':'#9999ff'}, 
 
            flierprops = {'marker':'o','markerfacecolor':'black','color':'black','markersize':3}, 
 
            medianprops = {'linestyle':'--','color':'red'},
            
            labels=['PointPillar$\mathregular{s^2}$','SECON$\mathregular{D^2}$','Part-$\mathregular{A^2}$','PV-RCN$\mathregular{N^2}$']) 

colors=['sandybrown','dodgerblue','seagreen','cadetblue']

for patch,color in zip(bplot1['boxes'],colors):
  patch.set_facecolor(color)

plt.xlabel('Models',fontsize=14)
plt.ylabel('Jaccard Distance',fontsize=14)

plt.tick_params(top='off', right='off')

plt.savefig('results_imgs.png', bbox_inches='tight')
plt.show()