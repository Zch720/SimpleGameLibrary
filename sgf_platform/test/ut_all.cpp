#include <gtest/gtest.h>
#include <string>
#include <regex>

#include "test_env.h"
#include "platform_context_test.h"
#include "window_test.h"

struct Arg {
    std::string key;
    std::string value;
};

Arg parseArg(char *);
void handleArg(Arg);

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++) {
        handleArg(parseArg(argv[i]));
    }
    return RUN_ALL_TESTS();
}

Arg parseArg(char * arg) {
    std::string argStr(arg);
    std::regex reg("--([a-zA-Z]+)=(.+)");
    std::smatch result;

    if (std::regex_match(argStr, result, reg)) {
        if (result.size() == 3) return { .key = result[1], .value = result[2] };
    }
    return { "", "" };
}

void handleArg(Arg arg) {
    if (arg.key == "" || arg.value == "") return;

    if (arg.key == "skipHandTest") {
        if (arg.value == "true") {
            skipHandTest = true;
        } else {
            skipHandTest = false;
        }
    }
}
