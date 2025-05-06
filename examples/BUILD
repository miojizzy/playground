package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "//examples/utils:utils_examples",
        "//examples/algorithms:algorithms_examples",
        "//examples/data_structures:data_structures_examples",
        "//examples/math:math_examples",
    ],
)

# Keep the old example_main for backwards compatibility
cc_binary(
    name = "example_main",
    srcs = ["example_main.cc"],
    deps = [
        "//:cpp_utils_lib",
    ],
)
