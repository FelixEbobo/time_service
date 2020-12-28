#include <iostream>
#include <ctime>

#include <boost/asio.hpp>

#include "server/server.cpp"

int main(int argc, char* argv[]) {
    init_log_filename();

    try {
        if (argc != 2) {
            std::cerr << "Usage: time_service <port>\n";
            return 1;
        }
        printf("Starting server...\n");

        boost::asio::io_context io_context;

        Server s(io_context, std::atoi(argv[1]));

        printf("Server started\n");
        printf("Log file for this start>%s\n", log_filename);
        printf("You can input timezone ABBR like EST or location like Asia/Tokyo");
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}