#include <iostream>
#include "crow.h" // "crow_all.h"
#include <nlohmann/json.hpp>

// using json = nlohmann::json;
using crow::json::rvalue;
using crow::json::wvalue;

int main()
{
    crow::App app;

    // json j = json::parse(R"({"happy": true, "pi": 3.141})");

    //  GET(select)، POST (insert)، PUT (update)، PATCH و DELETE (delete)
    CROW_ROUTE(app, "/")([](){
        wvalue json = { {"hello", 1}, 
                        {"world", 2},
                        {"list", wvalue::list({1, 2, 3})}
                    };
        return json;

    });

// GET: 404 Not Found or 400 Bad Request :
    CROW_ROUTE(app, "/users")
    .methods("GET"_method)
    ([](crow::request& req, crow::response& res)
    {
        if (req.method == "GET"_method) {
            // list of all users
        }        
        res.end();
    });

    CROW_ROUTE(app, "/users/<int>")
    .methods("GET"_method, crow::HTTPMethod::PUT, crow::HTTPMethod::PATCH, crow::HTTPMethod::DELETE)
    ([](crow::request& req, crow::response& res, int id)
    {
        if (req.method == "GET"_method) {
            // select the user
        }
        if (req.method == "PATCH"_method) {
            /*
            {
                mail": "new.email@example.com"
            }
                این درخواست فقط ایمیل کاربر با شناسه ۱۲۳ را 
                به‌روزرسانی می‌کند و بقیه داده‌های کاربر را بدون تغییر می‌گذارد
            */
        }
        if (req.method == "PUT"_method) {
            /*
            {
                "name": "Anne",
                "email": "gfg@example.com"
            }
                این درخواست کاربر با شناسه ۱۲۳ را به‌روزرسانی می‌کند 
                یا اگر وجود نداشته باشد، کاربر جدیدی ایجاد می‌کند.
            */
        }
        if (req.method == "DELETE"_method) {
            // DELETE: 200 OK
            /*
            این درخواست کاربر با شناسه ۱۲۳ را حذف می‌کند.
            */
        }
        
        res.end();
    });

    CROW_ROUTE(app, "/users")
    .methods("POST"_method) ([]()
    {
        // POST:  201 Created را با هدر Location که به منبع جدید اشاره دارد، برمی‌گرداند.
        /*
        POST /users
        {
        "name": "Anne",
        "email": "gfg@example.com"
        }
        
        این درخواست یک کاربر جدید با داده‌های داده شده ایجاد می‌کند.
        */
    });



   


    auto feature = app.port(18080).multithreaded().run_async();
    /*
        app.bindaddr("192.168.1.2").port(443).ssl_file("certfile.crt","keyfile.key").multithreaded().run_async();
        
        app.route_dynamic(url);
        ارزیابی در زمان اجرا (Runtime) - کندی برنامه و خطر کرش با آدرس های غلط:
        به شما اجازه می‌دهد آدرس‌ها را به صورت پویا در زمان اجرای برنامه
        (مثلاً خواندن آدرس‌ها از یک فایل تنظیمات یا پایگاه داده) تعریف کنید.
    */
}
