#pragma once

#include <string>

class Updater
{
public:
    static bool checkForUpdates(const std::string &repo, std::string &latestVersion, const std::string &proxy = "", int retries = 3);
    static bool downloadUpdate(const std::string &url, const std::string &outputPath, const std::string &proxy = "", int retries = 3);
};
