package(default_visibility = ["//visibility:public"])

cc_test(
    name = "thread_safe_queue_test",
    srcs = ["thread_safe_queue_test.cc"],
    deps = [
        "//src/data_structures:thread_safe_queue",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "lru_cache_test",
    srcs = ["lru_cache_test.cc"],
    deps = [
        "//src/data_structures:lru_cache",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "custom_object_test",
    srcs = ["custom_object_test.cc"],
    deps = [
        "//src/data_structures:custom_object",
        "@com_google_googletest//:gtest_main",
    ],
)
