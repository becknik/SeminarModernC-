#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <format>
#include <ranges>
#include <algorithm>
#include <chrono>
#include <random>

// A simplified data structure of the JSON schema being pulled by this program
struct JapVocab {
    std::string word;
    std::string reading;
    std::string meaning;
    std::string jlpt;
    bool isCommon;
};

auto from_json(const nlohmann::json& json) -> JapVocab {
    const auto containsWord = json.at("japanese")[0].contains("word");

    std::string word; // Some words only compose from hiragana...
    if (containsWord) {
        word = json.at("japanese")[0].at("word");
    } else {
        word = json.at("japanese")[0].at("reading");
    }

    return JapVocab {
        std::move(word),
        json.at("japanese")[0].at("reading"),
        json.at("senses")[0].at("english_definitions")[0],
        json.at("jlpt")[0],
        json.at("is_common")
    };
}

// Callback function for curl to write fetched data to a string
auto writeCallback(void* contents, size_t size, size_t nmemb, std::string& output) {
    size_t total_size = size * nmemb;
    output.append(static_cast<char*>(contents), total_size);
    return total_size;
}

std::string getCacheFileName(int page) {
    return std::format(".cache/page_{}.json", page);
}

bool isCacheAvailable(int page) {
    return std::filesystem::exists(getCacheFileName(page));
}

void saveToCache(int page, const std::string& data) {
    std::ofstream cacheFile(getCacheFileName(page));
    cacheFile << data;
}

std::string readFromCache(int page) {
    std::ifstream cacheFile(getCacheFileName(page));
    return std::string((std::istreambuf_iterator<char>(cacheFile)), std::istreambuf_iterator<char>());
}

auto main() -> int {
    // Curl setup, error handling & callback registration
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error initializing libcurl." << std::endl;
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    std::vector<JapVocab> vocabList;

    // The Jisho REST-API to be leveraged receives a URL param from 1 <= i <= 172
    for (const auto page : std::views::iota(1,173)) {
        std::string jsonResult;

        if (isCacheAvailable(page)) {
            jsonResult = readFromCache(page);
        } else {
            std::cout << std::format("> Fetching Jisho API JLPT1 page {}...\n", page);

            // Set the URL for the libcurl request
            std::string fullUrl =
                    std::format("https://jisho.org/api/v1/search/words?keyword=%23jlpt-n1&page={}", page);
            curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());

            // Prepare writing fetched data to a string
            jsonResult = std::string{};
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResult);

            // Perform the request & check for errors
            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "Error fetching data: " << curl_easy_strerror(res) << std::endl;
                curl_easy_cleanup(curl);
                return 1;
            }

            saveToCache(page, jsonResult);
        }

        nlohmann::json jsonData = nlohmann::json::parse(jsonResult);

        // The parsed json contains a data field which holds 20 japanese words
        for (const auto& element : jsonData["data"]) {
            const auto vocab = from_json(element);
            vocabList.push_back(vocab);

            std::cout << std::format("{} - {}\n", vocab.word, vocab.reading);
        }
        std::cout << std::endl;
    }

    curl_easy_cleanup(curl);

    // Status information
    std::cout << std::format("> Fetched {} vocabularies into list!\n\n", std::ssize(vocabList));

    std::cout << "Amount of 'common'-tagged vocab: " << std::ranges::distance(
            vocabList | std::views::filter([](const auto& v){return v.isCommon;})
    ) << std::endl;

    // The Benchmark

    using std::chrono::high_resolution_clock;

    std::mt19937 mt19937{ static_cast<std::mt19937::result_type>(
                                  std::chrono::steady_clock::now().time_since_epoch().count()
                          ) };
    // Like the Jisho API the page parameter starts with 1
    std::uniform_int_distribution userPageRequest{ 1, 150 };

    // To warm up the cache
    //std::ranges::sort(vocabList, {}, [](const JapVocab& vocab) {return vocab.word;});

    // Warmup
    for (auto i = 0; i < 10; ++i) {
        const auto urlPageParameter = userPageRequest(mt19937) - 1;
        std::array<std::string,20> filtered {};
        auto dropCount = urlPageParameter * 20;
        auto takeCount = 20;

        for (const auto& vocab : vocabList) {
            if (!vocab.isCommon) {
                continue;
            }
            if (0 <= --dropCount) {
                continue;
            }
            if (0 <= --takeCount) {
                filtered[takeCount] = vocab.reading;
                continue;
            }
            break;
        }
    }

    for (auto i = 0; i < 50; ++i) {
        const auto urlPageParameter = userPageRequest(mt19937) - 1;

        const auto t1 = high_resolution_clock::now();

        std::array<std::string,20> filtered {};
        auto dropCount = urlPageParameter * 20;
        auto takeCount = 20;

        for (const auto& vocab : vocabList) {
            if (!vocab.isCommon) {
                continue;
            }
            if (0 <= --dropCount) {
                continue;
            }
            if (0 <= --takeCount) {
                filtered[takeCount] = vocab.reading;
                continue;
            }
            break;
        }

        for (const auto& v : filtered) {
            std::cout << v << ' ';
        }

        const auto t2 = high_resolution_clock::now();
        const auto delta_ms{std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1)};

        std::cout << std::format("\n{}:{}ns\n\n", urlPageParameter, delta_ms.count());
    }
    return 0;
}