/** 
 * @file main.cpp
 * @brief CommandLineParserTest
 * @author anzipex (anzipex@gmail.com)
 * @date August 23, 2017
 */

#include <iostream>
#include "CommandLine.h"

int main(int argc, char** argv) {
    CommandLine cmd(argc, argv);
    std::string pathToConfig = "test.cfg";
    cmd.parse(argc, argv, pathToConfig);
    std::cout << cmd.isArgument("drawborder") << std::endl;
    std::cout << cmd.getString("ipaddress") << std::endl;
    std::cout << cmd.getInt("pnsnumber") << std::endl;
    std::cout << cmd.getFloat("gravity") << std::endl;
    std::cout << cmd.list() << std::endl;
}