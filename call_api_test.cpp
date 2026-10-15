#include <iostream>
#include <exception>
#include <string>
#include "call_api.h"

int test_invalid_url() {
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
}

int test_body_to_utf8_non_ascii() {
    utility::string_t non_ascii = U("caf\u00e9 \u65e5\u672c");
    std::string result = body_to_utf8(non_ascii);
    std::string expected = "caf\xc3\xa9 \xe6\x97\xa5\xe6\x9c\xac";

    if (result != expected) {
        std::cerr << "Test failed: body_to_utf8 did not produce expected UTF-8 bytes." << std::endl;
        std::cerr << "Expected: " << expected << " (" << expected.size() << " bytes)" << std::endl;
        std::cerr << "Actual:   " << result << " (" << result.size() << " bytes)" << std::endl;
        return 1;
    }

    std::cout << "Regression test passed: body_to_utf8 preserves non-ASCII characters as UTF-8." << std::endl;
    return 0;
}

int main() {
    try {
        if (test_invalid_url() != 0) {
            return 1;
        }
        if (test_body_to_utf8_non_ascii() != 0) {
            return 1;
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with unexpected exception: " << e.what() << std::endl;
        return 1;
    }
}
