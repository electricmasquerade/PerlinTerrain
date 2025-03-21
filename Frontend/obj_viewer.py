import os.path
import tkinter as tk
from tkinter import ttk
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # required for 3D plotting
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import subprocess
import pandas as pd

# Dummy function to simulate terrain data generation
def generate_terrain_data(resolution):
    data = pd.read_csv('csvs/terrain.csv')
    X = data['x']
    Y = data['y']
    Z = data['z']
    return X, Y, Z

def update_plot():
    # Get current resolution from slider
    resolution = res_slider.get()
    frequency = freq_slider.get()
    x_offset = xoff_slider.get()
    y_offset = yoff_slider.get()

    # Call subprocess to generate terrain data
    exe_path = os.path.abspath("cmake-build-debug/Terrain")
    cmd = [exe_path, str(frequency), str(resolution), str(x_offset), str(y_offset), str(0)]
    subprocess.run(cmd, check=True)
    # Generate terrain data (you can also incorporate frequency, offsets, etc.)
    x, y, z = generate_terrain_data(resolution)

    # Clear the axes and re-plot
    ax.clear()
    ax.plot_trisurf(x, y, z, cmap='terrain', edgecolor='none')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    canvas.draw()

def export_obj():
    # Just reuse the update plot code basically. Does not plot data.
    print("Exporting OBJ file...")
    resolution = res_slider.get()
    frequency = freq_slider.get()
    x_offset = xoff_slider.get()
    y_offset = yoff_slider.get()

    # Call subprocess to generate terrain data
    exe_path = os.path.abspath("cmake-build-debug/Terrain")
    cmd = [exe_path, str(frequency), str(resolution), str(x_offset), str(y_offset), str(1)]
    subprocess.run(cmd, check=True)
    # Example: subprocess.run(["python", "export_obj.py"])
    # For demonstration purposes:
    export_status.config(text="OBJ exported successfully.")
    export_status.config(text="Located at ./objs/terrain.obj")

root = tk.Tk()
root.title("Terrain Generator GUI")
root.geometry("1200x1000")

# Configure grid rows and columns for the root
root.grid_rowconfigure(0, weight=1)  # Canvas row expands
root.grid_rowconfigure(1, weight=0)  # Parameter row remains fixed
root.grid_columnconfigure(0, weight=1)  # Single column expands

# Create the canvas and place it in row 0
fig = plt.figure(figsize=(6,6))
ax = fig.add_subplot(111, projection='3d')
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().grid(row=0, column=0, sticky="nsew")

# Create the parameter frame and place it in row 1
param_frame = ttk.Frame(root)
param_frame.grid(row=1, column=0, sticky="nsew", pady=10)

# Configure grid weight in the parameter frame:
# Assume we have, say, 8 columns (labels, sliders, and buttons) that we want to share space evenly.
for i in range(8):
    param_frame.grid_columnconfigure(i, weight=1)

# Now add your controls using grid instead of pack
ttk.Label(param_frame, text="Resolution:").grid(row=0, column=0, sticky="nsew", padx=5)
res_slider = tk.Scale(param_frame, from_=20, to=200, orient=tk.HORIZONTAL)
res_slider.set(25)
res_slider.grid(row=0, column=1, sticky="nsew", padx=5)

ttk.Label(param_frame, text="Frequency:").grid(row=0, column=2, sticky="nsew", padx=5)
freq_slider = tk.Scale(param_frame, from_=1, to=50, orient=tk.HORIZONTAL)
freq_slider.set(5)
freq_slider.grid(row=0, column=3, sticky="nsew", padx=5)

ttk.Label(param_frame, text="X-Offset:").grid(row=0, column=4, sticky="nsew", padx=5)
xoff_slider = tk.Scale(param_frame, from_=-10, to=10, orient=tk.HORIZONTAL)
xoff_slider.set(0)
xoff_slider.grid(row=0, column=5, sticky="nsew", padx=5)

ttk.Label(param_frame, text="Y-Offset:").grid(row=0, column=6, sticky="nsew", padx=5)
yoff_slider = tk.Scale(param_frame, from_=-10, to=10, orient=tk.HORIZONTAL)
yoff_slider.set(0)
yoff_slider.grid(row=0, column=7, sticky="nsew", padx=5)

# You can place the update and export buttons on a new row if desired.
update_btn = ttk.Button(param_frame, text="Update Plot", command=update_plot)
update_btn.grid(row=1, column=0, columnspan=4, sticky="nsew", padx=5, pady=5)
export_btn = ttk.Button(param_frame, text="Export OBJ", command=export_obj)
export_btn.grid(row=1, column=4, columnspan=4, sticky="nsew", padx=5, pady=5)

export_status = ttk.Label(param_frame, text="")
export_status.grid(row=2, column=0, columnspan=8, sticky="nsew", padx=5, pady=5)
update_plot()
root.mainloop()