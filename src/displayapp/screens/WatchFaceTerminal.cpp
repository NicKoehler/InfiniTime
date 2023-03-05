#include <lvgl/lvgl.h>
#include "displayapp/screens/WatchFaceTerminal.h"
#include "displayapp/screens/BatteryIcon.h"
#include "displayapp/screens/NotificationIcon.h"
#include "displayapp/screens/Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/ble/NotificationManager.h"
#include "components/heartrate/HeartRateController.h"
#include "components/motion/MotionController.h"
#include "components/settings/Settings.h"

using namespace Pinetime::Applications::Screens;

WatchFaceTerminal::WatchFaceTerminal(Controllers::DateTime& dateTimeController,
                                     const Controllers::Battery& batteryController,
                                     const Controllers::Ble& bleController,
                                     Controllers::NotificationManager& notificationManager,
                                     Controllers::Settings& settingsController,
                                     Controllers::HeartRateController& heartRateController,
                                     Controllers::MotionController& motionController)
  : currentDateTime {{}},
    dateTimeController {dateTimeController},
    batteryController {batteryController},
    bleController {bleController},
    notificationManager {notificationManager},
    settingsController {settingsController},
    heartRateController {heartRateController},
    motionController {motionController} {
  batteryValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_recolor(batteryValue, true);
  lv_obj_align(batteryValue, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, -60);

  connectState = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_recolor(connectState, true);
  lv_obj_align(connectState, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 40);

  notificationIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_align(notificationIcon, nullptr, LV_ALIGN_IN_LEFT_MID, 0, -100);

  label_date = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_recolor(label_date, true);
  lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, -20);

  label_prompt_1 = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_align(label_prompt_1, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, -80);
  lv_label_set_text_static(label_prompt_1, "nic@watch:~ > now");

  label_prompt_2 = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_align(label_prompt_2, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 60);
  lv_label_set_text_static(label_prompt_2, "nic@watch:~ >");

  label_time = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_recolor(label_time, true);
  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, -40);

  heartbeatValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_recolor(heartbeatValue, true);
  lv_obj_align(heartbeatValue, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 20);

  stepValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_recolor(stepValue, true);
  lv_obj_align(stepValue, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 0);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

WatchFaceTerminal::~WatchFaceTerminal() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void WatchFaceTerminal::Refresh() {
  powerPresent = batteryController.IsPowerPresent();
  batteryPercentRemaining = batteryController.PercentRemaining();
  if (batteryPercentRemaining.IsUpdated() || powerPresent.IsUpdated()) {
    lv_label_set_text_fmt(batteryValue, "BATT > #a6da95 %d%%", batteryPercentRemaining.Get());
    if (batteryController.IsPowerPresent()) {
      lv_label_ins_text(batteryValue, LV_LABEL_POS_LAST, " in carica");
    }
  }

  bleState = bleController.IsConnected();
  bleRadioEnabled = bleController.IsRadioEnabled();
  if (bleState.IsUpdated() || bleRadioEnabled.IsUpdated()) {
    if (!bleRadioEnabled.Get()) {
      lv_label_set_text_static(connectState, "STAT > #f0c6c6 Disabilitato#");
    } else {
      if (bleState.Get()) {
        lv_label_set_text_static(connectState, "STAT > #f0c6c6 Connesso#");
      } else {
        lv_label_set_text_static(connectState, "STAT > #f0c6c6 Disconnesso#");
      }
    }
  }

  notificationState = notificationManager.AreNewNotificationsAvailable();
  if (notificationState.IsUpdated()) {
    if (notificationState.Get()) {
      lv_label_set_text_static(notificationIcon, "Hai una notifica.");
    } else {
      lv_label_set_text_static(notificationIcon, "");
    }
  }

  currentDateTime = dateTimeController.CurrentDateTime();

  if (currentDateTime.IsUpdated()) {
    auto hour = dateTimeController.Hours();
    auto minute = dateTimeController.Minutes();
    auto second = dateTimeController.Seconds();
    auto year = dateTimeController.Year();
    auto month = dateTimeController.Month();
    auto dayOfWeek = dateTimeController.DayOfWeek();
    auto day = dateTimeController.Day();

    if (displayedHour != hour || displayedMinute != minute || displayedSecond != second) {
      displayedHour = hour;
      displayedMinute = minute;
      displayedSecond = second;

      if (settingsController.GetClockType() == Controllers::Settings::ClockType::H12) {
        char ampmChar[3] = "AM";
        if (hour == 0) {
          hour = 12;
        } else if (hour == 12) {
          ampmChar[0] = 'P';
        } else if (hour > 12) {
          hour = hour - 12;
          ampmChar[0] = 'P';
        }
        lv_label_set_text_fmt(label_time, "ORAR > #cba6f7 %02d:%02d:%02d %s#", hour, minute, second, ampmChar);
      } else {
        lv_label_set_text_fmt(label_time, "ORAR > #cba6f7 %02d:%02d:%02d", hour, minute, second);
      }
    }

    if ((year != currentYear) || (month != currentMonth) || (dayOfWeek != currentDayOfWeek) || (day != currentDay)) {
      lv_label_set_text_fmt(label_date, "DATA > #fab387 %02d/%02d/%04d#", char(day), char(month), short(year));

      currentYear = year;
      currentMonth = month;
      currentDayOfWeek = dayOfWeek;
      currentDay = day;
    }
  }

  heartbeat = heartRateController.HeartRate();
  heartbeatRunning = heartRateController.State() != Controllers::HeartRateController::States::Stopped;
  if (heartbeat.IsUpdated() || heartbeatRunning.IsUpdated()) {
    if (heartbeatRunning.Get()) {
      lv_label_set_text_fmt(heartbeatValue, "CUOR > #ed8796 %d bpm#", heartbeat.Get());
    } else {
      lv_label_set_text_static(heartbeatValue, "CUOR > #ed8796 ---#");
    }
  }

  stepCount = motionController.NbSteps();
  motionSensorOk = motionController.IsSensorOk();
  if (stepCount.IsUpdated() || motionSensorOk.IsUpdated()) {
    lv_label_set_text_fmt(stepValue, "PASS > #8aadf4 %lu passi#", stepCount.Get());
  }
}
