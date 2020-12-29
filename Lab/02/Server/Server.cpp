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


void yandex_alice(const Request& req, Response& res) {

}

int main()
{
    Server svr;                                 // Создаём сервер 
    svr.Get("/webhooks", get_webhooks);         //для работы с вх
    svr.Post("/webhooks", post_webhooks);
    svr.Post("/alice", yandex_alice);
    logger << u8"Сервер запущен по адресу http://localhost:1234/" << endl;
    svr.listen("localhost", 1234);
}


