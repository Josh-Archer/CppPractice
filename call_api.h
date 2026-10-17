#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <algorithm>
#include <cctype>
#include <vector>

#include <cpprest/http_client.h>
#include <cpprest/asyncrt_utils.h>
#include <pplx/pplxtasks.h>

inline std::string body_to_utf8(const utility::string_t& body) {
    return utility::conversions::to_utf8string(body);
}

inline bool is_valid_http_url(const utility::string_t& url) {
    if (!web::uri::validate(url)) {
        return false;
    }

    const web::uri parsed_url(url);
    std::string scheme = utility::conversions::to_utf8string(parsed_url.scheme());
    std::transform(scheme.begin(), scheme.end(), scheme.begin(), [](unsigned char character) {
        return static_cast<char>(std::tolower(character));
    });
    return (scheme == "http" || scheme == "https") && !parsed_url.host().empty();
}

inline pplx::task<web::http::http_response> call_api(const utility::string_t& url) {
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

template <typename T>
inline void wait_for_all_tasks(const std::vector<pplx::task<T>>& tasks) {
    pplx::when_all(tasks.begin(), tasks.end()).wait();
}
