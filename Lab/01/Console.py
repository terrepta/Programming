from tkinter import *
import json
import requests

def site(event = None):
	try:
		upload = requests.get('http://localhost:3000/raw').content.decode("utf8")
		upload_date = json.loads(upload)

		description.config(text=str(upload_date["description"]))
		temperature.config(text=str(round(upload_date["temp"])) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", site)
root.geometry("200x250")

color = "#eda42d"
w = 100
h = 30

top_frame = Frame(root, bg = color, width = w, height = h)
main_frame = Frame(root, bg = "white",  width = w, height = w)
down_frame = Frame(root, bg = color, width = w, height = h)

top_frame.pack(side = TOP, fill = X)
main_frame.pack(expand = True, fill = BOTH)
down_frame.pack(side = BOTTOM, fill = X)


city = Label(top_frame, font = ("Helvetica", 16), text = "Симферополь", bg = color)
temperature = Label(main_frame, font=("Helvetica", 60, 'bold'), bg = "white")
description = Label(top_frame, font=("Helvetica", 12), bg = color)

city.pack(pady = 0)
temperature.pack(expand = True)
description.pack(pady = 0)

site()

root.mainloop()