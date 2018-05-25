/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2018, The LineageOS Project. All rights reserved.

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

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

#include "init_msm8974.h"

using android::base::GetProperty;
using android::init::property_set;

void gsm_properties()
{
    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");
}

void h3g_properties()
{
    property_set("ro.telephony.default_network", "3");
    property_set("telephony.lteOnGsmDevice", "0");
}

#define ISMATCH(a, b) (!strncmp((a), (b), PROP_VALUE_MAX))

void init_target_properties()
{
    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("N9006") == 0) {
        /* h3gzn - China Unicom 3G */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/h3gzn/h3g:5.0/LRX21V/N9006ZNSGQD1:user/release-keys");
        property_override("ro.build.description", "h3gzn-user 5.0 LRX21V N9006ZNSGQD1 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N9006");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "h3gzn");
        h3g_properties();
    } else if (bootloader.find("N9008") == 0) {
        /* h3gzm - China Mobile 3G */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/h3gzm/h3g:5.0/LRX21V/N9008ZMSGQB1:user/release-keys");
        property_override("ro.build.description", "h3gzm-user 5.0 LRX21V N9008ZMSGQB1 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N9008");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "h3gzm");
        h3g_properties();
    } else if (bootloader.find("N9008V") == 0) {
        /* hltezm - China Mobile LTE*/
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/hltezm/hlte:5.0/LRX21V/N9008VZMSDQD2:user/release-keys");
        property_override("ro.build.description", "hltezm-user 5.0 LRX21V N9008VZMSDQD2 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N9008V");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "hltezm");
        gsm_properties();
    } else if (bootloader.find("N9008S") == 0) {
        /* hltezc - China LTE */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/hltezc/hlte:5.0/LRX21V/N9008SZCSCQD1:user/release-keys");
        property_override("ro.build.description", "hltezc-user 5.0 LRX21V N9008SZCSCQD1 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N9008S");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "hltezc");
        gsm_properties();
    } else {
        gsm_properties();
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}
