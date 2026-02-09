// This is like importing ingredients for cooking
#include "crow_all.h"
#include <string>
#include <chrono>
#include <ctime>

int main()
{
    // Create a web server (like opening a restaurant)
    crow::SimpleApp app;

    // ENDPOINT 1: Health Check
    // When someone visits /health, tell them we're alive
    CROW_ROUTE(app, "/health")
    ([](){
        crow::json::wvalue response;
        response["status"] = "healthy";
        response["timestamp"] = std::time(nullptr);
        return response;
    });

    // ENDPOINT 2: Welcome Message
    // When someone visits /, greet them
    CROW_ROUTE(app, "/")
    ([](){
        crow::json::wvalue response;
        response["message"] = "Welcome to C++ Microservice";
        response["version"] = "1.0.0";
        return response;
    });

    // ENDPOINT 3: Personal Greeting
    // When someone visits /api/greet/John, say "Hello, John!"
    CROW_ROUTE(app, "/api/greet/<string>")
    ([](std::string name){
        crow::json::wvalue response;
        response["message"] = "Hello, " + name + "!";
        response["timestamp"] = std::time(nullptr);
        return response;
    });

    // ENDPOINT 4: Echo
    // Send data, and we'll send it back (like an echo)
    CROW_ROUTE(app, "/api/echo").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid JSON");
        
        crow::json::wvalue response;
        response["received"] = body;
        return crow::response(response);
    });

    // Start the restaurant on port 8080
    app.port(8080).multithreaded().run();
}