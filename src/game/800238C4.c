typedef struct SortEntry {
    int a;
    int b;
    int key;
} SortEntry;

void func_800238C4(SortEntry *list, int count) {
    SortEntry tmp;
    SortEntry *mid;
    SortEntry *x;
    int lo;
    int hi;
    int pivot;

    if (count < 2) {
        return;
    }
    if (count == 2) {
        if (list[0].key > list[1].key) {
            tmp.b = list[0].b;
            tmp.a = list[0].a;
            tmp.key = list[0].key;
            list[0].b = list[1].b;
            list[0].a = list[1].a;
            list[0].key = list[1].key;
            list[1].b = tmp.b;
            list[1].a = tmp.a;
            list[1].key = tmp.key;
        }
        return;
    }
    lo = 1;
    hi = count - 1;
    pivot = list[0].key;
    while (lo < hi) {
        if (list[lo].key <= pivot) {
            lo++;
        } else if (list[hi].key >= pivot) {
            hi--;
        } else {
            tmp.b = list[lo].b;
            tmp.a = list[lo].a;
            tmp.key = list[lo].key;
            list[lo].b = list[hi].b;
            list[lo].a = list[hi].a;
            list[lo].key = list[hi].key;
            list[hi].b = tmp.b;
            list[hi].a = tmp.a;
            list[hi].key = tmp.key;
        }
    }
    mid = (SortEntry *)((lo * sizeof(SortEntry)) + (int)list);
    if (mid->key < pivot) {
        tmp.b = mid->b;
        tmp.a = mid->a;
        tmp.key = mid->key;
        mid->b = list->b;
        mid->a = list->a;
        mid->key = list->key;
        list->b = tmp.b;
        list->a = tmp.a;
        list->key = tmp.key;
        func_800238C4(list, lo);
        func_800238C4(mid + 1, count - lo - 1);
    } else {
        x = mid - 1;
        tmp.b = x->b;
        tmp.a = x->a;
        tmp.key = x->key;
        x->b = list->b;
        x->a = list->a;
        x->key = list->key;
        list->b = tmp.b;
        list->a = tmp.a;
        list->key = tmp.key;
        func_800238C4(list, lo - 1);
        func_800238C4(mid, count - lo);
    }
}
