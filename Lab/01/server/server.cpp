#include <iostream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using namespace httplib;
using json = nlohmann::json;

void gen_responce(const Request& req, Response& res) {
   
}
void gen_raw_responce(const Request& req, Response& res) {
}

int main() {
	Server weather;
	weather.Get("/", gen_responce);
	weather.Get("/raw", gen_raw_responce);
	weather.listen("localhost", 1234);
}

json getCurrentWeather() {
    json c_weath;

    Client get_weath("http://api.openweathermap.org");
    auto res = get_weath.Get("/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=daily,minutely,current&units=metric&lang=ru&appid=7c07aa2d844b83b4dc811d5a8663ac39");
    if (res) {
        if (res->status == 200) {
            c_weath = res->body;
            return c_weath;
        }
        else {
            cout << "Status code: " << res->status << endl;
        }
    }
    else {
        auto err = res.error();
        cout << "Error code: " << err << endl;
    }
}

json cache_weather(ifstream& ReadCache)
{
    json weather_file;
    weather_file = getCurrentWeather();
    ofstream write("cache.json");
    write << weather_file;
    return weather_file;
}

json getCurrentTime() {
    json time;
    Client get_time("http://worldtimeapi.org");
    auto res = get_time.Get("/api/timezone/Europe/Simferopol");
    if (res) {
        if (res->status == 200) {
            time = res->body;
            return time["unixtime"];
        }
        else {
            cout << "Status code: " << res->status << endl;
        }
    }
    else {
        auto err = res.error();
        cout << "Error code: " << err << endl;
    }
}

