/** \file src/DensityMatrixPart.h
** \brief Part (diagonal block) of a density matrix.
**
** \author Igor Krivenko (igor@shg.ru)
** \author Andrey Antipov (antipov@ct-qmc.org)
*/
#ifndef __INCLUDE_DENSITYMATRIXPART_H
#define __INCLUDE_DENSITYMATRIXPART_H

#include "Dumper.h"
#include "HamiltonianPart.h"

/** This class represents a part of a density matrix.
 * It is responsible for calculations of exponential weights
 * and a contribution to the partition function made by the corresponding
 * block of the Hamiltonian.
 */
#ifdef pomerolHDF5
class DensityMatrixPart : public Dumpable
#else
class DensityMatrixPart
#endif
{
    /** A reference to a part of a Hamiltonian. */
    HamiltonianPart& hpart;
    /** The inverse temperature. */
    RealType beta;
    /** The ground energy of the Hamiltonian.
     * It is subtracted from all energy levels to avoid
     * large non-normalized weights and possible loss of precision.
     */
    RealType GroundEnergy;

    /** The number of states in this part. */
    QuantumState partSize;
    /** A real vector holding all weights in this part. */
    RealVectorType weights;

    /** A contribution to the partition function. */
    RealType Z_part;

public:
    /** Constructor.
     * \param[in] hpart A reference to a part of the Hamiltonian.
     * \param[in] beta The inverse temperature.
     * \param[in] GroundEnergy The ground state energy of the Hamiltonian.
     */
    DensityMatrixPart(HamiltonianPart& hpart, RealType beta, RealType GroundEnergy);
    /** Divide all the weights by the partition function.
     * 
     * Warning! Must be called once and only once!
     * \param[in] Z The partition function.
     */
    void normalize(RealType Z);

    /** Returns an averaged value of the energy. */
    RealType getAverageEnergy(void);
    /** Performs computations of the weights and a contribution to the partition function. */
    RealType compute(void);
    /** Returns the weight corresponding to a specified number of state.
     * \param[in] m A number of a state inside this part.
     */
    RealType weight(int m);
    /** Returns the inverse temperature. */
    RealType getBeta();

    /** Returns the number of the state, which has the lowest statistical weight before exceeding TruncationTolerance 
     * \param[in] TruncationTolerance - the level at which the statistical weight should be cutted
     */
    InnerQuantumState getMaximumTruncationState( RealType TruncationTolerance);
#ifdef pomerolHDF5 
    void dumpIt(H5::CommonFG* FG) const;
#endif
};

#endif // endif :: #ifndef __INCLUDE_DENSITYMATRIXPART_H
