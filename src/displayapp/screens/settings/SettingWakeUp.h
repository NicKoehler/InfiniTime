#pragma once

#include <array>
#include <cstdint>
#include <lvgl/lvgl.h>
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingWakeUp : public Screen {
      public:
        SettingWakeUp(Pinetime::Controllers::Settings& settingsController);
        ~SettingWakeUp() override;

        void UpdateSelected(lv_obj_t* object);

      private:
        struct Option {
          Controllers::Settings::WakeUpMode wakeUpMode;
          const char* name;
        };

        Controllers::Settings& settingsController;
        static constexpr std::array<Option, 4> options = {{
          {Controllers::Settings::WakeUpMode::SingleTap, "Tocco singolo"},
          {Controllers::Settings::WakeUpMode::DoubleTap, "Tocco doppio"},
          {Controllers::Settings::WakeUpMode::RaiseWrist, "Solleva polso"},
          {Controllers::Settings::WakeUpMode::Shake, "Scuotimento"},
        }};

        lv_obj_t* cbOption[options.size()];
      };
    }
  }
}
