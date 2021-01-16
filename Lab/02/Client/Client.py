import openpyxl
from flask import Flask, request, jsonify
from datetime import datetime

def find_next_cell(sheet):
    i = 2
    while sheet[i][0].value != None:
        i += 1
    return i

buf = []
def gen_list(sheet):
    n = find_next_cell(sheet)
    for i in range(len(buf)):
        for j in range(len(buf[i]['check'])):
            sheet[num][0].value = n - 1
            sheet[num][1].value = buf[i]['user_id']
            sheet[num][2].value = buf[i]['datetime']
            sheet[num][3].value = buf[i]['check'][j]['item']
            sheet[num][4].value = buf[i]['check'][j]['price']
            n += 1
    del n, i, j
    return sheet

def exel_file(data):
    global buf
    data['datetime'] = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
    buf.append(data)
    if len(buf) >= 1000:
        try:
            book = openpyxl.open(r'C:\Users\Admin\Documents\Programming\Lab\02\Client\data.xlsx', read_only=False)
        except:
            book = openpyxl.Workbook()
        sheet = book.active
        if sheet['A1'].value == None:
            sheet['A1'] = 'N'
            sheet['B1'] = 'User ID'
            sheet['C1'] = 'Datetime'
            sheet['D1'] = 'Item'
            sheet['E1'] = 'Prise'
        sheet = gen_list(sheet)
        book.save(r'C:\Users\Admin\Documents\Programming\Lab\02\Client\data.xlsx')
        book.close()
        buf = []


app = Flask(__name__)
@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'GET':
        return 'Пришел GET запрос'
    elif request.method == 'POST':
        data = request.json
        exel_file(data)
        return 'OK'
if __name__ == "__main__":
    app.run()