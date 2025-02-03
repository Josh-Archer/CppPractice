#include <iostream>
#include <vector>
#include <string>
#include <windows.h>


#include <cpprest/http_client.h>
#include <cpprest/asyncrt_utils.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;
using namespace pplx;

task<http_response> call_api() {
    http_client client(U("https://www.google.com/"));
    task<http_response> task;
     try {
        // Make a GET request
        task = client.request(methods::GET);
        cout << "Making API Call..." << endl;
        //http_response response = task.get();

        // Print the status code
        //std::cout << "Status code: " << response.status_code() << std::endl;

        // Print the response body
        // std::cout << "Response body: " << response.extract_string().get() << std::endl;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return task;
}

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
        Sleep(1000);
        response.wait();
        cout << response.is_done() << endl;
        http_response resp = response.get();
        wstring body = resp.extract_string().get();
        cout << to_string(resp.status_code()).append(": ").append(string(body.begin(), body.end())) << endl;
    }
    cout << endl;
}