/*
 *
 *                This source code is part of
 *
 *                 G   R   O   M   A   C   S
 *
 *          GROningen MAchine for Chemical Simulations
 *
 * Written by David van der Spoel, Erik Lindahl, Berk Hess, and others.
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2009, The GROMACS development team,
 * check out http://www.gromacs.org for more information.

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * If you want to redistribute modifications, please consider that
 * scientific software is very special. Version control is crucial -
 * bugs must be traceable. We will be happy to consider code for
 * inclusion in the official distribution, but derived work must not
 * be called official GROMACS. Details are found in the README & COPYING
 * files - if they are missing, get the official version at www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the papers on the package - you can find them in the top README file.
 *
 * For more info, check our website at http://www.gromacs.org
 */
/*! \internal \file
 * \brief
 * Declares private implementation class for gmx::OptionsAssigner.
 *
 * \author Teemu Murtola <teemu.murtola@cbr.su.se>
 * \ingroup module_options
 */
#ifndef GMX_OPTIONS_OPTIONSASSIGNER_IMPL_H
#define GMX_OPTIONS_OPTIONSASSIGNER_IMPL_H

#include "optionsassigner.h"

namespace gmx
{

class AbstractErrorReporter;

class Option;
class Options;

/*! \internal \brief
 * Private implementation class for OptionsAssigner.
 *
 * \ingroup module_options
 */
class OptionsAssigner::Impl
{
    public:
        //! Sets the option object to assign to.
        Impl(Options *options, AbstractErrorReporter *errors);

        /*! \brief
         * Stores error code for later retrieval if it is the first error.
         *
         * \param[in] code  Error code to store.
         * \returns \p code
         *
         * The first call with a non-zero \p code sets the \p _errorCode
         * attribute; later calls do nothing   The return value allows the
         * function to be used like \c "return keepError(rc);"
         */
        int keepError(int code)
        {
            if (_errorCode == 0)
            {
                _errorCode = code;
            }
            return code;
        }

        //! Returns true if a subsection has been set.
        bool inSubSection() const { return _sectionStack.size() > 1; }
        //! Returns the Options object for the current section.
        Options &currentSection() const { return *_sectionStack.back(); }

        //! Options object to assign to.
        Options                &_options;
        //! Error reporter to use for errors.
        AbstractErrorReporter  *_errors;
        /*! \brief
         * List of (sub)sections being assigned to.
         *
         * The first element always points to \a _options.
         */
        std::vector<Options *>  _sectionStack;
        //! Current option being assigned to, or NULL if none.
        Option                 *_currentOption;
        //! Keeps the error code of the first error encountered, or 0 if none.
        int                     _errorCode;
        //! Number of values assigned so far to the current option.
        int                     _currentValueCount;
        //! If true, a "no" prefix was given for the current boolean option.
        bool                    _reverseBoolean;
};

} // namespace gmx

#endif
