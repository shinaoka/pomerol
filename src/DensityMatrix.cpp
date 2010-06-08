#include "DensityMatrix.h"

DensityMatrix::DensityMatrix(StatesClassification& S, Hamiltonian& H, RealType beta) : 
    parts(0), S(S), H(H), beta(beta)
{}

DensityMatrix::~DensityMatrix()
{
    if(parts)
        for(BlockNumber n = 0; n < NumOfBlocks; n++) delete parts[n];
    delete[] parts;
}

void DensityMatrix::prepare(void)
{
    NumOfBlocks = S.NumberOfBlocks();
    RealType GroundEnergy = H.getGroundEnergy();
    parts = new DensityMatrixPart* [NumOfBlocks];
    for(BlockNumber n = 0; n < NumOfBlocks; n++) parts[n] = new DensityMatrixPart(H.part(n),beta,GroundEnergy);
}

void DensityMatrix::compute(void)
{
    RealType Z = 0;
    for(BlockNumber n = 0; n < NumOfBlocks; n++) Z += parts[n]->compute();
    for(BlockNumber n = 0; n < NumOfBlocks; n++) parts[n]->normalize(Z);
    cout << "Partition Function = " << Z << endl;
}

RealType DensityMatrix::operator()( QuantumState &state )
{
    int inner_state = S.getInnerState(state);
    BlockNumber block_num = S.getBlockNumber(S.getStateInfo(state));
    
    return parts[block_num]->weight(inner_state);
}

DensityMatrixPart& DensityMatrix::part(const QuantumNumbers &in)
{
    return *parts[S.getBlockNumber(in)];
}

DensityMatrixPart& DensityMatrix::part(BlockNumber in)
{
    return *parts[in];
}

RealType DensityMatrix::getBeta()
{
	return beta;
}