# Toggle: pass OLED=yes to compile in the OLED code (Luna animation +
# status panel, ~5 KB). Default is no — keeps the firmware slim and frees
# flash for the autocorrect dict.
#   qmk compile -kb crkbd/rev1 -km bytemouse -e OLED=yes
OLED ?= no
ifeq ($(OLED),yes)
  OLED_ENABLE      = yes
  OLED_DRIVER      = ssd1306
else
  OLED_ENABLE      = no
endif
EXTRAKEY_ENABLE    = yes
RGBLIGHT_ENABLE    = no
MOUSEKEY_ENABLE    = no
LTO_ENABLE         = yes

# Hold-tap improvements
CHORDAL_HOLD       = no
CAPS_WORD_ENABLE   = yes
RGB_MATRIX_ENABLE  = no
WPM_ENABLE         = yes
UNICODEMAP_ENABLE  = yes   # for ñ ¿ ¡ on the ESP layer
AUTOCORRECT_ENABLE = yes

# Space-saving: disable QMK defaults this keymap doesn't use.
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE   = no
MAGIC_ENABLE       = no
BOOTMAGIC_ENABLE   = no   # not used; QK_BOOT key handles flashing. ~480 B
