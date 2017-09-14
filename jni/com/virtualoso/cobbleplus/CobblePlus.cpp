#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>

#include "com/mojang/minecraftpe/block/LiquidBlock.h"
#include "com/mojang/minecraftpe/level/BlockSource.h"
#include "com/mojang/minecraftpe/level/Level.h"
#include "com/mojang/minecraftpe/util/Random.h"

static bool (*_LiquidBlock$solidify)(LiquidBlock*, BlockSource&, const BlockPos&, const BlockPos&);
static bool LiquidBlock$solidify(LiquidBlock* self, BlockSource& region, const BlockPos& pos1, const BlockPos& pos2)
{
	Block* blockToReplace;
	int random = region.getLevel().getRandom()->genrand_int32() % 100;
	if(random < 55)
		return _LiquidBlock$solidify(self, region, pos1, pos2);
	else if(random < 78)
		blockToReplace = random < 62 ? Block::mIronOre : Block::mCoalOre;
	else if(random < 92)
		blockToReplace = random < 84 ? Block::mGoldOre : Block::mRedStoneOre;
	else
		blockToReplace = random < 97 ? Block::mLapisOre : (random == 98 ? Block::mDiamondOre : Block::mEmeraldOre);
	Block::mCobblestone = blockToReplace;
	bool result = _LiquidBlock$solidify(self, region, pos1, pos2);
	Block::mCobblestone = Block::mBlocks[4];
	return result;
}


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	
	MSHookFunction((void*) &LiquidBlock::solidify, (void*) &LiquidBlock$solidify, (void**) &_LiquidBlock$solidify);
	
	return JNI_VERSION_1_2;
}
