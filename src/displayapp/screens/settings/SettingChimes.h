#pragma once

#include <cstdint>
#include <lvgl/lvgl.h>
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"
#include <array>

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingChimes : public Screen {
      public:
        SettingChimes(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~SettingChimes() override;

        void UpdateSelected(lv_obj_t* object, lv_event_t event);

      private:
        struct Option {
          Controllers::Settings::ChimesOption chimesOption;
          const char* name;
        };
        static constexpr std::array<Option, 3> options = {{{Controllers::Settings::ChimesOption::None, " Spento"},
                                                           {Controllers::Settings::ChimesOption::Hours, " Ogni ora"},
                                                           {Controllers::Settings::ChimesOption::HalfHours, " Ogni 30\n minuti"}}};

        std::array<lv_obj_t*, options.size()> cbOption;

        Controllers::Settings& settingsController;
      };
    }
  }
}
