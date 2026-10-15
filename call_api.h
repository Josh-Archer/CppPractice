#pragma once

#include <iostream>
#include <string>
#include <exception>

#include <cpprest/http_client.h>
#include <cpprest/asyncrt_utils.h>
#include <pplx/pplxtasks.h>

inline pplx::task<web::http::http_response> call_api(const utility::string_t& url = U("https://www.google.com/")) {
    pplx::task<web::http::http_response> task;
    try {
        web::http::client::http_client client(url);
        // Make a GET request
        task = client.request(web::http::methods::GET);
        std::cout << "Making API Call..." << std::endl;
        //http_response response = task.get();

        // Print the status code
        //std::cout << "Status code: " << response.status_code() << std::endl;

        // Print the response body
        // std::cout << "Response body: " << response.extract_string().get() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return pplx::task_from_exception<web::http::http_response>(std::current_exception());
    }

    return task;
}
