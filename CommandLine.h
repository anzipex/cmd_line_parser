/** 
 * @file CommandLine.h
 * @brief CommandLine class reference
 * @author anzipex (anzipex@gmail.com)
 * @date August 4, 2017
 */

#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <fstream>
#include <vector>

class CommandLine {
public:
    /**
     * @brief Accepts command line parameters, opens the configuration file for reading
     * @param argc, number of parameters
     * @param argv, array of pointers to strings
     */
    CommandLine(int argc, char** argv);

    /**
     * @brief Closes the config
     */
    virtual ~CommandLine();

    /**
     * @brief Parsing config
     * @param argc, number of parameters
     * @param argv, array of pointers to strings
     * @param pathToConfig, path to config file
     */
    void parse(int argc, char** argv, const std::string& pathToConfig);

    /**
     * @brief Checks for the presence of a parameter with the full-name in the config file
     * @param fullName
     * @return the presence of an argument
     */
    bool isArgument(std::string fullName);

    /**
     * @brief Get the value type in int
     * @param fullName, string with full-name
     * @return value type in int
     */
    int getInt(std::string fullName);

    /**
     * @brief Get the value type in float
     * @param fullName, string with full-name
     * @return value type in float
     */
    float getFloat(std::string fullName);

    /**
     * @brief Get the value type in string
     * @param fullName, string with full-name
     * @return value type in string
     */
    std::string getString(std::string fullName);

    /**
     * @brief Get a list of all parameters from the command line
     * @return string of arguments
     */
    std::string list() const;

private:

    /**
     * @brief Checks if there is data in the structure from the command line
     */
    void checkDataContainerCmd() const;

    /**
     * @brief Checks whether there is data in the structure from the config
     */
    void checkDataContainerConfig() const;

    /**
     * @brief Structure with data from the config
     */
    struct ContainerConfig {
        std::string fullName; //!< full names from config
        std::string command; //!< argument names from the config
        std::string type; //!< value types from config
    };
    std::vector<ContainerConfig> _containerConfig; //!< vector of struct ContainerConfig

    /**
     * @brief The data structure, command line parameters
     */
    struct ContainerCmd {
        std::string command; //!< argument names from main
        std::string type; //!< value types from main
    };
    std::vector<ContainerCmd> _containerCmd; //!< vector of struct ContainerCmd

    /**
     * @brief Parsing the command line
     */
    void parseCmdLine();

    /**
     * @brief Defines what argument (command or parameter)
     * @param tempCmd, structure with data from the command line
     * @param _cmdArguments, vector of parameters from the command line
     * @param i, current item
     */
    void identifyArgument(ContainerCmd &tempCmd, std::vector<std::string> &_cmdArguments, int i);

    /**
     * @brief Opens the config
     * @param pathToConfig, path to config file
     */
    void openConfig(const std::string& pathToConfig);

    /**
     * @brief Closes the config
     */
    void closeConfig();

    /**
     * @brief Passing the structure of the full-name from the config for the function isArgument
     * @param fullName
     */
    void passFullNameIsArgument(std::string &fullName);

    /**
     * @brief Passing the structure of arguments from the config for the function isArgument
     * @param command, argument name
     */
    void passCommandIsArgument(std::string &command);

    /**
     * @brief Passage on the structure of types from the config for getString
     * @param fullName, full-name from config file
     */
    void passTypeGetString(std::string &fullName);

    /**
     * @brief Passing the structure of arguments from the config for getString
     * @param command, argument name
     */
    void passCommandGetString(std::string &command);

    bool _resultIsArgument; //!< the presence of an argument named fullName
    std::string _resultGetString; //!< received string with a type named fullName
    std::ifstream _file; //!< configuration file
    std::vector<std::string> _cmdArguments; //!< vector of parameters from the command line
};

#endif /* COMMANDLINE_H */
