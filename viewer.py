import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
import numpy as np


def load_ppm(filename):
    with open(filename, "rb") as f:
        header = f.readline().decode().strip()
        
        if header not in ("P3", "P6"):
            raise ValueError("Formato PPM não suportado!")

        
        while True:
            line = f.readline().decode().strip()
            if line.startswith("#"):  
                continue
            width, height = map(int, line.split())
            break
        
        max_val = float(f.readline().decode().strip())  

        
        if header == "P3": 
            pixels = []
            for line in f:
                for val in line.split():
                    num = float(val)  
                    pixels.append(int(num * 255) if max_val <= 1 else int(num)) 
            pixels = np.array(pixels, dtype=np.uint8).reshape((height, width, 3))

        elif header == "P6":  # Formato binário
            pixels = np.frombuffer(f.read(), dtype=np.uint8)
            pixels = pixels.reshape((height, width, 3))

        return Image.fromarray(pixels)


def open_file():
    file_path = filedialog.askopenfilename(filetypes=[("PPM files", "*.ppm")])
    if file_path:
        img = load_ppm(file_path)
        img = img.resize((500, 500))  
        img_tk = ImageTk.PhotoImage(img)
        label.config(image=img_tk)
        label.image = img_tk



root = tk.Tk()
root.title("Visualizador de PPM")

btn = tk.Button(root, text="Abrir PPM", command=open_file)
btn.pack()

label = tk.Label(root)
label.pack()

root.mainloop()
