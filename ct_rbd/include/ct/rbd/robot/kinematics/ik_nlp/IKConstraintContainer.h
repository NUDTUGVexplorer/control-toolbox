/**********************************************************************************************************************
This file is part of the Control Toolbox (https://adrlab.bitbucket.io/ct), copyright by ETH Zurich, Google Inc.
Licensed under Apache2 license (see LICENSE file in main directory)
**********************************************************************************************************************/

#pragma once

#include <ct/rbd/robot/Kinematics.h>
#include <ct/rbd/state/RBDState.h>
#include "JointLimitConstraints.h"

namespace ct {
namespace rbd {

/*!
 * @brief Inverse Kinematics constraint container
 * @warning currently this works only with fix-base systems
 */
template <typename KINEMATICS, typename SCALAR = double>
class IKConstraintsContainer final : public ct::optcon::tpl::DiscreteConstraintContainerBase<SCALAR>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    using JointPosition = typename ct::rbd::JointState<KINEMATICS::NJOINTS, SCALAR>::Position;

    IKConstraintsContainer(std::shared_ptr<ct::optcon::tpl::OptVector<SCALAR>> optVector,
        const JointPosition& lowerBound,
        const JointPosition& upperBound)
        : optVector_(optVector)
    {
        auto jointLimits = std::shared_ptr<JointLimitConstraints<KINEMATICS, SCALAR>>(
            new JointLimitConstraints<KINEMATICS, SCALAR>(optVector_, lowerBound, upperBound));
        this->constraints_.push_back(jointLimits);
    }

    ~IKConstraintsContainer() override = default;

    void prepareEvaluation() override { /* do nothing*/}

    void prepareJacobianEvaluation() override { /* do nothing*/}

private:
    std::shared_ptr<ct::optcon::tpl::OptVector<SCALAR>> optVector_;
};

}  // namespace rbd
}  // namespace ct
