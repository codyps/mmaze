/*
 * Prior to including this file, define:
 *
 * #define IF_INC "foo.def"
 * #define IF_PREFIX bar
 * #define IF_NAME foo
 */
#include <stddef.h>
#include <stdint.h>

#define R32(addr, sn, m, ln) uint32_t ln;
#define RES_1(addr) uint32_t res_##addr;
#define RES(a1, a2) uint32_t res_##a1##_to_##a2[(a2 - a1) / 4 + 1];
#define A32(base_addr, ct, sn, m, ln) uint32_t ln[ct];

#define SN__(prefix, name) prefix ## _ ## name
#define SN_(prefix, name) SN__(prefix, name)
#define SN SN_(IF_PREFIX, IF_NAME)

struct SN {
# include IF_INC()
};

#undef R32
#undef RES_1
#undef RES
#undef A32

/*
 * check offsets
 */

#define R32(addr, sn, m, ln) _Static_assert(offsetof(struct SN, ln) == addr, \
		"Offset wrong: " #ln "  " #addr);
#define RES_1(addr) _Static_assert(offsetof(struct SN, res_##addr) == addr, \
		"Offset wrong for reserved: " #addr);
#define RES(a1, a2) _Static_assert(offsetof(struct SN, res_##a1##_to_##a2) == a1, \
		"Offset wrong for reserved: " #a1 " to " #a2);
#define A32(base_addr, ct, sn, m, ln) _Static_assert(offsetof(struct SN, ln) == base_addr, \
		"Offset wrong: " #ln " " #base_addr);
#include IF_INC()

#undef R32
#undef RES_1
#undef RES
#undef A32

#undef SN
#undef SN_

#undef IF_INC
#undef IF_PREFIX
#undef IF_NAME
