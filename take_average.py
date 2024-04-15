
import pandas as pd
import os
import matplotlib.pyplot as plt

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
    plt.savefig(f"{filename}.png")
    #plt.show()


plot_average("test/increasing_N_add_average.csv")
plot_average("test/increasing_N_mul_average.csv")
plot_average("test/increasing_parallelis_add_average.csv")
plot_average("test/increasing_parallelis_mul_average.csv")