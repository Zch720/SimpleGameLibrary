#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/sgf/utils/logger/log.h"

class LoggerSuite: public testing::Test {
protected:
    void SetUp() override {
        deleteConsoleOutputFile();
        deleteFileOutputFile();
    }

    void TearDown() override {
        recoverStdout();
        deleteConsoleOutputFile();
        deleteFileOutputFile();
    }

    void replaceStdout() {
        originOutput = dup(fileno(stdout));
        (void)!freopen("./logger_temp.txt", "w", stdout);
    }

    void recoverStdout() {
        dup2(originOutput, fileno(stdout));
    }

    void loadConsoleOutput() {
        loadFile("./logger_temp.txt");
    }

    void loadFileOutput() {
        loadFile(PROJECT_DIR"/logs/log.txt");
    }

    void deleteConsoleOutputFile() {
        std::remove("./logger_temp.txt");
    }

    void deleteFileOutputFile() {
        std::remove(PROJECT_DIR"/logs/log.txt");
    }

    std::string getLine() {
        std::string line;
        std::getline(fileContent, line);
        return removeTime(line);
    }

private:
    std::string removeTime(const std::string & line) const {
        if (line.size() < 26) return "";
        return line.substr(26);
    }

    void loadFile(const std::string & path) {
        std::ifstream file(path);
        fileContent.clear();
        if (file) {
            fileContent << file.rdbuf();
        }
        file.close();
    }

    int originOutput;
    std::stringstream fileContent;
};

TEST_F(LoggerSuite, LogInfo) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_INFO);
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[info] This is an info message", getLine());
}

TEST_F(LoggerSuite, LogWarn) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_WARN);
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[warning] This is a warning message", getLine());
}

TEST_F(LoggerSuite, LogError) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_ERROR);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
}

TEST_F(LoggerSuite, LogDebug) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_DEBUG);
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[debug] This is a debug message", getLine());
}

TEST_F(LoggerSuite, LevelNoneShouldLogNothing) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_NONE);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, LevelErrorIsFirstLevel) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_ERROR);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, LevelWarnIsSecondLevel) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_WARN);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, LevelInfoIsThirdLevel) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_INFO);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("[info] This is an info message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, LevelDebugIsLastLevel) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_DEBUG);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();
    loadConsoleOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("[info] This is an info message", getLine());
    ASSERT_EQ("[debug] This is a debug message", getLine());
    ASSERT_EQ("", getLine());
}


TEST_F(LoggerSuite, FileLogInfo) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_INFO);
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[info] This is an info message", getLine());
}

TEST_F(LoggerSuite, FileLogWarn) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_WARN);
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[warning] This is a warning message", getLine());
}

TEST_F(LoggerSuite, FileLogError) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_ERROR);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
}

TEST_F(LoggerSuite, FileLogDebug) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_DEBUG);
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[debug] This is a debug message", getLine());
}

TEST_F(LoggerSuite, FileLevelNoneShouldLogNothing) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_NONE);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, FileLevelErrorIsFirstLevel) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_ERROR);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, FileLevelWarnIsSecondLevel) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_WARN);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, FileLevelInfoIsThirdLevel) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_INFO);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("[info] This is an info message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, FileLevelDebugIsLastLevel) {
    SGF_LOG_INIT();
    SGF_LOG_FILE(SGF_LOG_LEVEL_DEBUG);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    loadFileOutput();

    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("[info] This is an info message", getLine());
    ASSERT_EQ("[debug] This is a debug message", getLine());
    ASSERT_EQ("", getLine());
}

TEST_F(LoggerSuite, ConsoleAndFileSetToDifferentLevel) {
    replaceStdout();

    SGF_LOG_INIT();
    SGF_LOG_CONSOLE(SGF_LOG_LEVEL_WARN);
    SGF_LOG_FILE(SGF_LOG_LEVEL_INFO);
    SGF_LOG_ERROR("This is an error message");
    SGF_LOG_WARN("This is a warning message");
    SGF_LOG_INFO("This is an info message");
    SGF_LOG_DEBUG("This is a debug message");
    SGF_LOG_DROP();

    recoverStdout();

    loadConsoleOutput();
    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("", getLine());

    loadFileOutput();
    ASSERT_EQ("[error] This is an error message", getLine());
    ASSERT_EQ("[warning] This is a warning message", getLine());
    ASSERT_EQ("[info] This is an info message", getLine());
    ASSERT_EQ("", getLine());
}
