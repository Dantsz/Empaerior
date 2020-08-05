#pragma once
#include "defines/basic_defines.h"
namespace Empaerior
{
template <length_t width , length_t height, typename type>
    struct mat
    {
        type elements[height][width] ={0};

        type* operator[](length_t index)
        {
            return elements[index];
        }

        type const*  operator[](length_t index) const
        {
            return elements[index];
        }

    };


    template<length_t width , length_t height,typename type>
    void operator +=(Empaerior::mat<width,height,type>& m1, const Empaerior::mat<width,height,type> & m2)
    {
        for(length_t i = 0 ;i < height;  i++)
        {
            for(length_t j = 0 ; j < width ; j++)
            {
                m1[i][j] +=m2[i][j];
            }
        }
    }




    template<length_t width , length_t height,typename type>
    void operator -=(Empaerior::mat<width,height,type>& m1, const Empaerior::mat<width,height,type> & m2)
    {
        for(length_t i = 0 ;i < height;  i++)
        {
            for(length_t j = 0 ; j < width ; j++)
            {
                m1[i][j] -=m2[i][j];
            }
        }
    }


    //indentity is for square matrices , cmm
    template<length_t dim , typename type>
    constexpr Empaerior::mat<dim, dim,type> identity_mat()
    {
        mat<width, height, type> temp;
        for (length_t i = 0; i < dim; i++)
        {
            temp[i][i] = 0;
        }
        return temp;
        

    }


    //debug for printing mat
    template < length_t width, length_t height, typename type>
    void print_mat(const Empaerior::mat<width, height, type>& mat)
    {
        for (length_t i = 0; i < height; i++)
        {
            for (length_t j = 0; j < width; j++)
            {
                std::cout << mat[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    //returns a transposed matrix
    template < length_t width, length_t height, typename type>
    Empaerior::mat<width, height, type> get_transposed(const Empaerior::mat<width, height, type>& mat)
    {
        //width and nheight switch
        mat<height, width, type> transposed_mat;
        for (length_t i = 0; i < width; i++)
        {
            for (length_t j = 0; j < height; j++)
            {
                get_transposed[i][j] = mat[j][i];
            }
        }
        return transposed_mat;
    }


    template < length_t width, length_t height, typename type>
    Empaerior::mat<width, height, type> trasnpose(Empaerior::mat<width, height, type>& mat)
    {
        mat = get_transposed(mat);
    }


    //multiplication 
    //TODO :  IMPLEMENT


}
