int calc_changes(int sum, int num_nom, int *changes, int *nom) {
    if(changes == NULL || nom == NULL)
        abort();

    if(sum == 0) return 0;

    for(int is = 0; is < sum; is++){
        int min = INT_MAX;
        for(int in = 0; in < num_nom; in++){
            int step = is - nom[in];

            if(step > 0 && changes[step] < min)
                min = changes[step];
        }
        if(min != INT_MAX)
            changes[is] = min + 1;
        else
            changes[is] = INT_MAX;
    }

    return changes[sum];
}
