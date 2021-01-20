from tkinter import *
from PIL import Image, ImageTk

root = Tk()
root.title("Lines")
root.geometry("800x625")
bg_color = '#454545'
root["bg"] = bg_color
#newsize = (840, 625)                    #tried to set bgr picture
#bgr = Image.open("resources/page-bgr.png").resize(newsize)
#bgr_image = ImageTk.PhotoImage(bgr)
#bgr_lbl = Label(root, image=bgr_image)
#bgr_lbl.grid(rowspan=11, columnspan=14)

aqua_b = Image.open("resources/ball-aqua.png")
blue_b = Image.open("resources/ball-blue.png")
green_b = Image.open("resources/ball-green.png")

aqua = ImageTk.PhotoImage(aqua_b.crop((1, 0, 67, 66)).resize((35,35)))
blue = ImageTk.PhotoImage(blue_b.crop((1, 0, 67, 66)).resize((35,35)))
green= ImageTk.PhotoImage(green_b.crop((1, 0, 67, 66)).resize((35,35)))

tileset = Image.open("resources/cell-bgr.png")
img = ImageTk.PhotoImage(tileset.crop((1, 0, 67, 66))) #light cell
img_2 = ImageTk.PhotoImage(tileset.crop((1, 69, 67, 135))) #dark cell

for row in range(9):
    for col in range(9):
        lbl = Label(root, image=img, borderwidth=0)
        lbl.grid(row=row, column=col, padx=1, pady=1)

indent = 10
buttton_colour='#6e7078'

score = 0
lbl_name = Label(root, text='Линии', font=("Arial", 20), fg="white", bg=bg_color)
lbl_score = Label(root, text='Счет: '+ str(score), font=("Arial", 20), fg="white", bg=bg_color)
start_button = Button(text="Сделать ход", font=("Arial", 10), fg="white", width=12, height=1, bg=buttton_colour)
lbl_prompt = Label(root, text='Подсказка:', font=("Arial", 15), fg="light gray", bg=bg_color)
ng_button = Button(text="Новая игра", font=("Arial", 15), fg="white", width=11, height=1, bg=buttton_colour)

lbl_name.grid(row=0, column=10, sticky=W, padx=indent)
lbl_score.grid(row=1, column=10, sticky=W, padx=indent)
start_button.grid(row=2, column=10, padx=indent)
lbl_prompt.grid(row=3, column=10, sticky=N, padx=indent)
ng_button.place(x=622, y =300)

lbl_aqua = Label(root, image=aqua, bg=bg_color, borderwidth=0)
lbl_blue = Label(root, image=blue, bg=bg_color, borderwidth=0)
lbl_green = Label(root, image=green, bg=bg_color, borderwidth=0)
lbl_aqua.grid(row=3, column=10, sticky=SW, padx=indent)
lbl_blue.grid(row=3, column=10, sticky=S, padx=indent)
lbl_green.grid(row=3, column=10, sticky=SE, padx=indent)

root.mainloop()