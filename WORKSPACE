workspace(name = "cpp_utils_lib")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# GoogleTest dependency
http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/release-1.11.0.zip"],
    strip_prefix = "googletest-release-1.11.0",
    sha256 = "353571c2440176ded91c2de6d6cd88ddd41401d14692ec1f99e35d013feda55a",
)

# We replaced Abseil with standard library components

# Google Benchmark for performance testing
http_archive(
    name = "com_github_google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/v1.6.1.zip"],
    strip_prefix = "benchmark-1.6.1",
    sha256 = "6132883bc8c9b0df5375b16ab520fac1a85dc9e4cf5be59480448ece74b278d4",
)
