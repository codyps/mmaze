#pragma once

#define IRQN(id, name, long_name) SAM3_PERIPH_ID_##name = id,
#define IRQN_RESERVED(id)
enum sam3_periph_id {
# include "periph.def"
};
#undef IRQN
#undef IRQN_RESERVED
