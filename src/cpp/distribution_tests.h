#ifndef THESIS_WORK_CHECK_DISTRIBUTION_H
#define THESIS_WORK_CHECK_DISTRIBUTION_H

#include <atomic>
#include <iostream>
#include <execution>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <boost/format.hpp>

#include "hashes.h"
#include "test_parameters.h"
#include "log_duration.h"

namespace tests {

    using Bucket = std::uint16_t;

    void PrintReports(const std::vector<Bucket>& buckets, const DistTestParameters& dtp, const std::string& hash_name,
                      ReportsRoot& reports_root);

    template<typename HashStruct>
    void HashDistTest(const HashStruct& hs, const DistTestParameters& dtp, ReportsRoot& reports_root);

    template<typename HashStructs>
    void DistributionTest(const HashStructs& funcs, const DistTestParameters& dtp, ReportsRoot& reports_root);

    void RunDistTestNormal(size_t num_threads, ReportsRoot& reports_root);
    void RunDistTestWithBins(size_t num_threads, ReportsRoot& reports_root);

    void RunDistributionTests(ReportsRoot& reports_root);


// ==================================================

    template<typename HashStruct>
    void HashDistTest(const HashStruct& hs, const DistTestParameters& dtp, ReportsRoot& reports_root) {
        LOG_DURATION_STREAM('\t' + hs.name, reports_root.logger);

        // Выделить buckets, max_bucket и мьютекс в отдельный класс (например, Distributor).
        // При этом добавление нового элемента вынести в метод класса AddHash
        std::vector<std::atomic<Bucket>> buckets(dtp.num_buckets);
        const auto max_bucket = std::numeric_limits<Bucket>::max();

        auto lambda = [&hs, &dtp, &buckets, max_bucket](uint64_t start, uint64_t end) {
            for (uint64_t number = start; number < end; ++number) {
                const uint64_t hash = hs.hasher(number);
                const uint64_t modified = ModifyHash(dtp, hash);
                std::atomic<Bucket>& current_bucket = buckets[modified];
                Bucket old_bucket, new_bucket;
                do {
                    old_bucket = current_bucket.load();
                    const Bucket tmp = (old_bucket != max_bucket) ? 1 : 0;
                    new_bucket = old_bucket + tmp;
                } while (!current_bucket.compare_exchange_weak(old_bucket, new_bucket));
            }
        };

        uint64_t start = 0;
        uint64_t step = dtp.num_keys / dtp.num_threads;
        std::vector<std::thread> threads(dtp.num_threads - 1);

        for (auto& t : threads) {
            t = std::thread{lambda, start, start + step};
            start += step;
        }
        lambda(start, dtp.num_keys);

        for (auto& t : threads) {
            t.join();
        }

        PrintReports(buckets, dtp, hs.name, reports_root);

    }

    template<typename HashStructs>
    void DistributionTest(const HashStructs& funcs, const DistTestParameters& dtp, ReportsRoot& reports_root) {
        reports_root.logger << "--- START " << dtp.hash_bits << " BITS TEST ---\n";
        for (const auto& current_hash : funcs) {
            HashDistTest(current_hash, dtp, reports_root);
        }
        reports_root.logger << "--- END " << dtp.hash_bits << " BITS TEST ---\n\n";
    }
}

#endif //THESIS_WORK_CHECK_DISTRIBUTION_H
