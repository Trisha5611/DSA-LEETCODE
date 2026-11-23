

typedef struct {
    int prefix[40001];
    int size;
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* obj = malloc(sizeof(ProductOfNumbers));
    obj->size = 0;
    obj->prefix[0] = 1;
    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 0;
        obj->prefix[0] = 1;
    } else {
        obj->prefix[obj->size + 1] =
            obj->prefix[obj->size] * num;
        obj->size++;
    }
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    if (k > obj->size)
        return 0;

    return obj->prefix[obj->size] /
           obj->prefix[obj->size - k];
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj);
}
