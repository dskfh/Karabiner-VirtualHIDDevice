// -*- Mode: c++ -*-

#pragma once

// Do not use <cstring> for kext
#include <stdint.h>
#include <string.h>

namespace pqrs {
class karabiner_virtualhiddevice {
public:
  class hid_report final {
  public:
    class __attribute__((packed)) keyboard_input final {
    public:
      keyboard_input(void) : modifiers(0), reserved(0), keys{} {}
      bool operator==(const hid_report::keyboard_input& other) const { return (memcmp(this, &other, sizeof(*this)) == 0); }
      bool operator!=(const hid_report::keyboard_input& other) const { return !(*this == other); }

      uint8_t modifiers;
      uint8_t reserved;
      uint8_t keys[6];
    };

    class __attribute__((packed)) pointing_input final {
    public:
      pointing_input(void)
          : buttons{}, x(0), y(0), vertical_wheel(0), horizontal_wheel(0) {}

      uint8_t buttons[4]; // 32 bits for each button (32 buttons)
      uint8_t x;
      uint8_t y;
      uint8_t vertical_wheel;
      uint8_t horizontal_wheel;

      // buttons[0] = (0x1 << 0) -> button 1
      // buttons[0] = (0x1 << 1) -> button 2
      // buttons[0] = (0x1 << 2) -> button 3
      // ...
      // buttons[1] = (0x1 << 0) -> button 9
      // ...
      // buttons[2] = (0x1 << 0) -> button 17
      // ...
      // buttons[3] = (0x1 << 0) -> button 25
    };
  };

  enum class user_client_method {
    initialize_virtual_hid_keyboard,
    initialize_virtual_hid_pointing,
    terminate_virtual_hid_keyboard,
    terminate_virtual_hid_pointing,
    post_keyboard_input_report,
    post_pointing_input_report,
    end_,
  };

  static const char* get_virtual_hid_manager_name(void) {
    return "org_pqrs_driver_VirtualHIDManager_v020200";
  }
};
}
