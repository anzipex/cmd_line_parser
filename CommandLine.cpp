/** 
 * @file CommandLine.cpp
 * @brief Implementing the CommandLine class
 * @author anzipex (anzipex@gmail.com)
 * @date August 4, 2017
 */

#include <iostream>
#include "CommandLine.h"

CommandLine::CommandLine(int argc, char** argv) :
_resultIsArgument(false),
_resultGetString(),
_file(nullptr),
_cmdArguments() {
    for (int i = 1; i < argc; ++i) {
        _cmdArguments.push_back(argv[i]);
    }
    parseCmdLine();
    checkDataContainerCmd();
}

CommandLine::~CommandLine() {
    closeConfig();
}

void CommandLine::closeConfig() {
    _file.close();
}

void CommandLine::checkDataContainerCmd() {
    if (_containerCmd.empty()) {
        std::cout << "command line is empty, program closed" << std::endl;
        exit(1);
    }
}

void CommandLine::checkDataContainerConfig() {
    if (_containerConfig.empty()) {
        std::cout << "config is empty, program closed" << std::endl;
        exit(1);
    }
}

void CommandLine::openConfig(const std::string& pathToConfig) {
    _file.open(pathToConfig);
    if (!_file.good()) {
        std::cerr << "unable to open config, or file not found" << std::endl;
    }
}

void CommandLine::identifyArgument(ContainerCmd &tempCmd,
                                   std::vector<std::string> &_cmdArguments, int i) {
    std::string str = _cmdArguments[i];
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
    for (int i = 0; i < _cmdArguments.size(); ++i) {
        identifyArgument(tempCmd, _cmdArguments, i);
    }
    _containerCmd.push_back(tempCmd);
}

void CommandLine::parse(int argc, char** argv, const std::string& pathToConfig) {
    openConfig(pathToConfig);
    ContainerConfig configEntry;
    while (_file >> configEntry.fullName >> configEntry.command >> configEntry.type) {
        _containerConfig.push_back(configEntry);
    }
    checkDataContainerConfig();
}

bool CommandLine::isArgument(std::string fullName) {
    _resultIsArgument = false;
    passFullNameIsArgument(fullName);
    return _resultIsArgument;
}

void CommandLine::passFullNameIsArgument(std::string fullName) {
    ContainerConfig tempConfig;
    for (int i = 0; i < _containerConfig.size(); ++i) {
        tempConfig = _containerConfig[i];
        if (tempConfig.fullName == fullName) {
            std::string command = tempConfig.command;
            passCommandIsArgument(command);
        }
    }
}

void CommandLine::passCommandIsArgument(std::string command) {
    ContainerCmd tempCmd;
    for (int i = 0; i < _containerCmd.size(); ++i) {
        tempCmd = _containerCmd[i];
        if (tempCmd.command == command) {
            _resultIsArgument = true;
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
    _resultGetString = "no such fullName in config file";
    passTypeGetString(fullName);
    return _resultGetString;
}

void CommandLine::passTypeGetString(std::string fullName) {
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

void CommandLine::passCommandGetString(std::string command) {
    ContainerCmd tempCmd;
    for (int i = 0; i < _containerCmd.size(); ++i) {
        tempCmd = _containerCmd[i];
        if (tempCmd.command == command) {
            _resultGetString = tempCmd.type;
            break;
        }
    }
}

std::string CommandLine::list() {
    std::string str;
    for (int i = 0; i < _cmdArguments.size(); ++i) {
        str += _cmdArguments[i] + " ";
    }
    return str;
}