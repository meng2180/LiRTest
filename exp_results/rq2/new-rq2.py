import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

plt.figure(figsize=(18, 3))

ax1=plt.subplot(1,4,1)

mpl.rcParams["font.sans-serif"] = ["SimHei"]
mpl.rcParams["axes.unicode_minus"] = False

x = np.arange(1,14,2)
y = [66.6549, 36.5507, 74.728, 75.4814,68.3458,63.1621,76.1137]
y1 = [24.7856, 1.9701, 26.0902, 42.5572,49.6148,47.6116,48.7307]
y2 = [23.6412, 20.6404, 41.2975, 56.3089,57.4581,54.6192,60.4761]

for i in range(len(y)):
  y[i]=78.3964-y[i]
for i in range(len(y1)):
  y1[i]=51.4145-y1[i] 
for i in range(len(y2)):
  y2[i]=62.9381-y2[i]   

bar_width = 0.45
tick_label = ["RN", "SW", "FG", "TR", "RO","SC","SY"]

ax1.bar(x, y, bar_width, align="center", color="c", label="Car", alpha=0.6)
ax1.bar(x+bar_width, y1, bar_width, color="b", align="center", label="Pedestrian", alpha=0.5)
ax1.bar(x+2*bar_width, y2, bar_width, color="r", align="center", label="Cyclist", alpha=0.7)

ax1.set_xlabel("Pointpillar",fontsize=12)
ax1.set_ylabel("$\mathregular{AP_{T_{O}}}$-$\mathregular{AP_{T_{A}}}$")

ax1.set_xticks(x+bar_width)
ax1.set_xticklabels(tick_label)
ax1.set_ylim(-5,52)

ax1.legend()


ax2=plt.subplot(1,4,2)
mpl.rcParams["font.sans-serif"] = ["SimHei"]
mpl.rcParams["axes.unicode_minus"] = False

x = np.arange(1,14,2)

y = [72.7346,73.9676,79.0499,80.9536,72.058,68.9295,79.1552]
y1 = [31.6602,36.377,39.8015,47.7289,52.4546,53.0951,50.9525]
y2 = [39.7451,56.9571,52.2307,66.2157,62.4614,60.7394,64.2628]

for i in range(len(y)):
  y[i]=81.6116-y[i]
for i in range(len(y1)):
  y1[i]=51.1434-y1[i] 
for i in range(len(y2)):
  y2[i]=66.7401-y2[i]   


bar_width = 0.45
tick_label = ["RN", "SW", "FG", "TR", "RO","SC","SY"]

ax2.bar(x, y, bar_width, align="center", color="c", label="Car", alpha=0.6)
ax2.bar(x+bar_width, y1, bar_width, color="b", align="center", label="Pedestrian", alpha=0.5)
ax2.bar(x+2*bar_width, y2, bar_width, color="r", align="center", label="Cyclist", alpha=0.7)

ax2.set_xlabel("SECOND",fontsize=12)
ax2.set_ylabel("$\mathregular{AP_{T_{O}}}$-$\mathregular{AP_{T_{A}}}$")

ax2.set_xticks(x+bar_width)
ax2.set_xticklabels(tick_label)

ax2.set_ylim(-5,52)
ax2.legend()



ax3=plt.subplot(1,4,3)
mpl.rcParams["font.sans-serif"] = ["SimHei"]
mpl.rcParams["axes.unicode_minus"] = False

x = np.arange(1,14,2)

y = [71.1375,70.8618,77.7341,80.3462,76.1113,68.5777,79.4366]
y1 = [32.8919,50.0041,41.0662,63.9803,66.0779,59.1345,64.1447]
y2 = [38.6075,65.6249,48.6625,74.0425,67.6023,63.7407,71.1023]

for i in range(len(y)):
  y[i]=80.3118-y[i]
for i in range(len(y1)):
  y1[i]=66.4004-y1[i] 
for i in range(len(y2)):
  y2[i]=75.3263-y2[i]   


bar_width = 0.45
tick_label = ["RN", "SW", "FG", "TR", "RO","SC","SY"]

ax3.bar(x, y, bar_width, align="center", color="c", label="Car", alpha=0.6)
ax3.bar(x+bar_width, y1, bar_width, color="b", align="center", label="Pedestrian", alpha=0.5)
ax3.bar(x+2*bar_width, y2, bar_width, color="r", align="center", label="Cyclist", alpha=0.7)

ax3.set_xlabel("Part-$\mathregular{A^2}$Net",fontsize=12)
ax3.set_ylabel("$\mathregular{AP_{T_{O}}}$-$\mathregular{AP_{T_{A}}}$")
ax3.set_xticks(x+bar_width)
ax3.set_ylim(-5,52)
ax3.set_xticklabels(tick_label)
ax3.legend()



ax4=plt.subplot(1,4,4)
mpl.rcParams["font.sans-serif"] = ["SimHei"]
mpl.rcParams["axes.unicode_minus"] = False

x = np.arange(1,14,2)

y = [76.2459, 69.7369, 82.3133, 82.7859,79.1844,75.8945,82.0691]
y1 = [26.4622, 33.8783, 38.2203, 49.1807,54.379,57.7245,53.9581]
y2 = [26.1079, 48.8155, 38.7079, 68.269,66.4296,62.9678,70.2927]

for i in range(len(y)):
  y[i]=84.3605-y[i]
for i in range(len(y1)):
  y1[i]=54.4902-y1[i] 
for i in range(len(y2)):
  y2[i]=70.3809-y2[i]   


bar_width = 0.45
tick_label = ["RN", "SW", "FG", "TR", "RO","SC","SY"]

ax4.bar(x, y, bar_width, align="center", color="c", label="Car", alpha=0.6)
ax4.bar(x+bar_width, y1, bar_width, color="b", align="center", label="Pedestrian", alpha=0.5)
ax4.bar(x+2*bar_width, y2, bar_width, color="r", align="center", label="Cyclist", alpha=0.7)

ax4.set_xlabel("PV-RCNN",fontsize=12)
ax4.set_ylabel("$\mathregular{AP_{T_{O}}}$-$\mathregular{AP_{T_{A}}}$")

ax4.set_xticks(x+bar_width)
ax4.set_xticklabels(tick_label)
ax4.set_ylim(-5,52)

ax4.legend()



plt.savefig('new_5-2.pdf', bbox_inches='tight')

plt.show()

						
						
						
						
						
						

						
						
						
						
						
						
						
