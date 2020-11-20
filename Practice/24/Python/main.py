import json

with open('in.json', 'r') as f:     #открытие in.json
    in_file = json.load(f)          #чтение файла

all_u = 0;		
for item in in_file:         		#подсчет количества юзеров
	if item ['userId'] >= all_u:
	    all_u = item ['userId']

out_file = []                       #создание нового списка out_file

for i in range(1, all_u + 1):          #перебор всех юзеров, в данном цикле каждому их них
    n_task_comp = 0                   #будет присваиваться свое значение n_task_comp (количество выполненных заданий)
    for j in range(len(in_file)):
        if in_file[j]['completed'] and in_file[j]['userId'] == i:  #подсчет выполненных заданий
            n_task_comp +=1                                       #одного юзера
    element = {"task_completed":n_task_comp, "userId":i}  #внесение записей в словарь
    out_file += [element]                               #добавление элементов в список out_file

with open("out.json", "w") as w:            #открытие out.json
    json.dump(out_file, w, indent=2)        #запись списка в файл out.json