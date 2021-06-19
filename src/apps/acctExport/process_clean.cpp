/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"

//---------------------------------------------------------------
bool cleanMonitorFile(const string_q& path, void* data) {
    ENTER("visitFile");

    if (endsWith(path, '/')) {
        forEveryFileInFolder(path + "*", cleanMonitorFile, data);

    } else {
        if (endsWith(path, "acct.bin")) {
            if (isTestMode()) {
                CMonitor m;
                if (path > m.getMonitorPathProduction("0x9"))
                    return false;
            }

            CMonitor m;
            size_t sizeThen = m.nRecords(path);
            if (!sizeThen)
                EXIT_NOMSG(!shouldQuit());

            CMonitoredAppearanceArray apps;
            if (!m.loadAppearances(path, apps))
                EXIT_FAIL("Could not open cache file.");
            sort(apps.begin(), apps.end());

            CMonitoredAppearance prev;
            CMonitoredAppearanceArray deduped;
            for (auto a : apps) {
                if (a.blk != prev.blk || a.txid != prev.txid) {
                    deduped.push_back(a);
                }
                prev = a;
            }

            CArchive archiveOut(WRITING_ARCHIVE);
            archiveOut.Lock(path, modeWriteCreate, LOCK_WAIT);
            for (auto item : deduped)
                archiveOut << item.blk << item.txid;
            archiveOut.Release();

            static bool first = true;
            if (!first)
                cout << ",";
            first = false;
            size_t sizeNow = m.nRecords(path);
            cout << "{ ";
            cout << "\"path\": \"" << substitute(path, m.getMonitorPathProduction(""), "$CACHE/") << "\", ";
            cout << "\"sizeThen\": " << sizeThen << ", ";
            cout << "\"sizeNow\": " << sizeNow;
            if (sizeThen > sizeNow)
                cout << ", \"dupsRemoved\": " << (sizeThen - sizeNow);
            cout << " }" << endl;
        }
    }

    return !shouldQuit();
}

//---------------------------------------------------------------
bool COptions::process_clean(void) {
    CMonitor m;
    cout << "[";
    bool ret = forEveryFileInFolder(m.getMonitorPathProduction(""), cleanMonitorFile, NULL);
    cout << "]";
    return ret;
}
