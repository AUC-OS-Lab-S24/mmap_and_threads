
import pandas as pd
import os
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

dfs = []

def compute_average(base_filename):
    dfs = []
    for i in range(5):
        filename = f"{base_filename}_{i}.csv"
        if os.path.exists(filename):
            df = pd.read_csv(filename)
            df.reset_index(drop=True, inplace=True)  # Reset the index
            dfs.append(df)

    if dfs:
        df_concat = pd.concat(dfs)
        df_avg = df_concat.groupby(df_concat.index).mean()
        # write to csv
        df_avg.to_csv(f"{base_filename}_average.csv", index=False)  # Don't write row names (index)
    else:
        print("No CSV files found.")

compute_average("test/increasing_N_add")
compute_average("test/increasing_N_mul")
compute_average("test/increasing_parallelis_add")
compute_average("test/increasing_parallelis_mul")

# Plot averages using matplotlib 

import matplotlib.pyplot as plt

def plot_average(filename):
    df = pd.read_csv(filename)
    x = df.columns[0]
    y = df.columns[1:]
    

    
    df.plot(x=x, y=y, kind='line')
    plt.title(filename)
    plt.xlabel(x)
    plt.ylabel("Time (s)")
    plt.savefig(f"{filename}.png")

    # plot only mmap and threads
    y = ['mmap','parallel']
    df.plot(x=x, y=y, kind='line') 
    plt.title(filename+" (mmap and threads)")
    plt.xlabel(x)
    plt.ylabel("Time (s)")
    plt.savefig(f"{filename}_mmap_threads.png")


    #plt.show()


plot_average("test/increasing_N_add_average.csv")
plot_average("test/increasing_N_mul_average.csv")
plot_average("test/increasing_parallelis_add_average.csv")
plot_average("test/increasing_parallelis_mul_average.csv")

## Read the CSV files
#df1 = pd.read_csv('test/increasing_N_mul_average.csv')
#df2 = pd.read_csv('test/increasing_parallelis_mul_average.csv')
#
## Add a new column to represent the 'N' or 'Parallelism' value
#df1['Parallelism'] = 0
#df2['N'] = 0
#
## Concatenate the two dataframes into one
#df = pd.concat([df1, df2])
#
## Create a 3D plot
#fig = plt.figure(figsize=(12, 8))
#ax = fig.add_subplot(111, projection='3d')
#
#for column in ['mmap', 'threads', 'sequential', 'parallel']:
#    ax.scatter(df['N'], df['Parallelism'], df[column], label=column)
#
#ax.set_xlabel('N')
#ax.set_ylabel('Parallelism')
#ax.set_zlabel('Time')
#ax.legend()
#
#plt.tight_layout()
#plt.show()

from matplotlib.patches import Patch

# Read the CSV files
df1 = pd.read_csv('test/increasing_N_mul_average.csv')
df2 = pd.read_csv('test/increasing_parallelis_mul_average.csv')

# Add a new column to represent the 'N' or 'Parallelism' value
df1['Parallelism'] = 0
df2['N'] = 0

# Concatenate the two dataframes into one
df = pd.concat([df1, df2])

# Create a grid of 'N' and 'Parallelism' values
N = np.linspace(df['N'].min(), df['N'].max(), len(df['N'].unique()))
Parallelism = np.linspace(df['Parallelism'].min(), df['Parallelism'].max(), len(df['Parallelism'].unique()))
N, Parallelism = np.meshgrid(N, Parallelism)

# Create a 3D plot
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Plot a surface for each method
for method, color in zip(['mmap', 'threads', 'sequential', 'parallel'], ['blue', 'green', 'red', 'yellow']):
    # Interpolate the 'Time' values
    Time = griddata((df['N'], df['Parallelism']), df[method], (N, Parallelism), method='linear')

    # Create a surface plot
    ax.plot_surface(N, Parallelism, Time, rstride=1, cstride=1, color=color, alpha=0.5, linewidth=0.1)

# Create a legend
legend_elements = [Patch(facecolor=color, label=label) for color, label in zip(['blue', 'green', 'red', 'yellow'], ['mmap', 'threads', 'sequential', 'parallel'])]
ax.legend(handles=legend_elements)

ax.set_xlabel('N')
ax.set_ylabel('Parallelism')
ax.set_zlabel('Time')

plt.tight_layout()
plt.show()