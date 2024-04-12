#pragma once

#include <iostream>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#endif
#include <gtest/gtest.h>

#define ASSERT_THROW_MESSAGE(code, expected_exception, expected_message)                \
    try {                                                                               \
        { code; }                                                                       \
        FAIL() << "Except throw exception." << std::endl;                               \
    } catch (const expected_exception &e) {                                             \
        EXPECT_EQ(std::string(e.what()), expected_message);                             \
    } catch (const std::exception &e) {                                                 \
        FAIL() << "Get exception with unexpected message:" << e.what() << std::endl;    \
    } catch (...) {                                                                     \
        FAIL() << "Get unknow exception" << std::endl;                                  \
    }

#define PRINTF(...) { printf("             "); printf("\033[0;33m"); printf(__VA_ARGS__); printf("\033[0;37m"); }

#ifndef _WIN32
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
#endif

void EndOfGetKey() {
    fflush(stdin);
    printf("\n");
}

void CheckSuccess(bool success, std::string message) {
    if (success) {
        SUCCEED();
    } else {
        FAIL() << message;
    }
}

void SuccessCheckFromInput(std::string message) {
    char c = 0;
    while (c != 's' && c != 'f') {
#ifdef _WIN32
        if (_kbhit()) c = _getch();
#else
        if (_kbhit()) c = getchar();
#endif
    }

    EndOfGetKey();
    CheckSuccess(c == 's', message);
}

bool SuccessCheckFromInputForLoop(std::string message) {
    char c = 0;
#ifdef _WIN32
    if (_kbhit()) c = _getch();
#else
    if (_kbhit()) c = getchar();
#endif
    if (c == 's' || c == 'f') {
        EndOfGetKey();
        CheckSuccess(c == 's', message);
        return true;
    }
    return false;
}