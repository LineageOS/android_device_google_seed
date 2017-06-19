/*
   Copyright (c) 2017, The LineageOS Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <fstream>
#include <string>
#include <sys/sysinfo.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm8916.h"

char const *heapstartsize;
char const *heapgrowthlimit;
char const *heapsize;
char const *heapminfree;

void check_device()
{
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram > 1024ull * 1024 * 1024) {
        // from - phone-xhdpi-2048-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heapminfree = "512k";
    } else {
        // from - phone-xhdpi-1024-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "96m";
        heapsize = "256m";
        heapminfree = "2m";
    }
}

void init_target_properties()
{
    check_device();

    property_set("dalvik.vm.heapstartsize", heapstartsize);
    property_set("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_set("dalvik.vm.heapsize", heapsize);
    property_set("dalvik.vm.heaptargetutilization", "0.75");
    property_set("dalvik.vm.heapminfree", heapminfree);
    property_set("dalvik.vm.heapmaxfree", "8m");

    std::string device = property_get("ro.product.device");

    if (device == "ctih220_sprout") {
        property_set("ro.build.fingerprint", "google/ctih220/ctih220_sprout:7.1.1/N4F26W/3815918:user/release-keys");
    } else if (device == "imobileiq2_sprout") {
        property_set("ro.build.fingerprint", "google/imobileiq2/imobileiq2_sprout:7.1.1/N4F26W/3815918:user/release-keys");
    } else if (device == "gm4g_sprout") {
        property_set("ro.build.fingerprint", "google/gm4g/gm4g_sprout:7.1.1/N4F26W/3815918:user/release-keys");
    } else if (device == "gm4g_s_sprout") {
        property_set("ro.build.fingerprint", "google/gm4g_s/gm4g_s_sprout:7.1.1/N4F26W/3815918:user/release-keys");
    }

    property_set("ro.build.description", "seed_l8150-user 7.1.1 N4F26W 3815918 release-keys");
}
