//
// Created by Aaryan Gulia on 02/02/2024.
//
#include "iostream"
#define ASIO_STANDALONE
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

std::vector<char> vBuffer(1 * 1024);
void GrabSomeData(asio::ip::tcp::socket& socket){
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
    [&](std::error_code ec, std::size_t length){
        if(!ec){
            std::cout << "\n\nRead " << length << " bytes\n\n" << std::endl;
            for(int i = 0; i < length; i++){
                std::cout << vBuffer[i];
            }
            GrabSomeData(socket);
        }
    });
}

//int main() {
//    asio::error_code ec;
//    asio::io_context context;
//    asio::io_context::work idleWork(context);
//    std::thread theContext = std::thread([&](){context.run();});
//
//    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.36", ec), 80);
//    asio::ip::tcp::socket socket(context);
//    socket.connect(endpoint, ec);
//
//    if (!ec) {
//        std::cout << "Connected!" << std::endl;
//    } else {
//        std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
//    }
//    if(socket.is_open()){
//        std::string request = "GET /index.html HTTP/1.1\r\n"
//                              "Host: example.com\r\n"
//                              "Connection: close\r\n\r\n";
//        socket.write_some(asio::buffer(request.data(), request.size()), ec);
//        GrabSomeData(socket);
//        socket.wait(socket.wait_read);
//
//    }
//    return 0;
//}