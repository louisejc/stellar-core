#pragma once

// Copyright 2019 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"

namespace stellar
{

class AbstractLedgerTxn;

class BaseManageOfferOpFrame : public OperationFrame
{
    Asset const mSheep;
    Asset const mWheat;
    uint64_t const mOfferID;
    Price const mPrice;

    bool const mPassive;

    bool checkOfferValid(AbstractLedgerTxn& lsOuter);

    bool computeOfferExchangeParameters(AbstractLedgerTxn& ltxOuter,
                                        bool creatingNewOffer,
                                        int64_t& maxSheepSend,
                                        int64_t& maxWheatReceive);

    LedgerEntry buildOffer(int64_t amount, uint32_t flags) const;

  public:
    BaseManageOfferOpFrame(Operation const& op, OperationResult& res,
                           TransactionFrame& parentTx, Asset const& sheep,
                           Asset const& wheat, uint64_t offerID,
                           Price const& price, bool passive);

    bool doApply(AbstractLedgerTxn& lsOuter) override;

    virtual bool isDeleteOffer() = 0;

    virtual int64_t getOfferBuyingLiabilities() = 0;
    virtual int64_t getOfferSellingLiabilities() = 0;

    virtual void applyOperationSpecificLimits(int64_t& maxSheepSend,
                                              int64_t sheepSent,
                                              int64_t& maxWheatReceive,
                                              int64_t wheatReceived) = 0;
    virtual void getExchangeParametersBeforeV10(int64_t& maxSheepSend,
                                                int64_t& maxWheatReceive) = 0;

    virtual bool isResultSuccess() = 0;
    virtual ManageOfferSuccessResult& getSuccessResult() = 0;

    virtual void setResultSuccess() = 0;
    virtual void setResultSellNoTrust() = 0;
    virtual void setResultBuyNoTrust() = 0;
    virtual void setResultSellNotAuthorized() = 0;
    virtual void setResultBuyNotAuthorized() = 0;
    virtual void setResultLineFull() = 0;
    virtual void setResultUnderfunded() = 0;
    virtual void setResultCrossSelf() = 0;
    virtual void setResultSellNoIssuer() = 0;
    virtual void setResultBuyNoIssuer() = 0;
    virtual void setResultNotFound() = 0;
    virtual void setResultLowReserve() = 0;
};
}
