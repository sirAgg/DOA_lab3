#include <iostream>
#include <cstdlib>
#include <time.h>


using namespace std;

struct __RetStruct {
    int largest;
    int smallest;
    int nominator;   // täljare
    int denominator; // nämnare
};

__RetStruct largest_quota(int* arr, int size)
{
    if( size <= 2 )
    {
        return __RetStruct{
            (arr[0] < arr[1]) ? 1 : 0,
            (arr[0] > arr[1]) ? 1 : 0,
            1,
            0,
        };
    }
    else if ( size == 3 )
    {
        __RetStruct ret;

        double first_middle_q = (double)arr[1]/(double)arr[0];
        double middle_last_q = (double)arr[2]/(double)arr[1];
        double first_last_q = (double)arr[2]/(double)arr[0];

        if( first_middle_q > middle_last_q && first_middle_q > first_last_q )
        {
            ret.nominator = 1;
            ret.denominator = 0;
        }
        else if( middle_last_q > first_last_q && middle_last_q > first_middle_q )
        {
            ret.nominator = 2;
            ret.denominator = 1;
        }
        else
        {
            ret.nominator = 2;
            ret.denominator = 0;
        }

        ret.largest = (arr[0] < arr[1]) ? 1 : 0; // Find MAX
        ret.largest = (arr[ret.largest] < arr[2]) ? 2 : ret.largest;
        ret.smallest = (arr[0] > arr[1]) ? 1 : 0; // Find MAX
        ret.smallest = (arr[ret.smallest] > arr[2]) ? 2 : ret.smallest;
        return ret;
    }
    else
    {
        __RetStruct left = largest_quota(arr, size/2);
        __RetStruct right = largest_quota(arr + size/2, size-size/2);
        right.largest += size/2;
        right.smallest += size/2;
        right.denominator += size/2;
        right.nominator += size/2;

        double left_q = (double)arr[left.nominator]/(double)arr[left.denominator];
        double right_q = (double)arr[right.nominator]/(double)arr[right.denominator];
        double qouta = (double)arr[right.largest]/(double)arr[left.smallest];

        __RetStruct ret;

        if( left_q > right_q && left_q > qouta )
        {
            ret.nominator = left.nominator;
            ret.denominator = left.denominator;
        }
        else if( right_q > qouta && right_q > left_q )
        {
            ret.nominator = right.nominator;
            ret.denominator = right.denominator;
        }
        else
        {
            ret.nominator = right.largest;
            ret.denominator = left.smallest;
        }

        ret.largest = (arr[left.largest] < arr[right.largest]) ? right.largest : left.largest;
        ret.smallest = (arr[left.smallest] > arr[right.smallest]) ? right.smallest : left.smallest;

        // cout << ret.nominator << '/' << ret.denominator << " " << ret.largest << "|" << ret.smallest << endl;
        return ret;
    }
}

__RetStruct largest_qouta_bad(int* arr, int size)
{
    __RetStruct ret;

    ret.denominator = 0;
    ret.nominator = 1;
    double largest_q = (double)arr[ret.nominator]/(double)arr[ret.denominator];

    for(int i = 0; i < size; i++)
    {
        for(int j = i+1; j < size; j++)
        {
            double q = (double)arr[j]/(double)arr[i];
            if (q > largest_q)
            {
                ret.denominator = i;
                ret.nominator = j;
                largest_q = q;
            }
        }
    }

    return ret;
}

int main(int argc, char *argv[])
{
    //
    // CUSTOM TEST CASES
    //
    int custom_test_arr[5][9] = {
        {3,2,8,6,3,2,8,6,1},
        {9,8,7,6,5,4,3,2,1},
        {1,2,3,4,5,6,7,8,9},
        {1,1,1,1,1,1,1,1,1},
        {2,2,2,2,2,2,1,1,1},
    };

    for(int i = 0; i < sizeof(custom_test_arr)/sizeof(custom_test_arr[0]); i++)
    {
        __RetStruct ret = largest_quota(custom_test_arr[i], sizeof(custom_test_arr[0])/sizeof(custom_test_arr[0][0]));
        cout << custom_test_arr[i][ret.nominator] << '/' << custom_test_arr[i][ret.denominator] << " " << custom_test_arr[i][ret.largest] << "|" << custom_test_arr[i][ret.smallest] << endl;
    }


    //
    // TEST PARAMETERS
    //
    int size = 1000;
    int n_tests = 10000;

    int seed = time(NULL);


    int n_fails = 0;
    int* test_arr = new int[size];
    for (int _test = 0; _test < n_tests; _test++)
    {
        srand(seed);
        for (int i = 0; i < size; i++)
            test_arr[i] = rand() % 10000 +1;

        __RetStruct res = largest_quota(test_arr, size);

        __RetStruct bres = largest_qouta_bad(test_arr, size);

        if(!(test_arr[bres.nominator ]== test_arr[res.nominator ]&& test_arr[bres.denominator ]== test_arr[res.denominator]))
        {
            cout << "Failed with seed : " << seed << "\n" << test_arr[res.nominator] << '/' << test_arr[res.denominator] << " [" << res.nominator << "]/[" << res.denominator << "]" << endl;
            cout << test_arr[bres.nominator] << '/' << test_arr[bres.denominator] << " [" << bres.nominator << "]/[" << bres.denominator << "]" << endl;
            n_fails++;
        }
        seed *= 3 + 1;
    }

    cout << "Failed " << n_fails << " times out of " << n_tests << " tests." << endl;

    return 0;
}
