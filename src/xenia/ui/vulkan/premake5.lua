project_root = "../../../.."
include(project_root.."/tools/build")

group("src")
project("xenia-ui-vulkan")
  uuid("4933d81e-1c2c-4d5d-b104-3c0eb9dc2f00")
  kind("StaticLib")
  language("C++")
  links({
    "xenia-base",
    "xenia-ui",
    "xenia-ui-spirv",
  })
  defines({
  })
  includedirs({
    project_root.."/third_party/gflags/src",
    project_root.."/third_party/vulkan/",
  })
  local_platform_files()
  files({
    "shaders/bin/*.h",
  })
  removefiles({"*_demo.cc"})

group("demos")
project("xenia-ui-window-vulkan-demo")
  uuid("97598f13-3177-454c-8e58-c59e2b6ede27")
  kind("WindowedApp")
  language("C++")
  links({
    "gflags",
    "imgui",
    "volk",
    "xenia-base",
    "xenia-ui",
    "xenia-ui-spirv",
    "xenia-ui-vulkan",
  })
  defines({
  })
  includedirs({
    project_root.."/third_party/gflags/src",
    project_root.."/third_party/vulkan/",
  })
  files({
    "../window_demo.cc",
    "vulkan_window_demo.cc",
    project_root.."/src/xenia/base/main_"..platform_suffix..".cc",
    project_root.."/src/xenia/base/main_entrypoint_"..platform_suffix..".cc",
  })
  resincludedirs({
    project_root,
  })

  filter("files:"..project_root.."/src/xenia/base/main_entrypoint_"..platform_suffix..".cc")
    vectorextensions("IA32")  -- Disable AVX so our AVX check/error can happen.

  filter("platforms:Linux")
    links({
      "X11",
      "xcb",
      "X11-xcb",
      "GL",
      "vulkan",
    })
