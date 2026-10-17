#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#include <cpprest/http_client.h>
#include <cpprest/asyncrt_utils.h>
#include "call_api.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;
using namespace pplx;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    vector<task<http_response>> taskVector;
    for (const string& word : msg)
    {
        cout << word << " ";
        task<http_response> task = call_api();
        cout << task.is_done() << endl;
        taskVector.push_back(task);
    }

    for(const task<http_response>& response : taskVector) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        try {
            response.wait();
        } catch (...) {
        }
        cout << response.is_done() << endl;
        try {
            http_response resp = response.get();
            utility::string_t body = resp.extract_string().get();
            cout << format_status_and_body_length(resp.status_code(), body) << endl;
        } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << endl;
            continue;
        }
    }
    cout << endl;
}