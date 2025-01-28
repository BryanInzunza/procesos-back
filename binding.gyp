{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "src/addon.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")",
        "node_modules/node-addon-api"
      ],
      "dependencies": [
        "node_modules/node-addon-api/node_api.gyp:nothing"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      }
    }
  ]
}