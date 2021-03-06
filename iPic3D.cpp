
#include <mpi.h>
#include <iomanip>
#include "iPic3D.h"
#include "debug.h"
#include "TimeTasks.h"

using namespace iPic3D;

int main(int argc, char **argv) {

  iPic3D::c_Solver KCode;
  bool b_err = false;

  MPIdata::init(&argc, &argv);
  KCode.Init(argc, argv);

  for (int i = KCode.FirstCycle(); i < KCode.LastCycle(); i++) {

    if (KCode.get_myrank() == 0) cout << " ======= Cycle " << i << " ======= " << endl;

    if (!b_err) {
      timeTasks.resetCycle();
      KCode.CalculateMoments();
      KCode.CalculateField();
      b_err = KCode.ParticlesMover();
      KCode.CalculateB();

      // print out total time for all tasks
      timeTasks.print_cycle_times(i);
    }

    if (b_err) {
      i = KCode.LastCycle() + 1;
    }

#if FILE_IO
    KCode.WriteOutput(i);
    KCode.WriteConserved(i);
    KCode.WriteRestart(i);
#endif

  }

  KCode.Finalize();

  return 0;
}
