/********************************************************************************
*    Blockchain is a sample program to to introduce into blockchain technology  *
*    Copyright (C) 2020  Łukasz Buśko                                           *
*                                                                               *
*    This program is free software: you can redistribute it and/or modify       *
*    it under the terms of the GNU General Public License as published by       *
*    the Free Software Foundation, either version 3 of the License, or          *
*    (at your option) any later version.                                        *
*                                                                               *
*    This program is distributed in the hope that it will be useful,            *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*    GNU General Public License for more details.                               *
*                                                                               *
*    You should have received a copy of the GNU General Public License          *
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
*********************************************************************************/
#include <stdexcept>
#include <typeinfo>

template<typename R, typename T>
R narrow_cast(T in) {
    R out = static_cast<R>(in);
    if (out != in) {
        std::cerr << typeid(T).name() << " [" << in << "] to " << typeid(R).name() << " [" << out <<"]" << std::endl; 
        throw std::out_of_range("narrow_cast");
    }
    return out;
}
