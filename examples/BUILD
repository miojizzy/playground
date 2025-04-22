package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "example_main",
    srcs = ["example_main.cc"],
    deps = [
        "//:cpp_utils_lib",
    ],
)

cc_binary(
    name = "data_structures_example",
    srcs = ["data_structures_example.cc"],
    deps = [
        "//src/data_structures:data_structures",
    ],
)

cc_binary(
    name = "utils_example",
    srcs = ["utils_example.cc"],
    deps = [
        "//src/utils:utils",
    ],
)
