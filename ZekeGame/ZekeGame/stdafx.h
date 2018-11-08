#pragma once

#define  MRT_MAX  8

#include "Game/PythonBridge/include/Python.h"

#include <WinSock2.h>
#include <ws2def.h>

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>

#include "Engine/PreCompile.h"

const float FRAME_BUFFER_W = 1280.0f;				
const float FRAME_BUFFER_H = 720.0f;				
static const int MAX_BONE = 512;
//int MRT_MAX = 8;		//!<MRT‚ÌÅ‘å”B
