#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die( const char *message )
{
    if ( errno ) {
        perror( message );
    } else {
        printf("ERROR: %s\n", message);
    }
}

int sorted_order( int a , int b )
{
    return a - b;
}

int reverse_order( int a , int b )
{
    return b -a;
}

int strange_order( int a , int b  )
{
    if ( a == 0 || b == 0 ) {
        return 0;
    } else {
        return a % b;
    }
}

/*
 * typedef creates a fake type,
 * in this case for a function pointer
 */
typedef int (*compare_cb)( int a , int b );

/*
 * HEAP: return formatted array as type pointer bc original data is kept in HEAP
 */
int *bubble_sort( int *numbers , int count , compare_cb compare )
{
    int temp = 0;
    int i = 0;
    int j = 0;
    /*
     * HEAP: keeps formatted, rearranged array bc original is also there and is freed in last line of test_sorting function
     */
    int *sorted = (int *)malloc( sizeof(int) * count );

    if ( !sorted ) {
        die( "There was a problem allocating heap memory in bubble_sort\n" );
    }

    /*does actual copy from heap location to heap location*/
    memcpy( sorted , numbers , count * sizeof( int ) );

    for (i = 0; i < count; ++i) {
        for (j = 0; j < count -1; ++j) {
            if ( compare( sorted[j] , sorted[j+1] ) > 0 ) {
                temp = sorted[j+1];
                sorted[j+1] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    return sorted;
}

/*
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out
 */
void test_sorting( int *numbers , int count , compare_cb compare )
{
    int i = 0;
    /*
     * HEAP: returns formatted rearranged numbers bc original is in HEAP and in freed at end of this function
     */
    int *sorted = bubble_sort( numbers , count , compare );

    if ( !sorted ) {
        die( "Failed to sort in test_sorting function\n" );
    }

    for (i = 0; i < count; ++i) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free( sorted );
}

int main(int argc, char *argv[])

{
    if ( argc < 2 ) {
        printf( "ERROR: >2 paramenter must be passed, ex: ./ex18 0 3 5 4 8 9 " );
    }

    int i = 0;
    int count = argc - 1;
    char **inputs = argv + 1;

    /*
     * HEAP: keeps numbers passed in program and frees heap space at end of this funtion
     */
    int *numbers = (int *)malloc( count * sizeof( int ) );
    if ( !numbers ) {
        die( "Memory Error" );
    }

    for (i = 0; i < count; ++i) {
        numbers[ i ] = atoi( inputs[ i ] );
    }

    test_sorting( numbers , count , sorted_order );
    test_sorting( numbers , count , reverse_order );
    test_sorting( numbers , count , strange_order );

    free( numbers );

    return 0;
} 
