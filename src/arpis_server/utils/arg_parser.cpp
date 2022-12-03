#include "arpis_server/utils/arg_parser.hpp"
#include "rclcpp/rclcpp.hpp"

namespace arpis_server::utils {

int ArgParser::parse_mode(std::string mode) {
    int id;
    if (mode == (std::string) "sdk")
        id = 1;
    else if (mode == (std::string) "dummy")
        id = 2;
    else if (mode == (std::string) "cm740")
        id = 3;
    else
    {
        RCLCPP_ERROR(rclcpp::get_logger("arpis_server"), "invalid id, please specify use SDK, Dummy, or CM740");
        exit(0);
    }
    return id;
}

const char *ArgParser::get_addr(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (argv[i] == (std::string)"--addr")
            return (const char*)argv[i+1];
    } 
    return (const char*)"127.0.0.1"; // default addr
}

int ArgParser::get_port(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (argv[i] == (std::string)"--port")
            return (int)atoi(argv[i+1]);
    } 
    return 3000; // default port
}

}