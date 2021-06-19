#pragma once
/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * Parts of this file were generated with makeClass --run. Edit only those parts of
 * the code inside of 'EXISTING_CODE' tags.
 */
#include "etherlib.h"
#include "transaction.h"
#include "reconciliation.h"
#include "ethstate.h"
#include "monitoredapp.h"

namespace qblocks {

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
class CMonitor : public CAccountName {
  public:
    blknum_t nAppearances;
    blknum_t lastExport;
    blknum_t firstAppearance;
    blknum_t latestAppearance;
    uint64_t sizeInBytes;

  public:
    CMonitor(void);
    CMonitor(const CMonitor& mo);
    virtual ~CMonitor(void);
    CMonitor& operator=(const CMonitor& mo);

    DECLARE_NODE(CMonitor);

    // EXISTING_CODE
  public:
    bool isStaging;
    blknum_t lastVisitedBlock;
    bloom_t bloom;
    CArchive* tx_cache;

    CMonitor(const string_q& _addr, const string_q& _name, blknum_t fB, blknum_t lB);
    CMonitor(const address_t& _addr, const string_q& _name);

    bool openForWriting(bool staging);
    void writeMonitorArray(const CMonitoredAppearanceArray& array);
    void writeLastBlockInMonitor(blknum_t bn, bool staging);

    blknum_t getLastVisited(bool fresh = false) const;
    blknum_t getLastBlockInMonitor(void) const;

    bool loadAppearances(const string_q& path, CMonitoredAppearanceArray& apps) const;
    string_q getMonitorPath(const address_t& addr, bool staging) const;
    string_q getMonitorPathProduction(const address_t& addr) const;
    string_q getMonitorPathStaging(const address_t& addr) const;
    string_q getMonitorPathLast(const address_t& addr, bool staging) const;
    string_q getMonitorPathLastProduction(const address_t& addr) const;
    string_q getMonitorPathLastStaging(const address_t& addr) const;
    string_q getMonitorPathDels(const address_t& addr) const;

    size_t fileSize(const string_q& path) const;
    size_t nRecords(const string_q& path) const;
    size_t fileSize(void) const;
    size_t nRecords(void) const;

    bool monitorExists(void) const;
    bool isMonitorLocked(string_q& msg) const;
    bool clearMonitorLocks(void);
    void moveToProduction(bool staging);

    bool isDeleted(void) const;
    void deleteMonitor(void);
    void undeleteMonitor(void);
    void removeMonitor(void);

    bloom_t getBloom(void);
    // EXISTING_CODE
    bool operator==(const CMonitor& it) const;
    bool operator!=(const CMonitor& it) const {
        return !operator==(it);
    }
    friend bool operator<(const CMonitor& v1, const CMonitor& v2);
    friend ostream& operator<<(ostream& os, const CMonitor& it);

  protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CMonitor& mo);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CMonitor::CMonitor(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CMonitor::CMonitor(const CMonitor& mo) {
    // EXISTING_CODE
    tx_cache = NULL;
    // EXISTING_CODE
    duplicate(mo);
}

// EXISTING_CODE
//--------------------------------------------------------------------------
inline CMonitor::CMonitor(const string_q& _addr, const string_q& _name, blknum_t fB, blknum_t lB) {
    initialize();
    address = toLower(_addr);
    name = _name;
    firstAppearance = fB;
    latestAppearance = lB;
}

//--------------------------------------------------------------------------
inline CMonitor::CMonitor(const address_t& _addr, const string_q& _name) {
    initialize();
    address = toLower(_addr);
    name = _name;
    firstAppearance = 0;
    latestAppearance = 0;
}
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CMonitor::~CMonitor(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CMonitor::clear(void) {
    // EXISTING_CODE
    if (tx_cache) {
        tx_cache->Release();
        delete tx_cache;
    }
    tx_cache = NULL;
    lastVisitedBlock = NOPOS;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CMonitor::initialize(void) {
    CAccountName::initialize();

    nAppearances = 0;
    lastExport = 0;
    firstAppearance = 0;
    latestAppearance = 0;
    sizeInBytes = 0;

    // EXISTING_CODE
    isStaging = false;
    bloom = bloom_t();
    tx_cache = NULL;
    lastVisitedBlock = NOPOS;
    latestAppearance = UINT_MAX;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CMonitor::duplicate(const CMonitor& mo) {
    clear();
    CAccountName::duplicate(mo);

    nAppearances = mo.nAppearances;
    lastExport = mo.lastExport;
    firstAppearance = mo.firstAppearance;
    latestAppearance = mo.latestAppearance;
    sizeInBytes = mo.sizeInBytes;

    // EXISTING_CODE
    isStaging = mo.isStaging;
    bloom = mo.bloom;
    tx_cache = NULL;  // we do not copy the tx_cache
    lastVisitedBlock = mo.lastVisitedBlock;
    latestAppearance = mo.latestAppearance;
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CMonitor& CMonitor::operator=(const CMonitor& mo) {
    duplicate(mo);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CMonitor::operator==(const CMonitor& it) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default equal operator in class definition, assume none are equal (so find fails)
    return false;
}

//-------------------------------------------------------------------------
inline bool operator<(const CMonitor& v1, const CMonitor& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted, preserve ordering
    return true;
}

//---------------------------------------------------------------------------
typedef vector<CMonitor> CMonitorArray;
extern CArchive& operator>>(CArchive& archive, CMonitorArray& array);
extern CArchive& operator<<(CArchive& archive, const CMonitorArray& array);

//---------------------------------------------------------------------------
extern const char* STR_DISPLAY_MONITOR;

//---------------------------------------------------------------------------
// EXISTING_CODE
typedef map<address_t, CMonitor> CMonitorMap;  // NOLINT
extern string_q getTokenBalanceOf(const CMonitor& token, const address_t& holder, blknum_t blockNum);
extern string_q getTokenSymbol(const CMonitor& token, blknum_t blockNum);
extern string_q getTokenState(const CMonitor& token, const string_q& whichState, const CAbi& abi_spec,
                              blknum_t blockNum);
extern void establishMonitorFolders(void);
extern void cleanMonitorStage(void);
// EXISTING_CODE
}  // namespace qblocks
