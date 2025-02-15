#include "update.h"
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <cstdlib>

bool Updater::checkForUpdates(const std::string &repo, std::string &latestVersion)
{
    std::string command = "curl -s https://api.github.com/repos/" + repo + "/releases/latest";
    std::string result;
    char buffer[128];
    FILE *pipe = _popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Failed to run curl command." << std::endl;
        return false;
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    _pclose(pipe);

    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errs;

    std::istringstream s(result);
    if (!Json::parseFromStream(readerBuilder, s, &root, &errs))
    {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return false;
    }

    latestVersion = root["tag_name"].asString();
    return true;
}

bool Updater::downloadUpdate(const std::string &url, const std::string &outputPath)
{
    std::string command = "curl -L " + url + " -o " + outputPath;
    int result = std::system(command.c_str());
    return result == 0;
}
