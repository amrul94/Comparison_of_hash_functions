#include "generated_tests.h"
#include "distribution_tests.h"
#include "english_tests.h"
#include "log_duration.h"
#include "speed_tests.h"
#include "avalanche_tests.h"
#include "images_tests.h"

#include <pcg_random.hpp>
#include <algorithm>

#include "hashes.h"
#include "img.h"
#include "jpeg_image.h"
#include "my_assert.h"


#include <libcuckoo/cuckoohash_map.hh>

void TempTests(tests::ReportsRoot& report_root) {
    namespace fs = std::filesystem;
    fs::path images_dir = std::filesystem::current_path() / "data/images (new)/Original/Checked (Part 2)";

/*
    const tests::TestParameters tp(32, 1);
    libcuckoo::cuckoohash_map<uint64_t, std::atomic_uint64_t> hashes;
    for (const auto& dir_entry: fs::recursive_directory_iterator(images_dir)) {
        const auto& path = dir_entry.path();
        const auto status = fs::status(path);
        if (!fs::is_directory(status)) {
            img::Image image = img::LoadJPEG(path);
            const auto hash = hfl::murmur_hash1(image);
            const uint64_t modify = ModifyHash(tp, hash);
            hashes.;
        }
    }

    std::cout << "Collisions " << tests::CountCollisions(hashes) << std::endl;
    */
}

void HashIsCorrectTest() {
    auto lambda = [](const auto& hs, const std::vector<uint64_t>& numbers) {
        for (uint64_t number : numbers) {
            ASSERT_EQUAL_HINT(hs.hasher(number), hs.hasher(number), hs.name + " is not correct");
        }
        std::cout << boost::format("\t%1% is correct\n") % hs.name;
    };

    uint64_t count = 100000;
    pcg64 rng;
    std::vector<uint64_t> numbers;
    numbers.reserve(count);
    for (int i = 0; i < count; ++i) {
        numbers.emplace_back(rng());
    }

    const auto hashes16 = hfl::Build16bitsHashes();
    for (const auto& hs : hashes16) {
        lambda(hs, numbers);
    }

    const auto hashes24 = hfl::Build24bitsHashes();
    for (const auto& hs : hashes24) {
        lambda(hs, numbers);
    }

    const auto hashes32 = hfl::Build32bitsHashes();
    for (const auto& hs : hashes32) {
        lambda(hs, numbers);
    }

    const auto hashes48 = hfl::Build48bitsHashes();
    for (const auto& hs : hashes48) {
        lambda(hs, numbers);
    }

    const auto hashes64 = hfl::Build64bitsHashes();
    for (const auto& hs : hashes64) {
        lambda(hs, numbers);
    }
}


void RunTests(const std::vector<int>& test_numbers, tests::ReportsRoot& reports_root) {
    LOG_DURATION_STREAM("FULL TIME", reports_root.logger);
    for (int test_number : test_numbers) {
        switch (test_number) {
            case 0:
                reports_root.logger << "=== CHECK HASHES ===\n\n";
                HashIsCorrectTest();
                reports_root.logger << "=== CHECH HASHES ===\n\n\n";
                break;
            case 1:
                reports_root.logger << "=== START DISTRIBUTION TEST ===\n\n";
                tests::RunDistributionTests(reports_root);
                reports_root.logger << "=== END DISTRIBUTION TEST ===\n\n\n";
                break;
            case 2:
                reports_root.logger << "=== START GENERATED BLOCKS TEST (length = 16) ===\n\n";
                tests::RunTestWithGeneratedBlocks(16, reports_root);
                reports_root.logger << "=== END GENERATED BLOCKS TEST (length = 16) ===\n\n\n";
                break;
            case 3:
                reports_root.logger << "=== START GENERATED BLOCKS TEST (length = 4096) ===\n\n";
                tests::RunTestWithGeneratedBlocks(FOUR_KILOBYTES, reports_root);
                reports_root.logger << "=== END GENERATED BLOCKS TEST (length = 4096) ===\n\n\n";
                break;
            case 4:
                reports_root.logger << "=== START ENGLISH WORDS TEST ===\n\n";
                tests::RunTestWithEnglishWords(reports_root);
                reports_root.logger << "=== END ENGLISH WORDS TEST ===\n\n\n";
                break;
            case 5:
                reports_root.logger << "=== START SPEED TEST ===\n\n";
                tests::RunSpeedTests(2'000'000, FOUR_KILOBYTES, reports_root);
                reports_root.logger << "=== END SPEED TEST ===\n\n\n";
                break;
            case 6:
                reports_root.logger << "=== START AVALANCHE TEST ===\n\n";
                tests::RunAvalancheTests(reports_root);
                reports_root.logger << "=== END AVALANCHE TEST ===\n\n\n";
                break;
            case 7:
                reports_root.logger << "=== START IMAGES TEST ===\n\n";
                tests::RunImagesTests(reports_root);
                reports_root.logger << "=== END IMAGES TEST ===\n\n\n";
                break;
            default:
                TempTests(reports_root);
                break;
        }
    }
}

tests::ReportsRoot CreateReportsRoot() {
    const auto current_path = std::filesystem::current_path();
    const std::filesystem::path reports_dir{"reports"};
    const auto reports_path = current_path / reports_dir / CurrentTime() / "cpp";
    std::filesystem::create_directories(reports_path);
    return tests::ReportsRoot{reports_path};
}

int main() {
    const std::vector test_numbers{0};
    tests::ReportsRoot reports_root = CreateReportsRoot();
    RunTests(test_numbers, reports_root);
}

