/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"

//--------------------------------------------------------------------------------
void COptions::handle_config(ostream& os) {
    if (mode.empty()) {  // it's a get
        handle_config_get(os);
    } else {
        handle_config_put(os);
    }
}

//--------------------------------------------------------------------------------
void COptions::handle_config_get(ostream& os) {
    CConfiguration config;

    {
        const CToml *cc = getGlobalConfig();
        CConfigFile  f("quickBlocks.toml");
        CConfigGroup g1("settings");
        string_q     v1 = (isTestMode() ? "--rpcProvider--" : cc->getConfigStr(g1.name, "rpcProvider",     "http://localhost:8545"));
        string_q     v2 = (isTestMode() ? "--apiProvider--" : cc->getConfigStr(g1.name, "apiProvider",     "http://localhost:8080"));
        string_q     v3 = (isTestMode() ? "--balanceProv--" : cc->getConfigStr(g1.name, "balanceProvider", "http://localhost:8080"));
        string_q     v4 = (isTestMode() ? "--configPath--"  : cc->getConfigStr(g1.name, "configPath",      "~/.quickBlocks/"));
        string_q     v5 = (isTestMode() ? "--cachePath--"   : cc->getConfigStr(g1.name, "cachePath",       "~/.quickBlocks/cache/"));
        string_q     v6 = (isTestMode() ? "--indexPath--"   : cc->getConfigStr(g1.name, "indexPath",       "~/.quickBlocks/cache/addr_index/"));
        CConfigItem  i1("rpcProvider",     v1, "url",  "the Ethereum node's RPC endpoint",                 true,  false); g1.keys.push_back(i1);
        CConfigItem  i2("apiProvider",     v2, "url",  "TrueBlocks' API endpoint",                         true,  false); g1.keys.push_back(i2);
        CConfigItem  i3("balanceProvider", v3, "url",  "alternative node endpoint for account balances",   false, false); g1.keys.push_back(i3);
        CConfigItem  i4("configPath",      v4, "path", "location of config files, read only",              true,  true);  g1.keys.push_back(i4);
        CConfigItem  i5("cachePath",       v5, "path", "location of cache (on external SSD, for example)", false, false); g1.keys.push_back(i5);
        CConfigItem  i6("indexPath",       v6, "path", "location of index (on internal SSD for speed)",    false, false); g1.keys.push_back(i6);
        f.groups.push_back(g1);
#if 0
        acctExport.toml     STR_DISPLAY_TRANSACTION     hash, timestamp, from, to, ether, blockNumber, transactionIndex, etherGasPrice, gasUsed, isError, encoding
        acctExport.toml     STR_DISPLAY_LOG             blockNumber, transactionIndex, logIndex, address, topic0, topic1, topic2, topic3, data, type, compressedLog
        acctExport.toml     STR_DISPLAY_TRACE           blockNumber, transactionIndex, traceAddress
        acctExport.toml     STR_DISPLAY_BALANCERECORD   address, blockNum, tx_id, priorBalance, balance
#endif
        config.files.push_back(f);
    }

    {
        const CToml *cc = getGlobalConfig("blockScrape");
        CConfigFile  f("blockScrape.toml");
        CConfigGroup g1("settings");
        string_q     v1 = (isTestMode() ? "--nBlocks--"     : cc->getConfigStr(g1.name, "nBlocks",     "2000"));
        string_q     v2 = (isTestMode() ? "--nAddrProcs--"  : cc->getConfigStr(g1.name, "nAddrProcs",  "20"));
        string_q     v3 = (isTestMode() ? "--nBlockProcs--" : cc->getConfigStr(g1.name, "nBlockProcs", "10"));
        CConfigItem  i1("nBlocks",     v1, "uint",  "number of blocks to process per invocation of blaze (> 50)",        true, false); g1.keys.push_back(i1);
        CConfigItem  i2("nAddrProcs",  v2, "uint",  "number of parallel go processes to use to process addresses (> 0)", true, false); g1.keys.push_back(i2);
        CConfigItem  i3("nBlockProcs", v3, "uint",  "number of parallel go processes to use to process blocks (> 0)",    true, false); g1.keys.push_back(i3);
        f.groups.push_back(g1);
        config.files.push_back(f);
    }

    {
        const CToml *cc = getGlobalConfig("acctExport");
        CConfigFile  f("acctExport.toml");
        CConfigGroup g1("settings");
        CConfigGroup g2("balances");
        string_q     v1 = (isTestMode() ? "--writeTxs--"    : cc->getConfigStr(g1.name, "writeTxs",     "true"));
        string_q     v2 = (isTestMode() ? "--writeTraces--" : cc->getConfigStr(g1.name, "writeTraces",  "true"));
        string_q     v3 = (isTestMode() ? "--remote--"      : cc->getConfigStr(g2.name, "remote",       "false"));
        CConfigItem  i1("writeTxs",    v1, "bool", "write transactions to the TrueBlocks binary cache", false, false); g1.keys.push_back(i1);
        CConfigItem  i2("writeTraces", v2, "bool", "write traces to the TrueBlocks binary cache",       false, false); g1.keys.push_back(i2);
        CConfigItem  i3("remote",      v3, "bool", "get balances from balanceProvider",                 false, false); g2.keys.push_back(i3);
        f.groups.push_back(g1);
        f.groups.push_back(g2);
        config.files.push_back(f);
    }

#if 0
    {
        //const CToml *cc = getGlobalConfig("getBlock");
        CConfigFile  f("getBlock.toml");
        CConfigGroup g1("display");
        CConfigItem  i1("block_fmt", "<not-set>", "display_str", "format to display block data", false, false); g1.keys.push_back(i1);
        f.groups.push_back(g1);
        config.files.push_back(f);
    }
#endif

#if 0
    getBlock.toml
    getTrans.toml       STR_DISPLAY_TRANSACTION     date, timestamp, blockNumber, transactionIndex, hash, compressedTx
    getReceipt.toml     STR_DISPLAY_RECEIPT         blockNumber, transactionIndex, hash, gasUsed, status, isError
    getLogs.toml        STR_DISPLAY_LOG             blockNumber, transactionIndex, logIndex, address, topic0, topic1, topic2, topic3, data, type, compressedLog
    getTrace.toml       STR_DISPLAY_TRACE           blockNumber, transactionIndex, traceAddress, action
    getState.toml       STR_DISPLAY_STATE           blockNumber, address, balance, nonce, code, storage, deployed, acctType
    getAccounts.toml    STR_DISPLAY_ACCOUNTNAME     group, address, name, symbol, source, description, logo, is_contract, is_private, is_shared
    grabABI.toml        STR_DISPLAY_FUNCTION        name, type, anonymous, constant, payable, signature, encoding, inputs, outputs
    ethQuote.toml       STR_DISPLAY_ETHQUOTE        blockNumber, timestamp, price
    whenBlock.toml      STR_DISPLAY_WHEN            blockNumber, timestamp, date, name
    whereBlock.toml     STR_DISPLAY_WHERE           blockNumber, path, cached
#endif

    {
        manageFields("CAccountName:firstAppearance,latestAppearance,nRecords,sizeInBytes", false);

        const CToml *cc = getGlobalConfig("getAccounts");
        CConfigFile  f("getAccounts.toml");
        CConfigGroup g1("custom");

        CConfigItem i1("list", "", "json array", "user specific list of names for addresses -- private data -- not shared", false, false);
        if (isTestMode()) {
            i1.named.push_back(CAccountName(CAccountName("81-Custom\t0x0000100001000010000100001000010000100001\tTestWallet1")));
            i1.named.push_back(CAccountName(CAccountName("81-Custom\t0x0000200002000020000200002000020000200002\tTestWallet2")));

        } else {

            string_q customStr = cc->getConfigJson("custom", "list", "");
            CAccountName item;
            while (item.parseJson3(customStr)) {
                i1.named.push_back(item);
                item = CAccountName();
            }
        }

        g1.keys.push_back(i1);
        f.groups.push_back(g1);
        config.files.push_back(f);
    }

    {
        const CToml *cc = getGlobalConfig("ethslurp");
        CConfigFile  f("ethslurp.toml");
        CConfigGroup g1("settings");
        string_q     v1 = (isTestMode() ? "--api_key--" : cc->getConfigStr(g1.name, "api_key", "<not-set>"));
        CConfigItem  i1("api_key", v1, "string", "api key required to use EtherScan apis -- private data -- not shared", false, false); g1.keys.push_back(i1);
        f.groups.push_back(g1);
        config.files.push_back(f);
    }

    //blockNumber, transactionIndex, traceAddress, action::callType, error, action::from, action::to, action:value, action::ether, action::gas, result::gasUsed, action::input, compressedTrace, result::output


    os << config << endl;

    return;
}

//--------------------------------------------------------------------------------
void COptions::handle_config_put(ostream& os) {
    CConfiguration config;
    string_q str = asciiFileToString("input.json");
    config.parseJson3(str);
    {
        if (true) { //isTestMode()) {
            cout << "Would have written:" << endl;
            for (auto file : config.files) {
                for (auto group : file.groups) {
                    for (auto key : group.keys) {
                        cout << "  ";
                        cout << "getGlobalConfig(\"" << file.name << "\")->";
                        cout << "setConfigStr(\"" << group.name << "\", \"" << key.name << "\", \"" << key.getValueByName("value") << "\");" << endl;
                    }
                }
            }
        }
    }
    return;
}
