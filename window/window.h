#pragma once

#include <atomic>

void createWindow();
void windowMessageLoop();

extern std::atomic_bool done;