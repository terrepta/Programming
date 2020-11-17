import json

with open('in.json', 'r') as f:     #открытие in.json
    in_file = json.load(f)

all_u = 0;		
for item in in_file:         		#подсчет количества юзеров
	if item ['userId'] >= all_u:
	    all_u = item ['userId']










for item in in_file:	
    for u in range (all_u):					
        del item ['id']
        del item ['title']
        del item ['completed']
        item ["task_completed"] = n_task_comp[i-1];
        item ["userId"] = i;

