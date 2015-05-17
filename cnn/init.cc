#include "cnn/init.h"
#include "cnn/aligned-mem-pool.h"

#include <iostream>
#include <random>
#include <cmath>

#if HAVE_CUDA
#include "cnn/cuda.h"
#include <device_launch_parameters.h>
#endif

using namespace std;

namespace cnn {

#define ALIGN 12
AlignedMemoryPool<ALIGN>* fxs;
AlignedMemoryPool<ALIGN>* dEdfs;

mt19937* rndeng = nullptr;

void Initialize(int& argc, char**& argv) {
  cerr << "Initializing...\n";
#if HAVE_CUDA
  Initialize_GPU(argc, argv);
#else
  kSCALAR_MINUSONE = new float;
  *kSCALAR_MINUSONE = -1;
  kSCALAR_ONE = new float;
  *kSCALAR_ONE = 1;
  kSCALAR_ZERO = new float;
  *kSCALAR_ZERO = 0;
#endif
  random_device rd;
  rndeng = new mt19937(rd());
//  rndeng = new mt19937(1);
  cerr << "Allocating memory...\n";
  fxs = new AlignedMemoryPool<ALIGN>(100000000);
  dEdfs = new AlignedMemoryPool<ALIGN>(100000000);
  cerr << "Done.\n";
}

} // namespace cnn

