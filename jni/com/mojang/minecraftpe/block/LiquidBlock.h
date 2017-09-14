#pragma once
#include "Block.h"

class LiquidBlock : public Block {
public:
	bool solidify(BlockSource&, const BlockPos&, const BlockPos&) const;
};
