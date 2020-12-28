#include <cstdlib>
#include <iostream>

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include "session.cpp"

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port)
        : io_context_(io_context),
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
            Session* new_session = new Session(io_context_);
            acceptor_.async_accept(new_session->socket(),
                boost::bind(&Server::handle_accept, this, new_session,
                    boost::asio::placeholders::error));
        }

    void handle_accept(Session* new_session,
            const boost::system::error_code& error) {
        if (!error) {
            new_session->start();
            new_session = new Session(io_context_);
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&Server::handle_accept, this, new_session,
                        boost::asio::placeholders::error));
            // std::cout << new_session->get_session_id() << std::endl;
        } else {
            delete new_session;
        }
    }

private:
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};