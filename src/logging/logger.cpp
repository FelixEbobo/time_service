#include <cstdio>
#include <string>
#include <string.h>
#include <fstream>

#include <ctime>

static char log_filename[32];

void init_log_filename() {
    auto cur_time = time(NULL);
    auto f_name = asctime(localtime(&cur_time));
    strcat(log_filename, "logs/");
    strcat(log_filename, f_name);
    for (size_t i = 0; i < 24; i++) {
        if (log_filename[i] == ' ') {
            log_filename[i] = '_';
        }
    }
    log_filename[29] = '.';
    strcat(log_filename, "log");
}

auto get_current_time_short() {
    auto cur_time = time(NULL);
    auto time_tm = localtime(&cur_time);
    char return_time[30];
    strftime(return_time, 30, "%D %R", time_tm);
    return (std::string) return_time;
}

// sample, not for actual logging!
void write_log_to_file() {
    std::ofstream file_out;
    file_out.open(log_filename, std::ofstream::app);
    file_out << "Log " << get_current_time_short() << ": Sample text\n" ;
    file_out.close();
}
void write_log_to_file(std::string string_to_write) {
    std::ofstream file_out;
    file_out.open(log_filename, std::ofstream::app);
    file_out << "Log " << get_current_time_short() << ": " << string_to_write;
    file_out.close();
}