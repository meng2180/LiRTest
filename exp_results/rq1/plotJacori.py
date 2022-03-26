import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

Jac_pp=np.loadtxt('Jacori_pp.txt') 
Jac_sc=np.loadtxt('Jacori_sc.txt') 
Jac_part=np.loadtxt('Jacori_part.txt') 
Jac_pv=np.loadtxt('Jacori_pv.txt') 

plt.rcParams['axes.unicode_minus'] = False 

# print(np.percentile(Jac_pv[3],(50),interpolation='midpoint'))
for i in range(7): 
  print(np.mean(Jac_pv[i]))


plt.figure(figsize=(18,4))

ax1=plt.subplot(1,4,1)

data=[Jac_pp[0],Jac_pp[1],Jac_pp[2],Jac_pp[3],Jac_pp[4],Jac_pp[5],Jac_pp[6]]

bplot1=ax1.boxplot(x = data, 
 
            patch_artist=True, 
 
            boxprops = {'color':'black','facecolor':'#9999ff'}, 
 
            flierprops = {'marker':'o','markerfacecolor':'black','color':'black','markersize':3}, 
 
            medianprops = {'linestyle':'--','color':'red'},
            
            labels=['RN','SW','FG','TR','RO','SC','SY']) 

colors=['cornflowerblue','sandybrown','cadetblue','mediumpurple','mediumseagreen','rosybrown','slategray']

for patch,color in zip(bplot1['boxes'],colors):
  patch.set_facecolor(color)

ax1.set_xlabel('PointPillars',fontsize=12)
ax1.set_ylabel('Jaccard Distance',fontsize=9)

plt.tick_params(top='off', right='off')



ax2=plt.subplot(1,4,2)

data=[Jac_sc[0],Jac_sc[1],Jac_sc[2],Jac_sc[3],Jac_sc[4],Jac_sc[5],Jac_sc[6]]


bplot1=ax2.boxplot(x = data, 
 
            patch_artist=True, 
 
            boxprops = {'color':'black','facecolor':'#9999ff'},
 
            flierprops = {'marker':'o','markerfacecolor':'black','color':'black','markersize':3}, 

            medianprops = {'linestyle':'--','color':'red'},
            
            labels=['RN','SW','FG','TR','RO','SC','SY']) 

colors=['cornflowerblue','sandybrown','cadetblue','mediumpurple','mediumseagreen','rosybrown','slategray']

for patch,color in zip(bplot1['boxes'],colors):
  patch.set_facecolor(color)

ax2.set_xlabel('SECOND',fontsize=12)
ax2.set_ylabel('Jaccard Distance',fontsize=9)




ax3=plt.subplot(1,4,3)

data=[Jac_part[0],Jac_part[1],Jac_part[2],Jac_part[3],Jac_part[4],Jac_part[5],Jac_part[6]]

bplot1=ax3.boxplot(x = data, 
 
            patch_artist=True, 

            boxprops = {'color':'black','facecolor':'#9999ff'},
 
            flierprops = {'marker':'o','markerfacecolor':'black','color':'black','markersize':3}, 
 
            medianprops = {'linestyle':'--','color':'red'},
            
            labels=['RN','SW','FG','TR','RO','SC','SY']) 

colors=['cornflowerblue','sandybrown','cadetblue','mediumpurple','mediumseagreen','rosybrown','slategray']

for patch,color in zip(bplot1['boxes'],colors):
  patch.set_facecolor(color)

ax3.set_xlabel('Part-$\mathregular{A^2}$',fontsize=12)
ax3.set_ylabel('Jaccard Distance',fontsize=9)


ax4=plt.subplot(1,4,4)

data=[Jac_pv[0],Jac_pv[1],Jac_pv[2],Jac_pv[3],Jac_pv[4],Jac_pv[5],Jac_pv[6]]


bplot1=ax4.boxplot(x = data, 
 
            patch_artist=True, 
 
            boxprops = {'color':'black','facecolor':'#9999ff'}, 
 
            flierprops = {'marker':'o','markerfacecolor':'black','color':'black','markersize':3}, 
 
            medianprops = {'linestyle':'--','color':'red'},
            
            labels=['RN','SW','FG','TR','RO','SC','SY']) 

colors=['cornflowerblue','sandybrown','cadetblue','mediumpurple','mediumseagreen','rosybrown','slategray']

for patch,color in zip(bplot1['boxes'],colors):
  patch.set_facecolor(color)

ax4.set_xlabel('PV-RCNN',fontsize=12)
ax4.set_ylabel('Jaccard Distance',fontsize=9)

plt.tick_params(top='off', right='off')

plt.savefig('results_imgs.pdf', bbox_inches='tight') 

plt.show()