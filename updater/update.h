#pragma once

#include <string>

class Updater
{
public:
    static bool checkForUpdates(const std::string &repo, std::string &latestVersion);
    static bool downloadUpdate(const std::string &url, const std::string &outputPath);
};
