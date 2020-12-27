#include <iostream>
#include <fstream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>;
#include "replace.h"
using namespace std;
using namespace httplib;
using json = nlohmann::json;
ofstream logger("log.txt"); //создаем глобальный файловый поток

string html_template = "wh_template.html";
string html_page = "wh_page.html";
string config_file = "config.json";
json file;

//десериализация конфигурационного файла
json get_config() {
    ifstream config("config.json"); //чтение из config.json
    if (!config) {
        logger << u8"Не удалось открыть файл.\nБудет создан пустой конфигурационный файл.\n\n";
        file["webhooks"] = json::array();
    }
    else {
        config >> file;
        logger << u8"Десериализация json прошла успешно.\n\n";
        config.close();
    }
    return file;
}

//обновление конфигурационного файла
void record_to_config(json file) {
    ofstream record("config.json");
    if (!record) {
        logger << u8"Не удалось открыть config.json.  \n\n";
    }
    else {
        logger << u8"Обновление кофигурационного файла...\n";
        record << file.dump(4);// переписываем в строку с опред. кол-вом пробелов
        logger << u8"Обновление завершено.\n\n";
        record.close();
    }
}

string gen_page() {
    string web;
    ifstream page(html_page);
    if (!page) {
        logger << u8"Не удалось открыть wh_page.html.\n";
        return ""; 
    }
    else {
        logger << u8"Считываем данные из wh_page.html.\n";
        getline(page, web, '\0');
        page.close();
    }
    string whooks;
    if (file["webhooks"].empty()){
        logger << u8"Файл пуст.\n";
        file = get_config();
    }
    else {
        int n = file["webhooks"].size();
        for (int i = 0; i < n; i++) {
            replace(html_template, "{Webhook URL}", file["webhooks"][i].get<string>());
            whooks += html_template;
        }
    }
    replace(web, "{webhooks_list}", whooks);
    return web;
}

void get_webhooks(const Request& req, Response& res){
    res.set_content(gen_page(), "text/html; charset=UTF-8");
}

void post_webhooks(const Request& req, Response& res) {
    if (req.has_param("del")){
        string v = req.get_param_value("del");
        if (v != "")
        {
            logger << u8"Был получен новый параметр del\n";
            for (auto count = file["webhooks"].begin(); count != file["webhooks"].end(); ++count){
                if (count->is_string() && count->get<string>() == v) {
                    logger << u8"Вебхук был удалён.\n\n";
                    file["webhooks"].erase(count);
                    break;
                }
            }
        }
        else
        {
            logger << u8"Поступил пустой запрос на удаление вебхука.\n\n";
        }
    }
    if (req.has_param("set")){
        string v = req.get_param_value("set");
        if (v != "") {
            logger << u8"<Был получен новый параметр set\n";
            if (!file["webhooks"].empty()) {
                bool webhook_exist = false;
                for (auto count = file["webhooks"].begin(); count != file["webhooks"].end(); ++count) {
                    if (count->is_string() && count->get<string>() == v) {
                        webhook_exist = true;
                        break;
                    }
                }
                if (!webhook_exist) {
                    file["webhooks"].push_back(v);
                }
                logger << u8"Новый вебхук был добавлен (уже существовал).\n\n";
            }
            else {
                file["webhooks"].push_back(v);
                logger << u8"Новый вебхук был добавлен .\n\n";
            }
        }
        else {
            logger << u8"Поступил пустой запрос на создание вебхука.\n\n";
        }
    }
}


int main()
{
    Server svr;                             // Создаём сервер 
    svr.Get("/webhooks", get_webhooks);         //для работы с вх
    svr.Post("/webhooks", post_webhooks);    
    logger << u8"Сервер запущен по адресу http://localhost:1234/"<<endl;
    cout << "Start server... OK\n"; // cout использовать нельзя
    svr.listen("localhost", 1234);
}

