#include <gtest/gtest.h>
#include "../src/time/time.cpp"

char UTC_TZ[] = "TZ=UTC"; 

struct Container {
    Container(std::string ns1, std::string ns2)
        : s1(ns1), s2(ns2){};

    std::string s1;
    std::string s2;
};

Container get_time_in_zone(size_t hours_to_add, 
                      std::string timezone_to_set,
                      std::string timezone) {
    Time time_machine;
    time_machine.set_timezone(timezone);
    auto test_string = time_machine.get_time();

    putenv(UTC_TZ);
    tzset();

    tm time_info{};
    auto cur_time = time(NULL);
    cur_time += 3600 * hours_to_add;
    time_info = *localtime(&cur_time);
    time_info.tm_zone = timezone_to_set.c_str();

    char buffer[80];
    strftime(buffer, 80, "%a %b %e %T %Z %Y\n", 
             &time_info);
    
    Container return_strings{test_string, 
                             (std::string) buffer};

    return return_strings;
}

TEST(time_test, BST_time) {
    auto strings = get_time_in_zone(1, "BST", "BST");    

    EXPECT_STREQ(
        strings.s1.c_str(),
        strings.s2.c_str()
    );
}

TEST(time_test, Tokyo_time) {
    auto strings = get_time_in_zone(9, "JST", "Asia/Tokyo");

    EXPECT_STREQ(
        strings.s1.c_str(),
        strings.s2.c_str()
    );
}

TEST(time_test, Moscow_time) {
    auto strings = get_time_in_zone(3, "MSK", "Europe/Moscow");

    EXPECT_STREQ(
        strings.s1.c_str(),
        strings.s2.c_str()
    );
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}