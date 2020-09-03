static const std::map<uint64_t, std::pair<std::string, std::string>> LUT = {
    { CF_CIPHER("AES_128_CBC"), {"AES-128/CBC", "AES-128"} },
    { CF_CIPHER("AES_128_CTR"), {"AES-128/CTR", "AES-128"} },
    { CF_CIPHER("AES_128_OCB"), {"AES-128/OCB", "AES-128"} },
    { CF_CIPHER("AES_128_XTS"), {"AES-128/XTS", "AES-128"} },
    { CF_CIPHER("AES_192_CBC"), {"AES-192/CBC", "AES-192"} },
    { CF_CIPHER("AES_192_CTR"), {"AES-192/CTR", "AES-192"} },
    { CF_CIPHER("AES_256_CBC"), {"AES-256/CBC", "AES-256"} },
    { CF_CIPHER("AES_256_CTR"), {"AES-256/CTR", "AES-256"} },
    { CF_CIPHER("AES_256_OCB"), {"AES-256/OCB", "AES-256"} },
    { CF_CIPHER("AES_256_XTS"), {"AES-256/XTS", "AES-256"} },
    { CF_CIPHER("ARIA_128_CBC"), {"ARIA-128/CBC", "ARIA-128"} },
    { CF_CIPHER("ARIA_128_CTR"), {"ARIA-128/CTR", "ARIA-128"} },
    { CF_CIPHER("ARIA_192_CBC"), {"ARIA-192/CBC", "ARIA-192"} },
    { CF_CIPHER("ARIA_192_CTR"), {"ARIA-192/CTR", "ARIA-192"} },
    { CF_CIPHER("ARIA_256_CBC"), {"ARIA-256/CBC", "ARIA-256"} },
    { CF_CIPHER("ARIA_256_CTR"), {"ARIA-256/CTR", "ARIA-256"} },
    { CF_CIPHER("BF_CBC"), {"Blowfish/CBC", "Blowfish"} },
    { CF_CIPHER("CAMELLIA_128_CBC"), {"Camellia-128/CBC", "Camellia-128"} },
    { CF_CIPHER("CAMELLIA_192_CBC"), {"Camellia-192/CBC", "Camellia-192"} },
    { CF_CIPHER("CAMELLIA_256_CBC"), {"Camellia-256/CBC", "Camellia-256"} },
    { CF_CIPHER("CAST5_CBC"), {"CAST5/CBC", "CAST5"} },
    { CF_CIPHER("CHACHA20"), {"ChaCha(20)", "ChaCha(20)"} },
    { CF_CIPHER("DESX_B_CBC"), {"DESX/CBC", "DESX"} },
    { CF_CIPHER("DES_CBC"), {"DES/CBC", "DES"} },
    { CF_CIPHER("DES_EDE3_CBC"), {"DES-EDE/CBC", "DES-EDE"} },
    { CF_CIPHER("IDEA_CBC"), {"IDEA/CBC", "IDEA"} },
    { CF_CIPHER("KASUMI_CBC"), {"KASUMI/CBC", "KASUMI"} },
    { CF_CIPHER("KASUMI_CTR"), {"KASUMI/CTR", "KASUMI"} },
    { CF_CIPHER("KASUMI_OFB"), {"KASUMI/OFB", "KASUMI"} },
    { CF_CIPHER("KASUMI_XTS"), {"KASUMI/XTS", "KASUMI"} },
    { CF_CIPHER("MISTY1_CBC"), {"MISTY1/CBC", "MISTY1"} },
    { CF_CIPHER("MISTY1_CTR"), {"MISTY1/CTR", "MISTY1"} },
    { CF_CIPHER("MISTY1_OFB"), {"MISTY1/OFB", "MISTY1"} },
    { CF_CIPHER("MISTY1_XTS"), {"MISTY1/XTS", "MISTY1"} },
    { CF_CIPHER("NOEKEON_CBC"), {"Noekeon/CBC", "Noekeon"} },
    { CF_CIPHER("NOEKEON_CTR"), {"Noekeon/CTR", "Noekeon"} },
    { CF_CIPHER("NOEKEON_OFB"), {"Noekeon/OFB", "Noekeon"} },
    { CF_CIPHER("NOEKEON_XTS"), {"Noekeon/XTS", "Noekeon"} },
    { CF_CIPHER("SEED_CBC"), {"SEED/CBC", "SEED"} },
    { CF_CIPHER("SEED_OFB"), {"SEED/OFB", "SEED"} },
    { CF_CIPHER("SERPENT_CBC"), {"Serpent/CBC", "Serpent"} },
    { CF_CIPHER("SERPENT_CTR"), {"Serpent/CTR", "Serpent"} },
    { CF_CIPHER("SERPENT_OFB"), {"Serpent/OFB", "Serpent"} },
    { CF_CIPHER("SERPENT_XTS"), {"Serpent/XTS", "Serpent"} },
    { CF_CIPHER("SHACAL2_CBC"), {"SHACAL2/CBC", "SHACAL2"} },
    { CF_CIPHER("SHACAL2_CTR"), {"SHACAL2/CTR", "SHACAL2"} },
    { CF_CIPHER("SHACAL2_OFB"), {"SHACAL2/OFB", "SHACAL2"} },
    { CF_CIPHER("SHACAL2_XTS"), {"SHACAL2/XTS", "SHACAL2"} },
    { CF_CIPHER("SM4_CBC"), {"SM4/CBC", "SM4"} },
    { CF_CIPHER("SM4_CTR"), {"SM4/CTR", "SM4"} },
    { CF_CIPHER("SM4_OFB"), {"SM4/OFB", "SM4"} },
    { CF_CIPHER("THREEFISH_512_CBC"), {"Threefish-512/CBC", "Threefish-512"} },
    { CF_CIPHER("THREEFISH_512_CTR"), {"Threefish-512/CTR", "Threefish-512"} },
    { CF_CIPHER("THREEFISH_512_OFB"), {"Threefish-512/OFB", "Threefish-512"} },
    { CF_CIPHER("THREEFISH_512_XTS"), {"Threefish-512/XTS", "Threefish-512"} },
    { CF_CIPHER("TWOFISH_CBC"), {"Twofish/CBC", "Twofish"} },
    { CF_CIPHER("TWOFISH_CTR"), {"Twofish/CTR", "Twofish"} },
    { CF_CIPHER("TWOFISH_OFB"), {"Twofish/OFB", "Twofish"} },
    { CF_CIPHER("TWOFISH_XTS"), {"Twofish/XTS", "Twofish"} },
    { CF_CIPHER("XTEA_CBC"), {"XTEA/CBC", "XTEA"} },
    { CF_CIPHER("XTEA_CTR"), {"XTEA/CTR", "XTEA"} },
    { CF_CIPHER("XTEA_OFB"), {"XTEA/OFB", "XTEA"} },
    { CF_CIPHER("XTEA_XTS"), {"XTEA/XTS", "XTEA"} },
    { CF_CIPHER("GOST-28147-89_CBC"), {"GOST-28147-89/CBC", "GOST-28147-89"} },
    { CF_CIPHER("SALSA20_128"), {"Salsa20(128)", "Salsa20(128)"} },
    { CF_CIPHER("SALSA20_256"), {"Salsa20(256)", "Salsa20(256)"} },
};
