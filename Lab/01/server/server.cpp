#include <iostream>
#include <fstream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using json = nlohmann::json;

int hour;
bool relevance = false;
//запрос текущей погоды с сайта и возврат json-a с этой погодой
string getCurrentWeather() {
    string s_weather;
    Client GetWeather("http://api.openweathermap.org");
    auto res = GetWeather.Get("/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=daily,minutely,current&units=metric&lang=ru&appid=7c07aa2d844b83b4dc811d5a8663ac39");
    if (!res) {
        cout << "Can't get weather info.\n";
    }
    else {
        s_weather = res->body;
        cout << "Weather info was recieved.\n";
    }
    return s_weather;
}

//запрос точного текущего времени и возврат текущего часа
string getCurrentTime() {
    string s_time;
    Client GetTime("http://worldtimeapi.org");
    auto res = GetTime.Get("/api/timezone/Europe/Simferopol");
    if (res->status == 200) {
        s_time = res->body;
        cout << "Time was recieved.\n";
    } 
    else {
        cout << "Can't get time.\n";
    }
    return s_time;
}

json j_weather, j_time;
string widget_template;
//обработка запроса на '/'
void gen_responce(const Request& req, Response& res) {
    if (j_weather.empty()) {
        j_weather = json::parse(getCurrentWeather());
    }
    j_time = json::parse(getCurrentTime());
    for (int i = 0; i < 48; i++) {
        if (j_time["unixtime"] < j_weather["hourly"][i]["dt"]) {
            hour = i;
            break;
        }
    }

    if (j_time["unixtime"] < j_weather["hourly"][hour]["dt"]){ //значит в кэше есть этот час
        string temp1 = "{hourly[i].weather[0].description}";
        string temp2 = "{hourly[i].weather[0].icon}";
        string temp3 = "{hourly[i].temp}";
        
        string description = j_weather["hourly"][0]["weather"][0]["description"];
        string icon = j_weather["hourly"][0]["weather"][0]["icon"];
        double temp_value = j_weather["hourly"][hour]["temp"];
        string str_temp_value = to_string(int(round(temp_value)));

        ifstream t_file("template_file.html");
        if (t_file.is_open()) {
            getline(t_file, widget_template, '\0');
        }
        else {
            cout << "Can`t open template.\n";
        }

        widget_template.replace(widget_template.find(temp1), temp1.length(), description);
        widget_template.replace(widget_template.find(temp2), temp2.length(), icon);
        widget_template.replace(widget_template.find(temp3), temp3.length(), str_temp_value);
        widget_template.replace(widget_template.find(temp3), temp3.length(), str_temp_value);
        cout << "Widget strings have been updated.\n"
            << widget_template << endl;
        
    }
    else {
        j_weather = json::parse(getCurrentWeather());

        string temp1 = "{hourly[i].weather[0].description}";
        string temp2 = "{hourly[i].weather[0].icon}";
        string temp3 = "{hourly[i].temp}";

        string description = j_weather["hourly"][0]["weather"][0]["description"];
        string icon = j_weather["hourly"][0]["weather"][0]["icon"];
        double temp_value = j_weather["hourly"][hour]["temp"];
        string str_temp_value = to_string(int(round(temp_value)));

        ifstream t_file("template_file.html");
        if (t_file.is_open()) {
            getline(t_file, widget_template, '\0');
        }
        else {
            cout << "Can`t open template.\n";
        }

        widget_template.replace(widget_template.find(temp1), temp1.length(), description);
        widget_template.replace(widget_template.find(temp2), temp2.length(), icon);
        widget_template.replace(widget_template.find(temp3), temp3.length(), str_temp_value);
        widget_template.replace(widget_template.find(temp3), temp3.length(), str_temp_value);
        cout << "Widget strings have been updated.\n"
            << widget_template << endl;
    }
    res.set_content(widget_template, "text/html");
}

json raw;
//обработка запроса на '/raw'
void gen_raw_responce(const Request& req, Response& res) {
    if (j_weather.empty()) {
        j_weather = json::parse(getCurrentWeather());
    }
    j_time = json::parse(getCurrentTime());
    for (int i = 0; i < 48; i++) {
        if (j_time["unixtime"] < j_weather["hourly"][i]["dt"]) {
            hour = i;
            break;
        }
    }

    if (j_time["unixtime"] < j_weather["hourly"][hour]["dt"]) { //значит в кэше есть этот час
        double temp_value = j_weather["hourly"][hour]["temp"];
        int int_temp_value = round(temp_value);
        string description = j_weather["hourly"][hour]["weather"][0]["description"];
        raw["temp"] = int_temp_value;
        raw["description"] = description;
        cout <<"Raw strings have been updated.\n"<< raw.dump(4) << endl;
    }
    else {
        j_weather = json::parse(getCurrentWeather());
        double temp_value = j_weather["hourly"][hour]["temp"];
        int int_temp_value = round(temp_value);
        string description = j_weather["hourly"][hour]["weather"][0]["description"];
        raw["temp"] = int_temp_value;
        raw["description"] = description;
        cout << "Raw strings have been updated.\n" << raw.dump(4) << endl;
    }
    res.set_content(raw.dump(), "text/json");
}

//запуск сервера
int main() {
    Server weather;
    weather.Get("/", gen_responce);
    weather.Get("/raw", gen_raw_responce);
    cout << "Start server...OK\n";
    weather.listen("localhost", 3000);
}

