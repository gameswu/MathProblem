#include "file.h"

#include <fstream>

File::File(std::vector<Problem *> problems, std::string fileName, int numProblems, bool needAnswer, int fileFormat)
{
    this->problems = problems;
    this->fileName = fileName;
    this->numProblems = numProblems;
    this->needAnswer = needAnswer;
    this->fileFormat = fileFormat;
}

void File::generateFile()
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        return;
    }
    for (int i = 0; i < numProblems; i++)
    {
        file << problems[i]->getProblem();
        if (needAnswer)
        {
            file << problems[i]->getAnswer();
        }
        if (this->fileFormat == 1)
        {
            file << " \\\\" << std::endl;
        }
        else
        {
            file << std::endl;
        }
    }
    file.close();
}