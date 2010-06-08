#ifndef ____DEFINE_DENSITY_MATRIX____
#define ____DEFINE_DENSITY_MATRIX____

#include "StatesClassification.h"
#include "BitClassification.h"
#include "Hamiltonian.h"
#include "DensityMatrixPart.h"

class DensityMatrix
{
    DensityMatrixPart** parts;
    StatesClassification& S;
    Hamiltonian &H;
    RealType beta;
    
    BlockNumber NumOfBlocks;

public:
    DensityMatrix(StatesClassification& S, Hamiltonian& H, RealType beta);
    ~DensityMatrix();
    
    DensityMatrixPart& part(const QuantumNumbers &in);
    DensityMatrixPart& part(BlockNumber in);  
    
    void prepare(void);
    void compute(void);
    RealType operator()(QuantumState &state);
    RealType getBeta();
};

#endif // endif :: #ifndef ____DEFINE_DENSITY_MATRIX____