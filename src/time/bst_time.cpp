// Unused

#include <time.h>
#include <string>
#include "time.cpp"

struct BST : AbstractTime {
    BST() : timezone("BST"){};

    std::string get_time() override {
        auto cur_time = time(nullptr);
        return "Yes";
    }

    std::string get_timezone() override {
        return this->timezone;
    }
private:
    std::string timezone;
};