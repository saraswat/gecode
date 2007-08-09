#!/bin/sh
#
#  Main authors:
#     Guido Tack <tack@gecode.org>
#
#  Copyright:
#     Guido Tack, 2006
#
#  Last modified:
#     $Date$ by $Author$
#     $Revision$
#
#  This file is part of Gecode, the generic constraint
#  development environment:
#     http://www.gecode.org
#
#  Permission is hereby granted, free of charge, to any person obtaining
#  a copy of this software and associated documentation files (the
#  "Software"), to deal in the Software without restriction, including
#  without limitation the rights to use, copy, modify, merge, publish,
#  distribute, sublicense, and/or sell copies of the Software, and to
#  permit persons to whom the Software is furnished to do so, subject to
#  the following conditions:
#
#  The above copyright notice and this permission notice shall be
#  included in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
#  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
#  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
#  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#

set -e

# List of file extensions for which properties should be set
KEYWORDEXTS="cc icc hh sh perl ac in"

for ext in ${KEYWORDEXTS}; do
    find . -name "*.$ext" ! -wholename './contribs/*' -prune \
    -exec svn propset svn:keywords 'Author Date Id Revision' "{}" ";"
done

# List of normal directories to set ignore properties on
NORMALDIRS="int iter kernel minimodel search set support"

for dir in ${NORMALDIRS}; do
    find . -type d -wholename "./gecode/$dir*" \
	! -wholename '*.svn*' \
	-exec svn propset svn:ignore -F misc/svn-ignore.txt '{}' \;
done
find . -type d -wholename "./test*" \
    ! -wholename '*.svn*' \
    -exec svn propset svn:ignore -F misc/svn-ignore.txt '{}' \;

