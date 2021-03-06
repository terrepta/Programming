<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>

<br><br>

<p>студентки 1 курса группы ПИ-б-о-201(2)<br>
Коротеевой Кристины Александровны<br>
направления подготовки 09.03.04 "Программная инженерия"</p>


<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>

<p align="center">Симферополь, 2020</p>
<hr>


## Цели работы

* Получить представления о структуре post-запроса;
* Изучить метод взаимодействия web-приложений через webhook-и;

## Постановка задачи

1. Разработайте и зарегистрируйте навык для Алисы на сервисе Яндекс.Диалоги

2. В качестве backend-a для навыка реализуйте приложение на языке С++ выполняющее следующие функции:

    1. Составление продуктовой корзины:

        * Добавление продукта в корзину;
        * Удаление продукта из корзины;
        * Очистка корзины;
        * Вывод списка товаров в корзине;
        * Подсчёт стоимости товаров в корзине.

    2. Вывод справочной информации по навыку;

    3. Регистрацию webhook-ов сторонних сервисов;

    4. Отправку данных на сторонние сервисы. 

3. В качестве стороннего сервиса реализуйте приложение на языке Python выполняющее следующие функции:

    1. Ожидание данных о покупке;
    2. Сохранение поступивших данных в excel-документ.

Подробности указаны далее.

## Выполнение работы

#### Подготовка к созданию программы, изучение материала

1. Изучаем структуру post-запросов
2. Изучаем информацию о вебхуках

#### Подготовка и создание серверного приложения

Создаём серверное приложение, генерирующее сайт с вебхуками посредством post- и get-запросов. Сервер принимает запросы, приходящие на `1234` пост и, используя шаблон, генерирует страницу с внесенными вебхуками. При получении post-запроса (он отправляется при нажатии кнопок `Принять` или `Удалить`) сервер изменяет шаблон страницы, исходя из пришедшего запроса - удаляет вебхук или добавляет новый.

![](./pictures/webhooks.png)

*Рисунок 1. Страница с вебхуками*

#### Подготовка webhook для Алисы и регистрация навыка

1. Запускаем ngrok и по команде ngrok http 1234 получаем личную ссылку. Не закрываем ngrok до завершения работы с лабораторной.
2. Регистрируем и настраиваем навык на сервисе Яндекс.Диалоги, указываем ссылку из ngrok в подразделе Backend

![](./pictures/settings.png)

*Рисунок 2. Навык для Алисы*

Далее прописываем непосредственно функционал навыка, помогающего составить список покупок. Сервер должен отвечать на POST-запросы Алисы. Данный навык имеет два режима: режим помощи и основной режим. Режим помощи выводит ссылку о функционале навыка.

![](./pictures/help_mode.png)

*Рисунок 3. Демонстрация режима Помощь*

Основной режим изменяет содержимое корзины: добавляет/удаляет новые товары, выводит их список, рассчитывает общую сумму покупки и др.

![](./pictures/main_mode.png)

*Рисунок 4. Демонстрация работы основного режима*

Помимо этого доступна функция, отключающая озвучку реплик Алисы.

![](./pictures/voice.png)

*Рисунок 5. Демонстрация работы кнопок "Говорить"/"Молчать"*

<details>
<summary>Исходный код серверной части</summary>

```c++
#include <iostream>
#include <fstream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>;
using namespace std;
using namespace httplib;
using json = nlohmann::json;
ofstream logger("log.txt");                                         //создаем глобальный файловый поток

string webhook_template = u8R"(
    <div class="form-row align-items-center">
        <div class="col">
            <input type="how_to_write" value="{Webhook URL}" class="form-control mb-2" disabled>
        </div>
        <div class="col">
         <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
        </div>
    </div>)";
string w_url = "{Webhook URL}";
string w_list = "{webhooks_list}";
string config_file = "config.json";
json file;

//десериализация конфигурационного файла
json get_config() {
	ifstream config("config.json");
	string config_s;
	config >> config_s;
	if (!config or config_s.empty()) {
		logger << u8"Файл config.json невозможно открыть, либо он пуст. Будет создан пустой конфигурационный файл.\n";
		file["webhooks"] = json::array();
	}
	else {
		config >> file;
		logger << u8"Десериализация json прошла успешно.\n";
		config.close();
	}
	return file;
}

//запись/обновление информации получаемого json-а в config.json
void record_to_config(json file) {
	ofstream record("config.json");
	if (!record) {
		logger << u8"Не удалось открыть config.json.  \n";
	}
	else {
		logger << u8"Запись/обновление кофигурационного файла...\n";
		record << file.dump();
		logger << u8"Обновление файла окончено.\n";
		record.close();
	}
}

//создание шаблона страницы с вебхуками
string page() {
	string web_temp;
	ifstream page("webhooks.html");
	if (!page) {
		logger << u8"Не удалось открыть webhooks.html.\n";
		return "";
	}
	else {
		logger << u8"Считывание шаблона из webhooks.html.\n";            //считывание в строку web
		getline(page, web_temp, '\0');
		page.close();
	}

	string final_page;
	string part_of_page;
	int n = file["webhooks"].size();
	if (n == 0) {
		web_temp.replace(web_temp.find(w_list), w_list.size(), "");
	}
	else {
		for (int i = 0; i < n; i++) {
			part_of_page = webhook_template;
			part_of_page.replace(part_of_page.find(w_url), w_url.size(), file["webhooks"][i]);
			part_of_page.replace(part_of_page.find(w_url), w_url.size(), file["webhooks"][i]);
			final_page += part_of_page;
		}
		web_temp.replace(web_temp.find(w_list), w_list.size(), final_page);
	}
	return web_temp;
}


//вывод страницы с вебхуками
void get_webhooks(const Request& req, Response& res) {
	res.set_content(page(), "text/html; charset=UTF-8");
}

//работает при нажатии кнопок на странице
//обрабатывает вносимые изменения
void post_webhooks(const Request& req, Response& res) {
	if (req.has_param("del")) {
		string value = req.get_param_value("del");
		if (value != "") {
			logger << u8"Был получен новый параметр del\n";
			int n = file["webhooks"].size();
			for (int i = 0; i < n; i++) {
				if (file["webhooks"][i] == value) {
					file["webhooks"].erase(file["webhooks"].begin() + i);
					logger << u8"Вебхук был удалён.\n";
					break;
				}
			}
		}
		else {
			logger << u8"Поступил пустой запрос на удаление вебхука.\n";
		}
	}
	if (req.has_param("set")) {
		string value = req.get_param_value("set");
		if (value != "") {                                         //если пришла не пустая строка
			logger << u8"Был получен новый параметр set\n";
			if (!file["webhooks"].empty()) {                       //если в конфигурационном файле что-то уже есть
				bool exists = false;
				int n = file["webhooks"].size();
				for (int i = 0; i < n; i++) {
					if (file["webhooks"][i] == value) {
						exists = true;
						logger << u8"Добавляемый вебхук уже существует.\n";
						break;
					}
				}
				if (!exists) {
					file["webhooks"].push_back(value);
					logger << u8"Новый вебхук был добавлен.\n";
				}
			}
			else {
				file["webhooks"].push_back(value);
				logger << u8"Новый вебхук был добавлен.\n";
			}
		}
		else {
			logger << u8"Поступил пустой запрос на создание вебхука.\n";
		}
	}

	record_to_config(file);
	res.set_content(page(), "text/html; charset=UTF-8");
}

//начало работы с Алисой
//объявление режимов, основные кнопки и кнопки помощи
enum voice {
	on,
	off
};
enum skills {
	help_skill,
	exit_skill
};

json silence = {
	{"title", u8"Молчать"},
	{"hide", true}
};

json speaker = {
	{"title", u8"Говорить"},
	{"hide", true}
};

json help = {
	{
		{"title", u8"Помощь"},
		{"hide", true}
	}
};
json help_buttons = {
	{
		{"title", u8"Молчать"},
		{"hide", true}
	},
	{
		{"title", u8"Говорить"},
		{"hide", true}
	},
	{
		{"title", u8"Корзина"},
		{"hide", true}
	},
	{
		{"title", u8"Выход"},
		{"hide", true}
	}
};

//заполнение и возврат json-a с ответом на запрос 
json send_to_user(const string& text, const string& tts, const json& buttons, const json* new_session = nullptr, const bool end_session = false) {
	json data = {
		{"response",
		{
			{"buttons", buttons},
			{"end_session", end_session}
		}
		},
		{"version", "1.0"}
	};
	if (new_session != nullptr && (*new_session)["voice"] == on) {
		if (tts != "") {
			data["response"]["tts"] = tts;
		}
		data["response"]["buttons"].push_back(silence);
	}
	else if (new_session != nullptr && (*new_session)["voice"] == off) {
		data["response"]["buttons"].push_back(speaker);
	}
	if (text != "") {
		data["response"]["text"] = text;
	}

	return data;
}

json session_json = json::array();
void alice(const Request& req, Response& res)
{
	json request = json::parse(req.body);
	string user_id = request["session"]["application"]["application_id"];
	json* new_session = nullptr;
	string txt, tts;

	for (auto& session : session_json) {
		if (session["user_id"] == user_id) {
			new_session = &session;
			break;
		}
	}
	if (request["session"]["new"].get<bool>()) {
		if (new_session == nullptr) {		//если сессия новая, то 
			json session;
			session["user_id"] = user_id;		//считывается id пользователя
			session["skills"] = exit_skill;		//набор кнопок начальный
			session["voice"] = on;				//озвучка реплик включена
			session["check"] = json::array();

			session_json.push_back(session);
			new_session = &session_json[session_json.size() - 1];
		}
		else {
			(*new_session)["skills"] = exit_skill;
			(*new_session)["voice"] = on;
		}
		txt = u8"Здравствуйте! Я помогу вам с покупками";
		tts = u8"Здравствуйте! Я помогу вам с покупками";
		json res_file = send_to_user(txt, tts, help, new_session);
		res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		return;
	}
	if (new_session == nullptr) {
		txt = u8"Произошла ошибка, сессия окончена.";
		tts = u8"Произошла ошибка, сессия окончена.";
		json res_file = send_to_user(txt, tts, help, new_session);
		res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		return;
	}

	string com = request["request"]["command"];

	if ((*new_session)["skills"] == help_skill) {
		if (com == u8"молчать") {
			txt = u8R"(Данная команда отключает озвучку всех сообщений.
				       О чем ещё рассказать?)";
			tts = u8R"(Данная команда отключает озвучку всех сообщений.
				       О чем ещё рассказать?)";
		}
		else if (com == u8"говорить") {
			txt = u8R"(Данная команда подключает озвучку всех сообщений.
					   О чем ещё рассказать?)";
			tts = u8R"(Данная команда подключает озвучку всех сообщений.
				       О чем ещё рассказать?)";
		}
		else if (com == u8"корзина") {
			txt = u8R"(Возможность Корзина имеет несколько команд:
					   1. Очистить корзину - удаляет все содержимое вашей корзины.
                       2. Добавить в корзину - добавляет в корзину новый товар.
					      Для добавления используйте "Добавить в корзину <наименование, цена> рублей"
					   3. Удалить из корзины - удаляет один товар из вашей корзины.
						  Для удаления используйте "Удалить из корзины <наименование>"
					   4. Что в корзине - отображение полного списка ваших товаров.
					   5. Сумма - считает стоимость собранной вами корзины.
					   6. Покупка завершена - очищение корзины и сохранение полного списка в таблицу.
					   О чем рассказать ещё?)";
			tts = u8R"(Возможность Корзина имеет несколько команд:
					   1. Очистить корзину - удаляет все содержимое вашей корзины.
                       2. Добавить в корзину - добавляет в корзину новый товар.
					      Для добавления используйте "Добавить в корзину <наименование, цена> рублей"
					   3. Удалить из корзины - удаляет один товар из вашей корзины.
						  Для удаления используйте "Удалить из корзины <наименование>"
					   4. Что в корзине - отображение полного списка ваших товаров.
					   5. Сумма - считает стоимость собранной вами корзины.
					   6. Покупка завершена - очищение корзины и сохранение полного списка в таблицу.
					   О чем рассказать ещё?)";
		}
		else if (com == u8"выход") {
			txt = u8"Выход из режима помощи";
			tts = u8"Выход из режима помощи";
			(*new_session)["skills"] = exit_skill;
		}
		else {
			txt = u8"Неизвестная команда";
			tts = u8"Неизвестная команда";
		}
		json res_file;
		if ((*new_session)["skills"] == help_skill) {
			res_file = send_to_user(txt, tts, help_buttons, new_session);
		}
		else {
			res_file = send_to_user(txt, tts, help, new_session);
		}
		res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
	}
	else {
		if (com == u8"молчать") {
			txt = u8"Молчу, молчу";
			tts;
			(*new_session)["voice"] = off;
			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com == u8"говорить") {
			txt = u8"Хорошо";
			tts = u8"Хорошо";
			(*new_session)["voice"] = on;
			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com == u8"помощь") {
			txt = u8R"(Молчать - отключение озвучки реплик.
					 Говорить - включение озвучки реплик. 
					 Корзина - помощь в организации вашей покупки.
				     О чем рассказать подробнее?
					 Нажмите "Выход" для выхода из режима помощи.)";
			tts = u8R"(Молчать - отключение озвучки реплик.
					 Говорить - включение озвучки реплик. 
					 Корзина - помощь в организации вашей покупки.
				     О чем рассказать подробнее?
					 Нажмите "Выход" для выхода из режима помощи.)";
			json res_file = send_to_user(txt, tts, help_buttons, new_session);
			(*new_session)["skills"] = help_skill;
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}

		else if (com == u8"очистить корзину") {
			txt = u8"Корзина очищена";
			tts = u8"Корзина очищена";
			json res_file = send_to_user(txt, tts, help, new_session);
			(*new_session).erase("check");
			(*new_session)["check"] = json::array();
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com.find(u8"добавить в корзину") == 0) {
			size_t size = request["request"]["nlu"]["tokens"].size();
			txt = u8"ОК";
			tts = u8"ОК";
			string item_name;
			int item_price = 0, num_index = 0;
			bool set_price = false;

			for (auto ent : request["request"]["nlu"]["entities"]) {
				if (ent["type"].get<string>() == "YANDEX.NUMBER") {
					num_index = ent["tokens"]["start"];
					int val = ent["value"];
					if (val <= 0) {
						txt = u8"Цена не может быть отрицательной или равняться нулю";
						tts = u8"Цена не может быть отрицательной или равняться нулю";
					}
					else {
						item_price = val;
					}
					set_price = true;
					break;
				}
			}
			if (size == 3) {
				txt = u8"Что добавлять?";
				tts = u8"Что добавлять?";
			}
			else if (num_index == 3) {
				txt = u8"Укажите название товара";
				tts = u8"Укажите название товара";
			}
			else if (!set_price) {
				txt = u8"Укажите цену";
				tts = u8"Укажите цену";
			}
			else {
				for (int i = 3; i < num_index; ++i) {
					item_name += request["request"]["nlu"]["tokens"][i].get<string>();
					item_name += " ";
				}
				item_name.pop_back();
				json item = {
					{"item",  item_name},
					{"price", item_price}
				};
				(*new_session)["check"].push_back(item);
			}

			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com.find(u8"удалить из корзины") == 0) {
			size_t size = request["request"]["nlu"]["tokens"].size();
			string name = "";

			for (int i = 3; i < size; ++i) {
				name += request["request"]["nlu"]["tokens"][i].get<string>();
				name += " ";
			}
			bool found = false;
			int	item_index = 0;

			if (name == "") {
				txt = u8"Укажите название товара";
				tts = u8"Укажите название товара";
			}
			else {
				name.pop_back();
				for (auto& cart_item : (*new_session)["check"]) {
					if (cart_item["item"].get<string>() == name) {
						found = true;
						break;
					}
					++item_index;
				}
				if (!found) {
					txt = u8"Товар отсутствует в корзине";
					tts = u8"Товар отсутствует в корзине";
				}
				else {
					txt = u8"ОК";
					tts = u8"ОК";
					(*new_session)["check"].erase((*new_session)["check"].begin() + item_index);
				}
			}
			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com == u8"что в корзине") {
			if ((*new_session)["check"].empty()) {
				txt = u8"В корзине ничего нет";
				tts = u8"В корзине ничего нет";
			}
			else {
				txt = u8"Товары в корзине:";
				tts = u8"Товары в корзине:";
				for (auto& elem : (*new_session)["check"]) {
					int price = elem["price"].get<int>();

					txt += "\n"
						+ elem["item"].get<string>()
						+ u8" ценой "
						+ std::to_string(price);
					tts += "\n"
						+ elem["item"].get<string>()
						+ u8" ценой "
						+ std::to_string(price);

					if (price % 10 == 1) {
						txt += u8" рубль,";
						tts += u8" рубль,";
					}
					else if (price % 10 < 5 && price % 10 > 0) {
						txt += u8" рубля,";
						tts += u8" рубля,";
					}
					else {
						txt += u8" рублей,";
						tts += u8" рублей,";
					}
				}
				txt.pop_back();
				tts = txt;
			}

			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com == u8"сумма") {
			size_t size = request["request"]["nlu"]["tokens"].size();
			int sum = 0;
			for (auto& cart_item : (*new_session)["check"]) {
				sum += cart_item["price"].get<int>();
			}
			string str_sum = to_string(sum);
			txt = u8"В корзине товаров на " + str_sum;
			tts = u8"В корзине товаров на " + str_sum;

			if (sum % 10 == 1) {
				txt += u8" рубль";
				tts += u8" рубль";
			}
			else if (sum % 10 < 5 && sum % 10 > 0) {
				txt += u8" рубля";
				tts += u8" рубля";
			}
			else {
				txt += u8" рублей";
				tts += u8" рублей";
			}

			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else if (com == u8"покупка завершена") {
			txt = u8"Покупка завершена. Заходите ещё!";
			tts = u8"Покупка завершена. Заходите ещё!";
			json output, conf;
			output["user_id"] = user_id;
			output["check"] = (*new_session)["check"];
			conf = get_config();

			for (string link : conf["webhooks"])
			{
				int ind = link.find('/', static_cast<string>("https://").size());
				Client cli(link.substr(0, ind).c_str());
				cli.Post(link.substr(ind, -1).c_str(), output.dump(2), "application/json; charset=UTF-8");
			}

			(*new_session).erase("check");
			(*new_session)["check"] = json::array();

			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
		else {
			txt = u8"Неизвестная команда";
			tts = u8"Неизвестная команда";

			json res_file = send_to_user(txt, tts, help, new_session);
			res.set_content(res_file.dump(2), "text/json; charset=UTF-8");
		}
	}
}

int main()
{
	Server svr;                                 // Создаём сервер 
	svr.Get("/webhooks", get_webhooks);         //для работы с вх
	svr.Post("/webhooks", post_webhooks);
	svr.Post("/", alice);						//команды Алисы
	logger << u8"Сервер запущен по адресу http://localhost:1234/" << endl;
	svr.listen("localhost", 1234);
}
```
</details>
<br>


#### Создание клиентского приложения

Создаём клиентское приложение, которое будет запускаться и ждать post-запрос к роуту `/` `1234` поста. При получении запроса данные записываются в буфер. Когда количество записей в буфере превосходит 1000, данные сохраняются таблицу data.xlsx, а буфер очищается. Если файл уже существует, то данные отправляются в конец файла.

<details>
<summary>Исходный код клиента</summary>

```python
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
```
</details>
<br>

[Файл](./Client/data.xlsx) со списком покупок.

## Вывод

В ходе работы было получено представление о структуре post-запросов, а также изучен метод взаимодействия web-приложений через webhook-и.