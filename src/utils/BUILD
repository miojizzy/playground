package(default_visibility = ["//visibility:public"])

cc_library(
    name = "utils",
    srcs = [
        "string_utils.cc",
        "file_utils.cc",
    ],
    hdrs = [
        "string_utils.h",
        "file_utils.h",
    ],
    copts = ["-std=c++17"],
)

cc_library(
    name = "string_utils",
    srcs = ["string_utils.cc"],
    hdrs = ["string_utils.h"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "file_utils",
    srcs = ["file_utils.cc"],
    hdrs = ["file_utils.h"],
    copts = ["-std=c++17"],
    deps = [
        ":string_utils",
    ],
)
