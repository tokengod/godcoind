// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <iostream>

#include "superblock.h"
#include "streams.h"
#include "utilstrencodings.h"
#include "version.h"
#include "chain.h"
#include "consensus/consensus.h"

//godcoin:superblock
static const uint256 SUPER_BLOCK_HASH1 = uint256S("a538753e8e81ef8a9f2be4f553ce61a2d7d30e4f8807db4743540da07bcd1080");
static const uint256 SUPER_BLOCK_HASH2 = uint256S("5826695fba4e11758a44a10598af716b83dafb529c20bf1d91df639f894932eb");
static const uint256 SUPER_BLOCK_HASH3 = uint256S("67a808a392bf285993efcf3d5c63207f0430a85fceff86cbda8ccb7d424083bb");

bool isSuperBlock(const CBlock& block) {
    return isSuperBlockHash(block.GetHash());
}

bool isSuperBlockHash(const uint256 hash) {
    return hash ==  SUPER_BLOCK_HASH1||
        hash ==  SUPER_BLOCK_HASH2 ||
        hash ==  SUPER_BLOCK_HASH3;
}

//godcoin:superblock
static const char* superBlocks[] = {"00000020d7901582a10f1d35f102eb138f21adaf82055c4c8ccd06000000000000000000e08fe1dfacf4a4dce56913a3d490cc00da07b3cd3962882452beeddaccdead654e225f5affff7f20000000000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1103c89c07000b2f503253482f627463642fffffffff010040e59c301200001976a9149e2ee6d80fcb41bef7da5cbbe142bc52925a182b88ac00000000", 
    "000000203e88ffe6026719646d93a698574cd08a0d6984d4b9e31b8ff45c1c89dc19711d0714805d9bc6d4d59a75a8d054cb8f7d31e002b917abd68301f3bd2f45d795b14e225f5affff7f20000000000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1103c99c07000b2f503253482f627463642fffffffff010088526a740000001976a9142e12023a49c3d81a98a1d8b4f6947681f5bf1e5688ac00000000",
    "00000020d0b63412f663adbfa73896196663f25437c9d28c82654d6be9efa6be8f7cf4b9fa08020834314223ceb6a6e2398a8f0db28e15575efc03c0ba09d93efbc63cb64e225f5affff7f20000000000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1103ca9c07000b2f503253482f627463642fffffffff010088526a740000001976a91435591e81072a8f2fde1617259dab02e10cc807cb88ac00000000"};

//godcoin:superblock
std::shared_ptr<CBlock> getSuperBlock(int i) {
    std::shared_ptr<CBlock> pblock = std::make_shared<CBlock>();
    CDataStream stream(ParseHex(superBlocks[i]),SER_NETWORK, PROTOCOL_VERSION);
    pblock = std::make_shared<CBlock>();
    stream >> *pblock;
    return pblock;
}

bool getSuperBlockWorkLimit(const CBlockIndex* pindexLast,unsigned int& nProofOfWorkLimit) {
    if (pindexLast != nullptr && 
            (pindexLast->nHeight + 1) >= SUPER_BLOCK_HEIGHT && 
            (pindexLast->nHeight + 1) < LAST_POW_BLOCK_HEIGHT) { 
        nProofOfWorkLimit =  UintToArith256(uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff")).GetCompact();
        return true;
    }
    return false;
}