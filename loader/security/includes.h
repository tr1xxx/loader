#pragma once

/* normal includes */
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <random>

/* cryptopp */
#include <cryptopp/dll.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

/* VMProtect SDK */
#include <VMProtectSDK.h>

/* Driver Mapper Include */
#include "../kdmapper/kdmapper.hpp"

/* Windows */
#include <Windows.h>
#include <Winternl.h>

#include <WinInet.h>
#pragma comment(lib,"WinInet.lib")

/* Project includes */
#include "hardware.h"
#include "../app/app.h"
#include "../app/json/json.hpp"
#include "../app/menu/menu.h"