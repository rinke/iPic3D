/*******************************************************************************************************
  Grid3DCUCU.h  -  uniform cartesian 3D local grid for each process, including che guard cells
  -------------------

 *******************************************************************************************************/

#ifndef GRID3DCU_H
#define GRID3DCU_H

#include <iostream>

#include "Grid.h"
#include "CollectiveIO.h"
#include "ComInterpNodes3D.h"
#include "ComNodes3D.h"
#include "VirtualTopology3D.h"
#include "Alloc.h"

using std::cout;
using std::endl;

/**
 * Uniform cartesian local grid 3D
 *
 * @date Fri Jun 4 2008
 * @par Copyright:
 * @author Stefano Markidis, Giovanni Lapenta
 * @version 3.0
 *
 */
class Grid3DCU                  // :public Grid
{
public:
  /** constructor */
  Grid3DCU(CollectiveIO * col, VirtualTopology3D * vct);
  /** destructor */
  ~Grid3DCU();
  /** allocate grid arrays for this domain */
  void allocate(CollectiveIO * ptC, VirtualTopology3D * ptVCT);
  /** deallocate grid arrays for this domain */
  void deallocate();
  /** print grid info */
  void print(VirtualTopology3D * ptVCT);
  /** calculate a derivative along a direction on nodes */
  void derivN(doubleArr3& derN,
    doubleCar4& scFieldC, int ns, int dir);
  /** calculate gradient on nodes, given a scalar field defined on central points  */
  void gradC2N(doubleArr3& gradXN, doubleArr3& gradYN, doubleArr3& gradZN,
    doubleCar3& scFieldC);
  /** calculate gradient on nodes, given a scalar field defined on central points  */
  void gradN2C(doubleArr3& gradXC, doubleArr3& gradYC, doubleArr3& gradZC,
    doubleCar3& scFieldN);
  /** calculate divergence on central points, given a vector field defined on nodes  */
  void divN2C(doubleArr3& divC,
    doubleCar3& vecFieldXN,
    doubleCar3& vecFieldYN,
    doubleCar3& vecFieldZN);
  /** calculate divergence on nodes, given a vector field defined on central points  */
  void divC2N(doubleArr3& divN,
    doubleCar3& vecFieldXC,
    doubleCar3& vecFieldYC,
    doubleCar3& vecFieldZC);
  /** calculate curl on nodes, given a vector field defined on central points  */
  void curlC2N(doubleArr3& curlXN, doubleArr3& curlYN,
    doubleArr3& curlZN,
    doubleCar3& vecFieldXC,
    doubleCar3& vecFieldYC,
    doubleCar3& vecFieldZC);
  /** calculate curl on central points, given a vector field defined on nodes  */
  void curlN2C(doubleArr3& curlXC, doubleArr3& curlYC, doubleArr3& curlZC,
    doubleCar3& vecFieldXN,
    doubleCar3& vecFieldYN,
    doubleCar3& vecFieldZN);

  /** calculate divergence on central points, given a Tensor field defined on nodes  */
  void divSymmTensorN2C(doubleArr3& divCX, doubleArr3& divCY, doubleArr3& divCZ,
    doubleCar4& pXX,
    doubleCar4& pXY,
    doubleCar4& pXZ,
    doubleCar4& pYY,
    doubleCar4& pYZ,
    doubleCar4& pZZ, int ns);

  /** calculate laplacian on nodes, given a scalar field defined on nodes */
  void lapN2N(doubleArr3& lapN,
    doubleCar3& scFieldN, VirtualTopology3D * vct);
  /** calculate laplacian on central points, given a scalar field defined on central points for Poisson */
  void lapC2Cpoisson(doubleArr3& lapC,
    doubleArr3& scFieldC, VirtualTopology3D * vct);
  /** calculate laplacian on central points, given a scalar field defined on central points */
  void lapC2C(doubleArr3& lapC,
    doubleCar3& scFieldC, VirtualTopology3D * vct);

  /** calculate divergence on boundaries */
  void divBCleft(doubleArr3& divBC,
    doubleCar3& vectorX,
    doubleCar3& vectorY,
    doubleCar3& vectorZ, int leftActiveNode, int dirDER);
  /** calculate divergence on boundaries */
  void divBCright(doubleArr3& divBC,
    doubleCar3& vectorX,
    doubleCar3& vectorY,
    doubleCar3& vectorZ, int rightActiveNode, int dirDER);
  /** calculate derivative on boundaries */
  void derBC(doubleArr3& derBC,
    doubleCar3& vector, int leftActiveNode, int dirDER);


  /** interpolate on nodes from central points */
  void interpC2N(doubleArr3& vecFieldN, doubleCar3& vecFieldC);
  /** interpolate on central points from nodes */
  void interpN2C(doubleArr3& vecFieldC, doubleCar3& vecFieldN);
  /** interpolate on central points from nodes */
  void interpN2C(doubleArr4& vecFieldC, int ns, doubleCar4& vecFieldN);

  // /////////// PRIVATE VARIABLES //////////////
private:
  /** number of cells - X direction, including + 2 (guard cells) */
  int nxc;
  /** number of nodes - X direction, including + 2 extra nodes for guard cells */
  int nxn;
  /** number of cell - Y direction, including + 2 (guard cells) */
  int nyc;
  /** number of nodes - Y direction, including + 2 extra nodes for guard cells */
  int nyn;
  /** number of cell - Z direction, including + 2 (guard cells) */
  int nzc;
  /** number of nodes - Z direction, including + 2 extra nodes for guard cells */
  int nzn;
  /** dx = space step - X direction */
  double dx;
  /** dy = space step - Y direction */
  double dy;
  /** dz = space step - Z direction */
  double dz;
  /** invdx = 1/dx */
  double invdx;
  /** invdy = 1/dy */
  double invdy;
  /** invdz = 1/dz */
  double invdz;
  /** invol = inverse of volume*/
  double invVOL;
  /** node coordinate */
  double *node_xcoord;
  double *node_ycoord;
  double *node_zcoord;
  /** center coordinate */
  double *center_xcoord;
  double *center_ycoord;
  double *center_zcoord;
  /** local grid boundaries coordinate  */
  double xStart, xEnd, yStart, yEnd, zStart, zEnd;

public: // accessors (inline)
  int getNXC() { return (nxc); }
  int getNXN() { return (nxn); }
  int getNYC() { return (nyc); }
  int getNYN() { return (nyn); }
  int getNZC() { return (nzc); }
  int getNZN() { return (nzn); }
  double getDX() { return (dx); }
  double getDY() { return (dy); }
  double getDZ() { return (dz); }
  //
  // coordinate accessors
  //
  // calculated equivalents (preferred for accelerator?):
  //const double &calcXN(int X) { return xStart+(X-1)*dx;}
  //const double &calcYN(int Y) { return yStart+(Y-1)*dy;}
  //const double &calcZN(int Z) { return zStart+(Z-1)*dz;}
  const double &getXN(int X) { return node_xcoord[X];}
  const double &getYN(int Y) { return node_ycoord[Y];}
  const double &getZN(int Z) { return node_zcoord[Z];}
  const double &getXC(int X) { return center_xcoord[X];}
  const double &getYC(int Y) { return center_ycoord[Y];}
  const double &getZC(int Z) { return center_zcoord[Z];}
  //
  // The following could be eliminated in favor of the previous
  // unless we truly anticipate generalizing to a deformed
  // logically cartesian mesh.  See issue #40.
  //
  const double &getXN(int X, int Y, int Z) { return node_xcoord[X];}
  const double &getYN(int X, int Y, int Z) { return node_ycoord[Y];}
  const double &getZN(int X, int Y, int Z) { return node_zcoord[Z];}
  const double &getXC(int X, int Y, int Z) { return center_xcoord[X];}
  const double &getYC(int X, int Y, int Z) { return center_ycoord[Y];}
  const double &getZC(int X, int Y, int Z) { return center_zcoord[Z];}
  //
  double getXstart() { return (xStart); }
  double getXend() { return (xEnd); }
  double getYstart() { return (yStart); }
  double getYend() { return (yEnd); } 
  double getZstart() { return (zStart); }
  double getZend() { return (zEnd); }
  double getInvVOL() { return (invVOL); }
};

typedef Grid3DCU Grid;

#endif
