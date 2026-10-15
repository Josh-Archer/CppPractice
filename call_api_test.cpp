#include <iostream>
#include <exception>
#include "call_api.h"

int main() {
    try {
        // A request to an invalid URL yields a scheduled task without needing network
        auto task = call_api(U("not a valid uri"));

        if (!task.is_done()) {
            std::cerr << "Test failed: task was expected to be completed immediately." << std::endl;
            return 1;
        }

        bool exception_thrown = false;
        try {
            task.get();
        } catch (const std::exception& e) {
            exception_thrown = true;
            std::cout << "Caught expected exception from task.get(): " << e.what() << std::endl;
        }

        if (!exception_thrown) {
            std::cerr << "Test failed: task.get() did not throw an exception." << std::endl;
            return 1;
        }

        std::cout << "Regression test passed: invalid URL yields a task whose get() throws." << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with unexpected exception outside task.get(): " << e.what() << std::endl;
        return 1;
    }
}
