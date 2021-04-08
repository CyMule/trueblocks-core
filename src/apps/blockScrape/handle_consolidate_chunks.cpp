/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2018, 2019 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"
#include "consolidator.h"

//--------------------------------------------------------------------------
bool CConsolidator::consolidate_chunks(void) {
    ENTER("consolidate_chunks");

    // We are now in a valid state. All records that have not yet been consolidated
    // are in newStage. Count how many lines we have...
    blknum_t nRecords = fileSize(newStage) / 59;
    blknum_t chunkSize = MAX_ROWS;
    int64_t distToHead = (int64_t(chunkSize) - int64_t(nRecords));

    LOG_FN8(tmpFile);
    LOG_FN8(tmp_fn);
    LOG_FN8(oldStage);
    LOG_FN8(newStage);
    LOG8("nRecords: ", nRecords);
    LOG8("chunkSize: ", chunkSize);
    LOG8("Distance to head: ", distToHead);

    // ...if we don't have enough, return and get more...
    if (nRecords <= chunkSize) {
        LOG_INFO("");
        LOG_INFO(bBlue, "Consolidation not ready...", cOff);
        LOG_INFO(cYellow, "  Have ", nRecords, " records of ", chunkSize, ". Need ", distToHead, " more.", cOff);
        LOG_FN8(newStage);
        EXIT_NOMSG(true);
    }

    EXIT_NOMSG(write_chunks(chunkSize, false));
}

//---------------------------------------------------------------------------------------------------
bool visitToPin(const string_q& chunkId, void* data) {
    LOG_INFO("  Pinning");
    LOG_FN8(chunkId);
    ASSERT(data);
    CPinnedChunkArray& pinList = *(CPinnedChunkArray*)data;  // NO_LINT
    CPinnedChunk pinRecord;
    pinlib_pinChunk(pinList, chunkId, pinRecord);
    return !shouldQuit();
}
