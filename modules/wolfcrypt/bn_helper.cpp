#include "bn_ops.h"

namespace cryptofuzz {
namespace module {

namespace wolfCrypt_detail {
#if defined(CRYPTOFUZZ_WOLFCRYPT_ALLOCATION_FAILURES)
    extern bool haveAllocFailure;
#endif
} /* namespace wolfCrypt_detail */

namespace wolfCrypt_bignum {

void Bignum::baseConversion(void) const {
#if !defined(WOLFSSL_SP_MATH)
    uint8_t base = 2;
    char* str = nullptr;

    try { base = ds.Get<uint8_t>(); } catch ( fuzzing::datasource::Datasource::OutOfData ) { }

    {
        int size;
        CF_CHECK_EQ(mp_radix_size(mp, base, &size), MP_OKAY);
        CF_ASSERT(size > 0, "Output of mp_radix_size is 0 or less");

        str = (char*)util::malloc(size);

        CF_CHECK_EQ(mp_toradix(mp, str, base), MP_OKAY);

        wolfCrypt_detail::haveAllocFailure = false;
        CF_ASSERT(mp_read_radix(mp, str, base) == MP_OKAY || wolfCrypt_detail::haveAllocFailure, "wolfCrypt cannot parse the output of mp_toradix");
    }

end:
    util::free(str);
#endif
}

Bignum::Bignum(Datasource& ds) :
    ds(ds) {
    mp = (mp_int*)util::malloc(sizeof(mp_int));
    if ( mp_init(mp) != MP_OKAY ) {
        util::free(mp);
        throw std::exception();
    }
}
        
Bignum::Bignum(mp_int* mp, Datasource& ds) :
    mp(mp),
    ds(ds),
    noFree(true)
{ }

Bignum::Bignum(const Bignum& other) :
    ds(other.ds) {
    mp = (mp_int*)util::malloc(sizeof(mp_int));
    if ( mp_init(mp) != MP_OKAY ) {
        util::free(mp);
        throw std::exception();
    }
    if ( mp_copy(other.mp, mp) != MP_OKAY ) {
        util::free(mp);
        throw std::exception();
    }
}

Bignum::Bignum(const Bignum&& other) :
    ds(other.ds) {
    mp = (mp_int*)util::malloc(sizeof(mp_int));
    if ( mp_init(mp) != MP_OKAY ) {
        util::free(mp);
        throw std::exception();
    }
    if ( mp_copy(other.mp, mp) != MP_OKAY ) {
        util::free(mp);
        throw std::exception();
    }
}

Bignum::~Bignum() {
    if ( noFree == false ) {
        /* noret */ mp_clear(mp);
        util::free(mp);
    }
}

void Bignum::SetNoFree(void) {
    noFree = true;
}

bool Bignum::Set(const std::string s) {
    bool ret = false;

    bool hex = false;
    try {
        hex = ds.Get<bool>();
    } catch ( ... ) { }

#if defined(WOLFSSL_SP_MATH)
    hex = true;
#endif

    if ( hex == true ) {
        const auto asDec = util::DecToHex(s);
        CF_CHECK_EQ(mp_read_radix(mp, asDec.c_str(), 16), MP_OKAY);
    } else {
        CF_CHECK_EQ(mp_read_radix(mp, s.c_str(), 10), MP_OKAY);
    }

    ret = true;
end:
    return ret;
}

bool Bignum::Set(const component::Bignum i) {
    bool ret = false;

    CF_CHECK_EQ(Set(i.ToString()), true);

    ret = true;
end:
    return ret;
}

mp_int* Bignum::GetPtr(void) const {
    {
        /* Optionally clamp the bignum. This should not affect its value. */

        bool clamp = false;

        try { clamp = ds.Get<bool>(); } catch ( fuzzing::datasource::Datasource::OutOfData ) { }

        if ( clamp ) {
            /* noret */ mp_clamp(mp);
        }
    }

    {
        /* Optionally convert to a random base and back */

        bool convert = false;

        try { convert = ds.Get<bool>(); } catch ( fuzzing::datasource::Datasource::OutOfData ) { }

        if ( convert ) {
            baseConversion();
        }
    }

    return mp;
}
        
std::optional<uint64_t> Bignum::AsUint64(void) const {
    std::optional<uint64_t> ret = std::nullopt;
    uint64_t v = 0;

#if !defined(WOLFSSL_SP_MATH)
    CF_CHECK_EQ(mp_isneg(mp), 0);
#endif
    CF_CHECK_LTE(mp_count_bits(mp), (int)(sizeof(v) * 8));
    CF_CHECK_EQ(mp_to_unsigned_bin_len(mp, (uint8_t*)&v, sizeof(v)), MP_OKAY);
    v =
        ((v & 0xFF00000000000000) >> 56) |
        ((v & 0x00FF000000000000) >> 40) |
        ((v & 0x0000FF0000000000) >> 24) |
        ((v & 0x000000FF00000000) >>  8) |
        ((v & 0x00000000FF000000) <<  8) |
        ((v & 0x0000000000FF0000) << 24) |
        ((v & 0x000000000000FF00) << 40) |
        ((v & 0x00000000000000FF) << 56);

    ret = v;
end:
    return ret;
}

std::optional<std::string> Bignum::ToDecString(void) {
    std::optional<std::string> ret = std::nullopt;
    char* str = nullptr;

#if defined(WOLFSSL_SP_MATH)
    str = (char*)util::malloc(8192);

    CF_CHECK_EQ(mp_tohex(mp, str), MP_OKAY);
    ret = { util::HexToDec(str) };
#else
    bool hex = false;
    int size;

    try {
        hex = ds.Get<bool>();
    } catch ( ... ) { }


    if ( hex == true ) {
        CF_CHECK_EQ(mp_radix_size(mp, 16, &size), MP_OKAY);
        CF_ASSERT(size > 0, "Output of mp_radix_size is 0 or less");

        str = (char*)util::malloc(size+1);

        CF_CHECK_EQ(mp_tohex(mp, str), MP_OKAY);
        ret = { util::HexToDec(str) };
    } else {
        CF_CHECK_EQ(mp_radix_size(mp, 10, &size), MP_OKAY);
        CF_ASSERT(size > 0, "Output of mp_radix_size is 0 or less");

        str = (char*)util::malloc(size);

        CF_CHECK_EQ(mp_toradix(mp, str, 10), MP_OKAY);
        ret = std::string(str);
    }
#endif

end:
    free(str);

    return ret;
}

std::optional<component::Bignum> Bignum::ToComponentBignum(void) {
    std::optional<component::Bignum> ret = std::nullopt;

    auto str = ToDecString();
    CF_CHECK_NE(str, std::nullopt);
    ret = { str };
end:
    return ret;
}

bool Bignum::ToBin(uint8_t* dest, const size_t size) {
    bool ret = false;

    CF_CHECK_EQ(mp_to_unsigned_bin_len(GetPtr(), dest, size), MP_OKAY);

    ret = true;
end:
    return ret;
}


std::optional<std::vector<uint8_t>> Bignum::ToBin(Datasource& ds, const component::Bignum b, std::optional<size_t> size) {
    std::optional<std::vector<uint8_t>> ret = std::nullopt;
    std::vector<uint8_t> v;
    Bignum bn(ds);

    CF_CHECK_EQ(bn.Set(b), true);
    if ( size != std::nullopt ) {
        v.resize(*size);
    } else {
        v.resize( mp_unsigned_bin_size(bn.GetPtr()) );
    }
    CF_CHECK_EQ(bn.ToBin(v.data(), v.size()), true);

    ret = v;
end:
    return ret;
}

bool Bignum::ToBin(Datasource& ds, const component::Bignum b, uint8_t* dest, const size_t size) {
    bool ret = false;
    Bignum bn(ds);

    CF_CHECK_EQ(bn.Set(b), true);
    CF_CHECK_EQ(bn.ToBin(dest, size), true);

    ret = true;
end:
    return ret;
}

bool Bignum::ToBin(Datasource& ds, const component::BignumPair b, uint8_t* dest, const size_t size) {
    CF_ASSERT((size % 2) == 0, "Input size is not multiple of 2 in Bignum::ToBin");

    bool ret = false;
    const auto halfSize = size / 2;

    CF_CHECK_EQ(ToBin(ds, b.first, dest, halfSize), true);
    CF_CHECK_EQ(ToBin(ds, b.second, dest + halfSize, halfSize), true);

    ret = true;
end:
    return ret;
}

std::optional<component::Bignum> Bignum::BinToBignum(Datasource& ds, const uint8_t* src, const size_t size) {
    std::optional<component::Bignum> ret = std::nullopt;

    wolfCrypt_bignum::Bignum bn(ds);
    CF_CHECK_EQ(mp_read_unsigned_bin(bn.GetPtr(), src, size), MP_OKAY);

    ret = bn.ToComponentBignum();

end:
    return ret;
}

std::optional<component::BignumPair> Bignum::BinToBignumPair(Datasource& ds, const uint8_t* src, const size_t size) {
    CF_ASSERT((size % 2) == 0, "Input size is not multiple of 2 in Bignum::BinToBignumPair");

    std::optional<component::BignumPair> ret = std::nullopt;
    std::optional<component::Bignum> A, B;
    const auto halfSize = size / 2;

    {
        wolfCrypt_bignum::Bignum bn(ds);
        CF_CHECK_EQ(mp_read_unsigned_bin(bn.GetPtr(), src, halfSize), MP_OKAY);
        CF_CHECK_NE(A = bn.ToComponentBignum(), std::nullopt);
    }

    {
        wolfCrypt_bignum::Bignum bn(ds);
        CF_CHECK_EQ(mp_read_unsigned_bin(bn.GetPtr(), src + halfSize, halfSize), MP_OKAY);
        CF_CHECK_NE(B = bn.ToComponentBignum(), std::nullopt);
    }


    ret = {A->ToTrimmedString(), B->ToTrimmedString()};

end:
    return ret;
}
        
bool Bignum::operator==(const Bignum& rhs) const {
    return mp_cmp(GetPtr(), rhs.GetPtr()) == MP_EQ;
}

BignumCluster::BignumCluster(Datasource& ds, Bignum bn0, Bignum bn1, Bignum bn2, Bignum bn3) :
    ds(ds),
    bn({bn0, bn1, bn2, bn3})
{ }

Bignum& BignumCluster::operator[](const size_t index) {
    CF_ASSERT(index < bn.size(), "Invalid index requested in BignumCluster::operator[]");

    try {
        /* Rewire? */
        if ( ds.Get<bool>() == true ) {
            /* Pick a random bignum */
            const auto newIndex = ds.Get<uint8_t>() % 4;

            /* Same value? */
            if ( bn[newIndex] == bn[index] ) {
                /* Then return reference to other bignum */
                return bn[newIndex];
            }

            /* Fall through */
        }
    } catch ( fuzzing::datasource::Datasource::OutOfData ) { }

    return bn[index];
}

bool BignumCluster::Set(const size_t index, const std::string s) {
    CF_ASSERT(index < bn.size(), "Invalid index requested in BignumCluster::Set");

    return bn[index].Set(s);
}

mp_int* BignumCluster::GetDestPtr(const size_t index) {
    return bn[index].GetPtr();
}

} /* namespace wolfCrypt_bignum */
} /* namespace module */
} /* namespace cryptofuzz */
