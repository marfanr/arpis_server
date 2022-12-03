#ifndef ARG_PARSER_HPP_
#define ARG_PARSER_HPP_

#include <string>

namespace arpis_server::utils {

class ArgParser {
public:
    static int parse_mode(std::string mode);
    static const char *get_addr(int argc, char **argv);
    static int get_port(int argc, char **argv);
protected:
private:
};

}

#endif