int search(int nums[], int x)
{
    int low = 0, mid, high, item;

    high = length -1;
    while (low  < high)
    {
        mid = (low + high)/2;
        item = nums[mid];
        printf("->%d\n", item);

        if (x == item)
           return mid;
        else if (x < item)
            high = mid - 1;
         else
             low = mid + 1;
    }
    return(-1);
}

