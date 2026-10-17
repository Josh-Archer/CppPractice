#pragma once

#include <iostream>
#include <string>
#include <exception>

#include <cpprest/http_client.h>
#include <cpprest/asyncrt_utils.h>
#include <pplx/pplxtasks.h>

inline std::string body_to_utf8(const utility::string_t& body) {
    return utility::conversions::to_utf8string(body);
}

// Status code and UTF-8 body length only. string_t is wstring on Windows and
// string on Linux, so body.size() is not a portable length of the bytes that
// would otherwise be written.
inline std::string format_status_and_body_length(web::http::status_code status,
                                                  const utility::string_t& body) {
    return std::to_string(status) + ": " + std::to_string(body_to_utf8(body).size());
}

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
        // std::cout << "Response body: " << body_to_utf8(response.extract_string().get()) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return pplx::task_from_exception<web::http::http_response>(std::current_exception());
    }

    return task;
}
