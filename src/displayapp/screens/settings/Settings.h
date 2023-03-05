#pragma once

#include <array>
#include <memory>
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/ScreenList.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/screens/List.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class Settings : public Screen {
      public:
        Settings(DisplayApp* app, Pinetime::Controllers::Settings& settingsController);
        ~Settings() override;

        bool OnTouchEvent(Pinetime::Applications::TouchEvents event) override;

      private:
        DisplayApp* app;
        auto CreateScreenList() const;
        std::unique_ptr<Screen> CreateScreen(unsigned int screenNum) const;

        Controllers::Settings& settingsController;

        static constexpr int entriesPerScreen = 4;

        // Increment this when more space is needed
        static constexpr int nScreens = 3;

        static constexpr std::array<List::Applications, entriesPerScreen * nScreens> entries {{
          {Symbols::sun, "Schermo", Apps::SettingDisplay},
          {Symbols::eye, "Risveglio", Apps::SettingWakeUp},
          {Symbols::clock, "Formato ora", Apps::SettingTimeFormat},
          {Symbols::home, "Watch face", Apps::SettingWatchFace},

          {Symbols::shoe, "Passi", Apps::SettingSteps},
          {Symbols::clock, "Imposta data", Apps::SettingSetDate},
          {Symbols::clock, "Imposta ora", Apps::SettingSetTime},
          {Symbols::batteryHalf, "Batteria", Apps::BatteryInfo},

          {Symbols::clock, "Rintocchi", Apps::SettingChimes},
          {Symbols::tachometer, "Cal. Scuoti", Apps::SettingShakeThreshold},
          {Symbols::check, "Firmware", Apps::FirmwareValidation},
          {Symbols::bluetooth, "Bluetooth", Apps::SettingBluetooth},

          {Symbols::list, "Informazioni", Apps::SysInfo},

          // {Symbols::none, "None", Apps::None},
          // {Symbols::none, "None", Apps::None},
          // {Symbols::none, "None", Apps::None},
          // {Symbols::none, "None", Apps::None},
        }};
        ScreenList<nScreens> screens;
      };
    }
  }
}
