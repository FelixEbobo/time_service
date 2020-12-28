#include <boost/format.hpp>
#include <string.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <map>


// Thu Jun  1 10:09:17 BST 2017 - Needed format
struct Time {

    ~Time() = default;
    Time() : timezone("UTC+00"){};
    
    void set_timezone(std::string new_timezone) {
        this->timezone = new_timezone;
    }

    std::string get_timezone() {
        return this->timezone;
    } 
    std::string get_time() {
        // Conversion from std::string to char*
        std::string tz = (boost::format("TZ=%s") % timezone).str();
        char* arr = new char[tz.length()];
        strcpy(arr, tz.c_str());
        putenv(arr);
        tzset();

        tm time_info{};
        auto cur_time = time(NULL);
        check_time(cur_time);     
        time_info = *localtime(&cur_time);

        char buffer[80];
        strftime(buffer, 80, "%a %b %e %T %Z %Y\n", &time_info);

        char IRK_TZ[] = "TZ=Asia/Irkutsk"; 
        putenv(IRK_TZ);
        tzset();
        return (std::string) buffer;
    }

    // std::string get_time_boost() {
    //     auto cur_time = time(NULL);
    //     auto time_info = localtime(&cur_time);
    //     boost::local_time::time_zone_ptr tz{boost::local_time::time_zone{}};
    //     boost::posix_time::time_duration td;
    //     auto pt = boost::posix_time::from_time_t(time(NULL));
    //     boost::local_time::local_date_time dt{pt, tz};
    //     std::cout << dt.local_time() << std::endl;
    // }
    
private:
    std::string timezone;

    void check_time(time_t& time_to_change) {
        auto time_iter = TIMEZONES.find(timezone);
        if (time_iter == TIMEZONES.end()) {
            return;
        }
        time_to_change += time_iter->second;
        return; 
    }
    // Hard-coded map 'cause for BST time change doesn't work
    std::map<std::string, int> TIMEZONES = {
        {"BST", 3600 * 1},
    };
};