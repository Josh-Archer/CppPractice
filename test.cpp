#include <iostream>
#include <vector>
#include <string>

#include <cpprest/http_client.h>
#include <cpprest/asyncrt_utils.h>
#include "call_api.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;
using namespace pplx;

int main(int argc, char* argv[])
{
    const string usage = string("Usage: ") + argv[0] + " <request-url>";
    if (argc != 2) {
        cerr << usage << endl;
        return 1;
    }

    const utility::string_t url = utility::conversions::to_string_t(argv[1]);
    if (!is_valid_http_url(url)) {
        cerr << "Invalid request URL." << endl << usage << endl;
        return 1;
    }

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    vector<task<http_response>> taskVector;
    for (const string& word : msg)
    {
        cout << word << " ";
        task<http_response> task = call_api(url);
        cout << task.is_done() << endl;
        taskVector.push_back(task);
    }

    try {
        wait_for_all_tasks(taskVector);
    } catch (...) {
        // Individual failures are reported while retrieving each response below.
    }
    for(const task<http_response>& response : taskVector) {
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
