#pragma once

#include <lvgl/lvgl.h>

namespace Colors {
  static constexpr lv_color_t deepOrange = LV_COLOR_MAKE(0xff, 0x40, 0x0);
  static constexpr lv_color_t orange = LV_COLOR_MAKE(0xff, 0xb0, 0x0);
  static constexpr lv_color_t green = LV_COLOR_MAKE(0x0, 0xb0, 0x0);
  static constexpr lv_color_t lightGray = LV_COLOR_MAKE(0xb0, 0xb0, 0xb0);
  static constexpr lv_color_t mauve = LV_COLOR_MAKE(0xcb, 0xa6, 0xf7);
  static constexpr lv_color_t blue = LV_COLOR_MAKE(0x89, 0xb4, 0xfa);
  static constexpr lv_color_t yellow = LV_COLOR_MAKE(0xf9, 0xe2, 0xaf);
  static constexpr lv_color_t peace = LV_COLOR_MAKE(0xfa, 0xb3, 0x87);
  static constexpr lv_color_t red = LV_COLOR_MAKE(0xf3, 0x8b, 0xa8);
  static constexpr lv_color_t violet = LV_COLOR_MAKE(0x85, 0x60, 0xbb);

  static constexpr lv_color_t bg = LV_COLOR_MAKE(0x5d, 0x69, 0x7e);
  static constexpr lv_color_t bgAlt = LV_COLOR_MAKE(0x29, 0x20, 0x31);
  static constexpr lv_color_t bgDark = LV_COLOR_MAKE(0x18, 0x18, 0x18);
  static constexpr lv_color_t highlight = violet;
};

/**
 * Initialize the default
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param flags ORed flags starting with `LV_THEME_DEF_FLAG_...`
 * @param font_small pointer to a small font
 * @param font_normal pointer to a normal font
 * @param font_subtitle pointer to a large font
 * @param font_title pointer to a extra large font
 * @return a pointer to reference this theme later
 */
lv_theme_t* lv_pinetime_theme_init();
