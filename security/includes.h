#pragma once

/* normal includes */
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <random>

/* cryptopp */
#include <cryptopp/dll.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

/* VMProtect SDK */
#include <VMProtectSDK.h>
#define main_function "main"
#define checksum_function "checksum"
#define menu_function "menu"
#define login_function "login"
#define menu_A "menuA"
#define inject_A "injectA"
#define rename_filename "filename_function"

/* Windows */
#define NOMINMAX
#define _WINSOCKAPI_
#include <Windows.h>
#include <Winternl.h>

#include <WinInet.h>
#pragma comment(lib,"WinInet.lib")

/* Project includes */
#include "hardware.h"
#include "../app/app.h"
#include "../app/json/json.hpp"
#include "../app/menu/menu.h"