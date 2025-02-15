#include "update.h"
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <cstdlib>

bool Updater::checkForUpdates(const std::string &repo, std::string &latestVersion, const std::string &proxy, int retries)
{
    std::string command = "curl -s https://api.github.com/repos/" + repo + "/releases/latest";
    if (!proxy.empty())
    {
        command += " --proxy " + proxy;
    }

    std::string result;
    char buffer[128];
    int attempt = 0;

    while (attempt < retries)
    {
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

        if (!result.empty())
        {
            break;
        }

        attempt++;
    }

    if (result.empty())
    {
        std::cerr << "Failed to fetch update information after " << retries << " attempts." << std::endl;
        return false;
    }

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

bool Updater::downloadUpdate(const std::string &url, const std::string &outputPath, const std::string &proxy, int retries)
{
    std::string command = "curl -L " + url + " -o " + outputPath;
    if (!proxy.empty())
    {
        command += " --proxy " + proxy;
    }

    int attempt = 0;
    int result = 0;

    while (attempt < retries)
    {
        result = std::system(command.c_str());
        if (result == 0)
        {
            break;
        }

        attempt++;
    }

    if (result != 0)
    {
        std::cerr << "Failed to download update after " << retries << " attempts." << std::endl;
    }

    return result == 0;
}
