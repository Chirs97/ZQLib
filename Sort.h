#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace ZQLib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator =(const Sort&);

    template<typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template<typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool minTomax)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while((i <= mid) && (j <= end))
        {
            if(minTomax ? (src[i] < src[j]) : (src[i] > src[j]))
            {
                helper[k++] = src[i++];
            }
            else
            {
                helper[k++] = src[j++];
            }
        }

        while(i <= mid)
        {
            helper[k++] = src[i++];
        }

        while(j <= end)
        {
            helper[k++] = src[j++];
        }

        for(i = begin; i <= end; i++)
        {
            src[i] = helper[i];
        }
    }

    template<typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool minTomax)
    {
        if(begin != end)
        {
            int mid = (begin + end) / 2;
            Merge(src, helper, begin, mid, minTomax);
            Merge(src, helper, mid + 1, end, minTomax);
            Merge(src, helper, begin, mid, end, minTomax);
        }
    }

    template<typename T>
    static int Partition(T array[], int begin, int end, bool minTomax)
    {
        T pv = array[begin];

        while(begin < end)
        {
            while((begin < end) && (minTomax ? (array[end] > pv) : (array[end] < pv)))
            {
                end--;
            }
            Swap(array[begin], array[end]);

            while((begin < end) && (minTomax ? (array[begin] <= pv) : (array[begin] >= pv)))
            {
                begin++;
            }
            Swap(array[begin], array[end]);
        }

        array[begin] = pv;
        return begin;
    }

    template<typename T>
    static void Quick(T array[], int begin, int end, bool minTomax)
    {
        if(begin < end)
        {
            int pivot = Partition(array, begin, end, minTomax);

            Quick(array, begin, pivot-1, minTomax);
            Quick(array, pivot+1, end, minTomax);
        }
    }


public:
    template<typename T>
    static void Select(T array[], int len, bool minTomax = true)
    {
        for(int i = 0; i < len; i++)
        {
            int min = i;
            for(int j = i + 1; j < len; j++)
            {
                if(minTomax ? (array[min] > array[j]) : (array[min] < array[j]))
                {
                    min = j;

                }
            }

            if(min != i)
            {
                Swap(array[i], array[min]);
            }
        }
    }

    template<typename T>
    static void Insert(T array[], int len, bool minTomax = true)
    {
        for(int i = 1; i < len; i++)
        {
            int k = i;
            T e = array[i];

            for(int j = i - 1; (j >= 0) && (minTomax ? (array[j] > e) : (array[j] < e)); j--)
            {
                array[j+1] = array[j];
                k = j;
            }

            if(k != i)
            {
                array[k] = e;
            }
        }
    }

    template<typename T>
    static void Bubble(T array[], int len, bool minTomax = true)
    {
        bool exchange = true;
        for(int i = 0; (i < len) && exchange; i++)
        {
            exchange = false;
            for(int j = len - 1; j > i; j--)
            {
                if(minTomax ? (array[j] < array[j - 1]) : (array[j] > array[j - 1]))
                {
                    Swap(array[j], array[j - 1]);
                    exchange = true;
                }
            }
        }
    }

    template<typename T>
    static void Shell(T array[], int len, bool minTomax = true)
    {
        int d =len;

        do
        {
            d = d/3 + 1;

            for(int i=d; i<len; i+=d)
            {
                int k = i;
                T e = array[i];

                for(int j = i - d; (j >= 0) && (minTomax ? (array[j] > e) : (array[j] < e)); j-=d)
                {
                    array[j+d] = array[j];
                    k = j;
                }

                if(k != i)
                {
                    array[k] = e;
                }
            }
        }while(d > 1);
    }

    template<typename T>
    static void Merge(T array[], int len, bool minTomax = true)
    {
        T* helper = new T[len];

        if(helper != NULL)
        {
            Merge(array, helper, 0, len-1, minTomax);
        }

        delete[] helper;
    }

    template<typename T>
    static void Quick(T array[], int len, bool minTomax = true)
    {
        Quick(array, 0, len-1, minTomax);
    }

    template<typename T>
    static void Select(Array<T>& array, bool minTomax = true)
    {
        Select(array.array(), array.Length(), minTomax);
    }

    template<typename T>
    static void Insert(Array<T>& array, bool minTomax = true)
    {
        Insert(array.array(), array.Length(), minTomax);
    }

    template<typename T>
    static void Bubble(Array<T>& array, bool minTomax = true)
    {
        Bubble(array.array(), array.Length(), minTomax);
    }

    template<typename T>
    static void Shell(Array<T>& array, bool minTomax = true)
    {
        Shell(array.array(), array.Length(), minTomax);
    }

    template<typename T>
    static void Merge(Array<T>& array, bool minTomax = true)
    {
        Merge(array.array(), array.Length(), minTomax);
    }

    template<typename T>
    static void Quick(Array<T>& array, bool minTomax = true)
    {
        Quick(array.array(), array.Length(), minTomax);
    }

};

}

#endif // SORT_H
