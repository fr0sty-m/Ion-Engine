#pragma once

typedef enum WindowStyle {
  FULLSCREEN = 0x00000001,    /**< fullscreen window */
  OPENGL = 0x00000002,        /**< window usable with OpenGL context */
  SHOWN = 0x00000004,         /**< window is visible */
  HIDDEN = 0x00000008,        /**< window is not visible */
  BORDERLESS = 0x00000010,    /**< no window decoration */
  RESIZABLE = 0x00000020,     /**< window can be resized */
  MINIMIZED = 0x00000040,     /**< window is minimized */
  MAXIMIZED = 0x00000080,     /**< window is maximized */
  MOUSE_GRABBED = 0x00000100, /**< window has grabbed mouse input */
  INPUT_FOCUS = 0x00000200,   /**< window has input focus */
  MOUSE_FOCUS = 0x00000400,   /**< window has mouse focus */
} WindowStyle;
