// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, uint256("0x7c51316bf1e3af0904f2dfd4519d301327e381c0ebcf98424efac738b1ad1cb6"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1422234505, // * UNIX timestamp of last checkpoint block
        0,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        100.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x7c51316bf1e3af0904f2dfd4519d301327e381c0ebcf98424efac738b1ad1cb6"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1405625749,
        4440,
        5000
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x7c51316bf1e3af0904f2dfd4519d301327e381c0ebcf98424efac738b1ad1cb6"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1405166035,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0x15;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xad;
        vAlertPubKey = ParseHex("047885d9f6c0cf9e918d04634d4dd696cf172763f1975aad099daddca3f3c712c98754eae293b36484055e0d414800e519f5a342e56e09217faf07abff5bd96507");
        nDefaultPort = 18554;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 25000;
        nEnforceBlockUpgradeMajority = 15000;
        nRejectBlockOutdatedMajority = 19000;
        nToCheckBlockUpgradeMajority = 20000;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        nTargetSpacing = 1 * 45;
        nCLTVStartBlock = 1;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=4e9b54001f9976049830128ec0331515eaabe35a70970d79971da1539a400ba1, PoW=000001a16729477595c7247e1b49b4ec93acca8345037177cabbe898ce8a5783, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, 
         *     hashMerkleRoot=0317d32e01a2adf6f2ac6f58c7cdaab6c656edc6fdb45986c739290053275200,
         *     nTime=1405164774, nBits=1e01ffff, nNonce=4016033, vtx=1)
         *   CTransaction(hash=0317d32e01, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *   CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d01044c4e426c6f636b20233331303337393a30303030303030303030303030303030323431323532613762623237626539376265666539323138633132393064666633366331666631323965633732313161)
         *   CTxOut(nValue=0.00000000, scriptPubKey=0459934a6a228ce9716fa0b13aa1cd)
         * vMerkleTree: 0317d32e01a2adf6f2ac6f58c7cdaab6c656edc6fdb45986c739290053275200
         */
        const char* pszTimestamp = "Wired 26/Jan/2015 An Ingenious New Typeface Inspired by Old Maps, But Made With Algorithms";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1422234505;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 1137826;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x7c51316bf1e3af0904f2dfd4519d301327e381c0ebcf98424efac738b1ad1cb6"));
        assert(genesis.hashMerkleRoot == uint256("0x846e08b063243e3201b25ed09bcada3fb47133182f150d07bd5c3be8303eb72f"));
        

        vSeeds.push_back(CDNSSeedData("extractcoin.com", "seed.extractcoin.com"));
        vSeeds.push_back(CDNSSeedData("seed.extractcoin.com", "extractcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(75);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(33);
        base58Prefixes[SECRET_KEY] =     list_of(199);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa9;
        pchMessageStart[1] = 0xc5;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0x92;
        vAlertPubKey = ParseHex("045c480dac3b2c8ef95a8577faa2420eabfe376fbfa31b2bb1896b3e5a30675403f4b3d084724d65afcbbb61473a302a6ed3286e39041176d9af6ff601543bd113");
        nDefaultPort = 25223;
        nEnforceBlockUpgradeMajority = 510;
        nRejectBlockOutdatedMajority = 750;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 1 * 24;
        nCLTVStartBlock = 502664;
        bnProofOfWorkLimit = ~uint256(0) >> 19;
        genesis.nBits = 0x1e0ffff0;

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1422234505;
        genesis.nNonce = 1137826;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x7c51316bf1e3af0904f2dfd4519d301327e381c0ebcf98424efac738b1ad1cb6"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet.extractcoin.net", "testnet.extractcoin.net"));
        vSeeds.push_back(CDNSSeedData("extractcoin.net", "testnet.extractcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(127);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(255);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x97;
        pchMessageStart[2] = 0x7b;
        pchMessageStart[3] = 0x37;
        nSubsidyHalvingInterval = 5400;
        nEnforceBlockUpgradeMajority = 7500;
        nRejectBlockOutdatedMajority = 9500;
        nToCheckBlockUpgradeMajority = 10000;
        nMinerThreads = 1;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 1 * 24;
        nCLTVStartBlock = 1;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1422234505;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1137826;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 15224;
        assert(hashGenesisBlock == uint256("0x7c51316bf1e3af0904f2dfd4519d301327e381c0ebcf98424efac738b1ad1cb6"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultCheckMemPool(bool afDefaultCheckMemPool)  { fDefaultCheckMemPool=afDefaultCheckMemPool; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
