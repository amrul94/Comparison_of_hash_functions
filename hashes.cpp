#include "hashes.h"

namespace hashes {
    //----------- BuildHashes ----------

    std::vector<HashStruct> Build32bitsHashes() {
        using namespace std::literals;
        std::vector<HashStruct> hash_functions;

        hash_functions.emplace_back("RollingHash (BuzHash32)", buz_hash_32);
        hash_functions.emplace_back("CityHash32", city_hash_32);
        hash_functions.emplace_back("Bernstein's hash djb2 32", djb2_hash_32);

        hash_functions.emplace_back("FarmHash32", farm_hash_32);
        hash_functions.emplace_back("FarmHash32WithSeed", farm_hash_32_with_seed);

        hash_functions.emplace_back("FastHash32", fast_hash_32);
        hash_functions.emplace_back("FNV-1a hash 32", fnv_1a_hash_32);

        hash_functions.emplace_back("Jenkins hash (One at a time)", one_at_a_time_hash);
        hash_functions.emplace_back("Jenkins hash (lookup3 - little)", lookup3_little_hash);
        hash_functions.emplace_back("Jenkins hash (lookup3 - big)", lookup_big_hash);

        hash_functions.emplace_back("MurmurHash1", murmur_hash1);
        hash_functions.emplace_back("MurmurHash1Aligned", murmur_hash1_aligned);
        hash_functions.emplace_back("MurmurHash2", murmur_hash2);

        hash_functions.emplace_back("PearsonHash32", pearson_hash_32);
        hash_functions.emplace_back("PJW Hash 32", pjw_hash_32);
        hash_functions.emplace_back("SDBM 32", sdbm_hash_32);
        hash_functions.emplace_back("SuperFastHash", super_fast_hash);
        hash_functions.emplace_back("Spooky hash 32", spooky_hash_32);

        hash_functions.emplace_back("T1HA0 32le", t1ha0_32le_hash);
        hash_functions.emplace_back("T1HA0 32be", t1ha0_32be_hash);

        hash_functions.emplace_back("xxHash32", xx_hash_32);

        return hash_functions;
    }

    std::vector<HashStruct> Build64bitsHashes() {
        using namespace std::literals;
        std::vector<HashStruct> hashes;

        hashes.emplace_back("RollingHash (BuzHash64)", buz_hash_64);

        hashes.emplace_back("CityHash64", city_hash_64);
        hashes.emplace_back("CityHash64WithSeed", city_hash_64_with_seed);
        hashes.emplace_back("CityHash64WithSeeds", city_hash_64_with_seeds);

        hashes.emplace_back("Bernstein's hash djb2 64", djb2_hash_64);

        hashes.emplace_back("FarmHash64", farm_hash_64);
        hashes.emplace_back("FarmHash64WithSeed", farm_hash_64_with_seed);
        hashes.emplace_back("FarmHash64WithSeeds", farm_hash_64_with_seeds);

        hashes.emplace_back("FastHash64", fast_hash_64);
        hashes.emplace_back("FNV-1a hash 64", fnv_1a_hash_64);

        hashes.emplace_back("MetroHash64_1", metro_hash_64_1);
        hashes.emplace_back("MetroHash64_2", metro_hash_64_2);

        hashes.emplace_back("MurmurHash64A", murmur_hash_64a);
        hashes.emplace_back("MurmurHash64B", murmur_hash_64b);

        hashes.emplace_back("PJW Hash 64", pjw_hash_64);
        hashes.emplace_back("PearsonHash64", pearson_hash_64);
        hashes.emplace_back("SDBMHash64", sdbm_hash_64);
        hashes.emplace_back("Spooky hash 64", spooky_hash_64);

        hashes.emplace_back("T1HA1 le", t1ha1_le_hash);
        hashes.emplace_back("T1HA1 be", t1ha1_be_hash);
        hashes.emplace_back("T1HA2 atonce", t1ha2_atonce_hash);

        hashes.emplace_back("xxHash64", xx_hash_64);
        hashes.emplace_back("XXH3_64bits", xxh3_64bits);
        hashes.emplace_back("XXH3_64bits_withSeed", xxh3_64bits_with_seed);

        return hashes;
    }
}