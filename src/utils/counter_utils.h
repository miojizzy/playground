/**
 * @file counter_utils.h
 * @brief Utility functions for counters.
 */

#ifndef CPP_UTILS_LIB_SRC_UTILS_COUNTER_UTILS_H_
#define CPP_UTILS_LIB_SRC_UTILS_COUNTER_UTILS_H_

#include <optional>

namespace cpp_utils::utils {

/**
    * @description: 用于统计元素的计数器，按照元素某成员的值进行分类统计
    * @tparam Key: 要统计的元素的成员类型
    * @tparam Value: 统计的元素的类型
    * @tparam KeyExtractor: 从元素value中提取成员值key的函数
    */
template<typename Key, typename Value>
class CounterTp {
public:
    using KeyExtractor = std::function<Key(const Value&)>;

    explicit CounterTp(KeyExtractor key_extractor): key_extractor_(std::move(key_extractor)) {}
    virtual ~CounterTp() = default;

    /**
        * @description: 传入要统计的元素，根据key_extractor_提取的key进行计数
        * @param value: 要统计的元素
        */
    void Count(const Value& value) { count_map_[key_extractor_(value)]++; }

    /**
        * @description: 获取统计结果，返回<成员类型Key，int32_t>映射
        * @return: 统计结果
        */
    const auto& GetCountMap() const { return count_map_; }
    std::vector<std::pair<Key, int32_t>> GetReverseByValue()
    {
        std::vector<std::pair<Key, int32_t>> ret;
        for(auto&& [key, value]: count_map_)
        {
            ret.emplace_back(key, value);
        }
        return ret;
    }
private:
    KeyExtractor key_extractor_; // 提取key的函数
    std::map<Key, int32_t> count_map_; // 统计结果, 有序输出
};


}  // namespace cpp_utils::utils

#endif  // CPP_UTILS_LIB_SRC_UTILS_COUNTER_UTILS_H_
