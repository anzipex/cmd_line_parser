#include <iostream>
#include "CommandLine.h"

CommandLine::CommandLine(int argc, char** argv) :
resultIsArgument_(false),
resultGetString_(),
file_(nullptr),
cmdArguments_() {
    for (int i = 1; i < argc; ++i) {
        cmdArguments_.push_back(argv[i]);
    }
    parseCmdLine();
    checkDataContainerCmd();
}

CommandLine::~CommandLine() {
    closeConfig();
}

void CommandLine::closeConfig() {
    file_.close();
}

void CommandLine::checkDataContainerCmd() const {
    if (_containerCmd.empty()) {
        std::cout << "command line is empty, program closed" << std::endl;
        exit(1);
    }
}

void CommandLine::checkDataContainerConfig() const {
    if (_containerConfig.empty()) {
        std::cout << "config is empty, program closed" << std::endl;
        exit(1);
    }
}

void CommandLine::openConfig(const std::string& pathToConfig) {
    file_.open(pathToConfig);
    if (!file_.good()) {
        std::cerr << "unable to open config, or file not found" << std::endl;
    }
}

void CommandLine::identifyArgument(ContainerCmd &tempCmd,
                                   std::vector<std::string> &cmdArguments_, int i) {
    std::string str = cmdArguments_[i];
    if (str[0] == '-') {
        if (i > 0) {
            _containerCmd.push_back(tempCmd);
            tempCmd = ContainerCmd();
        }
        tempCmd.command = str;
    } else {
        tempCmd.type = str;
    }
}

void CommandLine::parseCmdLine() {
    ContainerCmd tempCmd;
    for (int i = 0; i < cmdArguments_.size(); ++i) {
        identifyArgument(tempCmd, cmdArguments_, i);
    }
    _containerCmd.push_back(tempCmd);
}

void CommandLine::parse(int argc, char** argv, const std::string& pathToConfig) {
    openConfig(pathToConfig);
    ContainerConfig configEntry;
    while (file_ >> configEntry.fullName >> configEntry.command >> configEntry.type) {
        _containerConfig.push_back(configEntry);
    }
    checkDataContainerConfig();
}

bool CommandLine::isArgument(std::string fullName) {
    resultIsArgument_ = false;
    passFullNameIsArgument(fullName);
    return resultIsArgument_;
}

void CommandLine::passFullNameIsArgument(std::string &fullName) {
    ContainerConfig tempConfig;
    for (int i = 0; i < _containerConfig.size(); ++i) {
        tempConfig = _containerConfig[i];
        if (tempConfig.fullName == fullName) {
            std::string command = tempConfig.command;
            passCommandIsArgument(command);
        }
    }
}

void CommandLine::passCommandIsArgument(std::string &command) {
    ContainerCmd tempCmd;
    for (int i = 0; i < _containerCmd.size(); ++i) {
        tempCmd = _containerCmd[i];
        if (tempCmd.command == command) {
            resultIsArgument_ = true;
            break;
        }
    }
}

int CommandLine::getInt(std::string fullName) {
    if (!isArgument(fullName)) {
        return 0;
    }
    std::string value = getString(fullName);
    if (isdigit(value[0])) {
        return std::stoi(value);
    } else {
        return 0;
    }
}

float CommandLine::getFloat(std::string fullName) {
    if (!isArgument(fullName)) {
        return 0;
    }
    std::string value = getString(fullName);
    if (isdigit(value[0])) {
        return std::stof(value);
    } else {
        return 0;
    }
}

std::string CommandLine::getString(std::string fullName) {
    resultGetString_ = "no such fullName in config file";
    passTypeGetString(fullName);
    return resultGetString_;
}

void CommandLine::passTypeGetString(std::string &fullName) {
    ContainerCmd tempCmd;
    ContainerConfig tempConfig;
    for (int i = 0; i < _containerConfig.size(); ++i) {
        tempConfig = _containerConfig[i];
        if (tempConfig.fullName == fullName) {
            std::string command = tempConfig.command;
            passCommandGetString(command);
        }
    }
}

void CommandLine::passCommandGetString(std::string &command) {
    ContainerCmd tempCmd;
    for (int i = 0; i < _containerCmd.size(); ++i) {
        tempCmd = _containerCmd[i];
        if (tempCmd.command == command) {
            resultGetString_ = tempCmd.type;
            break;
        }
    }
}

std::string CommandLine::list() const {
    std::string str;
    for (int i = 0; i < cmdArguments_.size(); ++i) {
        str += cmdArguments_[i] + " ";
    }
    return str;
}
