/*************************************************************************************

    Grid physics library, www.github.com/paboyle/Grid 

    Source file: ./lib/lattice/Lattice_reality.h

    Copyright (C) 2015

Author: Azusa Yamaguchi <ayamaguc@staffmail.ed.ac.uk>
Author: Peter Boyle <paboyle@ph.ed.ac.uk>
Author: neo <cossu@post.kek.jp>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    See the full license in the file "LICENSE" in the top level distribution directory
*************************************************************************************/
/*  END LEGAL */
#ifndef GRID_LATTICE_REALITY_H
#define GRID_LATTICE_REALITY_H


// FIXME .. this is the sector of the code 
// I am most worried about the directions
// The choice of burying complex in the SIMD
// is making the use of "real" and "imag" very cumbersome

NAMESPACE_BEGIN(Grid);

template<class vobj> inline Lattice<vobj> adj(const Lattice<vobj> &lhs){
  Lattice<vobj> ret(lhs.Grid());

  autoView( lhs_v, lhs, AcceleratorRead);
  autoView( ret_v, ret, AcceleratorWrite);

  ret.Checkerboard()=lhs.Checkerboard();
  accelerator_for( ss, lhs_v.size(), vobj::Nsimd(), {
    coalescedWrite(ret_v[ss], adj(lhs_v(ss)));
  });
  return ret;
};

template<class vobj> inline Lattice<vobj> conjugate(const Lattice<vobj> &lhs){
  Lattice<vobj> ret(lhs.Grid());

  autoView( lhs_v, lhs, AcceleratorRead);
  autoView( ret_v, ret, AcceleratorWrite);

  ret.Checkerboard() = lhs.Checkerboard();
  accelerator_for( ss, lhs_v.size(), vobj::Nsimd(), {
    coalescedWrite( ret_v[ss] , conjugate(lhs_v(ss)));
  });
  return ret;
};

NAMESPACE_END(Grid);

#endif
