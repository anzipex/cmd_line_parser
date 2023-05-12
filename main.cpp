#include <iostream>
#include <string>
#include "command_line.h"

using namespace std;

int main(int argc, char** argv) {
    CommandLine cmd(argc, argv);
    cmd.parse(argc, argv, "example.cfg");

    cout << cmd.isArgument("drawborder") << endl;
    cout << cmd.getString("ipaddress") << endl;
    cout << cmd.getInt("pnsnumber") << endl;
    cout << cmd.getFloat("gravity") << endl;
    cout << cmd.list() << endl;
}
