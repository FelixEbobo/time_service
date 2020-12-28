#include <cstdlib>
#include <iostream>
#include <ctime>

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "../time/time.cpp"
#include "../logging/logger.cpp"

using boost::asio::ip::tcp;

class Session {
public:
    Session(boost::asio::io_context& io_context) 
            : socket_(tcp::socket(io_context)) {
        // Throws bad file descriptor (?)
        // id_ = socket_.remote_endpoint().address().to_string();
        
        auto cur_t = time(nullptr);
        auto cur_tm = localtime(&cur_t);
        char buffer[80];
        strftime(buffer, 80, "%Y_%d_%m_%T", cur_tm);
        std::string tmp(buffer);
        id_ = tmp;
    }

    tcp::socket& socket() {
        return socket_;
    }

    void start() {
        id_ = socket_.remote_endpoint().address().to_string();
        write_log_to_file(str(boost::format("for %s socket created\n")
                                        % id_.c_str()));
        boost::asio::async_read_until(socket_,
            boost::asio::dynamic_buffer(message), "\r\n",
            boost::bind(&Session::handler_read, this,
                boost::asio::placeholders::error));
    }

    void handler_read(const boost::system::error_code& error) {

        std::string edit_str(message.c_str());
        if (edit_str.length() == 0) {
            return;
        }
        edit_str.replace(edit_str.find("\r\n"), 64, "");
        time_machine.set_timezone((std::string) edit_str);
        message = time_machine.get_time();


        if (!error) {
            boost::asio::async_write(socket_,
            boost::asio::buffer(message.c_str(), message.length()),
            boost::bind(&Session::handler_close_socket, this,
                boost::asio::placeholders::error));
        } else {
            delete this;
        }
        write_log_to_file(str(boost::format("for %s return %s")
                                        % id_.c_str() 
                                        % message.c_str()));
    }

    void handler_close_socket(const boost::system::error_code& error) {
        write_log_to_file(str(boost::format("for %s connection closed\n")
                                        % id_.c_str()));
        socket_.close();
        delete this;
        return;
    }

    std::string get_session_id() {
        return id_;
    }

private:
    Time time_machine;
    std::string id_;
    tcp::socket socket_;

    std::string message;
    enum { max_length = 64 };
    char data_[max_length];

};