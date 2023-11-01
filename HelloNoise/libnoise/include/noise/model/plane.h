// plane.h
//
// Copyright (C) 2004 Owen Jacobson
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (COPYING.txt) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The developer's email is ojacobson@lionsanctuary.net
//

#ifndef NOISE_MODEL_PLANE_H
#define NOISE_MODEL_PLANE_H

#include <assert.h>
#include "../module/modulebase.h"

namespace noise
{

  namespace model
  {
    /// @addtogroup libnoise
    /// @{

    /// @addtogroup models
    /// @{

    /// Model that defines the surface of a plane.
    ///
    /// This model returns an output value from a noise module given the
    /// coordinates of an input value located on the surface of an ( @a x,
    /// @a z ) plane.
    ///
    /// To generate an output value, pass the ( @a x, @a z ) coordinates of
    /// an input value to the GetValue() method.
    ///
    /// This model is useful for creating:
    /// - two-dimensional textures
    /// - terrain height maps for local areas
    ///
    /// This plane extends infinitely in both directions.
    class NOISE_EXPORT Plane
    {

      public:

        /// Constructor.
        Plane ();

        /// Constructor
        ///
        /// @param module The noise module that is used to generate the output
        /// values.
        Plane (const module::Module& module);

        /// Returns the noise module that is used to generate the output
        /// values.
        ///
        /// @returns A reference to the noise module.
        ///
        /// @pre A noise module was passed to the SetModule() method.
        const module::Module& GetModule () const
        {
          assert (m_pModule != NULL);
          return *m_pModule;
        }

        /// Returns the output value from the noise module given the
        /// ( @a x, @a z ) coordinates of the specified input value located
        /// on the surface of the plane.
        ///
        /// @param x The @a x coordinate of the input value.
        /// @param z The @a z coordinate of the input value.
        ///
        /// @returns The output value from the noise module.
        ///
        /// @pre A noise module was passed to the SetModule() method.
        ///
        /// This output value is generated by the noise module passed to the
        /// SetModule() method.
        double GetValue (double x, double z) const;

        /// Sets the noise module that is used to generate the output values.
        ///
        /// @param module The noise module that is used to generate the output
        /// values.
        ///
        /// This noise module must exist for the lifetime of this object,
        /// until you pass a new noise module to this method.
        void SetModule (const module::Module& module)
        {
          m_pModule = &module;
        }

      private:

        /// A pointer to the noise module used to generate the output values.
        const module::Module* m_pModule;

    };

    /// @}

    /// @}

  }

}

#endif
