/*
 **
 ** Copyright 2024, The Android Open Source Project
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 **     http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 */

#pragma once

#include <android/hardware/keymaster/3.0/IKeymasterDevice.h>

typedef struct keymaster1_device keymaster1_device_t;
typedef struct keymaster2_device keymaster2_device_t;

namespace skeymaster {
namespace ng {
using ::android::hardware::keymaster::V3_0::IKeymasterDevice;
IKeymasterDevice* CreateSKeymasterDevice(keymaster2_device_t* km2_device);
IKeymasterDevice* CreateSKeymasterDevice(keymaster1_device_t* km1_device);
}  // namespace ng
}  // namespace keymaster
