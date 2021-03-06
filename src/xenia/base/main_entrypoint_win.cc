/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/base/main.h"

#include <fcntl.h>
#include <gflags/gflags.h>
#include <io.h>

#include <cstdlib>

// Autogenerated by `xb premake`.
#include "build/version.h"

#include "xenia/base/platform_win.h"
#include "xenia/base/string.h"

#include "third_party/xbyak/xbyak/xbyak_util.h"

namespace xe {
void AttachConsole();
int Main();
};  // namespace xe

// Used in console mode apps; automatically picked based on subsystem.
int main(int, char**) {
  Xbyak::util::Cpu cpu;
  if (!cpu.has(Xbyak::util::Cpu::tAVX)) {
    printf(
        "Your CPU does not support AVX, which is required by Xenia.\r\nSee the "
        "FAQ for system requirements at https://xenia.jp\r\n");
    return -1;
  }
  return xe::Main();
}

// Used in windowed apps; automatically picked based on subsystem.
int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
  Xbyak::util::Cpu cpu;
  if (!cpu.has(Xbyak::util::Cpu::tAVX)) {
    MessageBoxA(
        NULL,
        "Your CPU does not support AVX, which is required by Xenia. See the "
        "FAQ for system requirements at https://xenia.jp",
        "Xenia Error", MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
    return -1;
  }

  // Attach a console so we can write output to stdout. If the user hasn't
  // redirected output themselves it'll pop up a window.
  xe::AttachConsole();

  // Run normal entry point.
  return xe::Main();
}

#if defined _M_IX86
#pragma comment( \
    linker,      \
    "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")  // NOLINT(whitespace/line_length)
#elif defined _M_IA64
#pragma comment( \
    linker,      \
    "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")  // NOLINT(whitespace/line_length)
#elif defined _M_X64
#pragma comment( \
    linker,      \
    "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")  // NOLINT(whitespace/line_length)
#else
#pragma comment( \
    linker,      \
    "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  // NOLINT(whitespace/line_length)
#endif
